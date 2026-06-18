
#ifndef SYOBON_EXTRA_GRAPHICS_H
#define SYOBON_EXTRA_GRAPHICS_H

//効果を持たないグラ (Grass with no effect)
// @attention +KZ: void eyobi() is now void CreateExtraGraphic()
void CreateExtraGraphic(int PosX, int PosY, int xc, int xd, int xe, int xf, int xnobia,
	   int xnobib, int xgtype, int xtm);

void HandleExtraGraphics();

void RenderExtraGraphics();
void RenderBackground();

#endif
