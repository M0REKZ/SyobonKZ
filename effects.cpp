
#include "global_vars.h"
#include "main.h"
#include "effects.h"
#include "loadg.h"

//効果を持たないグラ
int EffectCount;
int EffectX[EFFECT_MAX], EffectY[EFFECT_MAX], EffectSizeX[EFFECT_MAX], EffectSizeY[EFFECT_MAX], EffectVelX[EFFECT_MAX], EffectVelY[EFFECT_MAX];
int EffectFrictionX[EFFECT_MAX], EffectFrictionY[EFFECT_MAX], EffectTimer[EFFECT_MAX];
EEffectType EffectType[EFFECT_MAX];

void HandleEffects()
{
    // グラ
    for (t = 0; t < EFFECT_MAX; t++)
    {
        xx[0] = EffectX[t] - fx;
        xx[1] = EffectY[t] - fy;
        xx[2] = EffectSizeX[t] / 100;
        xx[3] = EffectSizeY[t] / 100;
        if (EffectTimer[t] >= 0)
            EffectTimer[t]--;
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax && xx[1] + xx[3] * 100 >= -10 - 8000 && xx[3] <= fymax && EffectTimer[t] >= 0)
        {
            EffectX[t] += EffectVelX[t];
            EffectY[t] += EffectVelY[t];
            EffectVelX[t] += EffectFrictionX[t];
            EffectVelY[t] += EffectFrictionY[t];
        }
        else
        {
            EffectX[t] = -9000000;
        }

    } // emax
}

void RenderEffects()
{
    // グラ //+KZ: Seems this is about non-entity graphics
    for (t = 0; t < EFFECT_MAX; t++)
    {
        xx[0] = EffectX[t] - fx;
        xx[1] = EffectY[t] - fy;
        xx[2] = EffectSizeX[t] / 100;
        xx[3] = EffectSizeY[t] / 100;
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax && xx[1] + xx[3] * 100 >= -10 - 8000 && xx[3] <= fymax)
        {

            // コイン (Coin)
            if (EffectType[t] == EEffectType::COIN)
                drawimage(Sliced_GFX[0][2], xx[0] / 100, xx[1] / 100);

            // ブロックの破片 (Block fragments)
            if (EffectType[t] == EEffectType::BLOCK_FRAGMENT)
            {
                if (LevelType == ELevelType::OVERWORLD || LevelType == ELevelType::SKY || LevelType == ELevelType::ICY || LevelType == ELevelType::KAIZO_SYOBON_OVERWORLD_SLIP)
                    setcolor(9 * 16, 6 * 16, 3 * 16);
                if (LevelType == ELevelType::UNDERGROUND)
                    setcolor(0, 120, 160);
                if (LevelType == ELevelType::CASTLE)
                    setcolor(192, 192, 192);

                fillarc(xx[0] / 100, xx[1] / 100, 7, 7);
                setcolor(0, 0, 0);
                drawarc(xx[0] / 100, xx[1] / 100, 7, 7);
            }
            // リフトの破片 (Lift fragments)
            if (EffectType[t] == EEffectType::LIFT_FRAGMENT_LEFT ||
                EffectType[t] == EEffectType::LIFT_FRAGMENT_RIGHT)
            {
                if (EffectType[t] == EEffectType::LIFT_FRAGMENT_RIGHT)
                    mirror = 1;
                drawimage(Sliced_GFX[0][5], xx[0] / 100, xx[1] / 100);
                mirror = 0;
            }
            // ポール (pole)
            if (EffectType[t] == EEffectType::GOAL_POLE)
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

            if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
            {
                if (EffectType[t] == EEffectType::SA3_MUSHROOM)
                {
                    drawimage(Sliced_GFX[1][2], (EffectX[t] - fx) / 100, (EffectY[t] - fy) / 100);
                }
            }
        }
    }
}

int CreateEffect(double PosX, double PosY, double VelX, double VelY, double FrictionX, double FrictionY, double SizeX, double SizeY,
    EEffectType Type, int Timer, int index)
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
        //use EffectCount to keep compat with CreateEffectLegacy()
        index = EffectCount++;
        if(EffectCount == EFFECT_MAX)
            EffectCount = 0;
    }

    if(index >= 0 && index < EFFECT_MAX)
    {
        EffectX[index] = PosX;
        EffectY[index] = PosY;
        EffectVelX[index] = (VelX * BLOCK_DEFAULT_SIZE * 100);
        EffectVelY[index] = (VelY * BLOCK_DEFAULT_SIZE * 100);
        EffectFrictionX[index] = (FrictionX * BLOCK_DEFAULT_SIZE * 100);
        EffectFrictionY[index] = (FrictionY * BLOCK_DEFAULT_SIZE * 100);
        EffectType[index] = Type;
        EffectTimer[index] = Timer;
        EffectSizeX[index] = (SizeX * BLOCK_DEFAULT_SIZE * 100);
        EffectSizeY[index] = (SizeY * BLOCK_DEFAULT_SIZE * 100);
    }
    else
    {
        fprintf(stderr, "CreateEffect - Could not create extra graphic %d at %d %d! (index %d)", Type, (int)PosX, (int)PosY, index);
    }

    return index;
}

void ClearAllEffects()
{
    for(int index = 0; index < EFFECT_MAX; index++)
    {
        EffectX[index] = std::numeric_limits<int>::min();
        EffectY[index] = std::numeric_limits<int>::min();
        EffectVelX[index] = 0;
        EffectVelY[index] = 0;
        EffectFrictionX[index] = 0;
        EffectFrictionY[index] = 0;

        //game wont render a invalid type
        EffectType[index] = (EEffectType)std::numeric_limits<int>::max();

        EffectTimer[index] = 0;
        EffectSizeX[index] = 0;
        EffectSizeY[index] = 0;
    }

    EffectCount = 0;
}

// グラ作成 (Graphic creation)
void CreateEffectLegacy(
    int PosX, //int xa
    int PosY, //int xb
    int VelX, //int xc
    int VelY, //int xd
    int FrictionX, //int xe
    int FrictionY, //int xf
    int SizeX, //int xnobia
	int SizeY, //int xnobib
    EEffectType Type, //int xgtype
    int Timer //int xtm
)
{

	EffectX[EffectCount] = PosX;
	EffectY[EffectCount] = PosY;
	EffectVelX[EffectCount] = VelX;
	EffectVelY[EffectCount] = VelY;
	EffectFrictionX[EffectCount] = FrictionX;
	EffectFrictionY[EffectCount] = FrictionY;
	EffectType[EffectCount] = Type;
	EffectTimer[EffectCount] = Timer;
	EffectSizeX[EffectCount] = SizeX;
	EffectSizeY[EffectCount] = SizeY;

	EffectCount++;
	if (EffectCount >= EFFECT_MAX)
		EffectCount = 0;

} // eyobi
