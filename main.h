#ifndef SYOBON_MAIN_H
#define SYOBON_MAIN_H

#include "DxLib.h"
#include "crossplatform.h"

#define SHORT

void loadg();
void parseArgs(int argc, char* argv[]);

//String 使用

//メインプログラム (Main Program)
void Mainprogram();
void rpaint();


//サブクラス
//(ウエイト系
//+KZ: wait() moved to crossplatform.h
void wait2(long starttime, long endtime, int FLAME_TIME);
// @attention +KZ: int rand() is now int SyobonRand()
int SyobonRand(int Rand);
#define end() exit(0)

//描画 (Drawing)
void setfont(int a);
void setcolor(int red, int green, int blue);
#define setc0() setcolor(0, 0, 0)
#define setc1() setcolor(255, 255, 255)
void drawpixel(int a, int b);
void drawline(int a, int b, int c, int d);
void drawrect(int a, int b, int c, int d);
void fillrect(int a, int b, int c, int d);
void drawarc(int a, int b, int c, int d);
void fillarc(int a, int b, int c, int d);
void FillScreen();

//+KZ: these functions are not used
//SDL_Surface *loadimage(std::string b);
//SDL_Surface *loadimage(int a, int x, int y, int r, int z);

void drawimage(SDL_Surface * mx, int a, int b);
void drawimage(SDL_Surface * mx, int a, int b, int c, int d, int e, int f);
//void setre(); //+KZ: function does not exist
//void setre2(); //+KZ: function does not exist
//void setno(); //+KZ: function does not exist

// @attention +KZ: void ot() is now void PlaySound()
void PlaySound(SyobonKZChunk * x);
void bgmchange(SyobonKZMusic * x);

//文字 (Letter)
//+KZ: Draws a std::string using DrawString()
void str(std::string c, int a, int b);


//)



//ブロック (Block)
// @attention +KZ: void tyobi() is now void BlockCreate()
void BlockCreate(int x, int y, int type);
// @attention +KZ: void brockbreak() is now void BlockBreak()
void BlockBreak(int t);

//メッセージブロック (Message Block)
void ttmsg();
void txmsg(std::string x, int a);
void setfont(int x, int y);

#endif
