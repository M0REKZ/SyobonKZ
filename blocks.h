
#ifndef SYOBON_BLOCKS_H
#define SYOBON_BLOCKS_H

#include "level_enums.hpp"

void RenderBlocks();
void RenderWalls();
void RenderOverwritePipe();

//+KZ: new functions for easy use.
// new BlockCreate function that searchs for empty spaces to create blocks
// no guarantee it will work well with BlockCreateLegacy (tyobi)
// use index -1 to let this function choose block index
void BlockCreate(double x, double y, EBlockType type, EBlockSubType subtype = EBlockSubType::NONE, int index = -1);

//+KZ: clear all blocks from memory
void BlockClearAll();

//+KZ: clear all objects from memory
void GroundClearAll();

//ブロック (Block)
// @attention +KZ: void tyobi() is now void BlockCreateLegacy()
void BlockCreateLegacy(int x, int y, EBlockType type);
// @attention +KZ: void brockbreak() is now void BlockBreak()
void BlockBreak(int t);

#endif
