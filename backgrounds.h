#ifndef SYOBONKZ_BACKGROUNDS_H
#define SYOBONKZ_BACKGROUNDS_H

#include "level_enums.hpp"

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
extern EBackgroundType BackgroundType[BACKGROUND_MAX];
// @attention +KZ int ne[nmax] renamed to BackgroundWidth[nmax]
//extern int BackgroundWidth[BACKGROUND_MAX]; //+KZ: value is set but never used
// @attention +KZ int nf[nmax] renamed to BackgroundHeight[nmax]
//extern int BackgroundHeight[BACKGROUND_MAX]; //+KZ: value is set but never used
//extern int ng[nmax], nx[nmax]; //+KZ: unused

void RenderBackground();

//+KZ: Backgrounds didnt have a create function
//	this works like the new BlockCreate() and CreateEnemy() functions
int CreateBackground(double PosX, double PosY, EBackgroundType Type, int index = -1);
void ClearAllBackgrounds();

#endif
