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
extern int maintm;

//ステージ (Stage)
extern int stagecolor;
extern int sta, stb, stc;

//クイック (Quick)
extern int fast;

//トラップ表示
extern int trap;

//中間ゲート
extern int tyuukan;


//スタッフロール
extern int ending;


//ステージ読み込みループ(いじらない)
extern int stagerr, stagepoint;
//オーバーフローさせる
extern int over;

//ステージスイッチ
extern int stageonoff;

//メインプログラム
extern int maint;

//描画
extern Uint32 color;
extern Uint32 gfxcolor;

extern SDL_Surface *grap[161][8];
extern SDL_Surface *mgrap[51];
extern SDL_Surface *Main_GFX_KZ[1]; //+KZ
extern SDL_Surface *Sliced_GFX_KZ[2]; //+KZ

extern int mirror;

extern Mix_Music *otom[7]; //+KZ increased for Syobon Action 2 music
extern Mix_Chunk *oto[19];

//1-ステージ
//10-ステージ前
//

//ループ
extern int t, tt, t1, t2, t3, t4;


//初期化
extern int zxon, zzxon;

//キーコンフィグ
extern int key, keytm;

//三角関数
extern double pai;


//地面
#define smax 31
extern int sx, sco;
extern int sa[smax], sb[smax], sc[smax], sd[smax], stype[smax], sxtype[smax], sr[smax];
extern int sgtype[smax];



//プレイヤー
extern int mainmsgtype;
extern int ma, mb, mnobia, mnobib, mhp;
extern int mc, md, macttype, atkon, atktm, mactsok, msstar, nokori, mactp, mact;

extern int mtype, mxtype, mtm, mzz;
extern int mzimen, mrzimen, mkasok, mmuki, mmukitm, mjumptm, mkeytm, mcleartm;
extern int mmutekitm, mmutekion;
extern int mztm, mztype;
extern int actaon[7];
//メッセージ
extern int mmsgtm, mmsgtype;

extern int mascrollmax;	//9000

//ブロック
#define tmax 641
extern int tco;
extern int ta[tmax], tb[tmax], tc[tmax], td[tmax], thp[tmax], ttype[tmax];
extern int titem[tmax], txtype[tmax];

//メッセージブロック
extern int tmsgtm, tmsgtype, tmsgx, tmsgy, tmsgnobix, tmsgnobiy, tmsg;

//効果を持たないグラ
#define emax 201
extern int eco;
extern int ea[emax], eb[emax], enobia[emax], enobib[emax], ec[emax], ed[emax];
extern int ee[emax], ef[emax], etm[emax];
extern int egtype[emax];

//敵キャラ
#define amax 24
extern int aco;
extern int aa[amax], ab[amax], anobia[amax], anobib[amax], ac[amax], ad[amax];
extern int ae[amax], af[amax], abrocktm[amax];
extern int aacta[amax], aactb[amax], azimentype[amax], axzimen[amax];
extern int atype[amax], axtype[amax], amuki[amax], ahp[amax];
extern int anotm[amax], anx[160], any[160];
extern int atm[amax], a2tm[amax];
extern int amsgtm[amax], amsgtype[amax];

//敵出現
#define bmax 81
extern int bco;
extern int ba[bmax], bb[bmax], btm[bmax];
extern int btype[bmax], bxtype[bmax], bz[bmax];


//背景
#define nmax 41
extern int nxxmax, nco;
extern int na[nmax], nb[nmax], nc[nmax], nd[nmax], ntype[nmax];
extern int ne[nmax], nf[nmax], ng[nmax], nx[nmax];


//リフト
#define srmax 21
extern int srco;
extern int sra[srmax], srb[srmax], src[srmax], srd[srmax], sre[srmax], srf[srmax];
extern int srtype[srmax], srgtype[srmax], sracttype[srmax], srsp[srmax];
extern int srmuki[srmax], sron[srmax], sree[srmax];
extern int srsok[srmax], srmovep[srmax], srmove[srmax];





//スクロール範囲
extern int fx, fy, fzx, fzy, scrollx, scrolly;
//全体のポイント

//Open Syobon Action: "fma" already exists, so call it something else and add a define
//+KZ: done
extern int fmaZ;
extern int fmb;

//強制スクロール
extern int kscroll;
//画面サイズ(ファミコンサイズ×2)(256-224)
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
