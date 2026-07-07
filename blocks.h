
#ifndef SYOBON_BLOCKS_H
#define SYOBON_BLOCKS_H

#include "level_enums.hpp"

void RenderBlocks();
void RenderWalls();
void RenderOverwritePipe();

//+KZ: added in SyobonKZ
void RenderObjectsBehind();

//+KZ: new functions for easy use.
// use index -1 to let this function choose block index
// returns the block index if its created successfully
int BlockCreate(double x, double y, EBlockType type, EBlockSubType subtype = EBlockSubType::NONE, int index = -1);

//+KZ: clear all blocks from memory
void BlockClearAll();

//+KZ: like BlockCreate but for Objects
int ObjectCreate(double x, double y, double size_x, double size_y, EObjectType type, EObjectSubType subtype, int index = -1);

//+KZ: clear all objects from memory
void ObjectClearAll();

//ブロック (Block)
// @attention +KZ: void tyobi() is now void BlockCreateLegacy()
void BlockCreateLegacy(int x, int y, EBlockType type);
// @attention +KZ: void brockbreak() is now void BlockBreak()
void BlockBreak(int t);

#endif
