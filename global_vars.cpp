
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
SDL_Surface *Main_GFX_KZ[1]; //+KZ
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
int GroundX[smax], GroundY[smax], GroundSizeX[smax], GroundSizeY[smax];
EObjectType GroundType[smax];
int GroundSubType[smax],
    GroundVelY[smax];
int GroundAI[smax];



//プレイヤー
int mainmsgtype;
int PlayerX, PlayerY, PlayerSizeX, PlayerSizeY, Health;
int PlayerVelX, PlayerVelY, atktm, PlayerWalkAnimTimer, PlayerWalkAnim;
int Lives = 3;

int PlayerState, PlayerSubState, PlayerAITimer, mzz;
int PlayerGrounded, PlayerLookingDirection, mjumptm, mkeytm;
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
int BlockX[tmax], BlockY[tmax], thp[tmax];
EBlockType BlockType[tmax];
int BlockItemCount[tmax], BlockSubType[tmax];

//メッセージブロック
int tmsgtm, tmsgtype, tmsgx, tmsgy, tmsgnobix, tmsgnobiy, tmsg;

//効果を持たないグラ
int ExtraGraphicCount;
int ExtraGraphicX[emax], ExtraGraphicY[emax], ExtraGraphicSizeX[emax], ExtraGraphicSizeY[emax], ExtraGraphicVelX[emax], ExtraGraphicVelY[emax];
int ExtraGraphicFrictionX[emax], ExtraGraphicFrictionY[emax], ExtraGraphicTimer[emax];
int ExtraGraphicType[emax];



//敵キャラ
int EnemyCount;
int EnemyX[amax], EnemyY[amax], EnemySizeX[amax], EnemySizeY[amax], EnemyVelX[amax], EnemyVelY[amax];
int af[amax], EnemyBlockAppearTimer[amax];
int aacta[amax], aactb[amax], azimentype[amax], axzimen[amax];
EEnemyType EnemyType[amax];
EEnemySubType EnemySubType[amax];
int EnemyLookingDirection[amax];
int anotm[amax], EnemyDefaultSizeX[160], EnemyDefaultSizeY[160];
int EnemyAITimer[amax];
int EnemyMessageTimer[amax], EnemyMessageType[amax];

//敵出現
int EnemyAppearCount;
int EnemyAppearX[bmax], EnemyAppearY[bmax], EnemyAppearTimer[bmax];
EEnemyType EnemyAppearType[bmax];
EEnemySubType EnemyAppearSubType[bmax];
int bz[bmax];


//背景
int BackgroundCount;
int BackgroundX[nmax], BackgroundY[nmax];
EDecorationType BackgroundType[nmax];
int BackgroundWidth[nmax], BackgroundHeight[nmax];


//リフト
int LiftCount;
int LiftX[srmax], LiftY[srmax], LiftSizeX[srmax], LiftVelY[srmax], LiftFrictionY[srmax];
int srtype[srmax], sracttype[srmax];
ELiftType LiftType[srmax];
int srmuki[srmax], sron[srmax], sree[srmax];
int srsok[srmax], srmovep[srmax], srmove[srmax];





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
byte stagedate[17][2001];

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
