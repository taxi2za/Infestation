// dllmain.cpp : Defines the entry point for the DLL application.
#include "Headers.h"
#include "Hook.h"


DWORD dwPacketFunc = NULL;
HMODULE hHackModule = NULL;


DWORD processID = 0;

char text[255];
bool login = true;
DWORD MainThread(LPVOID lpArgs)
{

	l180)
		cTools.hGameBase = GetModuleHandle(NULL);
	l181)
		if (!cTools.szGameBase)
		{
			::Sleep(100);
			cTools.szGameBase = cTools.GetFileSizeA(NULL);
		}

	pGameRend = pEng.GetRenderer();
	cTools.AddLog("Renderer %p", pGameRend);

	pGame = pEng.Client();
	cTools.AddLog("pGame %p", pGame);

	pGameWorld = pEng.GetGameWorld();
	cTools.AddLog("pGameWorld %p", pGameWorld);

	cTools.pGetFirstObject = pEng.GetFirstObject();
	cTools.AddLog("pGetFirstObject %p", cTools.pGetFirstObject);

	cTools.pGetNextObject = pEng.GetNextObject();
	cTools.AddLog("pGetNextObject %p", cTools.pGetNextObject);

	if (!pDevice)
	{
		::Sleep(4000);
		pDevice = (LPDIRECT3DDEVICE9)pGameRend->pDevice;
	}

	DWORD* dVtable = (DWORD*)pDevice;

	dVtable = (DWORD*)dVtable[0];

	pReset = (oReset)dVtable[16];

	oEndScene = (tEndScene)dVtable[42];

	if (MH_Initialize() != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)dVtable[42], &hEndScene, (LPVOID*)&oEndScene) != MH_OK) { return 1; }
	if (MH_CreateHook((DWORD_PTR*)dVtable[16], &hkReset, (LPVOID*)&pReset) != MH_OK) { return 1; }


	pMenu.GameWindow = FindWindow("r3dWin", NULL);
	pMenu.oldWindowProc = (WNDPROC)SetWindowLongPtr(pMenu.GameWindow, GWL_WNDPROC, (LONG_PTR)WndProc);

	pDevice->Release();

	while (1)
	{
		Sleep(100);
		if (MH_EnableHook((DWORD_PTR*)dVtable[42]) != MH_OK) { return 1; }
		if (MH_EnableHook((DWORD_PTR*)dVtable[16]) != MH_OK) { return 1; }

	}

	return 1;

}
/*
extern "C" __declspec(dllexport) */BOOL WINAPI DllMain(HMODULE hDll, DWORD lpReason, LPVOID lpReversed)
{
	if (lpReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDll);
		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, NULL, NULL, NULL);
		MessageBox(NULL, "ERROR", "ERROR", MB_OK | MB_ICONERROR);
		hHackModule = hDll;
	}
	return TRUE;
}