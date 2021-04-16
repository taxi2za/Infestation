#pragma once

class CEsp
{
public:
	void RenderPlayers();
	void DrawSkeleton(obj_Player* pPlayer, Color Color);
	void MatrixToScreen();
	/*void RenderWorldStuff();
	void RadarPlayers(obj_Player *pBaseEnt, DWORD tCol);
	void DrawRadar(float x, float y, float s, char* text);
	void RadarHeader(int x, int y, int w, int h, char *title);*/
};
void RenderPlayers_test();
std::string ShowIDitem(int Id);
extern CEsp pEsp;


class cItems {
public:
	const char* name;
	D3DCOLOR typeColor;
	int type;

	cItems()
	{
	};

	cItems(const char* name, D3DCOLOR typeColor, int type)
	{
		this->name = name;
		this->typeColor = typeColor;
		this->type = type;
	}
};

static enum eTypes { Gear, Armour, Backpacks, Helmts, Consumable, Food, Throwable, Weapon, Melee, Attachment, Other, Crafting, Unknown1, Sniper };
static cItems getObjectFromId(int ID) 
{
	 std::map <int, cItems> items;
	 bool init = false;

	if (!init) {
		init = !init;

		items[101306] = cItems("Flashlight", White, Melee);
		items[101307] = cItems("Hammer", White, Melee);
		items[101309] = cItems("Pickaxe", White, Melee);
		items[101267] = cItems("Tactical Knife", White, Melee);
		items[101278] = cItems("Bat", White, Melee);
		items[101313] = cItems("Spiked Bat", White, Melee);
		items[101314] = cItems("Metal Bat", White, Melee);
		items[101335] = cItems("Kandy Kane", White, Melee);
		items[101336] = cItems("Katana", White, Melee);
		items[101339] = cItems("Machete", White, Melee);
		items[101344] = cItems("Canoe Paddle", White, Melee);
		items[101385] = cItems("Garden Shears", White, Melee);
		items[101386] = cItems("Golf Club", White, Melee);
		items[101345] = cItems("Cricket Bat", White, Melee);
		items[101382] = cItems("Crowbar", White, Melee);
		items[101391] = cItems("Wrench", White, Melee);
		items[101383] = cItems("Fire Axe", White, Melee);
		items[101381] = cItems("Butterfly Knif", White, Melee);
		items[101343] = cItems("Brass Knuckles", White, Melee);
		items[101346] = cItems("Shovel", White, Melee);
		items[101338] = cItems("Wakizashi", White, Melee);
		items[101337] = cItems("Jokoto Katan", White, Melee);
		items[101308] = cItems("Hatchet", White, Melee);
		items[101389] = cItems("Police Baton", White, Melee);
		items[101386] = cItems("Police Bato", White, Melee);	//old?
		items[101388] = cItems("Pitchfork", White, Melee);
		items[101384] = cItems("Frying Pan", White, Melee);
		items[101390] = cItems("Power Drill", White, Melee);

		items[101068] = cItems("SVD", Purple, Sniper);
		items[101084] = cItems("VSS", Purple, Sniper);
		items[101085] = cItems("Mauser", Purple, Sniper);
		items[101087] = cItems("AWM", Purple, Sniper);
		items[101088] = cItems("M107", Purple, Sniper);
		items[101217] = cItems("MAURSER DESERT", Purple, Sniper);
		items[101247] = cItems("BLASER R93", Purple, Sniper);

		//guns primeri
		items[101002] = cItems("M16", Red, Weapon);
		items[101332] = cItems("Kruger .22 Rifle", Red, Weapon);
		items[101005] = cItems("G36", Red, Weapon);
		items[101022] = cItems("AK47M", Red, Weapon);
		items[101032] = cItems("AKM", Red, Weapon);
		items[101035] = cItems("AKS74U", Red, Weapon);
		items[101040] = cItems("M4 SEMI", Red, Weapon);
		items[101055] = cItems("M4", Red, Weapon);
		items[101172] = cItems("SIG556 ASR", Red, Weapon);
		items[101173] = cItems("IMITAR21", Red, Weapon);
		items[101106] = cItems("HONEYBADGER", Red, Weapon);
		items[101169] = cItems("MASADA", Red, Weapon);
		items[101193] = cItems("FN SCAR", Red, Weapon);
		items[101210] = cItems("FNSCARNS", Red, Weapon);
		items[101334] = cItems("KRUGER MINI14", Red, Weapon);
		items[101060] = cItems("PKM", Red, Weapon);
		items[101093] = cItems("RPK", Red, Weapon);
		items[101095] = cItems("FN M249", Red, Weapon);
		items[101197] = cItems("RA H23", Red, Weapon);
		items[101103] = cItems("MP5", Red, Weapon);
		items[101107] = cItems("P90", Red, Weapon);
		items[101108] = cItems("EVO3", Red, Weapon);
		items[101109] = cItems("BIZON", Red, Weapon);
		items[101063] = cItems("MP7", Red, Weapon);
		items[101064] = cItems("UZI", Red, Weapon);
		items[101201] = cItems("SR1 VERSEK", Red, Weapon);
		items[101246] = cItems("P90S", Red, Weapon);
		items[101004] = cItems("FN Five7", Red, Weapon);
		items[101111] = cItems("B92", Red, Weapon);
		items[101112] = cItems("B93R", Red, Weapon);
		items[101115] = cItems("JERICHO", Red, Weapon);
		items[101120] = cItems("SIG P226", Red, Weapon);
		items[101180] = cItems("DESERT EAGLE", Red, Weapon);
		items[101224] = cItems("STI EAGLE ELITE", Red, Weapon);
		items[101331] = cItems("ANACONDA", Red, Weapon);
		items[101330] = cItems("KRUGER .22", Red, Weapon);
		items[101098] = cItems("SAIGA", Red, Weapon);
		items[101158] = cItems("MOSSBERG", Red, Weapon);
		items[101183] = cItems("KTDECIDER", Red, Weapon);
		items[101200] = cItems("AA-12", Red, Weapon);
		items[101321] = cItems("DOUBLE BARREL", Red, Weapon);
		items[101322] = cItems("CROSS BOW", Red, Weapon);
		items[101320] = cItems("FLARE GUN", Red, Other);
		items[101310] = cItems("Frag Grenade", Red, Weapon);
		items[101392] = cItems("Nail Gun", Red, Weapon);
		items[101341] = cItems("Mosin Rifle", Red, Weapon);
		items[101342] = cItems("1911", Red, Weapon);
		items[800011] = cItems("FAMAS", Red, Weapon);
		items[800030] = cItems("QBZ", Red, Weapon);
		items[800032] = cItems("PECHENEG", Red, Weapon);
		items[800027] = cItems("LS 90", Red, Weapon);
		items[700001] = cItems("SCAR WORLD", Red, Weapon);




		//Meds + Baricadas
		items[101256] = cItems("Antibiotics", White, Consumable);
		items[101261] = cItems("Bandages", White, Consumable);
		items[101262] = cItems("Bandages DX", White, Consumable);
		items[101300] = cItems("Pain killers", White, Consumable);
		items[101301] = cItems("Zombie Repellent", White, Other);
		items[101302] = cItems("C01-Vaccine", White, Consumable);
		items[101303] = cItems("C04-Vaccine", White, Consumable);
		items[101304] = cItems("Medkit", White, Consumable);
		items[101399] = cItems("Repair Kit", White, Consumable);
		items[101312] = cItems("Flare", White, Other);
		items[101305] = cItems("Time Capsule", White, Other);
		items[101324] = cItems("Sandbag Barricade", White, Consumable);
		items[101316] = cItems("Barb Wire Barricade", White, Consumable);
		items[101317] = cItems("Wood Shield Barricade", White, Consumable);
		items[800066] = cItems("Desert Riot", White, Consumable);
		items[101318] = cItems("Riot Shield", White, Consumable);
		items[101323] = cItems("Air Horn", White, Consumable);

		//Atachment + amm
		items[101315] = cItems("Binoculars", Green, Other);
		items[101319] = cItems("Range Finder", Green, Other);
		items[400000] = cItems("Forward Grip", Green, Other);
		items[400001] = cItems("5.45 AK 30", Green, Attachment);
		items[400003] = cItems("ACOG", Green, Other);
		items[400004] = cItems("Rifle Laser", Green, Other);
		items[400005] = cItems("Holographic", Green, Other);
		items[400006] = cItems("SCAR IS", Green, Other);
		items[400007] = cItems("Kobra", Green, Other);
		items[400008] = cItems("Tactical Sniper Scope", Green, Other);
		items[400009] = cItems("SMG Grip", Green, Other);
		items[400010] = cItems("STANAG 60", Green, Attachment);
		items[400012] = cItems("Flash Hider", Green, Other);
		items[400013] = cItems("Silencer", Green, Attachment);
		items[400015] = cItems("STANAG 45", Green, Attachment);
		items[400016] = cItems("STANAG 30", Green, Attachment);
		items[400017] = cItems("STANAG C-Mag", Green, Attachment);
		items[400018] = cItems("Rifle Flashlight", Green, Other);
		items[400019] = cItems("Compact Scope", Green, Other);
		items[400020] = cItems("Red Dot SP", Green, Other);
		items[400021] = cItems("Pistol laser", Green, Other);
		items[400022] = cItems("Pistol Flashlight", Green, Other);
		items[400023] = cItems("Reflex Sight", Green, Other);
		items[400024] = cItems("M4 IS", Green, Other);
		items[400025] = cItems("SIG 556", Green, Other);
		items[400026] = cItems("MP7 IS", Green, Other);
		items[400027] = cItems("PSO-1", Green, Other);
		items[400029] = cItems("G36 ammo", Green, Attachment);
		items[400030] = cItems("VSS-20", Green, Attachment);
		items[400031] = cItems("VSS-10", Green, Attachment);
		items[400032] = cItems("MP7 40", Green, Attachment);
		items[400033] = cItems("MP7 30", Green, Attachment);
		items[400034] = cItems("9x19 Para Mag", Green, Other);
		items[400035] = cItems("M249 IS", Green, Other);
		items[400036] = cItems("KT IS", Green, Other);
		items[400038] = cItems("Blackwater Long Range", Green, Attachment);
		items[400039] = cItems("Swiss Arms Scope 8x", Green, Attachment);
		items[400040] = cItems("Iron AK74M", Green, Other);
		items[400042] = cItems("Iron G36", Green, Other);
		items[400043] = cItems("AWM .338 Magnum ammo", Green, Attachment);
		items[400046] = cItems("P90 50 rounds", Green, Attachment);
		items[400047] = cItems("Bizon 64 ammo", Green, Attachment);
		items[400048] = cItems("SVD ammo", Green, Attachment);
		items[400049] = cItems("CZ Scorpion EVO-3 ammo", Green, Attachment);
		items[400050] = cItems("AA-12 Drum", Green, Attachment);
		items[400051] = cItems("EVO-3 IS", Green, Other);
		items[400052] = cItems("Bizon IS", Green, Other);
		items[400053] = cItems("USS-12 IS", Green, Other);
		items[400054] = cItems("P90 IS", Green, Other);
		items[400055] = cItems("Pecheneg IS", Green, Other);
		items[400056] = cItems("PKM IS", Green, Other);
		items[400058] = cItems("SIG516 IS", Green, Other);
		items[400059] = cItems("TAR21 IS", Green, Other);
		items[400060] = cItems("RPK IS", Green, Other);
		items[400061] = cItems("RPO IS", Green, Other);
		items[400062] = cItems("AN94 IS", Green, Other);
		items[400065] = cItems("AT4 IS", Green, Other);
		items[400066] = cItems("M4 IS2", Green, Other);
		items[400069] = cItems("5.45 AK 45", Green, Attachment);
		items[400070] = cItems(".308 Winchester Sniper rifle ammo", Green, Attachment);
		items[400071] = cItems("9mm Mag", Green, Attachment);
		items[400073] = cItems("Saiga 10 ammo", Green, Attachment);
		items[400074] = cItems("standard muzzle", Green, Other);
		items[400079] = cItems("MP5 10mm Mag", Green, Attachment);
		items[400080] = cItems("SAIGA IS", Green, Other);
		items[400081] = cItems("XA5 IS", Green, Other);
		items[400082] = cItems("M590 Is", Green, Other);
		items[400083] = cItems("Veresk IS", Green, Other);
		items[400084] = cItems("SMG-20 ammo", Green, Attachment);
		items[400085] = cItems("SMG-40 ammo", Green, Attachment);
		items[400086] = cItems("Desert Eagle ammo", Green, Other);
		items[400087] = cItems("5.7 FN M240 Mag", Green, Attachment);
		items[400088] = cItems("SMG Grip 1", Green, Other);
		items[400099] = cItems("G36 C-Mag", Green, Attachment);
		items[400100] = cItems("5.45 AK Drum", Green, Attachment);
		items[400101] = cItems("7.62 AKM clip", Green, Attachment);
		items[400119] = cItems("MASADA IS", Green, Other);
		items[400121] = cItems("USS-12 IS", Green, Other);
		items[400127] = cItems("M16 IS", Green, Other);
		items[400128] = cItems("AKM IS", Green, Other);
		items[400129] = cItems("AKS IS", Green, Other);
		items[400133] = cItems(".50 BMG", Green, Attachment);
		items[400134] = cItems("UZI IS", Green, Other);
		items[400135] = cItems(".45 ACP STI Eagle Elite ammo", Green, Attachment);
		items[400136] = cItems("12 Gauge Ammo", Green, Attachment);
		items[400137] = cItems("2x 12gauge", Green, Attachment);
		items[400139] = cItems("Arrow Explosive", Green, Attachment);
		items[400140] = cItems("Arrow", Green, Attachment);
		items[400141] = cItems("Shotgun shell 2x", Green, Attachment);
		items[400142] = cItems("Shotgun shell 8x", Green, Attachment);
		items[400143] = cItems("M249 Ammo Box", Green, Attachment);
		items[400144] = cItems(".22 Caliber Clip", Green, Attachment);
		items[400145] = cItems("Anaconda clip", Green, Attachment);
		items[400146] = cItems("Large Kruger Rifle Clip", Green, Attachment);
		items[400147] = cItems("Medium Kruger Rifle Clip", Green, Attachment);
		items[400148] = cItems("Stardard Kruger .22 Rifle Clip", Green, Attachment);
		items[400149] = cItems("Kruger Rifle IS", Green, Other);
		items[400150] = cItems("Kruger Mini-14 clip", Green, Attachment);
		items[400151] = cItems("Kruger Mini-14 IS", Green, Attachment);
		items[400154] = cItems(".40 Caliber 1911MAG", Green, Attachment);
		items[400153] = cItems("Standart Mosin Magazine", Green, Attachment);
		items[400152] = cItems("Flare Clip", Green, Other);
		items[400157] = cItems("Nail Strip", Green, Attachment);

		//Armour
		items[20015] = cItems("Custom Guerilla", Grey, Gear);
		items[20054] = cItems("IBA Sand", Grey, Gear);
		items[20056] = cItems("MTV Forest", Grey, Gear);
		items[20059] = cItems("Light Gear Forest", Grey, Gear);
		items[800014] = cItems("Midium VDM", Grey, Gear);

		//Backpacks
		items[20175] = cItems("Medium Backpack", Grey, Gear);
		items[20176] = cItems("Small Backpack", Grey, Gear);
		items[20179] = cItems("Large Backpack", Grey, Gear);
		items[20180] = cItems("Military Ruck", Grey, Gear);
		items[20181] = cItems("Teddy Bear backpack", Grey, Gear);
		items[20185] = cItems("ALICE Rucksack", Grey, Gear);
		items[20196] = cItems("GameSpot BackPack", Grey, Gear);
		items[20200] = cItems("Santa's Sack", Grey, Gear);

		//Helmts
		items[20006] = cItems("K.Style Helmet", Grey, Gear);
		items[20022] = cItems("Beret Cover", Grey, Gear);
		items[20023] = cItems("Boonie Cover", Grey, Gear);
		items[20025] = cItems("Shadow", Grey, Gear);
		items[20032] = cItems("Black Mask", Grey, Gear);
		items[20033] = cItems("Clown Mask", Grey, Gear);
		items[20034] = cItems("Jason Mask", Grey, Gear);
		items[20035] = cItems("Skull Mask", Grey, Gear);
		items[20036] = cItems("Slash Mask", Grey, Gear);
		items[20041] = cItems("Boonie Desert", Grey, Gear);
		items[20042] = cItems("Boonie Green", Grey, Gear);
		items[20043] = cItems("M9 helmet black", Grey, Gear);
		items[20046] = cItems("M9 Helmet with Goggles", Grey, Gear);
		items[20047] = cItems("M9 Helmet Green", Grey, Gear);
		items[20048] = cItems("M9 Helmet Urban", Grey, Gear);
		items[20049] = cItems("M9 Helmet Forest 1", Grey, Gear);
		items[20050] = cItems("M9 Helmet Goggles 1", Grey, Gear);
		items[20067] = cItems("NVG Goggles", Grey, Gear);
		items[20096] = cItems("Boonie Hat Leather", Grey, Gear);
		items[20097] = cItems("Fireman Helmet", Grey, Gear);
		items[20098] = cItems("Hard Hat", Grey, Gear);
		items[20177] = cItems("Gas Mask", Grey, Gear);
		items[20178] = cItems("Gas Mask 2", Grey, Gear);
		items[20187] = cItems("Night vision military", Grey, Gear);
		items[20188] = cItems("Night vision civilian", Grey, Gear);
		items[20192] = cItems("Helloween Special!", Grey, Gear);
		items[20197] = cItems("Christmas Special", Grey, Gear);
		items[20198] = cItems("Santa's Lil Helper", Grey, Gear);
		items[20199] = cItems("Captain Jack Frost", Grey, Gear);
		items[20211] = cItems("Dakotaz Hat", Grey, Gear);

		//Food And Drinks
		//Drinks 
		items[101286] = cItems("Coconut Water", White, Food);
		items[101294] = cItems("Energy drink", White, Food);
		items[101295] = cItems("Electro-AID", White, Food);
		items[101296] = cItems("Can of soda", White, Food);
		items[101297] = cItems("Juice", White, Food);
		items[101298] = cItems("Water 1L", White, Food);
		items[101299] = cItems("Water 375ml", White, Food);

		//Food
		items[101283] = cItems("Bag of Chips", White, Food);
		items[101284] = cItems("Bag MRE", White, Food);
		items[101285] = cItems("Instant Oatmeal", White, Food);
		items[101288] = cItems("Chocolate Bar", White, Food);
		items[101290] = cItems("Can of Pasta", White, Food);
		items[101291] = cItems("Can of Soup", White, Food);
		items[101292] = cItems("Can of Ham", White, Food);
		items[101293] = cItems("Can of Tuna", White, Food);
		items[101340] = cItems("MiniSaints", White, Food);
		items[101289] = cItems("Granola Bar", White, Food);

		//Throwable
		items[101340] = cItems("Chemlight White", White, Throwable);
		items[101340] = cItems("Flare", White, Throwable);
		items[101340] = cItems("Chemlight Blue", White, Throwable);
		items[101340] = cItems("Chemlight Green", White, Throwable);
		items[101340] = cItems("Chemlight Orange", White, Throwable);
		items[101340] = cItems("Chemlight Red", White, Throwable);
		items[101340] = cItems("Chemlight Yellow", White, Throwable);

		//Crafting
		items[301370] = cItems("Rope", White, Crafting);
		items[301319] = cItems("Duct Tape", White, Crafting);
		items[301357] = cItems("Charcoal", White, Crafting);
		items[301320] = cItems("Empty Bottle", Crafting, Crafting);
		items[101408] = cItems("Tool", White, Crafting);
		items[301321] = cItems("Gasoline", White, Crafting);
		items[301366] = cItems("Ointment", White, Crafting);
		items[301335] = cItems("Scissors", White, Crafting);
		items[301318] = cItems("Empty Can", White, Crafting);
		items[301319] = cItems("Duct Tape", White, Crafting);
		items[301324] = cItems("Gun Powder", White, Crafting);
		items[301320] = cItems("Empty Bottle", White, Crafting);
		items[301328] = cItems("Nails", White, Crafting);
		items[301331] = cItems("Rag", White, Crafting);
		items[301327] = cItems("Metal Scrap", White, Crafting);
		items[301355] = cItems("Broom", White, Crafting);
		items[301332] = cItems("Barbed Wire", White, Crafting);

		//Other
		//items[0xc358d] = cItems("Heart Board", White, Other);
		//items[0xc358c] = cItems("Mom Board ", White, Other);
		//items[0xc358b] = cItems("Love Board", White, Other);
		items[0x474F4C44] = cItems("Money", White, Gear);
		items[0x4C4F4F54] = cItems("Mystery Crate", Purple, Gear);
		items[1280266066] = cItems("Mystery Crate", Purple, Gear);
		//items[0xC353B] = cItems("Water Ball", White, Other);
		//items[0x65006a] = cItems("Repair Bench", White, Other);

		//other not needed
		//items[101348] = cItems("Personal Lock", White, Crafting);
	}
	if (items.count(ID) > 0)
	{
		return items[ID];
	}
	else
	{
		return cItems("_ITEM_", D3DCOLOR_ARGB(255, 255, 255, 255), Throwable);
	}
}