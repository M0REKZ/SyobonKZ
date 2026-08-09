#ifndef SYOBONKZ_LOADG_H
#define SYOBONKZ_LOADG_H

//+KZ: Moved loaded assets variables here

#include "sdl_includer.h"

// @attention +KZ: renamed grap[][] to Sliced_GFX[][]
extern SDL_Surface *Sliced_GFX[161][8];

// @attention +KZ: renamed mgrap[][] to Main_GFX[][]
extern SDL_Surface *Main_GFX[51];

//+KZ increased it for Syobon Action 2 music
// @attention +KZ: Mix_Music *otom is now Mix_Music *Music
extern SyobonKZMusic *Music[7];

// @attention +KZ: Mix_Chunk *oto is now Mix_Chunk *Sounds
extern SyobonKZChunk *Sounds[19];

// +KZ: i added these
#define MAIN_GFX_KZ_MAX 28
#define SLICED_GFX_KZ_MAX 8
#define SOUNDS_KZ_MAX 2
extern SDL_Surface *Main_GFX_KZ[MAIN_GFX_KZ_MAX]; //+KZ
extern SDL_Surface *Sliced_GFX_KZ[SLICED_GFX_KZ_MAX]; //+KZ
extern SyobonKZChunk *Sounds_KZ[SOUNDS_KZ_MAX]; //+KZ

#endif
