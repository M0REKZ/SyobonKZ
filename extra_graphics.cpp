
#include "global_vars.h"
#include "main.h"
#include "extra_graphics.h"

void HandleExtraGraphics()
{
    // グラ
    for (t = 0; t < emax; t++)
    {
        xx[0] = ea[t] - fx;
        xx[1] = eb[t] - fy;
        xx[2] = enobia[t] / 100;
        xx[3] = enobib[t] / 100;
        if (etm[t] >= 0)
            etm[t]--;
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax && xx[1] + xx[3] * 100 >= -10 - 8000 && xx[3] <= fymax && etm[t] >= 0)
        {
            ea[t] += ec[t];
            eb[t] += ed[t];
            ec[t] += ee[t];
            ed[t] += ef[t];
        }
        else
        {
            ea[t] = -9000000;
        }

    } // emax
}

void RenderExtraGraphics()
{
    // グラ //+KZ: Seems this is about non-entitty graphics
    for (t = 0; t < emax; t++)
    {
        xx[0] = ea[t] - fx;
        xx[1] = eb[t] - fy;
        xx[2] = enobia[t] / 100;
        xx[3] = enobib[t] / 100;
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax && xx[1] + xx[3] * 100 >= -10 - 8000 && xx[3] <= fymax)
        {

            // コイン (Coin)
            if (egtype[t] == 0)
                drawimage(Sliced_GFX[0][2], xx[0] / 100, xx[1] / 100);

            // ブロックの破片 (Block fragments)
            if (egtype[t] == 1)
            {
                if (stagecolor == 1 || stagecolor == 3 || stagecolor == 5)
                    setcolor(9 * 16, 6 * 16, 3 * 16);
                if (stagecolor == 2)
                    setcolor(0, 120, 160);
                if (stagecolor == 4)
                    setcolor(192, 192, 192);

                fillarc(xx[0] / 100, xx[1] / 100, 7, 7);
                setcolor(0, 0, 0);
                drawarc(xx[0] / 100, xx[1] / 100, 7, 7);
            }
            // リフトの破片 (Lift fragments)
            if (egtype[t] == 2 || egtype[t] == 3)
            {
                if (egtype[t] == 3)
                    mirror = 1;
                drawimage(Sliced_GFX[0][5], xx[0] / 100, xx[1] / 100);
                mirror = 0;
            }
            // ポール (pole)
            if (egtype[t] == 4)
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
        }
    }
}

void RenderBackground()
{
    // 背景 (Background)
    for (t = 0; t < nmax; t++)
    {
        xx[0] = na[t] - fx;
        xx[1] = nb[t] - fy;
        //+KZ: added some checks because this gets out of bounds in level 1-4
        //+KZ later: ....wait this code is useless, we set xx[2] and xx[3] just below this
        /*if (ntype[t] < nmax)
        {
            xx[2] = BackgroundWidth[ntype[t]] * 100;
            xx[3] = BackgroundHeight[ntype[t]] * 100;
        }*/
        xx[2] = 16000;
        xx[3] = 16000;

        if (xx[0] + xx[2] >= -10 && xx[0] <= fxmax && xx[1] + xx[3] >= -10 && xx[3] <= fymax)
        {

            if (ntype[t] != 3)
            {
                if ((ntype[t] == 1 || ntype[t] == 2) && stagecolor == 5)
                {
                    drawimage(Sliced_GFX[ntype[t] + 30] //+KZ: so.. this draws the broken grass in 3-1, did it even work correctly in any syobon action version?
                                        [4],
                              xx[0] / 100, xx[1] / 100);
                }
                else
                {
                    drawimage(Sliced_GFX[ntype[t]][4],
                              xx[0] / 100, xx[1] / 100);
                }
            }
            if (ntype[t] == 3)
                drawimage(Sliced_GFX[ntype[t]][4],
                          xx[0] / 100 - 5, xx[1] / 100);

            // 51
            if (ntype[t] == 100)
            {
                DrawFormatString(xx[0] / 100 + fmaZ,
                                 xx[1] / 100 + fmb,
                                 GetColor(255, 255, 255), "51");
            }

            if (ntype[t] == 101)
                DrawFormatString(xx[0] / 100 + fmaZ,
                                 xx[1] / 100 + fmb,
                                 GetColor(255, 255,
                                          255),
                                 "ゲームクリアー");
            if (ntype[t] == 102)
                DrawFormatString(xx[0] / 100 + fmaZ,
                                 xx[1] / 100 + fmb,
                                 GetColor(255, 255,
                                          255),
                                 "プレイしてくれてありがとー");
        }
    } // t
}
