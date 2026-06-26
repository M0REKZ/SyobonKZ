
#ifndef SYOBON_BLOCKS_H
#define SYOBON_BLOCKS_H

#include "level_enums.hpp"

void RenderBlocks();
void RenderWalls();
void RenderOverwritePipe();

//ブロック (Block)
// @attention +KZ: void tyobi() is now void BlockCreate()
void BlockCreate(int x, int y, EBlockType type);
// @attention +KZ: void brockbreak() is now void BlockBreak()
void BlockBreak(int t);

#endif
