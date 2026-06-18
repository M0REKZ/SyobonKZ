#include <SDL_stdinc.h>
#include <SDL_video.h>
#include <SDL_mixer.h>
#include <string>
#include "DxLib.h"

#ifndef SYOBON_GLOBAL_VARS_H
#define SYOBON_GLOBAL_VARS_H

//プログラム中
//main-10
//タイトル-100

enum class ESyobonState
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
extern int stagecolor;
// @attention +KZ: int sta is now int SyobonWorld
extern int SyobonWorld;
// @attention +KZ: int stb is now int SyobonLevel
extern int SyobonLevel;
// @attention +KZ: int stc is now int SyobonSection
extern int SyobonSection;

//クイック (Quick)
extern int fast;

//トラップ表示 (Trap display) //+KZ: ??
extern int trap;

//中間ゲート (Intermediate gate) //+KZ: ??
extern int tyuukan;


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
extern SDL_Surface *Main_GFX_KZ[1]; //+KZ
extern SDL_Surface *Sliced_GFX_KZ[2]; //+KZ

//+KZ: mirrors the image drawn by drawimage()
extern int mirror;

//+KZ increased it for Syobon Action 2 music
// @attention +KZ: Mix_Music *otom is now Mix_Music *Music
extern Mix_Music *Music[7];
// @attention +KZ: Mix_Chunk *oto is now Mix_Chunk *Sounds
extern Mix_Chunk *Sounds[19];

//1-ステージ (1-Stage)
//10-ステージ前 (10-Before Stage)
//

//ループ (Loop)
//+KZ: these should be local variables in many places inside main.cpp
extern int t, tt, t1, t2, t3, t4;


//初期化 (Initialization)
extern int zxon;//, zzxon; //+KZ: zzxon is unused

//キーコンフィグ (Key Configuration)
extern int key;//, keytm; //+KZ: keytm is useless

//三角関数 (Trigonometric functions)
extern double pai;


//地面 (Ground)
#define smax 31
extern int sx, sco;
extern int sa[smax], sb[smax], sc[smax], sd[smax], stype[smax], sxtype[smax], sr[smax];
extern int sgtype[smax];



//プレイヤー (Player)
extern int mainmsgtype;
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
extern int mc, md, macttype, atkon, atktm, mactsok, msstar, mactp, mact;
// @attention +KZ: int nokori is now int Lives;
extern int Lives;

extern int mtype, mxtype, mtm, mzz;
// @attention +KZ: int mzimen is now int PlayerGrounded
extern int PlayerGrounded;
enum class EGroundType
{
    NORMAL = 0,
    SLIP = 1,
};
// @attention +KZ: int mrzimen is now EGroundType GroundType
extern EGroundType GroundType;
// @attention +KZ: int mmuki is now int PlayerLookingDirection
extern int PlayerLookingDirection;

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
#define tmax 641
extern int tco;
// @attention +KZ: int ta[tmax] is now int BlockX[tmax]
extern int BlockX[tmax];
// @attention +KZ: int tb[tmax] is now int BlockY[tmax]
extern int BlockY[tmax];
extern int tc[tmax], td[tmax], thp[tmax], ttype[tmax];
extern int titem[tmax], txtype[tmax];

//メッセージブロック (Message Block)
extern int tmsgtm, tmsgtype, tmsgx, tmsgy, tmsgnobix, tmsgnobiy, tmsg;

//効果を持たないグラ (Grass with no effect)
#define emax 201
extern int eco;
extern int ea[emax], eb[emax], enobia[emax], enobib[emax], ec[emax], ed[emax];
extern int ee[emax], ef[emax], etm[emax];
extern int egtype[emax];

//敵キャラ (Enemy character)
#define amax 24
// @attention +KZ: int aco[amax] is now int EnemyCount[amax]
extern int EnemyCount;
// @attention +KZ: int aa[amax] is now int EnemyX[amax]
extern int EnemyX[amax];
// @attention +KZ: int ab[amax] is now int EnemyY[amax]
extern int EnemyY[amax];
// @attention +KZ: int anobia[amax] is now int EnemySizeX[amax]
extern int EnemySizeX[amax];
// @attention +KZ: int anobib[amax] is now int EnemySizeY[amax]
extern int EnemySizeY[amax];
extern int ac[amax], ad[amax];
extern int ae[amax], af[amax], abrocktm[amax];
extern int aacta[amax], aactb[amax], azimentype[amax], axzimen[amax];
// @attention +KZ: int atype[amax] is now int EnemyType[amax]
extern int EnemyType[amax];
// @attention +KZ: int axtype[amax] is now int EnemySubType[amax]
extern int EnemySubType[amax];
extern int amuki[amax], ahp[amax];
extern int anotm[amax], anx[160], any[160];
extern int atm[amax], a2tm[amax];
extern int amsgtm[amax], amsgtype[amax];

//敵出現 (Enemy Appearance)
#define bmax 81
//+KZ: does "bco" count appearing enemies?
extern int bco;
// @attention +KZ: int ba[bmax] is now int EnemyAppearX[bmax]
extern int EnemyAppearX[bmax];
// @attention +KZ: int bb[bmax] is now int EnemyAppearY[bmax]
extern int EnemyAppearY[bmax];
// @attention +KZ: int btm[bmax] is now int EnemyAppearTimer[bmax]
extern int EnemyAppearTimer[bmax];
// @attention +KZ: int btype[bmax] is now int EnemyAppearType[bmax]
extern int EnemyAppearType[bmax];
// @attention +KZ: int bxtype[bmax] is now int EnemyAppearSubType[bmax]
extern int EnemyAppearSubType[bmax];
extern int bz[bmax];


//背景 (Background)
#define nmax 41
extern int nxxmax, nco;
extern int na[nmax], nb[nmax], nc[nmax], nd[nmax], ntype[nmax];
// @attention +KZ int ne[nmax] renamed to BackgroundWidth[nmax]
// @attention +KZ int nf[nmax] renamed to BackgroundHeight[nmax]
extern int BackgroundWidth[nmax], BackgroundHeight[nmax];
extern int ng[nmax], nx[nmax];


//リフト (Lift)
#define srmax 21
extern int srco;
extern int sra[srmax], srb[srmax], src[srmax], srd[srmax], sre[srmax], srf[srmax];
extern int srtype[srmax], srgtype[srmax], sracttype[srmax], srsp[srmax];
extern int srmuki[srmax], sron[srmax], sree[srmax];
extern int srsok[srmax], srmovep[srmax], srmove[srmax];





//スクロール範囲 (Scroll range)
extern int fx, fy, fzx, fzy, scrollx, scrolly;
//全体のポイント (Overall points)

//Open Syobon Action: "fma" already exists, so call it something else and add a define
//+KZ: done
extern int fmaZ;
extern int fmb;

//強制スクロール (Force Scroll)
extern int kscroll;
//画面サイズ(ファミコンサイズ×2)(256-224) (Screen size (NES size x 2) (256 x 224))
extern int fxmax, fymax;



//ステージ
extern byte stagedate[17][2001];

//画面黒
extern int blacktm, blackx;



//自由な値 (Free value)
//+KZ: these should be local variables in many places inside main.cpp
extern int xx[91];
extern double xd[11];
extern std::string xs[31];


//タイマー測定 (Timer measurement)
//Open Syobon Action: Do with this what we did with fma
extern long stimeZ;
#define stime stimeZ

//+KZ
#define PLUSKZ_EDITION_TEXT "+KZ Edition"
enum ESyobonActionGame
{
    SYOBON_ACTION_1 = 0,
    SYOBON_ACTION_2 = 1,
    SYOBON_ACTION_3 = 2, // Extremely incomplete, dont allow to choose
};
extern ESyobonActionGame currentGame;
extern bool SA3_Level1MushroomTriggered;
extern int SA3_Level1MushroomTimer;

#endif
