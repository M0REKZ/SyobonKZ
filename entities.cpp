#include <unordered_map>
#include "global_vars.h"
#include "main.h"
#include "entities.h"
#include "blocks.h"
#include "extra_graphics.h"

std::unordered_map<std::string, SDL_Surface *> apEnemyMessages;

void CreateEntityMessageCache()
{
    Uint32 temp_color = GetColor(255, 255, 255);

    #define ENEMY_MESSAGE(text) apEnemyMessages[text] = StringToSurface(text, temp_color, 16, DX_FONTTYPE_EDGE)

    ENEMY_MESSAGE("ヤッフー!!");
    ENEMY_MESSAGE("え?俺勝っちゃったの?");
    ENEMY_MESSAGE("貴様の死に場所はここだ!");
    ENEMY_MESSAGE("二度と会う事もないだろう");
    ENEMY_MESSAGE("俺、最強!!");
    ENEMY_MESSAGE("一昨日来やがれ!!");
    ENEMY_MESSAGE("漢に後退の二文字は無い!!");
    ENEMY_MESSAGE("ハッハァ!!");

    //ENEMY_MESSAGE("ヤッフー!!"];
    //ENEMY_MESSAGE("え?俺勝っちゃったの?"];
    //ENEMY_MESSAGE("貴様の死に場所はここだ!"];
    ENEMY_MESSAGE("身の程知らずが……");
    ENEMY_MESSAGE("油断が死を招く");
    ENEMY_MESSAGE("おめでたい奴だ");
    ENEMY_MESSAGE("屑が!!");
    ENEMY_MESSAGE("無謀な……");

    //ENEMY_MESSAGE("ヤッフー!!"];
    //ENEMY_MESSAGE("え?俺勝っちゃったの?"];
    ENEMY_MESSAGE("二度と会う事もないだろう");
    //ENEMY_MESSAGE("身の程知らずが……"];
    ENEMY_MESSAGE("僕は……負けない!!");
    ENEMY_MESSAGE("貴様に見切れる筋は無い");
    ENEMY_MESSAGE("今死ね、すぐ死ね、骨まで砕けろ!!");
    ENEMY_MESSAGE("任務完了!!");

    //ENEMY_MESSAGE("ヤッフー!!"];
    //ENEMY_MESSAGE("え?俺勝っちゃったの?"];
    //ENEMY_MESSAGE("貴様の死に場所はここだ!"];
    //ENEMY_MESSAGE("身の程知らずが……"];
    //ENEMY_MESSAGE("油断が死を招く"];
    //ENEMY_MESSAGE("おめでたい奴だ"];
    //ENEMY_MESSAGE("屑が!!"];
    //ENEMY_MESSAGE("無謀な……"];

    ENEMY_MESSAGE("鉄壁!!よって、無敵!!");
    ENEMY_MESSAGE("丸腰で勝てるとでも?");
    ENEMY_MESSAGE("パリイ!!");
    ENEMY_MESSAGE("自業自得だ");
    ENEMY_MESSAGE("Zzz");
    ENEMY_MESSAGE("ク、クマー");
    ENEMY_MESSAGE("?");
    ENEMY_MESSAGE("食べるべきではなかった!!");
    ENEMY_MESSAGE("うめぇ!!");
    ENEMY_MESSAGE("ブロックを侮ったな?");
    ENEMY_MESSAGE("シャキーン");

    ENEMY_MESSAGE("波動砲!!");
    ENEMY_MESSAGE("裏切られたとでも思ったか?");
    ENEMY_MESSAGE("ポールアターック!!");

    #undef ENEMY_MESSAGE
}

void HandleEntities()
{
    // 敵キャラ (Enemy character)
    for (t = 0; t < amax; t++)
    {
        xx[0] = EnemyX[t] - fx;
        xx[1] = EnemyY[t] - fy;
        xx[2] = EnemySizeX[t];
        xx[3] = EnemySizeY[t];
        xx[14] = 12000 * 1;
        if (anotm[t] >= 0)
            anotm[t]--;
        if (xx[0] + xx[2] >= -xx[14] && xx[0] <= fxmax + xx[14] && xx[1] + xx[3] >= -10 - 9000 && xx[1] <= fymax + 20000)
        {
            aacta[t] = 0;
            aactb[t] = 0;

            xx[10] = 0;

            switch (EnemyType[t])
            {
            case EEnemyType::BALL:
                xx[10] = 100;
                break;

                // こうらの敵 (Shell enemy)
            case EEnemyType::BALL_SHELLED:
                xx[10] = 100;
                break;

                // こうら (Shell)
            case EEnemyType::SHELL:
                xx[10] = 0;
                xx[17] = 800;
                if (EnemySubType[t] >= 1)
                    xx[10] = xx[17];
                // if (axtype[t]==1)xx[10]=xx[17];
                // if (axtype[t]==2)xx[10]=-xx[17];
                // 他の敵を倒す (Defeat other enemies)
                if (EnemySubType[t] >= 1)
                {
                    for (tt = 0; tt < amax; tt++)
                    {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = EnemyX[tt] - fx;
                        xx[9] = EnemyY[tt] - fy;
                        if (t != tt)
                        {
                            if (EnemyX[t] +
                                        EnemySizeX[t] -
                                        fx >
                                    xx[8] +
                                        xx[0] * 2 &&
                                EnemyX[t] -
                                        fx <
                                    xx[8] +
                                        EnemySizeX[tt] -
                                        xx[0] * 2 &&
                                EnemyY[t] +
                                        EnemySizeY[t] - fy >
                                    xx[9] + xx[5] &&
                                EnemyY[t] +
                                        EnemySizeY[t] -
                                        fy <
                                    xx[9] + xx[1] * 3 + xx[12] + 1500)
                            {
                                EnemyX[tt] = -800000;
                                PlaySound(Sounds[6]);
                            }
                        }
                    }
                }

                break;

                // あらまき
            case EEnemyType::SEAL:
                azimentype[t] = 0; // end();
                if (EnemySubType[t] == 0)
                {
                    EnemyY[t] -= 800;
                }
                if (EnemySubType[t] == 1)
                    EnemyY[t] += 1200;

                // xx[10]=100;
                break;

                // スーパージエン
            case EEnemyType::BALL_SPIKY:
                xx[10] = 120;
                xx[0] = 250;
                xx[8] = EnemyX[t] - fx;
                xx[9] = EnemyY[t] - fy;
                if (EnemyAITimer[t] >= 0)
                    EnemyAITimer[t]--;
                if (abs(PlayerX + PlayerSizeX - xx[8] - xx[0] * 2) < 9000
                    /*&& abs(ma < //+KZ "warning: result of comparison of constant 3000 with expression of type 'bool' is always true"
                           xx[8] - anobia[t] +
                           xx[0] * 2) < 3000*/
                    && PlayerVelY <= -600 && EnemyAITimer[t] <= 0)
                {
                    if (EnemySubType[t] == 1 && PlayerGrounded == 0 && axzimen[t] == 1)
                    {
                        EnemyVelY[t] = -1600;
                        EnemyAITimer[t] = 40;
                        EnemyY[t] -= 1000;
                    }
                } //
                break;

                // クマー (Bear)
            case EEnemyType::KUMA:
                xx[10] = 160;
                // azimentype[t]=2;
                break;

                // デフラグさん (Defrag-san)
            case EEnemyType::DEFRAG:
                if (azimentype[t] == 30)
                {
                    EnemyVelY[t] = -1600;
                    EnemyY[t] += EnemyVelY[t];
                }

                xx[10] = 120;
                if (EnemyAITimer[t] >= 10)
                {
                    EnemyAITimer[t]++;
                    if (Health >= 1)
                    {
                        if (EnemyAITimer[t] <= 19)
                        {
                            PlayerX = xx[0];
                            PlayerY = xx[1] - 3000;
                            PlayerState = 0;
                        }
                        xx[10] = 0;
                        if (EnemyAITimer[t] == 20)
                        {
                            PlayerVelX = 700;
                            mkeytm = 24;
                            PlayerVelY = -1200;
                            PlayerY = xx[1] - 1000 - 3000;
                            EnemyLookingDirection[t] = 1;
                            if (EnemySubType[t] == 1)
                            {
                                PlayerVelX = 840;
                                EnemySubType[t] = 0;
                            }
                        }
                        if (EnemyAITimer[t] == 40)
                        {
                            EnemyLookingDirection[t] = 0;
                            EnemyAITimer[t] = 0;
                        }
                    }
                }
                // ポール捨て (Discarding the pole)
                if (EnemySubType[t] == 1)
                {
                    for (tt = 0; tt < smax; tt++)
                    {
                        if (GroundType[tt] == 300)
                        {
                            // sa[sco]=xx[21]*100;sb[sco]=xx[22]*100;sc[sco]=3000;sd[sco]=(12-t)*3000;stype[sco]=300;sco++;
                            if (EnemyX[t] -
                                        fx >=
                                    -8000 &&
                                EnemyX[t] >=
                                    GroundX[tt] +
                                        2000 &&
                                EnemyX[t] <= GroundX[tt] + 3600 && axzimen[t] == 1)
                            {
                                GroundX[tt] = -800000;
                                EnemyAITimer[t] = 100;
                            }
                        }
                    }

                    if (EnemyAITimer[t] == 100)
                    {
                        CreateExtraGraphic(EnemyX[t] + 1200 -
                                  1200,
                              EnemyY[t] + 3000 -
                                  10 * 3000 - 1500,
                              0, 0, 0, 0, 1000,
                              10 * 3000 - 1200, 4, 20);
                        if (PlayerState == 300)
                        {
                            PlayerState = 0;
                            StopSoundMem(Sounds[11]);
                            bgmchange(Music[1]);
                        }
                        for (t1 = 0; t1 < smax; t1++)
                        {
                            if (GroundType[t1] == 104)
                                GroundX[t1] = -80000000;
                        }
                    }
                    if (EnemyAITimer[t] == 120)
                    {
                        CreateExtraGraphic(EnemyX[t] + 1200 -
                                  1200,
                              EnemyY[t] + 3000 -
                                  10 * 3000 - 1500,
                              600, -1200, 0,
                              160, 1000, 10 * 3000 - 1200, 4, 240);
                        EnemyLookingDirection[t] = 1;
                    }
                    // mc=700;mkeytm=24;md=-1200;mb=xx[1]-1000-3000;amuki[t]=1;if (axtype[t]==1){mc=840;axtype[t]=0;}}
                    if (EnemyAITimer[t] == 140)
                    {
                        EnemyLookingDirection[t] = 0;
                        EnemyAITimer[t] = 0;
                    }
                }
                if (EnemyAITimer[t] >= 220)
                {
                    EnemyAITimer[t] = 0;
                    EnemyLookingDirection[t] = 0;
                }
                // 他の敵を投げる (Throw other enemies)
                for (tt = 0; tt < amax; tt++)
                {
                    xx[0] = 250;
                    xx[5] = -800;
                    xx[12] = 0;
                    xx[1] = 1600;
                    xx[8] = EnemyX[tt] - fx;
                    xx[9] = EnemyY[tt] - fy;
                    if (t != tt && (int)EnemyType[tt] >= 100) //WARNING +KZ: EEnemyType is casted to int here!
                    {
                        if (EnemyX[t] + EnemySizeX[t] -
                                    fx >
                                xx[8] + xx[0] * 2 &&
                            EnemyX[t] - fx <
                                xx[8] + EnemySizeX[tt] -
                                    xx[0] * 2 &&
                            EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[5] && EnemyY[t] + EnemySizeY[t] - fy < xx[9] + xx[1] * 3 + xx[12] + 1500)
                        {
                            // aa[tt]=-800000;
                            EnemyLookingDirection[tt] = 1;
                            EnemyX[tt] = EnemyX[t] + 300;
                            EnemyY[tt] = EnemyY[t] - 3000;
                            EnemyBlockAppearTimer[tt] = 120; // aa[tt]=0;
                            EnemyAITimer[t] = 200;
                            EnemyLookingDirection[t] = 1;
                        }
                    }
                }

                break;

                // ジエン大砲
            case EEnemyType::BALL_ROCKET:
                azimentype[t] = 0;
                xx[10] = 0;
                xx[11] = 400;
                if (EnemySubType[t] == 0)
                    xx[10] = xx[11];
                if (EnemySubType[t] == 1)
                    xx[10] = -xx[11];
                if (EnemySubType[t] == 2)
                    EnemyY[t] -= xx[11];
                if (EnemySubType[t] == 3)
                    EnemyY[t] += xx[11];
                break;

                // スーパーブーン (Super Boon) //+KZ: xD??
            case EEnemyType::SUPER_BOON:
                azimentype[t] = 0;
                xx[22] = 20;
                if (EnemyAITimer[t] == 0)
                {
                    af[t] += xx[22];
                    EnemyVelY[t] += xx[22];
                }
                if (EnemyAITimer[t] == 1)
                {
                    af[t] -= xx[22];
                    EnemyVelY[t] -= xx[22];
                }
                if (EnemyVelY[t] > 300)
                    EnemyVelY[t] = 300;
                if (EnemyVelY[t] < -300)
                    EnemyVelY[t] = -300;
                if (af[t] >= 1200)
                    EnemyAITimer[t] = 1;
                if (af[t] < -0)
                    EnemyAITimer[t] = 0;
                EnemyY[t] += EnemyVelY[t];
                // atype[t]=151;
                break;
                // ノーマルブーン (Normal Boon)
            case EEnemyType::NORMAL_BOON:
                azimentype[t] = 2;
                break;

                // ファイアー玉 (Fireball)
            case EEnemyType::MAGMA:
                azimentype[t] = 5;
                EnemyY[t] += EnemyVelY[t];
                EnemyVelY[t] += 100;
                if (EnemyY[t] >= fymax + 1000)
                {
                    EnemyVelY[t] = 900;
                }
                if (EnemyY[t] >= fymax + 12000)
                {
                    EnemyY[t] = fymax;
                    EnemyVelY[t] = -2600;
                }
                break;

                // ファイアー (Fire)
            case EEnemyType::FLAME:
                azimentype[t] = 0;
                xx[10] = 0;
                xx[11] = 400;
                if (EnemySubType[t] == 0)
                    xx[10] = xx[11];
                if (EnemySubType[t] == 1)
                    xx[10] = -xx[11];
                break;

                // モララー (Molalla)
            case EEnemyType::MOLALLA:
                EnemyAITimer[t] += 1;
                if (EnemySubType[t] == 0)
                {
                    if (EnemyAITimer[t] == 50 && PlayerY >= 6000)
                    {
                        EnemyVelX[t] = 300;
                        EnemyVelY[t] -= 1600;
                        EnemyY[t] -= 1000;
                    }

                    for (tt = 0; tt < amax; tt++)
                    {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = EnemyX[tt] - fx;
                        xx[9] = EnemyY[tt] - fy;
                        if (t != tt && EnemyType[tt] == EEnemyType::MUSHROOM_POISONOUS)
                        {
                            if (EnemyX[t] +
                                        EnemySizeX[t] -
                                        fx >
                                    xx[8] +
                                        xx[0] * 2 &&
                                EnemyX[t] -
                                        fx <
                                    xx[8] +
                                        EnemySizeX[tt] -
                                        xx[0] * 2 &&
                                EnemyY[t] +
                                        EnemySizeY[t] - fy >
                                    xx[9] + xx[5] &&
                                EnemyY[t] +
                                        EnemySizeY[t] -
                                        fy <
                                    xx[9] + xx[1] * 3 + xx[12] + 1500)
                            {
                                EnemyX[tt] = -800000;
                                EnemySubType[t] = 1;
                                EnemyVelY[t] = -1600;
                                EnemyMessageTimer[t] = 30;
                                EnemyMessageType[t] = 25;
                            }
                        }
                    }
                }
                if (EnemySubType[t] == 1)
                {
                    azimentype[t] = 0;
                    EnemyY[t] += EnemyVelY[t];
                    EnemyVelY[t] += 120;
                }
                break;

                // レーザー (Laser)
            case EEnemyType::LASER:
                azimentype[t] = 0;
                xx[10] = 1600;
                if (EnemySubType[t] == 1)
                {
                    xx[10] = 1200;
                    EnemyY[t] -= 200;
                }
                if (EnemySubType[t] == 2)
                {
                    xx[10] = 1200;
                    EnemyY[t] += 200;
                }
                if (EnemySubType[t] == 3)
                {
                    xx[10] = 900;
                    EnemyY[t] -= 600;
                }
                if (EnemySubType[t] == 4)
                {
                    xx[10] = 900;
                    EnemyY[t] += 600;
                }
                break;

                // 雲の敵 (Enemy of the Clouds)
            case EEnemyType::EVIL_CLOUD:
                azimentype[t] = 0;
                // xx[10]=100;
                break;
            case EEnemyType::EVIL_CLOUD_TOUCHED:
                azimentype[t] = 0;
                break;
            case EEnemyType::SPIKY_BLOCK:
                azimentype[t] = 0;
                break;
            case EEnemyType::SPIKY_BLOCK_TOUCHED:
                azimentype[t] = 0;
                break;

            case EEnemyType::LAVA_FROM_PIPE:
                azimentype[t] = 2;
                break;

            case EEnemyType::FAKE_POLE:
                xx[23] = 400;
                if (EnemySubType[t] == 0)
                {
                    EnemySubType[t] = 1;
                    EnemyLookingDirection[t] = 1;
                }
                if (PlayerY >= 30000 && PlayerX >= EnemyX[t] - 3000 * 5 - fx && PlayerX <= EnemyX[t] - fx && EnemySubType[t] == 1)
                {
                    EnemySubType[t] = 5;
                    EnemyLookingDirection[t] = 0;
                }
                if (PlayerY >= 24000 && PlayerX <= EnemyX[t] + 3000 * 8 - fx && PlayerX >= EnemyX[t] - fx && EnemySubType[t] == 1)
                {
                    EnemySubType[t] = 5;
                    EnemyLookingDirection[t] = 1;
                }
                if (EnemySubType[t] == 5)
                    xx[10] = xx[23];
                break;

            case EEnemyType::FALLING_CAT:
                azimentype[t] = 4;
                xx[23] = 1000;
                if (PlayerX >= EnemyX[t] - fx - PlayerSizeX - xx[26] && PlayerX <= EnemyX[t] - fx + EnemySizeX[t] + xx[26])
                {
                    EnemyAITimer[t] = 1;
                }
                if (EnemyAITimer[t] == 1)
                {
                    EnemyY[t] += 1200;
                }
                break;

                // ファイアバー (Fire Bar)
            case EEnemyType::FIREBAR_CLOCKWISE:
                azimentype[t] = 0;
                if (EnemyX[t] % 10 != 1)
                    EnemyAITimer[t] += 6;
                else
                {
                    EnemyAITimer[t] -= 6;
                }
                xx[25] = 2;
                if (EnemyAITimer[t] > 360 * xx[25])
                    EnemyAITimer[t] -= 360 * xx[25];
                if (EnemyAITimer[t] < 0)
                    EnemyAITimer[t] += 360 * xx[25];

                for (tt = 0; tt <= EnemySubType[t] % 100; tt++)
                {
                    xx[26] = 18;
                    xd[4] = tt * xx[26] * cos(EnemyAITimer[t] * pai / 180 / 2);
                    xd[5] = tt * xx[26] * sin(EnemyAITimer[t] * pai / 180 / 2);

                    xx[4] = 1800;
                    xx[5] = 800;
                    xx[8] = EnemyX[t] - fx + int(xd[4]) * 100 - xx[4] / 2;
                    xx[9] = EnemyY[t] - fy + int(xd[5]) * 100 - xx[4] / 2;

                    if (PlayerX + PlayerSizeX > xx[8] + xx[5] && PlayerX < xx[8] + xx[4] - xx[5] && PlayerY + PlayerSizeY > xx[9] + xx[5] && PlayerY < xx[9] + xx[4] - xx[5])
                    {
                        Health -= 1;
                        PlayerMessageType = 51;
                        PlayerMessageTimer = 30;
                    }
                }

                break;

                //+KZ: Syobon Action 2 inverted Fire Bar
            case EEnemyType::FIREBAR_COUNTERCLOCKWISE:
                azimentype[t] = 0;
                if (EnemyX[t] % 10 != 1)
                    EnemyAITimer[t] += 6;
                else
                {
                    EnemyAITimer[t] -= 6;
                }
                xx[25] = 2;
                if (EnemyAITimer[t] > 360 * xx[25])
                    EnemyAITimer[t] -= 360 * xx[25];
                if (EnemyAITimer[t] < 0)
                    EnemyAITimer[t] += 360 * xx[25];

                for (tt = 0; tt <= EnemySubType[t] % 100; tt++)
                {
                    xx[26] = 18;
                    xd[4] = -tt * xx[26] * cos(EnemyAITimer[t] * pai / 180 / 2);
                    xd[5] = tt * xx[26] * sin(EnemyAITimer[t] * pai / 180 / 2);

                    xx[4] = 1800;
                    xx[5] = 800;
                    xx[8] = EnemyX[t] - fx + int(xd[4]) * 100 - xx[4] / 2;
                    xx[9] = EnemyY[t] - fy + int(xd[5]) * 100 - xx[4] / 2;

                    if (PlayerX + PlayerSizeX > xx[8] + xx[5] && PlayerX < xx[8] + xx[4] - xx[5] && PlayerY + PlayerSizeY > xx[9] + xx[5] && PlayerY < xx[9] + xx[4] - xx[5])
                    {
                        Health -= 1;
                        PlayerMessageType = 51;
                        PlayerMessageTimer = 30;
                    }
                }

                break;

            case EEnemyType::BALL_BIG:
                xx[10] = 160;
                // azimentype[t]=0;
                break;

                // おいしいキノコ (Delicious mushrooms)
            case EEnemyType::MUSHROOM:
                azimentype[t] = 1;
                xx[10] = 100;

                // ほかの敵を巨大化 (Enlarge other enemies)
                if (EnemySubType[t] == 2)
                {
                    for (tt = 0; tt < amax; tt++)
                    {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = EnemyX[tt] - fx;
                        xx[9] = EnemyY[tt] - fy;
                        if (t != tt)
                        {
                            if (EnemyX[t] +
                                        EnemySizeX[t] -
                                        fx >
                                    xx[8] +
                                        xx[0] * 2 &&
                                EnemyX[t] -
                                        fx <
                                    xx[8] +
                                        EnemySizeX[tt] -
                                        xx[0] * 2 &&
                                EnemyY[t] +
                                        EnemySizeY[t] - fy >
                                    xx[9] + xx[5] &&
                                EnemyY[t] +
                                        EnemySizeY[t] -
                                        fy <
                                    xx[9] + xx[1] * 3 + xx[12])
                            {
                                if (EnemyType[tt] == EEnemyType::BALL || EnemyType[tt] == EEnemyType::BALL_SPIKY)
                                {
                                    EnemyType[tt] = EEnemyType::BALL_BIG; // PlaySound(Sounds[6]);
                                    EnemySizeX[tt] = 6400;
                                    EnemySizeY[tt] = 6300;
                                    EnemySubType[tt] = 0;
                                    EnemyX[tt] -= 1050;
                                    EnemyY[tt] -= 1050;
                                    PlaySound(Sounds[9]);
                                    EnemyX[t] = -80000000;
                                }
                            }
                        }
                    }
                }

                break;

                // 毒キノコ (Poisonous mushrooms)
            case EEnemyType::MUSHROOM_POISONOUS:
                azimentype[t] = 1;
                xx[10] = 100;
                if (EnemySubType[t] == 1)
                    xx[10] = 200;
                break;

                // 悪スター (Bad Star)
            case EEnemyType::BAD_STAR:
                azimentype[t] = 1;
                xx[10] = 200;
                if (axzimen[t] == 1)
                {
                    EnemyY[t] -= 1200;
                    EnemyVelY[t] = -1400;
                }
                break;

            case EEnemyType::BALL_NO_COLLISION:
                azimentype[t] = 1;
                xx[10] = 100;
                break;

                /*
                    +KZ: there was a lot of commented out code here, i just removed it
                */

            } // sw

            if (EnemyBlockAppearTimer[t] >= 1)
                xx[10] = 0;

            if (EnemyLookingDirection[t] == 0)
                aacta[t] -= xx[10];
            if (EnemyLookingDirection[t] == 1)
                aacta[t] += xx[10];

            // 最大値 (Maximum value)
            xx[0] = 850;
            xx[1] = 1200;

            // if (mc>xx[0]){mc=xx[0];}
            // if (mc<-xx[0]){mc=-xx[0];}
            if (EnemyVelY[t] > xx[1] && azimentype[t] != 5)
            {
                EnemyVelY[t] = xx[1];
            }
            // 行動 (Action)
            EnemyX[t] += aacta[t]; // ab[t]+=aactb[t];

            if ((azimentype[t] >= 1 || azimentype[t] == -1) && EnemyBlockAppearTimer[t] <= 0)
            {
                // if (atype[t]==4)end();

                // 移動 (Move)
                EnemyX[t] += EnemyVelX[t];
                if (azimentype[t] >= 1 && azimentype[t] <= 3)
                {
                    EnemyY[t] += EnemyVelY[t];
                    EnemyVelY[t] += 120;
                } // ad[t]+=180;

                if (axzimen[t] == 1)
                {
                    xx[0] = 100;
                    if (EnemyVelX[t] >= 200)
                    {
                        EnemyVelX[t] -= xx[0];
                    }
                    else if (EnemyVelX[t] <= -200)
                    {
                        EnemyVelX[t] += xx[0];
                    }
                    else
                    {
                        EnemyVelX[t] = 0;
                    }
                }

                axzimen[t] = 0;

                // 地面判定 (Ground judgment)
                if (azimentype[t] != 2)
                {
                    HandleEntitiesBlocks();
                }

            } // azimentype[t]>=1

            // ブロックから出現するさい (When appearing from a block)
            if (EnemyBlockAppearTimer[t] > 0)
            {
                EnemyBlockAppearTimer[t]--;
                if (EnemyBlockAppearTimer[t] < 100)
                {
                    EnemyY[t] -= 180;
                }
                if (EnemyBlockAppearTimer[t] > 100)
                {
                }
                if (EnemyBlockAppearTimer[t] == 100)
                {
                    EnemyY[t] -= 800;
                    EnemyVelY[t] = -1200;
                    EnemyVelX[t] = 700;
                    EnemyBlockAppearTimer[t] = 0;
                }
            } // abrocktm[t]>0

            // プレイヤーからの判定 (Player's judgment)
            xx[0] = 250;
            xx[1] = 1600;
            xx[2] = 1000;
            xx[4] = 500;
            xx[5] = -800;

            xx[8] = EnemyX[t] - fx;
            xx[9] = EnemyY[t] - fy;
            xx[12] = 0;
            if (PlayerVelY >= 100)
                xx[12] = PlayerVelY;
            xx[25] = 0;

            if (PlayerX + PlayerSizeX > xx[8] + xx[0] * 2 && PlayerX < xx[8] + EnemySizeX[t] - xx[0] * 2 && PlayerY + PlayerSizeY > xx[9] - xx[5] && PlayerY + PlayerSizeY < xx[9] + xx[1] + xx[12] && (mmutekitm <= 0 || PlayerVelY >= 100) && EnemyBlockAppearTimer[t] <= 0)
            {
                if (EnemyType[t] != EEnemyType::BALL_SPIKY && EnemyType[t] != EEnemyType::MAGMA && EnemyType[t] != EEnemyType::FLAME && ((int)EnemyType[t] <= 78 || EnemyType[t] == EEnemyType::FAKE_POLE) && PlayerGrounded != 1 && PlayerState != 200)
                { // && atype[t]!=4 && atype[t]!=7){

                    if (EnemyType[t] == EEnemyType::BALL)
                    {
                        if (EnemySubType[t] == 0)
                            EnemyX[t] = -900000;
                        if (EnemySubType[t] == 1)
                        {
                            PlaySound(Sounds[5]);
                            PlayerY = xx[9] - 900 - EnemySizeY[t];
                            PlayerVelY = -2100;
                            xx[25] = 1;
                            actaon[2] = 0;
                        }
                    }

                    if (EnemyType[t] == EEnemyType::BALL_SHELLED)
                    {
                        EnemyType[t] = EEnemyType::SHELL;
                        EnemySizeY[t] = 3000;
                        EnemySubType[t] = 0;
                    }
                    // こうら (Shell)
                    else if (EnemyType[t] == EEnemyType::SHELL && PlayerVelY >= 0)
                    {
                        if (EnemySubType[t] == 1 || EnemySubType[t] == 2)
                        {
                            EnemySubType[t] = 0;
                        }
                        else if (EnemySubType[t] == 0)
                        {
                            if (PlayerX +
                                        PlayerSizeX >
                                    xx[8] +
                                        xx[0] * 2 &&
                                PlayerX <
                                    xx[8] + EnemySizeX[t] / 2 - xx[0] * 4)
                            {
                                EnemySubType[t] = 1;
                                EnemyLookingDirection[t] = 1;
                            }
                            else
                            {
                                EnemySubType[t] = 1;
                                EnemyLookingDirection[t] = 0;
                            }
                        }
                    }
                    if (EnemyType[t] == EEnemyType::SEAL)
                    {
                        xx[25] = 1;
                    }

                    if (EnemyType[t] == EEnemyType::DEFRAG)
                    {
                        EnemyAITimer[t] = 10;
                        PlayerVelY = 0;
                        actaon[2] = 0;
                    }

                    if (EnemyType[t] == EEnemyType::BALL_ROCKET)
                    {
                        EnemyX[t] = -900000;
                    }

                    if (EnemyType[t] == EEnemyType::SUPER_BOON)
                    {
                        EnemyType[t] = EEnemyType::NORMAL_BOON;
                        EnemyVelY[t] = 0;
                    }
                    // if (atype[t]==4){
                    // xx[25]=1;
                    // }

                    if (EnemyType[t] != EEnemyType::FAKE_POLE)
                    {
                        if (xx[25] == 0)
                        {
                            PlaySound(Sounds[5]);
                            PlayerY = xx[9] - 1000 - EnemySizeY[t];
                            PlayerVelY = -1000;
                        }
                    }
                    if (EnemyType[t] == EEnemyType::FAKE_POLE)
                    {
                        if (xx[25] == 0)
                        {
                            PlaySound(Sounds[5]);
                            PlayerY = xx[9] - 4000;
                            PlayerVelY = -1000;
                            EnemySubType[t] = 5;
                        }
                    }

                    if (actaon[2] == 1)
                    {
                        PlayerVelY = -1600;
                        actaon[2] = 0;
                    }
                }
                // if (atype[t]==200){mb=xx[9]-900-anobib[t];md=-2400;}
            }
            // if (aa[t]+anobia[t]-fx>xx[8]-xx[0] && aa[t]-fx<xx[8]){md=-1000;}//aa[t]=-9000000;
            //  && ab[t]-fy<xx[9]+xx[1]/2 && ab[t]+anobib[t]-fy>xx[9]+mnobib-xx[2]

            xx[15] = -500;

            // プレイヤーに触れた時 (When the player touches it)
            xx[16] = 0;
            if (EnemyType[t] == EEnemyType::BALL_SPIKY || EnemyType[t] == EEnemyType::MAGMA || EnemyType[t] == EEnemyType::FLAME)
                xx[16] = -3000;
            if (EnemyType[t] == EEnemyType::SPIKY_BLOCK || EnemyType[t] == EEnemyType::SPIKY_BLOCK_TOUCHED || EnemyType[t] == EEnemyType::LAVA_FROM_PIPE)
                xx[16] = -3200;
            if (EnemyType[t] == EEnemyType::FAKE_POLE)
                xx[16] = -EnemySizeY[t] + 6000;
            if (PlayerX + PlayerSizeX > xx[8] + xx[4] && PlayerX < xx[8] + EnemySizeX[t] - xx[4] && PlayerY < xx[9] + EnemySizeY[t] + xx[15] && PlayerY + PlayerSizeY > xx[9] + EnemySizeY[t] - xx[0] + xx[16] && anotm[t] <= 0 && EnemyBlockAppearTimer[t] <= 0)
            {
                if (mmutekion == 1)
                {
                    EnemyX[t] = -9000000;
                }
                if (mmutekitm <= 0 && ((int)EnemyType[t] <= 99 || (int)EnemyType[t] >= 200))
                {
                    if (mmutekion != 1 && PlayerState != 200)
                    {
                        // if (mmutekitm<=0)

                        // ダメージ (Damage)
                        if ((EnemyType[t] != EEnemyType::SHELL || EnemySubType[t] != 0) && Health >= 1)
                        {
                            if (EnemyType[t] != EEnemyType::DEFRAG)
                            {
                                Health -= 1;
                                // mmutekitm=40;
                            }
                        }

                        if (EnemyType[t] == EEnemyType::DEFRAG)
                        {
                            EnemyAITimer[t] = 10;
                        }
                        // せりふ (Dialogue)
                        if (Health == 0)
                        {

                            if (EnemyType[t] == EEnemyType::BALL || EnemyType[t] == EEnemyType::BALL_ROCKET)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = SyobonRand(7) + 1 + 1000 + (SyobonLevel - 1) * 10;
                            }

                            if (EnemyType[t] == EEnemyType::BALL_SHELLED)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = SyobonRand(2) + 15;
                            }

                            if (EnemyType[t] == EEnemyType::SHELL && EnemySubType[t] >= 1 && mmutekitm <= 0)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = 18;
                            }

                            if (EnemyType[t] == EEnemyType::SEAL)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = 20;
                            }

                            if (EnemyType[t] == EEnemyType::BALL_SPIKY)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = SyobonRand(7) + 1 + 1000 + (SyobonLevel - 1) * 10;
                            }

                            if (EnemyType[t] == EEnemyType::KUMA)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = 21;
                            }

                            if (EnemyType[t] == EEnemyType::MAGMA || EnemyType[t] == EEnemyType::FLAME)
                            {
                                PlayerMessageTimer = 30;
                                PlayerMessageType = 54;
                            }

                            if (EnemyType[t] == EEnemyType::KUKURRU)
                            {
                                EnemyMessageTimer[t] = 30;
                                EnemyMessageType[t] = 24;
                            }

                            if (EnemyType[t] == EEnemyType::EVIL_CLOUD || EnemyType[t] == EEnemyType::EVIL_CLOUD_TOUCHED)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = 30;
                            }

                            if (EnemyType[t] == EEnemyType::SPIKY_BLOCK)
                            {
                                EnemyMessageTimer[t] = 20;
                                EnemyMessageType[t] = SyobonRand(1) + 31;
                                xx[24] = 900;
                                EnemyType[t] = EEnemyType::SPIKY_BLOCK_TOUCHED;
                                EnemyX[t] -= xx[24] + 100;
                                EnemyY[t] -= xx[24] - 100 * 0;
                            } // 82

                            if (EnemyType[t] == EEnemyType::LAVA_FROM_PIPE)
                            {
                                PlayerMessageTimer = 30;
                                PlayerMessageType = 50;
                            }

                            if (EnemyType[t] == EEnemyType::FAKE_POLE)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = SyobonRand(1) + 85;
                            }
                            // 雲
                            if (EnemyType[t] == EEnemyType::EVIL_CLOUD)
                            {
                                EnemyType[t] = EEnemyType::EVIL_CLOUD_TOUCHED;
                            }

                        } // Health==0

                        // こうら (Shell)
                        if (EnemyType[t] == EEnemyType::SHELL)
                        {
                            // if (axtype[t]==1 || axtype[t]==2){axtype[t]=0;}
                            if (EnemySubType[t] == 0)
                            {
                                if (PlayerX + PlayerSizeX > xx[8] + xx[0] * 2 && PlayerX < xx[8] + EnemySizeX[t] / 2 - xx[0] * 4)
                                {
                                    EnemySubType[t] = 1;
                                    EnemyLookingDirection[t] = 1;
                                    EnemyX[t] = PlayerX + PlayerSizeX + fx + PlayerVelX;
                                    mmutekitm = 5;
                                }
                                else
                                {
                                    EnemySubType[t] = 1;
                                    EnemyLookingDirection[t] = 0;
                                    EnemyX[t] = PlayerX - EnemySizeX[t] + fx - PlayerVelX;
                                    mmutekitm = 5;
                                }
                            }
                            else
                            {
                                Health -= 1;
                            } // mmutekitm=40;}
                        }
                    }
                }
                // else if (mmutekitm>=0 && mmutekitm<=2){mmutekitm+=1;}
                // アイテム (Item)
                if ((int)EnemyType[t] >= 100 && (int)EnemyType[t] <= 199)
                {

                    if (EnemyType[t] == EEnemyType::MUSHROOM && EnemySubType[t] == 0)
                    {
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 1;
                        PlaySound(Sounds[9]);
                    }
                    if (EnemyType[t] == EEnemyType::MUSHROOM && EnemySubType[t] == 1)
                    {
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 2;
                        PlaySound(Sounds[9]);
                    }
                    if (EnemyType[t] == EEnemyType::MUSHROOM && EnemySubType[t] == 2)
                    {
                        PlayerSizeX = 5200;
                        PlayerSizeY = 7300;
                        PlaySound(Sounds[9]);
                        PlayerX -= 1100;
                        PlayerY -= 4000;
                        PlayerState = 1;
                        Health = 50000000;
                    }

                    if (EnemyType[t] == EEnemyType::BURNING_FLOWER)
                    {
                        Health -= 1;
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 11;
                    }
                    if (EnemyType[t] == EEnemyType::MUSHROOM_POISONOUS)
                    {
                        Health -= 1;
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 10;
                    }
                    //?ボール (? Ball)
                    if (EnemyType[t] == EEnemyType::MYSTERY_BALL)
                    {
                        if (EnemySubType[t] == 0)
                        {
                            PlaySound(Sounds[4]);
                            GroundAI[26] = 6;
                        }
                        if (EnemySubType[t] == 1)
                        {
                            BlockSubType[7] = 80;
                            PlaySound(Sounds[4]);

                            // CreateEntity(aa[t]-6*3000+1000,-3*3000,0,0,0,110,0);
                            CreateEntity(EnemyX[t] -
                                             8 * 3000 -
                                             1000,
                                         -4 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, 0);
                            CreateEntity(EnemyX[t] -
                                             10 *
                                                 3000 +
                                             1000,
                                         -1 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, 0);

                            CreateEntity(EnemyX[t] +
                                             4 * 3000 +
                                             1000,
                                         -2 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, 0);
                            CreateEntity(EnemyX[t] +
                                             5 * 3000 -
                                             1000,
                                         -3 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, 0);
                            CreateEntity(EnemyX[t] +
                                             6 * 3000 +
                                             1000,
                                         -4 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, 0);
                            CreateEntity(EnemyX[t] +
                                             7 * 3000 -
                                             1000,
                                         -2 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, 0);
                            CreateEntity(EnemyX[t] +
                                             8 * 3000 +
                                             1000,
                                         -2 * 3000 - 1000, 0, 0, 0, EEnemyType::BAD_STAR, 0);
                            BlockY[0] += 3000 * 3;
                        }
                    } // 105

                    if (EnemyType[t] == EEnemyType::BAD_STAR)
                    {
                        Health -= 1;
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 3;
                    }

                    /*
                    if (atype[t]==101){mmutekitm=120;mmutekion=1;}
                    if (atype[t]==102){Health-=1;mmutekitm=20;}
                    if (atype[t]==103){
                    //xx[24]=2400;
                    eyobi(aa[t]-500,ab[t],0,-600,0,80,2500,1600,2,32);
                    }
                    if (atype[t]==104){mztm=120;mztype=1;}
                    if (atype[t]==105){mztm=160;mztype=2;}

                    if (atype[t]==120){mtype=3;mnobia=3800;mnobib=2300;}

                    if (atype[t]==130){msoubi=1;}
                    if (atype[t]==131){msoubi=2;}
                    if (atype[t]==132){msoubi=3;}
                    if (atype[t]==133){msoubi=4;}

                    */
                    EnemyX[t] = -90000000;
                }

            } //(ma
        }
        else
        {
            EnemyX[t] = -9000000;
        }

    } // t
}

//+KZ: uhhh i realized about lines like EnemyDefaultSizeX[(int)EnemyAppearType[t]], i dont recommend using EnemyAppear things
void PlaceEntities()
{
    // 敵キャラの配置 (Enemy character placement)
    for (t = 0; t < bmax; t++)
    {
        if (EnemyAppearX[t] >= -80000)
        {

            if (EnemyAppearTimer[t] >= 0)
            {
                EnemyAppearTimer[t] = EnemyAppearTimer[t] - 1;
            }

            for (tt = 0; tt <= 1; tt++)
            {
                int local_xx_0 = 0; // xx[0] = 0;
                int local_xx_1 = 0; // xx[1] = 0;

                if (bz[t] == 0 && EnemyAppearTimer[t] < 0 && EnemyAppearX[t] - fx >= fxmax + 2000 && EnemyAppearX[t] - fx < fxmax + 2000 + PlayerVelX && tt == 0)
                {
                    local_xx_0 = 1;
                    EnemyLookingDirection[EnemyCount] = 0;
                } // && mmuki==1
                if (bz[t] == 0 && EnemyAppearTimer[t] < 0 && EnemyAppearX[t] - fx >= -400 - EnemyDefaultSizeX[(int)EnemyAppearType[t]] + PlayerVelX && EnemyAppearX[t] - fx < -400 - EnemyDefaultSizeX[(int)EnemyAppearType[t]] && tt == 1)
                {
                    local_xx_0 = 1;
                    local_xx_1 = 1;
                    EnemyLookingDirection[EnemyCount] = 1;
                } // && mmuki==0
                if (bz[t] == 1 && EnemyAppearX[t] - fx >= 0 - EnemyDefaultSizeX[(int)EnemyAppearType[t]] && EnemyAppearX[t] - fx <= fxmax + 4000 && EnemyAppearY[t] - fy >= -9000 && EnemyAppearY[t] - fy <= fymax + 4000 && EnemyAppearTimer[t] < 0)
                {
                    local_xx_0 = 1;
                    bz[t] = 0;
                } // && xza<=5000// && tyuukan!=1
                // if (bz[t]==2){local_xx_0=0;local_xx_1=0;}
                // if (btype[t]>=100){bz[t]=2;}

                if (local_xx_0 == 1)
                { // 400
                    EnemyAppearTimer[t] = 401;
                    local_xx_0 = 0; // if (btype[t]>=20 && btype[t]<=23){btm[t]=90000;}
                    if ((int)EnemyAppearType[t] >= 10)
                    {
                        EnemyAppearTimer[t] = 9999999;
                    }
                    // 10
                    CreateEntity(EnemyAppearX[t], EnemyAppearY[t], 0, 0, 0, EnemyAppearType[t], EnemyAppearSubType[t]);
                }

            } // tt
        }
    } // t
}

void HandleEnemiesMessages()
{
    // 敵キャラのメッセージ (Message from enemy character)
    setc0();
    for (t = 0; t < amax; t++)
    {
        if (EnemyMessageTimer[t] >= 1)
        {
            EnemyMessageTimer[t]--; // end();

            xs[0] = "";

            if (EnemyMessageType[t] == 1001)
                xs[0] = "ヤッフー!!";
            if (EnemyMessageType[t] == 1002)
                xs[0] = "え?俺勝っちゃったの?";
            if (EnemyMessageType[t] == 1003)
                xs[0] = "貴様の死に場所はここだ!";
            if (EnemyMessageType[t] == 1004)
                xs[0] = "二度と会う事もないだろう";
            if (EnemyMessageType[t] == 1005)
                xs[0] = "俺、最強!!";
            if (EnemyMessageType[t] == 1006)
                xs[0] = "一昨日来やがれ!!";
            if (EnemyMessageType[t] == 1007)
                xs[0] = "漢に後退の二文字は無い!!";
            if (EnemyMessageType[t] == 1008)
                xs[0] = "ハッハァ!!";

            if (EnemyMessageType[t] == 1011)
                xs[0] = "ヤッフー!!";
            if (EnemyMessageType[t] == 1012)
                xs[0] = "え?俺勝っちゃったの?";
            if (EnemyMessageType[t] == 1013)
                xs[0] = "貴様の死に場所はここだ!";
            if (EnemyMessageType[t] == 1014)
                xs[0] = "身の程知らずが……";
            if (EnemyMessageType[t] == 1015)
                xs[0] = "油断が死を招く";
            if (EnemyMessageType[t] == 1016)
                xs[0] = "おめでたい奴だ";
            if (EnemyMessageType[t] == 1017)
                xs[0] = "屑が!!";
            if (EnemyMessageType[t] == 1018)
                xs[0] = "無謀な……";

            if (EnemyMessageType[t] == 1021)
                xs[0] = "ヤッフー!!";
            if (EnemyMessageType[t] == 1022)
                xs[0] = "え?俺勝っちゃったの?";
            if (EnemyMessageType[t] == 1023)
                xs[0] = "二度と会う事もないだろう";
            if (EnemyMessageType[t] == 1024)
                xs[0] = "身の程知らずが……";
            if (EnemyMessageType[t] == 1025)
                xs[0] = "僕は……負けない!!";
            if (EnemyMessageType[t] == 1026)
                xs[0] = "貴様に見切れる筋は無い";
            if (EnemyMessageType[t] == 1027)
                xs[0] =
                    "今死ね、すぐ死ね、骨まで砕けろ!!";
            if (EnemyMessageType[t] == 1028)
                xs[0] = "任務完了!!";

            if (EnemyMessageType[t] == 1031)
                xs[0] = "ヤッフー!!";
            if (EnemyMessageType[t] == 1032)
                xs[0] = "え?俺勝っちゃったの?";
            if (EnemyMessageType[t] == 1033)
                xs[0] = "貴様の死に場所はここだ!";
            if (EnemyMessageType[t] == 1034)
                xs[0] = "身の程知らずが……";
            if (EnemyMessageType[t] == 1035)
                xs[0] = "油断が死を招く";
            if (EnemyMessageType[t] == 1036)
                xs[0] = "おめでたい奴だ";
            if (EnemyMessageType[t] == 1037)
                xs[0] = "屑が!!";
            if (EnemyMessageType[t] == 1038)
                xs[0] = "無謀な……";

            if (EnemyMessageType[t] == 15)
                xs[0] = "鉄壁!!よって、無敵!!";
            if (EnemyMessageType[t] == 16)
                xs[0] = "丸腰で勝てるとでも?";
            if (EnemyMessageType[t] == 17)
                xs[0] = "パリイ!!";
            if (EnemyMessageType[t] == 18)
                xs[0] = "自業自得だ";
            if (EnemyMessageType[t] == 20)
                xs[0] = "Zzz";
            if (EnemyMessageType[t] == 21)
                xs[0] = "ク、クマー";
            if (EnemyMessageType[t] == 24)
                xs[0] = "?";
            if (EnemyMessageType[t] == 25)
                xs[0] = "食べるべきではなかった!!";
            if (EnemyMessageType[t] == 30)
                xs[0] = "うめぇ!!";
            if (EnemyMessageType[t] == 31)
                xs[0] = "ブロックを侮ったな?";
            if (EnemyMessageType[t] == 32)
                xs[0] = "シャキーン";

            if (EnemyMessageType[t] == 50)
                xs[0] = "波動砲!!";
            if (EnemyMessageType[t] == 85)
                xs[0] = "裏切られたとでも思ったか?";
            if (EnemyMessageType[t] == 86)
                xs[0] = "ポールアターック!!";

            if (EnemyMessageType[t] != 31)
            {
                xx[5] = (EnemyX[t] + EnemySizeX[t] + 300 - fx) / 100;
                xx[6] = (EnemyY[t] - fy) / 100;
            }
            else
            {
                xx[5] = (EnemyX[t] + EnemySizeX[t] + 300 - fx) / 100;
                xx[6] = (EnemyY[t] - fy - 800) / 100;
            }

            /*ChangeFontType(DX_FONTTYPE_EDGE);
            setc1();
            str(xs[0], xx[5], xx[6]);
            ChangeFontType(DX_FONTTYPE_NORMAL);*/
            DrawGraphZ(xx[5], xx[6], apEnemyMessages[xs[0]]);

        } // amsgtm
    } // amax
}

void HandleEntitiesBlocks()
{

	// 壁 (Wall)
	for (tt = 0; tt < smax; tt++)
	{
		if (GroundX[tt] - fx + GroundSizeX[tt] >= -12010 && GroundX[tt] - fx <= fxmax + 12100 && GroundType[tt] <= 99)
		{
			xx[0] = 200;
			xx[2] = 1000;
			xx[1] = 2000; // anobia[t]

			xx[8] = GroundX[tt] - fx;
			xx[9] = GroundY[tt] - fy;
			if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] - xx[0] && EnemyX[t] - fx < xx[8] + xx[2] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] * 3 / 4 && EnemyY[t] - fy < xx[9] + GroundSizeY[tt] - xx[2])
			{
				EnemyX[t] = xx[8] - xx[0] - EnemySizeX[t] + fx;
				EnemyLookingDirection[t] = 0;
			}
			if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + GroundSizeX[tt] - xx[0] && EnemyX[t] - fx < xx[8] + GroundSizeX[tt] + xx[0] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] * 3 / 4 && EnemyY[t] - fy < xx[9] + GroundSizeY[tt] - xx[2])
			{
				EnemyX[t] = xx[8] + GroundSizeX[tt] + xx[0] + fx;
				EnemyLookingDirection[t] = 1;
			}
			// if (aa[t]+anobia[t]-fx>xx[8]+xx[0] && aa[t]-fx<xx[8]+sc[tt]-xx[0] && ab[t]+anobib[t]-fy>xx[9] && ab[t]+anobib[t]-fy<xx[9]+xx[1] && ad[t]>=-100){ab[t]=sb[tt]-fy-anobib[t]+100+fy;ad[t]=0;}//PlayerGrounded=1;}
			if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + GroundSizeX[tt] - xx[0] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] && EnemyY[t] + EnemySizeY[t] - fy < xx[9] + GroundSizeY[tt] - xx[1] && EnemyVelY[t] >= -100)
			{
				EnemyY[t] = GroundY[tt] - fy - EnemySizeY[t] + 100 + fy;
				EnemyVelY[t] = 0;
				axzimen[t] = 1;
			}

			if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + GroundSizeX[tt] - xx[0] && EnemyY[t] - fy > xx[9] + GroundSizeY[tt] - xx[1] && EnemyY[t] - fy < xx[9] + GroundSizeY[tt] + xx[0])
			{
				EnemyY[t] = xx[9] + GroundSizeY[tt] + xx[0] + fy;
				if (EnemyVelY[t] < 0)
				{
					EnemyVelY[t] = -EnemyVelY[t] * 2 / 3;
				} // axzimen[t]=1;
			}
		}
	}

	// ブロック (Block)
	for (tt = 0; tt < tmax; tt++)
	{
		xx[0] = 200;
		xx[1] = 3000;
		xx[2] = 1000;
		xx[8] = BlockX[tt] - fx;
		xx[9] = BlockY[tt] - fy;
		if (BlockX[tt] - fx + xx[1] >= -12010 && BlockX[tt] - fx <= fxmax + 12000)
		{
			if (EnemyType[t] != EEnemyType::FALLING_CAT && EnemyType[t] != EEnemyType::BALL_BIG && BlockType[tt] != EBlockType::SWORD)
			{

				// 上 (Above)
				if (BlockType[tt] != EBlockType::ITEM_BLOCK_HIDDEN)
				{
					// if (ttype[tt]==117 && txtype[t]==1){ad[t]=-1500;}
					if (!(BlockType[tt] == EBlockType::NOTE_BLOCK))
					{
						// if (!(ttype[tt]==120 && txtype[t]==0)){
						if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + xx[1] - xx[0] * 1 && EnemyY[t] + EnemySizeY[t] - fy > xx[9] && EnemyY[t] + EnemySizeY[t] - fy < xx[9] + xx[1] && EnemyVelY[t] >= -100)
						{
							EnemyY[t] = xx[9] - EnemySizeY[t] + 100 + fy;
							EnemyVelY[t] = 0;
							axzimen[t] = 1;
							// ジャンプ台 (Ski jump)
							if (BlockType[tt] == EBlockType::TRAMPOLINE)
							{
								EnemyVelY[t] = -1600;
								azimentype[t] = 30;
							}
							//}
						}
					}
				}
				// 下 (Below)
				if (BlockType[tt] != EBlockType::NOTE_BLOCK)
				{
					if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + xx[1] - xx[0] * 1 && EnemyY[t] - fy > xx[9] + xx[1] - xx[1] && EnemyY[t] - fy < xx[9] + xx[1] + xx[0])
					{
						EnemyY[t] = xx[9] + xx[1] + xx[0] + fy;
						if (EnemyVelY[t] < 0)
						{
							EnemyVelY[t] = 0;
						} //=-ad[t]*2/3;}
						// if (ttype[t]==7){
						// for (t2=0;t2<tmax;t2++){if (ttype[t2]==5){ttype[t2]=6;}else if (ttype[t2]==6){ttype[t2]=5;}}
						// }
					}
				}
				// 左右 (Left and right)
				xx[27] = 0;
				if (((int)EnemyType[t] >= 100 || (BlockType[tt] != EBlockType::ITEM_BLOCK_HIDDEN || BlockType[tt] == EBlockType::ITEM_BLOCK_HIDDEN && EnemyType[t] == EEnemyType::SHELL)) && BlockType[tt] != EBlockType::NOTE_BLOCK)
				{
					if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] && EnemyX[t] - fx < xx[8] + xx[2] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] / 2 - xx[0] && EnemyY[t] - fy < xx[9] + xx[2])
					{
						EnemyX[t] = xx[8] - EnemySizeX[t] + fx;
						EnemyVelX[t] = 0;
						EnemyLookingDirection[t] = 0;
						xx[27] = 1;
					}
					if (EnemyX[t] + EnemySizeX[t] - fx >
							xx[8] + xx[1] - xx[0] * 2 &&
						EnemyX[t] - fx < xx[8] + xx[1] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] / 2 - xx[0] && EnemyY[t] - fy < xx[9] + xx[2])
					{
						EnemyX[t] = xx[8] + xx[1] + fx;
						EnemyVelX[t] = 0;
						EnemyLookingDirection[t] = 1;
						xx[27] = 1;
					}
					// こうらブレイク (Shell break)
					if (xx[27] == 1 && (BlockType[tt] == EBlockType::ITEM_BLOCK_HIDDEN || BlockType[tt] == EBlockType::BRICK) && EnemyType[t] == EEnemyType::SHELL)
					{
						if (BlockType[tt] == EBlockType::ITEM_BLOCK_HIDDEN)
						{
							PlaySound(Sounds[4]);
							BlockType[tt] = EBlockType::ITEM_BLOCK_OPEN;
							CreateExtraGraphic(BlockX[tt] + 10,
								  BlockY[tt], 0, -800,
								  0, 40, 3000, 3000, 0, 16);
						}
						else if (BlockType[tt] == EBlockType::BRICK)
						{
							PlaySound(Sounds[3]);
							CreateExtraGraphic(BlockX[tt] + 1200,
								  BlockY[tt] + 1200,
								  300, -1000, 0, 160, 1000, 1000, 1, 120);
							CreateExtraGraphic(BlockX[tt] + 1200,
								  BlockY[tt] + 1200,
								  -300, -1000, 0, 160, 1000, 1000, 1, 120);
							CreateExtraGraphic(BlockX[tt] + 1200,
								  BlockY[tt] + 1200,
								  240, -1400, 0, 160, 1000, 1000, 1, 120);
							CreateExtraGraphic(BlockX[tt] + 1200,
								  BlockY[tt] + 1200,
								  -240, -1400, 0, 160, 1000, 1000, 1, 120);
							BlockBreak(tt);
						}
					}
				}
			}
			if (EnemyType[t] == EEnemyType::FALLING_CAT || EnemyType[t] == EEnemyType::BALL_BIG)
			{
				if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] && EnemyX[t] - fx < xx[8] + xx[1] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] && EnemyY[t] - fy < xx[9] + xx[1])
				{
					PlaySound(Sounds[3]);
					CreateExtraGraphic(BlockX[tt] + 1200, BlockY[tt] + 1200, 300,
						  -1000, 0, 160, 1000, 1000, 1, 120);
					CreateExtraGraphic(BlockX[tt] + 1200, BlockY[tt] + 1200,
						  -300, -1000, 0, 160, 1000, 1000, 1, 120);
					CreateExtraGraphic(BlockX[tt] + 1200, BlockY[tt] + 1200, 240,
						  -1400, 0, 160, 1000, 1000, 1, 120);
					CreateExtraGraphic(BlockX[tt] + 1200, BlockY[tt] + 1200,
						  -240, -1400, 0, 160, 1000, 1000, 1, 120);
					BlockBreak(tt);
				}
			} // 90
		}
		// 剣とってクリア (Get the sword and clear the stage)
		if (BlockType[tt] == EBlockType::SWORD)
		{
			if (EnemyY[t] - fy > xx[9] - xx[0] * 2 - 2000 && EnemyY[t] - fy < xx[9] + xx[1] - xx[0] * 2 + 2000 && EnemyX[t] + EnemySizeX[t] - fx > xx[8] - 400 && EnemyX[t] - fx < xx[8] + xx[1])
			{
				BlockX[tt] = -800000; // PlaySound(Sounds[4]);
				sracttype[20] = 1;
				sron[20] = 1;
			}
		}
	} // tt

} // tekizimen

void RenderEnemies()
{
    // 敵キャラ (Enemy character)
    for (t = 0; t < amax; t++)
    {

        xx[0] = EnemyX[t] - fx;
        xx[1] = EnemyY[t] - fy;
        xx[2] = EnemySizeX[t] / 100;
        xx[3] = EnemySizeY[t] / 100;
        xx[14] = 3000;
        xx[16] = 0;
        if (xx[0] + xx[2] * 100 >= -10 - xx[14] && xx[1] <= fxmax + xx[14] && xx[1] + xx[3] * 100 >= -10 && xx[3] <= fymax)
        {
            if (EnemyLookingDirection[t] == 1)
            {
                mirror = 1;
            }
            if (EnemyType[t] == EEnemyType::SEAL && EnemySubType[t] == 1)
            {
                DrawVertTurnGraph(xx[0] / 100 + 13,
                                  xx[1] / 100 + 15, Sliced_GFX[(int)EEnemyType::SEAL][3]);
                xx[16] = 1;
            }
            if (EnemyType[t] == EEnemyType::MAGMA && EnemyVelY[t] >= 1)
            {
                DrawVertTurnGraph(xx[0] / 100 + 13,
                                  xx[1] / 100 + 15, Sliced_GFX[(int)EEnemyType::MAGMA][3]);
                xx[16] = 1;
            }
            if ((int)EnemyType[t] >= 100 && EnemyLookingDirection[t] == 1)
                mirror = 0;

            // メイン (main)
            if ((int)EnemyType[t] < 200 && xx[16] == 0 && EnemyType[t] != EEnemyType::DEFRAG && EnemyType[t] != EEnemyType::LASER && EnemyType[t] != EEnemyType::FALLING_CAT && EnemyType[t] != EEnemyType::MOLALLA)
            {
                if (!((EnemyType[t] == EEnemyType::EVIL_CLOUD || EnemyType[t] == EEnemyType::EVIL_CLOUD_TOUCHED) && EnemySubType[t] == 1))
                {
                    drawimage(Sliced_GFX[(int)EnemyType[t]][3],
                              xx[0] / 100, xx[1] / 100);
                }
            }
            // デフラグさん (Defrag-san)
            if (EnemyType[t] == EEnemyType::DEFRAG)
            {
                if (EnemyAITimer[t] >= 10 && EnemyAITimer[t] <= 19 || EnemyAITimer[t] >= 100 && EnemyAITimer[t] <= 119 || EnemyAITimer[t] >= 200)
                {
                    drawimage(Sliced_GFX[150][3], xx[0] / 100, xx[1] / 100);
                }
                else
                {
                    drawimage(Sliced_GFX[6][3], xx[0] / 100, xx[1] / 100);
                }
            }
            // モララー (Molalla)
            if (EnemyType[t] == EEnemyType::MOLALLA)
            {
                if (EnemySubType[t] == 0)
                    drawimage(Sliced_GFX[30][3], xx[0] / 100, xx[1] / 100);
                if (EnemySubType[t] == 1)
                    drawimage(Sliced_GFX[155][3], xx[0] / 100, xx[1] / 100);
            }
            // ステルス雲 (Stealth cloud)
            if ((EnemyType[t] == EEnemyType::EVIL_CLOUD_TOUCHED) && EnemySubType[t] == 1)
            {
                drawimage(Sliced_GFX[130][3], xx[0] / 100, xx[1] / 100);
            }

            if (EnemyType[t] == EEnemyType::LASER)
            {
                setcolor(250, 250, 0);
                fillrect(xx[0] / 100, xx[1] / 100, xx[2], xx[3]);
                setc0();
                drawrect(xx[0] / 100, xx[1] / 100, xx[2], xx[3]);
            }

            if (EnemyType[t] == EEnemyType::SPIKY_BLOCK)
            {

                if (EnemySubType[t] == 0)
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
                    xx[6] = 5 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }

                if (EnemySubType[t] == 1)
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
                    xx[6] = 4 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }

                if (EnemySubType[t] == 2)
                {
                    drawimage(Sliced_GFX[1][5], xx[0] / 100, xx[1] / 100);
                }
            }
            if (EnemyType[t] == EEnemyType::SPIKY_BLOCK_TOUCHED)
            {

                if (EnemySubType[t] == 0)
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
                    xx[6] = 5 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100 + 10, xx[1] / 100 + 9);
                }

                if (EnemySubType[t] == 1)
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
                    xx[6] = 4 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100 + 10, xx[1] / 100 + 9);
                }
            }
            // 偽ポール (Fake Pole)
            if (EnemyType[t] == EEnemyType::FAKE_POLE)
            {
                setc1();
                fillrect((xx[0]) / 100 + 10, (xx[1]) / 100, 10, xx[3]);
                setc0();
                drawrect((xx[0]) / 100 + 10, (xx[1]) / 100, 10, xx[3]);
                setcolor(0, 250, 200);
                fillarc((xx[0]) / 100 + 15 - 1, (xx[1]) / 100, 10, 10);
                setc0();
                drawarc((xx[0]) / 100 + 15 - 1, (xx[1]) / 100, 10, 10);

            } // 85

            // ニャッスン
            if (EnemyType[t] == EEnemyType::FALLING_CAT)
            {
                if (PlayerX >= EnemyX[t] - fx - PlayerSizeX - 4000 && PlayerX <= EnemyX[t] - fx + EnemySizeX[t] + 4000)
                {
                    drawimage(Sliced_GFX[152][3], xx[0] / 100, xx[1] / 100);
                }
                else
                {
                    drawimage(Sliced_GFX[86][3], xx[0] / 100, xx[1] / 100);
                }
            }

            if (EnemyType[t] == EEnemyType::BALL_NO_COLLISION)
                drawimage(Sliced_GFX[0][3], xx[0] / 100, xx[1] / 100);

            mirror = 0;
        }
    }
}

void RenderEnemiesTwo()
{
    // ファイアバー (Fire Bar)
    for (t = 0; t < amax; t++)
    {

        xx[0] = EnemyX[t] - fx;
        xx[1] = EnemyY[t] - fy;
        xx[14] = 12000;
        xx[16] = 0;
        if (EnemyType[t] == EEnemyType::FIREBAR_CLOCKWISE || EnemyType[t] == EEnemyType::FIREBAR_COUNTERCLOCKWISE)
        {
            if (xx[0] + xx[2] * 100 >= -10 - xx[14] && xx[1] <= fxmax + xx[14] && xx[1] + xx[3] * 100 >= -10 && xx[3] <= fymax)
            {

                for (tt = 0; tt <= EnemySubType[t] % 100; tt++)
                {
                    xx[26] = 18;
                    xd[4] = tt * xx[26] * cos(EnemyAITimer[t] * pai / 180 / 2);
                    xd[5] = tt * xx[26] * sin(EnemyAITimer[t] * pai / 180 / 2);
                    xx[24] = (int)xd[4];
                    xx[25] = (int)xd[5];
                    setcolor(230, 120, 0);
                    xx[23] = 8;
                    //+KZ: this checks rotation direction, was added in Syobon Action 2
                    if (EnemyType[t] == EEnemyType::FIREBAR_CLOCKWISE)
                    {
                        fillarc(xx[0] / 100 +
                                    xx[24],
                                xx[1] / 100 + xx[25], xx[23], xx[23]);
                        setcolor(0, 0, 0);
                        drawarc(xx[0] / 100 +
                                    xx[24],
                                xx[1] / 100 + xx[25], xx[23], xx[23]);
                    }
                    else
                    {
                        fillarc(xx[0] / 100 -
                                    xx[24],
                                xx[1] / 100 + xx[25], xx[23], xx[23]);
                        setcolor(0, 0, 0);
                        drawarc(xx[0] / 100 -
                                    xx[24],
                                xx[1] / 100 + xx[25], xx[23], xx[23]);
                    }
                }
            }
        }
    }

    // Syobon Action 3 Big Mushroom (WIP!)
    if (currentGame == ESyobonActionGame::SYOBON_ACTION_3 && fx >= 42000 && SA3_Level1MushroomTriggered)
    {
        SA3_Level1MushroomTimer++;
        DrawGraphZ(580 - fx / 100, (SA3_Level1MushroomTimer - 5) * 29, nullptr /*Big mushroom grapkz*/);
        if (SA3_Level1MushroomTimer == 10)
        {
            Health = 0; // nプレイヤー.hp
        }
        if (SA3_Level1MushroomTimer == 30)
        {
            SA3_Level1MushroomTriggered = false;
        }
    }
}

void HandleLifts()
{
    // リフト (Lift)
    for (t = 0; t < srmax; t++)
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
            switch (sracttype[t])
            {

            case 1:
                if (sron[t] == 1)
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
                if (srmove[t] == 0)
                {
                    srmuki[t] = 0;
                }
                else
                {
                    srmuki[t] = 1;
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
                if (sron[t] == 1)
                    LiftFrictionY[t] = 40;
                break;

            case 7:
                break;

            } // sw

            // if (srtype[t]==1){sre[10]=300;sre[11]=300;}

            // 乗ったとき (When I got on)
            if (!(mztm >= 1 && mztype == 1 && actaon[3] == 1) && Health >= 1)
            {
                if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY + PlayerSizeY < xx[9] + xx[1] && PlayerVelY >= -100)
                {
                    PlayerY = xx[9] - PlayerSizeY + 100;
                    // if (sracttype[t]!=7)PlayerGrounded=1;

                    if (srtype[t] == 1)
                    {
                        LiftVelY[10] = 900;
                        LiftVelY[11] = 900;
                    }

                    if (srsp[t] != 12)
                    {
                        PlayerGrounded = 1;
                        PlayerVelY = 0;
                    }
                    else
                    {
                        // すべり (Slip)
                        // md=0;GroundType=1;PlayerGrounded=1;
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
                    if ((sracttype[t] == 1) && sron[t] == 0)
                        sron[t] = 1;

                    if (sracttype[t] == 1 && sron[t] == 1 || sracttype[t] == 3 || sracttype[t] == 5)
                    {
                        PlayerY += LiftVelY[t];
                        // if (srmuki[t]==0)
                        // if (srf[t]<0)
                        // if (srmuki[t]==1)
                        // if (srf[t]>0)
                        // mb+=srsok[t];
                    }

                    if (sracttype[t] == 7)
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
                    if (srsp[t] == 1)
                    {
                        PlaySound(Sounds[3]);
                        CreateExtraGraphic(LiftX[t] + 200,
                              LiftY[t] - 1000,
                              -240, -1400, 0, 160, 4500, 4500, 2, 120);
                        CreateExtraGraphic(LiftX[t] + 4500 -
                                  200,
                              LiftY[t] - 1000,
                              240, -1400, 0, 160, 4500, 4500, 3, 120);
                        LiftX[t] = -70000000;
                    }

                    if (srsp[t] == 2)
                    {
                        PlayerVelX = -2400;
                        srmove[t] += 1;
                        if (srmove[t] >= 100)
                        {
                            Health = 0;
                            PlayerMessageType = 53;
                            PlayerMessageTimer = 30;
                            srmove[t] = -5000;
                        }
                    }

                    if (srsp[t] == 3)
                    {
                        PlayerVelX = 2400;
                        srmove[t] += 1;
                        if (srmove[t] >= 100)
                        {
                            Health = 0;
                            PlayerMessageType = 53;
                            PlayerMessageTimer = 30;
                            srmove[t] = -5000;
                        }
                    }
                    // if (srtype[t]==1){md=-600;mb-=610;Health-=1;if (mmutekion!=1)mmutekitm=40;}
                } // 判定内

                // 疲れ初期化
                if ((srsp[t] == 2 || srsp[t] == 3) && PlayerVelX != -2400 && srmove[t] > 0)
                {
                    srmove[t]--;
                }

                if (srsp[t] == 11)
                {
                    if (PlayerX + PlayerSizeX >
                            xx[8] + xx[0] - 2000 &&
                        PlayerX < xx[8] + xx[12] - xx[0])
                    {
                        sron[t] = 1;
                    } // && mb+mnobib>xx[9]-1000 && mb+mnobib<xx[9]+xx[1]+2000)
                    if (sron[t] == 1)
                    {
                        LiftFrictionY[t] = 60;
                        LiftY[t] += LiftVelY[t];
                    }
                }
                // トゲ(下) (Spikes (below))
                if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0] && PlayerY > xx[9] - xx[1] / 2 && PlayerY < xx[9] + xx[1] / 2)
                {
                    if (srtype[t] == 2)
                    {
                        if (PlayerVelY < 0)
                        {
                            PlayerVelY = -PlayerVelY;
                        }
                        PlayerY += 110;
                        if (mmutekitm <= 0)
                            Health -= 1;
                        if (mmutekion != 1)
                            mmutekitm = 40;
                    }
                }
                // 落下 (Falling)
                if (sracttype[t] == 6)
                {
                    if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + xx[12] - xx[0])
                    {
                        sron[t] = 1;
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

            if (sracttype[t] == 2 || sracttype[t] == 4)
            {
                if (srmuki[t] == 0)
                    LiftX[t] -= srsok[t];
                if (srmuki[t] == 1)
                    LiftX[t] += srsok[t];
            }
            if (sracttype[t] == 3 || sracttype[t] == 5)
            {
                if (srmuki[t] == 0)
                    LiftY[t] -= srsok[t];
                if (srmuki[t] == 1)
                    LiftY[t] += srsok[t];
            }
            // 敵キャラ適用 (Applies to enemy characters)
            for (tt = 0; tt < amax; tt++)
            {
                if (azimentype[tt] == 1)
                {
                    if (EnemyX[tt] + EnemySizeX[tt] - fx > xx[8] + xx[0] && EnemyX[tt] - fx < xx[8] + xx[12] - xx[0] && EnemyY[tt] + EnemySizeY[tt] > xx[11] - 100 && EnemyY[tt] + EnemySizeY[tt] < xx[11] + xx[1] + 500 && EnemyVelY[tt] >= -100)
                    {
                        EnemyY[tt] = xx[9] - EnemySizeY[tt] + 100;
                        EnemyVelY[tt] = 0;
                        axzimen[tt] = 1;
                    }
                }
            }
        }
    } // リフト (Lift)
}

void RenderLifts()
{
    // リフト (lift)
    for (t = 0; t < srmax; t++)
    {
        xx[0] = LiftX[t] - fx;
        xx[1] = LiftY[t] - fy;
        if (xx[0] + LiftSizeX[t] >= -10 && xx[1] <= fxmax + 12100 && LiftSizeX[t] / 100 >= 1)
        {
            xx[2] = 14;
            if (srsp[t] == 1)
            {
                xx[2] = 12;
            }

            if (srsp[t] <= 9 || srsp[t] >= 20)
            {
                setcolor(220, 220, 0);
                if (srsp[t] == 2 || srsp[t] == 3)
                {
                    setcolor(0, 220, 0);
                }
                if (srsp[t] == 21)
                {
                    setcolor(180, 180, 180);
                }
                fillrect((LiftX[t] - fx) / 100,
                         (LiftY[t] - fy) / 100, LiftSizeX[t] / 100, xx[2]);

                setcolor(180, 180, 0);
                if (srsp[t] == 2 || srsp[t] == 3)
                {
                    setcolor(0, 180, 0);
                }
                if (srsp[t] == 21)
                {
                    setcolor(150, 150, 150);
                }
                drawrect((LiftX[t] - fx) / 100,
                         (LiftY[t] - fy) / 100, LiftSizeX[t] / 100, xx[2]);
            }
            else if (srsp[t] <= 14)
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
                             LiftSizeX[t] / 100 - 40, 480);
                    setcolor(100, 80, 20);
                    drawrect((LiftX[t] - fx) / 100 +
                                 20,
                             (LiftY[t] - fy) / 100 +
                                 30,
                             LiftSizeX[t] / 100 - 40, 480);
                }
            }
            if (srsp[t] == 15)
            {
                for (t2 = 0; t2 <= 2; t2++)
                {
                    xx[6] = 1 + 0;
                    drawimage(Sliced_GFX[xx[6]][1],
                              (LiftX[t] - fx) / 100 +
                                  t2 * 29,
                              (LiftY[t] - fy) / 100);
                }
            } // 15
        }
    } // t
}

// 敵キャラ、アイテム作成 (Enemy character and item creation)
void CreateEntity(
    int PosX, //int xa
    int PosY, //int xb
    int VelX, //int xc
    int VelY, //int xd
    int xnotm,
    EEnemyType EntityType, // int xtype
    int EntitySubType // int xxtype
)
{
    int rz = 0;
    for (t1 = 0; t1 <= 1; t1++)
    {
        t1 = 2;
        if (EnemyX[EnemyCount] >= -9000 && EnemyX[EnemyCount] <= 30000)
            t1 = 0;
        rz++;

        if (rz <= amax)
        {
            t1 = 3;

            EnemyX[EnemyCount] = PosX;
            EnemyY[EnemyCount] = PosY; // ag[aco]=0;ah[aco]=0;ai[aco]=bb[t];//ad[t]=0;aeon[t]=1;
            EnemyVelX[EnemyCount] = VelX;
            EnemyVelY[EnemyCount] = VelY;
            if (EntitySubType > 100)
                EnemyVelX[EnemyCount] = EntitySubType;
            // ae[aco]=0;af[aco]=0;
            EnemyType[EnemyCount] = EntityType;
            if (EntitySubType >= 0 && EntitySubType <= 99100)
                EnemySubType[EnemyCount] = EntitySubType; // ahp[aco]=iz[bxtype[t]];aytm[aco]=0;
            // if (xxtype==1)end();
            anotm[EnemyCount] = xnotm;
            if (EnemyX[EnemyCount] - fx <= PlayerX + PlayerSizeX / 2)
                EnemyLookingDirection[EnemyCount] = 1;
            if (EnemyX[EnemyCount] - fx > PlayerX + PlayerSizeX / 2)
                EnemyLookingDirection[EnemyCount] = 0;
            if (EnemyBlockAppearTimer[EnemyCount] >= 1)
                EnemyLookingDirection[EnemyCount] = 1;
            if (EnemyBlockAppearTimer[EnemyCount] == 20)
                EnemyLookingDirection[EnemyCount] = 0;

            EnemySizeX[EnemyCount] = EnemyDefaultSizeX[(int)EnemyType[EnemyCount]];
            EnemySizeY[EnemyCount] = EnemyDefaultSizeY[(int)EnemyType[EnemyCount]];

            // 大砲音 (Cannon sound)
            if (EntityType == EEnemyType::BALL_ROCKET && CheckSoundMem(Sounds[10]) == 0)
            {
                PlaySound(Sounds[10]);
            }
            // ファイア音 (Fire sound)
            if (EntityType == EEnemyType::FLAME && CheckSoundMem(Sounds[18]) == 0)
            {
                PlaySound(Sounds[18]);
            }

            azimentype[EnemyCount] = 1;

            // if (atype[aco]<=30 && atype[aco]!=4)atm[aco]=20;

            // azimentype[aco]=1;

            //+KZ removed empty switch

            if (EntityType == EEnemyType::FIREBAR_CLOCKWISE)
            {
                EnemyAITimer[EnemyCount] = SyobonRand(179) + (-90);
            }

            EnemyCount += 1;
            if (EnemyCount >= amax - 1)
            {
                EnemyCount = 0;
            }
        } // t1

        // if (bz[t]==1){bz[t]=0;}
    } // rz

} // ayobi
