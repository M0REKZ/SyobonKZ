//This file is a reverse engineered "DxLib.h" to the extent that
//Syobon Action uses it. Minor functions are just replaced with SDL
//counterparts.
#ifndef SYOBON_DXLIB_H
#define SYOBON_DXLIB_H

#include "sdl_includer.h"
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <locale.h>

#include "joyconfig.h"

#define TRUE 1
#define FALSE 0
#define byte unsigned char

#define GetNowCount() SDL_GetTicks()

//UNIMPLEMENTED - macro substitution
#define SetFontThickness(f);
#define StopSoundMem(s);
//#define ChangeVolumeSoundMem(s, v); //+KZ seems unused

//Sound
#define DX_PLAYTYPE_LOOP -1
#define DX_PLAYTYPE_BACK 0
void PlaySoundMem(SyobonKZChunk* s, int l);
SyobonKZChunk* LoadSoundMem(const char* f);
SyobonKZMusic* LoadMusicMem(const char* f);
#define CheckSoundMem(s) (!s)

int DxLib_Init();

//Main screen
extern SDL_Surface *screen;

//Fonts
#define FONT_MAX 64
extern TTF_Font *font[FONT_MAX];

//Strings & fonts
#define DX_FONTTYPE_NORMAL 0
#define DX_FONTTYPE_EDGE 1
void SetFontSize(byte size);
void ChangeFontType(byte type);
SDL_Surface *StringToSurface(const char * pstring, Uint32 color, byte font_size, byte font_type); //+KZ
void DrawString(int a, int b, const char *x, Uint32 c);
void DrawFormatString(int a, int b, Uint32 color, const char *str, ...);

extern SDL_Joystick* joystick;

byte ProcessMessage();
byte CheckHitKey(int key);
byte WaitKey();

//Uint32 GetColor(byte r, byte g, byte b);

#define DrawGraph(a, b, mx, z) DrawGraphZ(a, b, mx)
void DrawGraphZ(int a, int b, SDL_Surface * mx);

#define DrawTurnGraph(a, b, mx, z) DrawTurnGraphZ(a, b, mx)
void DrawTurnGraphZ(int a, int b, SDL_Surface * mx);

//#define DrawVertTurnGraph(x, y, e, a, mx, z) DrawRotaGraphZ(x, y, a, mx)
void DrawVertTurnGraph(int a, int b, SDL_Surface * mx);

SDL_Surface *DerivationGraph(int srcx, int srcy, int width, int height,
			     SDL_Surface * src);

//Noticably different than the original
SDL_Surface *LoadGraph(const char *filename, bool fix = true);

void SetKeyState(Uint32 key, bool state);
bool GetKeyState(Uint32 key);

extern bool DxLibExit;

#endif
