
#include "global_vars.h"
#include "lifts.h"
#include "main.h"
#include "loadg.h"
#include "effects.h"
#include "player.h"
#include "entities.h"

//リフト
int LiftCount;
int LiftX[LIFT_MAX], LiftY[LIFT_MAX], LiftSizeX[LIFT_MAX], LiftVelY[LIFT_MAX], LiftFrictionY[LIFT_MAX];
ELiftInteractType LiftInteractType[LIFT_MAX];
ELiftMovementType LiftMovementType[LIFT_MAX];
ELiftType LiftType[LIFT_MAX];
int LiftDirection[LIFT_MAX], LiftON[LIFT_MAX];
int LiftVelX[LIFT_MAX], LiftPlayerFatigueX[LIFT_MAX];

//from SA: All Stars
int LiftTimer[LIFT_MAX];
int LiftTimerMax[LIFT_MAX];
bool LiftTouchSpeedUp[LIFT_MAX];

void HandleLifts()
{
    // リフト (Lift)
    for (t = 0; t < LIFT_MAX; t++)
    {
        xx[10] = LiftX[t];
        xx[11] = LiftY[t];
        xx[12] = LiftSizeX[t];
        //xx[13] = srd[t]; //+KZ value is never read
        xx[8] = xx[10] - fx;
        xx[9] = xx[11] - fy;
        if (xx[8] + xx[12] >= -10 - 12000 && xx[8] <= fxmax + 12100)
        {
            xx[0] = 500;
            xx[1] = 1200;
            xx[2] = 1000;
            xx[7] = 2000;
            if (PlayerVelY >= 100)
            {
                xx[1] = 900 + PlayerVelY;
            }

            if (PlayerVelY > xx[1])
                xx[1] = PlayerVelY + 100;

            LiftY[t] += LiftVelY[t];
            LiftVelY[t] += LiftFrictionY[t];

            // 動き (Movement)
            switch (LiftMovementType[t])
            {

            case ELiftMovementType::FALL:
                if (LiftON[t] == 1)
                    LiftFrictionY[t] = 60;
                break;

            case ELiftMovementType::SA_ALL_STARS_HORIZONTAL_MOVEMENT:
                //from SA: All Stars
                if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                {
                    LiftTimer[t]++;
					if (LiftTimer[t] == LiftTimerMax[t])
					{
						LiftTimer[t] = 0;
						LiftDirection[t] ^= 1;
					}
					if (LiftDirection[t] == 0)
					{
						LiftX[t] -= LiftVelX[t];
					}
					else
					{
						LiftX[t] += LiftVelX[t];
					}
					break;
                }
                break;

            case ELiftMovementType::SA_ALL_STARS_VERTICAL_MOVEMENT:
                //from SA: All Stars
                if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                {
                    LiftTimer[t]++;
					if (LiftTimer[t] == LiftTimerMax[t])
					{
						LiftTimer[t] = 0;
						LiftDirection[t] ^= 1;
					}
					if (LiftDirection[t] == 0)
					{
						LiftY[t] -= LiftVelX[t];
					}
					else
					{
						LiftY[t] += LiftVelX[t];
					}
					break;
                }
                break;

            case ELiftMovementType::WRAP_VERTICALLY:
                if (LiftPlayerFatigueX[t] == 0)
                {
                    LiftDirection[t] = 0;
                }
                else
                {
                    LiftDirection[t] = 1;
                }
                if (LiftY[t] - fy < -2100)
                {
                    LiftY[t] = fymax + fy + scrolly + 2000;
                }
                if (LiftY[t] - fy > fymax + scrolly + 2000)
                {
                    LiftY[t] = -2100 + fy;
                }
                break;

            case ELiftMovementType::FALL_UNUSED:
                if (LiftON[t] == 1)
                    LiftFrictionY[t] = 40;
                break;

            case ELiftMovementType::BOUNCY_UNUSED:
                break;

            default:
                break;
            } // sw

            // 乗ったとき (When I got on)
            if (!(mztm >= 1 && mztype == 1 && actaon[3] == 1) && PlayerHealth >= 1)
            {
                if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY + PlayerSizeY < xx[9] + xx[1] && PlayerVelY >= -100)
                {
                    PlayerY = xx[9] - PlayerSizeY + 100;

                    if (LiftInteractType[t] == ELiftInteractType::TRIGGER_VERTICAL_SPEEDUP)
                    {
                        if(currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                        {
                            LiftVelY[10] = 900;
                            LiftVelY[11] = 900;
                        }
                        else
                        {
                            for(int i = 0; i < LIFT_MAX; i++)
                            {
                                if(LiftTouchSpeedUp[i])
                                    LiftVelY[i] = 900;
                            }
                        }
                    }

                    if (LiftType[t] != ELiftType::PILLAR_BOUNCY)
                    {
                        PlayerGrounded = 1;
                        PlayerVelY = 0;
                    }
                    else
                    {
                        // すべり (Slip)
                        PlayerVelY = -800;
                    }

                    // 落下 (Falling)
                    if ((LiftMovementType[t] == ELiftMovementType::FALL) && LiftON[t] == 0)
                        LiftON[t] = 1;

                    if (
                        LiftMovementType[t] == ELiftMovementType::FALL && LiftON[t] == 1 ||
                        LiftMovementType[t] == ELiftMovementType::SA_ALL_STARS_VERTICAL_MOVEMENT ||
                        LiftMovementType[t] == ELiftMovementType::WRAP_VERTICALLY
                    )
                    {
                        PlayerY += LiftVelY[t];
                    }

                    //From Syobon Action: All Stars
                    if (currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                    {
                        if(LiftMovementType[t] == ELiftMovementType::SA_ALL_STARS_HORIZONTAL_MOVEMENT)
                        {
                            if (LiftDirection[t] != 0)
                            {
                                PlayerX += LiftVelX[t] + 100;
                            }
                            else
                            {
                                PlayerX -= LiftVelX[t] + 100;
                            }
                        }
                    }

                    if (LiftMovementType[t] == ELiftMovementType::BOUNCY_UNUSED)
                    {
                        if (actaon[2] != 1)
                        {
                            PlayerVelY = -600;
                            PlayerY -= 810;
                        }
                        if (actaon[2] == 1)
                        {
                            PlayerY -= 400;
                            PlayerVelY = -1400;
                            mjumptm = 10;
                        }
                    }
                    // 特殊 (Special)
                    if (LiftType[t] == ELiftType::BREAKING)
                    {
                        PlaySound(Sounds[3]);
                        CreateEffectLegacy(LiftX[t] + 200,
                              LiftY[t] - 1000,
                              -240, -1400, 0, 160, 4500, 4500, EEffectType::LIFT_FRAGMENT_LEFT, 120);
                        CreateEffectLegacy(LiftX[t] + 4500 -
                                  200,
                              LiftY[t] - 1000,
                              240, -1400, 0, 160, 4500, 4500, EEffectType::LIFT_FRAGMENT_RIGHT, 120);
                        LiftX[t] = -70000000;
                    }

                    if (LiftType[t] == ELiftType::PUSH_LEFT)
                    {
                        PlayerVelX = -2400;
                        LiftPlayerFatigueX[t] += 1;
                        if (LiftPlayerFatigueX[t] >= 100)
                        {
                            PlayerHealth = 0;
                            PlayerMessageType = 53;
                            PlayerMessageTimer = 30;
                            LiftPlayerFatigueX[t] = -5000;
                        }
                    }

                    if (LiftType[t] == ELiftType::PUSH_RIGHT)
                    {
                        PlayerVelX = 2400;
                        LiftPlayerFatigueX[t] += 1;
                        if (LiftPlayerFatigueX[t] >= 100)
                        {
                            PlayerHealth = 0;
                            PlayerMessageType = 53;
                            PlayerMessageTimer = 30;
                            LiftPlayerFatigueX[t] = -5000;
                        }
                    }
                } // 判定内 (Within the judgment)

                // 疲れ初期化 (Fatigue reset)
                if ((LiftType[t] == ELiftType::PUSH_LEFT || LiftType[t] == ELiftType::PUSH_RIGHT) && PlayerVelX != -2400 && LiftPlayerFatigueX[t] > 0)
                {
                    LiftPlayerFatigueX[t]--;
                }

                if (LiftType[t] == ELiftType::PILLAR_FALL)
                {
                    if (PlayerX + PlayerSizeX >
                            xx[8] + xx[0] - 2000 &&
                        PlayerX < xx[8] + xx[12] - xx[0])
                    {
                        LiftON[t] = 1;
                    }
                    if (LiftON[t] == 1)
                    {
                        LiftFrictionY[t] = 60;
                        LiftY[t] += LiftVelY[t];
                    }
                }
                // トゲ(下) (Spikes (below))
                if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0] && PlayerY > xx[9] - xx[1] / 2 && PlayerY < xx[9] + xx[1] / 2)
                {
                    if (LiftInteractType[t] == ELiftInteractType::SPIKES_BELOW)
                    {
                        if (PlayerVelY < 0)
                        {
                            PlayerVelY = -PlayerVelY;
                        }
                        PlayerY += 110;
                        if (PlayerNoDamageTimer <= 0)
                            PlayerHealth -= 1;
                        if (PlayerInvincibleON != 1)
                            PlayerNoDamageTimer = 40;
                    }
                }
                // 落下 (Falling)
                if (LiftMovementType[t] == ELiftMovementType::FALL_UNUSED && PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0])
                {
                    LiftON[t] = 1;
                }

            } //!

            if (LiftMovementType[t] == ELiftMovementType::SA_ALL_STARS_HORIZONTAL_MOVEMENT || LiftMovementType[t] == ELiftMovementType::HORIZONTAL_MOVEMENT_UNUSED)
            {
                if (LiftDirection[t] == 0)
                    LiftX[t] -= LiftVelX[t];
                if (LiftDirection[t] == 1)
                    LiftX[t] += LiftVelX[t];
            }
            if (LiftMovementType[t] == ELiftMovementType::SA_ALL_STARS_VERTICAL_MOVEMENT || LiftMovementType[t] == ELiftMovementType::WRAP_VERTICALLY)
            {
                if (LiftDirection[t] == 0)
                    LiftY[t] -= LiftVelX[t];
                if (LiftDirection[t] == 1)
                    LiftY[t] += LiftVelX[t];
            }
            // 敵キャラ適用 (Applies to enemy characters)
            for (tt = 0; tt < ENEMY_MAX; tt++)
            {
                if (EnemyMovementType[tt] == 1)
                {
                    if (EnemyX[tt] + EnemySizeX[tt] - fx > xx[8] + xx[0] && EnemyX[tt] - fx < xx[8] + xx[12] - xx[0] && EnemyY[tt] + EnemySizeY[tt] > xx[11] - 100 && EnemyY[tt] + EnemySizeY[tt] < xx[11] + xx[1] + 500 && EnemyVelY[tt] >= -100)
                    {
                        EnemyY[tt] = xx[9] - EnemySizeY[tt] + 100;
                        EnemyVelY[tt] = 0;
                        EnemyGrounded[tt] = 1;
                    }
                }
            }
        }
    } // リフト (Lift)
}

void RenderLifts()
{
    // リフト (lift)
    for (t = 0; t < LIFT_MAX; t++)
    {
        xx[0] = LiftX[t] - fx;
        xx[1] = LiftY[t] - fy;
        if (xx[0] + LiftSizeX[t] >= -10 && xx[1] <= fxmax + 12100 && LiftSizeX[t] / 100 >= 1)
        {
            xx[2] = 14;
            if (LiftType[t] == ELiftType::BREAKING)
            {
                xx[2] = 12;
            }

            if (LiftType[t] < ELiftType::PILLAR /* +KZ: it was <= 9 */ || (int)LiftType[t] >= 20)
            {
                setcolor(220, 220, 0);
                if (LiftType[t] == ELiftType::PUSH_LEFT || LiftType[t] == ELiftType::PUSH_RIGHT)
                {
                    setcolor(0, 220, 0);
                }
                if (LiftType[t] == ELiftType::GRAY)
                {
                    setcolor(180, 180, 180);
                }
                fillrect((LiftX[t] - fx) / 100,
                         (LiftY[t] - fy) / 100, LiftSizeX[t] / 100, xx[2]);

                setcolor(180, 180, 0);
                if (LiftType[t] == ELiftType::PUSH_LEFT || LiftType[t] == ELiftType::PUSH_RIGHT)
                {
                    setcolor(0, 180, 0);
                }
                if (LiftType[t] == ELiftType::GRAY)
                {
                    setcolor(150, 150, 150);
                }
                drawrect((LiftX[t] - fx) / 100,
                         (LiftY[t] - fy) / 100, LiftSizeX[t] / 100, xx[2]);
            }
            else if (LiftType[t] < ELiftType::PILLAR_BRICKS /* +KZ: it was <= 14 */)
            {
                if (LiftSizeX[t] >= 5000)
                {
                    setcolor(0, 200, 0);
                    fillrect((LiftX[t] - fx) / 100,
                             (LiftY[t] - fy) / 100, LiftSizeX[t] / 100, 30);
                    setcolor(0, 160, 0);
                    drawrect((LiftX[t] - fx) / 100,
                             (LiftY[t] - fy) / 100, LiftSizeX[t] / 100, 30);

                    setcolor(180, 120, 60);
                    fillrect((LiftX[t] - fx) / 100 +
                                 20,
                             (LiftY[t] - fy) / 100 +
                                 30,
                             LiftSizeX[t] / 100 - 40, 480); //+KZ: 480 is SYOBONKZ_SCREEN_SIZE_X, but here is used as Y?
                    setcolor(100, 80, 20);
                    drawrect((LiftX[t] - fx) / 100 +
                                 20,
                             (LiftY[t] - fy) / 100 +
                                 30,
                             LiftSizeX[t] / 100 - 40, 480); //+KZ: 480 is SYOBONKZ_SCREEN_SIZE_X, but here is used as Y?
                }
            }
            if (LiftType[t] == ELiftType::PILLAR_BRICKS)
            {
                for (t2 = 0; t2 <= 2; t2++)
                {
                    //xx[6] = 1 + 0; //+KZ: this is useless, and xx[6] is set to other value after RenderLifts(), it is safe to remove
                    drawimage(Sliced_GFX[1][1],
                              (LiftX[t] - fx) / 100 +
                                  t2 * 29,
                              (LiftY[t] - fy) / 100);
                }
            } // 15
        }
    } // t
}

int CreateLift(double PosX, double PosY, double Width, double VelY, ELiftType Type, ELiftMovementType MovementType ,int index)
{
    PosX *= BLOCK_DEFAULT_SIZE;
    PosY *= BLOCK_DEFAULT_SIZE;

    PosY -= 12; //stage() does -12

    //the game uses fixed point numbers
    //by multiplying all positions by 100
    PosX *= 100;
    PosY *= 100;

    if(index < 0)
    {
        //use BlockCount to keep compat with BlockCreateLegacy()
        index = LiftCount++;
        if(LiftCount == LIFT_MAX)
            LiftCount = 0;
    }

    if(index >= 0 && index < LIFT_MAX)
    {
        LiftX[index] = (int)PosX;
        LiftY[index] = (int)PosY;
        LiftType[index] = Type;
        LiftVelY[index] = VelY;
        LiftSizeX[index] = DOUBLE_TO_GAME_X_POS(Width);
        LiftMovementType[index] = MovementType;

        LiftInteractType[index] = ELiftInteractType::NONE;
        LiftVelX[index] = 0;
        LiftDirection[index] = 0;
        LiftFrictionY[index] = 0;
        LiftON[index] = 0;
        LiftPlayerFatigueX[index] = 0;
    }
    else
    {
        fprintf(stderr, "CreateLift - Could not create lift %d at %d %d! (index %d)", Type, (int)PosX, (int)PosY, index);
    }

    return index;
}

void ClearAllLifts()
{
    for (int i = 0; i < LIFT_MAX; i++)
    {
        LiftX[i] = std::numeric_limits<int>::min();
		LiftY[i] = std::numeric_limits<int>::min();
		LiftSizeX[i] = 1;
        LiftVelX[i] = 0;
		LiftVelY[i] = 0;
		LiftFrictionY[i] = 0;
		LiftDirection[i] = 0;
		LiftON[i] = 0;
		LiftPlayerFatigueX[i] = 0;
		LiftType[i] = ELiftType::YELLOW;
        LiftInteractType[i] = ELiftInteractType::NONE;
        LiftMovementType[i] = ELiftMovementType::NONE;

        LiftTimer[i] = 0;
        LiftTimerMax[i] = 0;
        LiftTouchSpeedUp[i] = false;
    }

    LiftCount = 0;
}
