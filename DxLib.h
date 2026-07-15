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

#define GetNowCount() SDL_GetTicks()

//UNIMPLEMENTED - macro substitution
#define SetFontThickness(f);
//#define ChangeVolumeSoundMem(s, v); //+KZ seems unused

//Sound
#define DX_PLAYTYPE_LOOP -1
#define DX_PLAYTYPE_BACK 0
void PlaySoundMem(SyobonKZChunk* s, int l);
void StopSoundMem(SyobonKZChunk * pchunk);
SyobonKZChunk* LoadSoundMem(const char* f);
SyobonKZMusic* LoadMusicMem(const char* f);
#define CheckSoundMem(s) (!s)

int DxLib_Init();

//Main screen
extern SDL_Surface *screen;

//Fonts
#define FONT_MAX 64
extern TTF_Font * font[FONT_MAX][2];

//Strings & fonts
#define DX_FONTTYPE_NORMAL 0
#define DX_FONTTYPE_EDGE 1
void SetFontSize(Uint8 size);
void ChangeFontType(Uint8 type);
SDL_Surface *StringToSurface(const char * pstring, Uint32 color, Uint8 font_size, Uint8 font_type); //+KZ
void DrawString(int a, int b, const char *x, Uint32 c);
void DrawFormatString(int a, int b, Uint32 color, const char *str, ...);

extern SDL_Joystick* joystick;

Uint8 ProcessMessage();
Uint8 CheckHitKey(int key);
Uint8 WaitKey();

//Uint32 GetColor(Uint8 r, Uint8 g, Uint8 b);

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

//moved here to be used in other places (main.cpp)
extern bool sound;

//+KZ custom
void SyobonKZDrawGraphScaled(int x, int y, int scale_x, int scale_y, SDL_Surface * psurface);
SyobonKZChunk * SyobonKZGetLastSoundInChannel(int channel);
void SyobonKZSetFontFile(int id);

#endif
