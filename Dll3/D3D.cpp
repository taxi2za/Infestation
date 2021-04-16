#include "Headers.h"

D3DRenderer pDXRend;
int ScreenCenterX, ScreenCenterY;


void D3DRenderer::TextEsp(int x, int y, D3DCOLOR dwColour, ID3DXFont* Font, const char* text, ...)
{
	RECT rct;
	rct.left = x - 1;
	rct.right = x + 1;
	rct.top = y - 1;
	rct.bottom = y + 1;

	va_list va_alist;
	char logbuf[256] = { 0 };
	va_start(va_alist, text);
	_vsnprintf(logbuf + strlen(logbuf), sizeof(logbuf) - strlen(logbuf), text, va_alist);
	va_end(va_alist);

	Font->DrawTextA(0, logbuf, -1, &rct, /*DT_CENTER |*/ DT_NOCLIP, dwColour);
}

void D3DRenderer::DrawTextImGui(float x, float y, Color color, const char* Format, ...)
{
	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);
	ImDrawList* draw_list = ImGui::GetWindowDrawList();
	draw_list->PushClipRectFullScreen();
	draw_list->AddText(ImVec2(x, y), color.GetU32(), Buffer);
}

HRESULT D3DRenderer::GenerateTexture(IDirect3DDevice9 *pD3Ddev, IDirect3DTexture9 **ppD3Dtex, DWORD colour32)
{
	if (FAILED(pD3Ddev->CreateTexture(8, 8, 1, 0, D3DFMT_A4R4G4B4, D3DPOOL_MANAGED, ppD3Dtex, NULL)))
		return E_FAIL;

	WORD colour16 = ((WORD)((colour32 >> 28) & 0xF) << 12)
		| (WORD)(((colour32 >> 20) & 0xF) << 8)
		| (WORD)(((colour32 >> 12) & 0xF) << 4)
		| (WORD)(((colour32 >> 4) & 0xF) << 0);
	D3DLOCKED_RECT d3dlr;
	(*ppD3Dtex)->LockRect(0, &d3dlr, 0, 0);
	WORD *pDst16 = (WORD*)d3dlr.pBits;
	for (int xy = 0; xy < 8 * 8; xy++)
		*pDst16++ = colour16;
	(*ppD3Dtex)->UnlockRect(0);
	return S_OK;
}


void D3DRenderer::DrawLine(float x1, float y1, float x2, float y2, Color clr, float thickness = 1.5f)
{
	ImGuiRender._drawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), clr.GetU32(), thickness);
}

void D3DRenderer::DrawRect(int x, int y, int w, int h,  Color clr, int thickness)
{
	ImGuiRender._drawList->AddRect(ImVec2(x, y), ImVec2(x + w, y + h),  clr.GetU32(), 0, 0, thickness);
}

void D3DRenderer::DrawFilledRect(int x, int y, int w, int h,  Color clr)
{
	ImGuiRender._drawList->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h),  clr.GetU32(), 0, 0);
}

void D3DRenderer::DrawCircleFilled(int x, int y, int radius,  Color clr, int segments)
{
	ImGuiRender._drawList->AddCircleFilled(ImVec2(x, y), radius,  clr.GetU32(), segments);
}

void D3DRenderer::DrawCircle(int x, int y, int radius,  Color clr, int segments)
{
	ImGuiRender._drawList->AddCircle(ImVec2(x, y), radius,  clr.GetU32());
}

void D3DRenderer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3,  Color clr, float thickne)
{
	ImGuiRender._drawList->AddTriangle(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3),  clr.GetU32(), thickne);
}

void D3DRenderer::DrawTriangleFilled(int x1, int y1, int x2, int y2, int x3, int y3,  Color clr)
{
	ImGuiRender._drawList->AddTriangleFilled(ImVec2(x1, y1), ImVec2(x2, y2), ImVec2(x3, y3),  clr.GetU32());
}


void D3DRenderer::DrawStrokeText(int x, int y, Color clr, Color black, const char* message)
{
	char output[1024] = {};
	va_list args;
	va_start(args, message);
	vsprintf_s(output, message, args);
	va_end(args);
	auto coord = ImVec2(x, y);
	auto size = ImGui::CalcTextSize(output);
	ImGuiRender._drawList->PushTextureID(cTools.Font1->ContainerAtlas->TexID);
	ImGui::PushFont(cTools.Font1);
	ImGuiRender._drawList->AddText(ImVec2(x, y - 1), black.GetU32(), output);
	ImGuiRender._drawList->AddText(ImVec2(x, y + 1), black.GetU32(), output);
	ImGuiRender._drawList->AddText(ImVec2(x - 1, y), black.GetU32(), output);
	ImGuiRender._drawList->AddText(ImVec2(x + 1, y), black.GetU32(), output);
	ImGuiRender._drawList->AddText(ImVec2(x, y), clr.GetU32(), output);
	ImGui::PopFont();
}


void D3DRenderer::DrawCornerBox(int x, int y, int w, int h, int borderPx, Color color)
{
	DrawFilledRect(x + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x + w - w / 3 + borderPx, y, w / 3, borderPx, color); //top 
	DrawFilledRect(x, y, borderPx, h / 3, color); //left 
	DrawFilledRect(x, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color); //left 
	DrawFilledRect(x + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w - w / 3 + borderPx, y + h + borderPx, w / 3, borderPx, color); //bottom 
	DrawFilledRect(x + w + borderPx, y, borderPx, h / 3, color);//right 
	DrawFilledRect(x + w + borderPx, y + h - h / 3 + borderPx * 2, borderPx, h / 3, color);//right 
}

static ImFont* GetDefaultFont()
{
	ImGuiContext& g = *GImGui;
	return g.IO.FontDefault ? g.IO.FontDefault : g.IO.Fonts->Fonts[0];
}

void DrawTextIm1(float x, float y, float* color, const char* Format, ...)
{
	char Buffer[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(Buffer, Format, va_alist);
	va_end(va_alist);
	ImGuiRender._drawList->PushTextureID(cTools.Font3->ContainerAtlas->TexID);
	ImGui::PushFont(cTools.Font3);
	ImGuiRender._drawList->AddText(ImVec2(x, y), ImGui::GetColorU32(ImVec4(color[0], color[1], color[2], color[3])), Buffer);
	ImGui::PopFont();
}

void DrawTextIm(float x, float y, float* color, float Alpha, const char* Format, ...)
{
	char output[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, Format);
	vsprintf_s(output, Format, va_alist);
	va_end(va_alist);

	ImGuiRender._drawList->PushTextureID(cTools.Font3->ContainerAtlas->TexID);
	ImGui::PushFont(cTools.Font3);
	float ShadowColorPlayer[4] = { 0.000f, 0.000f, 0.000f, 1.000 };
	ImGuiRender._drawList->AddText(ImVec2(x, y - 1), ImGui::GetColorU32(ImVec4(ShadowColorPlayer[0], ShadowColorPlayer[1], ShadowColorPlayer[2], Alpha)), output);
	ImGuiRender._drawList->AddText(ImVec2(x, y + 1), ImGui::GetColorU32(ImVec4(ShadowColorPlayer[0], ShadowColorPlayer[1], ShadowColorPlayer[2], Alpha)), output);
	ImGuiRender._drawList->AddText(ImVec2(x - 1, y), ImGui::GetColorU32(ImVec4(ShadowColorPlayer[0], ShadowColorPlayer[1], ShadowColorPlayer[2], Alpha)), output);
	ImGuiRender._drawList->AddText(ImVec2(x + 1, y), ImGui::GetColorU32(ImVec4(ShadowColorPlayer[0], ShadowColorPlayer[1], ShadowColorPlayer[2], Alpha)), output);
	ImGuiRender._drawList->AddText(ImVec2(x, y), ImGui::GetColorU32(ImVec4(color[0], color[1], color[2], Alpha)), output);
	ImGui::PopFont();
}


void D3DRenderer::TextEspF(int x, int y, D3DCOLOR dwColour, ID3DXFont* Font, const char* text)
{
	TextEsp(x, y - 1, Black, Font, text);
	TextEsp(x, y + 1, Black, Font, text);
	TextEsp(x - 1, y, Black, Font, text);
	TextEsp(x + 1, y, Black, Font, text);
	TextEsp(x, y, dwColour, Font, text);
}

void DrawLine(float x1, float y1, float x2, float y2, float* color, float a = 1.0f, float thickness = 1.0f)
{
	ImGuiRender._drawList->AddLine(ImVec2(x1, y1), ImVec2(x2, y2), ImGui::GetColorU32(ImVec4(color[0], color[1], color[2], a)), thickness);
}

void D3DRenderer::DrawBone(obj_Player* pPlayer, int Start, int End, Color Color)
{
	D3DXVECTOR3 vStart, vEnd;
	vStart = pEng.GetBoneOrigin(pPlayer, Start);
	vEnd = pEng.GetBoneOrigin(pPlayer, End);
	D3DXVECTOR3 vStartPos, vEndPos;
	if (pEng.ProjectToScreen(vStart, &vStartPos) && pEng.ProjectToScreen(vEnd, &vEndPos))
	{
		DrawLine(vStartPos.x, vStartPos.y, vEndPos.x, vEndPos.y, Color);
	}
}

void  D3DRenderer::DrawBoneFix(obj_Player* pPlayer, int Start, int End, Color Color)
{
	D3DXVECTOR3 vStart, vEnd;
	vStart = pEng.GetBoneOrigin(pPlayer, Start);
	vEnd = pEng.GetBoneOrigin(pPlayer, End);
	D3DXVECTOR3 vStartPos, vEndPos;
	if (pEng.ProjectToScreen(vStart, &vStartPos) && pEng.ProjectToScreen(vEnd + D3DXVECTOR3(0,0.0001, 0), &vEndPos))
	{
		DrawLine(vStartPos.x, vStartPos.y, vEndPos.x, vEndPos.y, Color);
	}
}

void D3DRenderer::Line(float X, float Y, float X2, float Y2, DWORD Color)
{
	D3DTLVERTEX Vertex[2] = {
		{ (float)X , (float)Y, 0.0f, 1.0f, Color },
	{ (float)X2 , (float)Y2 , 1.0f, 1.0f, Color },
	};

	const DWORD FVFTL = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	IDirect3DBaseTexture9* pTexture = NULL;

	DWORD dwLighting = 0, dwZEnable = 0, dwZFunc = 0, dwFVF = 0, dwColorOp = 0, dwColorArg = 0;

	pDevice->GetTexture(0, &pTexture);
	pDevice->GetRenderState(D3DRS_LIGHTING, &dwLighting);
	pDevice->GetRenderState(D3DRS_ZENABLE, &dwZEnable);
	pDevice->GetRenderState(D3DRS_ZFUNC, &dwZFunc);
	pDevice->GetFVF(&dwFVF);
	pDevice->GetTextureStageState(0, D3DTSS_COLOROP, &dwColorOp);
	pDevice->GetTextureStageState(0, D3DTSS_COLORARG1, &dwColorArg);

	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetFVF(FVFTL);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, &Vertex, sizeof(D3DTLVERTEX));

	pDevice->SetTexture(0, pTexture);
	pDevice->SetRenderState(D3DRS_LIGHTING, dwLighting);
	pDevice->SetRenderState(D3DRS_ZENABLE, dwZEnable);
	pDevice->SetRenderState(D3DRS_ZFUNC, dwZFunc);
	pDevice->SetFVF(dwFVF);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, dwColorOp);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, dwColorArg);
}