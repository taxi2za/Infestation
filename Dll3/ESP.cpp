#include "Headers.h"
ImU32 Text;
D3DCOLOR colESP;
char* GetReputation(int Rep)
{
	if (Rep <= -5) {
		if (Rep <= -1000)
			return (char*)"Villain";
		else if (Rep <= -600)
			return (char*)"Assassin";
		else if (Rep <= -300)
			return (char*)"Hitman";
		else if (Rep <= -100)
			return (char*)"Bandit";
		else if (Rep <= -20)
			return (char*)"Outlaw";
		else
			return (char*)"Thug";

	}
	else if (Rep >= 5) {
		if (Rep >= 1000)
			return (char*)"Paragon";
		else if (Rep >= 500)
			return (char*)"Vigilante";
		else if (Rep >= 250)
			return (char*)"Guardian";
		else if (Rep >= 80)
			return (char*)"Lawmen";
		else if (Rep >= 20)
			return (char*)"Deputy";
		else
			return (char*)"Constable";
	}

	return (char*)"Civilian";
}

char* GetReputation(char* name) {

	int rep = 0;
	bool repset = false;

	for (int i = 0; i < 512; i++) {
		HudEntry ent = *(HudEntry*)((DWORD)pGame + 0x1124 + (i * 0x67C));

		char* name1 = ent.name;
		char* name2 = name;

		if (strstr(name1, name2)) {
			rep = ent.reputation;
			repset = true;
			break;
		}
	}

	if (!repset)
		return (char*)"Not found!";

	return GetReputation(rep);
}

float Distance(D3DXVECTOR3  me, D3DXVECTOR3 you)
{

	float tempx, tempy, tempz, tempA;

	tempx = (me.x - you.x) * (me.x - you.x);
	tempy = (me.y - you.y) * (me.y - you.y);
	tempz = (me.z - you.z) * (me.z - you.z);

	tempA = tempx + tempy + tempz;

	if (tempA < 0)
		tempA = (tempA * (-1));

	return sqrt(tempA);
}
double GetDistance(double x1, double y1, double x2, double y2)
{
	return sqrt(pow((x2 - x1), 2) + pow((y2 - y1), 2));
}


CEsp pEsp;
char txt[1024] = { '\0' };
void CEsp::DrawSkeleton(obj_Player* pPlayer, Color Color)
{
	pDXRend.DrawBone(pPlayer, 0, 2, Color); //spine
	pDXRend.DrawBone(pPlayer, 2, 3, Color);
	pDXRend.DrawBone(pPlayer, 3, 4, Color);
	pDXRend.DrawBone(pPlayer, 4, 5, Color);
	pDXRend.DrawBoneFix(pPlayer, 5, 6, Color);

	pDXRend.DrawBone(pPlayer, 0, 53, Color);
	pDXRend.DrawBone(pPlayer, 53, 54, Color);
	pDXRend.DrawBone(pPlayer, 54, 55, Color);
	pDXRend.DrawBone(pPlayer, 55, 56, Color);

	pDXRend.DrawBone(pPlayer, 0, 58, Color);
	pDXRend.DrawBone(pPlayer, 58, 59, Color);
	pDXRend.DrawBone(pPlayer, 59, 60, Color);
	pDXRend.DrawBone(pPlayer, 60, 61, Color);

	pDXRend.DrawBone(pPlayer, 5, 7, Color); //L arm
	pDXRend.DrawBone(pPlayer, 7, 8, Color);
	pDXRend.DrawBone(pPlayer, 8, 9, Color);
	pDXRend.DrawBone(pPlayer, 9, 10, Color);

	pDXRend.DrawBone(pPlayer, 5, 28, Color); //R arm
	pDXRend.DrawBone(pPlayer, 28, 29, Color);
	pDXRend.DrawBone(pPlayer, 29, 30, Color);
	pDXRend.DrawBone(pPlayer, 30, 31, Color);
}

void test3Dbox(r3dBox3D Box, float* color, float a)
{
	_107)
	D3DXVECTOR3 p1, p2;
	D3DXVECTOR3 r[12], e[12];
	// 1
	_108)
	p1 = Box.Org;
	_109)
	p2 = p1;
	_110)
	p2.x += Box.Size.x;
	_111)
	if (pEng.ProjectToScreen(p1, &r[1]))
	{
		_112)
		if (pEng.ProjectToScreen(p2, &e[1]))
		{
			_113)
			DrawLine(r[1].x, r[1].y, e[1].x, e[1].y, color, a, 1);
		}
	}
	_114)
	p2 = p1;
	_115)
	p2.z += Box.Size.z;
	_116)
	if (pEng.ProjectToScreen(p1, &r[2]))
	{
		_180)
		if (pEng.ProjectToScreen(p2, &e[2]))
		{
			_117)
			DrawLine(r[2].x, r[2].y, e[2].x, e[2].y, color, a, 1);
		}
	}
	_118)
	p2 = p1;
	_119)
	p2.y += Box.Size.y;
	_120)
	if (pEng.ProjectToScreen(p1, &r[3]))
	{
		_121)
		if (pEng.ProjectToScreen(p2, &e[3]))
		{
			_122)
			DrawLine(r[3].x, r[3].y, e[3].x, e[3].y, color, a, 1);
		}
	}
	_123)
	p1.y += Box.Size.y;
	p2 = p1;
	_124)
	p2.x += Box.Size.x;
	_125)
	if (pEng.ProjectToScreen(p1, &r[4]))
	{
		_126)
		if (pEng.ProjectToScreen(p2, &e[4]))
		{
			_127)
			DrawLine(r[4].x, r[4].y, e[4].x, e[4].y, color, a, 1);
		}
	}
	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);
	_128)
	p2 = p1;
	_129)
	p2.z += Box.Size.z;
	_130)
	if (pEng.ProjectToScreen(p1, &r[5]))
	{
		_131)
		if (pEng.ProjectToScreen(p2, &e[5]))
		{
			_132)
			DrawLine(r[5].x, r[5].y, e[5].x, e[5].y, color, a, 1);
		}
		_1)
	}
	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);

	// 2
	_133)
	p1 = Box.Org;
	_134)
	p1.x += Box.Size.x;
	_135)
	p2 = p1;
	_136)
	p2.z += Box.Size.z;
	_137)
	if (pEng.ProjectToScreen(p1, &r[6]))
	{
		_138)
		if (pEng.ProjectToScreen(p2, &e[6]))
		{
			_139)
			DrawLine(r[6].x, r[6].y, e[6].x, e[6].y, color, a, 1);
		}_140)
	}
	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);
	_141)
	p2 = p1;
	_142)
	p2.y += Box.Size.y;
	_143)
	if (pEng.ProjectToScreen(p1, &r[7]))
	{
		_144)
		if (pEng.ProjectToScreen(p2, &e[7]))
		{
			_145)
			DrawLine(r[7].x, r[7].y, e[7].x, e[7].y, color, a, 1);
		}
	}_146)
	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);

	// 3
		_147)
	p1 = Box.Org;
	_148)
	p1.z += Box.Size.z;
	_149)
	p2 = p1;
	_150)
	p2.x += Box.Size.x;
	_151)
	if (pEng.ProjectToScreen(p1, &r[8]))
	{
		_152)
		if (pEng.ProjectToScreen(p2, &e[8]))
		{
			_153)
			DrawLine(r[8].x, r[8].y, e[8].x, e[8].y, color, a, 1);
		}_154)
	}
	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);
	_155)
	p2 = p1;
	_156)
	p2.y += Box.Size.y;
	_157)
	if (pEng.ProjectToScreen(p1, &r[9]))
	{
		_158)
		if (pEng.ProjectToScreen(p2, &e[9]))
		{
			_159)
			DrawLine(r[9].x, r[9].y, e[9].x, e[9].y, color, a, 1);
		}_160)
	}
	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);
	_161)
	// 4
	p1 = Box.Org + Box.Size;
	_162)
	p2 = p1; _163)
	p2.x -= Box.Size.x; _164)
	if (pEng.ProjectToScreen(p1, &r[10]))
	{
		_165)
		if (pEng.ProjectToScreen(p2, &e[10]))
		{
			_166)
			DrawLine(r[10].x, r[10].y, e[10].x, e[10].y, color, a, 1);
		}_167)
	}_168)
	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);
	p2 = p1; _169)
	p2.z -= Box.Size.z; _170)
	if (pEng.ProjectToScreen(p1, &r[11]))
	{
		_171)
		if (pEng.ProjectToScreen(p2, &e[11]))
		{
			_172)
			DrawLine(r[11].x, r[11].y, e[11].x, e[11].y, color, a, 1);
		}_173)
	}_174)

	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);
	p2 = p1; _175)
	p2.y -= Box.Size.y; _176)

	if (pEng.ProjectToScreen(p1, &r[12]))
	{
		_178)
		if (pEng.ProjectToScreen(p2, &e[12]))
		{
			_179)
			DrawLine(r[12].x, r[12].y, e[12].x, e[12].y, color, a, 1);
		}
	}
	//r3dDrawLine3D(p1, p2, Cam, fLineWidth, clr);

}


static const int GRID_SPAN_X = 10;
static const int GRID_SPAN_Y = 10;
bool GetItemScreenPosition(GameObject* item, float screenGrid[GRID_SPAN_X][GRID_SPAN_Y], float gridXSpan, float gridYSpan, int offsetHeight, float distance, float normalRadius, float& screenX, float& screenY) {

	float screenWidth = (float)pDXRend.Viewport.Width;
	float screenHeight = (float)pDXRend.Viewport.Height;

	float cellSizeX = screenWidth / (float)gridXSpan;
	float cellSizeY = screenHeight / (float)gridYSpan;
	D3DXVECTOR3 screenPos;

	if (pEng.ProjectToScreen(item->getPosition(), &screenPos))
	{

		int itemCellX = (int)(screenPos.x / cellSizeX);
		int itemCellY = (int)(screenPos.y / cellSizeY);

		int cellDrawX = ((float)cellSizeX * (float)itemCellX);
		int cellDrawY = ((float)cellSizeY * ((float)itemCellY + 1));

		if (itemCellX >= gridXSpan || itemCellY >= gridYSpan) {
			screenX = (float)screenPos.x;
			screenY = (float)screenPos.y;

			return true;
		}

		if (itemCellX < 0 || itemCellY < 0) {
			screenX = (float)screenPos.x;
			screenY = (float)screenPos.y;

			return true;
		}
		if (distance > normalRadius) {

			if (screenGrid[itemCellX][itemCellY] > 0) {
				int offset = screenGrid[itemCellX][itemCellY] * offsetHeight;
				screenX = cellDrawX;
				screenY = cellDrawY - offset;
			}

			screenGrid[itemCellX][itemCellY]++;
		}
		else {
			screenX = (float)screenPos.x;
			screenY = (float)screenPos.y;
		}
		
		return true;
	}

	return false;
}


void CEsp::MatrixToScreen()
{
	D3DXMATRIX matTmp = *(D3DXMATRIX*)((DWORD)pGameRend + 0x220);
	if (matTmp.m[3][3] != 1.f)
	{
		cTools.matProj = matTmp;
		cTools.matView = *(D3DXMATRIX*)((DWORD)pGameRend + 0x1A0);
	}
}

#define R3D_PI           3.1415926f
#define R3D_DEG2RAD(x)   (((x) * R3D_PI) / 180.0f)

D3DXMATRIX 	DrawRotMatrix;

template<class T>
__forceinline T R3D_MAX(const T a, const T b) { return a > b ? a : b; }

void RenderPlayers_test()
{
	if (VALID(pGame))
	{
		if (!VALID(pLocalPlayer))
			pLocalPlayer = (obj_Player*)pGame->GetLocalPlayer();

		if (VALID(pGameWorld))
		{
			GameObject* object = pGameWorld->GetFirstObject();
			do
			{
				if (VALID(object))
				{

					if (object == NULL /*|| object == (GameObject*)pLocalPlayer*/)
						continue;

					EGameObjectType objectType = object->GetObjType();


					if (!(objectType & OBJTYPE_Human) && !(objectType & OBJTYPE_Zombie) && !(objectType & OBJTYPE_GameplayItem) && !(objectType & OBJTYPE_Vehicle))
						continue;


					if (objectType & OBJTYPE_Human)
					{
						obj_Player* pEntity = (obj_Player*)(object);

						/*if (pLocalPlayer->bDead() == 1 || pEntity->bDead() == 1)
							continue;*/

						D3DXVECTOR3 screen;
						if (pEng.ProjectToScreen(pEntity->m_Position, &screen))
						{
							pDXRend.TextEsp(screen.x, screen.y, White, pDXRend.Font, "Entity");
						}

					}
				}
			} while (object = pGameWorld->GetNextObject(object));
		}
	}
}

bool RayCast(D3DXVECTOR3 position, D3DXVECTOR3 direction, float length, physx::PxRaycastHit& pRayHit)
{
	//const physx::PxSceneQueryFilterData& filterData = physx::PxSceneQueryFilterData(physx::PxSceneQueryFilterFlag::eSTATIC);
	CPhysicsWorld* pPhysicsWorld = CPhysicsWorld::Singleton();
	return pPhysicsWorld->m_pPXScene->raycastSingle(physx::PxVec3(position.x, position.y, position.z),physx::PxVec3(direction.x, direction.y, direction.z),length,physx::PxSceneQueryFlag::eIMPACT | physx::PxSceneQueryFlag::eNORMAL | physx::PxSceneQueryFlag::eDISTANCE,
		pRayHit, physx::PxSceneQueryFilterData(physx::PxSceneQueryFilterFlag::eSTATIC));
}
bool IsVisible(const D3DXVECTOR3& vPosition)
{
	D3DXVECTOR3 viewPosition = pGameRend->GetViewPosition();
	D3DXVECTOR3 vDistance = vPosition - viewPosition;
	D3DXVECTOR3 vUnitDirection;
	float tDistance = D3DXVec3Length(&vDistance);
	D3DXVec3Normalize(&vUnitDirection, &vDistance);

	physx::PxRaycastHit rayHitResult;
	if (!RayCast(viewPosition, vUnitDirection, tDistance, rayHitResult))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void CEsp::RenderPlayers()
{
	//CPhysicsWorld* pPhysicsWorld = CPhysicsWorld::Singleton();

	D3DXVECTOR3 AimBoneHead{};
	DOUBLE Farthest = func.AimFov;
	UINT BestTarget = -1;


	float screenGrid[GRID_SPAN_X][GRID_SPAN_Y];
	memset(screenGrid, 0, sizeof(screenGrid[0][0]) * GRID_SPAN_X * GRID_SPAN_Y);


	_1)
	GameObject* object = pGameWorld->GetFirstObject();
	do
	{
		_2)
			if (object == NULL || object == (GameObject*)pLocalPlayer)
				continue;
		_3)
			EGameObjectType objectType = object->GetObjType();

		_4)
			if (!(objectType & OBJTYPE_Human) && !(objectType & OBJTYPE_Zombie) && !(objectType & OBJTYPE_GameplayItem) && !(objectType & OBJTYPE_Vehicle))
				continue;

		_5)
			float distance = Distance(object->getPosition(), pGame->GetLocalPlayer()->getPosition());

		float fadeStart = float(func.DistancePlayer1) * 0.50f;
		float fadeEnd = float(func.DistancePlayer1);
		float Alpha = (distance < fadeStart) ? 1.0f * 255 : (1.0f - ((distance - fadeStart) / (fadeEnd - fadeStart))) * 255;
		

		D3DXVECTOR3 vDistance = object->getPosition() - pGame->GetLocalPlayer()->getPosition();
		D3DXVECTOR3 vUnitDirection;
		D3DXVec3Normalize(&vUnitDirection, &vDistance);

		_6)
			if (objectType & OBJTYPE_Human)
			{
				obj_Player* pTarget = (obj_Player*)(object);

				if (ValidPointer(pTarget))
				{

					_7)
					int i = 0;
					D3DXVECTOR3 screen;
					obj_Player* pTarget = (obj_Player*)(object);
					
					// If the player is dead, skip it
					_8)
					//if (!pTarget->isAlive())
					//	continue;

					_9)
					if (ValidPointer(pTarget))
					{
						_10)
					//	if (distance <= func.DistancePlayer1)
						{
							_11)
							if (pEng.ProjectToScreen(pTarget->getPosition(), &screen))
							{
								bool isvisible = IsVisible(pEng.GetBoneOrigin(pTarget, 6));
								
								if (pTarget->m_AuraType() == 4)
								{
									Text = ImColor(255, 215, 0, int(Alpha));
								}
								else
								{
									if (isvisible)
									{
										Text = ImColor(0, 255, 215, int(Alpha));
									}
									else
									{
										Text = ImColor(255, 255, 255, int(Alpha));
									}
								}

								_12)
								if (func.NamePlayer) { pTarget->GetName(txt); pDXRend.DrawStrokeText(screen.x, screen.y + (i * 12) + 3, Text, Black, txt); ++i; }

								_13)
								if (pTarget->ClanID() != 0)
								{
									if (func.NamePlayer)
									{
										_14)
										ImU32 clanTagColor;
										switch (pTarget->ClanColor())
										{
										default: clanTagColor = ImColor(255, 255, 255, 0);

										case 1: clanTagColor = ImColor(170, 0, 0); 
											break;
										case 2: clanTagColor = ImColor(166, 120, 12);
											break;
										case 3: clanTagColor = ImColor(16, 164, 158);
											break;
										case 4: clanTagColor = ImColor(32, 164, 20); 
											break;
										case 5: clanTagColor = ImColor(16, 78, 164); 
											break;
										case 6: clanTagColor = ImColor(150, 16, 164);
											break;
										case 7: clanTagColor = ImColor(68, 68, 68);
											break;
										case 8: clanTagColor = ImColor(164, 164, 164);
											break;
										}
										_15)
										sprintf_s(txt, "[%s]", pTarget->CLAN());
										pDXRend.DrawStrokeText(screen.x - 38, screen.y + 3, clanTagColor, Black, txt);
									}
								}



								if (func.WeaponPlayer)
								{
									if (pTarget->primID() != NULL)
									{
										cItems itemz = getObjectFromId(pTarget->primID());
										sprintf_s(txt, "%s", itemz.name);
										pDXRend.DrawStrokeText(screen.x, screen.y + (i * 12) + 3, (ImU32)ImColor(255, 0, 0), Black, txt); ++i;
									}
								}

								_16)
								if (func.RankPlayer) { pTarget->GetName(txt); pDXRend.DrawStrokeText(screen.x, screen.y + (i * 12) + 3, Text, Black, GetReputation(txt)); ++i; }
								_17)
								if (func.DistancePlayer) { sprintf_s(txt, "[%0.1f M]", distance); pDXRend.DrawStrokeText(screen.x, screen.y + (i * 12) + 3, Text, Black, txt); ++i; }
								_18)
								if (func.HealthPlayer) { float hp = pTarget->GetHealth(); sprintf_s(txt, "HP: %0.0f", hp); pDXRend.DrawStrokeText(screen.x, screen.y + (i * 12) + 3, Text, Black, txt); ++i; }
							

							//	BaseItemConfig* itemConfig = WeaponArmory__getConfig(pTarget->primID());
							//	sprintf_s(txt, "%s", itemConfig->m_StoreName);
							//	pDXRend.DrawStrokeText(screen.x, screen.y + (i * 12) + 3, Text, Black, txt); ++i;

								
								/*if (pTarget->m_AuraType() == 4)
								{
									sprintf_s(txt, "SpawnProtect: %0.0f", pTarget->m_SpawnProtectedUntil() - cTools.r3dGetTime); pDXRend.DrawStrokeText(screen.x, screen.y + (i * 12) + 3, Text, Black, txt); ++i;
								}*/
									//sprintf_s(txt, "AuraType: %d : %0.0f", pTarget->m_AuraType(), pTarget->m_AuraType()); pDXRend.DrawStrokeText(screen.x, screen.y + (i * 12) + 3, White, Black, txt); ++i;

								_19)
									if (func.SkeletonPlayer) 
									{
										if (pTarget->bDead() == 0)
										{
											DrawSkeleton(pTarget, Text);
										}
										D3DXVECTOR3 Bone_pos, Bone_Head;  _24)
											if (pEng.ProjectToScreen(pEng.GetBoneOrigin(pTarget, 6) + D3DXVECTOR3(0, 0.110, 0), &Bone_Head))
											{
												_25)
													if (pEng.ProjectToScreen(pEng.GetBoneOrigin(pTarget, 6) - D3DXVECTOR3(0, 0.02, 0), &Bone_pos))
													{
														_26)
															float BHeight = Bone_Head.y - Bone_pos.y;
														pDXRend.DrawCircle(Bone_Head.x, Bone_Head.y, BHeight, Text, 0xFF);
													}
											}
									}



								// aimbot
								if (func.Aimbot)
								{
									D3DXVECTOR3 HeadPos; _27)
									if (!pEng.ProjectToScreen(pEng.GetBoneOrigin(pTarget, 6), &HeadPos))
										continue;
									_28)
									float CrosshairDst = GetDistance(HeadPos.x, HeadPos.y, ScreenCenterX, ScreenCenterY);
									_29)
									pDXRend.DrawCircle(ScreenCenterX, ScreenCenterY, func.AimFov, White, 0xF5AC);
									_30)
									if (CrosshairDst < Farthest)
									{
										_31)
										Farthest = CrosshairDst;
										_32)
										BestTarget = i;
										_34)
										AimBoneHead = HeadPos;
									}
								}
							}
						}
					}
				}
			}
		if (objectType & OBJTYPE_Zombie)
		{
			_36)
			obj_Zombie* pTarget = (obj_Zombie*)(object);
			_37)
			if (ValidPointer(pTarget))
			{
				D3DXVECTOR3 screen; _38)
				if (pEng.ProjectToScreen(pTarget->Position(), &screen))
				{
					ImU32 Color = ImColor(255, 0, 0);
					_39)
					if (pTarget->m_typeIndex() == TRUE) // Zombie 0  SuperZombie 1 
					{
						_40)
						sprintf_s(txt, "SuperZombie");
						_41)
						pDXRend.DrawStrokeText(screen.x, screen.y, Color, Black, txt);
						_42)
						test3Dbox(object->bbox_world(), func.SuperZombie,1);
					}
					else
					{
						/*ImU32 Color = ImColor(255, 0, 0, Alpha);
						ImU32 Black1 = ImColor(0, 0, 0, Alpha);
				
						pDXRend.DrawStrokeText(screen.x, screen.y, Color, Black1, "Zombie");*/
					}
				}
			}
		}_43)
		if (objectType & OBJTYPE_Vehicle)
		{
			_44)
			if (ValidPointer(object))
			{
				D3DXVECTOR3 screen;
				_45)
				if (pEng.ProjectToScreen(object->getPosition(), &screen))
				{
					_46)
					test3Dbox(object->bbox_world(), func.TextColorCar,1);
				}
			}
		}_47)

		if (objectType & OBJTYPE_GameplayItem)
		{
			_48)
			obj_DroppedItem* item = (obj_DroppedItem*)(object);
			D3DXVECTOR3 screen;
			_49)
			int itemID = item->ItemId();
			_50)
			cItems itemz = getObjectFromId(item->ItemId());
			_51)
			if (!func.ESPItem)
				continue;

			float gatheredScreenX = 0;
			float gatheredScreenY = 0;

			_52)
			//if (distance <= func.DistanceItem)


			float fadeStart = float(func.DistanceItem) * 0.010f;
			float fadeEnd = float(func.DistanceItem);
			float Alpha = (distance < fadeStart) ? 1.0f / 255 : (1.0f - ((distance - fadeStart) / (fadeEnd - fadeStart))) / 255;

			{
				_53)
				if (pEng.ProjectToScreen(object->bbox_world().Center(), &screen))
				{
					_54)
					if (itemz.type == Weapon)
					{
						_56)
						if (func.WeaponI)
						{
							if (func.ESPBoxItem)
							{
								_59)
									test3Dbox(object->bbox_world(), func.itemzcolorWeapon, Alpha);
							}
							_57)
							if (func.ESPNameItem)
							{
								//if (GetItemScreenPosition(object, screenGrid, GRID_SPAN_X, GRID_SPAN_Y, 13, distance, 0, gatheredScreenX, gatheredScreenY)) 
								{
									if (gatheredScreenX == 0)
									{
										sprintf(txt, "%s", itemz.name);
										DrawTextIm(screen.x, screen.y, func.itemzcolorWeapon, Alpha, txt);
									}
									else
									{
									//	sprintf(txt, "%s", itemz.name);
									//	DrawTextIm(gatheredScreenX, gatheredScreenY, func.itemzcolorWeapon, txt);
									}
								}
							}
							
						}
					}
					if (itemz.type == Gear)
					{
						if (func.GearI)
						{
							if (func.ESPBoxItem)
							{
								_61)
									test3Dbox(object->bbox_world(), func.itemzcolorGear, Alpha);
							}
							if (func.ESPNameItem)
							{
								//if (GetItemScreenPosition(object, screenGrid, GRID_SPAN_X, GRID_SPAN_Y, 13, distance, 10, gatheredScreenX, gatheredScreenY)) 
								{
									if (gatheredScreenX == 0)
									{
										sprintf(txt, "%s", itemz.name);
										DrawTextIm(screen.x, screen.y, func.itemzcolorGear, Alpha, txt);
									}
									else
									{
									//	sprintf(txt, "%s", itemz.name);
									//	DrawTextIm(gatheredScreenX, gatheredScreenY, func.itemzcolorGear, txt);
									}
								}
							}

							
						}
					}_69)
					if (itemz.type == Attachment)
					{
						_70)
						if (func.AttachmentI)
						{
							if (func.ESPBoxItem)
							{
								_74)
									test3Dbox(object->bbox_world(), func.itemzcolorAttachment, Alpha);
							}
							_71)
							if (func.ESPNameItem)
							{
							//	if (GetItemScreenPosition(object, screenGrid, GRID_SPAN_X, GRID_SPAN_Y, 13, distance, 0, gatheredScreenX, gatheredScreenY))
								{
									if (gatheredScreenX == 0)
									{
										sprintf(txt, "%s", itemz.name);
										DrawTextIm(screen.x, screen.y, func.itemzcolorAttachment, Alpha, txt);
									}
									else
									{
									//	sprintf(txt, "%s", itemz.name);
									//	DrawTextIm(gatheredScreenX, gatheredScreenY, func.itemzcolorAttachment, txt);
									}
								}
							}
							
						}
					}_75)
					if (itemz.type == Consumable)
					{
						if (func.ConsumableI)
						{
							if (func.ESPBoxItem)
							{
								test3Dbox(object->bbox_world(), func.itemzcolorConsumable, Alpha);
							}
							if (func.ESPNameItem)
							{
								//if (GetItemScreenPosition(object, screenGrid, GRID_SPAN_X, GRID_SPAN_Y, 13, distance, 0, gatheredScreenX, gatheredScreenY)) 
								{
									if (gatheredScreenX == 0)
									{
										sprintf(txt, "%s", itemz.name, Alpha);
										DrawTextIm(screen.x, screen.y, func.itemzcolorConsumable, Alpha, txt);
									}
									else
									{
										//sprintf(txt, "%s", itemz.name);
										//DrawTextIm(gatheredScreenX, gatheredScreenY, func.itemzcolorConsumable, txt);
									}
								}
							}


							
						}
					}_81)
					if (itemz.type == Sniper)
					{
						_82)
						if (func.SniperI)
						{
							if (func.ESPBoxItem)
							{
								_86)
									test3Dbox(object->bbox_world(), func.itemzcolorSniper, Alpha);
							}
							_83)
							if (func.ESPNameItem)
							{
								//if (GetItemScreenPosition(object, screenGrid, GRID_SPAN_X, GRID_SPAN_Y, 13, distance, 0, gatheredScreenX, gatheredScreenY)) 
								{
									if (gatheredScreenX == 0)
									{
										sprintf(txt, "%s", itemz.name);
										DrawTextIm(screen.x, screen.y, func.itemzcolorSniper, Alpha, txt);
									}
									else
									{
									///	sprintf(txt, "%s", itemz.name);
									///	DrawTextIm(gatheredScreenX, gatheredScreenY, func.itemzcolorSniper, txt);
									}
								}
							}
							
						}
					}
					if (itemz.type == Throwable)
					{

					}
					if (itemz.type == Other)
					{
					}
					_87)
					if (itemz.type == Food)
					{
						_89)
						if (func.FoodI)
						{
							if (func.ESPBoxItem)
							{
								_93)
									test3Dbox(object->bbox_world(), func.itemzcolorFood, Alpha);
							}
							_90)
							if (func.ESPNameItem)
							{
								//if (GetItemScreenPosition(object, screenGrid, GRID_SPAN_X, GRID_SPAN_Y, 13, distance, 0, gatheredScreenX, gatheredScreenY)) 
								{
									if (gatheredScreenX == 0)
									{
										sprintf(txt, "%s", itemz.name);
										DrawTextIm(screen.x, screen.y, func.itemzcolorFood, Alpha, txt);
									}
									else
									{
										//sprintf(txt, "%s", itemz.name);
										//DrawTextIm(gatheredScreenX, gatheredScreenY, func.itemzcolorFood, txt);
									}
								}
							}
							
						}
					}
					if (itemz.type == Melee)
					{
						if (func.MeleeI)
						{
							if (func.ESPBoxItem)
							{
								_96)
									test3Dbox(object->bbox_world(), func.itemzcolorMelee, Alpha);
							}
							if (func.ESPNameItem)
							{
								//if (GetItemScreenPosition(object, screenGrid, GRID_SPAN_X, GRID_SPAN_Y, 13, distance, 0, gatheredScreenX, gatheredScreenY))
								{
									if (gatheredScreenX == 0)
									{
										sprintf(txt, "%s", itemz.name);
										DrawTextIm(screen.x, screen.y, func.itemzcolorMelee, Alpha, txt);
									}
									else
									{
										//sprintf(txt, "%s", itemz.name);
										//DrawTextIm(gatheredScreenX, gatheredScreenY, func.itemzcolorMelee, txt);
									}
								}
							}
						
						}
					}
					_97)
				}
				_98)
			}
			_99)
		}
		_100)
	}while (object = pGameWorld->GetNextObject(object));


		_101)
	// end loop
	if (func.Aimbot)
	{_102)
		if (BestTarget != -1)
		{
			_103)
			if (GetAsyncKeyState(func.Aimkey) & 0x8000)
			{
				_104)
				int offsetX = (AimBoneHead.x - ScreenCenterX) / func.AimSpeed;
				_105)
				int offsetY = (AimBoneHead.y - ScreenCenterY) / func.AimSpeed;
				_106)
				mouse_event(MOUSEEVENTF_ABSOLUTE || MOUSEEVENTF_MOVE, offsetX, offsetY, 0, 0);
			}
		}
	}

		
}
	