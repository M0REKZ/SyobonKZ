
//Variables used in Syobon Action game:

#include "global_vars.h"

//String 使用

//プログラム中
//main-10
//タイトル-100

//: This is unexcusable. How could someone in their right mind define
//: a variable called 'main'!?
//: The new define is after the main method
int mainZ = 100, maintm = 0;

//ステージ
int stagecolor = 1;
int sta = 1, stb = 4, stc = 0;

//クイック
int fast = 1;

//トラップ表示
int trap = 1;

//中間ゲート
int tyuukan = 0;


//スタッフロール
int ending = 0;


//ステージ読み込みループ(いじらない)
int stagerr, stagepoint;
//オーバーフローさせる
int over = 0;

//ステージスイッチ
int stageonoff = 0;


//メインプログラム
int maint;

//描画
Uint32 color;
Uint32 gfxcolor;

SDL_Surface *grap[161][8];
SDL_Surface *mgrap[51];
SDL_Surface *Main_GFX_KZ[1]; //+KZ
SDL_Surface *Sliced_GFX_KZ[2]; //+KZ

int mirror;

Mix_Music *otom[7]; //+KZ increased for Syobon Action 2 music
Mix_Chunk *oto[19];





//1-ステージ
//10-ステージ前
//



//ループ
int t, tt, t1, t2, t3, t4;


//初期化
int zxon, zzxon;

//キーコンフィグ
int key, keytm;

//三角関数
double pai = 3.1415926535;


//地面
int sx, sco;
int sa[smax], sb[smax], sc[smax], sd[smax], stype[smax], sxtype[smax],
    sr[smax];
int sgtype[smax];



//プレイヤー
int mainmsgtype;
int ma, mb, mnobia, mnobib, mhp;
int mc, md, macttype, atkon, atktm, mactsok, msstar, nokori =
    3, mactp, mact;

int mtype, mxtype, mtm, mzz;
int mzimen, mrzimen, mkasok, mmuki, mmukitm, mjumptm, mkeytm, mcleartm;
int mmutekitm, mmutekion;
int mztm, mztype;
int actaon[7];
//メッセージ
int mmsgtm, mmsgtype;

int mascrollmax = 21000;	//9000




//ブロック
int tco;
int ta[tmax], tb[tmax], tc[tmax], td[tmax], thp[tmax], ttype[tmax];
int titem[tmax], txtype[tmax];

//メッセージブロック
int tmsgtm, tmsgtype, tmsgx, tmsgy, tmsgnobix, tmsgnobiy, tmsg;

//効果を持たないグラ
int eco;
int ea[emax], eb[emax], enobia[emax], enobib[emax], ec[emax], ed[emax];
int ee[emax], ef[emax], etm[emax];
int egtype[emax];



//敵キャラ
int aco;
int aa[amax], ab[amax], anobia[amax], anobib[amax], ac[amax], ad[amax];
int ae[amax], af[amax], abrocktm[amax];
int aacta[amax], aactb[amax], azimentype[amax], axzimen[amax];
int atype[amax], axtype[amax], amuki[amax], ahp[amax];
int anotm[amax], anx[160], any[160];
int atm[amax], a2tm[amax];
int amsgtm[amax], amsgtype[amax];

//敵出現
int bco;
int ba[bmax], bb[bmax], btm[bmax];
int btype[bmax], bxtype[bmax], bz[bmax];


//背景
int nxxmax, nco;
int na[nmax], nb[nmax], nc[nmax], nd[nmax], ntype[nmax];
int ne[nmax], nf[nmax], ng[nmax], nx[nmax];


//リフト
int srco;
int sra[srmax], srb[srmax], src[srmax], srd[srmax], sre[srmax], srf[srmax];
int srtype[srmax], srgtype[srmax], sracttype[srmax], srsp[srmax];
int srmuki[srmax], sron[srmax], sree[srmax];
int srsok[srmax], srmovep[srmax], srmove[srmax];





//スクロール範囲
int fx = 0, fy = 0, fzx, fzy, scrollx, scrolly;
//全体のポイント

//: "fma" already exists, so call it something else and add a define
int fmaZ = 0, fmb = 0;

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
ESyobonActionGame currentGame = SYOBON_ACTION_3;


//Syobon Action 3
bool SA3_Level1MushroomTriggered = false;
int SA3_Level1MushroomTimer = 0;
