#ifndef SYOBON_EFFECTS_H
#define SYOBON_EFFECTS_H

#include "level_enums.hpp"

//効果を持たないグラ (Grass with no effect)
//+KZ: or Graphics with no effect? Google translate...
// or actually effect graphics
// @attention +KZ: emax is now EFFECT_MAX
#define EFFECT_MAX 201
// @attention +KZ: int eco is now int EffectCount
extern int EffectCount;
// @attention +KZ: int ea[emax] is now int EffectX[emax]
extern int EffectX[EFFECT_MAX];
// @attention +KZ: int eb[emax] is now int EffectY[emax]
extern int EffectY[EFFECT_MAX];
// @attention +KZ: int enobia[emax] is now int EffectSizeX[emax]
extern int EffectSizeX[EFFECT_MAX];
// @attention +KZ: int enobib[emax] is now int EffectSizeY[emax]
extern int EffectSizeY[EFFECT_MAX];
// @attention +KZ: int ec[emax] is now int EffectVelX[emax]
extern int EffectVelX[EFFECT_MAX];
// @attention +KZ: int ed[emax] is now int EffectVelY[emax]
extern int EffectVelY[EFFECT_MAX];
// @attention +KZ: int ee[emax] is now int EffectFrictionX[emax] (maybe should be a different name)
extern int EffectFrictionX[EFFECT_MAX];
// @attention +KZ: int ef[emax] is now int EffectFrictionY[emax] (maybe should be a different name)
extern int EffectFrictionY[EFFECT_MAX];
// @attention +KZ: int etm[emax] is now int EffectTimer[emax]
extern int EffectTimer[EFFECT_MAX];
// @attention +KZ: int egtype[emax] is now EEffectType EffectType[emax]
extern EEffectType EffectType[EFFECT_MAX];

void HandleEffects();

void RenderEffects();

//+KZ: same as above
int CreateEffect(double PosX, double PosY, double VelX, double VelY, double FrictionX, double FrictionY,
	double SizeX, double SizeY, EEffectType Type, int Timer, int index = -1);
void ClearAllEffects();

//効果を持たないグラ (Grass with no effect)
// @attention +KZ: void eyobi() is now void CreateEffectLegacy()
// @attention +KZ: int xa is now int PosX
// @attention +KZ: int xb is now int PosY
// @attention +KZ: int xc is now int VelX
// @attention +KZ: int xd is now int VelY
// @attention +KZ: int xe is now int FrictionX
// @attention +KZ: int xf is now int FrictionY
// @attention +KZ: int xnobia is now int SizeX
// @attention +KZ: int xnobib is now int SizeY
// @attention +KZ: int xgtype is now EEffectType Type
// @attention +KZ: int xtm is now int Timer
void CreateEffectLegacy(int PosX, int PosY, int VelX, int VelY, int FrictionX, int FrictionY, int SizeX,
	   int SizeY, EEffectType Type, int Timer);

#endif
