#include "Headers.h"

DWORD offLocalPlayer = 0;
ObjectManager* pGameWorld;
r3dRenderLayer* pGameRend;
ClientGameLogic* pGame;
obj_Player* pLocalPlayer;
IDirect3DDevice9* pDevice;

bool ValidPointer(void* p)
{
	return !IsBadReadPtr(p, 4) && p && HIWORD(p);
}