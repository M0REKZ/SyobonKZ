#include "global_vars.h"
#include "main.h"
#include "player.h"
#include "entities.h"

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
    if (GroundType == EGroundType::SLIP)
    {
        xx[0] = 20;
        xx[12] = 9;
        xx[13] = 10;
    }
    // if (PlayerGrounded==0){xx[0]-=15;}
    if (actaon[0] == -1)
    {
        if (!(PlayerGrounded == 0 && mc < -xx[8]))
        {
            if (mc >= -xx[9])
            {
                mc -= xx[0];
                if (mc < -xx[9])
                {
                    mc = -xx[9] - 1;
                }
            }
            if (mc < -xx[9] && atktm <= 0)
                mc -= xx[0] / 10;
        }
        if (GroundType != EGroundType::SLIP)
        {
            if (mc > 100 && PlayerGrounded == 0)
            {
                mc -= xx[0] * 2 / 3;
            }
            if (mc > 100 && PlayerGrounded == 1)
            {
                mc -= xx[0];
                if (PlayerGrounded == 1)
                {
                    mc -= xx[0] * 1 / 2;
                }
            }
            actaon[0] = 3;
            mkasok += 1;
        }
    }

    if (actaon[0] == 1)
    {
        if (!(PlayerGrounded == 0 && mc > xx[8]))
        {
            if (mc <= xx[9])
            {
                mc += xx[0];
                if (mc > xx[9])
                {
                    mc = xx[9] + 1;
                }
            }
            if (mc > xx[9] && atktm <= 0)
                mc += xx[0] / 10;
        }
        if (GroundType != EGroundType::SLIP)
        {
            if (mc < -100 && PlayerGrounded == 0)
            {
                mc += xx[0] * 2 / 3;
            }
            if (mc < -100 && PlayerGrounded == 1)
            {
                mc += xx[0];
                if (PlayerGrounded == 1)
                {
                    mc += xx[0] * 1 / 2;
                }
            }
            actaon[0] = 3;
            mkasok += 1;
        }
    }
    if (actaon[0] == 0 && mkasok > 0)
    {
        mkasok -= 2;
    }
    if (mkasok > 8)
    {
        mkasok = 8;
    }
    // すべり補正初期化 (Initialization of slip correction)
    if (PlayerGrounded != 1)
        GroundType = EGroundType::NORMAL;

    // ジャンプ (Jump)
    if (mjumptm >= 0)
        mjumptm--;
    if (actaon[1] == 1 && PlayerGrounded == 1)
    {
        mb -= 400;
        md = -1200;
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
        mtype = 200;
        mtm = 0;
        Mix_HaltChannel(-1);
        Mix_HaltMusic();
        PlaySound(Sounds[12]);
        StopSoundMem(Sounds[16]);
    } // Health
    // if (Health<=-10){
    if (mtype == 200)
    {
        if (mtm <= 11)
        {
            mc = 0;
            md = 0;
        }
        if (mtm == 12)
        {
            md = -1200;
        }
        if (mtm >= 12)
        {
            mc = 0;
        }
        if (mtm >= 100 || fast == 1)
        {
            zxon = 0;
            SyobonState = ESyobonState::LIVES_SPLASH;
            mtm = 0;
            mkeytm = 0;
            Lives--;
            if (fast == 1)
                mtype = 0;
        } // mtm>=100
    } // mtype==200

    // 音符によるワープ (Warp using musical notes)
    if (mtype == 2)
    {
        mtm++;

        mkeytm = 2;
        md = -1500;
        if (mb <= -6000)
        {
            blackx = 1;
            blacktm = 20;
            SyobonSection += 5;
            Mix_HaltMusic();
            mtm = 0;
            mtype = 0;
            mkeytm = -1;
        }
    } // 2

    // ジャンプ台アウト
    if (mtype == 3)
    {
        md = -2400;
        if (mb <= -6000)
        {
            mb = -80000000;
            Health = 0;
        }
    }
    // mtypeによる特殊的な移動 (Special movement using mtype)
    if (mtype >= 100)
    {
        mtm++;

        // 普通の土管
        if (mtype == 100)
        {
            if (mxtype == 0)
            {
                mc = 0;
                md = 0;
                t = 28;
                if (mtm <= 16)
                {
                    mb += 240;
                    mzz = 100;
                }
                if (mtm == 17)
                {
                    mb = -80000000;
                }
                if (mtm == 23)
                {
                    sa[t] -= 100;
                }
                if (mtm >= 44 && mtm <= 60)
                {
                    if (mtm % 2 == 0)
                        sa[t] += 200;
                    if (mtm % 2 == 1)
                        sa[t] -= 200;
                }
                if (mtm >= 61 && mtm <= 77)
                {
                    if (mtm % 2 == 0)
                        sa[t] += 400;
                    if (mtm % 2 == 1)
                        sa[t] -= 400;
                }
                if (mtm >= 78 && mtm <= 78 + 16)
                {
                    if (mtm % 2 == 0)
                        sa[t] += 600;
                    if (mtm % 2 == 1)
                        sa[t] -= 600;
                }
                if (mtm >= 110)
                {
                    sb[t] -= mzz;
                    mzz += 80;
                    if (mzz > 1600)
                        mzz = 1600;
                }
                if (mtm == 160)
                {
                    mtype = 0;
                    Health--;
                }
            }
            // ふっとばし (Knock it away)
            else if (mxtype == 10)
            {
                mc = 0;
                md = 0;
                if (mtm <= 16)
                {
                    ma += 240;
                } // mzz=100;}
                if (mtm == 16)
                    mb -= 1100;
                if (mtm == 20)
                    PlaySound(Sounds[10]);

                if (mtm >= 24)
                {
                    ma -= 2000;
                    mmuki = 0;
                }
                if (mtm >= 48)
                {
                    mtype = 0;
                    Health--;
                }
            }
            else
            {
                mc = 0;
                md = 0;
                if (mtm <= 16 && mxtype != 3)
                {
                    mb += 240;
                } // mzz=100;}
                if (mtm <= 16 && mxtype == 3)
                {
                    ma += 240;
                }
                if (mtm == 19 && mxtype == 2)
                {
                    Health = 0;
                    mtype = 2000;
                    mtm = 0;
                    mmsgtm = 30;
                    mmsgtype = 51;
                }
                if (mtm == 19 && mxtype == 5)
                {
                    Health = 0;
                    mtype = 2000;
                    mtm = 0;
                    mmsgtm = 30;
                    mmsgtype = 52;
                }
                if (mtm == 20)
                {
                    if (mxtype == 6)
                    {
                        SyobonSection += 10;
                    }
                    else
                    {
                        SyobonSection++;
                    }
                    mb = -80000000;
                    mxtype = 0;
                    blackx = 1;
                    blacktm = 20;
                    Mix_HaltMusic();
                }
            }
        } // 00

        if (mtype == 300)
        {
            mkeytm = 3;
            if (mtm <= 1)
            {
                mc = 0;
                md = 0;
            }
            if (mtm >= 2 && mtm <= 42)
            {
                md = 600;
                mmuki = 1;
            }
            if (mtm > 43 && mtm <= 108)
            {
                mc = 300;
            }
            if (mtm == 110)
            {
                mb = -80000000;
                mc = 0;
            }
            if (mtm == 250)
            {
                SyobonLevel++;
                SyobonSection = 0;
                zxon = 0;
                tyuukan = 0;
                SyobonState = ESyobonState::LIVES_SPLASH;
                SyobonStateTimer = 0;
            }
        } // mtype==300

        if (mtype == 301 || mtype == 302)
        {
            mkeytm = 3;

            if (mtm <= 1)
            {
                mc = 0;
                md = 0;
            }

            if (mtm >= 2 && (mtype == 301 && mtm <= 102 || mtype == 302 && mtm <= 60))
            {
                xx[5] = 500;
                ma -= xx[5];
                fx += xx[5];
                fzx += xx[5];
            }

            if ((mtype == 301 || mtype == 302) && mtm >= 2 && mtm <= 100)
            {
                mc = 250;
                mmuki = 1;
            }

            if (mtm == 200)
            {
                PlaySound(Sounds[17]);
                if (mtype == 301)
                {
                    na[nco] = 117 * 29 * 100 - 1100;
                    nb[nco] = 4 * 29 * 100;
                    ntype[nco] = 101;
                    nco++;
                    if (nco >= nmax)
                        nco = 0;
                    na[nco] = 115 * 29 * 100 - 1100;
                    nb[nco] = 6 * 29 * 100;
                    ntype[nco] = 102;
                    nco++;
                    if (nco >= nmax)
                        nco = 0;
                }
                else
                {
                    na[nco] = 157 * 29 * 100 - 1100;
                    nb[nco] = 4 * 29 * 100;
                    ntype[nco] = 101;
                    nco++;
                    if (nco >= nmax)
                        nco = 0;
                    na[nco] = 155 * 29 * 100 - 1100;
                    nb[nco] = 6 * 29 * 100;
                    ntype[nco] = 102;
                    nco++;
                    if (nco >= nmax)
                        nco = 0;
                }
            }
            // スタッフロールへ (Go to the credits)

            if (mtm == 440)
            {
                if (mtype == 301)
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
            if (mtm>=2 && mtm<=42){md=600;mmuki=1;}
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
    ma += mc;
    mb += md;
    if (mc < 0)
        mactp += (-mc);
    if (mc >= 0)
        mactp += mc;

    if (mtype <= 9 || mtype == 200 || mtype == 300 || mtype == 301 || mtype == 302)
        md += 100;

    // 走る際の最大値 (Maximum value when running)
    if (mtype == 0)
    {
        xx[0] = 800;
        xx[1] = 1600;
        if (mc > xx[0] && mc < xx[0] + 200)
        {
            mc = xx[0];
        }
        if (mc > xx[0] + 200)
        {
            mc -= 200;
        }
        if (mc < -xx[0] && mc > -xx[0] - 200)
        {
            mc = -xx[0];
        }
        if (mc < -xx[0] - 200)
        {
            mc += 200;
        }
        if (md > xx[1])
        {
            md = xx[1];
        }
    }
    // プレイヤー (Player)
    // 地面の摩擦 (Ground friction)
    if (PlayerGrounded == 1 && actaon[0] != 3)
    {
        if ((mtype <= 9) || mtype == 300 || mtype == 301 || mtype == 302)
        {
            if (GroundType == EGroundType::NORMAL)
            {
                xx[2] = 30;
                xx[1] = 60;
                xx[3] = 30;
                if (mc >= -xx[3] && mc <= xx[3])
                {
                    mc = 0;
                }
                if (mc >= xx[2])
                {
                    mc -= xx[1];
                }
                if (mc <= -xx[2])
                {
                    mc += xx[1];
                }
            }
            if (GroundType == EGroundType::SLIP)
            {
                xx[2] = 5;
                xx[1] = 10;
                xx[3] = 5;
                if (mc >= -xx[3] && mc <= xx[3])
                {
                    mc = 0;
                }
                if (mc >= xx[2])
                {
                    mc -= xx[1];
                }
                if (mc <= -xx[2])
                {
                    mc += xx[1];
                }
            }
        }
    }
    // 地面判定初期化 (Initialize ground judgment)
    PlayerGrounded = 0;

    // 場外
    if (mtype <= 9 && Health >= 1)
    {
        if (ma < 100)
        {
            ma = 100;
            mc = 0;
        }
        if (ma + mnobia > fxmax)
        {
            ma = fxmax - mnobia;
            mc = 0;
        }
    }
    // if (mb>=42000){mb=42000;PlayerGrounded=1;}
    if (mb >= 38000 && Health >= 0 && stagecolor == 4)
    {
        Health = -2;
        mmsgtm = 30;
        mmsgtype = 55;
    }
    if (mb >= 52000 && Health >= 0)
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
        if (CheckHitKey(KEY_INPUT_LEFT) && keytm <= 0)
        {
            actaon[0] = -1;
            mmuki = 0;
            actaon[4] = -1;
        }
        if (CheckHitKey(KEY_INPUT_RIGHT) && keytm <= 0)
        {
            actaon[0] = 1;
            mmuki = 1;
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
        if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_UP) == 1 || SDL_JoystickGetButton(joystick, JOYSTICK_JUMP))
        {
            if (actaon[1] == 10)
            {
                actaon[1] = 1;
                xx[0] = 1;
            }
            actaon[2] = 1;
        }
    }

    if (CheckHitKey(KEY_INPUT_Z) == 1 || CheckHitKey(KEY_INPUT_UP) == 1 || SDL_JoystickGetButton(joystick, JOYSTICK_JUMP))
    {
        if (mjumptm == 8 && md >= -900)
        {
            md = -1300;
            // ダッシュ中
            xx[22] = 200;
            if (mc >= xx[22] || mc <= -xx[22])
            {
                md = -1400;
            }
            xx[22] = 600;
            if (mc >= xx[22] || mc <= -xx[22])
            {
                md = -1500;
            }
        }
        // && xx[0]==0 && md<=-10

        // if (mjumptm==7 && md>=-900){}
        if (xx[0] == 0)
            actaon[1] = 10;
    }
    // if (( key & PAD_INPUT_UP) && keytm<=0){actaon[0]=-1;mmuki=0;}

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
        xx[8] = ta[t] - fx;
        xx[9] = tb[t] - fy; // xx[15]=0;
        if (ta[t] - fx + xx[1] >= -10 - xx[3] && ta[t] - fx <= fxmax + 12000 + xx[3])
        {
            if (mtype != 200 && mtype != 1 && mtype != 2)
            {
                if (ttype[t] < 1000 && ttype[t] != 800 && ttype[t] != 140 && ttype[t] != 141)
                { // && ttype[t]!=5){

                    // if (!(mztm>=1 && mztype==1 && actaon[3]==1)){
                    if (!(mztype == 1))
                    {
                        xx[16] = 0;
                        xx[17] = 0;

                        // 上 (Above)
                        if (ttype[t] != 7 && ttype[t] != 110 && !(ttype[t] == 114))
                        {
                            if (ma +
                                        mnobia >
                                    xx[8] +
                                        xx[0] * 2 +
                                        100 &&
                                ma <
                                    xx[8] +
                                        xx[1] -
                                        xx[0] * 2 - 100 &&
                                mb + mnobib > xx[9] && mb + mnobib < xx[9] + xx[1] && md >= -100)
                            {
                                if (ttype[t] != 115 && ttype[t] != 400 && ttype[t] != 117 && ttype[t] != 118 && ttype[t] != 120)
                                {
                                    mb = xx[9] - mnobib + 100;
                                    md = 0;
                                    PlayerGrounded = 1;
                                    xx[16] = 1;
                                }
                                else if (ttype[t] == 115)
                                {
                                    PlaySound(Sounds[3]);
                                    eyobi(ta[t] + 1200, tb[t] + 1200,
                                          300,
                                          -1000,
                                          0, 160, 1000, 1000, 1, 120);
                                    eyobi(ta[t] + 1200, tb[t] + 1200,
                                          -300,
                                          -1000,
                                          0, 160, 1000, 1000, 1, 120);
                                    eyobi(ta[t] + 1200, tb[t] + 1200,
                                          240,
                                          -1400,
                                          0, 160, 1000, 1000, 1, 120);
                                    eyobi(ta[t] + 1200, tb[t] + 1200,
                                          -240,
                                          -1400,
                                          0, 160, 1000, 1000, 1, 120);
                                    BlockBreak(t);
                                }
                                // Pスイッチ (P switch)
                                else if (ttype[t] == 400)
                                {
                                    md = 0;
                                    ta[t] = -8000000;
                                    PlaySound(Sounds[13]);
                                    for (tt = 0; tt < tmax; tt++)
                                    {
                                        if (ttype[tt] != 7)
                                        {
                                            ttype[tt] = 800;
                                        }
                                    }
                                    Mix_HaltMusic();
                                }
                                // 音符+ (Musical note+)
                                else if (ttype[t] == 117)
                                {
                                    PlaySound(Sounds[14]);
                                    md = -1500;
                                    mtype = 2;
                                    mtm = 0;
                                    if (txtype[t] >= 2 && mtype == 2)
                                    {
                                        mtype = 0;
                                        md = -1600;
                                        txtype[t] = 3;
                                    }
                                    if (txtype[t] == 0)
                                        txtype[t] = 1;
                                }
                                // ジャンプ台 (Ski jump) //+KZ: ??
                                else if (ttype[t] == 120)
                                {
                                    // txtype[t]=0;
                                    md = -2400;
                                    mtype = 3;
                                    mtm = 0;
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
                            if (t3 == xx[21] && mtype != 100 && ttype[t] != 117)
                            { // && xx[12]==0){
                                if (ma + mnobia > xx[8] + xx[0] * 2 + 800 && ma < xx[8] + xx[1] - xx[0] * 2 - 800 && mb > xx[9] - xx[0] * 2 && mb < xx[9] + xx[1] - xx[0] * 2 && md <= 0)
                                {
                                    xx[16] = 1;
                                    xx[17] = 1;
                                    mb = xx[9] + xx[1] + xx[0];
                                    if (md < 0)
                                    {
                                        md = -md * 2 / 3;
                                    } //}
                                    // 壊れる (Break)
                                    if (ttype[t] == 1 && PlayerGrounded == 0)
                                    {
                                        PlaySound(Sounds[3]);
                                        eyobi(ta[t] + 1200, tb[t] + 1200,
                                              300,
                                              -1000,
                                              0,
                                              160, 1000, 1000, 1, 120);
                                        eyobi(ta[t] + 1200, tb[t] + 1200,
                                              -300,
                                              -1000,
                                              0,
                                              160, 1000, 1000, 1, 120);
                                        eyobi(ta[t] + 1200, tb[t] + 1200,
                                              240,
                                              -1400,
                                              0,
                                              160, 1000, 1000, 1, 120);
                                        eyobi(ta[t] + 1200, tb[t] + 1200,
                                              -240,
                                              -1400,
                                              0,
                                              160, 1000, 1000, 1, 120);
                                        BlockBreak(t);
                                    }
                                    // コイン (Coin)
                                    if (ttype[t] == 2 && PlayerGrounded == 0)
                                    {
                                        PlaySound(Sounds[4]);
                                        eyobi(ta[t] +
                                                  10,
                                              tb
                                                  [t],
                                              0,
                                              -800,
                                              0,
                                              40, 3000, 3000, 0, 16);
                                        ttype[t] = 3;
                                    }
                                    // 隠し (Hidden)
                                    if (ttype[t] == 7)
                                    {
                                        PlaySound(Sounds[4]);
                                        eyobi(ta[t] +
                                                  10,
                                              tb
                                                  [t],
                                              0,
                                              -800,
                                              0,
                                              40, 3000, 3000, 0, 16);
                                        mb = xx[9] + xx[1] + xx[0];
                                        ttype[t] = 3;
                                        if (md < 0)
                                        {
                                            md = -md * 2 / 3;
                                        }
                                    }
                                    // トゲ (Spikes)
                                    if (ttype[t] == 10)
                                    {
                                        mmsgtm = 30;
                                        mmsgtype = 3;
                                        Health--;
                                    }
                                }
                            }
                            // 左右 (Left and right)
                            if (t3 == xx[22] && xx[15] == 0)
                            {
                                if (ttype[t] != 7 && ttype[t] != 110 && ttype[t] != 117)
                                {
                                    if (!(ttype[t] == 114))
                                    { // && txtype[t]==1)){
                                        if (ta[t] >= -20000)
                                        {
                                            // if (ma+mnobia>xx[8] && ma<xx[8]+xx[2] && mb+mnobib>xx[9]+xx[1]/2-xx[0] &&){
                                            if (ma + mnobia > xx[8] && ma < xx[8] + xx[2] && mb + mnobib > xx[9] + xx[1] / 2 - xx[0] && mb < xx[9] + xx[2] && mc >= 0)
                                            {
                                                ma = xx[8] - mnobia;
                                                mc = 0;
                                                xx[16] = 1;
                                                // if (ttype[t]!=4){ma=xx[8]-mnobia;mc=0;xx[16]=1;}
                                                // if (ttype[t]==4){ma=xx[8]-mnobia;mc=-mc*4/4;}
                                            }
                                            if (ma + mnobia >
                                                    xx[8] + xx[2] &&
                                                ma < xx[8] + xx[1] && mb + mnobib > xx[9] + xx[1] / 2 - xx[0] && mb < xx[9] + xx[2] && mc <= 0)
                                            {
                                                ma = xx[8] + xx[1];
                                                mc = 0;
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

                if (ttype[t] == 800)
                {
                    // if (xx[0]+xx[2]>=-xx[14] && xx[0]<=fxmax+xx[14] && xx[1]+xx[3]>=-10-9000 && xx[1]<=fymax+10000){
                    if (mb >
                            xx[9] - xx[0] * 2 - 2000 &&
                        mb <
                            xx[9] + xx[1] - xx[0] * 2 +
                                2000 &&
                        ma + mnobia > xx[8] - 400 && ma < xx[8] + xx[1])
                    {
                        ta[t] = -800000;
                        PlaySound(Sounds[4]);
                    }
                }
                // 剣とってクリア (Get the sword and clear the stage.)
                if (ttype[t] == 140)
                {
                    if (mb >
                            xx[9] - xx[0] * 2 - 2000 &&
                        mb <
                            xx[9] + xx[1] - xx[0] * 2 +
                                2000 &&
                        ma + mnobia > xx[8] - 400 && ma < xx[8] + xx[1])
                    {
                        ta[t] = -800000; // PlaySound(Sounds[4]);
                        sracttype[20] = 1;
                        sron[20] = 1;
                        Mix_HaltMusic();
                        mtype = 301;
                        mtm = 0;
                        PlaySound(Sounds[16]);
                    }
                }
                // 特殊的 (special)
                if (ttype[t] == 100)
                { // xx[9]+xx[1]+3000<mb && // && mb>xx[9]-xx[0]*2
                    if (mb >
                            xx[9] - xx[0] * 2 - 2000 &&
                        mb <
                            xx[9] + xx[1] - xx[0] * 2 +
                                2000 &&
                        ma + mnobia > xx[8] - 400 && ma < xx[8] + xx[1] && md <= 0)
                    {
                        if (txtype[t] == 0)
                            tb[t] = mb + fy - 1200 - xx[1];
                    }

                    if (txtype[t] == 1)
                    {
                        if (xx[17] == 1)
                        {
                            if (ma +
                                        mnobia >
                                    xx[8] - 400 &&
                                ma < xx[8] + xx[1] / 2 - 1500)
                            {
                                ta[t] += 3000;
                            }
                            else if (ma + mnobia >= xx[8] + xx[1] / 2 - 1500 && ma < xx[8] + xx[1])
                            {
                                ta[t] -= 3000;
                            }
                        }
                    }

                    if (xx[17] == 1 && txtype[t] == 0)
                    {
                        PlaySound(Sounds[4]);
                        eyobi(ta[t] + 10, tb[t],
                              0, -800, 0, 40, 3000, 3000, 0, 16);
                        ttype[t] = 3;
                    }
                } // 100

                // 敵出現 (Enemy Appearance)
                if (ttype[t] == 101)
                { // xx[9]+xx[1]+3000<mb && // && mb>xx[9]-xx[0]*2
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        ttype[t] = 3;
                        abrocktm[aco] = 16;
                        if (txtype[t] == 0)
                            CreateEntity(ta[t], tb[t], 0, 0, 0, 0, 0);
                        if (txtype[t] == 1)
                            CreateEntity(ta[t], tb[t], 0, 0, 0, 4, 0);
                        if (txtype[t] == 3)
                            CreateEntity(ta[t], tb[t], 0, 0, 0, 101, 0);
                        if (txtype[t] == 4)
                        {
                            abrocktm[aco] = 20;
                            CreateEntity(ta[t] -
                                             400,
                                         tb[t] - 1600, 0, 0, 0, 6, 0);
                        }
                        if (txtype[t] == 10)
                            CreateEntity(ta[t], tb[t], 0, 0, 0, 101, 0);
                    }
                } // 101

                // おいしいきのこ出現 (Delicious mushrooms have appeared.)
                if (ttype[t] == 102)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        ttype[t] = 3;
                        abrocktm[aco] = 16;
                        if (txtype[t] == 0)
                            CreateEntity(ta[t], tb[t], 0, 0, 0, 100, 0);
                        if (txtype[t] == 2)
                            CreateEntity(ta[t], tb[t], 0, 0, 0, 100, 2);
                        if (txtype[t] == 3)
                            CreateEntity(ta[t], tb[t], 0, 0, 0, 102, 1);
                    }
                } // 102

                // まずいきのこ出現 (First, mushrooms appear.)
                if (ttype[t] == 103)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        ttype[t] = 3;
                        abrocktm[aco] = 16;
                        CreateEntity(ta[t], tb[t], 0, 0, 0, 100, 1);
                    }
                } // 103

                // 悪スター出し (Bad Star)
                if (ttype[t] == 104)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        ttype[t] = 3;
                        abrocktm[aco] = 16;
                        CreateEntity(ta[t], tb[t], 0, 0, 0, 110, 0);
                    }
                } // 104

                // 毒きのこ量産 (Mass production of poisonous mushrooms)
                if (ttype[t] == 110)
                {
                    if (xx[17] == 1)
                    {
                        ttype[t] = 111;
                        thp[t] = 999;
                    }
                } // 110
                if (ttype[t] == 111 && ta[t] - fx >= 0)
                {
                    thp[t]++;
                    if (thp[t] >= 16)
                    {
                        thp[t] = 0;
                        PlaySound(Sounds[8]);
                        abrocktm[aco] = 16;
                        CreateEntity(ta[t], tb[t], 0, 0, 0, 102, 1);
                    }
                }
                // コイン量産 (Coin mass production)
                if (ttype[t] == 112)
                {
                    if (xx[17] == 1)
                    {
                        ttype[t] = 113;
                        thp[t] = 999;
                        titem[t] = 0;
                    }
                } // 110
                if (ttype[t] == 113 && ta[t] - fx >= 0)
                {
                    if (titem[t] <= 19)
                        thp[t]++;
                    if (thp[t] >= 3)
                    {
                        thp[t] = 0;
                        titem[t]++;
                        PlaySound(Sounds[4]);
                        eyobi(ta[t] + 10, tb[t],
                              0, -800, 0, 40, 3000, 3000, 0, 16);
                        // ttype[t]=3;
                    }
                }
                // 隠し毒きのこ (Hidden poisonous mushroom)
                if (ttype[t] == 114)
                {
                    if (xx[17] == 1)
                    {
                        if (txtype[t] == 0)
                        {
                            PlaySound(Sounds[8]);
                            ttype[t] = 3;
                            abrocktm[aco] = 16;
                            CreateEntity(ta[t], tb[t], 0, 0, 0, 102, 1);
                        }
                        if (txtype[t] == 2)
                        {
                            PlaySound(Sounds[4]);
                            eyobi(ta[t] +
                                      10,
                                  tb[t],
                                  0, -800, 0, 40, 3000, 3000, 0, 16);
                            ttype[t] = 115;
                            txtype[t] = 0;
                        }
                        if (txtype[t] == 10)
                        {
                            if (stageonoff == 1)
                            {
                                ttype[t] = 130;
                                stageonoff = 0;
                                PlaySound(Sounds[13]);
                                txtype[t] = 2;
                                for (t = 0; t < amax; t++)
                                {
                                    if (atype[t] == 87 || atype[t] == 88)
                                    {
                                        if (axtype[t] == 105)
                                        {
                                            axtype[t] = 110;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                PlaySound(Sounds[4]);
                                eyobi(ta[t] +
                                          10,
                                      tb
                                          [t],
                                      0,
                                      -800, 0, 40, 3000, 3000, 0, 16);
                                ttype[t] = 3;
                            }
                        }
                    }
                } // 114

                // もろいブロック (Fragile block)
                if (ttype[t] == 115)
                {

                } // 115

                // Pスイッチ (P switch)
                if (ttype[t] == 116)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[8]);
                        // PlaySound(Sounds[13]);
                        ttype[t] = 3; // abrocktm[aco]=18;CreateEntity(ta[t],tb[t],0,0,0,104,1);
                        BlockCreate(ta[t] / 100, (tb[t] / 100) - 29, 400);
                    }
                } // 116

                // ファイアバー強化 (Fire Bar Enhancement)
                if (ttype[t] == 124)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[13]);
                        for (t = 0; t < amax; t++)
                        {
                            if (atype[t] == 87 || atype[t] == 88)
                            {
                                if (axtype[t] == 101)
                                {
                                    axtype[t] = 120;
                                }
                            }
                        }
                        ttype[t] = 3;
                    }
                }
                // ONスイッチ (ON switch)
                if (ttype[t] == 130)
                {
                    if (xx[17] == 1)
                    {
                        if (txtype[t] != 1)
                        {
                            stageonoff = 0;
                            PlaySound(Sounds[13]);
                        }
                    }
                }
                else if (ttype[t] == 131)
                {
                    if (xx[17] == 1 && txtype[t] != 2)
                    {
                        stageonoff = 1;
                        PlaySound(Sounds[13]);
                        if (txtype[t] == 1)
                        {
                            for (t = 0; t < amax; t++)
                            {
                                if (atype[t] == 87 || atype[t] == 88)
                                {
                                    if (axtype[t] == 105)
                                    {
                                        axtype[t] = 110;
                                    }
                                }
                            }
                            bxtype[3] = 105;
                        }
                    }
                }
                // ヒント (Hint)
                if (ttype[t] == 300)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[15]);
                        if (txtype[t] <= 100)
                        {
                            tmsgtype = 1;
                            tmsgtm = 15;
                            tmsgy = 300 + (txtype[t] - 1);
                            tmsg = (txtype[t]);
                        }
                        if (txtype[t] == 540)
                        {
                            tmsgtype = 1;
                            tmsgtm = 15;
                            tmsgy = 400;
                            tmsg = 100;
                            txtype[t] = 541;
                        }
                    }
                } // 300

                if (ttype[t] == 301)
                {
                    if (xx[17] == 1)
                    {
                        PlaySound(Sounds[3]);
                        eyobi(ta[t] + 1200,
                              tb[t] + 1200, 300,
                              -1000, 0, 160, 1000, 1000, 1, 120);
                        eyobi(ta[t] + 1200,
                              tb[t] + 1200,
                              -300, -1000, 0, 160, 1000, 1000, 1, 120);
                        eyobi(ta[t] + 1200,
                              tb[t] + 1200, 240,
                              -1400, 0, 160, 1000, 1000, 1, 120);
                        eyobi(ta[t] + 1200,
                              tb[t] + 1200,
                              -240, -1400, 0, 160, 1000, 1000, 1, 120);
                        BlockBreak(t);
                    }
                } // 300
            }
            else if (mtype == 1)
            {
                if (ma + mnobia > xx[8] && ma < xx[8] + xx[1] && mb + mnobib > xx[9] && mb < xx[9] + xx[1])
                {

                    PlaySound(Sounds[3]);
                    eyobi(ta[t] + 1200,
                          tb[t] + 1200, 300, -1000,
                          0, 160, 1000, 1000, 1, 120);
                    eyobi(ta[t] + 1200,
                          tb[t] + 1200, -300, -1000,
                          0, 160, 1000, 1000, 1, 120);
                    eyobi(ta[t] + 1200,
                          tb[t] + 1200, 240, -1400,
                          0, 160, 1000, 1000, 1, 120);
                    eyobi(ta[t] + 1200,
                          tb[t] + 1200, -240, -1400,
                          0, 160, 1000, 1000, 1, 120);
                    BlockBreak(t);
                }
            }
            // ONOFF
            if (ttype[t] == 130 && stageonoff == 0)
            {
                ttype[t] = 131;
            }
            if (ttype[t] == 131 && stageonoff == 1)
            {
                ttype[t] = 130;
            }
            // ヒント
            if (ttype[t] == 300)
            {
                if (txtype[t] >= 500 && ta[t] >= -6000)
                { // && ta[t]>=-6000){
                    if (txtype[t] <= 539)
                        txtype[t]++;
                    if (txtype[t] >= 540)
                    {
                        ta[t] -= 500;
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
        if (sa[t] - fx + sc[t] >= -12000 && sa[t] - fx <= fxmax)
        {
            xx[0] = 200;
            xx[1] = 2400;
            xx[2] = 1000;
            xx[7] = 0;

            xx[8] = sa[t] - fx;
            xx[9] = sb[t] - fy;
            if ((stype[t] <= 99 || stype[t] == 200) && mtype < 10)
            {

                // おちるブロック (Falling blocks)
                if (stype[t] == 51)
                {
                    if (ma + mnobia >
                            xx[8] + xx[0] + 3000 &&
                        ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] + 3000 && sgtype[t] == 0)
                    {
                        if (sxtype[t] == 0)
                        {
                            sgtype[t] = 1;
                            sr[t] = 0;
                        }
                    }
                    if (ma + mnobia >
                            xx[8] + xx[0] + 1000 &&
                        ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] + 3000 && sgtype[t] == 0)
                    {
                        if ((sxtype[t] == 10) && sgtype[t] == 0)
                        {
                            sgtype[t] = 1;
                            sr[t] = 0;
                        }
                    }

                    if ((sxtype[t] == 1) && sb[27] >= 25000 && sa[27] > ma + mnobia && t != 27 && sgtype[t] == 0)
                    {
                        sgtype[t] = 1;
                        sr[t] = 0;
                    }
                    if (sxtype[t] == 2 && sb[28] >= 48000 && t != 28 && sgtype[t] == 0 && Health >= 1)
                    {
                        sgtype[t] = 1;
                        sr[t] = 0;
                    }
                    if ((sxtype[t] == 3 && mb >= 30000 || sxtype[t] == 4 && mb >= 25000) && sgtype[t] == 0 && Health >= 1 && ma + mnobia > xx[8] + xx[0] + 3000 - 300 && ma < xx[8] + sc[t] - xx[0])
                    {
                        sgtype[t] = 1;
                        sr[t] = 0;
                        if (sxtype[t] == 4)
                            sr[t] = 100;
                    }

                    if (sgtype[t] == 1 && sb[t] <= fymax + 18000)
                    {
                        sr[t] += 120;
                        if (sr[t] >= 1600)
                        {
                            sr[t] = 1600;
                        }
                        sb[t] += sr[t];
                        if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] && mb < xx[9] + sd[t] + xx[0])
                        {
                            Health--;
                            xx[7] = 1;
                        }
                    }
                }
                // おちるブロック2 (Falling Block 2)
                if (stype[t] == 52)
                {
                    if (sgtype[t] == 0 && ma + mnobia > xx[8] + xx[0] + 2000 && ma < xx[8] + sc[t] - xx[0] - 2500 && mb + mnobib > xx[9] - 3000)
                    {
                        sgtype[t] = 1;
                        sr[t] = 0;
                    }
                    if (sgtype[t] == 1)
                    {
                        sr[t] += 120;
                        if (sr[t] >= 1600)
                        {
                            sr[t] = 1600;
                        }
                        sb[t] += sr[t];
                    }
                }
                // 通常地面 (Normal Ground)
                if (xx[7] == 0)
                {
                    if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] && mb + mnobib < xx[9] + xx[1] && md >= -100)
                    {
                        mb = sb[t] - fy - mnobib + 100;
                        md = 0;
                        PlayerGrounded = 1;
                    }
                    if (ma + mnobia > xx[8] - xx[0] && ma < xx[8] + xx[2] && mb + mnobib > xx[9] + xx[1] * 3 / 4 && mb < xx[9] + sd[t] - xx[2])
                    {
                        ma = xx[8] - xx[0] - mnobia;
                        mc = 0;
                    }
                    if (ma + mnobia > xx[8] + sc[t] - xx[0] && ma < xx[8] + sc[t] + xx[0] && mb + mnobib > xx[9] + xx[1] * 3 / 4 && mb < xx[9] + sd[t] - xx[2])
                    {
                        ma = xx[8] + sc[t] + xx[0];
                        mc = 0;
                    }
                    if (ma + mnobia >
                            xx[8] + xx[0] * 2 &&
                        ma <
                            xx[8] + sc[t] - xx[0] * 2 &&
                        mb > xx[9] + sd[t] - xx[1] && mb < xx[9] + sd[t] + xx[0])
                    {
                        mb = xx[9] + sd[t] + xx[0];
                        if (md < 0)
                        {
                            md = -md * 2 / 3;
                        }
                    }
                } // xx[7]

                // 入る土管 (Entering a pipe)
                if (stype[t] == 50)
                {
                    if (ma + mnobia > xx[8] + 2800 && ma < xx[8] + sc[t] - 3000 && mb + mnobib > xx[9] - 1000 && mb + mnobib < xx[9] + xx[1] + 3000 && PlayerGrounded == 1 && actaon[3] == 1 && mtype == 0)
                    {
                        // 飛び出し
                        if (sxtype[t] == 0)
                        {
                            mtype = 100;
                            mtm = 0;
                            PlaySound(Sounds[7]);
                            mxtype = 0;
                        }
                        // 普通
                        if (sxtype[t] == 1)
                        {
                            mtype = 100;
                            mtm = 0;
                            PlaySound(Sounds[7]);
                            mxtype = 1;
                        }
                        // 普通
                        if (sxtype[t] == 2)
                        {
                            mtype = 100;
                            mtm = 0;
                            PlaySound(Sounds[7]);
                            mxtype = 2;
                        }
                        if (sxtype[t] == 5)
                        {
                            mtype = 100;
                            mtm = 0;
                            PlaySound(Sounds[7]);
                            mxtype = 5;
                        }
                        // ループ
                        if (sxtype[t] == 6)
                        {
                            mtype = 100;
                            mtm = 0;
                            PlaySound(Sounds[7]);
                            mxtype = 6;
                        }
                    }
                } // 50

                // 入る土管(左から) (Pipes to enter (from left))
                if (stype[t] == 40)
                {
                    if (ma + mnobia > xx[8] - 300 && ma < xx[8] + sc[t] - 1000 && mb > xx[9] + 1000 && mb + mnobib < xx[9] + xx[1] + 4000 && PlayerGrounded == 1 && actaon[4] == 1 && mtype == 0)
                    { // end();
                        // 飛び出し
                        if (sxtype[t] == 0)
                        {
                            mtype = 500;
                            mtm = 0;
                            PlaySound(Sounds[7]); // mxtype=1;
                            mtype = 100;
                            mxtype = 10;
                        }

                        if (sxtype[t] == 2)
                        {
                            mxtype = 3;
                            mtm = 0;
                            PlaySound(Sounds[7]); // mxtype=1;
                            mtype = 100;
                        }
                        // ループ
                        if (sxtype[t] == 6)
                        {
                            mtype = 3;
                            mtm = 0;
                            PlaySound(Sounds[7]);
                            mxtype = 6;
                        }
                    }
                } // 40

            } // stype
            else
            {
                if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + sc[t] - xx[0] && mb + mnobib > xx[9] && mb < xx[9] + sd[t] + xx[0])
                {
                    if (stype[t] == 100)
                    {
                        if (sxtype[t] == 0 || sxtype[t] == 1 && ttype[1] != 3)
                        {
                            CreateEntity(sa[t] + 1000, 32000, 0, 0, 0, 3, 0);
                            sa[t] = -800000000;
                            PlaySound(Sounds[10]);
                        }
                    }
                    if (stype[t] == 101)
                    {
                        CreateEntity(sa[t] + 6000, -4000, 0, 0, 0, 3, 1);
                        sa[t] = -800000000;
                        PlaySound(Sounds[10]);
                    }
                    if (stype[t] == 102)
                    {
                        if (sxtype[t] == 0)
                        {
                            for (t3 = 0; t3 <= 3; t3++)
                            {
                                CreateEntity(sa[t] +
                                                 t3 * 3000,
                                             -3000, 0, 0, 0, 0, 0);
                            }
                        }
                        if (sxtype[t] == 1 && mb >= 16000)
                        {
                            CreateEntity(sa[t] +
                                             1500,
                                         44000, 0, -2000, 0, 4, 0);
                        }
                        else if (sxtype[t] == 2)
                        {
                            CreateEntity(sa[t] +
                                             4500,
                                         30000, 0, -1600, 0, 5, 0);
                            PlaySound(Sounds[10]);
                            sxtype[t] = 3;
                            sa[t] -= 12000;
                        }
                        else if (sxtype[t] == 3)
                        {
                            sa[t] += 12000;
                            sxtype[t] = 4;
                        }
                        else if (sxtype[t] == 4)
                        {
                            CreateEntity(sa[t] +
                                             4500,
                                         30000, 0, -1600, 0, 5, 0);
                            PlaySound(Sounds[10]);
                            sxtype[t] = 5;
                            sxtype[t] = 0;
                        }

                        else if (sxtype[t] == 7)
                        {
                            mainmsgtype = 1;
                        }
                        else if (sxtype[t] == 8)
                        {
                            CreateEntity(sa[t] -
                                             5000 -
                                             3000 * 1,
                                         26000, 0, -1600, 0, 5, 0);
                            PlaySound(Sounds[10]);
                        }
                        else if (sxtype[t] == 9)
                        {
                            for (t3 = 0; t3 <= 2; t3++)
                            {
                                CreateEntity(sa[t] +
                                                 t3 *
                                                     3000 +
                                                 3000,
                                             48000, 0, -6000, 0, 3, 0);
                            }
                        }
                        if (sxtype[t] == 10)
                        {
                            sa[t] -= 5 * 30 * 100;
                            stype[t] = 101;
                        }

                        if (sxtype[t] == 12)
                        {
                            for (t3 = 1; t3 <= 3; t3++)
                            {
                                CreateEntity(sa[t] +
                                                 t3 *
                                                     3000 -
                                                 1000,
                                             40000, 0, -2600, 0, 9, 0);
                            }
                        }
                        // スクロール消し
                        if (sxtype[t] == 20)
                        {
                            scrollx = 0;
                        }
                        // クリア
                        if (sxtype[t] == 30)
                        {
                            sa[t] = -80000000;
                            md = 0;
                            Mix_HaltMusic();
                            mtype = 302;
                            mtm = 0;
                            PlaySound(Sounds[16]);
                        }

                        if (sxtype[t] != 3 && sxtype[t] != 4 && sxtype[t] != 10)
                        {
                            sa[t] = -800000000;
                        }
                    }

                    if (stype[t] == 103)
                    {
                        if (sxtype[t] == 0)
                        {
                            amsgtm[aco] = 10;
                            amsgtype[aco] = 50;
                            CreateEntity(sa[t] +
                                             9000,
                                         sb[t] + 2000, 0, 0, 0, 79, 0);
                            sa[t] = -800000000;
                        }

                        if (sxtype[t] == 1 && ttype[6] <= 6)
                        {
                            amsgtm[aco] = 10;
                            amsgtype[aco] = 50;
                            CreateEntity(sa[t] -
                                             12000,
                                         sb[t] + 2000, 0, 0, 0, 79, 0);
                            sa[t] = -800000000;
                            txtype[9] = 500; // ttype[9]=1;
                        }
                    } // 103

                    if (stype[t] == 104)
                    {
                        if (sxtype[t] == 0)
                        {
                            CreateEntity(sa[t] +
                                             12000,
                                         sb[t] + 2000 + 3000, 0, 0, 0, 79, 0);
                            CreateEntity(sa[t] +
                                             12000,
                                         sb[t] + 2000 + 3000, 0, 0, 0, 79, 1);
                            CreateEntity(sa[t] +
                                             12000,
                                         sb[t] + 2000 + 3000, 0, 0, 0, 79, 2);
                            CreateEntity(sa[t] +
                                             12000,
                                         sb[t] + 2000 + 3000, 0, 0, 0, 79, 3);
                            CreateEntity(sa[t] +
                                             12000,
                                         sb[t] + 2000 + 3000, 0, 0, 0, 79, 4);
                            sa[t] = -800000000;
                        }
                    }

                    if (stype[t] == 105 && PlayerGrounded == 0 && md >= 0)
                    {
                        ta[1] -= 1000;
                        ta[2] += 1000;
                        sxtype[t]++;
                        if (sxtype[t] >= 3)
                            sa[t] = -8000000;
                    }

                    if (stype[t] == 300 && mtype == 0 && mb < xx[9] + sd[t] + xx[0] - 3000 && Health >= 1)
                    {
                        Mix_HaltMusic();
                        mtype = 300;
                        mtm = 0;
                        ma = sa[t] - fx - 2000;
                        PlaySound(Sounds[11]);
                    }
                    // 中間ゲート (Intermediate gate)
                    if (stype[t] == 500 && mtype == 0 && Health >= 1)
                    {
                        tyuukan += 1;
                        sa[t] = -80000000;
                    }
                }

                if (stype[t] == 180)
                {
                    sr[t]++;
                    if (sr[t] >= sgtype[t])
                    {
                        sr[t] = 0;
                        CreateEntity(sa[t], 30000,
                                     rand(600) - 300,
                                     -1600 - rand(900), 0, 84, 0);
                    }
                }
            }
        }
    } // 壁 (Wall)
}
