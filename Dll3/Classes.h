
class ClientGameLogic;
class obj_Player;
class CPlayer;
class obj_Zombie;
class BaseItemConfig;
class CBone;
class CBoneTemp;
class CSkeleton;
class HudEntry;
class BasePhysicsObject;
#define r3dPoint3D D3DXVECTOR3
typedef r3dPoint3D r3dVector;

#ifndef MAKEDWORD
#define MAKEDWORD(a,b,c,d) ((unsigned __int32) (((unsigned __int32)a) & 0xFF) | ((((unsigned __int32)b) & 0xFF) << 8) | ((((unsigned __int32)c) & 0xFF) << 16) | ((((unsigned __int32)d) & 0xFF) << 24))
#endif



class CPhysicsWorld
{
public:
	char _0x0000[16];
	physx::PxScene* m_pPXScene; //0x004  

	static CPhysicsWorld* Singleton()
	{
		return *(CPhysicsWorld**)((DWORD)GetModuleHandle(NULL) + 0xCAE4C8); //(+0x13) E8 ? ? ? ? 8B 06 0F 57 C0 
	};
};



//BF3A9C


template<typename T, BYTE b0, BYTE b2, BYTE b1, BYTE b3> class r3EncPtr
{
public:
	static T Get(void* ptr, DWORD offset)
	{
		return (T)(*(DWORD*)((DWORD)ptr + offset) ^ MAKEDWORD(b0, b1, b2, b3));
	}
};

class r3dBox3D
	//----------------------------------------------------------------
{
public:
	D3DXVECTOR3 	Org;
	D3DXVECTOR3 	Size;
public:

	D3DXVECTOR3	Center()
	{
		return Org + Size * 0.5f;
	}
};

class HudEntry
{
public:
	int reputation;
	char pad0[0x10];
	char name[0x40];
	char pad1[0x4];
};

class r3dRenderLayer
{
public:
	__int32 bInited; //0x0000 
	__int32 Version; //0x0004 
	DWORD HLibWin; //0x0008 
	DWORD DeviceType; //0x000C 
	DWORD* pdi; //0x0010 
	IDirect3D9* pd3d; //0x0014 
	DWORD BackBufferWidth; //0x0018 
	DWORD BackBufferHeight; //0x001C 
	char _0x0020[4]; //0x0020 
	DWORD BackBufferCount; //0x0024 
	char _0x0028[4];
	DWORD MultiSampleQuality; //0x002C 
	char _0x0030[4];
	DWORD hDeviceWindow; //0x0034 
	DWORD Windowed; //0x0038 
	DWORD EnableAutoDepthStencil; //0x003C 
	__int32 refreshRate; //0x0040 
	char _0x0044[12];
	LPDIRECT3DDEVICE9 pDevice; //0x0050 
	char _0x0054[304];
	D3DXVECTOR3 CameraPosition; //0x0184 
	D3DXVECTOR3 DistanceCullRefPos; //0x0190 
	char _0x019C[4];
	D3DXMATRIX View; //0x01A0 
	D3DXMATRIX InverseView; //0x01E0 
	D3DXMATRIX Projection; //0x0220
	char _0x022C[572];
	float        ScreenW; // 0x49C
	float        ScreenH;
	float        ScreenW2;
	float        ScreenH2;
	float         ViewX;
	float        ViewY;
	float        ViewW;
	float        ViewH;
	float        ViewMinZ;
	float        ViewMaxZ;


	D3DXVECTOR3 GetViewPosition()
	{
		D3DXMATRIX inverseView;
		D3DXMatrixInverse(&inverseView, NULL, &View);
		return D3DXVECTOR3(inverseView._41, inverseView._42, inverseView._43);
	}

	D3DXVECTOR3 vLocalOrigin()
	{
		D3DXVECTOR3 LocalOrigin;

		D3DXMATRIX mView = this->View;
		LocalOrigin.x = -mView._41;
		LocalOrigin.y = -mView._42;
		LocalOrigin.z = -mView._43;

		D3DXMatrixTranspose(&mView, &mView);
		D3DXVec3TransformNormal(&LocalOrigin, &LocalOrigin, &mView);

		return LocalOrigin;
	}
};



class GBGameInfo
{
public:
	char name[32]; //0x0000
	uint8_t mapId; //0x0020
	uint16_t maxPlayers; //0x0021
	char pad_0023[1]; //0x0023
	uint32_t flags; //0x0024
	uint32_t gameServerId; //0x0028
	uint16_t gameTimeLimit; //0x002C
	uint8_t wut; //0x002E
	uint8_t region; //0x002F
	uint8_t channel; //0x0030
	char pad_0031[3]; //0x0031
}; //Size: 0x0034

class r3dNetworkImpl;

class r3dNetwork
{
private:
	r3dNetworkImpl* impl;

public:
	int		dumpStats_;
	int		lastPing_;
	DWORD		firstBindIP_;
	const static int FIRST_FREE_PACKET_ID = 0;
	const static int RAKNET_USER_PACKET = 134; // must be more that RakNet::ID_USER_PACKET_ENUM

public:
	r3dNetwork();
	~r3dNetwork();
};
#define r3d_assert(_Expression) (void)( (!!(_Expression)))
struct r3dNetPacketHeader
{
	// this first BYTE will be passed directly to RakNet network library.
	const BYTE	RakNetPacketID;
	const BYTE	EventID;

	r3dNetPacketHeader(int PKT_ID) : RakNetPacketID(r3dNetwork::RAKNET_USER_PACKET), EventID((BYTE)PKT_ID)
	{
		r3d_assert(PKT_ID >= r3dNetwork::FIRST_FREE_PACKET_ID && PKT_ID < 0xFF);
	}
};

class ClientGameLogic
{
public:
	virtual	void		OnNetPeerConnected(DWORD peerId);
	virtual	void		OnNetPeerDisconnected(DWORD peerId);
	virtual	void		OnNetData(DWORD peerId, const r3dNetPacketHeader* packetData, int packetSize);
	obj_Player* GetLocalPlayer();
	CPlayer* GetLocalCPlayer();

	char _0x0008[8];
	__int32 lastPing_; //0x0010 

	obj_Player* GetPlayer(_DWORD* pThis, int Idx)
	{
		//int v3; // [esp+4h] [ebp+4h]
		int result = pThis[Idx + 584]; //  eax
		if (result)
		{
			int v3 = *(_DWORD*)(result + 4); // [esp+4h] [ebp+4h]
			LOBYTE(v3) = *(_BYTE*)(result + 2) ^ v3;
			BYTE2(v3) ^= *(_BYTE*)result;
			BYTE1(v3) ^= *(_BYTE*)(result + 1);
			HIBYTE(v3) ^= *(_BYTE*)(result + 3);
			result = v3;
		}
		return (obj_Player*)result;
	}

	int GetLocalIndex(void)
	{
		return *(int*)((DWORD)(this) + 0xD0940); //3B BA ? ? ? ? 75 15 
	}

	GBGameInfo GameInfo()
	{
		GBGameInfo Info = *(GBGameInfo*)((DWORD)(this) + 0xD0948);
		return Info;
	}
};

enum EGameObjectType
{
	OBJTYPE_Generic = (1 << 0),
	OBJTYPE_Terrain = (1 << 1),		// terrain object
	OBJTYPE_Mesh = (1 << 2),		// mesh object
	OBJTYPE_Road = (1 << 3),		// road object
	OBJTYPE_Building = (1 << 4),		// building object
	OBJTYPE_Human = (1 << 5), // obj_Player
	OBJTYPE_Particle = (1 << 6), // particle emitter
	OBJTYPE_Sound = (1 << 7), // sound emitter
	OBJTYPE_Trees = (1 << 8), // all world trees
	OBJTYPE_ApexDestructible = (1 << 11),
	OBJTYPE_AnimMesh = (1 << 12),
	OBJTYPE_DecalProxy = (1 << 13),
	OBJTYPE_Sprite = (1 << 15),
	OBJTYPE_Vehicle = (1 << 16),
	OBJTYPE_Zombie = (1 << 17),
	OBJTYPE_GameplayItem = (1 << 18),
	OBJTYPE_CollectionProxy = (1 << 19),
	OBJTYPE_ItemSpawnPoint = (1 << 20),
	OBJTYPE_SharedUsableItem = (1 << 21),
};
enum Playerstate_e
{
	PLAYER_INVALID = -1,

	PLAYER_IDLE = 0,
	PLAYER_IDLEAIM,

	PLAYER_MOVE_CROUCH,
	PLAYER_MOVE_CROUCH_AIM,
	PLAYER_MOVE_WALK_AIM,
	PLAYER_MOVE_RUN,
	PLAYER_MOVE_SPRINT,
	PLAYER_MOVE_PRONE,

	PLAYER_PRONE_AIM,
	PLAYER_PRONE_UP,
	PLAYER_PRONE_DOWN,
	PLAYER_PRONE_IDLE,

	PLAYER_SWIM_IDLE,
	PLAYER_SWIM_SLOW,
	PLAYER_SWIM,
	PLAYER_SWIM_FAST,

	PLAYER_VEHICLE_DRIVER,
	PLAYER_VEHICLE_PASSENGER,

	PLAYER_DIE,

	PLAYER_NUM_STATES,
};

enum AuraType
{
	AT_NONE,
	AT_BERSERK,
	AT_HEALING,
	AT_MORHINE,
	AT_SPAWNPROTECTION,
	AT_COUNT
};

class AObject
{
	class AClass* Class;		// 0000
	unsigned char _0004[0x4];	// 0004
};

class GameObject : public AObject
{
public:

	D3DXVECTOR3 getPosition()
	{
		D3DXVECTOR3 vPlayer = *(D3DXVECTOR3*)((DWORD)(this) + 0x2C);
		return vPlayer;
	}

	EGameObjectType GetObjType()
	{
		EGameObjectType ObjTypeFlags = *(EGameObjectType*)((DWORD)(this) + 0x228);
		return ObjTypeFlags;
	}

	bool isObjType(EGameObjectType i)
	{
		return (GetObjType() & i);
	}

	r3dBox3D  bbox_world()
	{
		r3dBox3D  bbox_world = *(r3dBox3D*)((DWORD)(this) + 0x1A0);
		return bbox_world;
	}
	BasePhysicsObject* PhysicsObject()
	{
		return *(BasePhysicsObject * *)((DWORD)(this) + 0x298);
	}

};



class ObjectManager
{
public:
	GameObject* GetFirstObject()
	{
		DWORD pGetFirstObject = cTools.pGetFirstObject;
		__asm
		{
			mov ecx, this
			call pGetFirstObject
		}
	}
	GameObject* GetNextObject(GameObject* obj)
	{
		DWORD pGetNextObject = cTools.pGetNextObject;
		__asm
		{
			push obj
			call pGetNextObject
		}
	}
};


class CSkeleton
{
public:
	char _0x0000[40];
	CBoneTemp* BonePtr; //0x0028 
};

class CBoneTemp
{
public:
	char _0x0000[20];
	DWORD dwBoneNum;
	CBone* Bones; //0x0018 
};

class CBone
{
public:
	char* BoneName; //0x0000  
	char unknown4[136]; //0x0004
	D3DXMATRIX BoneMatrix; //0x008C
	D3DXMATRIX SomeMatrix; //0x00CC  
};//Size=0x010C(268)




class BasePhysicsObject
{
public:
	virtual ~BasePhysicsObject() {}
	virtual void			Move(const r3dPoint3D& move, float sharpness = 0.5f) = 0; // move object, used for controller
	virtual void 			SetPosition(const r3dPoint3D& pos) = 0;
	virtual void 			SetRotation(const r3dVector& Angles) = 0;
	virtual void 			SetVelocity(const r3dPoint3D& vel) = 0;
	virtual void			SetScale(const r3dPoint3D& scale) = 0;
	virtual r3dPoint3D 		GetPosition() const = 0;
	virtual D3DXMATRIX 		GetRotation() const = 0;
	virtual r3dPoint3D 		GetVelocity() const = 0;
	virtual r3dPoint3D		GetScale() const = 0;

	// physics object position is in a center of object. 
	// in engine, center of object is in pivot.
	// so this diff is to make sure that position in physics and engine is in sync
	virtual void			SetPositionCorrection(const r3dPoint3D& diff) = 0;

	virtual bool			IsSleeping() = 0;
	virtual void			ForceToSleep() = 0;

	virtual void			addSmoothVelocity(const r3dVector& vel) {};
	virtual void			addImpulse(const r3dVector& impulse) {};
	virtual void			AddImpulseAtPos(const r3dPoint3D& impulse, const r3dPoint3D& pos) {};
	virtual void			AddImpulseAtLocalPos(const r3dPoint3D& impulse, const r3dPoint3D& pos) {};
	virtual void			AdjustControllerSize(float new_radius, float new_height, float) {};


};

typedef float vec_t;

class Vector
{
public:
	vec_t x, y, z;
	vec_t Dot(const Vector& vOther) const;


};
FORCEINLINE vec_t DotProduct(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline vec_t Vector::Dot(const Vector& vOther) const
{
	return DotProduct(*this, vOther);
}


class CPlayer
{
public:

	char pad_0x0000[0x10]; //0x0000
	float hashID; //0x0010 
	D3DXVECTOR3 vLoadTimePos; //0x0014 
	D3DXVECTOR3 vScl; //0x0020 
	D3DXVECTOR3 vPos; //0x002C 
	D3DXVECTOR3 vLoadTimeRot; //0x0038 
	D3DXVECTOR3 vRot; //0x0044 
	DWORD NetworkID; //0x0050 
	char pad_0x0054[0x30C]; //0x0054
	__int32 m_AuraType; //0x0360 
	float m_AuraTransarency; //0x0364 
	float m_SpawnProtectedUntil; //0x0368 
	wchar_t m_MinimapTagIconName[64]; //0x036C 
	float CurrentSpread; //0x03EC 
	char pad_0x03F0[0x1D28]; //0x03F0
	__int32 HeroId; //0x2118 
	__int32 HeadIdx; //0x211C 
	__int32 BodyIdx; //0x2120 
	__int32 LegsIdx; //0x2124 
	__int32 BackpackID; //0x2128 
	__int32 Alive; //0x212C 
	__int64 DeathUtcTime; //0x2130 
	__int32 SecToRevive; //0x2138 
	float Health; //0x213C 
	float Hunger; //0x2140 
	float Thirst; //0x2144 
	float Toxic; //0x2148 
	float MedBleeding; //0x214C 
	float MedFeverCold; //0x2150 
	float MedBloodInfection; //0x2154 
	__int32 GameMapId; //0x2158 
	DWORD GameServerId; //0x215C 
	D3DXVECTOR3 GamePos; //0x2160 
	float GameDir; //0x216C 
	DWORD GameFlags; //0x2170 
	__int64 SecFromLastGame; //0x2174 
	char pad_0x217C[0x4]; //0x217C
	__int32 XP; //0x2180 
	__int32 SpendXP; //0x2184 
	__int32 TimePlayed; //0x2188 
	__int32 Reputation; //0x218C 
	char pad_0x2190[0x24]; //0x2190
	__int32 KilledZombies; //0x21B8 
	__int32 KilledSurvivors; //0x21BC 
	__int32 KilledBandits; //0x21C0 
	__int32 Deaths; //0x21C4 
	__int32 ShotsFired; //0x21C8 
	__int32 ShotsHits; //0x21CC 
	__int32 ShotsHeadshots; //0x21D0 
	char pad_0x21D4[0xE0]; //0x21D4
	__int32 BackpackSize; //0x22B4 
	__int64 InventoryID; //0x22B8 
	__int32 itemID; //0x22C0 
	__int32 quantity; //0x22C4 
	__int32 Var1; //0x22C8 
	__int32 Var2; //0x22CC 
	__int32 MAX_DURABILITY; //0x22D0 
	__int32 Var3; //0x22D4 
	char pad_0x22D8[0x558]; //0x22D8

};



class CWeaponInfo
{
public:
	unsigned char  unk0[0x14];   //0000
	DWORD    clip;    //0014
	unsigned char  unk1[0x0C];   //0018
	DWORD   Armory;    //0024
	DWORD    unk2;    //0028
	DWORD    state;    //002C
	DWORD    type;    //0030
	unsigned char  unk3[0x0C];   //0034
	float    damage;    //0040
	float    range;    //0044
	DWORD    firerate;   //0048
	float    recoil;    //004C
	float    spread;    //0050
	DWORD    clipsize;   //0054
};
class obj_Player /*: public GameObject*/
{
public:
	virtual void Func();
	virtual void Func1();
	virtual void Func2();
	virtual void Func3();
	virtual void Func4();
	virtual void Func5();
	virtual void Func6();
	virtual void Func7();
	virtual void Func8();
	virtual void Func9();
	virtual void Func10();
	virtual void Func11();
	virtual void Func12();
	virtual void SetPosition(const D3DXVECTOR3& pos, bool a = false /*false : 0 ? 1 */);
	virtual void SetPosition_0(const D3DXVECTOR3& pos, int a2 = 200 /*a2 != 200 WTF*/);//virtual void SetPosition(const D3DXVECTOR3& pos);
	virtual void Func15();//virtual void SetRotationVector(const D3DXVECTOR3& pos);
	virtual void Func16();//virtual void SetVelocity(const D3DXVECTOR3& pos);
	virtual void Func17();//virtual	const D3DXVECTOR3& GetPosition() const;
	virtual	const D3DXVECTOR3& GetRotationVector() const;

	char pad_0000[40]; //0x0000
	D3DXVECTOR3 m_Position; //0x0002C  

	AuraType m_AuraType()
	{
		return *(AuraType*)((DWORD)(this) + 0x360);
	}

	int primID()
	{
		return *(int*)((DWORD)(this) + 0x22c0);
	}

	float m_SpawnProtectedUntil()
	{
		return *(float*)((DWORD)(this) + 0x368);
	}
	BasePhysicsObject* PhysicsObject()
	{
		return *(BasePhysicsObject**)((DWORD)(this) + 0x298);
	}

	D3DXVECTOR3 getPosition()
	{
		D3DXVECTOR3 vPlayer = *(D3DXVECTOR3*)((DWORD)(this) + 0x2C);
		return vPlayer;
	}

	char* GetNameXor(void)
	{
		return (char*)((DWORD)(this) + 0x418);
	}
	int NameLenAddress(void)
	{
		return *(int*)((DWORD)(this) + 0x458);
	}
	void GetName(PCHAR pszName)
	{
		int iNameLen = this->NameLenAddress();
		memcpy(pszName, GetNameXor(), iNameLen + 1);
		for (int i = 0; i < iNameLen; i++)
		{
			pszName[i] ^= i + 79;
		}
	}
	float GetHealth()
	{
		return *(float*)((DWORD)(this) + 0x213C);
	}

	float yaw()
	{
		return *(float*)((DWORD)(this) + 0x3680);
	}

	float palt()
	{
		return *(float*)((DWORD)(this) + 0x3684);
	}

	bool isAlive()
	{
		return (this->GetHealth() > 0);
	}
	int bDead()
	{
		return *(int*)((DWORD)(this) + 0x345C); //83 BF ? ? ? ? ? 0F 85 ? ? ? ? 8B 8F ? ? ? ?
	}
	wchar_t* CLAN()
	{
		return (wchar_t*)((DWORD)(this) + 0x20A8); // 8D 86 ? ? ? ? BA ? ? ? ? BD ? ? ? ?
	}
	int ClanColor(void)
	{
		return *(int*)((DWORD)(this) + 0x20A8 - 0x4);
	}
	int ClanID(void)
	{
		return *(int*)((DWORD)(this) + 0x20A8 - 0x8);
	}

	CSkeleton* GetSkelet()
	{
		return *(CSkeleton * *)((DWORD)this + 0x2ED0);//8B 89 ? ? ? ? 8D 54 24 04
	}

	CWeaponInfo* WNP()
	{
		return *(CWeaponInfo * *)((DWORD)this + 0x2EE8);
	}

	D3DXMATRIX GetBoneCoeff()
	{
		return *(D3DXMATRIX*)((DWORD)this + 0x3580);//8D 81 ? ? ? ? 83 EC 40 
	}
};

enum EZombieStates // EGlobalStates
{
	ZState_Dead = 0,
	ZState_Sleep,
	ZState_Waking,
	ZState_Idle,
	ZState_Walk,
	ZState_Pursue,
	ZState_Attack,
	ZState_BarricadeAttack,

	ZState_NumStates,
};

class obj_Zombie
{
public:
	/*
.text:0049887D 81 F9 FD 4E 00 00                                               cmp     ecx, 4EFDh
.text:00498883 0F 94 C2                                                        setz    dl
.text:00498886 56                                                              push    esi
.text:00498887 89 86 58 03 00 00                                               mov     [esi+358h], eax <-- m_typeIndex
.text:0049888D 53                                                              push    ebx
.text:0049888E 8D BE 10 04 00 00                                               lea     edi, [esi+410h]
.text:00498894 89 96 5C 03 00 00                                               mov     [esi+35Ch], edx
.text:0049889A 8B 0C 85 C8 FD D7 00                                            mov     ecx, dword_D7FDC8[eax*4]
.text:004988A1 8B 14 85 C0 FD D7 00                                            mov     edx, dword_D7FDC0[eax*4]
.text:004988A8 51                                                              push    ecx
.text:004988A9 52                                                              push    edx
.text:004988AA 8B CF                                                           mov     ecx, edi
.text:004988AC E8 9F DC 2A 00                                                  call    sub_746550
.text:004988B1 8B 86 EF 03 00 00                                               mov     eax, [esi+3EFh]
.text:004988B7 8B 0D E4 E8 D7 00                                               mov     ecx, dword_D7E8E4
.text:004988BD 50                                                              push    eax
.text:004988BE E8 8D BF FA FF                                                  call    sub_444850
.text:004988C3 8B E8                                                           mov     ebp, eax
.text:004988C5 3B EB                                                           cmp     ebp, ebx
.text:004988C7 75 14                                                           jnz     short loc_4988DD
.text:004988C9 8B 8E EF 03 00 00                                               mov     ecx, [esi+3EFh] <-- HeroID
.text:004988CF 51                                                              push    ecx
.text:004988D0 68 58 A1 BB 00                                                  push    offset aThereIsNoZombi ; "there is no zombie hero %d"
.text:004988D5 E8 06 B0 2A 00                                                  call    sub_7438E0
	*/
	int HeroID()
	{
		int vPlayer = *(int*)((DWORD)(this) + 0x3F3);
		return vPlayer;
	}

	int m_typeIndex()
	{
		int vPlayer = *(int*)((DWORD)(this) + 0x35C);
		return vPlayer;
	}

	D3DXVECTOR3 Position()
	{
		D3DXVECTOR3 vPlayer = *(D3DXVECTOR3*)((DWORD)(this) + 0x02C);
		return vPlayer;
	}
	EZombieStates getZombieState(void)
	{
		EZombieStates ZombieState = *(EZombieStates*)((DWORD)(this) + 0x2484);
		return ZombieState;
	}
};

class obj_DroppedItem : public GameObject
{
public:
	D3DXVECTOR3 Position()
	{
		D3DXVECTOR3 vPlayer = *(D3DXVECTOR3*)((DWORD)(this) + 0x02C);
		return vPlayer;
	}
	int ItemId()
	{
		return *(int*)((DWORD)(this) + 0x3E0);
	}
};

class BaseItemConfig
{
public:
	char _0000[4];			// 0000
	UINT32 m_itemID;		// 0004
	int category;// 0008
	char* m_Description;	// 000C
	char* m_StoreIcon;		// 0010
	char* m_StoreName;		// 0014
	float m_Weight;			// 0018 in kg
	// wchar_t* m_StoreNameW;	// 0018
	// wchar_t* m_DescriptionW;// 001C
	char _001C[0x14];		// 001C
};







extern r3dRenderLayer* pGameRend;
extern ObjectManager* pGameWorld;
extern ClientGameLogic* pGame;
extern obj_Player* pLocalPlayer;
extern IDirect3DDevice9* pDevice;
extern bool ValidPointer(void* p);

