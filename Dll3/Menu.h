#pragma once

class MenuImGui
{
public:
	HWND            m_hTargetWindow;
	LONG_PTR        m_ulOldWndProc;
	WNDPROC oldWindowProc;
	void DrawRectRainbow(int x, int y, int width, int height, float flSpeed, float& flRainbow);
	void teams();
	void MenuRender();
	HWND GameWindow;
	bool RenderInit;
};

extern MenuImGui pMenu;
extern LRESULT ImGui_ImplDX9_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT __stdcall WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class ImGuiRendering {
public:
	void __stdcall CreateObjects(IDirect3DDevice9* pDevice);
	void __stdcall InvalidateObjects();
	void __stdcall PreRender(IDirect3DDevice9* device);
	void __stdcall PostRender(IDirect3DDevice9* deivce);
	void __stdcall EndPresent(IDirect3DDevice9* device);
	void __stdcall SetupPresent(IDirect3DDevice9* device);
	ImDrawList* _drawList;
private:
	ImDrawData _drawData;
	IDirect3DTexture9* _texture;
	ImFontAtlas _fonts;
	DWORD dwOld_D3DRS_COLORWRITEENABLE;
}; extern ImGuiRendering ImGuiRender;


class Features
{
public:
	bool ESP = 1;
	bool BoxPlayer = 0;
	bool SkeletonPlayer = 1;
	bool ClanPlayer = 0;
	bool NamePlayer = 1;
	bool RankPlayer = 0;
	bool WeaponPlayer = 1;
	bool Aimbot = 0;
	float AimSpeed = 3;
	float AimFov = 90;
	int Aimkey = 0x2;
	bool direction = 1;
	bool DebugPlayer = 0;
	bool FakeHero = 0;

	bool DistancePlayer = 0;
	bool NoCilp = 0;
	bool Superjump = 0;
	bool NoRecoil = 0;
	bool NoCilpV2 = 0;
	bool Time = 0;
	bool HealthPlayer = 1;
	bool FakePremium = 0;
	bool GhostMode = 0; 
	int keyGhost = 0x47; //https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
	float BoxColorPlayer[4] = { (1.000f, 1.000f, 1.000f, 1.000f) };
	float SkeletonColorPlayer[4] = { 1.000f, 1.000f, 1.000f, 1.000f };
	float ShadowColorPlayer[4] = { 1.000f, 1.000f, 1.000f, 1.000 };
	float TextColorPlayer[4] = { 1, 1, 1, 1 };
	float WeaponColorPlayer[4] = { 1.000, 1.000f, 1.000f, 1.000 };
	float TextColorCar[4] = { 1, 1, 1, 1 };
	float SuperZombie[4] = { 1.000f, 0.000f, 0.000f, 1.000f };
	float DirectionColor[4] = { 1.000f, 1.000f, 1.000f, 1.000f };

	bool ESPItem = 1;
	bool ESPNameItem = 1;
	bool ESPBoxItem = 1;
	bool AmmoI = 0;
	bool FoodI = 1;
	bool SniperI = 1;
	bool WeaponI = 1;
	bool GearI = 1;
	bool AttachmentI = 0;
	bool MeleeI = 0;
	bool ConsumableI = 1;
	float Alpha;

	float itemzcolorFood[4] = { 1.000f, 1.000f, 1.000f, 1.000f };
	float itemzcolorSniper[4] = { 0.627f, 0.125f, 0.941f, 1.000f };
	float itemzcolorWeapon[4] = { 1.000f, 0.000f, 0.000f, 1.000f };
	float itemzcolorGear[4] = { 0.439f, 0.439f, 0.438f, 1.000f };
	float INameTextColor[4] = { 1.000, 0.971, 0.000, 1.000 };
	float IAmmoTextColor[4] = { 1.000, 0.971, 0.000, 1.000 };
	float itemzcolorAttachment[4] = { 0.000f, 255.000f, 0.000f, 1.000f };
	float itemzcolorMelee[4] = { 255.000f, 0.502f, 0.000f, 1.000f };
	float itemzcolorConsumable[4] = { 0.975f, 0.000f, 0.696f, 1.000f };


	bool NoGrass = 0;
	bool InstantPickup = 0;
	bool Disconnect = 0;

	INT asd = 0;
	INT DayTime;
	INT DistancePlayer1 = 1000;
	INT Grass = 0;
	INT DistanceZombies = 350;
	INT DistanceItem = 150;
	float Test = 0.0f;
	float Test1 = 5.0f;
	
};
extern Features func;


