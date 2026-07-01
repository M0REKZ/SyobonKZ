
//Variables used in Syobon Action game:

#include "global_vars.h"

//String 使用

//プログラム中
//main-10
//タイトル-100

//: This is unexcusable. How could someone in their right mind define
//: a variable called 'main'!?
//: The new define is after the main method
ESyobonState SyobonState = ESyobonState::TITLE;
int SyobonStateTimer = 0;

//ステージ
ELevelType StageColor = ELevelType::OVERWORLD;
int SyobonWorld;
int SyobonLevel;
int SyobonSection;

//クイック
int fast = 1;

//トラップ表示
int TrapDisplay = 1;

//中間ゲート
int CurrentPlayerCheckpoint = 0;


//スタッフロール
int ending = 0;


//ステージ読み込みループ(いじらない) (Stage loading loop (do not modify))
//+KZ removed "int stagerr" because was unused
int stagepoint;
//オーバーフローさせる
int SyobonRandomMode = 0;

//ステージスイッチ
int stageonoff = 0;


//メインプログラム
int SyobonQuit;

//描画
Uint32 color;
Uint32 gfxcolor;

SDL_Surface *Sliced_GFX[161][8];
SDL_Surface *Main_GFX[51];

// +KZ: i added these
SDL_Surface *Main_GFX_KZ[2]; //+KZ
SDL_Surface *Sliced_GFX_KZ[2]; //+KZ

int mirror;

SyobonKZMusic *Music[7]; //+KZ increased for Syobon Action 2 music
SyobonKZChunk *Sounds[19];





//1-ステージ
//10-ステージ前
//



//ループ
int t, tt, t1, t2, t3, t4;


//初期化
int zxon;//, zzxon; //+KZ: zzxon is unused

//キーコンフィグ
int key;//, keytm; //+KZ: keytm is useless

//三角関数
double pai = 3.1415926535;


//地面
int GroundCount;
int GroundX[GROUND_MAX], GroundY[GROUND_MAX], GroundSizeX[GROUND_MAX], GroundSizeY[GROUND_MAX];
EObjectType GroundType[GROUND_MAX];
EObjectSubType GroundSubType[GROUND_MAX];
int GroundVelY[GROUND_MAX];
int GroundAI[GROUND_MAX];



//プレイヤー
int mainmsgtype;
int PlayerX, PlayerY, PlayerSizeX, PlayerSizeY, Health;
int PlayerVelX, PlayerVelY, atktm, PlayerWalkAnimTimer, PlayerWalkAnim;
int Lives = 3;

int PlayerState, PlayerSubState, PlayerAITimer, mzz;
int PlayerGrounded;
ELookingDirection PlayerLookingDirection;
int mjumptm, mkeytm;
EPlayerGroundType PlayerGroundType;
int mmutekitm, mmutekion;
//+KZ: these are never set, but are read?
int mztm, mztype;

int actaon[7];
//メッセージ
int PlayerMessageTimer, PlayerMessageType;

int mascrollmax = 21000;	//9000




//ブロック
int BlockCount;
int BlockX[BLOCK_MAX], BlockY[BLOCK_MAX], BlockAITimer[BLOCK_MAX];
EBlockType BlockType[BLOCK_MAX];
int BlockItemCount[BLOCK_MAX];
EBlockSubType BlockSubType[BLOCK_MAX];

//メッセージブロック
int tmsgtm, tmsgtype, tmsgx, tmsgy, tmsgnobix, tmsgnobiy, tmsg;

//効果を持たないグラ
int ExtraGraphicCount;
int ExtraGraphicX[EXTRA_GRAPHIC_MAX], ExtraGraphicY[EXTRA_GRAPHIC_MAX], ExtraGraphicSizeX[EXTRA_GRAPHIC_MAX], ExtraGraphicSizeY[EXTRA_GRAPHIC_MAX], ExtraGraphicVelX[EXTRA_GRAPHIC_MAX], ExtraGraphicVelY[EXTRA_GRAPHIC_MAX];
int ExtraGraphicFrictionX[EXTRA_GRAPHIC_MAX], ExtraGraphicFrictionY[EXTRA_GRAPHIC_MAX], ExtraGraphicTimer[EXTRA_GRAPHIC_MAX];
EExtraGraphicType ExtraGraphicType[EXTRA_GRAPHIC_MAX];



//敵キャラ
int EnemyCount;
int EnemyX[ENEMY_MAX], EnemyY[ENEMY_MAX], EnemySizeX[ENEMY_MAX], EnemySizeY[ENEMY_MAX], EnemyVelX[ENEMY_MAX], EnemyVelY[ENEMY_MAX];
int af[ENEMY_MAX], EnemyBlockAppearTimer[ENEMY_MAX];
int aacta[ENEMY_MAX], aactb[ENEMY_MAX], azimentype[ENEMY_MAX], axzimen[ENEMY_MAX];
EEnemyType EnemyType[ENEMY_MAX];
EEnemySubType EnemySubType[ENEMY_MAX];
ELookingDirection EnemyLookingDirection[ENEMY_MAX];
int EnemyPlayerNoInteractTimer[ENEMY_MAX], EnemyDefaultSizeX[160], EnemyDefaultSizeY[160];
int EnemyAITimer[ENEMY_MAX];
int EnemyMessageTimer[ENEMY_MAX], EnemyMessageType[ENEMY_MAX];

//敵出現
int EnemyAppearCount;
int EnemyAppearX[ENEMY_APPEAR_MAX], EnemyAppearY[ENEMY_APPEAR_MAX], EnemyAppearTimer[ENEMY_APPEAR_MAX];
EEnemyType EnemyAppearType[ENEMY_APPEAR_MAX];
EEnemySubType EnemyAppearSubType[ENEMY_APPEAR_MAX];
int bz[ENEMY_APPEAR_MAX];


//背景
int BackgroundCount;
int BackgroundX[BACKGROUND_MAX], BackgroundY[BACKGROUND_MAX];
EDecorationType BackgroundType[BACKGROUND_MAX];
//+KZ: value is set but never used
//int BackgroundWidth[BACKGROUND_MAX], BackgroundHeight[BACKGROUND_MAX];


//リフト
int LiftCount;
int LiftX[LIFT_MAX], LiftY[LIFT_MAX], LiftSizeX[LIFT_MAX], LiftVelY[LIFT_MAX], LiftFrictionY[LIFT_MAX];
int srtype[LIFT_MAX], sracttype[LIFT_MAX];
ELiftType LiftType[LIFT_MAX];
int srmuki[LIFT_MAX], sron[LIFT_MAX], sree[LIFT_MAX];
int srsok[LIFT_MAX], srmovep[LIFT_MAX], srmove[LIFT_MAX];





//スクロール範囲
int fx = 0, fy = 0, fzx, fzy, scrollx, scrolly;
//全体のポイント

//: "fma" already exists, so call it something else and add a define
//int fmaZ = 0, fmb = 0;

//強制スクロール
int kscroll = 0;
//画面サイズ(ファミコンサイズ×2)(256-224)
int fxmax = 48000, fymax = 42000;



//ステージ
ELegacyStageDate stagedate[17][2001];

//画面黒
int blacktm = 1, blackx = 0;



//自由な値
int xx[91];
double xd[11];
std::string xs[31];


//タイマー測定
//: Do with this what we did with fma
long stimeZ;

//+KZ
ESyobonActionGame currentGame = ESyobonActionGame::SYOBON_ACTION_1_AND_2;
bool HelpFlagHandled = false;
bool StartFullScreenFlag = false;

//Syobon Action 3
bool SA3_Level1MushroomTriggered = false;
int SA3_Level1MushroomTimer = 0;
