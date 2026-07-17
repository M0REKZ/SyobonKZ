#include <unordered_map>
#include "global_vars.h"
#include "main.h"
#include "player.h"
#include "entities.h"
#include "extra_graphics.h"
#include "blocks.h"
#include "title.h"
#include "config.h"
#include "loadg.h"

std::unordered_map<std::string, SDL_Surface *> apPlayerMessages;

//+KZ for SA3 falling floor
int prev_player_vel_y = 0;
int prev_player_grounded = 0;

void CreatePlayerMessageCache()
{
    Uint32 temp_color = GetColor(255, 255, 255);

    apPlayerMessages["お、おいしい!!"] = LoadGraph("text/player_10.bmp", false);
    apPlayerMessages["毒は無いが……"] = LoadGraph("text/player_9.bmp", false);
    apPlayerMessages["刺さった!!"] = LoadGraph("text/player_8.bmp", false);
    apPlayerMessages["食べるべきではなかった!!"] = LoadGraph("text/player_7.bmp", false);
    apPlayerMessages["俺は燃える男だ!!"] = LoadGraph("text/player_6.bmp", false);
    apPlayerMessages["体が……焼ける……"] = LoadGraph("text/player_4.bmp", false);
    apPlayerMessages[ "たーまやー!!"] = LoadGraph("text/player_2.bmp", false);
    apPlayerMessages["見事にオワタ"] = LoadGraph("text/player_1.bmp", false);
    apPlayerMessages["足が、足がぁ!!"] = LoadGraph("text/player_5.bmp", false);
    apPlayerMessages["流石は摂氏800度!!"] = LoadGraph("text/player_0.bmp", false);
    apPlayerMessages["溶岩と合体したい……"] = LoadGraph("text/player_3.bmp", false);
}

void DestroyPlayerMessageCache()
{
    for(auto &pPlayerMsg : apPlayerMessages)
    {
        if(pPlayerMsg.second)
            SyobonKZFreeImage(pPlayerMsg.second);
    }
}

void HandlePlayer()
{
    if(SyobonState != ESyobonGameState::TITLE)
        HandlePlayerInput();

    prev_player_vel_y = PlayerVelY;
    prev_player_grounded = PlayerGrounded;

    // 加速による移動 (Movement due to acceleration)
    xx[0] = 40;
    xx[1] = 700;
    xx[8] = 500;
    xx[9] = 700;
    xx[12] = 1;
    xx[13] = 2;

    // すべり補正 (Slip correction)
    if (PlayerGroundType == EPlayerGroundType::SLIP)
    {
        xx[0] = 20;
        xx[12] = 9;
        xx[13] = 10;
    }
    // if (PlayerGrounded==0){xx[0]-=15;}
    if (actaon[0] == -1)
    {
        if (!(PlayerGrounded == 0 && PlayerVelX < -xx[8]))
        {
            if (PlayerVelX >= -xx[9])
            {
                PlayerVelX -= xx[0];
                if (PlayerVelX < -xx[9])
                {
                    PlayerVelX = -xx[9] - 1;
                }
            }
            if (PlayerVelX < -xx[9] && atktm <= 0)
                PlayerVelX -= xx[0] / 10;
        }
        if (PlayerGroundType != EPlayerGroundType::SLIP)
        {
            if (PlayerVelX > 100 && PlayerGrounded == 0)
            {
                PlayerVelX -= xx[0] * 2 / 3;
            }
            if (PlayerVelX > 100 && PlayerGrounded == 1)
            {
                PlayerVelX -= xx[0];
                if (PlayerGrounded == 1)
                {
                    PlayerVelX -= xx[0] * 1 / 2;
                }
            }
            actaon[0] = 3;
        }
    }

    if (actaon[0] == 1)
    {
        if (!(PlayerGrounded == 0 && PlayerVelX > xx[8]))
        {
            if (PlayerVelX <= xx[9])
            {
                PlayerVelX += xx[0];
                if (PlayerVelX > xx[9])
                {
                    PlayerVelX = xx[9] + 1;
                }
            }
            if (PlayerVelX > xx[9] && atktm <= 0)
                PlayerVelX += xx[0] / 10;
        }
        if (PlayerGroundType != EPlayerGroundType::SLIP)
        {
            if (PlayerVelX < -100 && PlayerGrounded == 0)
            {
                PlayerVelX += xx[0] * 2 / 3;
            }
            if (PlayerVelX < -100 && PlayerGrounded == 1)
            {
                PlayerVelX += xx[0];
                if (PlayerGrounded == 1)
                {
                    PlayerVelX += xx[0] * 1 / 2;
                }
            }
            actaon[0] = 3;
        }
    }

    // すべり補正初期化 (Initialization of slip correction)
    if (PlayerGrounded != 1)
        PlayerGroundType = EPlayerGroundType::NORMAL;

    // ジャンプ (Jump)
    if (mjumptm >= 0)
        mjumptm--;
    if (actaon[1] == 1 && PlayerGrounded == 1)
    {
        PlayerY -= 400;
        PlayerVelY = -1200;
        mjumptm = 10;

        // PlaySound( "jump.mp3" , DX_PLAYTYPE_NORMAL ) ;

        // PlayMusic( "SE/jump.mp3" , DX_PLAYTYPE_NORMAL ) ;

        // PlaySoundMem( Sounds[1], DX_PLAYTYPE_NORMAL ) ;

        // PlaySoundMem( Sounds[1], DX_PLAYTYPE_BACK) ;
        PlaySound(Sounds[1]);

        /*
        md=-1040;
        xx[1]=600;if (mc>xx[1] || mc<=-xx[1]){md=-1400;}
        xx[1]=7;xx[2]=400;
        if (mkasok>xx[1] && (mc>xx[2] || mc<=-xx[2])){
        md=-1600;
        if (mc>=800 || mc<=-800){md=-1800;}
        }
        */

        PlayerGrounded = 0;
    }
    if (actaon[1] <= 9)
        actaon[1] = 0;

    // if (actaon[1]==1){my+=xx[1];actaon[1]=0;}

    //}//陸地 (Land)

    if (PlayerNoDamageTimer >= -1)
        PlayerNoDamageTimer--;

    // HPがなくなったとき (When HP runs out)
    if (Health <= 0 && Health >= -9)
    {
        mkeytm = 12;
        Health = -20;
        PlayerState = 200;
        PlayerAITimer = 0;
        //SyobonKZHaltChannel(-1);
        //+KZ: halt all channels except some sounds
        for(int ch = 0; ch < SYOBONKZ_MIX_CHANNELS; ch++)
        {
            SyobonKZChunk * snd = SyobonKZGetLastSoundInChannel(ch);
            if(snd != Sounds_KZ[0])
                SyobonKZHaltChannel(ch);
        }

        SyobonKZHaltMusic();
        PlaySound(Sounds[12]);
        //StopSoundMem(Sounds[16]); //+KZ this is not needed since we already halted all channels
    } // Health
    // if (Health<=-10){
    if (PlayerState == 200)
    {
        if (PlayerAITimer <= 11)
        {
            PlayerVelX = 0;
            PlayerVelY = 0;
        }
        if (PlayerAITimer == 12)
        {
            PlayerVelY = -1200;
        }
        if (PlayerAITimer >= 12)
        {
            PlayerVelX = 0;
        }
        if (PlayerAITimer >= 100 || fast == 1)
        {
            InGameInitialized = 0;
            if(SyobonState != ESyobonGameState::TITLE)
                SyobonState = ESyobonGameState::LIVES_SPLASH;
            PlayerAITimer = 0;
            mkeytm = 0;
            Lives--;
            if (fast == 1)
                PlayerState = 0;
        } // mtm>=100
    } // mtype==200

    // 音符によるワープ (Warp using musical notes)
    if (PlayerState == 2)
    {
        PlayerAITimer++;

        mkeytm = 2;
        PlayerVelY = -1500;
        if (PlayerY <= -6000)
        {
            blackx = 1;
            blacktm = 20;
            SyobonSection += 5;
            SyobonKZHaltMusic();
            PlayerAITimer = 0;
            PlayerState = 0;
            mkeytm = -1;
        }
    } // 2

    // ジャンプ台アウト
    if (PlayerState == 3)
    {
        PlayerVelY = -2400;
        if (PlayerY <= -6000)
        {
            PlayerY = -80000000;
            Health = 0;
        }
    }
    // mtypeによる特殊的な移動 (Special movement using mtype)
    if (PlayerState >= 100)
    {
        PlayerAITimer++;

        // 普通の土管 (ordinary drainpipe)
        //+KZ: did google translated it wrong? anyways this is where all pipes are handled
        if (PlayerState == 100)
        {
            if (PlayerSubState == 0)
            {
                PlayerVelX = 0;
                PlayerVelY = 0;
                t = 28;
                if (PlayerAITimer <= 16)
                {
                    PlayerY += 240;
                    PlayerRocketPipeTrapVelY = 100;
                }
                if (PlayerAITimer == 17)
                {
                    PlayerY = -80000000;
                }
                if (PlayerAITimer == 23)
                {
                    ObjectX[t] -= 100;
                }
                if (PlayerAITimer >= 44 && PlayerAITimer <= 60)
                {
                    if (PlayerAITimer % 2 == 0)
                        ObjectX[t] += 200;
                    if (PlayerAITimer % 2 == 1)
                        ObjectX[t] -= 200;
                }
                if (PlayerAITimer >= 61 && PlayerAITimer <= 77)
                {
                    if (PlayerAITimer % 2 == 0)
                        ObjectX[t] += 400;
                    if (PlayerAITimer % 2 == 1)
                        ObjectX[t] -= 400;
                }
                if (PlayerAITimer >= 78 && PlayerAITimer <= 78 + 16)
                {
                    if (PlayerAITimer % 2 == 0)
                        ObjectX[t] += 600;
                    if (PlayerAITimer % 2 == 1)
                        ObjectX[t] -= 600;
                }
                if (PlayerAITimer >= 110)
                {
                    ObjectY[t] -= PlayerRocketPipeTrapVelY;
                    PlayerRocketPipeTrapVelY += 80;
                    if (PlayerRocketPipeTrapVelY > 1600)
                        PlayerRocketPipeTrapVelY = 1600;
                }
                if (PlayerAITimer == 160)
                {
                    PlayerState = 0;
                    Health--;
                }
            }
            // ふっとばし (Knock it away)
            else if (PlayerSubState == 10)
            {
                PlayerVelX = 0;
                PlayerVelY = 0;
                if (PlayerAITimer <= 16)
                {
                    PlayerX += 240;
                } // mzz=100;}
                if (PlayerAITimer == 16)
                    PlayerY -= 1100;
                if (PlayerAITimer == 20)
                    PlaySound(Sounds[10]);

                if (PlayerAITimer >= 24)
                {
                    PlayerX -= 2000;
                    PlayerLookingDirection = LOOKING_LEFT;
                }
                if (PlayerAITimer >= 48)
                {
                    PlayerState = 0;
                    Health--;
                }
            }
            else
            {
                PlayerVelX = 0;
                PlayerVelY = 0;
                if (PlayerAITimer <= 16 && PlayerSubState != 3)
                {
                    PlayerY += 240;
                } // mzz=100;}
                if (PlayerAITimer <= 16 && PlayerSubState == 3)
                {
                    PlayerX += 240;
                }
                if (PlayerAITimer == 19 && PlayerSubState == 2)
                {
                    Health = 0;
                    PlayerState = 2000;
                    PlayerAITimer = 0;
                    PlayerMessageTimer = 30;
                    PlayerMessageType = 51;
                }
                if (PlayerAITimer == 19 && PlayerSubState == 5)
                {
                    Health = 0;
                    PlayerState = 2000;
                    PlayerAITimer = 0;
                    PlayerMessageTimer = 30;
                    PlayerMessageType = 52;
                }
                if (PlayerAITimer == 20)
                {
                    if (PlayerSubState == 6)
                    {
                        SyobonSection += 10;
                    }
                    else
                    {
                        SyobonSection++;
                    }
                    PlayerY = -80000000;
                    PlayerSubState = 0;
                    blackx = 1;
                    blacktm = 20;
                    SyobonKZHaltMusic();
                }
            }
        } // 00

        if (PlayerState == 300)
        {
            mkeytm = 3;
            if (PlayerAITimer <= 1)
            {
                PlayerVelX = 0;
                PlayerVelY = 0;
            }
            if (PlayerAITimer >= 2 && PlayerAITimer <= 42)
            {
                PlayerVelY = 600;
                PlayerLookingDirection = LOOKING_RIGHT;
            }
            if (PlayerAITimer > 43 && PlayerAITimer <= 108)
            {
                PlayerVelX = 300;
            }
            if (PlayerAITimer == 110)
            {
                PlayerY = -80000000;
                PlayerVelX = 0;
            }
            if (PlayerAITimer == 250)
            {
                //+KZ: save progress
                {
                    SyobonGlobalConfig.LevelsFinished.insert({currentGame, SyobonWorld, SyobonLevel});
                    SaveConfig();
                }

                //+KZ: patch for level 3-1 finish
                // so we dont get stuck in a invalid level (3-2 does not exist)
                if(currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 &&
                    (
                        SyobonWorld == 3 &&
                        SyobonLevel == 1 &&
                        SyobonSection == 0
                    )
                )
                {
                    SyobonState = ESyobonGameState::TITLE;
                    Lives = 2;
                    SyobonStateTimer = 0;
                    SyobonLevel = 0;
                    SyobonSection = 0;
                    CurrentPlayerCheckpoint = 0;
                    InGameInitialized = 0;
                }
                else
                {
                    SyobonLevel++;
                    SyobonSection = 0;
                    InGameInitialized = 0;
                    CurrentPlayerCheckpoint = 0;
                    if(SyobonState != ESyobonGameState::TITLE)
                        SyobonState = ESyobonGameState::LIVES_SPLASH;
                    SyobonStateTimer = 0;
                }
            }
        } // mtype==300

        if (PlayerState == 301 || PlayerState == 302)
        {
            mkeytm = 3;

            if (PlayerAITimer <= 1)
            {
                PlayerVelX = 0;
                PlayerVelY = 0;
            }

            if (PlayerAITimer >= 2 && (PlayerState == 301 && PlayerAITimer <= 102 || PlayerState == 302 && PlayerAITimer <= 60))
            {
                xx[5] = 500;
                PlayerX -= xx[5];
                fx += xx[5];
                fzx += xx[5];
            }

            //+KZ: Sword ending does not work in Syobon Action 1
            //  however, seems it was "fixed" in Syobon Action 2...
            //  but we want the original version, right?
            //  Lets "un-fix" it for level 1-4 so the chicken trap works
            if (
                (currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 && SyobonRandomMode == 0 &&
                SyobonWorld == 1 && SyobonLevel == 4 && SyobonSection == 0)
                ?
                (PlayerState == 301 || (PlayerState == 302 && PlayerAITimer >= 2 && PlayerAITimer <= 100)) //Original Syobon Action
                :
                ((PlayerState == 301 || PlayerState == 302) && PlayerAITimer >= 2 && PlayerAITimer <= 100) //Syobon Action 2
            )
            {
                PlayerVelX = 250;
                PlayerLookingDirection = LOOKING_RIGHT;
            }

            if (PlayerAITimer == 200)
            {
                PlaySound(Sounds[17]);
                if (PlayerState == 301)
                {
                    BackgroundX[BackgroundCount] = 117 * 29 * 100 - 1100;
                    BackgroundY[BackgroundCount] = 4 * 29 * 100;
                    BackgroundType[BackgroundCount] = EDecorationType::TEXT_GAME_CLEAR;
                    BackgroundCount++;
                    if (BackgroundCount >= BACKGROUND_MAX)
                        BackgroundCount = 0;
                    BackgroundX[BackgroundCount] = 115 * 29 * 100 - 1100;
                    BackgroundY[BackgroundCount] = 6 * 29 * 100;
                    BackgroundType[BackgroundCount] = EDecorationType::TEXT_THANKS_FOR_PLAYING;
                    BackgroundCount++;
                    if (BackgroundCount >= BACKGROUND_MAX)
                        BackgroundCount = 0;
                }
                else
                {
                    BackgroundX[BackgroundCount] = 157 * 29 * 100 - 1100;
                    BackgroundY[BackgroundCount] = 4 * 29 * 100;
                    BackgroundType[BackgroundCount] = EDecorationType::TEXT_GAME_CLEAR;
                    BackgroundCount++;
                    if (BackgroundCount >= BACKGROUND_MAX)
                        BackgroundCount = 0;
                    BackgroundX[BackgroundCount] = 155 * 29 * 100 - 1100;
                    BackgroundY[BackgroundCount] = 6 * 29 * 100;
                    BackgroundType[BackgroundCount] = EDecorationType::TEXT_THANKS_FOR_PLAYING;
                    BackgroundCount++;
                    if (BackgroundCount >= BACKGROUND_MAX)
                        BackgroundCount = 0;
                }
            }
            // スタッフロールへ (Go to the credits)

            if (PlayerAITimer == 440)
            {
                //+KZ: Save progress
                SyobonGlobalConfig.LevelsFinished.insert({currentGame, SyobonWorld, SyobonLevel});
                SaveConfig();

                if (PlayerState == 301)
                {
                    ending = 1;
                }
                else
                {
                    SyobonWorld++;
                    SyobonLevel = 1;
                    SyobonSection = 0;
                    InGameInitialized = 0;
                    CurrentPlayerCheckpoint = 0;
                    if(SyobonState != ESyobonGameState::TITLE)
                        SyobonState = ESyobonGameState::LIVES_SPLASH;
                    SyobonStateTimer = 0;
                }
            }

            /*
            if (mtm<=1){mc=0;md=0;}
            if (mtm>=2 && mtm<=42){md=600;PlayerLookingDirection=1;}
            if (mtm>43 && mtm<=108){mc=300;}
            if (mtm==110){mb=-80000000;mc=0;}
            if (mtm==250)end();
            */
        } // mtype==301

    } // mtype>=100

    // 移動 (Move)
    if (mkeytm >= 1)
    {
        mkeytm--;
    } // mc=0;}
    PlayerX += PlayerVelX;
    PlayerY += PlayerVelY;
    if (PlayerVelX < 0)
        PlayerWalkAnimTimer += (-PlayerVelX);
    if (PlayerVelX >= 0)
        PlayerWalkAnimTimer += PlayerVelX;

    if (PlayerState <= 9 || PlayerState == 200 || PlayerState == 300 || PlayerState == 301 || PlayerState == 302)
        PlayerVelY += 100;

    // 走る際の最大値 (Maximum value when running)
    if (PlayerState == 0)
    {
        xx[0] = 800;
        xx[1] = 1600;
        if (PlayerVelX > xx[0] && PlayerVelX < xx[0] + 200)
        {
            PlayerVelX = xx[0];
        }
        if (PlayerVelX > xx[0] + 200)
        {
            PlayerVelX -= 200;
        }
        if (PlayerVelX < -xx[0] && PlayerVelX > -xx[0] - 200)
        {
            PlayerVelX = -xx[0];
        }
        if (PlayerVelX < -xx[0] - 200)
        {
            PlayerVelX += 200;
        }
        if (PlayerVelY > xx[1])
        {
            PlayerVelY = xx[1];
        }
    }
    // プレイヤー (Player)
    // 地面の摩擦 (Ground friction)
    if (PlayerGrounded == 1 && actaon[0] != 3)
    {
        if ((PlayerState <= 9) || PlayerState == 300 || PlayerState == 301 || PlayerState == 302)
        {
            if (PlayerGroundType == EPlayerGroundType::NORMAL)
            {
                xx[2] = 30;
                xx[1] = 60;
                xx[3] = 30;
                if (PlayerVelX >= -xx[3] && PlayerVelX <= xx[3])
                {
                    PlayerVelX = 0;
                }
                if (PlayerVelX >= xx[2])
                {
                    PlayerVelX -= xx[1];
                }
                if (PlayerVelX <= -xx[2])
                {
                    PlayerVelX += xx[1];
                }
            }
            if (PlayerGroundType == EPlayerGroundType::SLIP)
            {
                xx[2] = 5;
                xx[1] = 10;
                xx[3] = 5;
                if (PlayerVelX >= -xx[3] && PlayerVelX <= xx[3])
                {
                    PlayerVelX = 0;
                }
                if (PlayerVelX >= xx[2])
                {
                    PlayerVelX -= xx[1];
                }
                if (PlayerVelX <= -xx[2])
                {
                    PlayerVelX += xx[1];
                }
            }
        }
    }
    // 地面判定初期化 (Initialize ground judgment)
    PlayerGrounded = 0;

    // 場外 (Outside the venue)
    if (PlayerState <= 9 && Health >= 1)
    {
        if (PlayerX < 100)
        {
            PlayerX = 100;
            PlayerVelX = 0;
        }
        if (PlayerX + PlayerSizeX > fxmax)
        {
            PlayerX = fxmax - PlayerSizeX;
            PlayerVelX = 0;
        }
    }
    // if (mb>=42000){mb=42000;PlayerGrounded=1;}
    if (PlayerY >= 38000 && Health >= 0 && StageColor == ELevelType::CASTLE)
    {
        Health = -2;
        PlayerMessageTimer = 30;
        PlayerMessageType = 55;
    }
    if (PlayerY >= 52000 && Health >= 0)
    {
        Health = -2;
    }

    HandlePlayerBlocks();
    HandlePlayerWalls();
}

void HandlePlayerInput()
{
    // プレイヤーの移動 (Player movement)
    xx[0] = 0;
    actaon[2] = 0;
    actaon[3] = 0;
    if (mkeytm <= 0)
    {
        if (CheckHitKey(KEY_INPUT_LEFT))
        {
            actaon[0] = -1;
            PlayerLookingDirection = LOOKING_LEFT;
            actaon[4] = -1;
        }
        if (CheckHitKey(KEY_INPUT_RIGHT))
        {
            actaon[0] = 1;
            PlayerLookingDirection = LOOKING_RIGHT;
            actaon[4] = 1;
        }
        if (CheckHitKey(KEY_INPUT_DOWN))
        {
            actaon[3] = 1;
        }
    }
    // if (CheckHitKey(KEY_INPUT_F1)==1){end();}
    if (CheckHitKey(KEY_INPUT_F1) == 1)
    {
        GoToTitleScreen();
    }
    // if (CheckHitKey(KEY_INPUT_Q)==1){mkeytm=0;}
    if (CheckHitKey(KEY_INPUT_O) == 1)
    {
        if (Health >= 1)
            Health = 0;
        if (SyobonSection >= 5)
        {
            SyobonSection = 0;
            stagepoint = 0;
        }
    }

    if (mkeytm <= 0)
    {
        if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_UP) == 1 || SyobonKZJoystickGetButton(joystick, JOYSTICK_JUMP))
        {
            if (actaon[1] == 10)
            {
                actaon[1] = 1;
                xx[0] = 1;
            }
            actaon[2] = 1;
        }
    }

    if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_UP) == 1 || SyobonKZJoystickGetButton(joystick, JOYSTICK_JUMP))
    {
        if (mjumptm == 8 && PlayerVelY >= -900)
        {
            PlayerVelY = -1300;
            // ダッシュ中
            xx[22] = 200;
            if (PlayerVelX >= xx[22] || PlayerVelX <= -xx[22])
            {
                PlayerVelY = -1400;
            }
            xx[22] = 600;
            if (PlayerVelX >= xx[22] || PlayerVelX <= -xx[22])
            {
                PlayerVelY = -1500;
            }
        }
        // && xx[0]==0 && md<=-10

        // if (mjumptm==7 && md>=-900){}
        if (xx[0] == 0)
            actaon[1] = 10;
    }
    // if (( key & PAD_INPUT_UP) && keytm<=0){actaon[0]=-1;PlayerLookingDirection=0;}

    // xx[0]=200;
    // if (actaon[0]==-1){ma-=xx[0];}
    // if (actaon[0]==1){ma+=xx[0];}
}

void HandlePlayerBlocks()
{
    // ブロック (Blocks)
    // 1-れんが、コイン、無し、土台、7-隠し (1 - Brick, Coin, None, Base, 7 - Hidden)

    xx[15] = 0;
    for (t = 0; t < BLOCK_MAX; t++)
    {
        xx[0] = 200;
        xx[1] = 3000;
        xx[2] = 1000;
        xx[3] = 3000; // xx[2]=1000
        xx[8] = BlockX[t] - fx;
        xx[9] = BlockY[t] - fy; // xx[15]=0;
        if (BlockX[t] - fx + xx[1] >= -10 - xx[3] && BlockX[t] - fx <= fxmax + 12000 + xx[3])
        {
            if (PlayerState != 200 && PlayerState != 1 && PlayerState != 2)
            {
                if ((int)BlockType[t] < 1000 && BlockType[t] != EBlockType::COIN && BlockType[t] != EBlockType::SWORD && BlockType[t] != EBlockType::BRIDGE_ROPE)
                { // && ttype[t]!=5){

                    // if (!(mztm>=1 && mztype==1 && actaon[3]==1)){
                    if (!(mztype == 1))
                    {
                        xx[16] = 0;
                        xx[17] = 0;

                        // 上 (Above)
                        if (BlockType[t] != EBlockType::ITEM_BLOCK_HIDDEN &&
                            (currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ? true : BlockType[t] != EBlockType::SYOBONKZ_HIDDEN_BLOCK) &&
                            BlockType[t] != EBlockType::ITEM_BLOCK_POISON_HIDDEN &&
                            !(BlockType[t] == EBlockType::ITEM_BLOCK_TRAP_HIDDEN))
                        {
                            if (PlayerX +
                                        PlayerSizeX >
                                    xx[8] +
                                        xx[0] * 2 +
                                        100 &&
                                PlayerX <
                                    xx[8] +
                                        xx[1] -
                                        xx[0] * 2 - 100 &&
                                PlayerY + PlayerSizeY > xx[9] && PlayerY + PlayerSizeY < xx[9] + xx[1] && PlayerVelY >= -100)
                            {
                                if (BlockType[t] != EBlockType::BRICK_BRITTLE && BlockType[t] != EBlockType::PSWITCH && BlockType[t] != EBlockType::NOTE_BLOCK && BlockType[t] != EBlockType::PUSH_BLOCK && BlockType[t] != EBlockType::TRAMPOLINE)
                                {
                                    PlayerY = xx[9] - PlayerSizeY + 100;
                                    PlayerVelY = 0;
                                    PlayerGrounded = 1;
                                    xx[16] = 1;
                                }
                                else if (BlockType[t] == EBlockType::BRICK_BRITTLE)
                                {
                                    PlaySound(Sounds[3]);
                                    CreateExtraGraphicLegacy(BlockX[t] + 1200, BlockY[t] + 1200,
                                          300,
                                          -1000,
                                          0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                                    CreateExtraGraphicLegacy(BlockX[t] + 1200, BlockY[t] + 1200,
                                          -300,
                                          -1000,
                                          0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                                    CreateExtraGraphicLegacy(BlockX[t] + 1200, BlockY[t] + 1200,
                                          240,
                                          -1400,
                                          0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                                    CreateExtraGraphicLegacy(BlockX[t] + 1200, BlockY[t] + 1200,
                                          -240,
                                          -1400,
                                          0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                                    BlockBreak(t);
                                }
                                // Pスイッチ (P switch)
                                else if (BlockType[t] == EBlockType::PSWITCH)
                                {
                                    PlayerVelY = 0;
                                    BlockX[t] = -8000000;
                                    PlaySound(Sounds[13]);
                                    for (tt = 0; tt < BLOCK_MAX; tt++)
                                    {
                                        if (BlockType[tt] != EBlockType::ITEM_BLOCK_HIDDEN)
                                        {
                                            BlockType[tt] = EBlockType::COIN;
                                        }
                                    }
                                    SyobonKZHaltMusic();
                                }
                                // 音符+ (Musical note+)
                                else if (BlockType[t] == EBlockType::NOTE_BLOCK)
                                {
                                    PlaySound(Sounds[14]);
                                    PlayerVelY = -1500;
                                    PlayerState = 2;
                                    PlayerAITimer = 0;
                                    if (BlockSubType[t] >= EBlockSubType::NOTE_BLOCK_WHITE_HIDDEN && PlayerState == 2)
                                    {
                                        PlayerState = 0;
                                        PlayerVelY = -1600;
                                        BlockSubType[t] = EBlockSubType::NOTE_BLOCK_WHITE_VISIBLE;
                                    }
                                    if (BlockSubType[t] == EBlockSubType::NOTE_BLOCK_RED_HIDDEN)
                                        BlockSubType[t] = EBlockSubType::NOTE_BLOCK_RED_VISIBLE;
                                }
                                // ジャンプ台 (Ski jump)
                                else if (BlockType[t] == EBlockType::TRAMPOLINE)
                                {
                                    // txtype[t]=0;
                                    PlayerVelY = -2400;
                                    PlayerState = 3;
                                    PlayerAITimer = 0;
                                }
                            }
                        }
                    } //!

                    // sstr=""+mjumptm;
                    // ブロック判定の入れ替え
                    if (!(mztm >= 1 && mztype == 1))
                    {
                        xx[21] = 0;
                        xx[22] = 1; // xx[12]=0;
                        if (
                            /*
                                +KZ: seems to be some weird logic to avoid checking for roof collision if we are grounded and just started jumping?
                                    Ill disable it for SA3 for now since this breaks some hidden block traps
                            */
                           (currentGame != ESyobonActionGame::SYOBON_ACTION_3) ?
                            (PlayerGrounded == 1 || mjumptm >= 10) : (PlayerGrounded == 1))
                        {
                            xx[21] = 3;
                            xx[22] = 0;
                        }
                        for (t3 = 0; t3 <= 1; t3++)
                        {

                            // 下 (Below)
                            if (t3 == xx[21] && PlayerState != 100 && BlockType[t] != EBlockType::NOTE_BLOCK)
                            { // && xx[12]==0){
                                if (PlayerX + PlayerSizeX > xx[8] + xx[0] * 2 + 800 && PlayerX < xx[8] + xx[1] - xx[0] * 2 - 800 && PlayerY > xx[9] - xx[0] * 2 && PlayerY < xx[9] + xx[1] - xx[0] * 2 && PlayerVelY <= 0)
                                {
                                    xx[16] = 1;
                                    xx[17] = 1;
                                    PlayerY = xx[9] + xx[1] + xx[0];
                                    if (PlayerVelY < 0)
                                    {
                                        PlayerVelY = -PlayerVelY * 2 / 3;
                                    } //}
                                    // 壊れる (Break)
                                    if (BlockType[t] == EBlockType::BRICK && PlayerGrounded == 0)
                                    {
                                        PlaySound(Sounds[3]);
                                        CreateExtraGraphicLegacy(BlockX[t] + 1200, BlockY[t] + 1200,
                                              300,
                                              -1000,
                                              0,
                                              160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                                        CreateExtraGraphicLegacy(BlockX[t] + 1200, BlockY[t] + 1200,
                                              -300,
                                              -1000,
                                              0,
                                              160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                                        CreateExtraGraphicLegacy(BlockX[t] + 1200, BlockY[t] + 1200,
                                              240,
                                              -1400,
                                              0,
                                              160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                                        CreateExtraGraphicLegacy(BlockX[t] + 1200, BlockY[t] + 1200,
                                              -240,
                                              -1400,
                                              0,
                                              160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                                        BlockBreak(t);
                                    }
                                    // コイン (Coin)
                                    if (BlockType[t] == EBlockType::ITEM_BLOCK_COIN && PlayerGrounded == 0)
                                    {
                                        PlaySound(Sounds[4]);
                                        CreateExtraGraphicLegacy(BlockX[t] +
                                                  10,
                                              BlockY
                                                  [t],
                                              0,
                                              -800,
                                              0,
                                              40, 3000, 3000, EExtraGraphicType::COIN, 16);
                                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                                    }
                                    // 隠し (Hidden)
                                    if (BlockType[t] == EBlockType::ITEM_BLOCK_HIDDEN)
                                    {
                                        PlaySound(Sounds[4]);
                                        CreateExtraGraphicLegacy(BlockX[t] +
                                                  10,
                                              BlockY
                                                  [t],
                                              0,
                                              -800,
                                              0,
                                              40, 3000, 3000, EExtraGraphicType::COIN, 16);
                                        PlayerY = xx[9] + xx[1] + xx[0];
                                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                                        if (PlayerVelY < 0)
                                        {
                                            PlayerVelY = -PlayerVelY * 2 / 3;
                                        }
                                    }
                                    // トゲ (Spikes)
                                    if (BlockType[t] == EBlockType::SPIKE)
                                    {
                                        PlayerMessageTimer = 30;
                                        PlayerMessageType = 3;
                                        Health--;
                                    }

                                    //+KZ
                                    if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 && BlockType[t] == EBlockType::SYOBONKZ_HIDDEN_BLOCK)
                                    {
                                        if(BlockSubType[t] == EBlockSubType::SYOBONKZ_HIDDEN_BLOCK_SPIKE_DOWN)
                                        {
                                            PlaySound(Sounds[14]);
                                            BlockType[t] = EBlockType::SPIKE;
                                            Health = 0;
                                        }
                                    }
                                }
                            }
                            // 左右 (Left and right)
                            if (t3 == xx[22] && xx[15] == 0)
                            {
                                if (BlockType[t] != EBlockType::ITEM_BLOCK_HIDDEN &&
                                    BlockType[t] != EBlockType::ITEM_BLOCK_POISON_HIDDEN &&
                                    BlockType[t] != EBlockType::NOTE_BLOCK &&
                                    (currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ? true : BlockType[t] != EBlockType::SYOBONKZ_HIDDEN_BLOCK)
                                )
                                {
                                    if (!(BlockType[t] == EBlockType::ITEM_BLOCK_TRAP_HIDDEN))
                                    { // && txtype[t]==1)){
                                        if (BlockX[t] >= -20000)
                                        {
                                            // if (ma+mnobia>xx[8] && ma<xx[8]+xx[2] && mb+mnobib>xx[9]+xx[1]/2-xx[0] &&){
                                            if (PlayerX + PlayerSizeX > xx[8] && PlayerX < xx[8] + xx[2] && PlayerY + PlayerSizeY > xx[9] + xx[1] / 2 - xx[0] && PlayerY < xx[9] + xx[2] && PlayerVelX >= 0)
                                            {
                                                PlayerX = xx[8] - PlayerSizeX;
                                                PlayerVelX = 0;
                                                xx[16] = 1;
                                                // if (ttype[t]!=4){ma=xx[8]-mnobia;mc=0;xx[16]=1;}
                                                // if (ttype[t]==4){ma=xx[8]-mnobia;mc=-mc*4/4;}
                                            }
                                            if (PlayerX + PlayerSizeX >
                                                    xx[8] + xx[2] &&
                                                PlayerX < xx[8] + xx[1] && PlayerY + PlayerSizeY > xx[9] + xx[1] / 2 - xx[0] && PlayerY < xx[9] + xx[2] && PlayerVelX <= 0)
                                            {
                                                PlayerX = xx[8] + xx[1];
                                                PlayerVelX = 0;
                                                xx[16] = 1; // end();
                                                            // if (ttype[t]!=4){ma=xx[8]+xx[1];mc=0;xx[16]=1;}
                                                            // if (ttype[t]==4){ma=xx[8]+xx[1];mc=-mc*4/4;}
                                            }
                                        }
                                    }
                                }

                                if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                                {
                                    if((BlockType[t] == EBlockType::SA3_GRAY_SPIKE_LEFT && xx[16] && PlayerX < xx[8]) ||
                                    (BlockType[t] == EBlockType::SA3_GRAY_SPIKE_RIGHT && xx[16] && PlayerX + PlayerSizeX > xx[8] + xx[1]))
                                    {
                                        PlayerMessageTimer = 30;
                                        PlayerMessageType = 3;
                                        Health--;
                                    }
                                }
                            }

                        } // t3
                    } //!

                } // && ttype[t]<50

                if (BlockType[t] == EBlockType::COIN)
                {
                    // if (xx[0]+xx[2]>=-xx[14] && xx[0]<=fxmax+xx[14] && xx[1]+xx[3]>=-10-9000 && xx[1]<=fymax+10000){
                    if (PlayerY >
                            xx[9] - xx[0] * 2 - 2000 &&
                        PlayerY <
                            xx[9] + xx[1] - xx[0] * 2 +
                                2000 &&
                        PlayerX + PlayerSizeX > xx[8] - 400 && PlayerX < xx[8] + xx[1])
                    {
                        BlockX[t] = -800000;
                        PlaySound(Sounds[4]);
                    }
                }
                // 剣とってクリア (Get the sword and clear the stage.)
                if (BlockType[t] == EBlockType::SWORD)
                {
                    if (PlayerY >
                            xx[9] - xx[0] * 2 - 2000 &&
                        PlayerY <
                            xx[9] + xx[1] - xx[0] * 2 +
                                2000 &&
                        PlayerX + PlayerSizeX > xx[8] - 400 && PlayerX < xx[8] + xx[1])
                    {
                        BlockX[t] = -800000; // PlaySound(Sounds[4]);
                        LiftMovementType[20] = 1;
                        LiftON[20] = 1;
                        SyobonKZHaltMusic();
                        PlayerState = 301;
                        PlayerAITimer = 0;
                        PlaySound(Sounds[16]);
                    }
                }
                // 特殊的 (special)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_DODGE)
                { // xx[9]+xx[1]+3000<mb && // && mb>xx[9]-xx[0]*2
                    if (PlayerY >
                            xx[9] - xx[0] * 2 - 2000 &&
                        PlayerY <
                            xx[9] + xx[1] - xx[0] * 2 +
                                2000 &&
                        PlayerX + PlayerSizeX > xx[8] - 400 && PlayerX < xx[8] + xx[1] && PlayerVelY <= 0)
                    {
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_DODGE_VERTICAL)
                            BlockY[t] = PlayerY + fy - 1200 - xx[1];
                    }

                    if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_DODGE_HORIZONTAL)
                    {
                        if (xx[17] == 1)
                        {
                            if (PlayerX +
                                        PlayerSizeX >
                                    xx[8] - 400 &&
                                PlayerX < xx[8] + xx[1] / 2 - 1500)
                            {
                                BlockX[t] += 3000;
                            }
                            else if (PlayerX + PlayerSizeX >= xx[8] + xx[1] / 2 - 1500 && PlayerX < xx[8] + xx[1])
                            {
                                BlockX[t] -= 3000;
                            }
                        }
                    }

                    if (xx[17] == 1 && BlockSubType[t] == EBlockSubType::ITEM_BLOCK_DODGE_VERTICAL)
                    {
                        PlaySound(Sounds[4]);
                        CreateExtraGraphicLegacy(BlockX[t] + 10, BlockY[t],
                              0, -800, 0, 40, 3000, 3000, EExtraGraphicType::COIN, 16);
                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                    }
                } // 100

                // 敵出現 (Enemy Appearance)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_ENEMY)
                { // xx[9]+xx[1]+3000<mb && // && mb>xx[9]-xx[0]*2
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_ENEMY_BALL_NORMAL)
                            CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::BALL, EEnemySubType::BALL_NORMAL);
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_ENEMY_BALL_SPIKY_NORMAL)
                            CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::BALL_SPIKY, EEnemySubType::BALL_SPIKY_NORMAL);
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_ENEMY_BURNING_FLOWER || BlockSubType[t] == EBlockSubType::ITEM_BLOCK_ENEMY_BURNING_FLOWER_10)
                            CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::BURNING_FLOWER, EEnemySubType::NONE);
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_ENEMY_DEFRAG_NORMAL)
                        {
                            EnemyBlockAppearTimer[EnemyCount] = 20;
                            CreateEnemyLegacy(BlockX[t] -
                                             400,
                                         BlockY[t] - 1600, 0, 0, 0, EEnemyType::DEFRAG, EEnemySubType::DEFRAG_NORMAL);
                        }
                        if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                        {
                            if(BlockSubType[t] == EBlockSubType::ITEM_BLOCK_ENEMY_SAJAM_BALL_NORMAL_BELOW)
                            {
                                int ind = CreateEnemy(GAME_X_POS_TO_DOUBLE(BlockX[t]), GAME_Y_POS_TO_DOUBLE(BlockY[t]) + 1, 0, 0,
                                    EEnemyType::BALL, EEnemySubType::BALL_NORMAL, ELookingDirection::LOOKING_RIGHT, 8);

                                if(ind >= 0)
                                {
                                    EnemyBlockAppearTimer[ind] = 0;
                                }
                            }
                        }
                    }
                } // 101

                // おいしいきのこ出現 (Delicious mushrooms have appeared.)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_MUSHROOM)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_MUSHROOM_DELICIOUS)
                            CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::MUSHROOM, EEnemySubType::MUSHROOM_DELICIOUS);
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_MUSHROOM_GROW)
                            CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::MUSHROOM, EEnemySubType::MUSHROOM_GROW);
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_MUSHROOM_POISONOUS_FASTER)
                            CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::MUSHROOM_POISONOUS, EEnemySubType::MUSHROOM_POISONOUS_FASTER);

                        if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                        {
                            if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_MUSHROOM_SA3_TRAP)
                            {
                                CreateExtraGraphic(GAME_X_POS_TO_DOUBLE(BlockX[t]), GAME_Y_POS_TO_DOUBLE(BlockY[t]), 0, -0.5, 0, 0, 1, 1, EExtraGraphicType::SA3_MUSHROOM, 50);
                                ObjectCreate(22.5, 0, 4, 13, EObjectType::SA3_TRIGGER_BIG_MUSHROOM_FALL, EObjectSubType::NONE);
                            }
                        }
                    }
                } // 102

                // まずいきのこ出現 (First, mushrooms appear.)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_MUSHROOM_2)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::MUSHROOM, EEnemySubType::MUSHROOM_NOT_POISONOUS);
                    }
                } // 103

                // 悪スター出し (Bad Star)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_STAR)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::BAD_STAR, EEnemySubType::NONE);
                    }
                } // 104

                //From SA: All Stars
                //this code is hard to understand
                if (BlockType[t] == EBlockType::KAIZO_SYOBON_ITEM_BLOCK_105 && xx[17] == 1)
                {
                    PlaySound(Sounds[8]);
                    BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                    //+KZ:?????
                    //oh, ok C# will give 0 to every other value
                    //.... which means this enemy is useless?? because it will spawn at 0,0
                    /*CEnemy ec6 = new CEnemy
                    {
                        brocktm = 16
                    };
                    Enemies.Add(ec6);*/
                }

                // 毒きのこ量産 (Mass production of poisonous mushrooms)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_POISON_HIDDEN)
                {
                    if (xx[17] == 1)
                    {
                        BlockType[t] = EBlockType::ITEM_BLOCK_POISON_OPEN;
                        BlockAITimer[t] = 999;
                    }
                } // 110
                if (BlockType[t] == EBlockType::ITEM_BLOCK_POISON_OPEN && BlockX[t] - fx >= 0)
                {
                    BlockAITimer[t]++;
                    if (BlockAITimer[t] >= 16)
                    {
                        BlockAITimer[t] = 0;
                        PlaySound(Sounds[8]);
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::MUSHROOM_POISONOUS, EEnemySubType::MUSHROOM_POISONOUS_FASTER);
                    }
                }
                // コイン量産 (Coin mass production)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_COINS)
                {
                    if (xx[17] == 1)
                    {
                        BlockType[t] = EBlockType::ITEM_BLOCK_COINS_OPEN;
                        BlockAITimer[t] = 999;
                        BlockItemCount[t] = 0;
                    }
                } // 110
                if (BlockType[t] == EBlockType::ITEM_BLOCK_COINS_OPEN && BlockX[t] - fx >= 0)
                {
                    if (BlockItemCount[t] <= 19)
                        BlockAITimer[t]++;
                    if (BlockAITimer[t] >= 3)
                    {
                        BlockAITimer[t] = 0;
                        BlockItemCount[t]++;
                        PlaySound(Sounds[4]);
                        CreateExtraGraphicLegacy(BlockX[t] + 10, BlockY[t],
                              0, -800, 0, 40, 3000, 3000, EExtraGraphicType::COIN, 16);
                        // ttype[t]=3;
                    }
                }
                // 隠し毒きのこ (Hidden poisonous mushroom)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_TRAP_HIDDEN)
                {
                    if (xx[17] == 1)
                    {
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_NORMAL)
                        {
                            PlaySound(Sounds[8]);
                            BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                            EnemyBlockAppearTimer[EnemyCount] = 16;
                            CreateEnemyLegacy(BlockX[t], BlockY[t], 0, 0, 0, EEnemyType::MUSHROOM_POISONOUS, EEnemySubType::MUSHROOM_POISONOUS_FASTER);
                        }
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_BRITTLE)
                        {
                            PlaySound(Sounds[4]);
                            CreateExtraGraphicLegacy(BlockX[t] +
                                      10,
                                  BlockY[t],
                                  0, -800, 0, 40, 3000, 3000, EExtraGraphicType::COIN, 16);
                            BlockType[t] = EBlockType::BRICK_BRITTLE;
                            BlockSubType[t] = EBlockSubType::BRICK_BRITTLE_ITEM_BLOCK_OPEN;
                        }
                        if (BlockSubType[t] == EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_FIREBAR_SWITCH)
                        {
                            if (stageonoff == 1)
                            {
                                BlockType[t] = EBlockType::ON_BLOCK;
                                stageonoff = 0;
                                PlaySound(Sounds[13]);
                                BlockSubType[t] = EBlockSubType::ON_BLOCK_UNLOCKED;
                                for (t = 0; t < ENEMY_MAX; t++)
                                {
                                    if (EnemyType[t] == EEnemyType::FIREBAR_CLOCKWISE || EnemyType[t] == EEnemyType::FIREBAR_COUNTERCLOCKWISE)
                                    {
                                        if ((int)EnemySubType[t] == 105)
                                        {
                                            EnemySubType[t] = (EEnemySubType)110;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                PlaySound(Sounds[4]);
                                CreateExtraGraphicLegacy(BlockX[t] +
                                          10,
                                      BlockY
                                          [t],
                                      0,
                                      -800, 0, 40, 3000, 3000, EExtraGraphicType::COIN, 16);
                                BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                            }
                        }
                        if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                        {
                            if(BlockSubType[t] == EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_SA3_1UP)
                            {
                                PlaySound(Sounds[8]);
                                BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                                int ind = CreateEnemy(GAME_X_POS_TO_DOUBLE(BlockX[t]), GAME_Y_POS_TO_DOUBLE(BlockY[t]), 0, 0, EEnemyType::MUSHROOM, EEnemySubType::MUSHROOM_SA3_1UP);
                                if(ind >= 0)
                                    EnemyBlockAppearTimer[ind] = 16;
                            }
                        }
                    }
                } // 114

                // もろいブロック (Fragile block)
                if (BlockType[t] == EBlockType::BRICK_BRITTLE)
                {

                } // 115

                // Pスイッチ (P switch)
                if (BlockType[t] == EBlockType::ITEM_BLOCK_PSWITCH)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        // PlaySound(Sounds[13]);
                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN; // abrocktm[aco]=18;CreateEntity(ta[t],tb[t],0,0,0,104,1);
                        BlockCreateLegacy(BlockX[t] / 100, (BlockY[t] / 100) - 29, EBlockType::PSWITCH);
                    }
                } // 116

                // ファイアバー強化 (Fire Bar Enhancement)
                if (BlockType[t] == EBlockType::FIREBAR_GROW)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[13]);
                        for (t = 0; t < ENEMY_MAX; t++)
                        {
                            if (EnemyType[t] == EEnemyType::FIREBAR_CLOCKWISE || EnemyType[t] == EEnemyType::FIREBAR_COUNTERCLOCKWISE)
                            {
                                if ((int)EnemySubType[t] == 101)
                                {
                                    EnemySubType[t] = (EEnemySubType)120;
                                }
                            }
                        }
                        BlockType[t] = EBlockType::ITEM_BLOCK_OPEN;
                    }
                }
                // ONスイッチ (ON switch)
                if (BlockType[t] == EBlockType::ON_BLOCK)
                {
                    if (xx[17] == 1)
                    {
                        if (BlockSubType[t] != EBlockSubType::ON_BLOCK_LOCKED)
                        {
                            stageonoff = 0;
                            PlaySound(Sounds[13]);
                        }
                    }
                }
                else if (BlockType[t] == EBlockType::OFF_BLOCK)
                {
                    if (xx[17] == 1 && BlockSubType[t] != EBlockSubType::OFF_BLOCK_LOCKED)
                    {
                        stageonoff = 1;
                        PlaySound(Sounds[13]);
                        if (BlockSubType[t] == EBlockSubType::OFF_BLOCK_FIREBARS)
                        {
                            for (t = 0; t < ENEMY_MAX; t++)
                            {
                                if (EnemyType[t] == EEnemyType::FIREBAR_CLOCKWISE || EnemyType[t] == EEnemyType::FIREBAR_COUNTERCLOCKWISE)
                                {
                                    if ((int)EnemySubType[t] == 105)
                                    {
                                        EnemySubType[t] = (EEnemySubType)110;
                                    }
                                }
                            }
                            EnemyAppearSubType[3] = (EEnemySubType)105;
                        }
                    }
                }
                // ヒント (Hint)
                if (BlockType[t] == EBlockType::MESSAGE_BLOCK)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[15]);
                        if (BlockSubType[t] <= EBlockSubType::MESSAGE_BLOCK_MAX)
                        {
                            TextBoxState = 1;
                            TextBoxTimer = 15;
                            TextBoxSizeY = 300 + ((int)BlockSubType[t] - 1);
                            TextBoxMessageID = (int)BlockSubType[t];
                        }
                        if (BlockSubType[t] == EBlockSubType::MESSAGE_BLOCK_1_3_0_4_WAIT_END)
                        {
                            TextBoxState = 1;
                            TextBoxTimer = 15;
                            TextBoxSizeY = 400;
                            TextBoxMessageID = 100;
                            BlockSubType[t] = EBlockSubType::MESSAGE_BLOCK_1_3_0_4_SHOW_MESSAGE;
                        }
                    }
                } // 300

                if (BlockType[t] == EBlockType::MESSAGE_BLOCK_BREAKABLE)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[3]);
                        CreateExtraGraphicLegacy(BlockX[t] + 1200,
                              BlockY[t] + 1200, 300,
                              -1000, 0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                        CreateExtraGraphicLegacy(BlockX[t] + 1200,
                              BlockY[t] + 1200,
                              -300, -1000, 0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                        CreateExtraGraphicLegacy(BlockX[t] + 1200,
                              BlockY[t] + 1200, 240,
                              -1400, 0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                        CreateExtraGraphicLegacy(BlockX[t] + 1200,
                              BlockY[t] + 1200,
                              -240, -1400, 0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                        BlockBreak(t);
                    }
                } // 300
            }
            else if (PlayerState == 1)
            {
                if (PlayerX + PlayerSizeX > xx[8] && PlayerX < xx[8] + xx[1] && PlayerY + PlayerSizeY > xx[9] && PlayerY < xx[9] + xx[1])
                {

                    PlaySound(Sounds[3]);
                    CreateExtraGraphicLegacy(BlockX[t] + 1200,
                          BlockY[t] + 1200, 300, -1000,
                          0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                    CreateExtraGraphicLegacy(BlockX[t] + 1200,
                          BlockY[t] + 1200, -300, -1000,
                          0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                    CreateExtraGraphicLegacy(BlockX[t] + 1200,
                          BlockY[t] + 1200, 240, -1400,
                          0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                    CreateExtraGraphicLegacy(BlockX[t] + 1200,
                          BlockY[t] + 1200, -240, -1400,
                          0, 160, 1000, 1000, EExtraGraphicType::BLOCK_FRAGMENT, 120);
                    BlockBreak(t);
                }
            }
            // ONOFF
            if (BlockType[t] == EBlockType::ON_BLOCK && stageonoff == 0)
            {
                BlockType[t] = EBlockType::OFF_BLOCK;
            }
            if (BlockType[t] == EBlockType::OFF_BLOCK && stageonoff == 1)
            {
                BlockType[t] = EBlockType::ON_BLOCK;
            }
            // ヒント (Hint)
            if (BlockType[t] == EBlockType::MESSAGE_BLOCK)
            {
                if (BlockSubType[t] >= EBlockSubType::MESSAGE_BLOCK_1_3_0_4_WAIT_START && BlockX[t] >= -6000)
                { // && ta[t]>=-6000){
                    if (BlockSubType[t] < EBlockSubType::MESSAGE_BLOCK_1_3_0_4_WAIT_END
                        /* +KZ: it was <= EBlockSubType::MESSAGE_BLOCK_539 */)
                    {
                        BlockSubType[t] = (EBlockSubType)((int)BlockSubType[t] + 1);
                    }
                    if (BlockSubType[t] >= EBlockSubType::MESSAGE_BLOCK_1_3_0_4_WAIT_END)
                    {
                        BlockX[t] -= 500;
                    }
                }
            } // 300
        }
    } // ブロック
}

void HandlePlayerWalls()
{
    // 壁 (Wall)
    for (t = 0; t < OBJECT_MAX; t++)
    {
        if (ObjectX[t] - fx + ObjectSizeX[t] >= -12000 && ObjectX[t] - fx <= fxmax)
        {
            xx[0] = 200;
            xx[1] = 2400;
            xx[2] = 1000;
            xx[7] = 0;

            xx[8] = ObjectX[t] - fx;
            xx[9] = ObjectY[t] - fy;
            if ((
                currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ?
                (
                    //+KZ: allow more objects in other games
                    ObjectType[t] < EObjectType::TRIGGERS_START ||
                    ObjectType[t] == EObjectType::CASTLE_BRICKS ||
                    (ObjectType[t] > EObjectType::LAST_LEGACY_OBJECT &&
                        !(ObjectType[t] >= EObjectType::SA3_TRIGGER_START &&
                            ObjectType[t] <= EObjectType::SA3_TRIGGER_END) &&
                        ObjectType[t] != EObjectType::SA3_FAKE_PIPE_BODY
                    )
                )
                :
                (ObjectType[t] < EObjectType::TRIGGERS_START /* +KZ: it was <= 99 */ ||
                ObjectType[t] == EObjectType::CASTLE_BRICKS)
             ) && PlayerState < 10)
            {

                // おちるブロック (Falling blocks)
                if (ObjectType[t] == EObjectType::FALLING_BLOCKS)
                {
                    if (PlayerX + PlayerSizeX >
                            xx[8] + xx[0] + 3000 &&
                        PlayerX < xx[8] + ObjectSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] + 3000 && ObjectAI[t] == 0)
                    {
                        if (ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_OVERWORLD_BRICK)
                        {
                            ObjectAI[t] = 1;
                            ObjectVelY[t] = 0;
                        }
                    }
                    if (PlayerX + PlayerSizeX >
                            xx[8] + xx[0] + 1000 &&
                        PlayerX < xx[8] + ObjectSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] + 3000 && ObjectAI[t] == 0)
                    {
                        if ((ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_X_ONLY) && ObjectAI[t] == 0)
                        {
                            ObjectAI[t] = 1;
                            ObjectVelY[t] = 0;
                        }
                    }

                    if ((ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK) && ObjectY[27] >= 25000 && ObjectX[27] > PlayerX + PlayerSizeX && t != 27 && ObjectAI[t] == 0)
                    {
                        ObjectAI[t] = 1;
                        ObjectVelY[t] = 0;
                    }
                    if (ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK_LEVEL_1_2 && ObjectY[28] >= 48000 /* +KZ: this is SYOBONKZ_SCREEN_SIZE_X * 100 */ && t != 28 && ObjectAI[t] == 0 && Health >= 1)
                    {
                        ObjectAI[t] = 1;
                        ObjectVelY[t] = 0;
                    }
                    if ((ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP && PlayerY >= 30000 || ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_4 && PlayerY >= 25000) && ObjectAI[t] == 0 && Health >= 1 && PlayerX + PlayerSizeX > xx[8] + xx[0] + 3000 - 300 && PlayerX < xx[8] + ObjectSizeX[t] - xx[0])
                    {
                        ObjectAI[t] = 1;
                        ObjectVelY[t] = 0;
                        if (ObjectSubType[t] == EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_4)
                            ObjectVelY[t] = 100;
                    }

                    if (ObjectAI[t] == 1 && ObjectY[t] <= fymax + 18000)
                    {
                        ObjectVelY[t] += 120;
                        if (ObjectVelY[t] >= 1600)
                        {
                            ObjectVelY[t] = 1600;
                        }
                        ObjectY[t] += ObjectVelY[t];
                        if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + ObjectSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY < xx[9] + ObjectSizeY[t] + xx[0])
                        {
                            Health--;
                            xx[7] = 1;
                        }
                    }
                }
                // おちるブロック2 (Falling Block 2)
                if (ObjectType[t] == EObjectType::FALLING_FLOOR ||
                    (currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 && ObjectType[t] == EObjectType::SA3_FALLING_FLOOR && ((prev_player_vel_y > 0 && prev_player_grounded == 0) || ObjectAI[t] != 0))
                )
                {
                    if (ObjectAI[t] == 0 && PlayerX + PlayerSizeX > xx[8] + xx[0] + 2000 && PlayerX < xx[8] + ObjectSizeX[t] - xx[0] - 2500 && PlayerY + PlayerSizeY > xx[9] - 3000)
                    {
                        ObjectAI[t] = 1;
                        ObjectVelY[t] = 0;
                    }
                    if (ObjectAI[t] == 1)
                    {
                        ObjectVelY[t] += 120;
                        if (ObjectVelY[t] >= 1600)
                        {
                            ObjectVelY[t] = 1600;
                        }
                        ObjectY[t] += ObjectVelY[t];
                    }
                }
                // 通常地面 (Normal Ground)
                if (xx[7] == 0)
                {
                    if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + ObjectSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY + PlayerSizeY < xx[9] + xx[1] && PlayerVelY >= -100)
                    {
                        PlayerY = ObjectY[t] - fy - PlayerSizeY + 100;
                        PlayerVelY = 0;
                        PlayerGrounded = 1;
                    }
                    if (PlayerX + PlayerSizeX > xx[8] - xx[0] && PlayerX < xx[8] + xx[2] && PlayerY + PlayerSizeY > xx[9] + xx[1] * 3 / 4 && PlayerY < xx[9] + ObjectSizeY[t] - xx[2])
                    {
                        PlayerX = xx[8] - xx[0] - PlayerSizeX;
                        PlayerVelX = 0;
                    }
                    if (PlayerX + PlayerSizeX > xx[8] + ObjectSizeX[t] - xx[0] && PlayerX < xx[8] + ObjectSizeX[t] + xx[0] && PlayerY + PlayerSizeY > xx[9] + xx[1] * 3 / 4 && PlayerY < xx[9] + ObjectSizeY[t] - xx[2])
                    {
                        PlayerX = xx[8] + ObjectSizeX[t] + xx[0];
                        PlayerVelX = 0;
                    }
                    if (PlayerX + PlayerSizeX >
                            xx[8] + xx[0] * 2 &&
                        PlayerX <
                            xx[8] + ObjectSizeX[t] - xx[0] * 2 &&
                        PlayerY > xx[9] + ObjectSizeY[t] - xx[1] && PlayerY < xx[9] + ObjectSizeY[t] + xx[0])
                    {
                        PlayerY = xx[9] + ObjectSizeY[t] + xx[0];
                        if (PlayerVelY < 0)
                        {
                            PlayerVelY = -PlayerVelY * 2 / 3;
                        }
                    }
                } // xx[7]

                // 入る土管 (Entering a pipe)
                if (ObjectType[t] == EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD)
                {
                    if (PlayerX + PlayerSizeX > xx[8] + 2800 && PlayerX < xx[8] + ObjectSizeX[t] - 3000 && PlayerY + PlayerSizeY > xx[9] - 1000 && PlayerY + PlayerSizeY < xx[9] + xx[1] + 3000 && PlayerGrounded == 1 && actaon[3] == 1 && PlayerState == 0)
                    {
                        // 飛び出し (Jumping out) //+KZ: ??
                        if (ObjectSubType[t] == EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_ROCKET)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 0;
                        }
                        // 普通 (Normal)
                        if (ObjectSubType[t] == EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 1;
                        }
                        // 普通 (Normal)
                        if (ObjectSubType[t] == EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_LAVA)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 2;
                        }
                        if (ObjectSubType[t] == EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_WARP_ZONE)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 5;
                        }
                        // ループ (Loop) //+KZ: ????
                        if (ObjectSubType[t] == EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_PLUS_10_SECTION)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 6;
                        }
                    }
                } // 50

                // 入る土管(左から) (Pipes to enter (from left))
                if (ObjectType[t] == EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD)
                {
                    if (PlayerX + PlayerSizeX > xx[8] - 300 && PlayerX < xx[8] + ObjectSizeX[t] - 1000 && PlayerY > xx[9] + 1000 && PlayerY + PlayerSizeY < xx[9] + xx[1] + 4000 && PlayerGrounded == 1 && actaon[4] == 1 && PlayerState == 0)
                    { // end();
                        // 飛び出し (Jumping out)
                        if (ObjectSubType[t] == EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_KILL_PLAYER_CANNON)
                        {
                            PlayerState = 500;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]); // mxtype=1;
                            PlayerState = 100;
                            PlayerSubState = 10;
                        }

                        if (ObjectSubType[t] == EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_GO_NEXT_SECTION)
                        {
                            PlayerSubState = 3;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]); // mxtype=1;
                            PlayerState = 100;
                        }
                        // ループ (Loop) //+KZ: ????????????
                        if (ObjectSubType[t] == EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_KILL_PLAYER_CANNON_UNUSED)
                        {
                            PlayerState = 3;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 6;
                        }
                    }
                } // 40

            } // stype
            else
            {
                if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + ObjectSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY < xx[9] + ObjectSizeY[t] + xx[0])
                {
                    if (ObjectType[t] == EObjectType::TRIGGER_SEAL_UP)
                    {
                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_SEAL_UP_NORMAL || ObjectSubType[t] == EObjectSubType::TRIGGER_SEAL_UP_LEVEL_1_2 && BlockType[1] != EBlockType::ITEM_BLOCK_OPEN)
                        {
                            CreateEnemyLegacy(ObjectX[t] + 1000, 32000, 0, 0, 0, EEnemyType::SEAL, EEnemySubType::SEAL_UP);
                            ObjectX[t] = -800000000;
                            PlaySound(Sounds[10]);
                        }
                    }
                    if (ObjectType[t] == EObjectType::TRIGGER_SEAL_DOWN)
                    {
                        CreateEnemyLegacy(ObjectX[t] + 6000, -4000, 0, 0, 0, EEnemyType::SEAL, EEnemySubType::SEAL_DOWN);
                        ObjectX[t] = -800000000;
                        PlaySound(Sounds[10]);
                    }
                    if (ObjectType[t] == EObjectType::TRIGGER_GENERIC_1)
                    {
                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_4_BALLS)
                        {
                            for (t3 = 0; t3 <= 3; t3++)
                            {
                                CreateEnemyLegacy(ObjectX[t] +
                                                 t3 * 3000,
                                             -3000, 0, 0, 0, EEnemyType::BALL, EEnemySubType::BALL_NORMAL);
                            }
                        }
                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_BALL_SPIKY_JUMP && PlayerY >= 16000)
                        {
                            CreateEnemyLegacy(ObjectX[t] +
                                             1500,
                                         44000, 0, -2000, 0, EEnemyType::BALL_SPIKY, EEnemySubType::BALL_SPIKY_NORMAL);
                        }
                        else if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_FIRST_KUMA)
                        {
                            CreateEnemyLegacy(ObjectX[t] +
                                             4500,
                                         30000, 0, -1600, 0, EEnemyType::KUMA, EEnemySubType::NONE);
                            PlaySound(Sounds[10]);
                            ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_ENABLE_SECOND_KUMA;
                            ObjectX[t] -= 12000;
                        }
                        else if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_ENABLE_SECOND_KUMA)
                        {
                            ObjectX[t] += 12000;
                            ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SECOND_KUMA;
                        }
                        else if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SECOND_KUMA)
                        {
                            CreateEnemyLegacy(ObjectX[t] +
                                             4500,
                                         30000, 0, -1600, 0, EEnemyType::KUMA, EEnemySubType::NONE);
                            PlaySound(Sounds[10]);
                            //ObjectSubType[t] = 5; //+KZ: xD? it is set to 0 just after

                            //+KZ: setting this value here will go inside a if thats below everything,
                            //which will teleport this trigger object out of bounds
                            //
                            //why chiku didnt just did that here like in other subtypes?
                            ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_4_BALLS;
                        }

                        else if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_WARP_ZONE)
                        {
                            WarpZoneMessageState = 1;
                        }
                        else if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_THIRD_KUMA)
                        {
                            CreateEnemyLegacy(ObjectX[t] -
                                             5000 -
                                             3000 * 1,
                                         26000, 0, -1600, 0, EEnemyType::KUMA, EEnemySubType::NONE);
                            PlaySound(Sounds[10]);
                        }
                        else if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_THREE_SEALS)
                        {
                            for (t3 = 0; t3 <= 2; t3++)
                            {
                                CreateEnemyLegacy(ObjectX[t] +
                                                 t3 *
                                                     3000 +
                                                 3000,
                                             48000 /* +KZ: this is SYOBONKZ_SCREEN_SIZE_X * 100 */, 0, -6000, 0, EEnemyType::SEAL, EEnemySubType::SEAL_UP);
                            }
                        }
                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SEAL_DOWN)
                        {
                            ObjectX[t] -= 5 * 30 * 100;
                            ObjectType[t] = EObjectType::TRIGGER_SEAL_DOWN;
                        }

                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SURPRISE_MAGMA)
                        {
                            for (t3 = 1; t3 <= 3; t3++)
                            {
                                CreateEnemyLegacy(ObjectX[t] +
                                                 t3 *
                                                     3000 -
                                                 1000,
                                             40000, 0, -2600, 0, EEnemyType::MAGMA, EEnemySubType::NONE);
                            }
                        }
                        // スクロール消し (Scrolling off)
                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SCROLLING_OFF)
                        {
                            scrollx = 0;
                        }
                        // クリア (Clear)
                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_CLEAR_GAME)
                        {
                            ObjectX[t] = -80000000;
                            PlayerVelY = 0;
                            SyobonKZHaltMusic();
                            PlayerState = 302;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[16]);
                        }

                        if (ObjectSubType[t] != EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_ENABLE_SECOND_KUMA &&
                            ObjectSubType[t] != EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SECOND_KUMA
                            && ObjectSubType[t] != EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SEAL_DOWN)
                        {
                            ObjectX[t] = -800000000;
                        }
                    }

                    if (ObjectType[t] == EObjectType::TRIGGER_LASER)
                    {
                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_LASER_NORMAL)
                        {
                            EnemyMessageTimer[EnemyCount] = 10;
                            EnemyMessageType[EnemyCount] = 50;
                            CreateEnemyLegacy(ObjectX[t] +
                                             9000,
                                         ObjectY[t] + 2000, 0, 0, 0, EEnemyType::LASER, EEnemySubType::LASER_HORIZONTAL);
                            ObjectX[t] = -800000000;
                        }

                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_LASER_LEVEL_1_3 && (int)BlockType[6] <= 6)
                        {
                            EnemyMessageTimer[EnemyCount] = 10;
                            EnemyMessageType[EnemyCount] = 50;
                            CreateEnemyLegacy(ObjectX[t] -
                                             12000,
                                         ObjectY[t] + 2000, 0, 0, 0, EEnemyType::LASER, EEnemySubType::LASER_HORIZONTAL);
                            ObjectX[t] = -800000000;
                            BlockSubType[9] = EBlockSubType::MESSAGE_BLOCK_1_3_0_4_WAIT_START; // ttype[9]=1;
                        }
                    } // 103

                    if (ObjectType[t] == EObjectType::TRIGGER_MULTI_LASER)
                    {
                        if (ObjectSubType[t] == EObjectSubType::TRIGGER_MULTI_LASER_ACTIVE)
                        {
                            CreateEnemyLegacy(ObjectX[t] + 12000, ObjectY[t] + 2000 + 3000, 0, 0, 0, EEnemyType::LASER, EEnemySubType::LASER_HORIZONTAL);
                            CreateEnemyLegacy(ObjectX[t] + 12000, ObjectY[t] + 2000 + 3000, 0, 0, 0, EEnemyType::LASER, EEnemySubType::LASER_10_DEGREE_UP);
                            CreateEnemyLegacy(ObjectX[t] + 12000, ObjectY[t] + 2000 + 3000, 0, 0, 0, EEnemyType::LASER, EEnemySubType::LASER_10_DEGREE_DOWN);
                            CreateEnemyLegacy(ObjectX[t] + 12000, ObjectY[t] + 2000 + 3000, 0, 0, 0, EEnemyType::LASER, EEnemySubType::LASER_33_DEGREE_UP);
                            CreateEnemyLegacy(ObjectX[t] + 12000, ObjectY[t] + 2000 + 3000, 0, 0, 0, EEnemyType::LASER, EEnemySubType::LASER_33_DEGREE_DOWN);
                            ObjectX[t] = -800000000;
                        }
                    }

                    if (ObjectType[t] == EObjectType::TRIGGER_PLATFORM_SPLIT && PlayerGrounded == 0 && PlayerVelY >= 0)
                    {
                        BlockX[1] -= 1000;
                        BlockX[2] += 1000;
                        ObjectSubType[t] = (EObjectSubType)((int)ObjectSubType[t] + 1);
                        if (ObjectSubType[t] >= EObjectSubType::TRIGGER_PLATFORM_SPLIT_TIMER_END)
                            ObjectX[t] = -8000000;
                    }

                    if (ObjectType[t] == EObjectType::GOAL_POLE && PlayerState == 0 && PlayerY < xx[9] + ObjectSizeY[t] + xx[0] - 3000 && Health >= 1)
                    {
                        SyobonKZHaltMusic();
                        PlayerState = 300;
                        PlayerAITimer = 0;
                        PlayerX = ObjectX[t] - fx - 2000;
                        PlaySound(Sounds[11]);
                    }
                    // 中間ゲート (Intermediate gate)
                    if (ObjectType[t] == EObjectType::CHECKPOINT && PlayerState == 0 && Health >= 1)
                    {
                        CurrentPlayerCheckpoint += 1;
                        ObjectX[t] = -80000000;
                    }

                    //Syobon Action 3
                    if(currentGame != ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2)
                    {
                        if(ObjectType[t] == EObjectType::SA3_TRIGGER_FAST_SEAL_UP)
                        {
                            {
                                if(ObjectSubType[t] == EObjectSubType::SA3_TRIGGER_FAST_SEAL_UP_4_SEALS)
                                {
                                    CreateEnemy(GAME_X_POS_TO_DOUBLE(ObjectX[t]) - 0.25, GAME_X_POS_TO_DOUBLE(ObjectY[t] + ObjectSizeY[t]) + 1, 0, -1.25, EEnemyType::SEAL, EEnemySubType::SEAL_SYOBONKZ_VERTICAL);
                                    CreateEnemy(GAME_X_POS_TO_DOUBLE(ObjectX[t]) - 0.25, GAME_X_POS_TO_DOUBLE(ObjectY[t] + ObjectSizeY[t]) + 3.25, 0, -1.25, EEnemyType::SEAL, EEnemySubType::SEAL_SYOBONKZ_VERTICAL);
                                    CreateEnemy(GAME_X_POS_TO_DOUBLE(ObjectX[t]) + 0.75, GAME_X_POS_TO_DOUBLE(ObjectY[t] + ObjectSizeY[t]) + 1, 0, -1.25, EEnemyType::SEAL, EEnemySubType::SEAL_SYOBONKZ_VERTICAL);
                                    CreateEnemy(GAME_X_POS_TO_DOUBLE(ObjectX[t]) + 0.75, GAME_X_POS_TO_DOUBLE(ObjectY[t] + ObjectSizeY[t]) + 3.25, 0, -1.25, EEnemyType::SEAL, EEnemySubType::SEAL_SYOBONKZ_VERTICAL);
                                }
                                else
                                {
                                    CreateEnemy(GAME_X_POS_TO_DOUBLE(ObjectX[t] + ObjectSizeX[t] / 2) - 0.5, GAME_X_POS_TO_DOUBLE(ObjectY[t] + ObjectSizeY[t]) + 1, 0, -1, EEnemyType::SEAL, EEnemySubType::SEAL_SYOBONKZ_VERTICAL);
                                }
                                ObjectX[t] = -800000000;
                                PlaySound(Sounds[10]);
                            }
                        }
                        else if(ObjectType[t] == EObjectType::SA3_TRIGGER_BIG_MUSHROOM_FALL)
                        {
                            CreateEnemy(GAME_X_POS_TO_DOUBLE(ObjectX[t]), -4, 0, 1, EEnemyType::SA3_BIG_MUSHROOM_FALLING, EEnemySubType::NONE);
                            
                            ObjectX[t] = -9999999;
                        }
                        else if(ObjectType[t] == EObjectType::SA3_TRIGGER_SPIKES_LEVEL_1_1 &&
                            ObjectSubType[t] == EObjectSubType::SA3_TRIGGER_SPIKES_LEVEL_1_1_WAITING)
                        {
                            ObjectSubType[t] = EObjectSubType::SA3_TRIGGER_SPIKES_LEVEL_1_1_ACTIVE;
                        }
                        else if(ObjectType[t] == EObjectType::SA3_TRIGGER_BIG_STONE_BALL_LEVEL_1_1 && Health > 0)
                        {
                            CreateEnemy(126, 1, -0.2, 0, EEnemyType::SA3_BIG_STONE, EEnemySubType::NONE);
                            CreateEnemy(126, 7, -0.2, 0, EEnemyType::SA3_BIG_STONE, EEnemySubType::NONE);
                            
                            ObjectX[t] = DOUBLE_TO_GAME_X_POS(108);
                            ObjectType[t] = EObjectType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1;
                        }
                        else if(ObjectType[t] == EObjectType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1 &&
                            ObjectSubType[t] == EObjectSubType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_WAITING)
                        {
                            ObjectSubType[t] = EObjectSubType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_ACTIVE;
                        }
                    }
                }

                if (ObjectType[t] == EObjectType::TRIGGER_LAVA_SPAWNER)
                {
                    ObjectVelY[t]++;
                    if (ObjectVelY[t] >= ObjectAI[t])
                    {
                        ObjectVelY[t] = 0;
                        CreateEnemyLegacy(ObjectX[t], 30000,
                                     SyobonRand(600) - 300,
                                     -1600 - SyobonRand(900), 0, EEnemyType::LAVA_FROM_PIPE, EEnemySubType::NONE);
                    }
                }

                if(currentGame == ESyobonActionGame::SYOBON_ACTION_3)
                {
                    if(Health > 0 && ObjectType[t] == EObjectType::SA3_TRIGGER_SPIKES_LEVEL_1_1 &&
                        ObjectSubType[t] == EObjectSubType::SA3_TRIGGER_SPIKES_LEVEL_1_1_ACTIVE)
                    {
                        //ObjectAI should be the first trap wall block
                        //ObjectAI + 1 should be the second trap wall block
                        if(ObjectAI[t] >= 0 && ObjectAI[t] < BLOCK_MAX - 1)
                        {
                            if(BlockY[ObjectAI[t] + 1] > DOUBLE_TO_GAME_Y_POS(6))
                            {
                                ObjectVelY[t] = -1;
                                BlockY[ObjectAI[t] + 1] -= DOUBLE_TO_GAME_X_POS(0.75);
                                if(BlockY[ObjectAI[t] + 1] < DOUBLE_TO_GAME_Y_POS(6))
                                    BlockY[ObjectAI[t] + 1] = DOUBLE_TO_GAME_Y_POS(6);
                                
                                for(int block_id_offset = 3; block_id_offset <= 14; block_id_offset += 2)
                                {
                                    int id = ObjectAI[t] + block_id_offset;
                                    if(id >= BLOCK_MAX)
                                        id -= BLOCK_MAX;
                                    BlockY[id] = BlockY[ObjectAI[t] + 1] + DOUBLE_TO_GAME_X_POS(((block_id_offset - 3) / 2) + 1);
                                }
                            }
                            else
                            {
                                if(ObjectVelY[t] < 0 || ObjectVelY[t] >= BLOCK_MAX)
                                {
                                    for(int i = 6; i <= 12; i++)
                                    {
                                        if(i == 6)
                                        {
                                            ObjectVelY[t] = BlockCreate(56, i, EBlockType::SA3_GRAY_SPIKE_RIGHT);
                                        }
                                        else
                                        {
                                            BlockCreate(56, i, EBlockType::SA3_GRAY_SPIKE_RIGHT);
                                        }
                                        BlockCreate(63, i, EBlockType::SA3_GRAY_SPIKE_LEFT);
                                    }
                                }
                                else
                                {
                                    int scnd = ObjectVelY[t] + 1;
                                    if(scnd >= BLOCK_MAX)
                                        scnd -= BLOCK_MAX;

                                    if(BlockX[ObjectVelY[t]] >= BlockX[scnd])
                                    {
                                        ObjectSubType[t] = EObjectSubType::SA3_TRIGGER_SPIKES_LEVEL_1_1_FINISHED;
                                    }
                                    else
                                    {                                    
                                        for(int spike_offset = 0; spike_offset < 14; spike_offset++)
                                        {
                                            int id = ObjectVelY[t] + spike_offset;
                                            if(id >= BLOCK_MAX)
                                                id -= BLOCK_MAX;

                                            int id2 = ObjectAI[t] + spike_offset;
                                            if(id2 >= BLOCK_MAX)
                                                id2 -= BLOCK_MAX;

                                            if(spike_offset % 2)
                                            {
                                                BlockX[id] -= DOUBLE_TO_GAME_X_POS(0.02);
                                                BlockX[id2] -= DOUBLE_TO_GAME_X_POS(0.02);
                                            }
                                            else
                                            {
                                                BlockX[id] += DOUBLE_TO_GAME_X_POS(0.02);
                                                BlockX[id2] += DOUBLE_TO_GAME_X_POS(0.02);
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                    else if(ObjectType[t] == EObjectType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1 &&
                        ObjectSubType[t] == EObjectSubType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_ACTIVE)
                    {
                        if(ObjectVelY[t] >= 0 && ObjectVelY[t] <= BLOCK_MAX && 
                            ObjectAI[t] >= 0 && ObjectAI[t] < BLOCK_MAX - ObjectVelY[t])
                        {
                            for(int wall_offset = 0; wall_offset < ObjectVelY[t]; wall_offset++)
                            {
                                int id = ObjectAI[t] + wall_offset;
                                if(id >= BLOCK_MAX)
                                    id -= BLOCK_MAX;

                                BlockY[id] += DOUBLE_TO_GAME_X_POS(0.5);
                            }
                            if(BlockY[ObjectAI[t]] > DOUBLE_TO_GAME_X_POS(-0.6))
                            {
                                ObjectSubType[t] = EObjectSubType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_FINISHED;
                                for(int wall_offset = 0; wall_offset < ObjectVelY[t]; wall_offset++)
                                {
                                    int id = ObjectAI[t] + wall_offset;
                                    if(id >= BLOCK_MAX)
                                        id -= BLOCK_MAX;

                                    BlockY[id] = DOUBLE_TO_GAME_Y_POS(-0.5 + wall_offset);
                                }
                            }
                        }
                        else
                        {
                            ObjectSubType[t] = EObjectSubType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_FINISHED;
                        }
                    }
                }
            }
        }
    } // 壁 (Wall)
}

void HandlePlayerMessage()
{
    // プレイヤーのメッセージ (Player's message)
    setc0();
    if (PlayerMessageTimer >= 1)
    {
        PlayerMessageTimer--;
        xs[0] = "";

        if (PlayerMessageType == 1)
            xs[0] = "お、おいしい!!";
        if (PlayerMessageType == 2)
            xs[0] = "毒は無いが……";
        if (PlayerMessageType == 3)
            xs[0] = "刺さった!!";
        if (PlayerMessageType == 10)
            xs[0] = "食べるべきではなかった!!";
        if (PlayerMessageType == 11)
            xs[0] = "俺は燃える男だ!!";
        if (PlayerMessageType == 50)
            xs[0] = "体が……焼ける……";
        if (PlayerMessageType == 51)
            xs[0] = "たーまやー!!";
        if (PlayerMessageType == 52)
            xs[0] = "見事にオワタ";
        if (PlayerMessageType == 53)
            xs[0] = "足が、足がぁ!!";
        if (PlayerMessageType == 54)
            xs[0] = "流石は摂氏800度!!";
        if (PlayerMessageType == 55)
            xs[0] = "溶岩と合体したい……";

        /*setc0();
        str(xs[0], (PlayerX + PlayerSizeX + 300) / 100 - 1, PlayerY / 100 - 1);
        str(xs[0], (PlayerX + PlayerSizeX + 300) / 100 + 1, PlayerY / 100 + 1);
        setc1();
        str(xs[0], (PlayerX + PlayerSizeX + 300) / 100, PlayerY / 100);*/
        setc1();
        DrawGraphZ((PlayerX + PlayerSizeX + 300) / 100, PlayerY / 100, apPlayerMessages[xs[0].c_str()]);

    } // PlayerMessageTimer
}

void RenderPlayer()
{
    // プレイヤー描画 (Player rendering)
    setcolor(0, 0, 255);

    if (PlayerWalkAnimTimer >= 2000)
    {
        PlayerWalkAnimTimer -= 2000;
        if (PlayerWalkAnim == 0)
        {
            PlayerWalkAnim = 1;
        }
        else
        {
            PlayerWalkAnim = 0;
        }
    }
    if (PlayerLookingDirection == 0)
        mirror = 1;

    if (PlayerState != 200 && PlayerState != 1)
    {
        if (PlayerGrounded == 1)
        {
            // 読みこんだグラフィックを拡大描画 (Enlarged rendering of loaded graphics)
            if (PlayerWalkAnim == 0)
                drawimage(Sliced_GFX[0][0], PlayerX / 100, PlayerY / 100);
            if (PlayerWalkAnim == 1)
                drawimage(Sliced_GFX[1][0], PlayerX / 100, PlayerY / 100);
        }
        if (PlayerGrounded == 0)
        {
            drawimage(Sliced_GFX[2][0], PlayerX / 100, PlayerY / 100);
        }
    }
    // 巨大化 (Huge)
    else if (PlayerState == 1)
    {
        drawimage(Sliced_GFX[41][0], PlayerX / 100, PlayerY / 100);
    }

    else if (PlayerState == 200)
    {
        drawimage(Sliced_GFX[3][0], PlayerX / 100, PlayerY / 100);
    }
}
