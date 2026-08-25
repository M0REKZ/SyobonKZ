#include "level_enums.hpp"
#include "global_vars.h"
#include "loadg.h"
#include "main.h"
#include "backgrounds.h"

//背景
int BackgroundCount;
int BackgroundX[BACKGROUND_MAX], BackgroundY[BACKGROUND_MAX];
EBackgroundType BackgroundType[BACKGROUND_MAX];
//+KZ: value is set but never used
//int BackgroundWidth[BACKGROUND_MAX], BackgroundHeight[BACKGROUND_MAX];

void RenderBackground()
{
    // 背景 (Background)
    for (t = 0; t < BACKGROUND_MAX; t++)
    {
        xx[0] = BackgroundX[t] - fx;
        xx[1] = BackgroundY[t] - fy;
        //+KZ: added some checks because this gets out of bounds in level 1-4
        //+KZ later: ....wait this code is useless, we set xx[2] and xx[3] just after this
        /*if (ntype[t] < nmax)
        {
            xx[2] = BackgroundWidth[ntype[t]] * 100;
            xx[3] = BackgroundHeight[ntype[t]] * 100;
        }*/
        xx[2] = 16000;
        xx[3] = 16000;

        if (xx[0] + xx[2] >= -10 && xx[0] <= fxmax && xx[1] + xx[3] >= -10 && xx[3] <= fymax)
        {

            if (BackgroundType[t] != EBackgroundType::CASTLE)
            {
                //+KZ: so.. this draws the broken grass in 3-1, did it even work correctly in any syobon action version?
                //  Changed code to use custom sprites in SyobonKZ
                switch (LevelType)
                {
                case ELevelType::ICY:
                    if(BackgroundType[t] == EBackgroundType::GRASS)
                    {
                        drawimage(Sliced_GFX_KZ[0], xx[0] / 100, xx[1] / 100);
                    }
                    else if(BackgroundType[t] == EBackgroundType::CLOUD)
                    {
                        drawimage(Sliced_GFX_KZ[1], xx[0] / 100, xx[1] / 100);
                    }
                    break;
                
                case ELevelType::OVERWORLD:
                case ELevelType::UNDERGROUND:
                case ELevelType::SKY:
                case ELevelType::CASTLE:
                case ELevelType::KAIZO_SYOBON_OVERWORLD_SLIP:
                    //Original code is like this
                    drawimage(Sliced_GFX[(int)BackgroundType[t]][4],
                            xx[0] / 100, xx[1] / 100);
                    break;
                }
            }
            else
            {
                drawimage(Sliced_GFX[(int)EBackgroundType::CASTLE][4],
                          xx[0] / 100 - 5, xx[1] / 100);
            }

            // 51
            if (BackgroundType[t] == EBackgroundType::TEXT_51)
            {
                DrawFormatString(xx[0] / 100,
                                 xx[1] / 100,
                                 GetColor(255, 255, 255), "51");
            }

            if (BackgroundType[t] == EBackgroundType::TEXT_GAME_CLEAR)
                DrawFormatString(xx[0] / 100,
                                 xx[1] / 100,
                                 GetColor(255, 255,
                                          255),
                                 "ゲームクリアー");
            if (BackgroundType[t] == EBackgroundType::TEXT_THANKS_FOR_PLAYING)
                DrawFormatString(xx[0] / 100,
                                 xx[1] / 100,
                                 GetColor(255, 255,
                                          255),
                                 "プレイしてくれてありがとー");

            if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
            {
                switch(BackgroundType[t])
                {
                    case EBackgroundType::SA3_FAKE_GROUND_TOP:
                    {
                        int offset_index = 0;
                        if (LevelType == ELevelType::UNDERGROUND)
                        {
                            offset_index = 30;
                        }
                        if (LevelType == ELevelType::CASTLE)
                        {
                            offset_index = 60;
                        }
                        if (LevelType == ELevelType::ICY)
                        {
                            offset_index = 90;
                        }
                        DrawGraphZ((BackgroundX[t] - fx) / 100, (BackgroundY[t] - fy) / 100, Sliced_GFX[offset_index + 5 /* GROUND_TOP */][1]);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
    } // t
}

int CreateBackground(double PosX, double PosY, EBackgroundType Type, int index)
{
    PosX *= BLOCK_DEFAULT_SIZE;
    PosY *= BLOCK_DEFAULT_SIZE;

    PosY -= 12; //stage() does -12 to blocks, lets be consistent

    //the game uses fixed point numbers
    //by multiplying all positions by 100
    PosX *= 100;
    PosY *= 100;

    if(index < 0)
    {
        //use BackgroundCount to keep compat with legacy background creation
        index = BackgroundCount++;
        if(BackgroundCount == BACKGROUND_MAX)
            BackgroundCount = 0;
    }

    if(index >= 0 && index < BACKGROUND_MAX)
    {
        BackgroundX[index] = PosX;
        BackgroundY[index] = PosY;
        BackgroundType[index] = Type;
    }
    else
    {
        fprintf(stderr, "CreateBackground - Could not create extra graphic %d at %d %d! (index %d)", Type, (int)PosX, (int)PosY, index);
    }

    return index;
}

void ClearAllBackgrounds()
{
    for(int index = 0; index < BACKGROUND_MAX; index++)
    {
        BackgroundX[index] = std::numeric_limits<int>::min();
        BackgroundY[index] = std::numeric_limits<int>::min();
        
        //game wont render a invalid type
        BackgroundType[index] = (EBackgroundType)std::numeric_limits<int>::max();
    }

    BackgroundCount = 0;
}
