#ifndef SYOBON_MAIN_H
#define SYOBON_MAIN_H

#include "DxLib.h"
#include "crossplatform.h"

#define SHORT

void loadg();
void parseArgs(int argc, char* argv[]);

//String 使用

//メインプログラム
void Mainprogram();
void rpaint();


//サブクラス
//(ウエイト系
//+KZ: wait() moved to crossplatform.h
void wait2(long stime, long etime, int FLAME_TIME);
int rand(int Rand);
#define end() exit(0)

//描画
void setfont(int a);
void setcolor(int red, int green, int blue);
void setc0();
void setc1();
void drawpixel(int a, int b);
void drawline(int a, int b, int c, int d);
void drawrect(int a, int b, int c, int d);
void fillrect(int a, int b, int c, int d);
void drawarc(int a, int b, int c, int d);
void fillarc(int a, int b, int c, int d);
void FillScreen();
SDL_Surface *loadimage(std::string b);
SDL_Surface *loadimage(int a, int x, int y, int r, int z);
void drawimage(SDL_Surface * mx, int a, int b);
void drawimage(SDL_Surface * mx, int a, int b, int c, int d, int e, int f);
void setre();
void setre2();
void setno();
void ot(Mix_Chunk * x);
void bgmchange(Mix_Music * x);

//文字
void str(std::string c, int a, int b);


//)

void stagecls();
void stage();
void stagep();



//ブロック
void tyobi(int x, int y, int type);
void brockbreak(int t);

//メッセージブロック
void ttmsg();
void txmsg(std::string x, int a);
void setfont(int x, int y);

//効果を持たないグラ
void eyobi(int xa, int xb, int xc, int xd, int xe, int xf, int xnobia,
	   int xnobib, int xgtype, int xtm);

//敵キャラ
void ayobi(int xa, int xb, int xc, int xd, int xnotm, int xtype,
	   int xxtype);
// @attention +KZ: void tekizimen() is now void HandleTiles()
void HandleTiles();

#endif
