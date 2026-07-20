#include "global_vars.h"
#include "main.h"
#include "loadg.h"
#include "objects.h"

//地面
int ObjectCount;
int ObjectX[OBJECT_MAX], ObjectY[OBJECT_MAX], ObjectSizeX[OBJECT_MAX], ObjectSizeY[OBJECT_MAX];
EObjectType ObjectType[OBJECT_MAX];
EObjectSubType ObjectSubType[OBJECT_MAX];
int ObjectVelY[OBJECT_MAX];
int ObjectAI[OBJECT_MAX];

void RenderWalls()
{
    // 地面(壁)//土管も (Ground (walls) // Also pipes)
    for (t = 0; t < OBJECT_MAX; t++)
    {
        if (ObjectX[t] - fx + ObjectSizeX[t] >= -10 && ObjectX[t] - fx <= fxmax + 1100)
        {

            if (ObjectType[t] == EObjectType::GREEN_OUTLINE_PIPE_PART)
            {
                setcolor(40, 200, 40);
                fillrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100,
                         ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
                drawrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100,
                         ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
            }
            // 土管
            if (ObjectType[t] == EObjectType::BLACK_OUTLINE_PIPE_PART)
            {
                setcolor(0, 230, 0);
                fillrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100,
                         ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
                setc0();
                drawrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100,
                         ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
            }
            // 土管(下)
            if (ObjectType[t] == EObjectType::VERTICAL_PIPE_BODY)
            {
                setcolor(0, 230, 0);
                fillrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100 + 1,
                         ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
                setc0();
                drawline((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100,
                         (ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100 + ObjectSizeY[t] / 100);
                drawline((ObjectX[t] - fx) / 100 +
                             ObjectSizeX[t] / 100,
                         (ObjectY[t] - fy) / 100,
                         (ObjectX[t] - fx) / 100 +
                             ObjectSizeX[t] / 100,
                         (ObjectY[t] - fy) / 100 + ObjectSizeY[t] / 100);
            }
            // 土管(横)
            if (ObjectType[t] == EObjectType::HORIZONTAL_PIPE_BODY)
            {
                setcolor(0, 230, 0);
                fillrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100 + 1,
                         ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
                setc0();
                drawline((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100,
                         (ObjectX[t] - fx) / 100 +
                             ObjectSizeX[t] / 100,
                         (ObjectY[t] - fy) / 100);
                drawline((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100 +
                             ObjectSizeY[t] / 100,
                         (ObjectX[t] - fx) / 100 +
                             ObjectSizeX[t] / 100,
                         (ObjectY[t] - fy) / 100 + ObjectSizeY[t] / 100);
            }
            // 落ちてくるブロック (Falling blocks)
            if (ObjectType[t] == EObjectType::FALLING_BLOCKS)
            {
                if (ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_OVERWORLD_BRICK)
                {
                    for (t3 = 0; t3 <= ObjectSizeX[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[1][1],
                                  (ObjectX[t] -
                                   fx) / 100 + 29 * t3,
                                  (ObjectY[t] - fy) / 100);
                    }
                }
                if (ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK ||
                    ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK_LEVEL_1_2)
                {
                    for (t3 = 0; t3 <= ObjectSizeX[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[31][1],
                                  (ObjectX[t] -
                                   fx) / 100 + 29 * t3,
                                  (ObjectY[t] - fy) / 100);
                    }
                }
                if (ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP ||
                    ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_4)
                {
                    for (t3 = 0; t3 <= ObjectSizeX[t] / 3000; t3++)
                    {
                        for (t2 = 0; t2 <= ObjectSizeY[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[65]
                                                [1],
                                      (ObjectX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (ObjectY[t] -
                                       fy) /
                                              100 +
                                          29 * t2);
                        }
                    }
                }

                if (ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_X_ONLY)
                {
                    for (t3 = 0; t3 <= ObjectSizeX[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[65][1],
                                  (ObjectX[t] -
                                   fx) / 100 + 29 * t3,
                                  (ObjectY[t] - fy) / 100);
                    }
                }

            } // 51

            // 落ちるやつ (The one that falls)
            if (ObjectType[t] == EObjectType::FALLING_FLOOR || 
                (currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 && 
                    (
                        ObjectType[t] == EObjectType::SA3_FALLING_FLOOR ||
                        ObjectType[t] == EObjectType::SA3_UNTOUCHABLE_FALLING_FLOOR
                    )
                ))
            {
                xx[29] = 0;
                if (LevelType == ELevelType::UNDERGROUND)
                {
                    xx[29] = 30;
                }
                if (LevelType == ELevelType::CASTLE)
                {
                    xx[29] = 60;
                }
                if (LevelType == ELevelType::ICY)
                {
                    xx[29] = 90;
                }

                for (t3 = 0; t3 <= ObjectSizeX[t] / 3000; t3++)
                {
                    if (ObjectSubType[t] == EObjectSubType::SA3_FALLING_FLOOR_GROUND_TOP_BOTTOM)
                    {
                        drawimage(Sliced_GFX[5 + xx[29]][1],
                                  (ObjectX[t] -
                                   fx) / 100 + 29 * t3,
                                  (ObjectY[t] - fy) / 100);
                        if (LevelType != ELevelType::CASTLE)
                        {
                            drawimage(Sliced_GFX[6 + xx[29]]
                                                [1],
                                      (ObjectX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (ObjectY[t] -
                                       fy) /
                                              100 + 29);
                        }
                        else
                        {
                            drawimage(Sliced_GFX[5 + xx[29]]
                                                [1],
                                      (ObjectX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (ObjectY[t] -
                                       fy) /
                                              100 + 29);
                        }
                    }
                    if (ObjectSubType[t] == EObjectSubType::SA3_FALLING_FLOOR_BRICK)
                    {
                        for (t2 = 0; t2 <= ObjectSizeY[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[1 + xx[29]]
                                                [1],
                                      (ObjectX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (ObjectY[t] -
                                       fy) /
                                              100 + 29 * t2);
                        }
                    }

                    if (ObjectSubType[t] == EObjectSubType::SA3_FALLING_FLOOR_GROUND_TOP)
                    {
                        for (t2 = 0; t2 <= ObjectSizeY[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[5 + xx[29]]
                                                [1],
                                      (ObjectX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (ObjectY[t] -
                                       fy) /
                                              100 + 29 * t2);
                        }
                    }

                    if (ObjectSubType[t] == EObjectSubType::SA3_FALLING_FLOOR_GROUND_BOTTOM)
                    {
                        for (t2 = 0; t2 <= ObjectSizeY[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[6 + xx[29]]
                                                [1],
                                      (ObjectX[t] -
                                       fx) /
                                              100 + 29 * t3,
                                      (ObjectY[t] -
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
                    (ObjectType[t] >= EObjectType::TRIGGERS_START && ObjectType[t] <= EObjectType::TRIGGERS_END) ||
                    (currentGame == ESyobonActionGame::SYOBON_ACTION_3 ?
                    ObjectType[t] >= EObjectType::SA3_TRIGGER_START && ObjectType[t] < EObjectType::SA3_TRIGGER_END
                    :
                    false
                    )
                )
                {
                    if (LevelType == ELevelType::OVERWORLD || LevelType == ELevelType::SKY || LevelType == ELevelType::ICY)
                        setc0();
                    if (LevelType == ELevelType::UNDERGROUND || LevelType == ELevelType::CASTLE)
                        setc1();
                    drawrect((ObjectX[t] - fx) / 100,
                             (ObjectY[t] - fy) / 100,
                             ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
                }
            }
            // ゴール (Goal)
            if (ObjectType[t] == EObjectType::GOAL_POLE)
            {
                setc1();
                fillrect((ObjectX[t] - fx) / 100 + 10,
                         (ObjectY[t] - fy) / 100, 10, ObjectSizeY[t] / 100 - 8);
                setc0();
                drawrect((ObjectX[t] - fx) / 100 + 10,
                         (ObjectY[t] - fy) / 100, 10, ObjectSizeY[t] / 100 - 8);
                setcolor(250, 250, 0);
                fillarc((ObjectX[t] - fx) / 100 + 15 - 1,
                        (ObjectY[t] - fy) / 100, 10, 10);
                setc0();
                drawarc((ObjectX[t] - fx) / 100 + 15 - 1,
                        (ObjectY[t] - fy) / 100, 10, 10);
            }
            // 中間
            if (ObjectType[t] == EObjectType::CHECKPOINT)
            {
                if(
                    (currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 && SyobonWorld == 1) ||
                    (currentGame == ESyobonActionGame::SYOBON_ACTION_3)
                )
                    drawimage(Sliced_GFX_KZ[6], (ObjectX[t] - fx) / 100, (ObjectY[t] - fy) / 100);
                else
                    drawimage(Sliced_GFX[20][4], (ObjectX[t] - fx) / 100, (ObjectY[t] - fy) / 100);
            }

            //Syobon Action 3
            if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
            {
                
            }
        }
    } // t
}

void RenderOverwritePipe()
{
    // 描画上書き(土管) (Overwrite drawing (pipe)) //+KZ: ??
    for (t = 0; t < OBJECT_MAX; t++)
    {
        if (ObjectX[t] - fx + ObjectSizeX[t] >= -10 && ObjectX[t] - fx <= fxmax + 1100)
        {

            // 入る土管(右)
            if (ObjectType[t] == EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD)
            {
                setcolor(0, 230, 0);
                fillrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100 + 1,
                         ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
                setc0();
                drawrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100 + 1,
                         ObjectSizeX[t] / 100, ObjectSizeY[t] / 100);
            }
            // とぶ土管
            if (ObjectType[t] == EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD)
            {
                setcolor(0, 230, 0);
                fillrect((ObjectX[t] - fx) / 100 + 5,
                         (ObjectY[t] - fy) / 100 + 30,
                         50, ObjectSizeY[t] / 100 - 30);
                setc0();
                drawline((ObjectX[t] - fx) / 100 + 5,
                         (ObjectY[t] - fy) / 100 + 30,
                         (ObjectX[t] - fx) / 100 + 5,
                         (ObjectY[t] - fy) / 100 + ObjectSizeY[t] / 100);
                drawline((ObjectX[t] - fx) / 100 + 5 +
                             50,
                         (ObjectY[t] - fy) / 100 + 30,
                         (ObjectX[t] - fx) / 100 + 50 +
                             5,
                         (ObjectY[t] - fy) / 100 + ObjectSizeY[t] / 100);

                setcolor(0, 230, 0);
                fillrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100 + 1, 60, 30);
                setc0();
                drawrect((ObjectX[t] - fx) / 100,
                         (ObjectY[t] - fy) / 100 + 1, 60, 30);
            }
            // 地面(ブロック)
            if (ObjectType[t] == EObjectType::CASTLE_BRICKS)
            {
                for (t3 = 0; t3 <= ObjectSizeX[t] / 3000; t3++)
                {
                    for (t2 = 0; t2 <= ObjectSizeY[t] / 3000; t2++)
                    {
                        drawimage(Sliced_GFX[65][1],
                                  (ObjectX[t] -
                                   fx) / 100 + 29 * t3,
                                  (ObjectY[t] - fy) / 100 + 29 * t2);
                    }
                }
            }
        }
    } // t
}

void RenderObjectsBehind()
{
    if(currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
        return;

    for (int ground_index = 0; ground_index < OBJECT_MAX; ground_index++)
    {
        if (ObjectX[ground_index] - fx + ObjectSizeX[ground_index] >= -10 && ObjectX[ground_index] - fx <= fxmax + 1100)
        {
            if (ObjectType[ground_index] == EObjectType::SA3_FAKE_PIPE_BODY)
            {
                setcolor(0, 230, 0);
                fillrect((ObjectX[ground_index] - fx) / 100,
                        (ObjectY[ground_index] - fy) / 100,
                        ObjectSizeX[ground_index] / 100, ObjectSizeY[ground_index] / 100);
                setc0();
                drawrect((ObjectX[ground_index] - fx) / 100,
                        (ObjectY[ground_index] - fy) / 100,
                        ObjectSizeX[ground_index] / 100, ObjectSizeY[ground_index] / 100);
            }
            if(ObjectType[ground_index] == EObjectType::GOAL_CASTLE)
            {
                drawimage(Sliced_GFX[3][4],
                        (ObjectX[ground_index] - fx) / 100 - 5, (ObjectY[ground_index] - fy) / 100);
            }
        }
    }
}

int ObjectCreate(double x, double y, double size_x, double size_y, EObjectType type, EObjectSubType subtype, int index)
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
        index = ObjectCount++;
        if(ObjectCount == OBJECT_MAX)
            ObjectCount = 0;
    }

    if(index >= 0 && index < OBJECT_MAX)
    {
        ObjectX[index] = (int)x;
        ObjectY[index] = (int)y;
        ObjectType[index] = type;
        ObjectSubType[index] = subtype;
        ObjectSizeX[index] = (int)(size_x * BLOCK_DEFAULT_SIZE * 100);
        ObjectSizeY[index] = (int)(size_y * BLOCK_DEFAULT_SIZE * 100);

        ObjectAI[index] = 0;
        ObjectVelY[index] = 0;
    }
    else
    {
        fprintf(stderr, "ObjectCreate - Could not create object %d %d at %d %d! (index %d)", type, subtype, (int)x, (int)y, index);
    }

    return index;
}

void ObjectClearAll()
{
    for(int i = 0; i < OBJECT_MAX; ++i)
    {
        ObjectX[i] = std::numeric_limits<int>::min();
        ObjectY[i] = std::numeric_limits<int>::min();
        ObjectSizeX[i] = std::numeric_limits<int>::min();
        ObjectSizeY[i] = std::numeric_limits<int>::min();

        //set a invalid type so it is ignored in all other functions
        ObjectType[i] = (EObjectType)std::numeric_limits<int>::min();
        ObjectSubType[i] = EObjectSubType::NONE;

        ObjectVelY[i] = 0;
        ObjectAI[i] = 0;
    }

    ObjectCount = 0;
}
