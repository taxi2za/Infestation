#include "Headers.h"
Features func;
MenuImGui pMenu;
ImGuiRendering ImGuiRender;
bool bShowMenu = true;
bool			PressedKeys[256];

extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT, WPARAM, LPARAM);

void __stdcall ImGuiRendering::CreateObjects(IDirect3DDevice9* pDevice)
{
	if (pMenu.GameWindow)
		ImGui_ImplDX9_CreateDeviceObjects();
	_drawList = new ImDrawList();
}

void __stdcall ImGuiRendering::InvalidateObjects()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	if (_drawList)
		delete _drawList;
	_drawList = nullptr;
}
static const ImWchar ranges[] =
{
	0x0020, 0x00FF, // Basic Latin + Latin Supplement
	0x0100, 0x024F, // Latin Extended-A + Latin Extended-B
	0x0E00, 0x0E7F, // Thai 
	0, // 0 should be always the last one
};

void __stdcall ImGuiRendering::SetupPresent(IDirect3DDevice9* device)
{
	ImGui_ImplDX9_Init(pMenu.GameWindow, device);
	cTools.Font1 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedBase85TTF(_compressed_data_base85, 13.0f);
	cTools.Font2 = ImGui::GetIO().Fonts->AddFontFromMemoryCompressedTTF(MyFonts_compressed_data, MyFonts_compressed_size, 14.0f, NULL, ImGui::GetIO().Fonts->GetGlyphRangesThai());
	cTools.Font3 = ImGui::GetIO().Fonts->AddFontDefault();
	
	ImGuiRender.CreateObjects(device);
	pMenu.RenderInit = true;
}

void __stdcall ImGuiRendering::EndPresent(IDirect3DDevice9* device)
{
	ImGui::Render();
	device->SetRenderState(D3DRS_COLORWRITEENABLE, dwOld_D3DRS_COLORWRITEENABLE);
}

void __stdcall ImGuiRendering::PreRender(IDirect3DDevice9* device)
{
	device->GetRenderState(D3DRS_COLORWRITEENABLE, &dwOld_D3DRS_COLORWRITEENABLE);
	device->SetRenderState(D3DRS_COLORWRITEENABLE, 0xffffffff);
	ImGui_ImplDX9_NewFrame();
	_drawData.Valid = false;
	_drawList->Clear();
	_drawList->PushClipRectFullScreen();
}
void ImGui_ImplDX9_RenderDrawLists(ImDrawData* draw_data);

void __stdcall ImGuiRendering::PostRender(IDirect3DDevice9* device)
{
	if (!_drawList->VtxBuffer.empty()) {
		_drawData.Valid = true;
		_drawData.CmdLists = &_drawList;
		_drawData.CmdListsCount = 1;
		_drawData.TotalVtxCount = _drawList->VtxBuffer.Size;
		_drawData.TotalIdxCount = _drawList->IdxBuffer.Size;
	}

	ImGui_ImplDX9_RenderDrawLists(&_drawData);
}
LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static bool PressedButtons = false;

	if (!PressedButtons && GetAsyncKeyState(VK_DELETE))
	{
		PressedButtons = true;
	}
	else if (PressedButtons && !GetAsyncKeyState(VK_DELETE))
	{
		PressedButtons = false;

		bShowMenu = !bShowMenu;
	}

	if (!PressedButtons && GetAsyncKeyState(VK_F1))
	{
		PressedButtons = true;
	}
	else if (PressedButtons && !GetAsyncKeyState(VK_F1))
	{
		PressedButtons = false;
		bShowMenu = !bShowMenu;
	}

	if (bShowMenu && ImGui_ImplDX9_WndProcHandler(hWnd, msg, wParam, lParam))
		return true;

	return CallWindowProcA(pMenu.oldWindowProc, hWnd, msg, wParam, lParam);
}

void MenuImGui::DrawRectRainbow(int x, int y, int width, int height, float flSpeed, float& flRainbow)
{
	ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

	Color colColor(0, 0, 0, 255);

	flRainbow += flSpeed;
	if (flRainbow > 1.f) flRainbow = 0.f;

	for (int i = 0; i < width; i++)
	{
		float hue = (1.f / (float)width) * i;
		hue -= flRainbow;
		if (hue < 0.f) hue += 1.f;

		Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
		windowDrawList->AddRectFilled(ImVec2(x + i, y), ImVec2(width, height), colRainbow.GetU32());
	}
}


std::array<const char*, 124> keyNames = {
{
	"-",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"-",
	"Backspace",
	"Tab",
	"-",
	"-",
	"Clear",
	"Enter",
	"-",
	"-",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"Escape",
	"-",
	"-",
	"-",
	"-",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"-",
	"-",
	"-",
	"Print",
	"Insert",
	"Delete",
	"-",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"-",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"-",
	"-",
	"-",
	"-",
	"-",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"-",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12"
 }
};

void MenuImGui::teams()
{
	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(15, 15);
	style.WindowRounding = 5.0f;
	style.FramePadding = ImVec2(5, 5);
	style.FrameRounding = 4.0f;
	style.ItemSpacing = ImVec2(12, 8);
	style.ItemInnerSpacing = ImVec2(8, 6);
	style.IndentSpacing = 25.0f;
	style.ScrollbarSize = 15.0f;
	style.ScrollbarRounding = 9.0f;
	style.GrabMinSize = 5.0f;
	style.GrabRounding = 3.0f;

	style.Colors[ImGuiCol_Text] = ImVec4(0.80f, 0.80f, 0.83f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.80f, 0.80f, 0.83f, 0.88f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.92f, 0.91f, 0.88f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.00f, 0.98f, 0.95f, 0.75f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.07f, 0.07f, 0.09f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.19f, 0.18f, 0.21f, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.80f, 0.80f, 0.83f, 0.31f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.10f, 0.09f, 0.12f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.24f, 0.23f, 0.29f, 1.00f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.56f, 0.56f, 0.58f, 1.00f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.06f, 0.05f, 0.07f, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.40f, 0.39f, 0.38f, 0.16f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.40f, 0.39f, 0.38f, 0.39f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.40f, 0.39f, 0.38f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.40f, 0.39f, 0.38f, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.25f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.25f, 1.00f, 0.00f, 0.43f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(1.00f, 0.98f, 0.95f, 0.73f);
}

bool ImGui::ShowStyleSelector(const char* label)
{
	static int style_idx = 3;
	if (ImGui::Combo(label, &style_idx, u8"Dark\0Classic\0Light\0Mcz\0เก่า\0"))
	{
		switch (style_idx)
		{
		case 0: ImGui::StyleColorsDark(); break;
		case 1: ImGui::StyleColorsClassic(); break;
		case 2: ImGui::StyleColorsLight(); break;
		case 3: ImGui::mcz(); break;
		case 4: pMenu.teams(); break;
		}
		return true;
	}
	return false;
}
void newmenu();
void oldMenu();
bool ShowStyleMenu(const char* label)
{
	static int style_idx = 0;
	if (ImGui::Combo(label, &style_idx, u8"เก่า\0ใหม่\0"))
	{
	
		if (style_idx == 0) oldMenu();
		if (style_idx == 1) newmenu();
	}
}

void ImGui::ShowStyleEditor(ImGuiStyle* ref)
{
	// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
	ImGuiStyle& style = ImGui::GetStyle();
	static ImGuiStyle ref_saved_style;

	// Default to using internal storage as reference
	static bool init = true;
	if (init && ref == NULL)
		ref_saved_style = style;
	init = false;
	if (ref == NULL)
		ref = &ref_saved_style;

	if (ImGui::ShowStyleSelector("Colors##Selector"))
		ref_saved_style = style;
}

void MenuStyleEditor(ImGuiStyle* ref)
{
	// You can pass in a reference ImGuiStyle structure to compare to, revert to and save to (else it compares to an internally stored reference)
	ImGuiStyle& style = ImGui::GetStyle();
	static ImGuiStyle ref_saved_style;

	// Default to using internal storage as reference
	static bool init = true;
	if (init && ref == NULL)
		ref_saved_style = style;
	init = false;
	if (ref == NULL)
		ref = &ref_saved_style;

	if (ShowStyleMenu("Menu##Selector"))
		ref_saved_style = style;
}

static int style_idx = 1;
void SetupMainMenuBar()
{

	if (ImGui::BeginMainMenuBar())
	{
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(8 * 2.0f, 4 * 2.0f));

		//std::string font_path; ImFontConfig config;

		static float flRainbow;
		float flSpeed = 0.0003f;


		int curWidth = 1;

		ImVec2 curPos = ImGui::GetCursorPos();
		ImVec2 curWindowPos = ImGui::GetWindowPos();
		curPos.x += curWindowPos.x;
		curPos.y += curWindowPos.y;

		int y = pGameRend->BackBufferWidth;
		int size = pGameRend->BackBufferHeight;

		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Close"))
			{
				exit(0);
			}
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Colors"))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			for (int i = 0; i < ImGuiCol_COUNT; i++)
			{
				const char* name = ImGui::GetStyleColorName((ImGuiCol)i);
				ImGui::ColorEdit3(name, (float*)& ImGui::GetStyleColorVec4((ImGuiCol)i));
			}
			ImGui::PopStyleVar();
			ImGui::EndMenu();
		}


		if (ImGui::BeginMenu("SET Theme"))
		{
			ImGui::ShowStyleEditor();
			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("SET MENU"))
		{
			
			if (ImGui::Combo("",&style_idx, u8"เก่า\0ใหม่\0"))
			{
			}
			ImGui::EndMenu();
		}
		


		ImGui::Text("Average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::PopStyleVar();
		ImGui::EndMainMenuBar();
	}
}
void RenderPlayer()
{
	//ImGui::Text(u8"การมองเห็น"); ImGui::NextColumn();
	//ImGui::PushItemWidth(300);
	ImGui::Columns(2, nullptr, true);
	{
		ImGui::Text(u8"ผู้เล่น"); ImGui::NextColumn(); ImGui::Text(u8"ล็อคเป้า"); ImGui::NextColumn();

		ImGui::Checkbox((u8"เปิด มองผู้เล่น"), &func.ESP);
		ImGui::Checkbox((u8"แสดง โครงกระดุก"), &func.SkeletonPlayer);
		ImGui::Checkbox(u8"แสดง ชื่อ", &func.NamePlayer);
		ImGui::Checkbox(u8"แสดง อาวุธ", &func.WeaponPlayer);
		ImGui::Checkbox(u8"แสดง ยศ", &func.RankPlayer);
		ImGui::Checkbox((u8"แสดง เลือด"), &func.HealthPlayer);
		ImGui::Checkbox((u8"แสดง ระยะ"), &func.DistancePlayer);
		ImGui::Checkbox((u8"แสดง ทิศทางการมอง"), &func.direction);
		//ImGui::Checkbox((u8"ระยะการมองเห็น"), &func.DistancePlayer1);
		ImGui::PushItemWidth(200);
		ImGui::SliderInt(u8"ระยะการมองเห็น", &func.DistancePlayer1, 0, 1000);
	}

	ImGui::NextColumn();
	{
		ImGui::Checkbox(u8"เปิดล็อคเป้า", &func.Aimbot);
		ImGui::Checkbox((u8"ยิงตรง & ลดแรงดีด"), &func.NoRecoil);
		ImGui::Combo((u8"ล็อค Key Key##1"), &func.Aimkey, keyNames.data(), keyNames.size());
		ImGui::SliderFloat(u8"ขอบเขตการล็อค", &func.AimFov, 0, 1000);
		ImGui::SliderFloat(u8"ความเร็วการล็อค", &func.AimSpeed, 3, 100);

	}
}


void RenderItem()
{
	ImGui::Text(u8"มองสิ่งของ"); ImGui::NextColumn();
	ImGui::Checkbox((u8"เปิด มองสิ่งของ"), &func.ESPItem);
	//ImGui::Columns(5, nullptr, true);
	{
		//ImGui::Checkbox(u8"Enable ESP##Item", &func.ESPItem);
		ImGui::Checkbox((u8"แสดง ชื่อ##Item"), &func.ESPNameItem);
		ImGui::Checkbox((u8"แสดง กรอบ##Item"), &func.ESPBoxItem);
		ImGui::SliderInt((u8"ระยะ ##2"), &func.DistanceItem, 0, 1000);
		ImGui::BeginChild((("Filter")), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 5));
		{
			ImGui::Selectable((u8" ปืน"), &func.WeaponI);
			ImGui::Selectable((u8" กระเป๋า"), &func.GearI);
			ImGui::Selectable((u8" กระสุน"), &func.AttachmentI);
			ImGui::Selectable((u8" อาวุธประชิด"), &func.MeleeI);
			ImGui::Selectable((u8" ยา"), &func.ConsumableI);
			ImGui::Selectable((u8" อาหาร"), &func.FoodI);
			ImGui::Selectable((u8" สไน"), &func.SniperI);
		} ImGui::EndChild();

		ImGui::ColorEdit4((u8"สี ปืน"), func.itemzcolorWeapon);
		ImGui::ColorEdit4((u8"สี กระเป๋า"), func.itemzcolorGear);
		ImGui::ColorEdit4((u8"สี กระสุน"), func.itemzcolorAttachment);
		ImGui::ColorEdit4((u8"สี อาวุธประชิด"), func.itemzcolorMelee);
		ImGui::ColorEdit4((u8"สี ยา"), func.itemzcolorConsumable);
		ImGui::ColorEdit4((u8"สี อาหาร"), func.itemzcolorFood);
		ImGui::ColorEdit4((u8"สี สไน"), func.itemzcolorSniper);
	}
}


void RenderMISC()
{
	ImGui::Columns(2, nullptr, true);
	{
		//ImGui::Text(u8"ผู้เล่น"); ImGui::NextColumn(); ImGui::Text(u8"ล็อคเป้า"); ImGui::NextColumn();

		ImGui::Checkbox((u8"เดินทะลุ 'V'"), &func.NoCilp);
		ImGui::PushItemWidth(150);
		ImGui::SliderFloat((u8"ความเร็วเดินทะลุ ##1"), &func.Test, 0, 10);
		ImGui::Checkbox((u8"กระโดดสูง"), &func.Superjump);
		ImGui::PushItemWidth(150);
		ImGui::SliderFloat((u8"ความสูง ##1"), &func.Test1, 0, 10);
		ImGui::Checkbox((u8"ดึงเน็ต"), &func.GhostMode);
		ImGui::Combo((u8"ดึงเน็ต Key##1"), &func.keyGhost, keyNames.data(), keyNames.size());
		//ImGui::ListBox(u8"ดึงเน็ต Key##1", &func.keyGhost, keyNames.data(), keyNames.size());

		ImGui::Checkbox((u8"ยิงตรง & ลดแรงดีด"), &func.NoRecoil);
		ImGui::Checkbox((u8"FakeHero"), &func.FakeHero);
		ImGui::Checkbox((u8"DebugPlayer"), &func.DebugPlayer);

		ImGui::Checkbox((u8"ลบหญ้า"), &func.NoGrass);
		ImGui::SliderInt(u8"ระยะของหญ้า", &func.Grass, 0, 1000);
	//	ImGui::SliderInt(u8"asd", &func.asd, 0, 1000);
	}
	ImGui::NextColumn();
	{
		ImGui::Checkbox((u8"เก็บของไว"), &func.NoGrass);
		ImGui::Checkbox((u8"ดิสไว 'F8'"), &func.Disconnect);
	}
}


void newmenu()
{
	if (bShowMenu)
	{
		static bool firstTime = true;

		if (firstTime == true) // so when the menu initializes, the window size will be same as tab index 0, set this to same value as index 0.
		{
			ImGui::SetWindowSize(ImVec2(526.0f, 470.0f));

			firstTime = false;
		}

		if (ImGui::Begin("MakeCheatZ"), &bShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | NULL)
		{
			static int page = 0;
			const char* tabs[] = {
				u8"ผู้เล่น",
				u8"ไอเทม",
				u8"ฟังชัน"
				//"Ragebot"
			};

			for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
			{

				//ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(54, 54, 54, 255);

				if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
					page = i;

				//ImGui::GetStyle().Colors[ImGuiCol_Button] = ImColor(54, 54, 54, 255);

				if (i < IM_ARRAYSIZE(tabs) - 1)
					ImGui::SameLine();
			}

			ImGui::Separator();



			switch (page)
			{
			case 0:
				RenderPlayer();
				break;
			case 1:
				RenderItem();
				break;
			case 2:
				RenderMISC();
				break;

			}
			ImGui::End();
		}
	}
}

void oldMenu()
{
	ImGui::SetNextWindowSize(ImVec2(505, 400), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("MakeCheatZ", &bShowMenu, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | NULL))
	{

		if (ImGui::CollapsingHeader(u8"มองผู้เล่น"))
		{
			ImGui::Checkbox(u8"เปิดมองผู้เล่น ##Player", &func.ESP);
			ImGui::Checkbox((u8"แสดง โครงกระดุก"), &func.SkeletonPlayer);
			ImGui::Checkbox(u8"แสดง ชื่อ", &func.NamePlayer);
			ImGui::Checkbox(u8"แสดง ยศ", &func.RankPlayer);
			ImGui::Checkbox((u8"แสดง เลือด"), &func.HealthPlayer);
			ImGui::Checkbox((u8"แสดง ระยะ"), &func.DistancePlayer);
			ImGui::Checkbox((u8"แสดง ทิศทางการมอง"), &func.direction);
			ImGui::Checkbox((u8"เดินทะลุ 'V' "), &func.NoCilp);
			ImGui::Checkbox((u8"กระโดดสูง"), &func.Superjump);
			ImGui::Checkbox((u8"ดึงเน็ต 'G'"), &func.GhostMode);
			ImGui::Combo((u8"ดึงเน็ต Key##1"), &func.keyGhost, keyNames.data(), keyNames.size());

			ImGui::SliderInt((u8"ระยะ ##1"), &func.DistancePlayer1, 0, 1000);
			ImGui::SliderFloat((u8"ความเร็วเดินทะลุ ##1"), &func.Test, 0, 10);
			ImGui::SliderFloat((u8"ความสูง ##1"), &func.Test1, 0, 10);
		}
		if (ImGui::CollapsingHeader(u8"มองไอเท็ม"))
		{
			ImGui::Checkbox((u8"เปิดมองไอเท็ม##Item"), &func.ESPItem);
			ImGui::Checkbox((u8"แสดง ชื่อ##Item"), &func.ESPNameItem);
			ImGui::Checkbox((u8"แสดง กรอบ##Item"), &func.ESPBoxItem);
			ImGui::SliderInt((u8"ระยะ ##2"), &func.DistanceItem, 0, 1000);
			ImGui::BeginChild((("Filter")), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 5));
			{
				ImGui::Selectable((u8" ปืน"), &func.WeaponI);
				ImGui::Selectable((u8" กระเป๋า"), &func.GearI);
				ImGui::Selectable((u8" กระสุน"), &func.AttachmentI);
				ImGui::Selectable((u8" อาวุธประชิด"), &func.MeleeI);
				ImGui::Selectable((u8" ยา"), &func.ConsumableI);
				ImGui::Selectable((u8" อาหาร"), &func.FoodI);
				ImGui::Selectable((u8" สไน"), &func.SniperI);
			} ImGui::EndChild();

			ImGui::ColorEdit4((u8"สี ปืน"), func.itemzcolorWeapon);
			ImGui::ColorEdit4((u8"สี กระเป๋า"), func.itemzcolorGear);
			ImGui::ColorEdit4((u8"สี กระสุน"), func.itemzcolorAttachment);
			ImGui::ColorEdit4((u8"สี อาวุธประชิด"), func.itemzcolorMelee);
			ImGui::ColorEdit4((u8"สี ยา"), func.itemzcolorConsumable);
			ImGui::ColorEdit4((u8"สี อาหาร"), func.itemzcolorFood);
			ImGui::ColorEdit4((u8"สี สไน"), func.itemzcolorSniper);
		}
		if (ImGui::CollapsingHeader(u8"ล็อคเป้า"))
		{
			ImGui::Checkbox(u8"เปิดล็อคเป้า", &func.Aimbot);
			ImGui::Combo((u8"ล็อค Key Key##1"), &func.Aimkey, keyNames.data(), keyNames.size());
			ImGui::SliderFloat(u8"ขอบเขตการล็อค", &func.AimFov, 0, 1000);
			ImGui::SliderFloat(u8"ความเร็วการล็อค", &func.AimSpeed, 3, 100);
			ImGui::Checkbox((u8"ยิงตรง & ลดแรงดีด"), &func.NoRecoil);
		}

		ImGui::End();
	}
}
void MenuImGui::MenuRender()
{
	//SetupMainMenuBar();


	if (bShowMenu)
	{
		ImGuiRender._drawList->PushTextureID(cTools.Font2);
		ImGui::PushFont(cTools.Font2);

		SetupMainMenuBar();
		if (style_idx == 0)
		{
			oldMenu();
		}
		if (style_idx == 1)
		{
			newmenu();
		}
		ImGui::PopFont();
	}

}