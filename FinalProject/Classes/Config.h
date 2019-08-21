#pragma once

#define WINDOWS_W 720

#define WINDOWS_H 1280

#define WINDOWS_NAME "Jumpy Bird!"

enum {
	zBackground = 0,
	zGameBoard,
	zUI,
};

// Save
static const char *USED_ITEM = "USED_ITEM";
static const char *USED_SLING_SHOT = "USED_SLING_SHOT";
static const char *YOUR_SLING_SHOT_1 = "YOUR_SLING_SHOT_1";
static const char *YOUR_SLING_SHOT_2 = "YOUR_SLING_SHOT_2";
static const char *YOUR_SLING_SHOT_3 = "YOUR_SLING_SHOT_3";
static const char *YOUR_SLING_SHOT_4 = "YOUR_SLING_SHOT_4";
static const char *YOUR_ITEMS_1 = "YOUR_ITEMS_1";
static const char *YOUR_ITEMS_2 = "YOUR_ITEMS_2";
static const char *YOUR_ITEMS_3 = "YOUR_ITEMS_3";
static const char *YOUR_ITEMS_4 = "YOUR_ITEMS_4";
static const char *TIME = "TIME";
static const char *NUM_DEAD = "NUM_DEAD";
static const char *CORN_SCORE = "CORN_SCORE";
static const char *HIGH_SCORE = "High_score";
static const char *CHECK_POINT_X = "CHECK_POINT_X";
static const char *CHECK_POINT_Y = "CHECK_POINT_Y";
static const char *POSITION_PLAYER_X = "POSITION_PLAYER_X";
static const char *POSITION_PLAYER_Y = "POSITION_PLAYER_Y";
static const char *IS_LOAD_GAME = "IS_LOAD_GAME";

#define PTM_RATIO 32.0f

#define MAX_DOT 10

#define MaxJump 4

#define FPS_Trajectory 5.0f

#define CON_SO_KY_LA 8.9f

#define CHEAT_CODE "rlrrrllrlr"

#define Friction_Collision 1.0f

#define Restitution_Collision 0.4f

#define Density_Collision 1.0f

#define Friction_Ice 0.35f

#define Restitution_Ice 0.4f

#define Density_Ice 1.0f

#define MaxVectorDistance 350.0f * (540 / 720.0f)

#define PowerMultiplier 6.5f * (540 / 720.0f)

#define TimeFixMovementBug 0.01

#define MinVelocityDoAutoFixBug 1.0f

#define HeightStartWind 4067

#define HeightEndWind 6723

#define HeightStartIce 6963

#define HeightEndIce 9587

#define HeightStartCastle 9792

#define HeightEndCastle 13265

#define GameItems 4

#define SlingShots 4

#define ScaleFactor 1.3

#define HandSensorSimulateBody 20

#define FootSensorSimulateBody 30

#define TurtorialNum 6

#define Plot1 11

#define Plot2 5

#define EndLayerImages 5

enum TypeEnemy
{
	ENEMY_1 = 1,
	ENEMY_2,
	ENEMY_3,
	ENEMY_4,
	ENEMY_5
};

enum TypeItem
{
	ARMOR = 1,
	ARMOR_BOOTS,
	BEANIE,
	THORNMAIL,
	WIND_COLAK,
	NORMAL_SLINGSHOT,
	TIME_SLINGSHOT,
	FIRE_SLINGSHOT,
	DIAMOND_SLINGSHOT
};

#define MoveActionCustom 0.01f

#define Const_Velocity 0.8f

#define NumWind 10

enum IdTypeObject
{
	IdCheckPoint,
	IdTayPlayer,
	IdChanPlayer,
	IdGold,
	IdTreasureChest,
	IdEnemy,
	IdBodyPlayer,
	IdDauPlayer,
	IdBoss,
	IdMovingPlatfrom,
	IdStone,
	IdButtonElevator,
	IdJail
};

#define NumStone 100 // so luong stone trong objectpool

#define MovePositionPlayerWithTranform true

// Enable debug
#define isEnableDebug false

#define isEnableDebugSimulation false

#define NumOfWind 100

#define DelayTimeUpdateWind 0.3f

#define NumOfWindInOneTime 5

enum TypeTreasureChest
{
	CHEST_1 = 1,
	CHEST_2,
	CHEST_3
};

#define Path_TMX_MAP "TiledMap1.tmx"

#define TimeEffectLand 0.5f