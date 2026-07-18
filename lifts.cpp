
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
int LiftInteractType[LIFT_MAX], LiftMovementType[LIFT_MAX];
ELiftType LiftType[LIFT_MAX];
int LiftDirection[LIFT_MAX], LiftON[LIFT_MAX];
int LiftVelX[LIFT_MAX], LiftPlayerFatigueX[LIFT_MAX];

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
            // if (srtype[t]==1){xx[0]=600;}
            if (PlayerVelY > xx[1])
                xx[1] = PlayerVelY + 100;
            // xx[18]=0;

            LiftY[t] += LiftVelY[t];
            LiftVelY[t] += LiftFrictionY[t];
            // if (srf[t]>=500)srf[t]=0;

            // 動き (Movement)
            switch (LiftMovementType[t])
            {

            case 1:
                if (LiftON[t] == 1)
                    LiftFrictionY[t] = 60;
                break;

            case 2:
                /*
                if (sra[t]<=srmovep[t]-srmove[t])srmuki[t]=1;
                if (sra[t]>=srmovep[t]+srmove[t])srmuki[t]=0;
                */
                break;

            case 3:
                /*
                if (srb[t]<=srmovep[t]-srmove[t])srmuki[t]=1;
                if (srb[t]>=srmovep[t]+srmove[t])srmuki[t]=0;
                */
                break;

                /*
                case 4:
                if (srmove[t]==0){srmuki[t]=0;}else{srmuki[t]=1;}
                if (sra[t]-fx<-1100-src[t]){sra[t]=fymax+fx+scrollx;}
                if (sra[t]-fx>24000+scrollx){sra[t]=-1100-src[t]+fx;}
                break;
                */

            case 5:
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

            case 6:
                if (LiftON[t] == 1)
                    LiftFrictionY[t] = 40;
                break;

            case 7:
                break;

            } // sw

            // if (srtype[t]==1){sre[10]=300;sre[11]=300;}

            // 乗ったとき (When I got on)
            if (!(mztm >= 1 && mztype == 1 && actaon[3] == 1) && PlayerHealth >= 1)
            {
                if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY + PlayerSizeY < xx[9] + xx[1] && PlayerVelY >= -100)
                {
                    PlayerY = xx[9] - PlayerSizeY + 100;
                    // if (sracttype[t]!=7)PlayerGrounded=1;

                    if (LiftInteractType[t] == 1)
                    {
                        LiftVelY[10] = 900;
                        LiftVelY[11] = 900;
                    }

                    if (LiftType[t] != ELiftType::PILLAR_BOUNCY)
                    {
                        PlayerGrounded = 1;
                        PlayerVelY = 0;
                    }
                    else
                    {
                        // すべり (Slip)
                        // md=0;ObjectType=1;PlayerGrounded=1;
                        PlayerVelY = -800;
                    }

                    /*
                    md=0;
                    if ((sracttype[t]==1 || sracttype[t]==6) && sron[t]==1)mb+=sre[t];

                    if (sracttype[t]==2 || sracttype[t]==4){
                    if (srmuki[t]==0)ma-=srsok[t];
                    if (srmuki[t]==1)ma+=srsok[t];
                    }
                    */

                    // 落下 (Falling)
                    if ((LiftMovementType[t] == 1) && LiftON[t] == 0)
                        LiftON[t] = 1;

                    if (LiftMovementType[t] == 1 && LiftON[t] == 1 || LiftMovementType[t] == 3 || LiftMovementType[t] == 5)
                    {
                        PlayerY += LiftVelY[t];
                        // if (srmuki[t]==0)
                        // if (srf[t]<0)
                        // if (srmuki[t]==1)
                        // if (srf[t]>0)
                        // mb+=srsok[t];
                    }

                    if (LiftMovementType[t] == 7)
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
                    // if (srtype[t]==1){md=-600;mb-=610;PlayerHealth-=1;if (mmutekion!=1)mmutekitm=40;}
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
                    } // && mb+mnobib>xx[9]-1000 && mb+mnobib<xx[9]+xx[1]+2000)
                    if (LiftON[t] == 1)
                    {
                        LiftFrictionY[t] = 60;
                        LiftY[t] += LiftVelY[t];
                    }
                }
                // トゲ(下) (Spikes (below))
                if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0] && PlayerY > xx[9] - xx[1] / 2 && PlayerY < xx[9] + xx[1] / 2)
                {
                    if (LiftInteractType[t] == 2)
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
                if (LiftMovementType[t] == 6)
                {
                    if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0])
                    {
                        LiftON[t] = 1;
                    }
                }

            } //!

            /*
            //ジャンプ台
            if (sracttype[t]==7){
            if (ma+mnobia>xx[8]+xx[0] && ma<xx[8]+xx[12]-xx[0] && mb+mnobib>xx[9]+xx[1]/2 && mb+mnobib<xx[9]+xx[1]*3/2 && md>=-100){
            if (actaon[2]!=1){md=-600;mb-=810;}
            if (actaon[2]==1){mb-=400;md=-1400;mjumptm=10;}
            }}
            */

            if (LiftMovementType[t] == 2 || LiftMovementType[t] == 4)
            {
                if (LiftDirection[t] == 0)
                    LiftX[t] -= LiftVelX[t];
                if (LiftDirection[t] == 1)
                    LiftX[t] += LiftVelX[t];
            }
            if (LiftMovementType[t] == 3 || LiftMovementType[t] == 5)
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

int CreateLift(double PosX, double PosY, double Width, double VelY, ELiftType Type, int MovementType ,int index)
{
    PosX *= BLOCK_DEFAULT_SIZE;
    PosY *= BLOCK_DEFAULT_SIZE;

    PosY -= 12; //stage() does -12

    //the game simulates floating point numbers
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
        LiftSizeX[index] = GAME_X_POS_TO_DOUBLE(Width);
        LiftMovementType[index] = MovementType;

        LiftInteractType[index] = 0;
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
        LiftInteractType[i] = 0;
        LiftMovementType[i] = 0;
    }

    LiftCount = 0;
}
