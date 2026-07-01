#include "main.h"
#include "global_vars.h"
#include "blocks.h"

void RenderBlocks()
{
    // ブロック描画 (Block drawing)
    for (t = 0; t < BLOCK_MAX; t++)
    {
        xx[0] = BlockX[t] - fx;
        xx[1] = BlockY[t] - fy;
        xx[2] = 32;
        xx[3] = xx[2];
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax)
        {

            xx[9] = 0;
            if (StageColor == ELevelType::UNDERGROUND)
            {
                xx[9] = 30;
            }
            if (StageColor == ELevelType::CASTLE)
            {
                xx[9] = 60;
            }
            if (StageColor == ELevelType::ICY)
            {
                xx[9] = 90;
            }

            if ((int)BlockType[t] < 100)
            {
                xx[6] = (int)BlockType[t] + xx[9];
                drawimage(Sliced_GFX[xx[6]][1], xx[0] / 100, xx[1] / 100);
            }

            if (BlockSubType[t] != EBlockSubType::ITEM_BLOCK_UNKNOWN_10)
            {

                if (
                    BlockType[t] == EBlockType::ITEM_BLOCK_DODGE ||
                    BlockType[t] == EBlockType::ITEM_BLOCK_ENEMY ||
                    BlockType[t] == EBlockType::ITEM_BLOCK_MUSHROOM ||
                    BlockType[t] == EBlockType::ITEM_BLOCK_MUSHROOM_2 ||
                    BlockType[t] == EBlockType::ITEM_BLOCK_STAR && BlockSubType[t] == EBlockSubType::ITEM_BLOCK_STAR_NORMAL ||
                    BlockType[t] == EBlockType::ITEM_BLOCK_TRAP_HIDDEN && BlockSubType[t] == EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_VISIBLE ||
                    BlockType[t] == EBlockType::ITEM_BLOCK_PSWITCH
                )
                {
                    xx[6] = 2 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }

                if (BlockType[t] == EBlockType::ITEM_BLOCK_COINS || BlockType[t] == EBlockType::ITEM_BLOCK_STAR && BlockSubType[t] == EBlockSubType::ITEM_BLOCK_STAR_BRICK || BlockType[t] == EBlockType::BRICK_BRITTLE && BlockSubType[t] == EBlockSubType::BRICK_BRITTLE_BRICK)
                {
                    xx[6] = 1 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }

                if (BlockType[t] == EBlockType::ITEM_BLOCK_POISON_OPEN || BlockType[t] == EBlockType::ITEM_BLOCK_COINS_OPEN || BlockType[t] == EBlockType::BRICK_BRITTLE && BlockSubType[t] == EBlockSubType::BRICK_BRITTLE_ITEM_BLOCK_OPEN || BlockType[t] == EBlockType::FIREBAR_GROW)
                {
                    xx[6] = 3 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }
            }

            if (BlockType[t] == EBlockType::NOTE_BLOCK && BlockSubType[t] == EBlockSubType::NOTE_BLOCK_RED_VISIBLE)
            {
                drawimage(Sliced_GFX[4][5], xx[0] / 100, xx[1] / 100);
            }

            if (BlockType[t] == EBlockType::NOTE_BLOCK && BlockSubType[t] >= EBlockSubType::NOTE_BLOCK_WHITE_VISIBLE)
            {
                drawimage(Sliced_GFX[3][5], xx[0] / 100, xx[1] / 100);
            }

            if (BlockType[t] == EBlockType::BRICK_BRITTLE && BlockSubType[t] == EBlockSubType::BRICK_BRITTLE_BRICK_3)
            {
                xx[6] = 1 + xx[9];
                drawimage(Sliced_GFX[xx[6]][1], xx[0] / 100, xx[1] / 100);
            }
            // ジャンプ台
            if (BlockType[t] == EBlockType::TRAMPOLINE && BlockSubType[t] != EBlockSubType::TRAMPOLINE_HIDDEN)
            {
                drawimage(Sliced_GFX[16][1], xx[0] / 100 + 3,
                          xx[1] / 100 + 2);
            }
            // ON-OFF
            if (BlockType[t] == EBlockType::ON_BLOCK)
                drawimage(Sliced_GFX[10][5], xx[0] / 100, xx[1] / 100);
            if (BlockType[t] == EBlockType::OFF_BLOCK)
                drawimage(Sliced_GFX[11][5], xx[0] / 100, xx[1] / 100);

            if (BlockType[t] == EBlockType::SWORD)
                drawimage(Sliced_GFX[12][5], xx[0] / 100, xx[1] / 100);
            if (BlockType[t] == EBlockType::BRIDGE_ROPE)
                drawimage(Sliced_GFX[13][5], xx[0] / 100, xx[1] / 100);
            if (BlockType[t] == EBlockType::MELON)
                drawimage(Sliced_GFX[14][5], xx[0] / 100, xx[1] / 100);

            if (BlockType[t] == EBlockType::MESSAGE_BLOCK || BlockType[t] == EBlockType::MESSAGE_BLOCK_BREAKABLE)
                drawimage(Sliced_GFX[1][5], xx[0] / 100, xx[1] / 100);

            // Pスイッチ (P switch)
            if (BlockType[t] == EBlockType::PSWITCH)
            {
                drawimage(Sliced_GFX[2][5], xx[0] / 100, xx[1] / 100);
            }
            // コイン (Coin)
            if (BlockType[t] == EBlockType::COIN)
            {
                drawimage(Sliced_GFX[0][2], xx[0] / 100 + 2,
                          xx[1] / 100 + 1);
            }
        }
    }
}

void RenderWalls()
{
    // 地面(壁)//土管も (Ground (walls) // Also pipes)
    for (t = 0; t < GROUND_MAX; t++)
    {
        if (GroundX[t] - fx + GroundSizeX[t] >= -10 && GroundX[t] - fx <= fxmax + 1100)
        {

            if (GroundType[t] == EObjectType::VERTICAL_PIPE_BODY)
            {
                setcolor(40, 200, 40);
                fillrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100,
                         GroundSizeX[t] / 100, GroundSizeY[t] / 100);
                drawrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100,
                         GroundSizeX[t] / 100, GroundSizeY[t] / 100);
            }
            // 土管
            if (GroundType[t] == EObjectType::VERTICAL_PIPE_HEAD)
            {
                setcolor(0, 230, 0);
                fillrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100,
                         GroundSizeX[t] / 100, GroundSizeY[t] / 100);
                setc0();
                drawrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100,
                         GroundSizeX[t] / 100, GroundSizeY[t] / 100);
            }
            // 土管(下)
            if (GroundType[t] == EObjectType::HORIZONTAL_PIPE_BODY)
            {
                setcolor(0, 230, 0);
                fillrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100 + 1,
                         GroundSizeX[t] / 100, GroundSizeY[t] / 100);
                setc0();
                drawline((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100,
                         (GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100 + GroundSizeY[t] / 100);
                drawline((GroundX[t] - fx) / 100 +
                             GroundSizeX[t] / 100,
                         (GroundY[t] - fy) / 100,
                         (GroundX[t] - fx) / 100 +
                             GroundSizeX[t] / 100,
                         (GroundY[t] - fy) / 100 + GroundSizeY[t] / 100);
            }
            // 土管(横)
            if (GroundType[t] == EObjectType::HORIZONTAL_PIPE_HEAD)
            {
                setcolor(0, 230, 0);
                fillrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100 + 1,
                         GroundSizeX[t] / 100, GroundSizeY[t] / 100);
                setc0();
                drawline((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100,
                         (GroundX[t] - fx) / 100 +
                             GroundSizeX[t] / 100,
                         (GroundY[t] - fy) / 100);
                drawline((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100 +
                             GroundSizeY[t] / 100,
                         (GroundX[t] - fx) / 100 +
                             GroundSizeX[t] / 100,
                         (GroundY[t] - fy) / 100 + GroundSizeY[t] / 100);
            }
            // 落ちてくるブロック (Falling blocks)
            if (GroundType[t] == EObjectType::FALLING_BLOCKS)
            {
                if (GroundSubType[t] == EObjectSubType::FALLING_BLOCKS_OVERWORLD_BRICK)
                {
                    for (t3 = 0; t3 <= GroundSizeX[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[1][1],
                                  (GroundX[t] -
                                   fx) / 100 + 29 * t3,
                                  (GroundY[t] - fy) / 100);
                    }
                }
                if (GroundSubType[t] == EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK ||
                    GroundSubType[t] == EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK_LEVEL_1_2)
                {
                    for (t3 = 0; t3 <= GroundSizeX[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[31][1],
                                  (GroundX[t] -
                                   fx) / 100 + 29 * t3,
                                  (GroundY[t] - fy) / 100);
                    }
                }
                if (GroundSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP ||
                    GroundSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_4)
                {
                    for (t3 = 0; t3 <= GroundSizeX[t] / 3000; t3++)
                    {
                        for (t2 = 0; t2 <= GroundSizeY[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[65]
                                                [1],
                                      (GroundX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (GroundY[t] -
                                       fy) /
                                              100 +
                                          29 * t2);
                        }
                    }
                }

                if (GroundSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_X_ONLY)
                {
                    for (t3 = 0; t3 <= GroundSizeX[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[65][1],
                                  (GroundX[t] -
                                   fx) / 100 + 29 * t3,
                                  (GroundY[t] - fy) / 100);
                    }
                }

            } // 51

            // 落ちるやつ (The one that falls)
            if (GroundType[t] == EObjectType::FALLING_FLOOR)
            {
                xx[29] = 0;
                if (StageColor == ELevelType::UNDERGROUND)
                {
                    xx[29] = 30;
                }
                if (StageColor == ELevelType::CASTLE)
                {
                    xx[29] = 60;
                }
                if (StageColor == ELevelType::ICY)
                {
                    xx[29] = 90;
                }

                for (t3 = 0; t3 <= GroundSizeX[t] / 3000; t3++)
                {
                    if (GroundSubType[t] == EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM)
                    {
                        drawimage(Sliced_GFX[5 + xx[29]][1],
                                  (GroundX[t] -
                                   fx) / 100 + 29 * t3,
                                  (GroundY[t] - fy) / 100);
                        if (StageColor != ELevelType::CASTLE)
                        {
                            drawimage(Sliced_GFX[6 + xx[29]]
                                                [1],
                                      (GroundX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (GroundY[t] -
                                       fy) /
                                              100 + 29);
                        }
                        else
                        {
                            drawimage(Sliced_GFX[5 + xx[29]]
                                                [1],
                                      (GroundX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (GroundY[t] -
                                       fy) /
                                              100 + 29);
                        }
                    }
                    if (GroundSubType[t] == EObjectSubType::FALLING_FLOOR_BRICK)
                    {
                        for (t2 = 0; t2 <= GroundSizeY[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[1 + xx[29]]
                                                [1],
                                      (GroundX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (GroundY[t] -
                                       fy) /
                                              100 + 29 * t2);
                        }
                    }

                    if (GroundSubType[t] == EObjectSubType::FALLING_FLOOR_GROUND_TOP)
                    {
                        for (t2 = 0; t2 <= GroundSizeY[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[5 + xx[29]]
                                                [1],
                                      (GroundX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (GroundY[t] -
                                       fy) /
                                              100 + 29 * t2);
                        }
                    }
                }
            }
            // ステージトラップ (Stage Trap)
            if (TrapDisplay == 1)
            {
                if (
                    (GroundType[t] >= EObjectType::TRIGGERS_START && GroundType[t] <= EObjectType::TRIGGERS_END) ||
                    (currentGame == ESyobonActionGame::SYOBON_ACTION_3 ?
                    GroundType[t] >= EObjectType::SA3_TRIGGER_START && GroundType[t] < EObjectType::SA3_TRIGGER_END
                    :
                    false
                    )
                )
                {
                    if (StageColor == ELevelType::OVERWORLD || StageColor == ELevelType::SKY || StageColor == ELevelType::ICY)
                        setc0();
                    if (StageColor == ELevelType::UNDERGROUND || StageColor == ELevelType::CASTLE)
                        setc1();
                    drawrect((GroundX[t] - fx) / 100,
                             (GroundY[t] - fy) / 100,
                             GroundSizeX[t] / 100, GroundSizeY[t] / 100);
                }
            }
            // ゴール (Goal)
            if (GroundType[t] == EObjectType::GOAL_POLE)
            {
                setc1();
                fillrect((GroundX[t] - fx) / 100 + 10,
                         (GroundY[t] - fy) / 100, 10, GroundSizeY[t] / 100 - 8);
                setc0();
                drawrect((GroundX[t] - fx) / 100 + 10,
                         (GroundY[t] - fy) / 100, 10, GroundSizeY[t] / 100 - 8);
                setcolor(250, 250, 0);
                fillarc((GroundX[t] - fx) / 100 + 15 - 1,
                        (GroundY[t] - fy) / 100, 10, 10);
                setc0();
                drawarc((GroundX[t] - fx) / 100 + 15 - 1,
                        (GroundY[t] - fy) / 100, 10, 10);
            }
            // 中間
            if (GroundType[t] == EObjectType::CHECKPOINT)
            {
                drawimage(Sliced_GFX[20][4],
                          (GroundX[t] - fx) / 100, (GroundY[t] - fy) / 100);
            }

            //Syobon Action 3
            if(currentGame == ESyobonActionGame::SYOBON_ACTION_3)
            {
                //empty for now
            }
        }
    } // t
}

void RenderOverwritePipe()
{
    // 描画上書き(土管) (Overwrite drawing (pipe)) //+KZ: ??
    for (t = 0; t < GROUND_MAX; t++)
    {
        if (GroundX[t] - fx + GroundSizeX[t] >= -10 && GroundX[t] - fx <= fxmax + 1100)
        {

            // 入る土管(右)
            if (GroundType[t] == EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD)
            {
                setcolor(0, 230, 0);
                fillrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100 + 1,
                         GroundSizeX[t] / 100, GroundSizeY[t] / 100);
                setc0();
                drawrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100 + 1,
                         GroundSizeX[t] / 100, GroundSizeY[t] / 100);
            }
            // とぶ土管
            if (GroundType[t] == EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD)
            {
                setcolor(0, 230, 0);
                fillrect((GroundX[t] - fx) / 100 + 5,
                         (GroundY[t] - fy) / 100 + 30,
                         50, GroundSizeY[t] / 100 - 30);
                setc0();
                drawline((GroundX[t] - fx) / 100 + 5,
                         (GroundY[t] - fy) / 100 + 30,
                         (GroundX[t] - fx) / 100 + 5,
                         (GroundY[t] - fy) / 100 + GroundSizeY[t] / 100);
                drawline((GroundX[t] - fx) / 100 + 5 +
                             50,
                         (GroundY[t] - fy) / 100 + 30,
                         (GroundX[t] - fx) / 100 + 50 +
                             5,
                         (GroundY[t] - fy) / 100 + GroundSizeY[t] / 100);

                setcolor(0, 230, 0);
                fillrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100 + 1, 60, 30);
                setc0();
                drawrect((GroundX[t] - fx) / 100,
                         (GroundY[t] - fy) / 100 + 1, 60, 30);
            }
            // 地面(ブロック)
            if (GroundType[t] == EObjectType::CASTLE_BRICKS)
            {
                for (t3 = 0; t3 <= GroundSizeX[t] / 3000; t3++)
                {
                    for (t2 = 0; t2 <= GroundSizeY[t] / 3000; t2++)
                    {
                        drawimage(Sliced_GFX[65][1],
                                  (GroundX[t] -
                                   fx) / 100 + 29 * t3,
                                  (GroundY[t] - fy) / 100 + 29 * t2);
                    }
                }
            }
        }
    } // t
}

void RenderObjectsBehind()
{
    for (int ground_index = 0; ground_index < GROUND_MAX; ground_index++)
    {
        if (GroundX[ground_index] - fx + GroundSizeX[ground_index] >= -10 && GroundX[ground_index] - fx <= fxmax + 1100)
        {
            if(currentGame == ESyobonActionGame::SYOBON_ACTION_3)
            {
                if (GroundType[ground_index] == EObjectType::SA3_FAKE_PIPE_BODY)
                {
                    setcolor(0, 230, 0);
                    fillrect((GroundX[ground_index] - fx) / 100,
                            (GroundY[ground_index] - fy) / 100,
                            GroundSizeX[ground_index] / 100, GroundSizeY[ground_index] / 100);
                    setc0();
                    drawrect((GroundX[ground_index] - fx) / 100,
                            (GroundY[ground_index] - fy) / 100,
                            GroundSizeX[ground_index] / 100, GroundSizeY[ground_index] / 100);
                }
            }
        }
    }
}

int BlockCreate(double x, double y, EBlockType type, EBlockSubType subtype, int index)
{
    x *= BLOCK_DEFAULT_SIZE;
    y *= BLOCK_DEFAULT_SIZE;

    y -= 12; //stage() does -12

    //the game simulates floating point numbers
    //by multiplying all positions by 100
    x *= 100;
    y *= 100;

    if(index < 0)
    {
        //use BlockCount to keep compat with BlockCreateLegacy()
        index = BlockCount++;
        if(BlockCount == BLOCK_MAX)
            BlockCount = 0;
    }

    if(index >= 0 && index < BLOCK_MAX)
    {
        BlockX[index] = (int)x;
        BlockY[index] = (int)y;
        BlockType[index] = type;
        BlockSubType[index] = subtype;

        BlockAITimer[index] = 0;
        BlockItemCount[index] = 0;
    }
    else
    {
        fprintf(stderr, "BlockCreate - Could not create block %d %d at %d %d! (index %d)", type, subtype, (int)x, (int)y, index);
    }

    return index;
}

void BlockClearAll()
{
    for(int i = 0; i < BLOCK_MAX; ++i)
    {
        //the enemies will ignore blocks with a very low or high X position
        BlockX[i] = std::numeric_limits<int>::min();
        BlockY[i] = std::numeric_limits<int>::min();

        //the player will ignore a extremely high block type
        BlockType[i] = (EBlockType)std::numeric_limits<int>::max();

        BlockSubType[i] = EBlockSubType::NONE;

        BlockAITimer[i] = 0;
        BlockItemCount[i] = 0;
    }

    BlockCount = 0;
}

int GroundCreate(double x, double y, double size_x, double size_y, EObjectType type, EObjectSubType subtype, int index)
{
    x *= BLOCK_DEFAULT_SIZE;
    y *= BLOCK_DEFAULT_SIZE;

    y -= 12; //stage() does -12 to blocks, lets be consistent

    //the game simulates floating point numbers
    //by multiplying all positions by 100
    x *= 100;
    y *= 100;

    if(index < 0)
    {
        //use BlockCount to keep compat with BlockCreateLegacy()
        index = GroundCount++;
        if(GroundCount == GROUND_MAX)
            GroundCount = 0;
    }

    if(index >= 0 && index < GROUND_MAX)
    {
        GroundX[index] = (int)x;
        GroundY[index] = (int)y;
        GroundType[index] = type;
        GroundSubType[index] = subtype;
        GroundSizeX[index] = (int)(size_x * BLOCK_DEFAULT_SIZE * 100);
        GroundSizeY[index] = (int)(size_y * BLOCK_DEFAULT_SIZE * 100);

        GroundAI[index] = 0;
        GroundVelY[index] = 0;
    }
    else
    {
        fprintf(stderr, "GroundCreate - Could not create object %d %d at %d %d! (index %d)", type, subtype, (int)x, (int)y, index);
    }

    return index;
}

void GroundClearAll()
{
    for(int i = 0; i < GROUND_MAX; ++i)
    {
        GroundX[i] = std::numeric_limits<int>::min();
        GroundY[i] = std::numeric_limits<int>::min();
        GroundSizeX[i] = std::numeric_limits<int>::min();
        GroundSizeY[i] = std::numeric_limits<int>::min();

        GroundType[i] = EObjectType::VERTICAL_PIPE_BODY;
        GroundSubType[i] = EObjectSubType::NONE;

        GroundVelY[i] = 0;
        GroundAI[i] = 0;
    }

    GroundCount = 0;
}

// ブロック出現 (Block appears)

void BlockCreateLegacy(int x, int y, EBlockType type)
{

	BlockX[BlockCount] = x * 100;
	BlockY[BlockCount] = y * 100;
	BlockType[BlockCount] = type;

	BlockCount++;
	if (BlockCount >= BLOCK_MAX)
		BlockCount = 0;
} // BlockCreate

// ブロック破壊 (Block destruction)
void BlockBreak(int t)
{
	//+KZ removed useless code
	BlockX[t] = -800000;
} // brock
