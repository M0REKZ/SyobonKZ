#include "global_vars.h"
#include "main.h"
#include "entities.h"

void HandleEntities()
{
    // 敵キャラ (Enemy character)
    for (t = 0; t < amax; t++)
    {
        xx[0] = aa[t] - fx;
        xx[1] = ab[t] - fy;
        xx[2] = anobia[t];
        xx[3] = anobib[t];
        xx[14] = 12000 * 1;
        if (anotm[t] >= 0)
            anotm[t]--;
        if (xx[0] + xx[2] >= -xx[14] && xx[0] <= fxmax + xx[14] && xx[1] + xx[3] >= -10 - 9000 && xx[1] <= fymax + 20000)
        {
            aacta[t] = 0;
            aactb[t] = 0;

            xx[10] = 0;

            switch (atype[t])
            {
            case 0:
                xx[10] = 100;
                break;

                // こうらの敵 (Shell enemy)
            case 1:
                xx[10] = 100;
                break;

                // こうら (Shell)
            case 2:
                xx[10] = 0;
                xx[17] = 800;
                if (axtype[t] >= 1)
                    xx[10] = xx[17];
                // if (axtype[t]==1)xx[10]=xx[17];
                // if (axtype[t]==2)xx[10]=-xx[17];
                // 他の敵を倒す (Defeat other enemies)
                if (axtype[t] >= 1)
                {
                    for (tt = 0; tt < amax; tt++)
                    {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = aa[tt] - fx;
                        xx[9] = ab[tt] - fy;
                        if (t != tt)
                        {
                            if (aa[t] +
                                        anobia[t] -
                                        fx >
                                    xx[8] +
                                        xx[0] * 2 &&
                                aa[t] -
                                        fx <
                                    xx[8] +
                                        anobia[tt] -
                                        xx[0] * 2 &&
                                ab[t] +
                                        anobib[t] - fy >
                                    xx[9] + xx[5] &&
                                ab[t] +
                                        anobib[t] -
                                        fy <
                                    xx[9] + xx[1] * 3 + xx[12] + 1500)
                            {
                                aa[tt] = -800000;
                                PlaySound(Sounds[6]);
                            }
                        }
                    }
                }

                break;

                // あらまき
            case 3:
                azimentype[t] = 0; // end();
                if (axtype[t] == 0)
                {
                    ab[t] -= 800;
                }
                if (axtype[t] == 1)
                    ab[t] += 1200;

                // xx[10]=100;
                break;

                // スーパージエン
            case 4:
                xx[10] = 120;
                xx[0] = 250;
                xx[8] = aa[t] - fx;
                xx[9] = ab[t] - fy;
                if (atm[t] >= 0)
                    atm[t]--;
                if (abs(ma + mnobia - xx[8] - xx[0] * 2) < 9000
                    /*&& abs(ma < //+KZ "warning: result of comparison of constant 3000 with expression of type 'bool' is always true"
                           xx[8] - anobia[t] +
                           xx[0] * 2) < 3000*/
                    && md <= -600 && atm[t] <= 0)
                {
                    if (axtype[t] == 1 && PlayerGrounded == 0 && axzimen[t] == 1)
                    {
                        ad[t] = -1600;
                        atm[t] = 40;
                        ab[t] -= 1000;
                    }
                } //
                break;

                // クマー (Bear)
            case 5:
                xx[10] = 160;
                // azimentype[t]=2;
                break;

                // デフラグさん (Defrag-san)
            case 6:
                if (azimentype[t] == 30)
                {
                    ad[t] = -1600;
                    ab[t] += ad[t];
                }

                xx[10] = 120;
                if (atm[t] >= 10)
                {
                    atm[t]++;
                    if (Health >= 1)
                    {
                        if (atm[t] <= 19)
                        {
                            ma = xx[0];
                            mb = xx[1] - 3000;
                            mtype = 0;
                        }
                        xx[10] = 0;
                        if (atm[t] == 20)
                        {
                            mc = 700;
                            mkeytm = 24;
                            md = -1200;
                            mb = xx[1] - 1000 - 3000;
                            amuki[t] = 1;
                            if (axtype[t] == 1)
                            {
                                mc = 840;
                                axtype[t] = 0;
                            }
                        }
                        if (atm[t] == 40)
                        {
                            amuki[t] = 0;
                            atm[t] = 0;
                        }
                    }
                }
                // ポール捨て (Discarding the pole)
                if (axtype[t] == 1)
                {
                    for (tt = 0; tt < smax; tt++)
                    {
                        if (stype[tt] == 300)
                        {
                            // sa[sco]=xx[21]*100;sb[sco]=xx[22]*100;sc[sco]=3000;sd[sco]=(12-t)*3000;stype[sco]=300;sco++;
                            if (aa[t] -
                                        fx >=
                                    -8000 &&
                                aa[t] >=
                                    sa[tt] +
                                        2000 &&
                                aa[t] <= sa[tt] + 3600 && axzimen[t] == 1)
                            {
                                sa[tt] = -800000;
                                atm[t] = 100;
                            }
                        }
                    }

                    if (atm[t] == 100)
                    {
                        eyobi(aa[t] + 1200 -
                                  1200,
                              ab[t] + 3000 -
                                  10 * 3000 - 1500,
                              0, 0, 0, 0, 1000,
                              10 * 3000 - 1200, 4, 20);
                        if (mtype == 300)
                        {
                            mtype = 0;
                            StopSoundMem(Sounds[11]);
                            bgmchange(Music[1]);
                        }
                        for (t1 = 0; t1 < smax; t1++)
                        {
                            if (stype[t1] == 104)
                                sa[t1] = -80000000;
                        }
                    }
                    if (atm[t] == 120)
                    {
                        eyobi(aa[t] + 1200 -
                                  1200,
                              ab[t] + 3000 -
                                  10 * 3000 - 1500,
                              600, -1200, 0,
                              160, 1000, 10 * 3000 - 1200, 4, 240);
                        amuki[t] = 1;
                    }
                    // mc=700;mkeytm=24;md=-1200;mb=xx[1]-1000-3000;amuki[t]=1;if (axtype[t]==1){mc=840;axtype[t]=0;}}
                    if (atm[t] == 140)
                    {
                        amuki[t] = 0;
                        atm[t] = 0;
                    }
                }
                if (atm[t] >= 220)
                {
                    atm[t] = 0;
                    amuki[t] = 0;
                }
                // 他の敵を投げる (Throw other enemies)
                for (tt = 0; tt < amax; tt++)
                {
                    xx[0] = 250;
                    xx[5] = -800;
                    xx[12] = 0;
                    xx[1] = 1600;
                    xx[8] = aa[tt] - fx;
                    xx[9] = ab[tt] - fy;
                    if (t != tt && atype[tt] >= 100)
                    {
                        if (aa[t] + anobia[t] -
                                    fx >
                                xx[8] + xx[0] * 2 &&
                            aa[t] - fx <
                                xx[8] + anobia[tt] -
                                    xx[0] * 2 &&
                            ab[t] + anobib[t] - fy > xx[9] + xx[5] && ab[t] + anobib[t] - fy < xx[9] + xx[1] * 3 + xx[12] + 1500)
                        {
                            // aa[tt]=-800000;
                            amuki[tt] = 1;
                            aa[tt] = aa[t] + 300;
                            ab[tt] = ab[t] - 3000;
                            abrocktm[tt] = 120; // aa[tt]=0;
                            atm[t] = 200;
                            amuki[t] = 1;
                        }
                    }
                }

                break;

                // ジエン大砲
            case 7:
                azimentype[t] = 0;
                xx[10] = 0;
                xx[11] = 400;
                if (axtype[t] == 0)
                    xx[10] = xx[11];
                if (axtype[t] == 1)
                    xx[10] = -xx[11];
                if (axtype[t] == 2)
                    ab[t] -= xx[11];
                if (axtype[t] == 3)
                    ab[t] += xx[11];
                break;

                // スーパーブーン (Super Boom) //+KZ: xD??
            case 8:
                azimentype[t] = 0;
                xx[22] = 20;
                if (atm[t] == 0)
                {
                    af[t] += xx[22];
                    ad[t] += xx[22];
                }
                if (atm[t] == 1)
                {
                    af[t] -= xx[22];
                    ad[t] -= xx[22];
                }
                if (ad[t] > 300)
                    ad[t] = 300;
                if (ad[t] < -300)
                    ad[t] = -300;
                if (af[t] >= 1200)
                    atm[t] = 1;
                if (af[t] < -0)
                    atm[t] = 0;
                ab[t] += ad[t];
                // atype[t]=151;
                break;
                // ノーマルブーン (Normal Boom)
            case 151:
                azimentype[t] = 2;
                break;

                // ファイアー玉 (Fireball)
            case 9:
                azimentype[t] = 5;
                ab[t] += ad[t];
                ad[t] += 100;
                if (ab[t] >= fymax + 1000)
                {
                    ad[t] = 900;
                }
                if (ab[t] >= fymax + 12000)
                {
                    ab[t] = fymax;
                    ad[t] = -2600;
                }
                break;

                // ファイアー (Fire)
            case 10:
                azimentype[t] = 0;
                xx[10] = 0;
                xx[11] = 400;
                if (axtype[t] == 0)
                    xx[10] = xx[11];
                if (axtype[t] == 1)
                    xx[10] = -xx[11];
                break;

                // モララー (Molalla)
            case 30:
                atm[t] += 1;
                if (axtype[t] == 0)
                {
                    if (atm[t] == 50 && mb >= 6000)
                    {
                        ac[t] = 300;
                        ad[t] -= 1600;
                        ab[t] -= 1000;
                    }

                    for (tt = 0; tt < amax; tt++)
                    {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = aa[tt] - fx;
                        xx[9] = ab[tt] - fy;
                        if (t != tt && atype[tt] == 102)
                        {
                            if (aa[t] +
                                        anobia[t] -
                                        fx >
                                    xx[8] +
                                        xx[0] * 2 &&
                                aa[t] -
                                        fx <
                                    xx[8] +
                                        anobia[tt] -
                                        xx[0] * 2 &&
                                ab[t] +
                                        anobib[t] - fy >
                                    xx[9] + xx[5] &&
                                ab[t] +
                                        anobib[t] -
                                        fy <
                                    xx[9] + xx[1] * 3 + xx[12] + 1500)
                            {
                                aa[tt] = -800000;
                                axtype[t] = 1;
                                ad[t] = -1600;
                                amsgtm[t] = 30;
                                amsgtype[t] = 25;
                            }
                        }
                    }
                }
                if (axtype[t] == 1)
                {
                    azimentype[t] = 0;
                    ab[t] += ad[t];
                    ad[t] += 120;
                }
                break;

                // レーザー (Laser)
            case 79:
                azimentype[t] = 0;
                xx[10] = 1600;
                if (axtype[t] == 1)
                {
                    xx[10] = 1200;
                    ab[t] -= 200;
                }
                if (axtype[t] == 2)
                {
                    xx[10] = 1200;
                    ab[t] += 200;
                }
                if (axtype[t] == 3)
                {
                    xx[10] = 900;
                    ab[t] -= 600;
                }
                if (axtype[t] == 4)
                {
                    xx[10] = 900;
                    ab[t] += 600;
                }
                break;

                // 雲の敵 (Enemy of the Clouds)
            case 80:
                azimentype[t] = 0;
                // xx[10]=100;
                break;
            case 81:
                azimentype[t] = 0;
                break;
            case 82:
                azimentype[t] = 0;
                break;
            case 83:
                azimentype[t] = 0;
                break;

            case 84:
                azimentype[t] = 2;
                break;

            case 85:
                xx[23] = 400;
                if (axtype[t] == 0)
                {
                    axtype[t] = 1;
                    amuki[t] = 1;
                }
                if (mb >= 30000 && ma >= aa[t] - 3000 * 5 - fx && ma <= aa[t] - fx && axtype[t] == 1)
                {
                    axtype[t] = 5;
                    amuki[t] = 0;
                }
                if (mb >= 24000 && ma <= aa[t] + 3000 * 8 - fx && ma >= aa[t] - fx && axtype[t] == 1)
                {
                    axtype[t] = 5;
                    amuki[t] = 1;
                }
                if (axtype[t] == 5)
                    xx[10] = xx[23];
                break;

            case 86:
                azimentype[t] = 4;
                xx[23] = 1000;
                if (ma >= aa[t] - fx - mnobia - xx[26] && ma <= aa[t] - fx + anobia[t] + xx[26])
                {
                    atm[t] = 1;
                }
                if (atm[t] == 1)
                {
                    ab[t] += 1200;
                }
                break;

                // ファイアバー (Fire Bar)
            case 87:
                azimentype[t] = 0;
                if (aa[t] % 10 != 1)
                    atm[t] += 6;
                else
                {
                    atm[t] -= 6;
                }
                xx[25] = 2;
                if (atm[t] > 360 * xx[25])
                    atm[t] -= 360 * xx[25];
                if (atm[t] < 0)
                    atm[t] += 360 * xx[25];

                for (tt = 0; tt <= axtype[t] % 100; tt++)
                {
                    xx[26] = 18;
                    xd[4] = tt * xx[26] * cos(atm[t] * pai / 180 / 2);
                    xd[5] = tt * xx[26] * sin(atm[t] * pai / 180 / 2);

                    xx[4] = 1800;
                    xx[5] = 800;
                    xx[8] = aa[t] - fx + int(xd[4]) * 100 - xx[4] / 2;
                    xx[9] = ab[t] - fy + int(xd[5]) * 100 - xx[4] / 2;

                    if (ma + mnobia > xx[8] + xx[5] && ma < xx[8] + xx[4] - xx[5] && mb + mnobib > xx[9] + xx[5] && mb < xx[9] + xx[4] - xx[5])
                    {
                        Health -= 1;
                        mmsgtype = 51;
                        mmsgtm = 30;
                    }
                }

                break;

                //+KZ: Syobon Action 2 inverted Fire Bar
            case 88:
                azimentype[t] = 0;
                if (aa[t] % 10 != 1)
                    atm[t] += 6;
                else
                {
                    atm[t] -= 6;
                }
                xx[25] = 2;
                if (atm[t] > 360 * xx[25])
                    atm[t] -= 360 * xx[25];
                if (atm[t] < 0)
                    atm[t] += 360 * xx[25];

                for (tt = 0; tt <= axtype[t] % 100; tt++)
                {
                    xx[26] = 18;
                    xd[4] = -tt * xx[26] * cos(atm[t] * pai / 180 / 2);
                    xd[5] = tt * xx[26] * sin(atm[t] * pai / 180 / 2);

                    xx[4] = 1800;
                    xx[5] = 800;
                    xx[8] = aa[t] - fx + int(xd[4]) * 100 - xx[4] / 2;
                    xx[9] = ab[t] - fy + int(xd[5]) * 100 - xx[4] / 2;

                    if (ma + mnobia > xx[8] + xx[5] && ma < xx[8] + xx[4] - xx[5] && mb + mnobib > xx[9] + xx[5] && mb < xx[9] + xx[4] - xx[5])
                    {
                        Health -= 1;
                        mmsgtype = 51;
                        mmsgtm = 30;
                    }
                }

                break;

            case 90:
                xx[10] = 160;
                // azimentype[t]=0;
                break;

                // おいしいキノコ (Delicious mushrooms)
            case 100:
                azimentype[t] = 1;
                xx[10] = 100;

                // ほかの敵を巨大化 (Enlarge other enemies)
                if (axtype[t] == 2)
                {
                    for (tt = 0; tt < amax; tt++)
                    {
                        xx[0] = 250;
                        xx[5] = -800;
                        xx[12] = 0;
                        xx[1] = 1600;
                        xx[8] = aa[tt] - fx;
                        xx[9] = ab[tt] - fy;
                        if (t != tt)
                        {
                            if (aa[t] +
                                        anobia[t] -
                                        fx >
                                    xx[8] +
                                        xx[0] * 2 &&
                                aa[t] -
                                        fx <
                                    xx[8] +
                                        anobia[tt] -
                                        xx[0] * 2 &&
                                ab[t] +
                                        anobib[t] - fy >
                                    xx[9] + xx[5] &&
                                ab[t] +
                                        anobib[t] -
                                        fy <
                                    xx[9] + xx[1] * 3 + xx[12])
                            {
                                if (atype[tt] == 0 || atype[tt] == 4)
                                {
                                    atype[tt] = 90; // PlaySound(Sounds[6]);
                                    anobia[tt] = 6400;
                                    anobib[tt] = 6300;
                                    axtype[tt] = 0;
                                    aa[tt] -= 1050;
                                    ab[tt] -= 1050;
                                    PlaySound(Sounds[9]);
                                    aa[t] = -80000000;
                                }
                            }
                        }
                    }
                }

                break;

                // 毒キノコ (Poisonous mushrooms)
            case 102:
                azimentype[t] = 1;
                xx[10] = 100;
                if (axtype[t] == 1)
                    xx[10] = 200;
                break;

                // 悪スター (Bad Star)
            case 110:
                azimentype[t] = 1;
                xx[10] = 200;
                if (axzimen[t] == 1)
                {
                    ab[t] -= 1200;
                    ad[t] = -1400;
                }
                break;

            case 200:
                azimentype[t] = 1;
                xx[10] = 100;
                break;

                /*
                case 1:
                xx[10]=180;
                if (axtype[t]==2)xx[10]=0;
                if (axzimen[t]==1){
                ab[t]-=1000;ad[t]=-1200;
                if (axtype[t]==1)ad[t]=-1600;
                if (axtype[t]==2){
                atm[t]+=1;
                if (atm[t]>=2){atm[t]=0;ad[t]=-1600;}else{ad[t]=-1000;}
                }
                }

                break;

                case 2:
                xx[10]=160;
                if (axtype[t]==1)azimentype[t]=2;xx[10]=100;
                if (axtype[t]==2)xx[10]=0;
                break;

                case 3:
                xx[10]=180;
                if (ae[t]==0)ad[t]+=10;
                if (ae[t]==1)ad[t]-=10;
                if (ad[t]>=100)ae[t]=1;
                if (ad[t]<=-100)ae[t]=0;
                ab[t]+=ad[t];//ad[t]+=

                if (axtype[t]==1){
                if (ab[t]<mb){ab[t]+=100;}
                }
                if (axtype[t]==2)xx[10]=0;
                break;

                case 4:
                if (ae[t]==0)ad[t]+=8;
                if (ae[t]==1)ad[t]-=8;
                if (ad[t]>=80)ae[t]=1;
                if (ad[t]<=-80)ae[t]=0;
                ab[t]+=ad[t];

                //sstr=""+atm[t];
                if (axtype[t]>=1){
                xx[22]=200;xx[21]=3600;

                if (atm[t]==0){atm[t]=ab[t]%2+1;a2tm[t]=aa[t];if (axtype[t]%2==0)a2tm[t]=ab[t];}

                if (axtype[t]%2==1){
                if (aa[t]<a2tm[t]-xx[21]){atm[t]=2;}
                if (aa[t]>a2tm[t]+xx[21]){atm[t]=1;}
                if (atm[t]==1){aa[t]-=xx[22];amuki[t]=0;}
                if (atm[t]==2){aa[t]+=xx[22];amuki[t]=1;}
                }
                if (axtype[t]%2==0){
                if (ab[t]<a2tm[t]-xx[21]){atm[t]=2;}
                if (ab[t]>a2tm[t]+xx[21]){atm[t]=1;}
                if (atm[t]==1){ab[t]-=xx[22];}
                if (atm[t]==2){ab[t]+=xx[22];}
                }

                }//axtype1

                break;

                case 5:
                xx[10]=120;atm[t]++;
                if (axtype[t]==2){xx[10]=200;azimentype[t]=2;}
                if (ma+mnobia>=aa[t]-fx && ma<=aa[t]+anobia[t]-fx && mb+mnobib+1000<ab[t]-fy){
                xx[10]=300;
                if (axtype[t]>=1){
                //xx[10]=240;
                if (atm[t]>=16){amuki[t]+=1;if (amuki[t]>=2)amuki[t]=0;atm[t]=0;
                //if (axtype[t]==2){ab[t]-=600;ad[t]=-900;}
                }}
                }
                break;

                case 6:
                atm[t]+=1;xx[10]=0;
                if (axtype[t]==1)atm[t]+=(rand(9)-4);
                if (axtype[t]==2)xx[10]=100;
                if (atm[t]>=40){
                xx[22]=360;if (amuki[t]==0)xx[22]=-xx[22];
                cyobi(aa[t]+amuki[t]*anobia[t],ab[t]+1600,xx[22],0,0,0,0,60);
                atm[t]=0;
                }

                if (axtype[t]!=2){
                if (ma+mnobia/2<=aa[t]+anobia[t]/2-fx){amuki[t]=0;}else{amuki[t]=1;}
                }
                break;

                case 7:
                xx[10]=160;
                if (axtype[t]==1)xx[10]=240;
                if (axtype[t]==2)xx[10]=60;
                break;

                case 8:
                atm[t]+=1;xx[10]=0;
                xx[15]=12;xx[17]=0;
                if (axtype[t]==1)xx[15]=8;
                if (axtype[t]==2){xx[15]=40;xx[17]=3;}

                if (atm[t]>=xx[15]){
                for (t3=0;t3<=xx[17];t3++){
                xx[16]=300;xx[22]=rand(xx[16])*5/4-xx[16]/4;
                a2tm[t]+=1;if (a2tm[t]>=1){xx[22]=-xx[22];a2tm[t]=-1;}
                cyobi(aa[t]+amuki[t]*anobia[t]/2,ab[t]+600,xx[22],-400-rand(600),0,80,1,60);
                //if ((xx[16]==0) || t3==xx[16])atm[t]=0;
                }//t
                atm[t]=0;
                }

                break;


                */

            } // sw

            if (abrocktm[t] >= 1)
                xx[10] = 0;

            if (amuki[t] == 0)
                aacta[t] -= xx[10];
            if (amuki[t] == 1)
                aacta[t] += xx[10];

            // 最大値 (Maximum value)
            xx[0] = 850;
            xx[1] = 1200;

            // if (mc>xx[0]){mc=xx[0];}
            // if (mc<-xx[0]){mc=-xx[0];}
            if (ad[t] > xx[1] && azimentype[t] != 5)
            {
                ad[t] = xx[1];
            }
            // 行動 (Action)
            aa[t] += aacta[t]; // ab[t]+=aactb[t];

            if ((azimentype[t] >= 1 || azimentype[t] == -1) && abrocktm[t] <= 0)
            {
                // if (atype[t]==4)end();

                // 移動 (Move)
                aa[t] += ac[t];
                if (azimentype[t] >= 1 && azimentype[t] <= 3)
                {
                    ab[t] += ad[t];
                    ad[t] += 120;
                } // ad[t]+=180;

                if (axzimen[t] == 1)
                {
                    xx[0] = 100;
                    if (ac[t] >= 200)
                    {
                        ac[t] -= xx[0];
                    }
                    else if (ac[t] <= -200)
                    {
                        ac[t] += xx[0];
                    }
                    else
                    {
                        ac[t] = 0;
                    }
                }

                axzimen[t] = 0;

                // 地面判定 (Ground judgment)
                if (azimentype[t] != 2)
                {
                    HandleTiles();
                }

            } // azimentype[t]>=1

            // ブロックから出現するさい (When appearing from a block)
            if (abrocktm[t] > 0)
            {
                abrocktm[t]--;
                if (abrocktm[t] < 100)
                {
                    ab[t] -= 180;
                }
                if (abrocktm[t] > 100)
                {
                }
                if (abrocktm[t] == 100)
                {
                    ab[t] -= 800;
                    ad[t] = -1200;
                    ac[t] = 700;
                    abrocktm[t] = 0;
                }
            } // abrocktm[t]>0

            // プレイヤーからの判定 (Player's judgment)
            xx[0] = 250;
            xx[1] = 1600;
            xx[2] = 1000;
            xx[4] = 500;
            xx[5] = -800;

            xx[8] = aa[t] - fx;
            xx[9] = ab[t] - fy;
            xx[12] = 0;
            if (md >= 100)
                xx[12] = md;
            xx[25] = 0;

            if (ma + mnobia > xx[8] + xx[0] * 2 && ma < xx[8] + anobia[t] - xx[0] * 2 && mb + mnobib > xx[9] - xx[5] && mb + mnobib < xx[9] + xx[1] + xx[12] && (mmutekitm <= 0 || md >= 100) && abrocktm[t] <= 0)
            {
                if (atype[t] != 4 && atype[t] != 9 && atype[t] != 10 && (atype[t] <= 78 || atype[t] == 85) && PlayerGrounded != 1 && mtype != 200)
                { // && atype[t]!=4 && atype[t]!=7){

                    if (atype[t] == 0)
                    {
                        if (axtype[t] == 0)
                            aa[t] = -900000;
                        if (axtype[t] == 1)
                        {
                            PlaySound(Sounds[5]);
                            mb = xx[9] - 900 - anobib[t];
                            md = -2100;
                            xx[25] = 1;
                            actaon[2] = 0;
                        }
                    }

                    if (atype[t] == 1)
                    {
                        atype[t] = 2;
                        anobib[t] = 3000;
                        axtype[t] = 0;
                    }
                    // こうら (Shell)
                    else if (atype[t] == 2 && md >= 0)
                    {
                        if (axtype[t] == 1 || axtype[t] == 2)
                        {
                            axtype[t] = 0;
                        }
                        else if (axtype[t] == 0)
                        {
                            if (ma +
                                        mnobia >
                                    xx[8] +
                                        xx[0] * 2 &&
                                ma <
                                    xx[8] + anobia[t] / 2 - xx[0] * 4)
                            {
                                axtype[t] = 1;
                                amuki[t] = 1;
                            }
                            else
                            {
                                axtype[t] = 1;
                                amuki[t] = 0;
                            }
                        }
                    }
                    if (atype[t] == 3)
                    {
                        xx[25] = 1;
                    }

                    if (atype[t] == 6)
                    {
                        atm[t] = 10;
                        md = 0;
                        actaon[2] = 0;
                    }

                    if (atype[t] == 7)
                    {
                        aa[t] = -900000;
                    }

                    if (atype[t] == 8)
                    {
                        atype[t] = 151;
                        ad[t] = 0;
                    }
                    // if (atype[t]==4){
                    // xx[25]=1;
                    // }

                    if (atype[t] != 85)
                    {
                        if (xx[25] == 0)
                        {
                            PlaySound(Sounds[5]);
                            mb = xx[9] - 1000 - anobib[t];
                            md = -1000;
                        }
                    }
                    if (atype[t] == 85)
                    {
                        if (xx[25] == 0)
                        {
                            PlaySound(Sounds[5]);
                            mb = xx[9] - 4000;
                            md = -1000;
                            axtype[t] = 5;
                        }
                    }

                    if (actaon[2] == 1)
                    {
                        md = -1600;
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
            if (atype[t] == 4 || atype[t] == 9 || atype[t] == 10)
                xx[16] = -3000;
            if (atype[t] == 82 || atype[t] == 83 || atype[t] == 84)
                xx[16] = -3200;
            if (atype[t] == 85)
                xx[16] = -anobib[t] + 6000;
            if (ma + mnobia > xx[8] + xx[4] && ma < xx[8] + anobia[t] - xx[4] && mb < xx[9] + anobib[t] + xx[15] && mb + mnobib > xx[9] + anobib[t] - xx[0] + xx[16] && anotm[t] <= 0 && abrocktm[t] <= 0)
            {
                if (mmutekion == 1)
                {
                    aa[t] = -9000000;
                }
                if (mmutekitm <= 0 && (atype[t] <= 99 || atype[t] >= 200))
                {
                    if (mmutekion != 1 && mtype != 200)
                    {
                        // if (mmutekitm<=0)

                        // ダメージ (Damage)
                        if ((atype[t] != 2 || axtype[t] != 0) && Health >= 1)
                        {
                            if (atype[t] != 6)
                            {
                                Health -= 1;
                                // mmutekitm=40;
                            }
                        }

                        if (atype[t] == 6)
                        {
                            atm[t] = 10;
                        }
                        // せりふ (Dialogue)
                        if (Health == 0)
                        {

                            if (atype[t] == 0 || atype[t] == 7)
                            {
                                amsgtm[t] = 60;
                                amsgtype[t] = rand(7) + 1 + 1000 + (SyobonLevel - 1) * 10;
                            }

                            if (atype[t] == 1)
                            {
                                amsgtm[t] = 60;
                                amsgtype[t] = rand(2) + 15;
                            }

                            if (atype[t] == 2 && axtype[t] >= 1 && mmutekitm <= 0)
                            {
                                amsgtm[t] = 60;
                                amsgtype[t] = 18;
                            }

                            if (atype[t] == 3)
                            {
                                amsgtm[t] = 60;
                                amsgtype[t] = 20;
                            }

                            if (atype[t] == 4)
                            {
                                amsgtm[t] = 60;
                                amsgtype[t] = rand(7) + 1 + 1000 + (SyobonLevel - 1) * 10;
                            }

                            if (atype[t] == 5)
                            {
                                amsgtm[t] = 60;
                                amsgtype[t] = 21;
                            }

                            if (atype[t] == 9 || atype[t] == 10)
                            {
                                mmsgtm = 30;
                                mmsgtype = 54;
                            }

                            if (atype[t] == 31)
                            {
                                amsgtm[t] = 30;
                                amsgtype[t] = 24;
                            }

                            if (atype[t] == 80 || atype[t] == 81)
                            {
                                amsgtm[t] = 60;
                                amsgtype[t] = 30;
                            }

                            if (atype[t] == 82)
                            {
                                amsgtm[t] = 20;
                                amsgtype[t] = rand(1) + 31;
                                xx[24] = 900;
                                atype[t] = 83;
                                aa[t] -= xx[24] + 100;
                                ab[t] -= xx[24] - 100 * 0;
                            } // 82

                            if (atype[t] == 84)
                            {
                                mmsgtm = 30;
                                mmsgtype = 50;
                            }

                            if (atype[t] == 85)
                            {
                                amsgtm[t] = 60;
                                amsgtype[t] = rand(1) + 85;
                            }
                            // 雲
                            if (atype[t] == 80)
                            {
                                atype[t] = 81;
                            }

                        } // Health==0

                        // こうら (Shell)
                        if (atype[t] == 2)
                        {
                            // if (axtype[t]==1 || axtype[t]==2){axtype[t]=0;}
                            if (axtype[t] == 0)
                            {
                                if (ma + mnobia > xx[8] + xx[0] * 2 && ma < xx[8] + anobia[t] / 2 - xx[0] * 4)
                                {
                                    axtype[t] = 1;
                                    amuki[t] = 1;
                                    aa[t] = ma + mnobia + fx + mc;
                                    mmutekitm = 5;
                                }
                                else
                                {
                                    axtype[t] = 1;
                                    amuki[t] = 0;
                                    aa[t] = ma - anobia[t] + fx - mc;
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
                if (atype[t] >= 100 && atype[t] <= 199)
                {

                    if (atype[t] == 100 && axtype[t] == 0)
                    {
                        mmsgtm = 30;
                        mmsgtype = 1;
                        PlaySound(Sounds[9]);
                    }
                    if (atype[t] == 100 && axtype[t] == 1)
                    {
                        mmsgtm = 30;
                        mmsgtype = 2;
                        PlaySound(Sounds[9]);
                    }
                    if (atype[t] == 100 && axtype[t] == 2)
                    {
                        mnobia = 5200;
                        mnobib = 7300;
                        PlaySound(Sounds[9]);
                        ma -= 1100;
                        mb -= 4000;
                        mtype = 1;
                        Health = 50000000;
                    }

                    if (atype[t] == 101)
                    {
                        Health -= 1;
                        mmsgtm = 30;
                        mmsgtype = 11;
                    }
                    if (atype[t] == 102)
                    {
                        Health -= 1;
                        mmsgtm = 30;
                        mmsgtype = 10;
                    }
                    //?ボール (? Ball)
                    if (atype[t] == 105)
                    {
                        if (axtype[t] == 0)
                        {
                            PlaySound(Sounds[4]);
                            sgtype[26] = 6;
                        }
                        if (axtype[t] == 1)
                        {
                            txtype[7] = 80;
                            PlaySound(Sounds[4]);

                            // CreateEntity(aa[t]-6*3000+1000,-3*3000,0,0,0,110,0);
                            CreateEntity(aa[t] -
                                             8 * 3000 -
                                             1000,
                                         -4 * 3000, 0, 0, 0, 110, 0);
                            CreateEntity(aa[t] -
                                             10 *
                                                 3000 +
                                             1000,
                                         -1 * 3000, 0, 0, 0, 110, 0);

                            CreateEntity(aa[t] +
                                             4 * 3000 +
                                             1000,
                                         -2 * 3000, 0, 0, 0, 110, 0);
                            CreateEntity(aa[t] +
                                             5 * 3000 -
                                             1000,
                                         -3 * 3000, 0, 0, 0, 110, 0);
                            CreateEntity(aa[t] +
                                             6 * 3000 +
                                             1000,
                                         -4 * 3000, 0, 0, 0, 110, 0);
                            CreateEntity(aa[t] +
                                             7 * 3000 -
                                             1000,
                                         -2 * 3000, 0, 0, 0, 110, 0);
                            CreateEntity(aa[t] +
                                             8 * 3000 +
                                             1000,
                                         -2 * 3000 - 1000, 0, 0, 0, 110, 0);
                            tb[0] += 3000 * 3;
                        }
                    } // 105

                    if (atype[t] == 110)
                    {
                        Health -= 1;
                        mmsgtm = 30;
                        mmsgtype = 3;
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
                    aa[t] = -90000000;
                }

            } //(ma
        }
        else
        {
            aa[t] = -9000000;
        }

    } // t
}

void PlaceEntities()
{
    // 敵キャラの配置 (Enemy character placement)
    for (t = 0; t < bmax; t++)
    {
        if (ba[t] >= -80000)
        {

            if (btm[t] >= 0)
            {
                btm[t] = btm[t] - 1;
            }

            for (tt = 0; tt <= 1; tt++)
            {
                int local_xx_0 = 0; // xx[0] = 0;
                int local_xx_1 = 0; // xx[1] = 0;

                if (bz[t] == 0 && btm[t] < 0 && ba[t] - fx >= fxmax + 2000 && ba[t] - fx < fxmax + 2000 + mc && tt == 0)
                {
                    local_xx_0 = 1;
                    amuki[aco] = 0;
                } // && mmuki==1
                if (bz[t] == 0 && btm[t] < 0 && ba[t] - fx >= -400 - anx[btype[t]] + mc && ba[t] - fx < -400 - anx[btype[t]] && tt == 1)
                {
                    local_xx_0 = 1;
                    local_xx_1 = 1;
                    amuki[aco] = 1;
                } // && mmuki==0
                if (bz[t] == 1 && ba[t] - fx >= 0 - anx[btype[t]] && ba[t] - fx <= fxmax + 4000 && bb[t] - fy >= -9000 && bb[t] - fy <= fymax + 4000 && btm[t] < 0)
                {
                    local_xx_0 = 1;
                    bz[t] = 0;
                } // && xza<=5000// && tyuukan!=1
                // if (bz[t]==2){local_xx_0=0;local_xx_1=0;}
                // if (btype[t]>=100){bz[t]=2;}

                if (local_xx_0 == 1)
                { // 400
                    btm[t] = 401;
                    local_xx_0 = 0; // if (btype[t]>=20 && btype[t]<=23){btm[t]=90000;}
                    if (btype[t] >= 10)
                    {
                        btm[t] = 9999999;
                    }
                    // 10
                    CreateEntity(ba[t], bb[t], 0, 0, 0, btype[t], bxtype[t]);
                }

            } // tt
        }
    } // t
}

void HandleLifts()
{
    // リフト (Lift)
    for (t = 0; t < srmax; t++)
    {
        xx[10] = sra[t];
        xx[11] = srb[t];
        xx[12] = src[t];
        xx[13] = srd[t];
        xx[8] = xx[10] - fx;
        xx[9] = xx[11] - fy;
        if (xx[8] + xx[12] >= -10 - 12000 && xx[8] <= fxmax + 12100)
        {
            xx[0] = 500;
            xx[1] = 1200;
            xx[2] = 1000;
            xx[7] = 2000;
            if (md >= 100)
            {
                xx[1] = 900 + md;
            }
            // if (srtype[t]==1){xx[0]=600;}
            if (md > xx[1])
                xx[1] = md + 100;
            // xx[18]=0;

            srb[t] += sre[t];
            sre[t] += srf[t];
            // if (srf[t]>=500)srf[t]=0;

            // 動き (Movement)
            switch (sracttype[t])
            {

            case 1:
                if (sron[t] == 1)
                    srf[t] = 60;
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
                if (srb[t] - fy < -2100)
                {
                    srb[t] = fymax + fy + scrolly + 2000;
                }
                if (srb[t] - fy > fymax + scrolly + 2000)
                {
                    srb[t] = -2100 + fy;
                }
                break;

            case 6:
                if (sron[t] == 1)
                    srf[t] = 40;
                break;

            case 7:
                break;

            } // sw

            // if (srtype[t]==1){sre[10]=300;sre[11]=300;}

            // 乗ったとき (When I got on)
            if (!(mztm >= 1 && mztype == 1 && actaon[3] == 1) && Health >= 1)
            {
                if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + xx[12] - xx[0] && mb + mnobib > xx[9] && mb + mnobib < xx[9] + xx[1] && md >= -100)
                {
                    mb = xx[9] - mnobib + 100;
                    // if (sracttype[t]!=7)PlayerGrounded=1;

                    if (srtype[t] == 1)
                    {
                        sre[10] = 900;
                        sre[11] = 900;
                    }

                    if (srsp[t] != 12)
                    {
                        PlayerGrounded = 1;
                        md = 0;
                    }
                    else
                    {
                        // すべり (Slip)
                        // md=0;GroundType=1;PlayerGrounded=1;
                        md = -800;
                    }

                    /*
                    md=0;
                    if ((sracttype[t]==1 || sracttype[t]==6) && sron[t]==1)mb+=sre[t];

                    if (sracttype[t]==2 || sracttype[t]==4){
                    if (srmuki[t]==0)ma-=srsok[t];
                    if (srmuki[t]==1)ma+=srsok[t];
                    }
                    */

                    // 落下
                    if ((sracttype[t] == 1) && sron[t] == 0)
                        sron[t] = 1;

                    if (sracttype[t] == 1 && sron[t] == 1 || sracttype[t] == 3 || sracttype[t] == 5)
                    {
                        mb += sre[t];
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
                            md = -600;
                            mb -= 810;
                        }
                        if (actaon[2] == 1)
                        {
                            mb -= 400;
                            md = -1400;
                            mjumptm = 10;
                        }
                    }
                    // 特殊 (Special)
                    if (srsp[t] == 1)
                    {
                        PlaySound(Sounds[3]);
                        eyobi(sra[t] + 200,
                              srb[t] - 1000,
                              -240, -1400, 0, 160, 4500, 4500, 2, 120);
                        eyobi(sra[t] + 4500 -
                                  200,
                              srb[t] - 1000,
                              240, -1400, 0, 160, 4500, 4500, 3, 120);
                        sra[t] = -70000000;
                    }

                    if (srsp[t] == 2)
                    {
                        mc = -2400;
                        srmove[t] += 1;
                        if (srmove[t] >= 100)
                        {
                            Health = 0;
                            mmsgtype = 53;
                            mmsgtm = 30;
                            srmove[t] = -5000;
                        }
                    }

                    if (srsp[t] == 3)
                    {
                        mc = 2400;
                        srmove[t] += 1;
                        if (srmove[t] >= 100)
                        {
                            Health = 0;
                            mmsgtype = 53;
                            mmsgtm = 30;
                            srmove[t] = -5000;
                        }
                    }
                    // if (srtype[t]==1){md=-600;mb-=610;Health-=1;if (mmutekion!=1)mmutekitm=40;}
                } // 判定内

                // 疲れ初期化
                if ((srsp[t] == 2 || srsp[t] == 3) && mc != -2400 && srmove[t] > 0)
                {
                    srmove[t]--;
                }

                if (srsp[t] == 11)
                {
                    if (ma + mnobia >
                            xx[8] + xx[0] - 2000 &&
                        ma < xx[8] + xx[12] - xx[0])
                    {
                        sron[t] = 1;
                    } // && mb+mnobib>xx[9]-1000 && mb+mnobib<xx[9]+xx[1]+2000)
                    if (sron[t] == 1)
                    {
                        srf[t] = 60;
                        srb[t] += sre[t];
                    }
                }
                // トゲ(下) (Spikes (below))
                if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + xx[12] - xx[0] && mb > xx[9] - xx[1] / 2 && mb < xx[9] + xx[1] / 2)
                {
                    if (srtype[t] == 2)
                    {
                        if (md < 0)
                        {
                            md = -md;
                        }
                        mb += 110;
                        if (mmutekitm <= 0)
                            Health -= 1;
                        if (mmutekion != 1)
                            mmutekitm = 40;
                    }
                }
                // 落下 (Falling)
                if (sracttype[t] == 6)
                {
                    if (ma + mnobia > xx[8] + xx[0] && ma < xx[8] + xx[12] - xx[0])
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
                    sra[t] -= srsok[t];
                if (srmuki[t] == 1)
                    sra[t] += srsok[t];
            }
            if (sracttype[t] == 3 || sracttype[t] == 5)
            {
                if (srmuki[t] == 0)
                    srb[t] -= srsok[t];
                if (srmuki[t] == 1)
                    srb[t] += srsok[t];
            }
            // 敵キャラ適用 (Applies to enemy characters)
            for (tt = 0; tt < amax; tt++)
            {
                if (azimentype[tt] == 1)
                {
                    if (aa[tt] + anobia[tt] - fx > xx[8] + xx[0] && aa[tt] - fx < xx[8] + xx[12] - xx[0] && ab[tt] + anobib[tt] > xx[11] - 100 && ab[tt] + anobib[tt] < xx[11] + xx[1] + 500 && ad[tt] >= -100)
                    {
                        ab[tt] = xx[9] - anobib[tt] + 100;
                        ad[tt] = 0;
                        axzimen[tt] = 1;
                    }
                }
            }
        }
    } // リフト (Lift)
}

// 敵キャラ、アイテム作成 (Enemy character and item creation)
void CreateEntity(
	int xa,
	int xb,
	int xc,
	int xd,
	int xnotm,
	int EntityType, //int xtype
	int xxtype
)
{
	int rz = 0;
	for (t1 = 0; t1 <= 1; t1++)
	{
		t1 = 2;
		if (aa[aco] >= -9000 && aa[aco] <= 30000)
			t1 = 0;
		rz++;

		if (rz <= amax)
		{
			t1 = 3;

			aa[aco] = xa;
			ab[aco] = xb; // ag[aco]=0;ah[aco]=0;ai[aco]=bb[t];//ad[t]=0;aeon[t]=1;
			ac[aco] = xc;
			ad[aco] = xd;
			if (xxtype > 100)
				ac[aco] = xxtype;
			// ae[aco]=0;af[aco]=0;
			atype[aco] = EntityType;
			if (xxtype >= 0 && xxtype <= 99100)
				axtype[aco] = xxtype; // ahp[aco]=iz[bxtype[t]];aytm[aco]=0;
			// if (xxtype==1)end();
			anotm[aco] = xnotm;
			if (aa[aco] - fx <= ma + mnobia / 2)
				amuki[aco] = 1;
			if (aa[aco] - fx > ma + mnobia / 2)
				amuki[aco] = 0;
			if (abrocktm[aco] >= 1)
				amuki[aco] = 1;
			if (abrocktm[aco] == 20)
				amuki[aco] = 0;

			anobia[aco] = anx[atype[aco]];
			anobib[aco] = any[atype[aco]];

			// 大砲音 (Cannon sound)
			if (EntityType == 7 && CheckSoundMem(Sounds[10]) == 0)
			{
				PlaySound(Sounds[10]);
			}
			// ファイア音 (Fire sound)
			if (EntityType == 10 && CheckSoundMem(Sounds[18]) == 0)
			{
				PlaySound(Sounds[18]);
			}

			azimentype[aco] = 1;

			// if (atype[aco]<=30 && atype[aco]!=4)atm[aco]=20;

			// azimentype[aco]=1;

			//+KZ removed empty switch

			if (EntityType == 87)
			{
				atm[aco] = rand(179) + (-90);
			}

			aco += 1;
			if (aco >= amax - 1)
			{
				aco = 0;
			}
		} // t1

		// if (bz[t]==1){bz[t]=0;}
	} // rz

} // ayobi
