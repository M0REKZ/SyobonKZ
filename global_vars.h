#include <string>
#include "level_enums.hpp"
#include "DxLib.h"

#ifndef SYOBON_GLOBAL_VARS_H
#define SYOBON_GLOBAL_VARS_H

//プログラム中
//main-10
//タイトル-100

enum class ESyobonState : int
{
    IN_GAME = 1,
    CREDITS = 2,
    LIVES_SPLASH = 10,
    TITLE = 100,
};
//Open Syobon Action:
// This is unexcusable. How could someone in their right mind define
// a variable called 'main'!?
// The new define is after the main method
//
// @attention +KZ: int mainZ is now ESyobonState SyobonState
extern ESyobonState SyobonState;
// @attention +KZ: int maintm is now int SyobonStateTimer
extern int SyobonStateTimer;

//ステージ (Stage)
// @attention +KZ: int stagecolor is now LevelType StageColor
extern ELevelType StageColor;
// @attention +KZ: int sta is now int SyobonWorld
extern int SyobonWorld;
// @attention +KZ: int stb is now int SyobonLevel
extern int SyobonLevel;
// @attention +KZ: int stc is now int SyobonSection
extern int SyobonSection;

//クイック (Quick)
extern int fast;

//トラップ表示 (Trap display) //+KZ: Enabling this will show trap hit boxes in-game
extern int TrapDisplay;

//中間ゲート (Intermediate gate)
// @attention +KZ: int tyuukan is now int CurrentPlayerCheckpoint
extern int CurrentPlayerCheckpoint;


//スタッフロール
extern int ending;


//ステージ読み込みループ(いじらない) (Stage loading loop (do not modify))
//+KZ removed "int stagerr" because was unused
extern int stagepoint;
//オーバーフローさせる (Overflow)
// @attention +KZ: int over is now int SyobonRandomMode
extern int SyobonRandomMode;

//ステージスイッチ (Stage Switch)
//+KZ: ON/OFF Tile
extern int stageonoff;

//メインプログラム (Main Program)
// @attention +KZ: int maint is now int SyobonQuit
extern int SyobonQuit;

//描画 (Drawing)
extern Uint32 color;
extern Uint32 gfxcolor;

// @attention +KZ: renamed grap[][] to Sliced_GFX[][]
extern SDL_Surface *Sliced_GFX[161][8];
// @attention +KZ: renamed mgrap[][] to Main_GFX[][]
extern SDL_Surface *Main_GFX[51];

// +KZ: i added these
extern SDL_Surface *Main_GFX_KZ[2]; //+KZ
extern SDL_Surface *Sliced_GFX_KZ[2]; //+KZ

//+KZ: mirrors the image drawn by drawimage()
extern int mirror;

//+KZ increased it for Syobon Action 2 music
// @attention +KZ: Mix_Music *otom is now Mix_Music *Music
extern SyobonKZMusic *Music[7];
// @attention +KZ: Mix_Chunk *oto is now Mix_Chunk *Sounds
extern SyobonKZChunk *Sounds[19];

//1-ステージ (1-Stage)
//10-ステージ前 (10-Before Stage)
//


//初期化 (Initialization)
extern int InGameInitialized;//, zzxon; //+KZ: zzxon is unused

//キーコンフィグ (Key Configuration)
//extern int key;//, keytm; //+KZ: keytm is useless... no wait both are useless/unused

//三角関数 (Trigonometric functions)
extern double pai;


//地面 (Ground)
// @attention +KZ: smax is now GROUND_MAX
#define GROUND_MAX 31
//extern int sx; //+KZ: unused
// @attention +KZ: int sco is now GroundCount
extern int GroundCount;
// @attention +KZ: int sa[smax] is now GroundX[smax]
extern int GroundX[GROUND_MAX];
// @attention +KZ: int sb[smax] is now GroundY[smax]
extern int GroundY[GROUND_MAX];
// @attention +KZ: int sc[smax] is now GroundSizeX[smax]
extern int GroundSizeX[GROUND_MAX];
// @attention +KZ: int sd[smax] is now GroundSizeY[smax]
extern int GroundSizeY[GROUND_MAX];
// @attention +KZ: int stype[smax] is now EObjectType GroundType[smax]
extern EObjectType GroundType[GROUND_MAX];
// @attention +KZ: int sxtype[smax] is now GroundSubType[smax]
extern EObjectSubType GroundSubType[GROUND_MAX];
// @attention +KZ: int sr[smax] is now GroundVelY[smax]
extern int GroundVelY[GROUND_MAX];
// @attention +KZ: int sgtype[smax] is now GroundAI[smax]
extern int GroundAI[GROUND_MAX];

//@attention +KZ: int mainmsgtype is now int WarpZoneMessageState
extern int WarpZoneMessageState;

//プレイヤー (Player)
// mainmsgtype is not really player related, moved above (and renamed)
// @attention +KZ: int ma is now int PlayerX
extern int PlayerX;
// @attention +KZ: int mb is now int PlayerY
extern int PlayerY;
// @attention +KZ: int mnobia is now int PlayerSizeX
extern int PlayerSizeX;
// @attention +KZ: int mnobib is now int PlayerSizeY
extern int PlayerSizeY;
// Condition "Health <= 0 && Health >= -9" makes the player die
// @attention +KZ: int mhp is now int Health
extern int Health;
// @attention +KZ: int mc is now int PlayerVelX
extern int PlayerVelX;
// @attention +KZ: int md is now int PlayerVelY
extern int PlayerVelY;
//extern int macttype, atkon; //+KZ unused
extern int atktm; //+KZ: never set, but still read?
//extern int mactsok, msstar;//+KZ unused
// @attention +KZ: int mactp is now int PlayerWalkAnimTimer
extern int PlayerWalkAnimTimer;
// @attention +KZ: int mact is now int PlayerWalkAnim
extern int PlayerWalkAnim;
// @attention +KZ: int nokori is now int Lives;
extern int Lives;

// @attention +KZ: int mactp is now int PlayerState
extern int PlayerState;
// @attention +KZ: int mactp is now int PlayerSubState
extern int PlayerSubState;
// @attention +KZ: int mactp is now int PlayerAITimer
extern int PlayerAITimer;
// @attention +KZ int mzz is now int PlayerRocketPipeTrapVelY
// This variable is specific for the rocket pipe trap from 1-1
extern int PlayerRocketPipeTrapVelY;
// @attention +KZ: int mzimen is now int PlayerGrounded
extern int PlayerGrounded;
enum class EPlayerGroundType
{
    NORMAL = 0,
    SLIP = 1,
};
// @attention +KZ: int mrzimen is now EGroundType GroundType
extern EPlayerGroundType PlayerGroundType;
// @attention +KZ: int mmuki is now ELookingDirection PlayerLookingDirection
extern ELookingDirection PlayerLookingDirection;

//+KZ: following player variables were unused:
//  * mmukitm
//  * mcleartm
//the following were used but also were useless:
//  * mkasok

extern int mjumptm, mkeytm;
extern int mmutekitm, mmutekion;

//+KZ: these are never set, but are read?
extern int mztm, mztype;

extern int actaon[7];
//メッセージ (Message)
// @attention +KZ: int mmsgtm is now int PlayerMessageTimer
extern int PlayerMessageTimer;
// @attention +KZ: int mmsgtype is now int PlayerMessageType
extern int PlayerMessageType;

extern int mascrollmax;	//9000

//ブロック (Block)
// @attention +KZ: tmax is now BLOCK_MAX
#define BLOCK_MAX 641
// @attention +KZ: int tco is now int BlockCount
extern int BlockCount;
// @attention +KZ: int ta[tmax] is now int BlockX[tmax]
extern int BlockX[BLOCK_MAX];
// @attention +KZ: int tb[tmax] is now int BlockY[tmax]
extern int BlockY[BLOCK_MAX];
//extern int tc[tmax], td[tmax]; //+KZ: unused
// @attention +KZ: int thp[tmax] is now int BlockAITimer[tmax]
extern int BlockAITimer[BLOCK_MAX];
// @attention +KZ: int ttype[tmax] is now EBlockType BlockType[tmax]
extern EBlockType BlockType[BLOCK_MAX];
//+KZ: titem[tmax] is specific for Block 112/113 (Coin mass production)
// @attention +KZ: int titem[tmax] is now int BlockItemCount[tmax]
extern int BlockItemCount[BLOCK_MAX];
// @attention +KZ: int txtype[tmax] is now EBlockSubType BlockSubType[tmax]
extern EBlockSubType BlockSubType[BLOCK_MAX];

//メッセージブロック (Message Block)
extern int tmsgtm, tmsgtype, tmsgx, tmsgy, tmsgnobix, tmsgnobiy, tmsg;

//効果を持たないグラ (Grass with no effect) //+KZ: or Graphics with no effect? Google translate...
// @attention +KZ: emax is now EXTRA_GRAPHIC_MAX
#define EXTRA_GRAPHIC_MAX 201
// @attention +KZ: int eco is now int ExtraGraphicCount
extern int ExtraGraphicCount;
// @attention +KZ: int ea[emax] is now int ExtraGraphicX[emax]
extern int ExtraGraphicX[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int eb[emax] is now int ExtraGraphicY[emax]
extern int ExtraGraphicY[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int enobia[emax] is now int ExtraGraphicSizeX[emax]
extern int ExtraGraphicSizeX[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int enobib[emax] is now int ExtraGraphicSizeY[emax]
extern int ExtraGraphicSizeY[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int ec[emax] is now int ExtraGraphicVelX[emax]
extern int ExtraGraphicVelX[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int ed[emax] is now int ExtraGraphicVelY[emax]
extern int ExtraGraphicVelY[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int ee[emax] is now int ExtraGraphicFrictionX[emax] (maybe should be a different name)
extern int ExtraGraphicFrictionX[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int ef[emax] is now int ExtraGraphicFrictionY[emax] (maybe should be a different name)
extern int ExtraGraphicFrictionY[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int etm[emax] is now int ExtraGraphicTimer[emax]
extern int ExtraGraphicTimer[EXTRA_GRAPHIC_MAX];
// @attention +KZ: int egtype[emax] is now EExtraGraphicType ExtraGraphicType[emax]
extern EExtraGraphicType ExtraGraphicType[EXTRA_GRAPHIC_MAX];

//敵キャラ (Enemy character)
// @attention +KZ: amax is now ENEMY_MAX
#define ENEMY_MAX 24
// @attention +KZ: int aco[amax] is now int EnemyCount[amax]
extern int EnemyCount;
// @attention +KZ: int aa[amax] is now int EnemyX[amax]
extern int EnemyX[ENEMY_MAX];
// @attention +KZ: int ab[amax] is now int EnemyY[amax]
extern int EnemyY[ENEMY_MAX];
// @attention +KZ: int anobia[amax] is now int EnemySizeX[amax]
extern int EnemySizeX[ENEMY_MAX];
// @attention +KZ: int anobib[amax] is now int EnemySizeY[amax]
extern int EnemySizeY[ENEMY_MAX];
// @attention +KZ: int ac[amax] is now int EnemyVelX[amax]
extern int EnemyVelX[ENEMY_MAX];
// @attention +KZ: int ad[amax] is now int EnemyVelY[amax]
extern int EnemyVelY[ENEMY_MAX];
//extern int ae[amax]; //+KZ: unused, always set to 0
// @attention +KZ: int af[amax] is now int EnemyFloatingTimer[amax]
// in Syobon Action 1 & 2 it is only used in SUPER_BOON
extern int EnemyFloatingTimer[ENEMY_MAX];
// @attention +KZ: int abrocktm[amax] is now int EnemyBlockAppearTimer[amax]
extern int EnemyBlockAppearTimer[ENEMY_MAX];
// @attention +KZ: int aacta[amax] is now int EnemyActionX[amax]
// it works like a Second kind of VelX, it is set depending of the looking direction by the enemy itself
extern int EnemyActionX[ENEMY_MAX];
// @attention +KZ: int aactb[amax] is now int EnemyActionY[amax]
// unused, seems like the Y axis version of EnemyActionX
extern int EnemyActionY[ENEMY_MAX];
// @attention +KZ: int azimentype[amax] is now int EnemyMovementType[amax]
// affects enemy movement and gravity, if your enemy is floating try using "EnemyMovementType = 1"
extern int EnemyMovementType[ENEMY_MAX];
// @attention +KZ int axzimen[amax] is now int EnemyGrounded[amax]
extern int EnemyGrounded[ENEMY_MAX];
// @attention +KZ: int atype[amax] is now EEnemyType EnemyType[amax]
extern EEnemyType EnemyType[ENEMY_MAX];
// @attention +KZ: int axtype[amax] is now EEnemySubType EnemySubType[amax]
extern EEnemySubType EnemySubType[ENEMY_MAX];
// @attention +KZ: int amuki[amax] is now ELookingDirection EnemyLookingDirection[amax]
extern ELookingDirection EnemyLookingDirection[ENEMY_MAX];
//extern int ahp[amax]; //+KZ: unused
// @attention +KZ: int anotm[amax] is now EnemyPlayerNoInteractTimer[amax]
extern int EnemyPlayerNoInteractTimer[ENEMY_MAX];
// @attention +KZ: int anx[160] is now int EnemyDefaultSizeX[160]
extern int EnemyDefaultSizeX[160];
// @attention +KZ: int any[160] is now int EnemyDefaultSizeY[160]
extern int EnemyDefaultSizeY[160];
// @attention +KZ: int atm[amax] is now int EnemyAITimer[amax]
extern int EnemyAITimer[ENEMY_MAX];
//extern int a2tm[amax]; //+KZ: unused
// @attention +KZ: int amsgtm[amax] is now int EnemyMessageTimer[amax]
extern int EnemyMessageTimer[ENEMY_MAX];
// @attention +KZ: int amsgtype[amax] is now int EnemyMessageType[amax]
extern int EnemyMessageType[ENEMY_MAX];

//敵出現 (Enemy Appearance)
// @attention +KZ: bmax is now ENEMY_APPEAR_MAX
#define ENEMY_APPEAR_MAX 81
// @attention +KZ: int bco is now int EnemyAppearCount[bmax]
extern int EnemyAppearCount;
// @attention +KZ: int ba[bmax] is now int EnemyAppearX[bmax]
extern int EnemyAppearX[ENEMY_APPEAR_MAX];
// @attention +KZ: int bb[bmax] is now int EnemyAppearY[bmax]
extern int EnemyAppearY[ENEMY_APPEAR_MAX];
// @attention +KZ: int btm[bmax] is now int EnemyAppearTimer[bmax]
extern int EnemyAppearTimer[ENEMY_APPEAR_MAX];
// @attention +KZ: int btype[bmax] is now EEnemyType EnemyAppearType[bmax]
extern EEnemyType EnemyAppearType[ENEMY_APPEAR_MAX];
// @attention +KZ: int bxtype[bmax] is now EEnemySubType EnemyAppearSubType[bmax]
extern EEnemySubType EnemyAppearSubType[ENEMY_APPEAR_MAX];
// @attention +KZ: int bz[bmax] is now int EnemyAppearMustPlace[bmax]
extern int EnemyAppearMustPlace[ENEMY_APPEAR_MAX];


//背景 (Background)
// @attention +KZ: nmax is now BACKGROUND_MAX
#define BACKGROUND_MAX 41
//extern int nxxmax; //+KZ: unused
// @attention +KZ: int nco[nmax] is now int BackgroundCount
extern int BackgroundCount;
// @attention +KZ: int na[nmax] is now int BackgroundX[nmax]
extern int BackgroundX[BACKGROUND_MAX];
// @attention +KZ: int nb[nmax] is now int BackgroundY[nmax]
extern int BackgroundY[BACKGROUND_MAX];
//extern int nc[nmax], nd[nmax]; //+KZ: unused
// @attention +KZ: int ntype[nmax] is now int BackgroundType[nmax]
extern EDecorationType BackgroundType[BACKGROUND_MAX];
// @attention +KZ int ne[nmax] renamed to BackgroundWidth[nmax]
//extern int BackgroundWidth[BACKGROUND_MAX]; //+KZ: value is set but never used
// @attention +KZ int nf[nmax] renamed to BackgroundHeight[nmax]
//extern int BackgroundHeight[BACKGROUND_MAX]; //+KZ: value is set but never used
//extern int ng[nmax], nx[nmax]; //+KZ: unused


//リフト (Lift)
// @attention +KZ: srmax is now LIFT_MAX
#define LIFT_MAX 21
// @attention +KZ int srco renamed to LiftCount
extern int LiftCount;
// @attention +KZ int sra[srmax] renamed to LiftX[srmax]
extern int LiftX[LIFT_MAX];
// @attention +KZ int srb[srmax] renamed to LiftY[srmax]
extern int LiftY[LIFT_MAX];
// @attention +KZ int src[srmax] renamed to LiftSizeX[srmax]
extern int LiftSizeX[LIFT_MAX];
//extern int srd[srmax]; //+KZ: useless
// @attention +KZ int sre[srmax] renamed to LiftVelY[srmax]
extern int LiftVelY[LIFT_MAX];
// @attention +KZ int srf[srmax] renamed to LiftFrictionY[srmax]
extern int LiftFrictionY[LIFT_MAX];
extern int srtype[LIFT_MAX];
//extern int srgtype[srmax]; //+KZ: unused
extern int sracttype[LIFT_MAX];
// @attention +KZ int srsp[srmax] is now ELiftType LiftType[srmax]
// +KZ: This is confusing, there are like 3 or more variables indicating the type of the lifts,
extern ELiftType LiftType[LIFT_MAX];
extern int srmuki[LIFT_MAX], sron[LIFT_MAX], sree[LIFT_MAX];
extern int srsok[LIFT_MAX], srmovep[LIFT_MAX], srmove[LIFT_MAX];





//スクロール範囲 (Scroll range)
//+KZ: i still dont rename some of these since i dont understand the purpose of fzx
extern int fx, fy, fzx, scrollx;
extern int scrolly; //+KZ: used but never initialized!
extern int fzy; //+KZ: unused, but i may want to give it a use in the future
//全体のポイント (Overall points)

//Open Syobon Action: "fma" already exists, so call it something else and add a define
//+KZ: done
//+KZ later: the values are always 0 and never modified, so they are useless
//extern int fmaZ;
//extern int fmb;

//強制スクロール (Force Scroll)
extern int kscroll;
//画面サイズ(ファミコンサイズ×2)(256-224) (Screen size (NES size x 2) (256 x 224))
extern int fxmax, fymax;



//ステージ (Stage)
// @attention +KZ: byte stagedate[17][2001] now is ELegacyStageDate stagedate[17][2001]
extern ELegacyStageDate stagedate[17][2001];

//画面黒 (Black screen)
extern int blacktm, blackx;



//+KZ: these should be just local variables in many places
//  but we can not replace them in a crazy way, make sure
//  it wont break anything in the game.
//自由な値 (Free value)
extern int xx[91];
extern double xd[11];
extern std::string xs[31];
//ループ (Loop)
extern int t, tt, t1, t2, t3, t4;


//タイマー測定 (Timer measurement)
//Open Syobon Action: Do with this what we did with fma
extern long stimeZ;

//+KZ
#define PLUSKZ_EDITION_TEXT "+KZ Edition"
#define PLUSKZ_REMAKE_TEXT "+KZ Remake"

//misc useful defines
#define BLOCK_DEFAULT_SIZE 29
constexpr double GAME_X_POS_TO_DOUBLE(int x_axis) { return ((((double)x_axis) / 100) / BLOCK_DEFAULT_SIZE); }
constexpr double GAME_Y_POS_TO_DOUBLE(int y_axis) { return ((((double)y_axis) / 100 + 12) / BLOCK_DEFAULT_SIZE); }
constexpr int DOUBLE_TO_GAME_X_POS(double x_axis) { return ((int)(x_axis * BLOCK_DEFAULT_SIZE * 100)); }
constexpr int DOUBLE_TO_GAME_Y_POS(double y_axis) { return ((int)((y_axis * BLOCK_DEFAULT_SIZE - 12) * 100)); }

extern bool HelpFlagHandled; // --help cli flag
extern bool StartFullScreenFlag;

enum class ESyobonActionGame
{
    SYOBON_ACTION_1_AND_2 = 0,
    SYOBON_ACTION_3,

    FIRST = SYOBON_ACTION_1_AND_2,
    LAST = SYOBON_ACTION_3,
};
extern ESyobonActionGame currentGame;

#endif
