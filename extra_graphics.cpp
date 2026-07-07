
#include "global_vars.h"
#include "main.h"
#include "extra_graphics.h"

void HandleExtraGraphics()
{
    // グラ
    for (t = 0; t < EXTRA_GRAPHIC_MAX; t++)
    {
        xx[0] = ExtraGraphicX[t] - fx;
        xx[1] = ExtraGraphicY[t] - fy;
        xx[2] = ExtraGraphicSizeX[t] / 100;
        xx[3] = ExtraGraphicSizeY[t] / 100;
        if (ExtraGraphicTimer[t] >= 0)
            ExtraGraphicTimer[t]--;
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax && xx[1] + xx[3] * 100 >= -10 - 8000 && xx[3] <= fymax && ExtraGraphicTimer[t] >= 0)
        {
            ExtraGraphicX[t] += ExtraGraphicVelX[t];
            ExtraGraphicY[t] += ExtraGraphicVelY[t];
            ExtraGraphicVelX[t] += ExtraGraphicFrictionX[t];
            ExtraGraphicVelY[t] += ExtraGraphicFrictionY[t];
        }
        else
        {
            ExtraGraphicX[t] = -9000000;
        }

    } // emax
}

void RenderExtraGraphics()
{
    // グラ //+KZ: Seems this is about non-entity graphics
    for (t = 0; t < EXTRA_GRAPHIC_MAX; t++)
    {
        xx[0] = ExtraGraphicX[t] - fx;
        xx[1] = ExtraGraphicY[t] - fy;
        xx[2] = ExtraGraphicSizeX[t] / 100;
        xx[3] = ExtraGraphicSizeY[t] / 100;
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax && xx[1] + xx[3] * 100 >= -10 - 8000 && xx[3] <= fymax)
        {

            // コイン (Coin)
            if (ExtraGraphicType[t] == EExtraGraphicType::COIN)
                drawimage(Sliced_GFX[0][2], xx[0] / 100, xx[1] / 100);

            // ブロックの破片 (Block fragments)
            if (ExtraGraphicType[t] == EExtraGraphicType::BLOCK_FRAGMENT)
            {
                if (StageColor == ELevelType::OVERWORLD || StageColor == ELevelType::SKY || StageColor == ELevelType::ICY || StageColor == ELevelType::KAIZO_SYOBON_UNKNOWN)
                    setcolor(9 * 16, 6 * 16, 3 * 16);
                if (StageColor == ELevelType::UNDERGROUND)
                    setcolor(0, 120, 160);
                if (StageColor == ELevelType::CASTLE)
                    setcolor(192, 192, 192);

                fillarc(xx[0] / 100, xx[1] / 100, 7, 7);
                setcolor(0, 0, 0);
                drawarc(xx[0] / 100, xx[1] / 100, 7, 7);
            }
            // リフトの破片 (Lift fragments)
            if (ExtraGraphicType[t] == EExtraGraphicType::LIFT_FRAGMENT_LEFT ||
                ExtraGraphicType[t] == EExtraGraphicType::LIFT_FRAGMENT_RIGHT)
            {
                if (ExtraGraphicType[t] == EExtraGraphicType::LIFT_FRAGMENT_RIGHT)
                    mirror = 1;
                drawimage(Sliced_GFX[0][5], xx[0] / 100, xx[1] / 100);
                mirror = 0;
            }
            // ポール (pole)
            if (ExtraGraphicType[t] == EExtraGraphicType::GOAL_POLE)
            {
                setc1();
                fillrect((xx[0]) / 100 + 10, (xx[1]) / 100, 10, xx[3]);
                setc0();
                drawrect((xx[0]) / 100 + 10, (xx[1]) / 100, 10, xx[3]);
                setcolor(250, 250, 0);
                fillarc((xx[0]) / 100 + 15 - 1, (xx[1]) / 100, 10, 10);
                setc0();
                drawarc((xx[0]) / 100 + 15 - 1, (xx[1]) / 100, 10, 10);
            } // 4

            if(currentGame != ESyobonActionGame::SYOBON_ACTION_1_AND_2)
            {
                if (ExtraGraphicType[t] == EExtraGraphicType::SA3_MUSHROOM)
                {
                    drawimage(Sliced_GFX[1][2], (ExtraGraphicX[t] - fx) / 100, (ExtraGraphicY[t] - fy) / 100);
                }
            }
        }
    }
}

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

            if (BackgroundType[t] != EDecorationType::CASTLE)
            {
                //+KZ: so.. this draws the broken grass in 3-1, did it even work correctly in any syobon action version?
                //  Changed code to use custom sprites in SyobonKZ
                switch (StageColor)
                {
                case ELevelType::ICY:
                    if(BackgroundType[t] == EDecorationType::GRASS)
                    {
                        drawimage(Sliced_GFX[31][4], xx[0] / 100, xx[1] / 100);
                    }
                    else if(BackgroundType[t] == EDecorationType::CLOUD)
                    {
                        drawimage(Sliced_GFX[32][4], xx[0] / 100, xx[1] / 100);
                    }
                    break;
                
                case ELevelType::OVERWORLD:
                case ELevelType::UNDERGROUND:
                case ELevelType::SKY:
                case ELevelType::CASTLE:
                case ELevelType::KAIZO_SYOBON_UNKNOWN:
                    //Original code is like this
                    drawimage(Sliced_GFX[(int)BackgroundType[t]][4],
                            xx[0] / 100, xx[1] / 100);
                    break;
                }
            }
            else
            {
                drawimage(Sliced_GFX[(int)EDecorationType::CASTLE][4],
                          xx[0] / 100 - 5, xx[1] / 100);
            }

            // 51
            if (BackgroundType[t] == EDecorationType::TEXT_51)
            {
                DrawFormatString(xx[0] / 100,
                                 xx[1] / 100,
                                 GetColor(255, 255, 255), "51");
            }

            if (BackgroundType[t] == EDecorationType::TEXT_GAME_CLEAR)
                DrawFormatString(xx[0] / 100,
                                 xx[1] / 100,
                                 GetColor(255, 255,
                                          255),
                                 "ゲームクリアー");
            if (BackgroundType[t] == EDecorationType::TEXT_THANKS_FOR_PLAYING)
                DrawFormatString(xx[0] / 100,
                                 xx[1] / 100,
                                 GetColor(255, 255,
                                          255),
                                 "プレイしてくれてありがとー");
        }
    } // t
}

int CreateBackground(double PosX, double PosY, EDecorationType Type, int index)
{
    PosX *= BLOCK_DEFAULT_SIZE;
    PosY *= BLOCK_DEFAULT_SIZE;

    PosY -= 12; //stage() does -12 to blocks, lets be consistent

    //the game simulates floating point numbers
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
        BackgroundType[index] = (EDecorationType)std::numeric_limits<int>::max();
    }

    BackgroundCount = 0;
}

int CreateExtraGraphic(double PosX, double PosY, double VelX, double VelY, double FrictionX, double FrictionY, double SizeX, double SizeY,
    EExtraGraphicType Type, int Timer, int index)
{
    PosX *= BLOCK_DEFAULT_SIZE;
    PosY *= BLOCK_DEFAULT_SIZE;

    PosY -= 12; //stage() does -12 to blocks, lets be consistent

    //the game simulates floating point numbers
    //by multiplying all positions by 100
    PosX *= 100;
    PosY *= 100;

    if(index < 0)
    {
        //use ExtraGraphicCount to keep compat with CreateExtraGraphicLegacy()
        index = ExtraGraphicCount++;
        if(ExtraGraphicCount == EXTRA_GRAPHIC_MAX)
            ExtraGraphicCount = 0;
    }

    if(index >= 0 && index < EXTRA_GRAPHIC_MAX)
    {
        ExtraGraphicX[index] = PosX;
        ExtraGraphicY[index] = PosY;
        ExtraGraphicVelX[index] = (VelX * BLOCK_DEFAULT_SIZE * 100);
        ExtraGraphicVelY[index] = (VelY * BLOCK_DEFAULT_SIZE * 100);
        ExtraGraphicFrictionX[index] = (FrictionX * BLOCK_DEFAULT_SIZE * 100);
        ExtraGraphicFrictionY[index] = (FrictionY * BLOCK_DEFAULT_SIZE * 100);
        ExtraGraphicType[index] = Type;
        ExtraGraphicTimer[index] = Timer;
        ExtraGraphicSizeX[index] = (SizeX * BLOCK_DEFAULT_SIZE * 100);
        ExtraGraphicSizeY[index] = (SizeY * BLOCK_DEFAULT_SIZE * 100);
    }
    else
    {
        fprintf(stderr, "CreateExtraGraphic - Could not create extra graphic %d at %d %d! (index %d)", Type, (int)PosX, (int)PosY, index);
    }

    return index;
}

void ClearAllExtraGraphics()
{
    for(int index = 0; index < EXTRA_GRAPHIC_MAX; index++)
    {
        ExtraGraphicX[index] = std::numeric_limits<int>::min();
        ExtraGraphicY[index] = std::numeric_limits<int>::min();
        ExtraGraphicVelX[index] = 0;
        ExtraGraphicVelY[index] = 0;
        ExtraGraphicFrictionX[index] = 0;
        ExtraGraphicFrictionY[index] = 0;

        //game wont render a invalid type
        ExtraGraphicType[index] = (EExtraGraphicType)std::numeric_limits<int>::max();

        ExtraGraphicTimer[index] = 0;
        ExtraGraphicSizeX[index] = 0;
        ExtraGraphicSizeY[index] = 0;
    }

    ExtraGraphicCount = 0;
}

// グラ作成 (Graphic creation)
void CreateExtraGraphicLegacy(
    int PosX, //int xa
    int PosY, //int xb
    int VelX, //int xc
    int VelY, //int xd
    int FrictionX, //int xe
    int FrictionY, //int xf
    int SizeX, //int xnobia
	int SizeY, //int xnobib
    EExtraGraphicType Type, //int xgtype
    int Timer //int xtm
)
{

	ExtraGraphicX[ExtraGraphicCount] = PosX;
	ExtraGraphicY[ExtraGraphicCount] = PosY;
	ExtraGraphicVelX[ExtraGraphicCount] = VelX;
	ExtraGraphicVelY[ExtraGraphicCount] = VelY;
	ExtraGraphicFrictionX[ExtraGraphicCount] = FrictionX;
	ExtraGraphicFrictionY[ExtraGraphicCount] = FrictionY;
	ExtraGraphicType[ExtraGraphicCount] = Type;
	ExtraGraphicTimer[ExtraGraphicCount] = Timer;
	ExtraGraphicSizeX[ExtraGraphicCount] = SizeX;
	ExtraGraphicSizeY[ExtraGraphicCount] = SizeY;

	ExtraGraphicCount++;
	if (ExtraGraphicCount >= EXTRA_GRAPHIC_MAX)
		ExtraGraphicCount = 0;

} // eyobi
