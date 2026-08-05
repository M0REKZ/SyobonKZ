#include <unordered_map>
#include "global_vars.h"
#include "main.h"
#include "entities.h"
#include "blocks.h"
#include "effects.h"
#include "loadg.h"
#include "lifts.h"
#include "player.h"
#include "objects.h"

//敵キャラ
int EnemyCount;
int EnemyX[ENEMY_MAX], EnemyY[ENEMY_MAX], EnemySizeX[ENEMY_MAX], EnemySizeY[ENEMY_MAX], EnemyVelX[ENEMY_MAX], EnemyVelY[ENEMY_MAX];
int EnemyFloatingTimer[ENEMY_MAX], EnemyBlockAppearTimer[ENEMY_MAX];
int EnemyActionX[ENEMY_MAX], EnemyActionY[ENEMY_MAX], EnemyMovementType[ENEMY_MAX], EnemyGrounded[ENEMY_MAX];
EEnemyType EnemyType[ENEMY_MAX];
EEnemySubType EnemySubType[ENEMY_MAX];
ELookingDirection EnemyLookingDirection[ENEMY_MAX];
int EnemyPlayerNoInteractTimer[ENEMY_MAX], EnemyDefaultSizeX[160], EnemyDefaultSizeY[160];
int EnemyAITimer[ENEMY_MAX];
int EnemyMessageTimer[ENEMY_MAX], EnemyMessageType[ENEMY_MAX];

//敵出現
int EnemyAppearCount;
int EnemyAppearX[ENEMY_APPEAR_MAX], EnemyAppearY[ENEMY_APPEAR_MAX], EnemyAppearTimer[ENEMY_APPEAR_MAX];
EEnemyType EnemyAppearType[ENEMY_APPEAR_MAX];
EEnemySubType EnemyAppearSubType[ENEMY_APPEAR_MAX];
int EnemyAppearMustPlace[ENEMY_APPEAR_MAX];

std::unordered_map<std::string, SDL_Surface *> apEnemyMessages;

void CreateEnemyMessageCache()
{
    Uint32 temp_color = GetColor(255, 255, 255);

    apEnemyMessages["ヤッフー!!"] = LoadGraph("text/enemy_30.bmp", false);
    apEnemyMessages["え?俺勝っちゃったの?"] = LoadGraph("text/enemy_29.bmp", false);
    apEnemyMessages["貴様の死に場所はここだ!"] = LoadGraph("text/enemy_23.bmp", false);
    apEnemyMessages["二度と会う事もないだろう"] = LoadGraph("text/enemy_27.bmp", false);
    apEnemyMessages["俺、最強!!"] = LoadGraph("text/enemy_26.bmp", false);
    apEnemyMessages["一昨日来やがれ!!"] = LoadGraph("text/enemy_28.bmp", false);
    apEnemyMessages["漢に後退の二文字は無い!!"] = LoadGraph("text/enemy_25.bmp", false);
    apEnemyMessages["ハッハァ!!"] = LoadGraph("text/enemy_21.bmp", false);
    apEnemyMessages["身の程知らずが……"] = LoadGraph("text/enemy_20.bmp", false);
    apEnemyMessages["油断が死を招く"] = LoadGraph("text/enemy_6.bmp", false);
    apEnemyMessages["おめでたい奴だ"] = LoadGraph("text/enemy_19.bmp", false);
    apEnemyMessages["屑が!!"] = LoadGraph("text/enemy_18.bmp", false);
    apEnemyMessages["無謀な……"] = LoadGraph("text/enemy_13.bmp", false);
    apEnemyMessages["二度と会う事もないだろう"] = LoadGraph("text/enemy_27.bmp", false);
    apEnemyMessages["僕は……負けない!!"] = LoadGraph("text/enemy_11.bmp", false);
    apEnemyMessages["貴様に見切れる筋は無い"] = LoadGraph("text/enemy_17.bmp", false);
    apEnemyMessages["今死ね、すぐ死ね、骨まで砕けろ!!"] = LoadGraph("text/enemy_12.bmp", false);
    apEnemyMessages["任務完了!!"] = LoadGraph("text/enemy_5.bmp", false);
    apEnemyMessages["鉄壁!!よって、無敵!!"] = LoadGraph("text/enemy_9.bmp", false);
    apEnemyMessages["丸腰で勝てるとでも?"] = LoadGraph("text/enemy_7.bmp", false);
    apEnemyMessages["パリイ!!"] = LoadGraph("text/enemy_24.bmp", false);
    apEnemyMessages["自業自得だ"] = LoadGraph("text/enemy_4.bmp", false);
    apEnemyMessages["Zzz"] = LoadGraph("text/enemy_16.bmp", false);
    apEnemyMessages["ク、クマー"] = LoadGraph("text/enemy_3.bmp", false);
    apEnemyMessages["食べるべきではなかった!!"] = LoadGraph("text/enemy_10.bmp", false);
    apEnemyMessages["うめぇ!!"] = LoadGraph("text/enemy_2.bmp", false);
    apEnemyMessages["ブロックを侮ったな?"] = LoadGraph("text/enemy_1.bmp", false);
    apEnemyMessages["シャキーン"] = LoadGraph("text/enemy_0.bmp", false);
    apEnemyMessages["波動砲!!"] = LoadGraph("text/enemy_15.bmp", false);
    apEnemyMessages["裏切られたとでも思ったか?"] = LoadGraph("text/enemy_22.bmp", false);
    apEnemyMessages["ポールアターック!!"] = LoadGraph("text/enemy_14.bmp", false);

    //+KZ: These are from the original Syobon Action, but got removed/modified in Syobon Action 2
    apEnemyMessages["？"] = LoadGraph("text/enemy_8.bmp", false);
    apEnemyMessages["HE☆TA☆RE"] = LoadGraph("text/hetare.bmp", false);
    apEnemyMessages["遅すぎるんだよ!!"] = LoadGraph("text/itstoolate.bmp", false);
    apEnemyMessages["フハハハハハハ"] = LoadGraph("text/hahahaha.bmp", false);
    apEnemyMessages["グゥレイトォ!!"] = LoadGraph("text/great.bmp", false);
    apEnemyMessages["さぁ 悪い子はどんどん(ry"] = LoadGraph("text/morebadkids.bmp", false);
    apEnemyMessages["粛清してやる!!"] = LoadGraph("text/illpurge.bmp", false);
    apEnemyMessages["ゆとりはいい 想像を絶する"] = LoadGraph("text/beyondimagination.bmp", false);
    apEnemyMessages["嘘だ!!"] = LoadGraph("text/thatsalie.bmp", false);
    apEnemyMessages["これぞ 必 殺!!"] = LoadGraph("text/suretokill.bmp", false);
    apEnemyMessages["ぷー クスクス"] = LoadGraph("text/poocouscous.bmp", false);
    apEnemyMessages["ごめんねぇ 強くてさぁ!!"] = LoadGraph("text/imsorryimstrong.bmp", false);
    apEnemyMessages["貴様 それでも軍人か!?"] = LoadGraph("text/stillasoldier.bmp", false);
    apEnemyMessages["戦闘力 1 のごみくずが…"] = LoadGraph("text/combatpowerofone.bmp", false);
    apEnemyMessages["性能の差だな…"] = LoadGraph("text/differenceinperfomance.bmp", false);
    apEnemyMessages["無駄無駄無駄無駄ァ!!"] = LoadGraph("text/uselessuseless.bmp", false);
}

void DestroyEnemyMessageCache()
{
    for(auto &pEnemyMsg : apEnemyMessages)
    {
        if(pEnemyMsg.second)
            SyobonKZFreeImage(pEnemyMsg.second);
    }
}

void HandleEnemies()
{
    // 敵キャラ (Enemy character)
    for (t = 0; t < ENEMY_MAX; t++)
    {
        xx[0] = EnemyX[t] - fx;
        xx[1] = EnemyY[t] - fy;
        xx[2] = EnemySizeX[t];
        xx[3] = EnemySizeY[t];
        xx[14] = 12000 * 1;
        if (EnemyPlayerNoInteractTimer[t] >= 0)
            EnemyPlayerNoInteractTimer[t]--;

        int player_pos_x = PlayerX + fx;
        int player_pos_y = PlayerY + fy;

        // Syobon Action 3
        if (currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
        {
            bool handled = false;
            //update
            switch (EnemyType[t])
            {
            case EEnemyType::SA3_JUMPSCARE_PLANT:

                EnemySizeX[t] = DOUBLE_TO_GAME_X_POS(1);
                EnemySizeY[t] = DOUBLE_TO_GAME_X_POS(1.5);

                if(EnemyAITimer[t] == 0)
                {
                    if(player_pos_x + PlayerSizeX >= EnemyX[t] && player_pos_x <= EnemyX[t] + EnemySizeX[t] &&
                    player_pos_y + PlayerSizeY >= EnemyY[t] - EnemySizeY[t] && player_pos_y <= EnemyY[t])
                    {
                        EnemyAITimer[t] = 1;
                        EnemyFloatingTimer[t] = EnemyY[t];
                        PlaySound(Sounds_KZ[0]);
                    }
                }
                else if(EnemyAITimer[t] != 3)
                {
                    if(player_pos_x + PlayerSizeX >= EnemyX[t] && player_pos_x <= EnemyX[t] + EnemySizeX[t] &&
                        player_pos_y + PlayerSizeY >= EnemyY[t] && player_pos_y <= EnemyY[t] + EnemySizeY[t])
                    {
                        PlayerHealth--;
                    }
                }

                if(EnemyAITimer[t] == 1)
                {
                    EnemyY[t] -= DOUBLE_TO_GAME_X_POS(0.5);
                    if(EnemyY[t] < EnemyFloatingTimer[t] - EnemySizeY[t])
                    {
                        EnemyY[t] = EnemyFloatingTimer[t] - EnemySizeY[t];
                        EnemyAITimer[t] = 2;
                    }
                }
                else if(EnemyAITimer[t] == 2)
                {
                    EnemyY[t] += DOUBLE_TO_GAME_X_POS(0.5);
                    if(EnemyY[t] > EnemyFloatingTimer[t])
                    {
                        EnemyY[t] = EnemyFloatingTimer[t];
                        EnemyAITimer[t] = 3;
                    }
                }
                handled = true;
                break;
            case EEnemyType::SA3_BIG_MUSHROOM_FALLING:

                if(EnemyX[t] <= -900000)
                    break;

                EnemyMovementType[t] = 0;
                EnemyY[t] += EnemyVelY[t];
                EnemySizeX[t] = EnemySizeY[t] = DOUBLE_TO_GAME_X_POS(4);

                if(EnemyY[t] > DOUBLE_TO_GAME_Y_POS(20))
                {
                    EnemyX[t] = -999999;
                }

                if(player_pos_x + PlayerSizeX >= EnemyX[t] && player_pos_x <= EnemyX[t] + EnemySizeX[t] &&
                    player_pos_y + PlayerSizeY >= EnemyY[t] && player_pos_y <= EnemyY[t] + EnemySizeY[t])
                {
                    PlayerHealth--;
                }

                handled = true;

                break;
            
            case EEnemyType::SA3_BIG_STONE:

                if(EnemyX[t] <= -900000)
                    break;

                EnemyMovementType[t] = 0;
                EnemyX[t] += EnemyVelX[t];
                EnemySizeX[t] = EnemySizeY[t] = 16000;

                if(player_pos_x + PlayerSizeX >= EnemyX[t] && player_pos_x <= EnemyX[t] + EnemySizeX[t] &&
                    player_pos_y + PlayerSizeY >= EnemyY[t] && player_pos_y <= EnemyY[t] + EnemySizeY[t])
                {
                    PlayerHealth--;
                }

                handled = true;

                break;
            case EEnemyType::SA3_FLYING_SHELL_JIEN:
                if(EnemyX[t] <= -900000)
                    break;

                if(EnemyFloatingTimer[t] < 100)
                {
                    EnemyVelY[t] = DOUBLE_TO_GAME_X_POS(0.05);
                }
                else if(EnemyFloatingTimer[t] >= 100 && EnemyFloatingTimer[t] < 200)
                {
                    EnemyVelY[t] = DOUBLE_TO_GAME_X_POS(-0.05);
                }
                else
                {
                    EnemyFloatingTimer[t] = 0;
                    EnemyVelY[t] = DOUBLE_TO_GAME_X_POS(0.05);
                }
                EnemyFloatingTimer[t]++;

                EnemyY[t] += EnemyVelY[t];
                EnemySizeX[t] = DOUBLE_TO_GAME_X_POS(2);
                EnemySizeY[t] = DOUBLE_TO_GAME_X_POS(1.3);

                HandleEnemyPlayerCollisionKZ(t);

                handled = true;
                break;

            case EEnemyType::ARAMAKI:
                //fast seals some times wont kill the player
                if(currentGame == ESyobonActionGame::SYOBON_ACTION_3)
                {
                    if(player_pos_x + PlayerSizeX >= EnemyX[t] && player_pos_x <= EnemyX[t] + EnemySizeX[t] &&
                        player_pos_y + PlayerSizeY >= EnemyY[t] && player_pos_y <= EnemyY[t] + EnemySizeY[t])
                    {
                        PlayerHealth--;

                        //set his message ("zzz")
                        EnemyMessageTimer[t] = 60;
                        EnemyMessageType[t] = 20;
                    }
                }
                break;

            case EEnemyType::SUPER_JIEN:
                if(EnemySubType[t] == EEnemySubType::SUPER_JIEN_SA3_HIDE_SPIKES)
                {
                    if(player_pos_x + PlayerSizeX >= EnemyX[t] && player_pos_x <= EnemyX[t] + EnemySizeX[t] &&
                        player_pos_y + PlayerSizeY >= EnemyY[t] && player_pos_y <= EnemyY[t] + EnemySizeY[t])
                    {
                        EnemySubType[t] = EEnemySubType::SUPER_JIEN_NORMAL;
                    }
                }
                break;

            case EEnemyType::CANNON_JIEN:
                if(EnemySubType[t] == EEnemySubType::CANNON_JIEN_SA3_GIANT)
                {
                    EnemySizeX[t] = DOUBLE_TO_GAME_X_POS(5);
                    EnemySizeY[t] = DOUBLE_TO_GAME_X_POS(5);

                    if(EnemyX[t] + EnemySizeX[t] * 2 > fx && (EnemyAITimer[t] == 1 || EnemyX[t] < fx + fxmax))
                    {
                        EnemyAITimer[t] = 1;
                        EnemyX[t] -= 400;

                        if(PlayerHealth > 0 && player_pos_x + PlayerSizeX >= EnemyX[t] && player_pos_x <= EnemyX[t] + EnemySizeX[t] &&
                        player_pos_y + PlayerSizeY >= EnemyY[t] && player_pos_y <= EnemyY[t] + EnemySizeY[t])
                        {
                            PlayerHealth--;

                            //set his message
                            EnemyMessageTimer[t] = 60;
                            EnemyMessageType[t] = SyobonRand(7) + 1 + 1000 + (SyobonLevel - 1) * 10;
                        }
                    }

                    handled = true;
                }    
                break;
            
            default:
                break;
            }

            int local_xx_14 = 12000;
            if ((EnemyX[t] - fx) + EnemySizeX[t] >= -local_xx_14 && (EnemyX[t] - fx) <= fxmax + local_xx_14 &&
                (EnemyY[t] - fy) + EnemySizeY[t] >= -10 - 9000 && (EnemyY[t] - fy) <= fymax + 20000)
            {

                if(EnemyType[t] > EEnemyType::LAST_LEGACY_ENEMY)
                {
                    HandleEnemiesBlocksKZ();
                }
            }

            if(handled)
                continue;
        }
        if (xx[0] + xx[2] >= -xx[14] && xx[0] <= fxmax + xx[14] && xx[1] + xx[3] >= -10 - 9000 && xx[1] <= fymax + 20000)
        {
            EnemyActionX[t] = 0;
            EnemyActionY[t] = 0;

            xx[10] = 0;

            switch (EnemyType[t])
            {
            //+KZ: These were not in the switch, however, since now they are a enum class, excluding them will give a warning
            default:
                break;

            case EEnemyType::JIEN:
                xx[10] = 100;
                break;

                // こうらの敵 (Shell enemy)
            case EEnemyType::SHELL_JIEN:
                xx[10] = 100;
                break;

                // こうら (Shell)
            case EEnemyType::SHELL:
                xx[10] = 0;
                xx[17] = 800;
                if (EnemySubType[t] >= EEnemySubType::SHELL_MOVING)
                    xx[10] = xx[17];
                // if (axtype[t]==1)xx[10]=xx[17];
                // if (axtype[t]==2)xx[10]=-xx[17];
                // 他の敵を倒す (Defeat other enemies)
                if (EnemySubType[t] >= EEnemySubType::SHELL_MOVING)
                {
                    for (tt = 0; tt < ENEMY_MAX; tt++)
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

                // あらまき (Aramaki)
            case EEnemyType::ARAMAKI:
                EnemyMovementType[t] = 0; // end();
                if (EnemySubType[t] == EEnemySubType::ARAMAKI_UP)
                {
                    EnemyY[t] -= 800;
                }
                if (EnemySubType[t] == EEnemySubType::ARAMAKI_DOWN)
                    EnemyY[t] += 1200;
                if(currentGame == ESyobonActionGame::SYOBON_ACTION_3)
                {
                    if(EnemySubType[t] == EEnemySubType::ARAMAKI_SYOBONKZ_VERTICAL)
                    {
                        EnemyY[t] += EnemyVelY[t];
                    }
                }

                // xx[10]=100;
                break;

                // スーパージエン (Super Jien)
            case EEnemyType::SUPER_JIEN:
                //+KZ: Spiky ball is slower in SA3
                xx[10] = currentGame != ESyobonActionGame::SYOBON_ACTION_3 ? 120 : 100;
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
                    if (EnemySubType[t] == EEnemySubType::SUPER_JIEN_JUMPER && PlayerGrounded == 0 && EnemyGrounded[t] == 1)
                    {
                        EnemyVelY[t] = -1600;
                        EnemyAITimer[t] = 40;
                        EnemyY[t] -= 1000;
                    }
                } //
                break;

                // クマー (Kuma)
            case EEnemyType::KUMA:
                xx[10] = 160;
                // azimentype[t]=2;
                break;

                // デフラグさん (Defrag-san)
            case EEnemyType::DEFRAG:
                if (EnemyMovementType[t] == 30)
                {
                    EnemyVelY[t] = -1600;
                    EnemyY[t] += EnemyVelY[t];
                }

                xx[10] = 120;
                if (EnemyAITimer[t] >= 10)
                {
                    EnemyAITimer[t]++;
                    if (PlayerHealth >= 1)
                    {
                        if (EnemyAITimer[t] <= 19)
                        {
                            PlayerX = xx[0];
                            PlayerY = xx[1] - 3000;
                            PlayerState = EPlayerState::PLAYING;
                        }
                        xx[10] = 0;
                        if (EnemyAITimer[t] == 20)
                        {
                            PlayerVelX = 700;
                            mkeytm = 24;
                            PlayerVelY = -1200;
                            PlayerY = xx[1] - 1000 - 3000;
                            EnemyLookingDirection[t] = LOOKING_RIGHT;
                            if (EnemySubType[t] == EEnemySubType::DEFRAG_GRAB_POLE)
                            {
                                PlayerVelX = 840;
                                EnemySubType[t] = EEnemySubType::DEFRAG_NORMAL;
                            }
                        }
                        if (EnemyAITimer[t] == 40)
                        {
                            EnemyLookingDirection[t] = LOOKING_LEFT;
                            EnemyAITimer[t] = 0;
                        }
                    }
                }
                // ポール捨て (Discarding the pole)
                if (EnemySubType[t] == EEnemySubType::DEFRAG_GRAB_POLE)
                {
                    for (tt = 0; tt < OBJECT_MAX; tt++)
                    {
                        if (ObjectType[tt] == EObjectType::GOAL_POLE)
                        {
                            // sa[sco]=xx[21]*100;sb[sco]=xx[22]*100;sc[sco]=3000;sd[sco]=(12-t)*3000;stype[sco]=300;sco++;
                            if (EnemyX[t] -
                                        fx >=
                                    -8000 &&
                                EnemyX[t] >=
                                    ObjectX[tt] +
                                        2000 &&
                                EnemyX[t] <= ObjectX[tt] + 3600 && EnemyGrounded[t] == 1)
                            {
                                ObjectX[tt] = -800000;
                                EnemyAITimer[t] = 100;
                            }
                        }
                    }

                    if (EnemyAITimer[t] == 100)
                    {
                        CreateEffectLegacy(EnemyX[t] + 1200 -
                                  1200,
                              EnemyY[t] + 3000 -
                                  10 * 3000 - 1500,
                              0, 0, 0, 0, 1000,
                              10 * 3000 - 1200, EEffectType::GOAL_POLE, 20);
                        if (PlayerState == EPlayerState::LEVEL_FINISH_ANIMATION)
                        {
                            PlayerState = EPlayerState::PLAYING;
                            StopSoundMem(Sounds[11]);
                            bgmchange(Music[1]);
                        }
                        for (t1 = 0; t1 < OBJECT_MAX; t1++)
                        {
                            if (ObjectType[t1] == EObjectType::TRIGGER_MULTI_LASER)
                                ObjectX[t1] = -80000000;
                        }
                    }
                    if (EnemyAITimer[t] == 120)
                    {
                        CreateEffectLegacy(EnemyX[t] + 1200 -
                                  1200,
                              EnemyY[t] + 3000 -
                                  10 * 3000 - 1500,
                              600, -1200, 0,
                              160, 1000, 10 * 3000 - 1200, EEffectType::GOAL_POLE, 240);
                        EnemyLookingDirection[t] = LOOKING_RIGHT;
                    }
                    // mc=700;mkeytm=24;md=-1200;mb=xx[1]-1000-3000;amuki[t]=1;if (axtype[t]==1){mc=840;axtype[t]=0;}}
                    if (EnemyAITimer[t] == 140)
                    {
                        EnemyLookingDirection[t] = LOOKING_LEFT;
                        EnemyAITimer[t] = 0;
                    }
                }
                if (EnemyAITimer[t] >= 220)
                {
                    EnemyAITimer[t] = 0;
                    EnemyLookingDirection[t] = LOOKING_LEFT;
                }
                // 他の敵を投げる (Throw other enemies)
                for (tt = 0; tt < ENEMY_MAX; tt++)
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
                            EnemyLookingDirection[tt] = LOOKING_RIGHT;
                            EnemyX[tt] = EnemyX[t] + 300;
                            EnemyY[tt] = EnemyY[t] - 3000;
                            EnemyBlockAppearTimer[tt] = 120; // aa[tt]=0;
                            EnemyAITimer[t] = 200;
                            EnemyLookingDirection[t] = LOOKING_RIGHT;
                        }
                    }
                }

                break;

                // ジエン大砲 (Jien Cannon) //+KZ: or "Cannon Jien" i guess, google translate is weird sometimes
            case EEnemyType::CANNON_JIEN:
                EnemyMovementType[t] = 0;
                xx[10] = 0;
                xx[11] = 400;
                if (EnemySubType[t] == EEnemySubType::CANNON_JIEN_NORMAL)
                    xx[10] = 400;
                if (EnemySubType[t] == EEnemySubType::CANNON_JIEN_BACKWARDS)
                    xx[10] = -400;
                if (EnemySubType[t] == EEnemySubType::CANNON_JIEN_UPWARDS)
                    EnemyY[t] -= 400;
                if (EnemySubType[t] == EEnemySubType::CANNON_JIEN_DOWNWARDS)
                    EnemyY[t] += 400;
                break;

                // スーパーブーン (Super Boon)
            case EEnemyType::SUPER_BOON:
                EnemyMovementType[t] = 0;
                xx[22] = 20;
                if (EnemyAITimer[t] == 0)
                {
                    EnemyFloatingTimer[t] += xx[22];
                    EnemyVelY[t] += xx[22];
                }
                if (EnemyAITimer[t] == 1)
                {
                    EnemyFloatingTimer[t] -= xx[22];
                    EnemyVelY[t] -= xx[22];
                }
                if (EnemyVelY[t] > 300)
                    EnemyVelY[t] = 300;
                if (EnemyVelY[t] < -300)
                    EnemyVelY[t] = -300;
                if (EnemyFloatingTimer[t] >= 1200)
                    EnemyAITimer[t] = 1;
                if (EnemyFloatingTimer[t] < -0)
                    EnemyAITimer[t] = 0;
                EnemyY[t] += EnemyVelY[t];
                // atype[t]=151;
                break;
                // ノーマルブーン (Normal Boon)
            case EEnemyType::NORMAL_BOON:
                EnemyMovementType[t] = 2;
                break;

                // ファイアー玉 (Fireball)
            case EEnemyType::MAGMA:
                EnemyMovementType[t] = 5;
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
                EnemyMovementType[t] = 0;
                xx[10] = 0;
                xx[11] = 400;
                if (EnemySubType[t] == EEnemySubType::FLAME_NORMAL)
                    xx[10] = 400;
                if (EnemySubType[t] == EEnemySubType::FLAME_BACKWARDS)
                    xx[10] = -400;
                break;

                // モララー (Morarā) //+KZ: also named Moralar, Molalla
            case EEnemyType::MOLALLA:
                EnemyAITimer[t] += 1;
                if (EnemySubType[t] == EEnemySubType::MOLALLA_ALIVE)
                {
                    if (EnemyAITimer[t] == 50 && PlayerY >= 6000)
                    {
                        EnemyVelX[t] = 300;
                        EnemyVelY[t] -= 1600;
                        EnemyY[t] -= 1000;
                    }

                    for (tt = 0; tt < ENEMY_MAX; tt++)
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
                                EnemySubType[t] = EEnemySubType::MOLALLA_DEAD;
                                EnemyVelY[t] = -1600;
                                EnemyMessageTimer[t] = 30;
                                EnemyMessageType[t] = 25;
                            }
                        }
                    }
                }
                if (EnemySubType[t] == EEnemySubType::MOLALLA_DEAD)
                {
                    EnemyMovementType[t] = 0;
                    EnemyY[t] += EnemyVelY[t];
                    EnemyVelY[t] += 120;
                }
                break;

                // レーザー (Laser)
            case EEnemyType::LASER:
                EnemyMovementType[t] = 0;
                xx[10] = 1600;
                if (EnemySubType[t] == EEnemySubType::LASER_10_DEGREE_UP)
                {
                    xx[10] = 1200;
                    EnemyY[t] -= 200;
                }
                if (EnemySubType[t] == EEnemySubType::LASER_10_DEGREE_DOWN)
                {
                    xx[10] = 1200;
                    EnemyY[t] += 200;
                }
                if (EnemySubType[t] == EEnemySubType::LASER_33_DEGREE_UP)
                {
                    xx[10] = 900;
                    EnemyY[t] -= 600;
                }
                if (EnemySubType[t] == EEnemySubType::LASER_33_DEGREE_DOWN)
                {
                    xx[10] = 900;
                    EnemyY[t] += 600;
                }
                break;

                // 雲の敵 (Enemy of the Clouds)
            case EEnemyType::EVIL_CLOUD:
                EnemyMovementType[t] = 0;
                // xx[10]=100;
                break;
            case EEnemyType::EVIL_CLOUD_TOUCHED:
                EnemyMovementType[t] = 0;
                break;
            case EEnemyType::SPIKY_BLOCK:
                EnemyMovementType[t] = 0;
                break;
            case EEnemyType::SPIKY_BLOCK_TOUCHED:
                EnemyMovementType[t] = 0;
                break;

            case EEnemyType::LAVA_FROM_PIPE:
                EnemyMovementType[t] = 2;
                break;

            case EEnemyType::FAKE_POLE:
                xx[23] = 400;
                if (EnemySubType[t] == EEnemySubType::FAKE_POLE_STAY)
                {
                    EnemySubType[t] = EEnemySubType::FAKE_POLE_TALKING;
                    EnemyLookingDirection[t] = LOOKING_RIGHT;
                }
                if (PlayerY >= 30000 && PlayerX >= EnemyX[t] - 3000 * 5 - fx && PlayerX <= EnemyX[t] - fx && EnemySubType[t] == EEnemySubType::FAKE_POLE_TALKING)
                {
                    EnemySubType[t] = EEnemySubType::FAKE_POLE_MOVE;
                    EnemyLookingDirection[t] = LOOKING_LEFT;
                }
                if (PlayerY >= 24000 && PlayerX <= EnemyX[t] + 3000 * 8 - fx && PlayerX >= EnemyX[t] - fx && EnemySubType[t] == EEnemySubType::FAKE_POLE_TALKING)
                {
                    EnemySubType[t] = EEnemySubType::FAKE_POLE_MOVE;
                    EnemyLookingDirection[t] = LOOKING_RIGHT;
                }
                if (EnemySubType[t] == EEnemySubType::FAKE_POLE_MOVE)
                    xx[10] = xx[23];
                break;

            case EEnemyType::NYASSUN:
                EnemyMovementType[t] = 4;
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
                EnemyMovementType[t] = 0;
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

                for (tt = 0; tt <= (int)EnemySubType[t] % 100; tt++)
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
                        PlayerHealth -= 1;
                        PlayerMessageType = 51;
                        PlayerMessageTimer = 30;
                    }
                }

                break;

                //+KZ: Syobon Action 2 inverted Fire Bar
            case EEnemyType::FIREBAR_COUNTERCLOCKWISE:
                EnemyMovementType[t] = 0;
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

                for (tt = 0; tt <= (int)EnemySubType[t] % 100; tt++)
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
                        PlayerHealth -= 1;
                        PlayerMessageType = 51;
                        PlayerMessageTimer = 30;
                    }
                }

                break;

            case EEnemyType::BIG_JIEN:
                xx[10] = 160;
                // azimentype[t]=0;
                break;

                // おいしいキノコ (Delicious mushrooms)
            case EEnemyType::MUSHROOM:
                EnemyMovementType[t] = 1;
                xx[10] = 100;

                // ほかの敵を巨大化 (Enlarge other enemies)
                if (EnemySubType[t] == EEnemySubType::MUSHROOM_GROW)
                {
                    for (tt = 0; tt < ENEMY_MAX; tt++)
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
                                if (EnemyType[tt] == EEnemyType::JIEN || EnemyType[tt] == EEnemyType::SUPER_JIEN)
                                {
                                    EnemyType[tt] = EEnemyType::BIG_JIEN; // PlaySound(Sounds[6]);
                                    EnemySizeX[tt] = 6400;
                                    EnemySizeY[tt] = 6300;
                                    EnemySubType[tt] = EEnemySubType::NONE;
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
                EnemyMovementType[t] = 1;
                xx[10] = 100;
                if (EnemySubType[t] == EEnemySubType::MUSHROOM_POISONOUS_FASTER)
                    xx[10] = 200;
                break;

                // 悪スター (Bad Star)
            case EEnemyType::BAD_STAR:
                EnemyMovementType[t] = 1;
                xx[10] = 200;
                if (EnemyGrounded[t] == 1)
                {
                    EnemyY[t] -= 1200;
                    EnemyVelY[t] = -1400;
                }
                break;

            case EEnemyType::JIEN_NO_COLLISION:
                EnemyMovementType[t] = 1;
                xx[10] = 100;
                break;

                /*
                    +KZ: there was a lot of commented out code here, i just removed it
                */

            } // sw

            if (EnemyBlockAppearTimer[t] >= 1)
                xx[10] = 0;

            if (EnemyLookingDirection[t] == 0)
                EnemyActionX[t] -= xx[10];
            if (EnemyLookingDirection[t] == 1)
                EnemyActionX[t] += xx[10];

            // 最大値 (Maximum value)
            xx[0] = 850;
            xx[1] = 1200;

            // if (mc>xx[0]){mc=xx[0];}
            // if (mc<-xx[0]){mc=-xx[0];}
            if (EnemyVelY[t] > xx[1] && EnemyMovementType[t] != 5)
            {
                EnemyVelY[t] = xx[1];
            }
            // 行動 (Action)
            EnemyX[t] += EnemyActionX[t]; // ab[t]+=aactb[t];

            if ((EnemyMovementType[t] >= 1 || EnemyMovementType[t] == -1) && EnemyBlockAppearTimer[t] <= 0)
            {
                // if (atype[t]==4)end();

                // 移動 (Move)
                EnemyX[t] += EnemyVelX[t];
                if (EnemyMovementType[t] >= 1 && EnemyMovementType[t] <= 3)
                {
                    EnemyY[t] += EnemyVelY[t];
                    EnemyVelY[t] += 120;
                } // ad[t]+=180;

                if (EnemyGrounded[t] == 1)
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

                EnemyGrounded[t] = 0;

                // 地面判定 (Ground judgment)
                if (EnemyMovementType[t] != 2)
                {
                    HandleEnemiesBlocks();
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

            if (PlayerX + PlayerSizeX > xx[8] + xx[0] * 2 && PlayerX < xx[8] + EnemySizeX[t] - xx[0] * 2 && PlayerY + PlayerSizeY > xx[9] - xx[5] && PlayerY + PlayerSizeY < xx[9] + xx[1] + xx[12] && (PlayerNoDamageTimer <= 0 || PlayerVelY >= 100) && EnemyBlockAppearTimer[t] <= 0)
            {
                if (EnemyType[t] != EEnemyType::SUPER_JIEN && EnemyType[t] != EEnemyType::MAGMA && EnemyType[t] != EEnemyType::FLAME && ((int)EnemyType[t] <= 78 || EnemyType[t] == EEnemyType::FAKE_POLE) && PlayerGrounded != 1 && PlayerState != EPlayerState::DEATH_ANIMATION)
                { // && atype[t]!=4 && atype[t]!=7){

                    if (EnemyType[t] == EEnemyType::JIEN)
                    {
                        if (EnemySubType[t] == EEnemySubType::JIEN_NORMAL)
                            EnemyX[t] = -900000;
                        if (EnemySubType[t] == EEnemySubType::JIEN_UNSTOMPABLE)
                        {
                            PlaySound(Sounds[5]);
                            PlayerY = xx[9] - 900 - EnemySizeY[t];
                            PlayerVelY = -2100;
                            xx[25] = 1;
                            actaon[2] = 0;
                        }
                    }

                    if (EnemyType[t] == EEnemyType::SHELL_JIEN)
                    {
                        EnemyType[t] = EEnemyType::SHELL;
                        EnemySizeY[t] = 3000;
                        if(
                            currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ||
                            (
                                currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 &&
                                EnemySubType[t] != EEnemySubType::SHELL_JIEN_INSTANT_KICK
                            )
                        )
                        {
                            EnemySubType[t] = EEnemySubType::SHELL_STAY;
                        }
                        else if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 &&
                            EnemySubType[t] == EEnemySubType::SHELL_JIEN_INSTANT_KICK)
                        {
                            EnemyY[t] += 1300; //otherwise some collision issues will happen

                            if (PlayerX +
                                        PlayerSizeX >
                                    xx[8] +
                                        xx[0] * 2 &&
                                PlayerX <
                                    xx[8] + EnemySizeX[t] / 2 - xx[0] * 4)
                            {
                                EnemySubType[t] = EEnemySubType::SHELL_MOVING;
                                EnemyLookingDirection[t] = LOOKING_RIGHT;
                            }
                            else
                            {
                                EnemySubType[t] = EEnemySubType::SHELL_MOVING;
                                EnemyLookingDirection[t] = LOOKING_LEFT;
                            }
                        }
                    }
                    // こうら (Shell)
                    else if (EnemyType[t] == EEnemyType::SHELL && PlayerVelY >= 0)
                    {
                        if (EnemySubType[t] == EEnemySubType::SHELL_MOVING || EnemySubType[t] == EEnemySubType::SHELL_MOVING_2)
                        {
                            EnemySubType[t] = EEnemySubType::SHELL_STAY;
                        }
                        else if (EnemySubType[t] == EEnemySubType::SHELL_STAY)
                        {
                            if (PlayerX +
                                        PlayerSizeX >
                                    xx[8] +
                                        xx[0] * 2 &&
                                PlayerX <
                                    xx[8] + EnemySizeX[t] / 2 - xx[0] * 4)
                            {
                                EnemySubType[t] = EEnemySubType::SHELL_MOVING;
                                EnemyLookingDirection[t] = LOOKING_RIGHT;
                            }
                            else
                            {
                                EnemySubType[t] = EEnemySubType::SHELL_MOVING;
                                EnemyLookingDirection[t] = LOOKING_LEFT;
                            }
                        }
                    }
                    if (EnemyType[t] == EEnemyType::ARAMAKI)
                    {
                        xx[25] = 1;
                    }

                    if (EnemyType[t] == EEnemyType::DEFRAG)
                    {
                        EnemyAITimer[t] = 10;
                        PlayerVelY = 0;
                        actaon[2] = 0;
                    }

                    if (EnemyType[t] == EEnemyType::CANNON_JIEN)
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
                    else
                    {
                        if (xx[25] == 0)
                        {
                            PlaySound(Sounds[5]);
                            PlayerY = xx[9] - 4000;
                            PlayerVelY = -1000;
                            EnemySubType[t] = EEnemySubType::FAKE_POLE_MOVE;
                        }
                    }

                    if (actaon[2] == 1 &&
                        //+KZ: you are not able to jump on seal in other games
                        (currentGame == ESyobonActionGame::SYOBON_ACTION_3 ?
                        EnemyType[t] != EEnemyType::ARAMAKI
                        :
                        true
                        )
                    )
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
            if (EnemyType[t] == EEnemyType::SUPER_JIEN || EnemyType[t] == EEnemyType::MAGMA || EnemyType[t] == EEnemyType::FLAME)
                xx[16] = -3000;
            if (EnemyType[t] == EEnemyType::SPIKY_BLOCK || EnemyType[t] == EEnemyType::SPIKY_BLOCK_TOUCHED || EnemyType[t] == EEnemyType::LAVA_FROM_PIPE)
                xx[16] = -3200;
            if (EnemyType[t] == EEnemyType::FAKE_POLE)
                xx[16] = -EnemySizeY[t] + 6000;
            if (PlayerX + PlayerSizeX > xx[8] + xx[4] && PlayerX < xx[8] + EnemySizeX[t] - xx[4] && PlayerY < xx[9] + EnemySizeY[t] + xx[15] && PlayerY + PlayerSizeY > xx[9] + EnemySizeY[t] - xx[0] + xx[16] && EnemyPlayerNoInteractTimer[t] <= 0 && EnemyBlockAppearTimer[t] <= 0)
            {
                if (PlayerInvincibleON == 1)
                {
                    EnemyX[t] = -9000000;
                }
                if (PlayerNoDamageTimer <= 0 && ((int)EnemyType[t] <= 99 || (int)EnemyType[t] >= 200))
                {
                    if (PlayerInvincibleON != 1 && PlayerState != EPlayerState::DEATH_ANIMATION)
                    {
                        // if (mmutekitm<=0)

                        // ダメージ (Damage)
                        if ((EnemyType[t] != EEnemyType::SHELL || EnemySubType[t] != EEnemySubType::NONE) && PlayerHealth >= 1)
                        {
                            if (EnemyType[t] != EEnemyType::DEFRAG)
                            {
                                PlayerHealth -= 1;
                                // mmutekitm=40;
                            }
                        }

                        if (EnemyType[t] == EEnemyType::DEFRAG)
                        {
                            EnemyAITimer[t] = 10;
                        }
                        // せりふ (Dialogue)
                        if (PlayerHealth == 0)
                        {

                            if (EnemyType[t] == EEnemyType::JIEN || EnemyType[t] == EEnemyType::CANNON_JIEN)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = SyobonRand(7) + 1 + 1000 + (SyobonLevel - 1) * 10;
                            }

                            if (EnemyType[t] == EEnemyType::SHELL_JIEN)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = SyobonRand(2) + 15;
                            }

                            if (EnemyType[t] == EEnemyType::SHELL && EnemySubType[t] >= EEnemySubType::SHELL_MOVING && PlayerNoDamageTimer <= 0)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = 18;
                            }

                            if (EnemyType[t] == EEnemyType::ARAMAKI)
                            {
                                EnemyMessageTimer[t] = 60;
                                EnemyMessageType[t] = 20;
                            }

                            if (EnemyType[t] == EEnemyType::SUPER_JIEN)
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

                            if (EnemyType[t] == EEnemyType::KUKKURU)
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

                        } // PlayerHealth==0

                        // こうら (Shell)
                        if (EnemyType[t] == EEnemyType::SHELL)
                        {
                            // if (axtype[t]==1 || axtype[t]==2){axtype[t]=0;}
                            if (EnemySubType[t] == EEnemySubType::SHELL_STAY)
                            {
                                if (PlayerX + PlayerSizeX > xx[8] + xx[0] * 2 && PlayerX < xx[8] + EnemySizeX[t] / 2 - xx[0] * 4)
                                {
                                    EnemySubType[t] = EEnemySubType::SHELL_MOVING;
                                    EnemyLookingDirection[t] = LOOKING_RIGHT;
                                    EnemyX[t] = PlayerX + PlayerSizeX + fx + PlayerVelX;
                                    PlayerNoDamageTimer = 5;
                                }
                                else
                                {
                                    EnemySubType[t] = EEnemySubType::SHELL_MOVING;
                                    EnemyLookingDirection[t] = LOOKING_LEFT;
                                    EnemyX[t] = PlayerX - EnemySizeX[t] + fx - PlayerVelX;
                                    PlayerNoDamageTimer = 5;
                                }
                            }
                            else
                            {
                                PlayerHealth -= 1;
                            } // mmutekitm=40;}
                        }
                    }
                }
                // else if (mmutekitm>=0 && mmutekitm<=2){mmutekitm+=1;}
                // アイテム (Item)
                if ((int)EnemyType[t] >= 100 && (int)EnemyType[t] <= 199)
                {

                    if (EnemyType[t] == EEnemyType::MUSHROOM && EnemySubType[t] == EEnemySubType::MUSHROOM_DELICIOUS)
                    {
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 1;
                        PlaySound(Sounds[9]);
                    }
                    if (EnemyType[t] == EEnemyType::MUSHROOM && EnemySubType[t] == EEnemySubType::MUSHROOM_NOT_POISONOUS)
                    {
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 2;
                        PlaySound(Sounds[9]);
                    }
                    if (EnemyType[t] == EEnemyType::MUSHROOM && EnemySubType[t] == EEnemySubType::MUSHROOM_GROW)
                    {
                        PlayerSizeX = 5200;
                        PlayerSizeY = 7300;
                        PlaySound(Sounds[9]);
                        PlayerX -= 1100;
                        PlayerY -= 4000;
                        PlayerState = EPlayerState::BIG_PLAYER;
                        PlayerHealth = 50000000;
                    }
                    if (EnemyType[t] == EEnemyType::MUSHROOM && EnemySubType[t] == EEnemySubType::MUSHROOM_SA3_1UP)
                    {
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 1;
                        PlaySound(Sounds_KZ[1]);
                    }

                    if (EnemyType[t] == EEnemyType::BURNING_FLOWER)
                    {
                        PlayerHealth -= 1;
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 11;
                    }
                    if (EnemyType[t] == EEnemyType::MUSHROOM_POISONOUS)
                    {
                        PlayerHealth -= 1;
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 10;
                    }
                    //?ボール (? Ball)
                    if (EnemyType[t] == EEnemyType::MYSTERY_BALL)
                    {
                        if (EnemySubType[t] == EEnemySubType::MYSTERY_BALL_LEVEL_1_2)
                        {
                            PlaySound(Sounds[4]);
                            ObjectAI[26] = 6;
                        }
                        if (EnemySubType[t] == EEnemySubType::MYSTERY_BALL_LEVEL_1_3)
                        {
                            BlockSubType[7] = EBlockSubType::MESSAGE_BLOCK_1_3_0_3;
                            PlaySound(Sounds[4]);

                            // CreateEntity(aa[t]-6*3000+1000,-3*3000,0,0,0,110,0);
                            CreateEnemyLegacy(EnemyX[t] -
                                             8 * 3000 -
                                             1000,
                                         -4 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, EEnemySubType::NONE);
                            CreateEnemyLegacy(EnemyX[t] -
                                             10 *
                                                 3000 +
                                             1000,
                                         -1 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, EEnemySubType::NONE);

                            CreateEnemyLegacy(EnemyX[t] +
                                             4 * 3000 +
                                             1000,
                                         -2 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, EEnemySubType::NONE);
                            CreateEnemyLegacy(EnemyX[t] +
                                             5 * 3000 -
                                             1000,
                                         -3 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, EEnemySubType::NONE);
                            CreateEnemyLegacy(EnemyX[t] +
                                             6 * 3000 +
                                             1000,
                                         -4 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, EEnemySubType::NONE);
                            CreateEnemyLegacy(EnemyX[t] +
                                             7 * 3000 -
                                             1000,
                                         -2 * 3000, 0, 0, 0, EEnemyType::BAD_STAR, EEnemySubType::NONE);
                            CreateEnemyLegacy(EnemyX[t] +
                                             8 * 3000 +
                                             1000,
                                         -2 * 3000 - 1000, 0, 0, 0, EEnemyType::BAD_STAR, EEnemySubType::NONE);
                            BlockY[0] += 3000 * 3;
                        }
                    } // 105

                    if (EnemyType[t] == EEnemyType::BAD_STAR)
                    {
                        PlayerHealth -= 1;
                        PlayerMessageTimer = 30;
                        PlayerMessageType = 3;
                    }

                    /*
                    if (atype[t]==101){mmutekitm=120;mmutekion=1;}
                    if (atype[t]==102){PlayerHealth-=1;mmutekitm=20;}
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
            if(currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                EnemyX[t] = -9000000;
        }

    } // t
}

//+KZ: uhhh i realized about lines like EnemyDefaultSizeX[(int)EnemyAppearType[t]], i dont recommend using EnemyAppear things
// but seems that EnemyAppear has more space than Enemy it self
void PlaceEnemies()
{
    // 敵キャラの配置 (Enemy character placement)
    for (t = 0; t < ENEMY_APPEAR_MAX; t++)
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

                if (EnemyAppearMustPlace[t] == 0 && EnemyAppearTimer[t] < 0 && EnemyAppearX[t] - fx >= fxmax + 2000 && EnemyAppearX[t] - fx < fxmax + 2000 + PlayerVelX && tt == 0)
                {
                    local_xx_0 = 1;
                    EnemyLookingDirection[EnemyCount] = LOOKING_LEFT;
                } // && mmuki==1
                if (EnemyAppearMustPlace[t] == 0 && EnemyAppearTimer[t] < 0 && EnemyAppearX[t] - fx >= -400 - EnemyDefaultSizeX[(int)EnemyAppearType[t]] + PlayerVelX && EnemyAppearX[t] - fx < -400 - EnemyDefaultSizeX[(int)EnemyAppearType[t]] && tt == 1)
                {
                    local_xx_0 = 1;
                    local_xx_1 = 1;
                    EnemyLookingDirection[EnemyCount] = LOOKING_RIGHT;
                } // && mmuki==0
                if (EnemyAppearMustPlace[t] == 1 && EnemyAppearX[t] - fx >= 0 - EnemyDefaultSizeX[(int)EnemyAppearType[t]] && EnemyAppearX[t] - fx <= fxmax + 4000 && EnemyAppearY[t] - fy >= -9000 && EnemyAppearY[t] - fy <= fymax + 4000 && EnemyAppearTimer[t] < 0)
                {
                    local_xx_0 = 1;
                    EnemyAppearMustPlace[t] = 0;
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
                    CreateEnemyLegacy(EnemyAppearX[t], EnemyAppearY[t], 0, 0, 0, EnemyAppearType[t], EnemyAppearSubType[t]);
                }

            } // tt
        }
    } // t
}

void HandleEnemiesMessages()
{
    // 敵キャラのメッセージ (Message from enemy character)
    setc0();
    for (t = 0; t < ENEMY_MAX; t++)
    {
        if (EnemyMessageTimer[t] >= 1)
        {
            EnemyMessageTimer[t]--; // end();

            xs[0] = "";

            // +KZ: Syobon Action 2 replaced many strings with duplicated ones for some reason
            // ill try to replace some duplicates with some of the original strings
            if (EnemyMessageType[t] == 1001)
                xs[0] = "遅すぎるんだよ!!"; //From original Syobon Action
            if (EnemyMessageType[t] == 1002)
                xs[0] = "無駄無駄無駄無駄ァ!!"; //From original Syobon Action
            if (EnemyMessageType[t] == 1003)
                xs[0] = "性能の差だな…"; //From original Syobon Action
            if (EnemyMessageType[t] == 1004)
                xs[0] = "ぷー クスクス"; //From original Syobon Action
            if (EnemyMessageType[t] == 1005)
                xs[0] = "俺、最強!!";
            if (EnemyMessageType[t] == 1006)
                xs[0] = "一昨日来やがれ!!";
            if (EnemyMessageType[t] == 1007)
                xs[0] = "漢に後退の二文字は無い!!";
            if (EnemyMessageType[t] == 1008)
                xs[0] = "ハッハァ!!";

            if (EnemyMessageType[t] == 1011)
                xs[0] = "嘘だ!!"; //From original Syobon Action
            if (EnemyMessageType[t] == 1012)
                xs[0] = "HE☆TA☆RE"; //From original Syobon Action
            if (EnemyMessageType[t] == 1013)
                xs[0] = "ごめんねぇ 強くてさぁ!!"; //From original Syobon Action
            if (EnemyMessageType[t] == 1014)
                xs[0] = "貴様 それでも軍人か!?"; //From original Syobon Action
            if (EnemyMessageType[t] == 1015)
                xs[0] = "ゆとりはいい 想像を絶する"; //From original Syobon Action
            if (EnemyMessageType[t] == 1016)
                xs[0] = "粛清してやる!!"; //From original Syobon Action
            if (EnemyMessageType[t] == 1017)
                xs[0] = "さぁ 悪い子はどんどん(ry"; //From original Syobon Action
            if (EnemyMessageType[t] == 1018)
                xs[0] = "戦闘力 1 のごみくずが…"; //From original Syobon Action

            if (EnemyMessageType[t] == 1021)
                xs[0] = "グゥレイトォ!!"; //From original Syobon Action
            if (EnemyMessageType[t] == 1022)
                xs[0] = "これぞ 必 殺!!"; //From original Syobon Action
            if (EnemyMessageType[t] == 1023)
                xs[0] = "二度と会う事もないだろう";
            if (EnemyMessageType[t] == 1024)
                xs[0] = "フハハハハハハ"; //From original Syobon Action
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
                xs[0] = "？"; //From original Syobon Action
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

void HandleEnemiesBlocks()
{

	// 壁 (Wall)
	for (tt = 0; tt < OBJECT_MAX; tt++)
	{
        if(
            (currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ?
                (
                    (((int)ObjectType[tt] > 99) &&
                    ObjectType[tt] <= EObjectType::LAST_LEGACY_OBJECT)
                    ||
                    (ObjectType[tt] >= EObjectType::SA3_TRIGGER_START &&
                    ObjectType[tt] <= EObjectType::SA3_TRIGGER_END)
                    ||
                    ObjectType[tt] == EObjectType::SA3_FAKE_PIPE_BODY
                )
                :
                ((int)ObjectType[tt] > 99)
            )
        )
            continue;
		if (ObjectX[tt] - fx + ObjectSizeX[tt] >= -12010 && ObjectX[tt] - fx <= fxmax + 12100)
		{
			xx[0] = 200;
			xx[2] = 1000;
			xx[1] = 2000; // anobia[t]

			xx[8] = ObjectX[tt] - fx;
			xx[9] = ObjectY[tt] - fy;
			if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] - xx[0] && EnemyX[t] - fx < xx[8] + xx[2] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] * 3 / 4 && EnemyY[t] - fy < xx[9] + ObjectSizeY[tt] - xx[2])
			{
				EnemyX[t] = xx[8] - xx[0] - EnemySizeX[t] + fx;
				EnemyLookingDirection[t] = LOOKING_LEFT;
			}
			if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + ObjectSizeX[tt] - xx[0] && EnemyX[t] - fx < xx[8] + ObjectSizeX[tt] + xx[0] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] * 3 / 4 && EnemyY[t] - fy < xx[9] + ObjectSizeY[tt] - xx[2])
			{
				EnemyX[t] = xx[8] + ObjectSizeX[tt] + xx[0] + fx;
				EnemyLookingDirection[t] = LOOKING_RIGHT;
			}
			// if (aa[t]+anobia[t]-fx>xx[8]+xx[0] && aa[t]-fx<xx[8]+sc[tt]-xx[0] && ab[t]+anobib[t]-fy>xx[9] && ab[t]+anobib[t]-fy<xx[9]+xx[1] && ad[t]>=-100){ab[t]=sb[tt]-fy-anobib[t]+100+fy;ad[t]=0;}//PlayerGrounded=1;}
			if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + ObjectSizeX[tt] - xx[0] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] && EnemyY[t] + EnemySizeY[t] - fy < xx[9] + ObjectSizeY[tt] - xx[1] && EnemyVelY[t] >= -100)
			{
				EnemyY[t] = ObjectY[tt] - fy - EnemySizeY[t] + 100 + fy;
				EnemyVelY[t] = 0;
				EnemyGrounded[t] = 1;
			}

			if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + ObjectSizeX[tt] - xx[0] && EnemyY[t] - fy > xx[9] + ObjectSizeY[tt] - xx[1] && EnemyY[t] - fy < xx[9] + ObjectSizeY[tt] + xx[0])
			{
				EnemyY[t] = xx[9] + ObjectSizeY[tt] + xx[0] + fy;
				if (EnemyVelY[t] < 0)
				{
					EnemyVelY[t] = -EnemyVelY[t] * 2 / 3;
				} // axzimen[t]=1;
			}
		}
	}

	// ブロック (Block)
	for (tt = 0; tt < BLOCK_MAX; tt++)
	{

        //skip untouchable blocks
        if(
            (
                BlockType[tt] == EBlockType::ITEM_BLOCK_HIDDEN &&
                EnemyType[t] == EEnemyType::SHELL &&
                currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 &&
                BlockSubType[tt] == EBlockSubType::ITEM_BLOCK_HIDDEN_SA3_NO_SHELL
            )
            ||
            (
                (currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ? false :
                    (
                        BlockType[t] == EBlockType::SYOBONKZ_HIDDEN_BLOCK &&
                        EnemyType[t] == EEnemyType::SHELL
                    )
                )
            )
        )
        {
            continue;
        }

		xx[0] = 200;
		xx[1] = 3000;
		xx[2] = 1000;
		xx[8] = BlockX[tt] - fx;
		xx[9] = BlockY[tt] - fy;
		if (BlockX[tt] - fx + xx[1] >= -12010 && BlockX[tt] - fx <= fxmax + 12000)
		{
			if (EnemyType[t] != EEnemyType::NYASSUN && EnemyType[t] != EEnemyType::BIG_JIEN && BlockType[tt] != EBlockType::SWORD)
			{

				// 上 (Above)
				if (
                    BlockType[tt] != EBlockType::ITEM_BLOCK_HIDDEN &&
                    (currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ? true : BlockType[t] != EBlockType::SYOBONKZ_HIDDEN_BLOCK)
                )
				{
					// if (ttype[tt]==117 && txtype[t]==1){ad[t]=-1500;}
					if (!(BlockType[tt] == EBlockType::NOTE_BLOCK))
					{
						// if (!(ttype[tt]==120 && txtype[t]==0)){
						if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + xx[1] - xx[0] * 1 && EnemyY[t] + EnemySizeY[t] - fy > xx[9] && EnemyY[t] + EnemySizeY[t] - fy < xx[9] + xx[1] && EnemyVelY[t] >= -100)
						{
							EnemyY[t] = xx[9] - EnemySizeY[t] + 100 + fy;
							EnemyVelY[t] = 0;
							EnemyGrounded[t] = 1;
							// ジャンプ台 (Ski jump)
							if (BlockType[tt] == EBlockType::TRAMPOLINE)
							{
								EnemyVelY[t] = -1600;
								EnemyMovementType[t] = 30;
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
				if (((int)EnemyType[t] >= 100 ||
                (BlockType[tt] != EBlockType::ITEM_BLOCK_HIDDEN ||
                    (BlockType[tt] == EBlockType::ITEM_BLOCK_HIDDEN && EnemyType[t] == EEnemyType::SHELL) ||
                    (currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ? false : BlockType[t] == EBlockType::SYOBONKZ_HIDDEN_BLOCK)
                ))
                && BlockType[tt] != EBlockType::NOTE_BLOCK)
				{

                    //+KZ: Syobon Action has broken physics, which makes 2-3 be inconsistent when trying to hit
                    //  the hidden block with the shell in the start, this patch adds a very specific collision
                    //  check only for that SPECIFIC shell and that SPECIFIC block in that SPECIFIC level!
                    if(currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 && SyobonRandomMode == 0 &&
                        (
                            SyobonWorld == 2 &&
                            SyobonLevel == 3 &&
                            SyobonSection == 0 &&

                            //check for specific types and position
                            EnemyType[t] == EEnemyType::SHELL &&
                            BlockType[tt] == EBlockType::ITEM_BLOCK_HIDDEN &&
                            BlockX[tt] == (45 * 29 * 100) && //yeah im checking for the position instead of the index
                            BlockY[tt] == ((11 * 29 - 12) * 100)
                        )
                    )
                    {
                        //copypasted collision code but removed check for Y axis
                        if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] && EnemyX[t] - fx < xx[8] + xx[2])
                        {
                            EnemyX[t] = xx[8] - EnemySizeX[t] + fx;
                            EnemyVelX[t] = 0;
                            EnemyLookingDirection[t] = LOOKING_LEFT;
                            xx[27] = 1;
                        }
                        if (EnemyX[t] + EnemySizeX[t] - fx >
                                xx[8] + xx[1] - xx[0] * 2 &&
                            EnemyX[t] - fx < xx[8] + xx[1])
                        {
                            EnemyX[t] = xx[8] + xx[1] + fx;
                            EnemyVelX[t] = 0;
                            EnemyLookingDirection[t] = LOOKING_RIGHT;
                            xx[27] = 1;
                        }
                    }

					if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] && EnemyX[t] - fx < xx[8] + xx[2] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] / 2 - xx[0] && EnemyY[t] - fy < xx[9] + xx[2])
					{
						EnemyX[t] = xx[8] - EnemySizeX[t] + fx;
						EnemyVelX[t] = 0;
						EnemyLookingDirection[t] = LOOKING_LEFT;
						xx[27] = 1;
					}
					if (EnemyX[t] + EnemySizeX[t] - fx >
							xx[8] + xx[1] - xx[0] * 2 &&
						EnemyX[t] - fx < xx[8] + xx[1] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] / 2 - xx[0] && EnemyY[t] - fy < xx[9] + xx[2])
					{
						EnemyX[t] = xx[8] + xx[1] + fx;
						EnemyVelX[t] = 0;
						EnemyLookingDirection[t] = LOOKING_RIGHT;
						xx[27] = 1;
					}
					// こうらブレイク (Shell break)
					if (xx[27] == 1 && (BlockType[tt] == EBlockType::ITEM_BLOCK_HIDDEN || BlockType[tt] == EBlockType::BRICK) && EnemyType[t] == EEnemyType::SHELL)
					{
						if (BlockType[tt] == EBlockType::ITEM_BLOCK_HIDDEN)
						{
							PlaySound(Sounds[4]);
							BlockType[tt] = EBlockType::ITEM_BLOCK_OPEN;
							CreateEffectLegacy(BlockX[tt] + 10,
								  BlockY[tt], 0, -800,
								  0, 40, 3000, 3000, EEffectType::COIN, 16);
						}
						else if (BlockType[tt] == EBlockType::BRICK)
						{
							PlaySound(Sounds[3]);
							CreateEffectLegacy(BlockX[tt] + 1200,
								  BlockY[tt] + 1200,
								  300, -1000, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
							CreateEffectLegacy(BlockX[tt] + 1200,
								  BlockY[tt] + 1200,
								  -300, -1000, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
							CreateEffectLegacy(BlockX[tt] + 1200,
								  BlockY[tt] + 1200,
								  240, -1400, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
							CreateEffectLegacy(BlockX[tt] + 1200,
								  BlockY[tt] + 1200,
								  -240, -1400, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
							BlockBreak(tt);
						}

                        //+KZ
                        if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 && BlockType[t] == EBlockType::SYOBONKZ_HIDDEN_BLOCK)
                        {
                            if(BlockSubType[t] == EBlockSubType::SYOBONKZ_HIDDEN_BLOCK_SPIKE_DOWN)
                            {
                                PlaySound(Sounds[14]);
                                BlockType[tt] = EBlockType::SPIKE;
                            }
                        }
					}
				}
			}
			if (EnemyType[t] == EEnemyType::NYASSUN || EnemyType[t] == EEnemyType::BIG_JIEN)
			{
				if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] && EnemyX[t] - fx < xx[8] + xx[1] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] && EnemyY[t] - fy < xx[9] + xx[1])
				{
					PlaySound(Sounds[3]);
					CreateEffectLegacy(BlockX[tt] + 1200, BlockY[tt] + 1200, 300,
						  -1000, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
					CreateEffectLegacy(BlockX[tt] + 1200, BlockY[tt] + 1200,
						  -300, -1000, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
					CreateEffectLegacy(BlockX[tt] + 1200, BlockY[tt] + 1200, 240,
						  -1400, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
					CreateEffectLegacy(BlockX[tt] + 1200, BlockY[tt] + 1200,
						  -240, -1400, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
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
				LiftMovementType[20] = 1;
				LiftON[20] = 1;
			}
		}
	} // tt

} // tekizimen

void RenderEnemies()
{
    // 敵キャラ (Enemy character)
    for (t = 0; t < ENEMY_MAX; t++)
    {
        if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
        {
            if(EnemyType[t] == EEnemyType::SA3_BIG_MUSHROOM_FALLING && EnemyX[t] >= -900000)
            {
                SyobonKZDrawGraphScaled((EnemyX[t] - fx)/100, (EnemyY[t] - fy)/100, 4, 4, Sliced_GFX[1][2]);
                continue;
            }
            else if(EnemyType[t] == EEnemyType::SA3_BIG_STONE)
            {
                int frame = ((int)(EnemyX[t] / 4.f)) % 6;
                DrawGraphZ((EnemyX[t] - fx)/100, (EnemyY[t] - fy)/100, Main_GFX_KZ[3 + frame]);
                continue;
            }
            else if(EnemyType[t] == EEnemyType::SA3_JUMPSCARE_PLANT)
            {
                if(EnemyAITimer[t] == 1)
                {
                    DrawGraphZ((EnemyX[t] - fx)/100, (EnemyY[t] - fy)/100, Main_GFX_KZ[9]);
                }
                else if(EnemyAITimer[t] == 2)
                {
                    DrawGraphZ((EnemyX[t] - fx)/100, (EnemyY[t] - fy)/100, Main_GFX_KZ[10]);
                }
                continue;
            }
            else if(EnemyType[t] == EEnemyType::SA3_FLYING_SHELL_JIEN)
            {
                if(GetNowCount() % 1000 < 900)
                {
                    DrawGraphZ((EnemyX[t] - fx)/100, (EnemyY[t] - fy)/100, Main_GFX_KZ[19]);
                }
                else
                {
                    DrawGraphZ((EnemyX[t] - fx)/100, (EnemyY[t] - fy)/100, Main_GFX_KZ[18]);
                }
            }
            else if(EnemyType[t] == EEnemyType::CANNON_JIEN && EnemySubType[t] == EEnemySubType::CANNON_JIEN_SA3_GIANT)
            {
                SyobonKZDrawGraphScaled((EnemyX[t] - fx)/100, (EnemyY[t] - fy)/100, 5, 5, Sliced_GFX[ 7 /* BALL_ROCKET */][3]);
                continue;
            }
            else if(EnemyType[t] == EEnemyType::MUSHROOM && EnemySubType[t] == EEnemySubType::MUSHROOM_SA3_1UP)
            {
                DrawGraphZ((EnemyX[t] - fx)/100, (EnemyY[t] - fy)/100, Sliced_GFX_KZ[5]);
                continue;
            }
        }

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
            if (EnemyType[t] == EEnemyType::ARAMAKI && (EnemySubType[t] == EEnemySubType::ARAMAKI_DOWN) ||
                (currentGame != ESyobonActionGame::SYOBON_ACTION_3 && EnemyType[t] == EEnemyType::ARAMAKI &&
                    EnemySubType[t] == EEnemySubType::ARAMAKI_SYOBONKZ_VERTICAL &&
                    EnemyVelY[t] > 0)
            )
            {
                DrawVertTurnGraph(xx[0] / 100 + 13,
                                  xx[1] / 100 + 15, Sliced_GFX[(int)EEnemyType::ARAMAKI][3]);
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
            if ((int)EnemyType[t] < 200 && xx[16] == 0 && EnemyType[t] != EEnemyType::DEFRAG && EnemyType[t] != EEnemyType::LASER && EnemyType[t] != EEnemyType::NYASSUN && EnemyType[t] != EEnemyType::MOLALLA)
            {
                if (!((EnemyType[t] == EEnemyType::EVIL_CLOUD || EnemyType[t] == EEnemyType::EVIL_CLOUD_TOUCHED) && EnemySubType[t] == EEnemySubType::EVIL_CLOUD_HIDDEN))
                {
                    //+KZ for SA3 spiky ball
                    if(EnemyType[t] == EEnemyType::SUPER_JIEN && EnemySubType[t] == EEnemySubType::SUPER_JIEN_SA3_HIDE_SPIKES)
                    {
                        drawimage(Sliced_GFX[0][3],
                                xx[0] / 100, (xx[1] / 100) + 6);
                    }
                    else //Syobon Action
                    {
                        drawimage(Sliced_GFX[(int)EnemyType[t]][3],
                                xx[0] / 100, xx[1] / 100);
                    }
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
                if (EnemySubType[t] == EEnemySubType::MOLALLA_ALIVE)
                    drawimage(Sliced_GFX[30][3], xx[0] / 100, xx[1] / 100);
                if (EnemySubType[t] == EEnemySubType::MOLALLA_DEAD)
                    drawimage(Sliced_GFX[155][3], xx[0] / 100, xx[1] / 100);
            }
            // ステルス雲 (Stealth cloud)
            if ((EnemyType[t] == EEnemyType::EVIL_CLOUD_TOUCHED) && EnemySubType[t] == EEnemySubType::EVIL_CLOUD_HIDDEN)
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

                if (EnemySubType[t] == EEnemySubType::SPIKY_BLOCK_GROUND_TOP)
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
                    xx[6] = 5 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }

                if (EnemySubType[t] == EEnemySubType::SPIKY_BLOCK_HARD_BLOCK)
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
                    xx[6] = 4 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }

                if (EnemySubType[t] == EEnemySubType::SPIKY_BLOCK_MESSAGE_BLOCK)
                {
                    drawimage(Sliced_GFX[1][5], xx[0] / 100, xx[1] / 100);
                }
            }
            if (EnemyType[t] == EEnemyType::SPIKY_BLOCK_TOUCHED)
            {

                if (EnemySubType[t] == EEnemySubType::SPIKY_BLOCK_TOUCHED_GROUND_TOP)
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
                    xx[6] = 5 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100 + 10, xx[1] / 100 + 9);
                }

                if (EnemySubType[t] == EEnemySubType::SPIKY_BLOCK_TOUCHED_HARD_BLOCK)
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

            // ニャッスン (Nyassun)
            if (EnemyType[t] == EEnemyType::NYASSUN)
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

            if (EnemyType[t] == EEnemyType::JIEN_NO_COLLISION)
                drawimage(Sliced_GFX[0][3], xx[0] / 100, xx[1] / 100);

            mirror = 0;
        }
    }
}

void RenderEnemiesTwo()
{
    // ファイアバー (Fire Bar)
    for (t = 0; t < ENEMY_MAX; t++)
    {

        xx[0] = EnemyX[t] - fx;
        xx[1] = EnemyY[t] - fy;
        xx[14] = 12000;
        xx[16] = 0;
        if (EnemyType[t] == EEnemyType::FIREBAR_CLOCKWISE || EnemyType[t] == EEnemyType::FIREBAR_COUNTERCLOCKWISE)
        {
            if (xx[0] + xx[2] * 100 >= -10 - xx[14] && xx[1] <= fxmax + xx[14] && xx[1] + xx[3] * 100 >= -10 && xx[3] <= fymax)
            {

                for (tt = 0; tt <= (int)EnemySubType[t] % 100; tt++)
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
}

void HandleEnemiesBlocksKZ()
{
    // ブロック (Block)
	for (int block_index = 0; block_index < BLOCK_MAX; block_index++)
	{
		xx[0] = 200;
		xx[1] = 3000;
		xx[2] = 1000;
		xx[8] = BlockX[block_index] - fx;
		xx[9] = BlockY[block_index] - fy;
		if (BlockX[block_index] - fx + xx[1] >= -12010 && BlockX[block_index] - fx <= fxmax + 12000)
		{
            //no need to check left right collision for this one
            if(EnemyType[t] == EEnemyType::SA3_BIG_MUSHROOM_FALLING ||
                EnemyType[t] == EEnemyType::SA3_BIG_STONE)
            {
                if(
                    EnemyX[t] + EnemySizeX[t] >= BlockX[block_index] && EnemyX[t] < BlockX[block_index] + xx[1] &&
                    EnemyY[t] + EnemySizeY[t] >= BlockY[block_index] && EnemyY[t] < BlockY[block_index] + xx[1]
                )
                {
                    if(BlockType[block_index] != EBlockType::COIN)
                    {
                        PlaySound(Sounds[3]);

                        CreateEffect(GAME_X_POS_TO_DOUBLE(BlockX[block_index] + 1200), GAME_Y_POS_TO_DOUBLE(BlockY[block_index] + 1200), GAME_X_POS_TO_DOUBLE(300), GAME_X_POS_TO_DOUBLE(-1000), 0, GAME_X_POS_TO_DOUBLE(160), GAME_X_POS_TO_DOUBLE(1000), GAME_X_POS_TO_DOUBLE(1000), EEffectType::BLOCK_FRAGMENT, 120);

                        CreateEffect(GAME_X_POS_TO_DOUBLE(BlockX[block_index] + 1200), GAME_Y_POS_TO_DOUBLE(BlockY[block_index] + 1200), GAME_X_POS_TO_DOUBLE(-300), GAME_X_POS_TO_DOUBLE(-1000), 0, GAME_X_POS_TO_DOUBLE(160), GAME_X_POS_TO_DOUBLE(1000), GAME_X_POS_TO_DOUBLE(1000), EEffectType::BLOCK_FRAGMENT, 120);

                        CreateEffect(GAME_X_POS_TO_DOUBLE(BlockX[block_index] + 1200), GAME_Y_POS_TO_DOUBLE(BlockY[block_index] + 1200), GAME_X_POS_TO_DOUBLE(240), GAME_X_POS_TO_DOUBLE(-1400), 0, GAME_X_POS_TO_DOUBLE(160), GAME_X_POS_TO_DOUBLE(1000), GAME_X_POS_TO_DOUBLE(1000), EEffectType::BLOCK_FRAGMENT, 120);

                        CreateEffect(GAME_X_POS_TO_DOUBLE(BlockX[block_index] + 1200), GAME_Y_POS_TO_DOUBLE(BlockY[block_index] + 1200), GAME_X_POS_TO_DOUBLE(-240), GAME_X_POS_TO_DOUBLE(-1400), 0, GAME_X_POS_TO_DOUBLE(160), GAME_X_POS_TO_DOUBLE(1000), GAME_X_POS_TO_DOUBLE(1000), EEffectType::BLOCK_FRAGMENT, 120);

                        BlockBreak(block_index);
                    }
                }

                continue;
            }


			//Above
            if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + xx[1] - xx[0] * 1 && EnemyY[t] + EnemySizeY[t] - fy > xx[9] && EnemyY[t] + EnemySizeY[t] - fy < xx[9] + xx[1] && EnemyVelY[t] >= -100)
            {
                EnemyY[t] = xx[9] - EnemySizeY[t] + 100 + fy;
                EnemyVelY[t] = 0;
                EnemyGrounded[t] = 1;
                // ジャンプ台 (Ski jump)
                if (BlockType[block_index] == EBlockType::TRAMPOLINE)
                {
                    EnemyVelY[t] = -1600;
                    EnemyMovementType[t] = 30;
                }
            }

			
            if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] + xx[0] && EnemyX[t] - fx < xx[8] + xx[1] - xx[0] * 1 && EnemyY[t] - fy > xx[9] + xx[1] - xx[1] && EnemyY[t] - fy < xx[9] + xx[1] + xx[0])
            {   
                EnemyY[t] = xx[9] + xx[1] + xx[0] + fy;
                if (EnemyVelY[t] < 0)
                {
                    EnemyVelY[t] = 0;
                }
            }
				
			// 左右 (Left and right)
			Uint8 hit_left_right = 0;
			
            if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] && EnemyX[t] - fx < xx[8] + xx[2] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] / 2 - xx[0] && EnemyY[t] - fy < xx[9] + xx[2])
            {
                EnemyX[t] = xx[8] - EnemySizeX[t] + fx;
                EnemyVelX[t] = 0;
                EnemyLookingDirection[t] = LOOKING_LEFT;
                hit_left_right = 1;
            }
            if (EnemyX[t] + EnemySizeX[t] - fx >
                    xx[8] + xx[1] - xx[0] * 2 &&
                EnemyX[t] - fx < xx[8] + xx[1] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] + xx[1] / 2 - xx[0] && EnemyY[t] - fy < xx[9] + xx[2])
            {
                EnemyX[t] = xx[8] + xx[1] + fx;
                EnemyVelX[t] = 0;
                EnemyLookingDirection[t] = LOOKING_RIGHT;
                hit_left_right = -1;
            }
					
			/*if (EnemyType[t] == EEnemyType::FALLING_CAT || EnemyType[t] == EEnemyType::BALL_BIG)
			{
				if (EnemyX[t] + EnemySizeX[t] - fx > xx[8] && EnemyX[t] - fx < xx[8] + xx[1] && EnemyY[t] + EnemySizeY[t] - fy > xx[9] && EnemyY[t] - fy < xx[9] + xx[1])
				{
					PlaySound(Sounds[3]);
					CreateEffectLegacy(BlockX[tt] + 1200, BlockY[tt] + 1200, 300,
						  -1000, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
					CreateEffectLegacy(BlockX[tt] + 1200, BlockY[tt] + 1200,
						  -300, -1000, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
					CreateEffectLegacy(BlockX[tt] + 1200, BlockY[tt] + 1200, 240,
						  -1400, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
					CreateEffectLegacy(BlockX[tt] + 1200, BlockY[tt] + 1200,
						  -240, -1400, 0, 160, 1000, 1000, EEffectType::BLOCK_FRAGMENT, 120);
					BlockBreak(tt);
				}
			} */
		}
	}
}

void HandleEnemyPlayerCollisionKZ(int enemy_index)
{
    if(PlayerState == EPlayerState::DEATH_ANIMATION)
        return;

    //above of the enemy
    if (
        PlayerX + PlayerSizeX + fx > EnemyX[enemy_index] + 500 &&
        PlayerX + fx < EnemyX[enemy_index] + EnemySizeX[enemy_index] - 500 &&
        PlayerY + PlayerSizeY + fy > EnemyY[enemy_index] + 800 &&
        PlayerY + PlayerSizeY + fy < EnemyY[enemy_index] + 1600 + (PlayerVelY >= 100 ? PlayerVelY : 0) &&
        (PlayerNoDamageTimer <= 0 || PlayerVelY >= 100) &&
        EnemyBlockAppearTimer[enemy_index] <= 0
    )
    {
        bool can_jump_key_bounce = false;
        switch(EnemyType[enemy_index])
        {
            case EEnemyType::SA3_FLYING_SHELL_JIEN:
                PlaySound(Sounds[5]);
                EnemyType[enemy_index] = EEnemyType::SHELL_JIEN;
                PlayerY = (EnemyY[enemy_index] - 900 - EnemySizeY[enemy_index]) - fy;
                PlayerVelY = -1000;
                can_jump_key_bounce = true;
                break;
            
            default:
                break;
        }

        if(can_jump_key_bounce)
        {
            if (actaon[2] == 1)
            {
                PlayerVelY = -1600;
                actaon[2] = 0;
            }
        }
    }

    if(
        PlayerX + PlayerSizeX + fx > EnemyX[t] + 500 &&
        PlayerX + fx < EnemyX[t] + EnemySizeX[t] - 500 &&
        PlayerY + fy < EnemyY[t] + EnemySizeY[t] - 500 &&
        PlayerY + PlayerSizeY + fy > EnemyY[t] + EnemySizeY[t] - 250 /* + 0 xx[16] is 0 for most types */ &&
        EnemyPlayerNoInteractTimer[t] <= 0 &&
        EnemyBlockAppearTimer[t] <= 0
    )
    {
        switch(EnemyType[enemy_index])
        {
            case EEnemyType::SA3_FLYING_SHELL_JIEN:
                PlayerHealth = 0;
                break;
            
            default:
                break;
        }
    }
}

int CreateEnemy(double PosX, double PosY, double VelX, double VelY, EEnemyType EntityType,
    EEnemySubType EntitySubType, ELookingDirection LookingDirection, int PlayerNoInteractTimer, int index)
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
        //use EnemyCount to keep compat with CreateEnemyLegacy()
        index = EnemyCount++;
        if(EnemyCount == ENEMY_MAX)
            EnemyCount = 0;
    }

    if(index >= 0 && index < ENEMY_MAX)
    {
        EnemyX[index] = (int)PosX;
        EnemyY[index] = (int)PosY;
        EnemyVelX[index] = VelX * BLOCK_DEFAULT_SIZE * 100;
        EnemyVelY[index] = VelY * BLOCK_DEFAULT_SIZE * 100;
        EnemyType[index] = EntityType;
        EnemySubType[index] = EntitySubType;

        EnemyLookingDirection[index] = LookingDirection;

        EnemyPlayerNoInteractTimer[index] = PlayerNoInteractTimer;

        EnemyAITimer[index] = 0;

        EnemyMovementType[index] = 1;

        int Type = (int)EnemyType[index];

        //avoid out of bounds memory access
        if(
            Type >= 0 &&
            Type < (sizeof(EnemyDefaultSizeX) / sizeof(int)) &&
            Type < (sizeof(EnemyDefaultSizeY) / sizeof(int))
        )
        {
            EnemySizeX[index] = EnemyDefaultSizeX[Type];
            EnemySizeY[index] = EnemyDefaultSizeY[Type];
        }
        else
        {
            EnemySizeX[index] = EnemySizeY[index] = 0;
        }
    }
    else
    {
        fprintf(stderr, "CreateEnemy - Could not create entity %d %d at %d %d! (index %d)", EntityType, EntitySubType, (int)PosX, (int)PosY, index);
    }

    return index;
}

int QueueEnemyAppear(double PosX, double PosY, EEnemyType EntityType, EEnemySubType EntitySubType, int Timer, int index)
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
        //use EnemyCount to keep compat with legacy behavior
        index = EnemyAppearCount++;
        if(EnemyAppearCount == ENEMY_MAX)
            EnemyAppearCount = 0;
    }

    if(index >= 0 && index < ENEMY_MAX)
    {
        EnemyAppearX[index] = (int)PosX;
        EnemyAppearY[index] = (int)PosY;
        EnemyAppearType[index] = EntityType;
        EnemyAppearSubType[index] = EntitySubType;

        EnemyAppearTimer[index] = Timer;

        EnemyAppearMustPlace[index] = 1; //to make PlaceEntities() place it
    }
    else
    {
        fprintf(stderr, "QueueEnemyAppear - Could not create entity appear %d %d at %d %d! (index %d)", EntityType, EntitySubType, (int)PosX, (int)PosY, index);
    }

    return index;
}

void ClearAllEnemies()
{
    for(int i = 0; i < ENEMY_MAX; ++i)
    {
        EnemyX[i] = std::numeric_limits<int>::min();
        EnemyY[i] = std::numeric_limits<int>::min();
        EnemySizeX[i] = 0;
        EnemySizeY[i] = 0;
        EnemyVelX[i] = 0;
        EnemyVelY[i] = 0;

        EnemyLookingDirection[i] = LOOKING_LEFT;

        EnemyFloatingTimer[i] = 0;

        EnemyActionX[i] = 0;
        EnemyActionY[i] = 0;
        EnemyMovementType[i] = 0;
        EnemyGrounded[i] = 0;

        //the player will ignore a extremely high block type
        EnemyType[i] = EEnemyType::JIEN;

        EnemySubType[i] = EEnemySubType::NONE;

        EnemyAITimer[i] = 0;
        EnemyBlockAppearTimer[i] = 0;
        EnemyPlayerNoInteractTimer[i] = 0;
        EnemyMessageTimer[i] = 0;
        EnemyMessageType[i] = 0;
    }

    for(int i = 0; i < ENEMY_APPEAR_MAX; ++i)
    {
        //the enemies will ignore blocks with a very low or high X position
        EnemyAppearX[i] = std::numeric_limits<int>::min();
        EnemyAppearY[i] = std::numeric_limits<int>::min();

        //the player will ignore a extremely high block type
        EnemyAppearTimer[i] = 0;

        EnemyAppearType[i] = EEnemyType::JIEN;
        EnemyAppearSubType[i] = EEnemySubType::NONE;

        EnemyAppearMustPlace[i] = 1;
    }

    EnemyCount = 0;
    EnemyAppearCount = 0;
}

// 敵キャラ、アイテム作成 (Enemy character and item creation)
void CreateEnemyLegacy(
    int PosX, //int xa
    int PosY, //int xb
    int VelX, //int xc
    int VelY, //int xd
    int PlayerNoInteractTimer, //int xnotm,
    EEnemyType EntityType, // int xtype
    EEnemySubType EntitySubType // int xxtype
)
{
    int rz = 0;
    for (t1 = 0; t1 <= 1; t1++)
    {
        t1 = 2;
        if (EnemyX[EnemyCount] >= -9000 && EnemyX[EnemyCount] <= 30000)
            t1 = 0;
        rz++;

        if (rz <= ENEMY_MAX)
        {
            t1 = 3;

            EnemyX[EnemyCount] = PosX;
            EnemyY[EnemyCount] = PosY; // ag[aco]=0;ah[aco]=0;ai[aco]=bb[t];//ad[t]=0;aeon[t]=1;
            EnemyVelX[EnemyCount] = VelX;
            EnemyVelY[EnemyCount] = VelY;
            if ((int)EntitySubType > 100)
                EnemyVelX[EnemyCount] = (int)EntitySubType;
            // ae[aco]=0;af[aco]=0;
            EnemyType[EnemyCount] = EntityType;
            if ((int)EntitySubType >= 0 && (int)EntitySubType <= 99100)
                EnemySubType[EnemyCount] = EntitySubType; // ahp[aco]=iz[bxtype[t]];aytm[aco]=0;
            // if (xxtype==1)end();
            EnemyPlayerNoInteractTimer[EnemyCount] = PlayerNoInteractTimer;
            if (EnemyX[EnemyCount] - fx <= PlayerX + PlayerSizeX / 2)
                EnemyLookingDirection[EnemyCount] = LOOKING_RIGHT;
            if (EnemyX[EnemyCount] - fx > PlayerX + PlayerSizeX / 2)
                EnemyLookingDirection[EnemyCount] = LOOKING_LEFT;
            if (EnemyBlockAppearTimer[EnemyCount] >= 1)
                EnemyLookingDirection[EnemyCount] = LOOKING_RIGHT;
            if (EnemyBlockAppearTimer[EnemyCount] == 20)
                EnemyLookingDirection[EnemyCount] = LOOKING_LEFT;

            EnemySizeX[EnemyCount] = EnemyDefaultSizeX[(int)EnemyType[EnemyCount]];
            EnemySizeY[EnemyCount] = EnemyDefaultSizeY[(int)EnemyType[EnemyCount]];

            // 大砲音 (Cannon sound)
            if (EntityType == EEnemyType::CANNON_JIEN && CheckSoundMem(Sounds[10]) == 0)
            {
                PlaySound(Sounds[10]);
            }
            // ファイア音 (Fire sound)
            if (EntityType == EEnemyType::FLAME && CheckSoundMem(Sounds[18]) == 0)
            {
                PlaySound(Sounds[18]);
            }

            EnemyMovementType[EnemyCount] = 1;

            // if (atype[aco]<=30 && atype[aco]!=4)atm[aco]=20;

            // azimentype[aco]=1;

            //+KZ removed empty switch

            if (EntityType == EEnemyType::FIREBAR_CLOCKWISE)
            {
                EnemyAITimer[EnemyCount] = SyobonRand(179) + (-90);
            }

            EnemyCount += 1;
            if (EnemyCount >= ENEMY_MAX - 1)
            {
                EnemyCount = 0;
            }
        } // t1

        // if (bz[t]==1){bz[t]=0;}
    } // rz

} // ayobi
