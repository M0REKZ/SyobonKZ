
#ifndef SYOBON_EXTRA_GRAPHICS_H
#define SYOBON_EXTRA_GRAPHICS_H

void HandleExtraGraphics();

void RenderExtraGraphics();
void RenderBackground();

//+KZ: Backgrounds didnt have a create function
//	this works like the new BlockCreate() and CreateEntity() functions
int CreateBackground(double PosX, double PosY, EDecorationType Type, int index = -1);
void ClearAllBackgrounds();

//+KZ: same as above
int CreateExtraGraphic(double PosX, double PosY, double VelX, double VelY, double FrictionX, double FrictionY,
	double SizeX, double SizeY, EExtraGraphicType Type, int Timer, int index = -1);
void ClearAllExtraGraphics();

//効果を持たないグラ (Grass with no effect)
// @attention +KZ: void eyobi() is now void CreateExtraGraphicLegacy()
// @attention +KZ: int xa is now int PosX
// @attention +KZ: int xb is now int PosY
// @attention +KZ: int xc is now int VelX
// @attention +KZ: int xd is now int VelY
// @attention +KZ: int xe is now int FrictionX
// @attention +KZ: int xf is now int FrictionY
// @attention +KZ: int xnobia is now int SizeX
// @attention +KZ: int xnobib is now int SizeY
// @attention +KZ: int xgtype is now EExtraGraphicType Type
// @attention +KZ: int xtm is now int Timer
void CreateExtraGraphicLegacy(int PosX, int PosY, int VelX, int VelY, int FrictionX, int FrictionY, int SizeX,
	   int SizeY, EExtraGraphicType Type, int Timer);

#endif
