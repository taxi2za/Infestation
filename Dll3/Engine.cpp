#include "Headers.h"
CEngine pEng;

typedef r3dRenderLayer* (__stdcall* tRender)(void);
tRender GetRender = (tRender)NULL;

DWORD dwRenderAddress = NULL;

static tRender* Render() {
	return (tRender*)(*(DWORD*)((DWORD)cTools.hGameBase + dwRenderAddress)); 
}
char name[MAX_PATH];
r3dRenderLayer* CEngine::GetRenderer()
{
	DWORD dwPBExe = (DWORD)GetModuleHandleA(NULL);
	while (dwRenderAddress ==  NULL)
	{
		dwRenderAddress = cTools.FindPattern1(cTools.hGameBase, 0x128000, (BYTE*)"\xA1\x00\x00\x00\x00\x05\x00\x00\x00\x00\x50", "x????x????x", 1);

		cTools.AddLog("dwRenderAddress %p", dwRenderAddress);
	}

	while (dwRenderAddress == NULL)
		return 0;

	dwRenderAddress = *(DWORD*)(dwRenderAddress);
	dwRenderAddress = dwRenderAddress - dwPBExe;

	GetRender = (tRender)((DWORD)Render);
	pGameRend = GetRender();
	return pGameRend;
}

typedef ClientGameLogic* (__stdcall* tGetGame)(void);
tGetGame GetGame = (tGetGame)NULL;

ClientGameLogic* CEngine::Client()
{
	DWORD PGame_offset = NULL;
	while (PGame_offset == 0)
	{
		//89 6C 24 28 E8 ? ? ? ? 89 44 24 10
		PGame_offset = cTools.FindPatternIDA(cTools.hGameBase, "89 6C 24 28 E8 ? ? ? ? 89 44 24 10") + 0x5;
		cTools.AddLog("PGame_offset %p", PGame_offset);
	}

	while (PGame_offset == NULL)
		return 0;

	PGame_offset = (*(DWORD*)PGame_offset + PGame_offset + 4);
	GetGame = (tGetGame)((DWORD)PGame_offset);
	pGame = GetGame();

	return pGame;
}



typedef ObjectManager* (__stdcall* tGetGameWorld)(void);
tGetGameWorld pGetGameWorld = (tGetGameWorld)NULL;

ObjectManager* CEngine::GetGameWorld()
{
	DWORD GameWorld_offset = NULL;
	while (GameWorld_offset == NULL)
	{//E8 ? ? ? ? 8B C8 E8 ? ? ? ? 85 C0 74 0F
		GameWorld_offset = cTools.FindPatternIDA(cTools.hGameBase, "E8 ? ? ? ? 8B C8 E8 ? ? ? ? 85 C0 74 0F") + 0x1;
		cTools.AddLog("GameWorld_offset %p", GameWorld_offset);
	}
	while (GameWorld_offset == NULL)
		return 0;

	GameWorld_offset = (*(DWORD*)GameWorld_offset + GameWorld_offset + 4);
	pGetGameWorld = (tGetGameWorld)((DWORD)GameWorld_offset);
	pGameWorld = pGetGameWorld();

	return pGameWorld;
}


DWORD CEngine::GetFirstObject()
{
	DWORD pGetFirstObject = NULL;
	while (pGetFirstObject == NULL)
	{//E8 ? ? ? ? 8B F0 3B F3 74 3E
		pGetFirstObject = cTools.FindPatternIDA(cTools.hGameBase, "E8 ? ? ? ? 8B F0 3B F3 74 3E") + 0x1;
		cTools.AddLog("pGetFirstObject %p", pGetFirstObject);
	}
	while (pGetFirstObject == NULL)
		return 0;

	pGetFirstObject = (*(DWORD*)pGetFirstObject + pGetFirstObject + 4);
	return pGetFirstObject;
}


DWORD CEngine::GetNextObject()
{
	DWORD pGetNextObject = NULL;
	while (pGetNextObject == NULL)
	{//E8 ? ? ? ? 8B F0 3B F3 75 CA
		pGetNextObject = cTools.FindPatternIDA(cTools.hGameBase, "E8 ? ? ? ? 8B F0 3B F3 75 CA") + 0x1;
		cTools.AddLog("pGetNextObject %p", pGetNextObject);
	}
	while (pGetNextObject == NULL)
		return 0;

	pGetNextObject = (*(DWORD*)pGetNextObject + pGetNextObject + 4);
	return pGetNextObject;
}


void CEngine::Auto_offset()
{
	DWORD NameAddress = NULL;
	DWORD HealthAddress = NULL;
	if (NameAddress == NULL)
	{//E8 ? ? ? ? 8B F0 8B 96 ? ? ? ?
		NameAddress = cTools.FindPatternIDA(cTools.hGameBase, "E8 ? ? ? ? 8B F0 8B 96 ? ? ? ?");
	}

	cTools.NameLenAddress = NameAddress + 0x9;
	cTools.NameLenAddress = *(DWORD*)(cTools.NameLenAddress);

	cTools.GetNameXor = NameAddress + 0xf;
	cTools.GetNameXor = *(DWORD*)(cTools.GetNameXor);

	if (HealthAddress == NULL)
	{//8B CE F3 0F 11 86 ? ? ? ? FF D0
		HealthAddress = cTools.FindPatternIDA(cTools.hGameBase, "8B CE F3 0F 11 86 ? ? ? ? FF D0");
	}
	
	cTools.Health = HealthAddress + 0x6;
	cTools.Health = *(DWORD*)(cTools.Health);
}

bool CEngine::ProjectToScreen(const D3DXVECTOR3& pvPos, D3DXVECTOR3* pvOut)
{
	D3DXMatrixIdentity(&cTools.matWorld);

	D3DXVec3Project(pvOut, &pvPos, &pDXRend.Viewport, &cTools.matProj, &cTools.matView, &cTools.matWorld);

	if (pvOut->z >= 1 || pvOut->z < 0 )
	{
		return false;

	}

	return true;
}


D3DXVECTOR3 CEngine::GetBonePos(obj_Player* pPlayer, char* BoneName)
{
	D3DXMATRIX v6;
	D3DXMATRIX v7;
	D3DXMATRIX BoneMatrix;
	D3DXVECTOR3 Pos;

	for (int i = 0; i < pPlayer->GetSkelet()->BonePtr->dwBoneNum; i++)
	{
		CBone* pBone = &pPlayer->GetSkelet()->BonePtr->Bones[i];

		if (pBone)
		{
			std::string BoneString = std::string(pBone->BoneName);

			std::transform(BoneString.begin(), BoneString.end(), BoneString.begin(), ::tolower);

			if (BoneString.find(BoneName) != std::string::npos)
			{
				D3DXMatrixRotationYawPitchRoll(&v6, 0.0, 1.5707963, 0.0);
				D3DXMatrixMultiply(&BoneMatrix, &pBone->BoneMatrix, &pPlayer->GetBoneCoeff());
				D3DXMatrixMultiply(&v7, &v6, &BoneMatrix);

				Pos.x = v7._41;
				Pos.y = v7._42;
				Pos.z = v7._43;

				return Pos;
			}
		}
	}
}


D3DXVECTOR3 CEngine::GetBoneOrigin(obj_Player* pPlayer, int iBoneID)
{
	if (!pPlayer != NULL || !pPlayer->GetSkelet() != NULL)
		return D3DXVECTOR3(0, 0, 0);

	if (!pPlayer->GetSkelet()->BonePtr != NULL)
		return D3DXVECTOR3(0, 0, 0);

	D3DXMATRIX v6;
	D3DXMATRIX v7;
	D3DXMATRIX BoneMatrix;
	D3DXVECTOR3 Pos;

	D3DXMatrixRotationYawPitchRoll(&v6, 0.0, 1.5707963, 0.0);
	BoneMatrix = pPlayer->GetSkelet()->BonePtr->Bones[iBoneID].BoneMatrix;
	D3DXMatrixMultiply(&BoneMatrix, &BoneMatrix, &pPlayer->GetBoneCoeff());
	D3DXMatrixMultiply(&v7, &v6, &BoneMatrix);

	Pos.x = v7._41;
	Pos.y = v7._42;
	Pos.z = v7._43;

	return Pos;
}