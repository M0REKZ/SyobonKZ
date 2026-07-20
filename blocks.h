
#ifndef SYOBON_BLOCKS_H
#define SYOBON_BLOCKS_H

#include "level_enums.hpp"

//ブロック (Block)
// @attention +KZ: tmax is now BLOCK_MAX
// +KZ: had to increase it to support SA3
#define LEGACY_BLOCK_MAX 641
#define BLOCK_MAX 1000
// @attention +KZ: int tco is now int BlockCount
extern int BlockCount;
// @attention +KZ: int ta[tmax] is now int BlockX[tmax]
extern int BlockX[BLOCK_MAX];
// @attention +KZ: int tb[tmax] is now int BlockY[tmax]
extern int BlockY[BLOCK_MAX];
//extern int tc[tmax], td[tmax]; //+KZ: unused
// @attention +KZ: int thp[tmax] is now int BlockAITimer[tmax]
extern int BlockAITimer[BLOCK_MAX];
// @attention +KZ: int ttype[tmax] is now EBlockType BlockType[tmax]
extern EBlockType BlockType[BLOCK_MAX];
//+KZ: titem[tmax] is specific for Block 112/113 (Coin mass production)
// @attention +KZ: int titem[tmax] is now int BlockItemCount[tmax]
extern int BlockItemCount[BLOCK_MAX];
// @attention +KZ: int txtype[tmax] is now EBlockSubType BlockSubType[tmax]
extern EBlockSubType BlockSubType[BLOCK_MAX];

void RenderBlocks();

//+KZ: new functions for easy use.
// use index -1 to let this function choose block index
// returns the block index if its created successfully
int BlockCreate(double x, double y, EBlockType type, EBlockSubType subtype = EBlockSubType::NONE, int index = -1);

//+KZ: clear all blocks from memory
void BlockClearAll();

//Legacy functions for compatibility
//ブロック (Block)
// @attention +KZ: void tyobi() is now void BlockCreateLegacy()
void BlockCreateLegacy(int x, int y, EBlockType type);
// @attention +KZ: void brockbreak() is now void BlockBreak()
void BlockBreak(int t);

#endif
