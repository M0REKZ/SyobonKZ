#include <unordered_map>
#include "global_vars.h"
#include "main.h"
#include "player.h"
#include "entities.h"
#include "extra_graphics.h"

std::unordered_map<std::string, SDL_Surface *> apPlayerMessages;

void CreatePlayerMessageCache()
{
    Uint32 temp_color = GetColor(255, 255, 255);
    #define PLAYER_MESSAGE(text) apPlayerMessages[text] = StringToSurface(text, temp_color, 16, DX_FONTTYPE_EDGE)

    PLAYER_MESSAGE("お、おいしい!!");
    PLAYER_MESSAGE("毒は無いが……");
    PLAYER_MESSAGE("刺さった!!");
    PLAYER_MESSAGE("食べるべきではなかった!!");
    PLAYER_MESSAGE("俺は燃える男だ!!");
    PLAYER_MESSAGE("体が……焼ける……");
    PLAYER_MESSAGE("たーまやー!!");
    PLAYER_MESSAGE("見事にオワタ");
    PLAYER_MESSAGE("足が、足がぁ!!");
    PLAYER_MESSAGE("流石は摂氏800度!!");
    PLAYER_MESSAGE("溶岩と合体したい……");

    #undef PLAYER_MESSAGE
}

void HandlePlayer()
{
    HandlePlayerInput();

    // 加速による移動 (Movement due to acceleration)
    xx[0] = 40;
    xx[1] = 700;
    xx[8] = 500;
    xx[9] = 700;
    xx[12] = 1;
    xx[13] = 2;

    // すべり補正 (Slip correction)
    if (PlayerGroundType == EGroundType::SLIP)
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
        if (PlayerGroundType != EGroundType::SLIP)
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
        if (PlayerGroundType != EGroundType::SLIP)
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
        PlayerGroundType = EGroundType::NORMAL;

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

    if (mmutekitm >= -1)
        mmutekitm--;

    // HPがなくなったとき (When HP runs out)
    if (Health <= 0 && Health >= -9)
    {
        mkeytm = 12;
        Health = -20;
        PlayerState = 200;
        PlayerAITimer = 0;
        SyobonKZHaltChannel(-1);
        SyobonKZHaltMusic();
        PlaySound(Sounds[12]);
        StopSoundMem(Sounds[16]);
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
            zxon = 0;
            SyobonState = ESyobonState::LIVES_SPLASH;
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
            SyobonSection += 85;
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

        // 普通の土管
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
                    mzz = 100;
                }
                if (PlayerAITimer == 17)
                {
                    PlayerY = -80000000;
                }
                if (PlayerAITimer == 23)
                {
                    GroundX[t] -= 100;
                }
                if (PlayerAITimer >= 44 && PlayerAITimer <= 60)
                {
                    if (PlayerAITimer % 2 == 0)
                        GroundX[t] += 200;
                    if (PlayerAITimer % 2 == 1)
                        GroundX[t] -= 200;
                }
                if (PlayerAITimer >= 61 && PlayerAITimer <= 77)
                {
                    if (PlayerAITimer % 2 == 0)
                        GroundX[t] += 400;
                    if (PlayerAITimer % 2 == 1)
                        GroundX[t] -= 400;
                }
                if (PlayerAITimer >= 78 && PlayerAITimer <= 78 + 16)
                {
                    if (PlayerAITimer % 2 == 0)
                        GroundX[t] += 600;
                    if (PlayerAITimer % 2 == 1)
                        GroundX[t] -= 600;
                }
                if (PlayerAITimer >= 110)
                {
                    GroundY[t] -= mzz;
                    mzz += 80;
                    if (mzz > 1600)
                        mzz = 1600;
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
                    PlayerLookingDirection = 0;
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
                PlayerLookingDirection = 1;
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
                SyobonLevel++;
                SyobonSection = 0;
                zxon = 0;
                tyuukan = 0;
                SyobonState = ESyobonState::LIVES_SPLASH;
                SyobonStateTimer = 0;
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

            if ((PlayerState == 301 || PlayerState == 302) && PlayerAITimer >= 2 && PlayerAITimer <= 100)
            {
                PlayerVelX = 250;
                PlayerLookingDirection = 1;
            }

            if (PlayerAITimer == 200)
            {
                PlaySound(Sounds[17]);
                if (PlayerState == 301)
                {
                    BackgroundX[BackgroundCount] = 117 * 29 * 100 - 1100;
                    BackgroundY[BackgroundCount] = 4 * 29 * 100;
                    BackgroundType[BackgroundCount] = 101;
                    BackgroundCount++;
                    if (BackgroundCount >= nmax)
                        BackgroundCount = 0;
                    BackgroundX[BackgroundCount] = 115 * 29 * 100 - 1100;
                    BackgroundY[BackgroundCount] = 6 * 29 * 100;
                    BackgroundType[BackgroundCount] = 102;
                    BackgroundCount++;
                    if (BackgroundCount >= nmax)
                        BackgroundCount = 0;
                }
                else
                {
                    BackgroundX[BackgroundCount] = 157 * 29 * 100 - 1100;
                    BackgroundY[BackgroundCount] = 4 * 29 * 100;
                    BackgroundType[BackgroundCount] = 101;
                    BackgroundCount++;
                    if (BackgroundCount >= nmax)
                        BackgroundCount = 0;
                    BackgroundX[BackgroundCount] = 155 * 29 * 100 - 1100;
                    BackgroundY[BackgroundCount] = 6 * 29 * 100;
                    BackgroundType[BackgroundCount] = 102;
                    BackgroundCount++;
                    if (BackgroundCount >= nmax)
                        BackgroundCount = 0;
                }
            }
            // スタッフロールへ (Go to the credits)

            if (PlayerAITimer == 440)
            {
                if (PlayerState == 301)
                {
                    ending = 1;
                }
                else
                {
                    SyobonWorld++;
                    SyobonLevel = 1;
                    SyobonSection = 0;
                    zxon = 0;
                    tyuukan = 0;
                    SyobonState = ESyobonState::LIVES_SPLASH;
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
            if (PlayerGroundType == EGroundType::NORMAL)
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
            if (PlayerGroundType == EGroundType::SLIP)
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
    if (PlayerY >= 38000 && Health >= 0 && stagecolor == 4)
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
            PlayerLookingDirection = 0;
            actaon[4] = -1;
        }
        if (CheckHitKey(KEY_INPUT_RIGHT))
        {
            actaon[0] = 1;
            PlayerLookingDirection = 1;
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
        SyobonState = ESyobonState::TITLE;
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
    for (t = 0; t < tmax; t++)
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
                if (BlockType[t] < 1000 && BlockType[t] != 800 && BlockType[t] != 140 && BlockType[t] != 141)
                { // && ttype[t]!=5){

                    // if (!(mztm>=1 && mztype==1 && actaon[3]==1)){
                    if (!(mztype == 1))
                    {
                        xx[16] = 0;
                        xx[17] = 0;

                        // 上 (Above)
                        if (BlockType[t] != 7 && BlockType[t] != 110 && !(BlockType[t] == 114))
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
                                if (BlockType[t] != 115 && BlockType[t] != 400 && BlockType[t] != 117 && BlockType[t] != 118 && BlockType[t] != 120)
                                {
                                    PlayerY = xx[9] - PlayerSizeY + 100;
                                    PlayerVelY = 0;
                                    PlayerGrounded = 1;
                                    xx[16] = 1;
                                }
                                else if (BlockType[t] == 115)
                                {
                                    PlaySound(Sounds[3]);
                                    CreateExtraGraphic(BlockX[t] + 1200, BlockY[t] + 1200,
                                          300,
                                          -1000,
                                          0, 160, 1000, 1000, 1, 120);
                                    CreateExtraGraphic(BlockX[t] + 1200, BlockY[t] + 1200,
                                          -300,
                                          -1000,
                                          0, 160, 1000, 1000, 1, 120);
                                    CreateExtraGraphic(BlockX[t] + 1200, BlockY[t] + 1200,
                                          240,
                                          -1400,
                                          0, 160, 1000, 1000, 1, 120);
                                    CreateExtraGraphic(BlockX[t] + 1200, BlockY[t] + 1200,
                                          -240,
                                          -1400,
                                          0, 160, 1000, 1000, 1, 120);
                                    BlockBreak(t);
                                }
                                // Pスイッチ (P switch)
                                else if (BlockType[t] == 400)
                                {
                                    PlayerVelY = 0;
                                    BlockX[t] = -8000000;
                                    PlaySound(Sounds[13]);
                                    for (tt = 0; tt < tmax; tt++)
                                    {
                                        if (BlockType[tt] != 7)
                                        {
                                            BlockType[tt] = 800;
                                        }
                                    }
                                    SyobonKZHaltMusic();
                                }
                                // 音符+ (Musical note+)
                                else if (BlockType[t] == 117)
                                {
                                    PlaySound(Sounds[14]);
                                    PlayerVelY = -1500;
                                    PlayerState = 2;
                                    PlayerAITimer = 0;
                                    if (BlockSubType[t] >= 2 && PlayerState == 2)
                                    {
                                        PlayerState = 0;
                                        PlayerVelY = -1600;
                                        BlockSubType[t] = 3;
                                    }
                                    if (BlockSubType[t] == 0)
                                        BlockSubType[t] = 1;
                                }
                                // ジャンプ台 (Ski jump) //+KZ: ??
                                else if (BlockType[t] == 120)
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
                        if (PlayerGrounded == 1 || mjumptm >= 10)
                        {
                            xx[21] = 3;
                            xx[22] = 0;
                        }
                        for (t3 = 0; t3 <= 1; t3++)
                        {

                            // 下 (Below)
                            if (t3 == xx[21] && PlayerState != 100 && BlockType[t] != 117)
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
                                    if (BlockType[t] == 1 && PlayerGrounded == 0)
                                    {
                                        PlaySound(Sounds[3]);
                                        CreateExtraGraphic(BlockX[t] + 1200, BlockY[t] + 1200,
                                              300,
                                              -1000,
                                              0,
                                              160, 1000, 1000, 1, 120);
                                        CreateExtraGraphic(BlockX[t] + 1200, BlockY[t] + 1200,
                                              -300,
                                              -1000,
                                              0,
                                              160, 1000, 1000, 1, 120);
                                        CreateExtraGraphic(BlockX[t] + 1200, BlockY[t] + 1200,
                                              240,
                                              -1400,
                                              0,
                                              160, 1000, 1000, 1, 120);
                                        CreateExtraGraphic(BlockX[t] + 1200, BlockY[t] + 1200,
                                              -240,
                                              -1400,
                                              0,
                                              160, 1000, 1000, 1, 120);
                                        BlockBreak(t);
                                    }
                                    // コイン (Coin)
                                    if (BlockType[t] == 2 && PlayerGrounded == 0)
                                    {
                                        PlaySound(Sounds[4]);
                                        CreateExtraGraphic(BlockX[t] +
                                                  10,
                                              BlockY
                                                  [t],
                                              0,
                                              -800,
                                              0,
                                              40, 3000, 3000, 0, 16);
                                        BlockType[t] = 3;
                                    }
                                    // 隠し (Hidden)
                                    if (BlockType[t] == 7)
                                    {
                                        PlaySound(Sounds[4]);
                                        CreateExtraGraphic(BlockX[t] +
                                                  10,
                                              BlockY
                                                  [t],
                                              0,
                                              -800,
                                              0,
                                              40, 3000, 3000, 0, 16);
                                        PlayerY = xx[9] + xx[1] + xx[0];
                                        BlockType[t] = 3;
                                        if (PlayerVelY < 0)
                                        {
                                            PlayerVelY = -PlayerVelY * 2 / 3;
                                        }
                                    }
                                    // トゲ (Spikes)
                                    if (BlockType[t] == 10)
                                    {
                                        PlayerMessageTimer = 30;
                                        PlayerMessageType = 3;
                                        Health--;
                                    }
                                }
                            }
                            // 左右 (Left and right)
                            if (t3 == xx[22] && xx[15] == 0)
                            {
                                if (BlockType[t] != 7 && BlockType[t] != 110 && BlockType[t] != 117)
                                {
                                    if (!(BlockType[t] == 114))
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
                            }

                        } // t3
                    } //!

                } // && ttype[t]<50

                if (BlockType[t] == 800)
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
                if (BlockType[t] == 140)
                {
                    if (PlayerY >
                            xx[9] - xx[0] * 2 - 2000 &&
                        PlayerY <
                            xx[9] + xx[1] - xx[0] * 2 +
                                2000 &&
                        PlayerX + PlayerSizeX > xx[8] - 400 && PlayerX < xx[8] + xx[1])
                    {
                        BlockX[t] = -800000; // PlaySound(Sounds[4]);
                        sracttype[20] = 1;
                        sron[20] = 1;
                        SyobonKZHaltMusic();
                        PlayerState = 301;
                        PlayerAITimer = 0;
                        PlaySound(Sounds[16]);
                    }
                }
                // 特殊的 (special)
                if (BlockType[t] == 100)
                { // xx[9]+xx[1]+3000<mb && // && mb>xx[9]-xx[0]*2
                    if (PlayerY >
                            xx[9] - xx[0] * 2 - 2000 &&
                        PlayerY <
                            xx[9] + xx[1] - xx[0] * 2 +
                                2000 &&
                        PlayerX + PlayerSizeX > xx[8] - 400 && PlayerX < xx[8] + xx[1] && PlayerVelY <= 0)
                    {
                        if (BlockSubType[t] == 0)
                            BlockY[t] = PlayerY + fy - 1200 - xx[1];
                    }

                    if (BlockSubType[t] == 1)
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

                    if (xx[17] == 1 && BlockSubType[t] == 0)
                    {
                        PlaySound(Sounds[4]);
                        CreateExtraGraphic(BlockX[t] + 10, BlockY[t],
                              0, -800, 0, 40, 3000, 3000, 0, 16);
                        BlockType[t] = 3;
                    }
                } // 100

                // 敵出現 (Enemy Appearance)
                if (BlockType[t] == 101)
                { // xx[9]+xx[1]+3000<mb && // && mb>xx[9]-xx[0]*2
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        BlockType[t] = 3;
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        if (BlockSubType[t] == 0)
                            CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 0, 0);
                        if (BlockSubType[t] == 1)
                            CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 4, 0);
                        if (BlockSubType[t] == 3)
                            CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 101, 0);
                        if (BlockSubType[t] == 4)
                        {
                            EnemyBlockAppearTimer[EnemyCount] = 20;
                            CreateEntity(BlockX[t] -
                                             400,
                                         BlockY[t] - 1600, 0, 0, 0, 6, 0);
                        }
                        if (BlockSubType[t] == 10)
                            CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 101, 0);
                    }
                } // 101

                // おいしいきのこ出現 (Delicious mushrooms have appeared.)
                if (BlockType[t] == 102)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        BlockType[t] = 3;
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        if (BlockSubType[t] == 0)
                            CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 100, 0);
                        if (BlockSubType[t] == 2)
                            CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 100, 2);
                        if (BlockSubType[t] == 3)
                            CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 102, 1);
                    }
                } // 102

                // まずいきのこ出現 (First, mushrooms appear.)
                if (BlockType[t] == 103)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        BlockType[t] = 3;
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 100, 1);
                    }
                } // 103

                // 悪スター出し (Bad Star)
                if (BlockType[t] == 104)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        BlockType[t] = 3;
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 110, 0);
                    }
                } // 104

                // 毒きのこ量産 (Mass production of poisonous mushrooms)
                if (BlockType[t] == 110)
                {
                    if (xx[17] == 1)
                    {
                        BlockType[t] = 111;
                        thp[t] = 999;
                    }
                } // 110
                if (BlockType[t] == 111 && BlockX[t] - fx >= 0)
                {
                    thp[t]++;
                    if (thp[t] >= 16)
                    {
                        thp[t] = 0;
                        PlaySound(Sounds[8]);
                        EnemyBlockAppearTimer[EnemyCount] = 16;
                        CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 102, 1);
                    }
                }
                // コイン量産 (Coin mass production)
                if (BlockType[t] == 112)
                {
                    if (xx[17] == 1)
                    {
                        BlockType[t] = 113;
                        thp[t] = 999;
                        BlockItemCount[t] = 0;
                    }
                } // 110
                if (BlockType[t] == 113 && BlockX[t] - fx >= 0)
                {
                    if (BlockItemCount[t] <= 19)
                        thp[t]++;
                    if (thp[t] >= 3)
                    {
                        thp[t] = 0;
                        BlockItemCount[t]++;
                        PlaySound(Sounds[4]);
                        CreateExtraGraphic(BlockX[t] + 10, BlockY[t],
                              0, -800, 0, 40, 3000, 3000, 0, 16);
                        // ttype[t]=3;
                    }
                }
                // 隠し毒きのこ (Hidden poisonous mushroom)
                if (BlockType[t] == 114)
                {
                    if (xx[17] == 1)
                    {
                        if (BlockSubType[t] == 0)
                        {
                            PlaySound(Sounds[8]);
                            BlockType[t] = 3;
                            EnemyBlockAppearTimer[EnemyCount] = 16;
                            CreateEntity(BlockX[t], BlockY[t], 0, 0, 0, 102, 1);
                        }
                        if (BlockSubType[t] == 2)
                        {
                            PlaySound(Sounds[4]);
                            CreateExtraGraphic(BlockX[t] +
                                      10,
                                  BlockY[t],
                                  0, -800, 0, 40, 3000, 3000, 0, 16);
                            BlockType[t] = 115;
                            BlockSubType[t] = 0;
                        }
                        if (BlockSubType[t] == 10)
                        {
                            if (stageonoff == 1)
                            {
                                BlockType[t] = 130;
                                stageonoff = 0;
                                PlaySound(Sounds[13]);
                                BlockSubType[t] = 2;
                                for (t = 0; t < amax; t++)
                                {
                                    if (EnemyType[t] == 87 || EnemyType[t] == 88)
                                    {
                                        if (EnemySubType[t] == 105)
                                        {
                                            EnemySubType[t] = 110;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                PlaySound(Sounds[4]);
                                CreateExtraGraphic(BlockX[t] +
                                          10,
                                      BlockY
                                          [t],
                                      0,
                                      -800, 0, 40, 3000, 3000, 0, 16);
                                BlockType[t] = 3;
                            }
                        }
                    }
                } // 114

                // もろいブロック (Fragile block)
                if (BlockType[t] == 115)
                {

                } // 115

                // Pスイッチ (P switch)
                if (BlockType[t] == 116)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        // PlaySound(Sounds[13]);
                        BlockType[t] = 3; // abrocktm[aco]=18;CreateEntity(ta[t],tb[t],0,0,0,104,1);
                        BlockCreate(BlockX[t] / 100, (BlockY[t] / 100) - 29, 400);
                    }
                } // 116

                // ファイアバー強化 (Fire Bar Enhancement)
                if (BlockType[t] == 124)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[13]);
                        for (t = 0; t < amax; t++)
                        {
                            if (EnemyType[t] == 87 || EnemyType[t] == 88)
                            {
                                if (EnemySubType[t] == 101)
                                {
                                    EnemySubType[t] = 120;
                                }
                            }
                        }
                        BlockType[t] = 3;
                    }
                }
                // ONスイッチ (ON switch)
                if (BlockType[t] == 130)
                {
                    if (xx[17] == 1)
                    {
                        if (BlockSubType[t] != 1)
                        {
                            stageonoff = 0;
                            PlaySound(Sounds[13]);
                        }
                    }
                }
                else if (BlockType[t] == 131)
                {
                    if (xx[17] == 1 && BlockSubType[t] != 2)
                    {
                        stageonoff = 1;
                        PlaySound(Sounds[13]);
                        if (BlockSubType[t] == 1)
                        {
                            for (t = 0; t < amax; t++)
                            {
                                if (EnemyType[t] == 87 || EnemyType[t] == 88)
                                {
                                    if (EnemySubType[t] == 105)
                                    {
                                        EnemySubType[t] = 110;
                                    }
                                }
                            }
                            EnemyAppearSubType[3] = 105;
                        }
                    }
                }
                // ヒント (Hint)
                if (BlockType[t] == 300)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[15]);
                        if (BlockSubType[t] <= 100)
                        {
                            tmsgtype = 1;
                            tmsgtm = 15;
                            tmsgy = 300 + (BlockSubType[t] - 1);
                            tmsg = (BlockSubType[t]);
                        }
                        if (BlockSubType[t] == 540)
                        {
                            tmsgtype = 1;
                            tmsgtm = 15;
                            tmsgy = 400;
                            tmsg = 100;
                            BlockSubType[t] = 541;
                        }
                    }
                } // 300

                if (BlockType[t] == 301)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[3]);
                        CreateExtraGraphic(BlockX[t] + 1200,
                              BlockY[t] + 1200, 300,
                              -1000, 0, 160, 1000, 1000, 1, 120);
                        CreateExtraGraphic(BlockX[t] + 1200,
                              BlockY[t] + 1200,
                              -300, -1000, 0, 160, 1000, 1000, 1, 120);
                        CreateExtraGraphic(BlockX[t] + 1200,
                              BlockY[t] + 1200, 240,
                              -1400, 0, 160, 1000, 1000, 1, 120);
                        CreateExtraGraphic(BlockX[t] + 1200,
                              BlockY[t] + 1200,
                              -240, -1400, 0, 160, 1000, 1000, 1, 120);
                        BlockBreak(t);
                    }
                } // 300
            }
            else if (PlayerState == 1)
            {
                if (PlayerX + PlayerSizeX > xx[8] && PlayerX < xx[8] + xx[1] && PlayerY + PlayerSizeY > xx[9] && PlayerY < xx[9] + xx[1])
                {

                    PlaySound(Sounds[3]);
                    CreateExtraGraphic(BlockX[t] + 1200,
                          BlockY[t] + 1200, 300, -1000,
                          0, 160, 1000, 1000, 1, 120);
                    CreateExtraGraphic(BlockX[t] + 1200,
                          BlockY[t] + 1200, -300, -1000,
                          0, 160, 1000, 1000, 1, 120);
                    CreateExtraGraphic(BlockX[t] + 1200,
                          BlockY[t] + 1200, 240, -1400,
                          0, 160, 1000, 1000, 1, 120);
                    CreateExtraGraphic(BlockX[t] + 1200,
                          BlockY[t] + 1200, -240, -1400,
                          0, 160, 1000, 1000, 1, 120);
                    BlockBreak(t);
                }
            }
            // ONOFF
            if (BlockType[t] == 130 && stageonoff == 0)
            {
                BlockType[t] = 131;
            }
            if (BlockType[t] == 131 && stageonoff == 1)
            {
                BlockType[t] = 130;
            }
            // ヒント
            if (BlockType[t] == 300)
            {
                if (BlockSubType[t] >= 500 && BlockX[t] >= -6000)
                { // && ta[t]>=-6000){
                    if (BlockSubType[t] <= 539)
                        BlockSubType[t]++;
                    if (BlockSubType[t] >= 540)
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
    for (t = 0; t < smax; t++)
    {
        if (GroundX[t] - fx + GroundSizeX[t] >= -12000 && GroundX[t] - fx <= fxmax)
        {
            xx[0] = 200;
            xx[1] = 2400;
            xx[2] = 1000;
            xx[7] = 0;

            xx[8] = GroundX[t] - fx;
            xx[9] = GroundY[t] - fy;
            if ((GroundType[t] <= 99 || GroundType[t] == 200) && PlayerState < 10)
            {

                // おちるブロック (Falling blocks)
                if (GroundType[t] == 51)
                {
                    if (PlayerX + PlayerSizeX >
                            xx[8] + xx[0] + 3000 &&
                        PlayerX < xx[8] + GroundSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] + 3000 && GroundAI[t] == 0)
                    {
                        if (GroundSubType[t] == 0)
                        {
                            GroundAI[t] = 1;
                            GroundVelY[t] = 0;
                        }
                    }
                    if (PlayerX + PlayerSizeX >
                            xx[8] + xx[0] + 1000 &&
                        PlayerX < xx[8] + GroundSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] + 3000 && GroundAI[t] == 0)
                    {
                        if ((GroundSubType[t] == 10) && GroundAI[t] == 0)
                        {
                            GroundAI[t] = 1;
                            GroundVelY[t] = 0;
                        }
                    }

                    if ((GroundSubType[t] == 1) && GroundY[27] >= 25000 && GroundX[27] > PlayerX + PlayerSizeX && t != 27 && GroundAI[t] == 0)
                    {
                        GroundAI[t] = 1;
                        GroundVelY[t] = 0;
                    }
                    if (GroundSubType[t] == 2 && GroundY[28] >= 48000 && t != 28 && GroundAI[t] == 0 && Health >= 1)
                    {
                        GroundAI[t] = 1;
                        GroundVelY[t] = 0;
                    }
                    if ((GroundSubType[t] == 3 && PlayerY >= 30000 || GroundSubType[t] == 4 && PlayerY >= 25000) && GroundAI[t] == 0 && Health >= 1 && PlayerX + PlayerSizeX > xx[8] + xx[0] + 3000 - 300 && PlayerX < xx[8] + GroundSizeX[t] - xx[0])
                    {
                        GroundAI[t] = 1;
                        GroundVelY[t] = 0;
                        if (GroundSubType[t] == 4)
                            GroundVelY[t] = 100;
                    }

                    if (GroundAI[t] == 1 && GroundY[t] <= fymax + 18000)
                    {
                        GroundVelY[t] += 120;
                        if (GroundVelY[t] >= 1600)
                        {
                            GroundVelY[t] = 1600;
                        }
                        GroundY[t] += GroundVelY[t];
                        if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + GroundSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY < xx[9] + GroundSizeY[t] + xx[0])
                        {
                            Health--;
                            xx[7] = 1;
                        }
                    }
                }
                // おちるブロック2 (Falling Block 2)
                if (GroundType[t] == 52)
                {
                    if (GroundAI[t] == 0 && PlayerX + PlayerSizeX > xx[8] + xx[0] + 2000 && PlayerX < xx[8] + GroundSizeX[t] - xx[0] - 2500 && PlayerY + PlayerSizeY > xx[9] - 3000)
                    {
                        GroundAI[t] = 1;
                        GroundVelY[t] = 0;
                    }
                    if (GroundAI[t] == 1)
                    {
                        GroundVelY[t] += 120;
                        if (GroundVelY[t] >= 1600)
                        {
                            GroundVelY[t] = 1600;
                        }
                        GroundY[t] += GroundVelY[t];
                    }
                }
                // 通常地面 (Normal Ground)
                if (xx[7] == 0)
                {
                    if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + GroundSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY + PlayerSizeY < xx[9] + xx[1] && PlayerVelY >= -100)
                    {
                        PlayerY = GroundY[t] - fy - PlayerSizeY + 100;
                        PlayerVelY = 0;
                        PlayerGrounded = 1;
                    }
                    if (PlayerX + PlayerSizeX > xx[8] - xx[0] && PlayerX < xx[8] + xx[2] && PlayerY + PlayerSizeY > xx[9] + xx[1] * 3 / 4 && PlayerY < xx[9] + GroundSizeY[t] - xx[2])
                    {
                        PlayerX = xx[8] - xx[0] - PlayerSizeX;
                        PlayerVelX = 0;
                    }
                    if (PlayerX + PlayerSizeX > xx[8] + GroundSizeX[t] - xx[0] && PlayerX < xx[8] + GroundSizeX[t] + xx[0] && PlayerY + PlayerSizeY > xx[9] + xx[1] * 3 / 4 && PlayerY < xx[9] + GroundSizeY[t] - xx[2])
                    {
                        PlayerX = xx[8] + GroundSizeX[t] + xx[0];
                        PlayerVelX = 0;
                    }
                    if (PlayerX + PlayerSizeX >
                            xx[8] + xx[0] * 2 &&
                        PlayerX <
                            xx[8] + GroundSizeX[t] - xx[0] * 2 &&
                        PlayerY > xx[9] + GroundSizeY[t] - xx[1] && PlayerY < xx[9] + GroundSizeY[t] + xx[0])
                    {
                        PlayerY = xx[9] + GroundSizeY[t] + xx[0];
                        if (PlayerVelY < 0)
                        {
                            PlayerVelY = -PlayerVelY * 2 / 3;
                        }
                    }
                } // xx[7]

                // 入る土管 (Entering a pipe)
                if (GroundType[t] == 50)
                {
                    if (PlayerX + PlayerSizeX > xx[8] + 2800 && PlayerX < xx[8] + GroundSizeX[t] - 3000 && PlayerY + PlayerSizeY > xx[9] - 1000 && PlayerY + PlayerSizeY < xx[9] + xx[1] + 3000 && PlayerGrounded == 1 && actaon[3] == 1 && PlayerState == 0)
                    {
                        // 飛び出し
                        if (GroundSubType[t] == 0)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 0;
                        }
                        // 普通
                        if (GroundSubType[t] == 1)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 1;
                        }
                        // 普通
                        if (GroundSubType[t] == 2)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 2;
                        }
                        if (GroundSubType[t] == 5)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 5;
                        }
                        // ループ
                        if (GroundSubType[t] == 6)
                        {
                            PlayerState = 100;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]);
                            PlayerSubState = 6;
                        }
                    }
                } // 50

                // 入る土管(左から) (Pipes to enter (from left))
                if (GroundType[t] == 40)
                {
                    if (PlayerX + PlayerSizeX > xx[8] - 300 && PlayerX < xx[8] + GroundSizeX[t] - 1000 && PlayerY > xx[9] + 1000 && PlayerY + PlayerSizeY < xx[9] + xx[1] + 4000 && PlayerGrounded == 1 && actaon[4] == 1 && PlayerState == 0)
                    { // end();
                        // 飛び出し
                        if (GroundSubType[t] == 0)
                        {
                            PlayerState = 500;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]); // mxtype=1;
                            PlayerState = 100;
                            PlayerSubState = 10;
                        }

                        if (GroundSubType[t] == 2)
                        {
                            PlayerSubState = 3;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[7]); // mxtype=1;
                            PlayerState = 100;
                        }
                        // ループ
                        if (GroundSubType[t] == 6)
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
                if (PlayerX + PlayerSizeX > xx[8] + xx[0] && PlayerX < xx[8] + GroundSizeX[t] - xx[0] && PlayerY + PlayerSizeY > xx[9] && PlayerY < xx[9] + GroundSizeY[t] + xx[0])
                {
                    if (GroundType[t] == 100)
                    {
                        if (GroundSubType[t] == 0 || GroundSubType[t] == 1 && BlockType[1] != 3)
                        {
                            CreateEntity(GroundX[t] + 1000, 32000, 0, 0, 0, 3, 0);
                            GroundX[t] = -800000000;
                            PlaySound(Sounds[10]);
                        }
                    }
                    if (GroundType[t] == 101)
                    {
                        CreateEntity(GroundX[t] + 6000, -4000, 0, 0, 0, 3, 1);
                        GroundX[t] = -800000000;
                        PlaySound(Sounds[10]);
                    }
                    if (GroundType[t] == 102)
                    {
                        if (GroundSubType[t] == 0)
                        {
                            for (t3 = 0; t3 <= 3; t3++)
                            {
                                CreateEntity(GroundX[t] +
                                                 t3 * 3000,
                                             -3000, 0, 0, 0, 0, 0);
                            }
                        }
                        if (GroundSubType[t] == 1 && PlayerY >= 16000)
                        {
                            CreateEntity(GroundX[t] +
                                             1500,
                                         44000, 0, -2000, 0, 4, 0);
                        }
                        else if (GroundSubType[t] == 2)
                        {
                            CreateEntity(GroundX[t] +
                                             4500,
                                         30000, 0, -1600, 0, 5, 0);
                            PlaySound(Sounds[10]);
                            GroundSubType[t] = 3;
                            GroundX[t] -= 12000;
                        }
                        else if (GroundSubType[t] == 3)
                        {
                            GroundX[t] += 12000;
                            GroundSubType[t] = 4;
                        }
                        else if (GroundSubType[t] == 4)
                        {
                            CreateEntity(GroundX[t] +
                                             4500,
                                         30000, 0, -1600, 0, 5, 0);
                            PlaySound(Sounds[10]);
                            GroundSubType[t] = 5;
                            GroundSubType[t] = 0;
                        }

                        else if (GroundSubType[t] == 7)
                        {
                            mainmsgtype = 1;
                        }
                        else if (GroundSubType[t] == 8)
                        {
                            CreateEntity(GroundX[t] -
                                             5000 -
                                             3000 * 1,
                                         26000, 0, -1600, 0, 5, 0);
                            PlaySound(Sounds[10]);
                        }
                        else if (GroundSubType[t] == 9)
                        {
                            for (t3 = 0; t3 <= 2; t3++)
                            {
                                CreateEntity(GroundX[t] +
                                                 t3 *
                                                     3000 +
                                                 3000,
                                             48000, 0, -6000, 0, 3, 0);
                            }
                        }
                        if (GroundSubType[t] == 10)
                        {
                            GroundX[t] -= 5 * 30 * 100;
                            GroundType[t] = 101;
                        }

                        if (GroundSubType[t] == 12)
                        {
                            for (t3 = 1; t3 <= 3; t3++)
                            {
                                CreateEntity(GroundX[t] +
                                                 t3 *
                                                     3000 -
                                                 1000,
                                             40000, 0, -2600, 0, 9, 0);
                            }
                        }
                        // スクロール消し
                        if (GroundSubType[t] == 20)
                        {
                            scrollx = 0;
                        }
                        // クリア
                        if (GroundSubType[t] == 30)
                        {
                            GroundX[t] = -80000000;
                            PlayerVelY = 0;
                            SyobonKZHaltMusic();
                            PlayerState = 302;
                            PlayerAITimer = 0;
                            PlaySound(Sounds[16]);
                        }

                        if (GroundSubType[t] != 3 && GroundSubType[t] != 4 && GroundSubType[t] != 10)
                        {
                            GroundX[t] = -800000000;
                        }
                    }

                    if (GroundType[t] == 103)
                    {
                        if (GroundSubType[t] == 0)
                        {
                            EnemyMessageTimer[EnemyCount] = 10;
                            EnemyMessageType[EnemyCount] = 50;
                            CreateEntity(GroundX[t] +
                                             9000,
                                         GroundY[t] + 2000, 0, 0, 0, 79, 0);
                            GroundX[t] = -800000000;
                        }

                        if (GroundSubType[t] == 1 && BlockType[6] <= 6)
                        {
                            EnemyMessageTimer[EnemyCount] = 10;
                            EnemyMessageType[EnemyCount] = 50;
                            CreateEntity(GroundX[t] -
                                             12000,
                                         GroundY[t] + 2000, 0, 0, 0, 79, 0);
                            GroundX[t] = -800000000;
                            BlockSubType[9] = 500; // ttype[9]=1;
                        }
                    } // 103

                    if (GroundType[t] == 104)
                    {
                        if (GroundSubType[t] == 0)
                        {
                            CreateEntity(GroundX[t] +
                                             12000,
                                         GroundY[t] + 2000 + 3000, 0, 0, 0, 79, 0);
                            CreateEntity(GroundX[t] +
                                             12000,
                                         GroundY[t] + 2000 + 3000, 0, 0, 0, 79, 1);
                            CreateEntity(GroundX[t] +
                                             12000,
                                         GroundY[t] + 2000 + 3000, 0, 0, 0, 79, 2);
                            CreateEntity(GroundX[t] +
                                             12000,
                                         GroundY[t] + 2000 + 3000, 0, 0, 0, 79, 3);
                            CreateEntity(GroundX[t] +
                                             12000,
                                         GroundY[t] + 2000 + 3000, 0, 0, 0, 79, 4);
                            GroundX[t] = -800000000;
                        }
                    }

                    if (GroundType[t] == 105 && PlayerGrounded == 0 && PlayerVelY >= 0)
                    {
                        BlockX[1] -= 1000;
                        BlockX[2] += 1000;
                        GroundSubType[t]++;
                        if (GroundSubType[t] >= 3)
                            GroundX[t] = -8000000;
                    }

                    if (GroundType[t] == 300 && PlayerState == 0 && PlayerY < xx[9] + GroundSizeY[t] + xx[0] - 3000 && Health >= 1)
                    {
                        SyobonKZHaltMusic();
                        PlayerState = 300;
                        PlayerAITimer = 0;
                        PlayerX = GroundX[t] - fx - 2000;
                        PlaySound(Sounds[11]);
                    }
                    // 中間ゲート (Intermediate gate)
                    if (GroundType[t] == 500 && PlayerState == 0 && Health >= 1)
                    {
                        tyuukan += 1;
                        GroundX[t] = -80000000;
                    }
                }

                if (GroundType[t] == 180)
                {
                    GroundVelY[t]++;
                    if (GroundVelY[t] >= GroundAI[t])
                    {
                        GroundVelY[t] = 0;
                        CreateEntity(GroundX[t], 30000,
                                     SyobonRand(600) - 300,
                                     -1600 - SyobonRand(900), 0, 84, 0);
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
