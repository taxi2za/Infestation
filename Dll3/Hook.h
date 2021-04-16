#define NO_SCAN			0
#define MEMORY_SCAN		1
#define MODULE_SCAN		2
#define DETOUR_ADD		0
#define DETOUR_REMOVE	1



#define GET_ORIGIN(VecOut,pMatrix) {VecOut.x = pMatrix._41;VecOut.y = pMatrix._42;VecOut.z = pMatrix._43;};
#define GET_X(VecOut,pMatrix) {D3DXVec3Normalize(&VecOut,&D3DXVECTOR3(pMatrix._11,pMatrix._12,pMatrix._13));};
#define GET_Y(VecOut,pMatrix) {D3DXVec3Normalize(&VecOut,&D3DXVECTOR3(pMatrix._21,pMatrix._22,pMatrix._23));};
#define GET_Z(VecOut,pMatrix) {D3DXVec3Normalize(&VecOut,&D3DXVECTOR3(pMatrix._31,pMatrix._32,pMatrix._33));};

#define DotProduct(x,y)			((x)[0]*(y)[0]+(x)[1]*(y)[1]+(x)[2]*(y)[2])
#define VectorSubtract(a,b,c)	((c)[0]=(a)[0]-(b)[0],(c)[1]=(a)[1]-(b)[1],(c)[2]=(a)[2]-(b)[2])
#define VectorAdd(a,b,c)		((c)[0]=(a)[0]+(b)[0],(c)[1]=(a)[1]+(b)[1],(c)[2]=(a)[2]+(b)[2])
#define VectorCopy(a,b)			((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2])
#define VectorCopy4(a,b)		((b)[0]=(a)[0],(b)[1]=(a)[1],(b)[2]=(a)[2],(b)[3]=(a)[3])
#define	VectorScale(v, s, o)	((o)[0]=(v)[0]*(s),(o)[1]=(v)[1]*(s),(o)[2]=(v)[2]*(s))
#define	VectorMA(v, s, b, o)	((o)[0]=(v)[0]+(b)[0]*(s),(o)[1]=(v)[1]+(b)[1]*(s),(o)[2]=(v)[2]+(b)[2]*(s))
#define VectorCmp(a,b)			(((a)[0]==(b)[0])&&((a)[1]==(b)[1])&&((a)[2]==(b)[2]))

#define ROTY 0
#define ROTX 1
#define ROTZ 2

#include "Md5.h"

static bool bWasOpen = false;
static bool bDoOnce = false;
bool quit = false;
bool hooked = false;
IDirect3DSurface9* pCleanFrame = NULL;
IDirect3DSurface9* pBackBuffer = NULL;

typedef HRESULT(__stdcall* tGetRenderTargetData)(LPDIRECT3DDEVICE9 pDevice, IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface);
tGetRenderTargetData oGetRenderTargetData;

typedef BaseItemConfig* (__stdcall* tWeaponArmory__getConfig)(DWORD itemID);
tWeaponArmory__getConfig WeaponArmory__getConfig = (tWeaponArmory__getConfig)NULL;


DWORD VTableHook(DWORD vtable, DWORD index, DWORD hook, DWORD org = NULL)
{
	DWORD addr = vtable + index * 4;
	DWORD tmp, prot;

	if (VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &prot))
	{
		tmp = *(DWORD*)addr;
		*(DWORD*)addr = hook;

		VirtualProtect((void*)addr, 4, prot, NULL);

		return (org == NULL ? tmp : org);
	}

	return 0;
}
HRESULT __stdcall hGetRenderTargetData(LPDIRECT3DDEVICE9 pDevice, IDirect3DSurface9* pRenderTarget, IDirect3DSurface9* pDestSurface)
{
	if (pCleanFrame == NULL || pBackBuffer == NULL)
	{
		return D3D_OK;
	}
	else if (pRenderTarget == pBackBuffer)
	{
		D3DXLoadSurfaceFromSurface(pDestSurface, NULL, NULL, pCleanFrame, NULL, NULL, D3DX_FILTER_NONE, 0);
		D3DXLoadSurfaceFromSurface(pRenderTarget, NULL, NULL, pCleanFrame, NULL, NULL, D3DX_FILTER_NONE, 0);
		return D3D_OK;
	}
	return oGetRenderTargetData(pDevice, pRenderTarget, pDestSurface);
}


/*typedef HRESULT(WINAPI* oPresent) (LPDIRECT3DDEVICE9 pDevice, CONST RECT *pSourceRect, CONST RECT *pDestRect, HWND hDestWindowOverride, CONST RGNDATA *pDirtyRegion);
oPresent pPresent;*/


static int	     _TimerInited = 0;
static double	     _fTicksPerSec;
static LARGE_INTEGER _llTimerStart;

float r3dGetTimeMyHack()
{
	if (!_TimerInited)
	{
		_TimerInited = 1;

		// Use QueryPerformanceFrequency() to get frequency of timer.  
		LARGE_INTEGER qwTicksPerSec;
		QueryPerformanceFrequency(&qwTicksPerSec);
		_fTicksPerSec = (double)qwTicksPerSec.QuadPart;
		QueryPerformanceCounter(&_llTimerStart);
	}

	LARGE_INTEGER qwTime;
	QueryPerformanceCounter(&qwTime);

	return float((double)(qwTime.QuadPart - _llTimerStart.QuadPart) / _fTicksPerSec);
}


DWORD MakeJMP(BYTE* pAddress, DWORD dwJumpTo, DWORD dwLen);


typedef float(__fastcall* tFunc)(void);
tFunc GetTime = (tFunc)(0x745290);

bool STOP11;

typedef HRESULT(__stdcall* tEndScene)(LPDIRECT3DDEVICE9 pDevice);
tEndScene oEndScene;

float ShowSave;
bool hue = true;


BOOL WriteAsm(DWORD pxAdress, const void* cpvPatch, DWORD dwSize);

obj_Player* ClientGameLogic::GetLocalPlayer()
{
	if (VALID(pGame))
	{
		int localIndex = pGame->GetLocalIndex();

		obj_Player* localPlayer = pGame->GetPlayer((_DWORD*)pGame, localIndex);

		if (VALID(localPlayer))
		{
			return localPlayer;
		}
		else return 0;
	}

	return NULL;
}
CPlayer* ClientGameLogic::GetLocalCPlayer()
{
	if (VALID(pGame))
	{
		int localIndex = pGame->GetLocalIndex();

		CPlayer* localPlayer = (CPlayer*)pGame->GetPlayer((_DWORD*)pGame, localIndex);

		if (VALID(localPlayer))
		{
			return localPlayer;
		}
		else return 0;
	}

	return NULL;
}



DWORD Recoil, NewRecoil;
__declspec(naked) void WINAPI NoRecoil()
{
	__asm
	{
		//movss[esp + 28], xmm0
		mov[esp + 0x3C], 0
		//nop
		jmp[NewRecoil]
	}
}

DWORD GetConfigWeapon_()
{
	DWORD GetConfigWeapon = NULL;
	while (GetConfigWeapon == NULL)
	{
		GetConfigWeapon = cTools.FindPatternIDA(cTools.hGameBase, "8B 0D ? ? ? ? E8 ? ? ? ? 8B F8") + 0x2;
	}

	while (GetConfigWeapon == NULL)
		return 0;

	return GetConfigWeapon;
}

bool test = true;
void SetNoRecoil()
{
	//F3 0F 11 44 24 ? E8 ? ? ? ? D8 4C 24 28 8B 4F 2C
	//F3 0F 11 44 24 ? E8 ? ? ? ? D8 4C 24 30 8B 4F 2C 
	//F3 0F 11 44 24 ? E8 ? ? ? ? D8 4C 24 38 //new
	if (test)
	{
		Recoil = cTools.FindPatternIDA(cTools.hGameBase, "F3 0F 11 44 24 ? E8 ? ? ? ? D8 4C 24 38");
		NewRecoil = Recoil + 6;
		test = false;
	}

	if (func.NoRecoil)
	{
		MakeJMP((BYTE*)Recoil, (DWORD)NoRecoil, 6);
	}
	else

	{
		WriteAsm(Recoil, "\xF3\x0F\x11\x44\x24\x38", 6);
	}
}

CPhysicsWorld* pPhysicsWorld = CPhysicsWorld::Singleton();
HRESULT __stdcall hEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (!pMenu.RenderInit)
		ImGuiRender.SetupPresent(pDevice);

	if (!bDoOnce)
	{
		D3DXCreateFont(pDevice, 16, 0, 400, 1, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial", &pDXRend.Font);
		D3DXCreateFont(pDevice, 12, 0, 400, 1, FALSE, DEFAULT_CHARSET, OUT_TT_ONLY_PRECIS, ANTIALIASED_QUALITY, FIXED_PITCH | FF_DECORATIVE, "Verdana", &pDXRend.objFont);
		D3DXCreateFont(pDevice, 13, 0, FW_THIN, 1, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DT_CENTER, "Tahoma", &pDXRend.pESP);
		D3DXCreateSprite(pDevice, &pDXRend.Sprite);
		D3DXCreateSprite(pDevice, &pDXRend.objSprite);
		D3DXCreateLine(pDevice, &pDXRend.pLine);
		pDevice->GetViewport(&pDXRend.Viewport);
		ScreenCenterX = pDXRend.Viewport.Width / 2;
		ScreenCenterY = pDXRend.Viewport.Height / 2;
		LPDIRECT3DSURFACE9 renderTarget = NULL;
		D3DSURFACE_DESC desc;
		pDevice->GetRenderTarget(0, &renderTarget);
		renderTarget->GetDesc(&desc);
		renderTarget->Release();
		//pMenu.teams();
		ImGui::mcz();

		bDoOnce = true;
	}
	cTools.r3dGetTime = GetTime();
	char txt[220];

	

	pEsp.MatrixToScreen();
	pLocalPlayer = pGame->GetLocalPlayer();

	static DWORD renderState = 0;
	pDevice->GetRenderState(D3DRS_ZFUNC, &renderState);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);


	ImGuiRender.PreRender(pDevice);
	if (pGame->GetLocalPlayer()) {/* RenderPlayers_test();*/pEsp.RenderPlayers(); }

	//RenderPlayers_test();
	ImGuiRender.PostRender(pDevice);
	pMenu.MenuRender();
	ImGuiRender.EndPresent(pDevice);


	//131AA88
	//	DWORD Warz = *(DWORD*)((DWORD)GetModuleHandle(NULL) + 0xBF3A9C);
	//DWORD r_grass_zoom_coef = *(DWORD*)((DWORD)GetModuleHandle(NULL) + (0x171AA88 - 0x400000));
	DWORD r_grass_view_dist = *(DWORD*)((DWORD)GetModuleHandle(NULL) + (0x171AA80 - 0x400000));
	//DWORD g_enable_zombie_sprint = *(DWORD*)((DWORD)GetModuleHandle(NULL) + (0x171AEAC - 0x400000));

	//sprintf(txt, "LocalPlayer 0x%x\nr_grass_view_dist 0x%x", pGame->GetLocalPlayer(), r_grass_view_dist);
	//pDXRend.TextEspF(60, 60, White, pDXRend.Font, txt);

	if (pGame->GetLocalPlayer())
	{

		//CPhysicsWorld* pPhysicsWorld = CPhysicsWorld::Singleton();
		//sprintf(txt, "LocalPlayer 0x%x\n", pGame->GetLocalPlayer());
		//pDXRend.TextEspF(60, 60, White, pDXRend.Font, txt);

		if (pGame->GetLocalPlayer())
		{
			if (pGame->GetLocalPlayer()->m_AuraType() == 4)
			{
				sprintf(txt, "LocalProtected: %.f", pGame->GetLocalPlayer()->m_SpawnProtectedUntil() - cTools.r3dGetTime);
				pDXRend.TextEspF(60, 240, White, pDXRend.Font, txt);
			}
		}

		if (func.DebugPlayer)
		{
			sprintf(txt, "HeroId %d\nBackpackID %d\nXP %d\nSpendXP %d\nKilledZombies %d\nKilledSurvivors %d\nKilledBandits %d\nDeaths %d\nShotsFired %d\nShotsHits %d\nShotsHeadshots %d",
				pGame->GetLocalCPlayer()->HeroId,
				pGame->GetLocalCPlayer()->BackpackID,
				pGame->GetLocalCPlayer()->XP,
				pGame->GetLocalCPlayer()->SpendXP,
				pGame->GetLocalCPlayer()->KilledZombies,
				pGame->GetLocalCPlayer()->KilledSurvivors,
				pGame->GetLocalCPlayer()->KilledBandits,
				pGame->GetLocalCPlayer()->Deaths,
				pGame->GetLocalCPlayer()->ShotsFired,
				pGame->GetLocalCPlayer()->ShotsHits,
				pGame->GetLocalCPlayer()->ShotsHeadshots);

			pDXRend.TextEspF(60, 75, White, pDXRend.Font, txt);
		}

		if (func.FakeHero)
		{
			pGame->GetLocalCPlayer()->HeroId = 20183;
		    //pGame->GetLocalCPlayer()->GameFlags = 0;
			//*(float*)((DWORD)pGame->GetLocalCPlayer() + 0x33d4) = 20;
			//*(float*)((DWORD)pGame->GetLocalCPlayer() + 0x33d8) = 20;

		}

		if (func.NoGrass)
		{
			*(float*)((DWORD)r_grass_view_dist + 0x188) = func.Grass;
		}

		if (func.Disconnect)
		{
			if (GetAsyncKeyState(VK_F8))
			{
				*(bool*)((DWORD)pGame + 0xD0934) = 0; //E8 ? ? ? ? E8 ? ? ? ? BF ? ? ? ?
			}
		}

		if (func.InstantPickup)
		{
			*(float*)((DWORD)pGame->GetLocalCPlayer() + 0x2F50) = 1.2f;
		}

	}
	
	if (func.GhostMode)
	{
		if (STOP)
		{
			sprintf(txt, " Ghost NO  && Internet Disconnect   [%d]", STOP);
			pDXRend.TextEspF(60, 120, White, pDXRend.Font, txt);
		}
		else
		{
			sprintf(txt, " Ghost OFF && Internet Connect   [%d] Lag [%d]", STOP);
			pDXRend.TextEspF(60, 120, White, pDXRend.Font, txt);
		}
		Ghost();
	}

	if (pGame->GetLocalPlayer())
	{
		if (pGame->GetLocalPlayer()->PhysicsObject())
		{
			if (func.NoCilp)
			{
				float fixNewYaw = (pGame->GetLocalPlayer()->GetRotationVector().x) - ((pGame->GetLocalPlayer()->GetRotationVector().x * 2));
				float Yaw = D3DXToRadian(fixNewYaw);
				if (GetAsyncKeyState('V') & 0x8000)
				{
					pGame->GetLocalPlayer()->PhysicsObject()->SetPosition(D3DXVECTOR3(pGame->GetLocalPlayer()->m_Position.x -= (float)(0.005 * func.Test) * sin(Yaw), pGame->GetLocalPlayer()->m_Position.y, pGame->GetLocalPlayer()->m_Position.z += (float)(0.005 * func.Test) * cos(Yaw)));
				}
			}
			if (func.Superjump)
			{
				if (GetAsyncKeyState(VK_SPACE))
				{
					pGame->GetLocalPlayer()->PhysicsObject()->SetPosition(D3DXVECTOR3(pGame->GetLocalPlayer()->m_Position.x, pGame->GetLocalPlayer()->m_Position.y += (float)(0.010 * func.Test1), pGame->GetLocalPlayer()->m_Position.z));
				}
			}
		}
	}

	SetNoRecoil();

	pDevice->SetRenderState(D3DRS_ZFUNC, renderState);
	
	return oEndScene(pDevice);
}





typedef HRESULT(WINAPI* oReset)(LPDIRECT3DDEVICE9 gpDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
oReset pReset;

HRESULT WINAPI hkReset(LPDIRECT3DDEVICE9 gpDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	if (!pMenu.RenderInit)
		return pReset(gpDevice, pPresentationParameters);

	//TRASH8
	if (pDXRend.Font)
		pDXRend.Font->OnLostDevice();

	if (pDXRend.objFont)
		pDXRend.objFont->OnLostDevice();

	if (pDXRend.pESP)
		pDXRend.pESP->OnLostDevice();

	if (pDXRend.objSprite)
		pDXRend.objSprite->OnLostDevice();

	if (pDXRend.Sprite)
		pDXRend.Sprite->OnLostDevice();

	if (pDXRend.pLine)
		pDXRend.pLine->OnLostDevice();

	ImGuiRender.InvalidateObjects();

	HRESULT hResult = (*pReset)(gpDevice, pPresentationParameters);

	ImGuiRender.CreateObjects(gpDevice);

	//TRASH9
	if (hResult == D3D_OK)
	{
		if (pDXRend.Font)
			pDXRend.Font->OnResetDevice();

		if (pDXRend.objFont)
			pDXRend.objFont->OnResetDevice();

		if (pDXRend.pESP)
			pDXRend.pESP->OnResetDevice();

		if (pDXRend.Sprite)
			pDXRend.Sprite->OnResetDevice();

		if (pDXRend.pLine)
			pDXRend.pLine->OnResetDevice();

		if (pDXRend.objSprite)
			pDXRend.objSprite->OnResetDevice();
	}
	return hResult;
}