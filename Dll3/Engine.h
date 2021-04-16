#pragma once

class CEngine
{
public:
	r3dRenderLayer * GetRenderer();
	ClientGameLogic * Client();
	ObjectManager* GetGameWorld();
	DWORD GetFirstObject();
	DWORD GetNextObject();
	void Auto_offset();
	bool ProjectToScreen(const D3DXVECTOR3& pvPos, D3DXVECTOR3* pvOut);
	D3DXVECTOR3 GetBonePos(obj_Player* pPlayer, char* BoneName);
	D3DXVECTOR3 GetBoneOrigin(obj_Player* pPlayer, int iBoneID);
};
extern CEngine pEng;


