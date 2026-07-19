#include "main.h"
#include "global_vars.h"
#include "loadg.h"
#include "blocks.h"

//ブロック
int BlockCount;
int BlockX[BLOCK_MAX], BlockY[BLOCK_MAX], BlockAITimer[BLOCK_MAX];
EBlockType BlockType[BLOCK_MAX];
int BlockItemCount[BLOCK_MAX];
EBlockSubType BlockSubType[BLOCK_MAX];

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
            if (LevelType == ELevelType::UNDERGROUND)
            {
                xx[9] = 30;
            }
            if (LevelType == ELevelType::CASTLE)
            {
                xx[9] = 60;
            }
            if (LevelType == ELevelType::ICY)
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
                    BlockType[t] == EBlockType::KAIZO_SYOBON_ITEM_BLOCK_105 ||
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

                if (
                    BlockType[t] == EBlockType::ITEM_BLOCK_POISON_OPEN ||
                    BlockType[t] == EBlockType::ITEM_BLOCK_COINS_OPEN ||
                    BlockType[t] == EBlockType::BRICK_BRITTLE && BlockSubType[t] == EBlockSubType::BRICK_BRITTLE_ITEM_BLOCK_OPEN ||
                    BlockType[t] == EBlockType::FIREBAR_GROW            
                )
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

            if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
            {
                switch(BlockType[t])
                {
                    case EBlockType::SA3_GRAY_SPIKE_LEFT:
                    case EBlockType::SA3_GRAY_SPIKE_RIGHT:
                        if(BlockType[t] == EBlockType::SA3_GRAY_SPIKE_LEFT)
                        {
                            DrawTurnGraphZ((BlockX[t] - fx) / 100, (BlockY[t] - fy) / 100, Main_GFX_KZ[2]);
                        }
                        else
                        {
                            DrawGraphZ((BlockX[t] - fx) / 100, (BlockY[t] - fy) / 100, Main_GFX_KZ[2]);
                        }
                        break;
                    case EBlockType::SA3_WHITE_SPIKE_DOWN:
                        DrawGraphZ((BlockX[t] - fx) / 100, (BlockY[t] - fy) / 100, Main_GFX_KZ[16]);
                        break;
                    case EBlockType::SA3_WHITE_SPIKE_UP:
                        SyobonKZDrawVertTurnGraph((BlockX[t] - fx) / 100, (BlockY[t] - fy) / 100, Main_GFX_KZ[16]);
                        break;
                    case EBlockType::SA3_BRICK_BRITTLE:
                        DrawGraphZ((BlockX[t] - fx) / 100, (BlockY[t] - fy) / 100, Main_GFX_KZ[17]);
                        break;
                    case EBlockType::SA3_ITEM_BLOCK_OPEN_OVERWORLD:
                        DrawGraphZ((BlockX[t] - fx) / 100, (BlockY[t] - fy) / 100, Sliced_GFX[3][1]);
                        break;
                    case EBlockType::BRICK_BRITTLE:
                        if(BlockSubType[t] == EBlockSubType::BRICK_BRITTLE_SA3_GROUND_TOP)
                        {
                            DrawGraphZ((BlockX[t] - fx) / 100, (BlockY[t] - fy) / 100, Sliced_GFX[xx[9] + 5 /* GROUND_TOP */][1]);
                        }
                        else if(BlockSubType[t] == EBlockSubType::BRICK_BRITTLE_SA3_GROUND_BOTTOM)
                        {
                            DrawGraphZ((BlockX[t] - fx) / 100, (BlockY[t] - fy) / 100, Sliced_GFX[xx[9] + 6 /* GROUND_BOTTOM */][1]);
                        }
                        break;
                    default:
                        break;
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
