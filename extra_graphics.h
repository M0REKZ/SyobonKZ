
#ifndef SYOBON_EXTRA_GRAPHICS_H
#define SYOBON_EXTRA_GRAPHICS_H

//効果を持たないグラ (Grass with no effect)
// @attention +KZ: void eyobi() is now void CreateExtraGraphic()
// @attention +KZ: int xa is now int PosX
// @attention +KZ: int xb is now int PosY
// @attention +KZ: int xc is now int VelX
// @attention +KZ: int xd is now int VelY
// @attention +KZ: int xe is now int FrictionX
// @attention +KZ: int xf is now int FrictionY
// @attention +KZ: int xnobia is now int SizeX
// @attention +KZ: int xnobib is now int SizeY
// @attention +KZ: int xgtype is now int Type
// @attention +KZ: int xtm is now int Timer
void CreateExtraGraphic(int PosX, int PosY, int VelX, int VelY, int FrictionX, int FrictionY, int SizeX,
	   int SizeY, int Type, int Timer);

void HandleExtraGraphics();

void RenderExtraGraphics();
void RenderBackground();

#endif
