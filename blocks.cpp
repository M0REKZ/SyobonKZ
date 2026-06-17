#include "main.h"
#include "global_vars.h"
#include "blocks.h"

void RenderBlocks()
{
    // ブロック描画 (Block drawing)
    for (t = 0; t < tmax; t++)
    {
        xx[0] = ta[t] - fx;
        xx[1] = tb[t] - fy;
        xx[2] = 32;
        xx[3] = xx[2];
        if (xx[0] + xx[2] * 100 >= -10 && xx[1] <= fxmax)
        {

            xx[9] = 0;
            if (stagecolor == 2)
            {
                xx[9] = 30;
            }
            if (stagecolor == 4)
            {
                xx[9] = 60;
            }
            if (stagecolor == 5)
            {
                xx[9] = 90;
            }

            if (ttype[t] < 100)
            {
                xx[6] = ttype[t] + xx[9];
                drawimage(Sliced_GFX[xx[6]][1], xx[0] / 100, xx[1] / 100);
            }

            if (txtype[t] != 10)
            {

                if (ttype[t] == 100 || ttype[t] == 101 || ttype[t] == 102 || ttype[t] == 103 || ttype[t] == 104 && txtype[t] == 1 || ttype[t] == 114 && txtype[t] == 1 || ttype[t] == 116)
                {
                    xx[6] = 2 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }

                if (ttype[t] == 112 || ttype[t] == 104 && txtype[t] == 0 || ttype[t] == 115 && txtype[t] == 1)
                {
                    xx[6] = 1 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }

                if (ttype[t] == 111 || ttype[t] == 113 || ttype[t] == 115 && txtype[t] == 0 || ttype[t] == 124)
                {
                    xx[6] = 3 + xx[9];
                    drawimage(Sliced_GFX[xx[6]][1],
                              xx[0] / 100, xx[1] / 100);
                }
            }

            if (ttype[t] == 117 && txtype[t] == 1)
            {
                drawimage(Sliced_GFX[4][5], xx[0] / 100, xx[1] / 100);
            }

            if (ttype[t] == 117 && txtype[t] >= 3)
            {
                drawimage(Sliced_GFX[3][5], xx[0] / 100, xx[1] / 100);
            }

            if (ttype[t] == 115 && txtype[t] == 3)
            {
                xx[6] = 1 + xx[9];
                drawimage(Sliced_GFX[xx[6]][1], xx[0] / 100, xx[1] / 100);
            }
            // ジャンプ台
            if (ttype[t] == 120 && txtype[t] != 1)
            {
                drawimage(Sliced_GFX[16][1], xx[0] / 100 + 3,
                          xx[1] / 100 + 2);
            }
            // ON-OFF
            if (ttype[t] == 130)
                drawimage(Sliced_GFX[10][5], xx[0] / 100, xx[1] / 100);
            if (ttype[t] == 131)
                drawimage(Sliced_GFX[11][5], xx[0] / 100, xx[1] / 100);

            if (ttype[t] == 140)
                drawimage(Sliced_GFX[12][5], xx[0] / 100, xx[1] / 100);
            if (ttype[t] == 141)
                drawimage(Sliced_GFX[13][5], xx[0] / 100, xx[1] / 100);
            if (ttype[t] == 142)
                drawimage(Sliced_GFX[14][5], xx[0] / 100, xx[1] / 100);

            if (ttype[t] == 300 || ttype[t] == 301)
                drawimage(Sliced_GFX[1][5], xx[0] / 100, xx[1] / 100);

            // Pスイッチ (P switch)
            if (ttype[t] == 400)
            {
                drawimage(Sliced_GFX[2][5], xx[0] / 100, xx[1] / 100);
            }
            // コイン (Coin)
            if (ttype[t] == 800)
            {
                drawimage(Sliced_GFX[0][2], xx[0] / 100 + 2,
                          xx[1] / 100 + 1);
            }
        }
    }
}

void RenderWalls()
{
    // 地面(壁)//土管も (Ground (walls) // Also pipes)
    for (t = 0; t < smax; t++)
    {
        if (sa[t] - fx + sc[t] >= -10 && sa[t] - fx <= fxmax + 1100)
        {

            if (stype[t] == 0)
            {
                setcolor(40, 200, 40);
                fillrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb,
                         sc[t] / 100, sd[t] / 100);
                drawrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb,
                         sc[t] / 100, sd[t] / 100);
            }
            // 土管
            if (stype[t] == 1)
            {
                setcolor(0, 230, 0);
                fillrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb,
                         sc[t] / 100, sd[t] / 100);
                setc0();
                drawrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb,
                         sc[t] / 100, sd[t] / 100);
            }
            // 土管(下)
            if (stype[t] == 2)
            {
                setcolor(0, 230, 0);
                fillrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb + 1,
                         sc[t] / 100, sd[t] / 100);
                setc0();
                drawline((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb,
                         (sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb + sd[t] / 100);
                drawline((sa[t] - fx) / 100 + fmaZ +
                             sc[t] / 100,
                         (sb[t] - fy) / 100 + fmb,
                         (sa[t] - fx) / 100 + fmaZ +
                             sc[t] / 100,
                         (sb[t] - fy) / 100 + fmb + sd[t] / 100);
            }
            // 土管(横)
            if (stype[t] == 5)
            {
                setcolor(0, 230, 0);
                fillrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb + 1,
                         sc[t] / 100, sd[t] / 100);
                setc0();
                drawline((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb,
                         (sa[t] - fx) / 100 + fmaZ +
                             sc[t] / 100,
                         (sb[t] - fy) / 100 + fmb);
                drawline((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb +
                             sd[t] / 100,
                         (sa[t] - fx) / 100 + fmaZ +
                             sc[t] / 100,
                         (sb[t] - fy) / 100 + fmb + sd[t] / 100);
            }
            // 落ちてくるブロック (Falling blocks)
            if (stype[t] == 51)
            {
                if (sxtype[t] == 0)
                {
                    for (t3 = 0; t3 <= sc[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[1][1],
                                  (sa[t] -
                                   fx) / 100 +
                                      fmaZ + 29 * t3,
                                  (sb[t] - fy) / 100 + fmb);
                    }
                }
                if (sxtype[t] == 1 || sxtype[t] == 2)
                {
                    for (t3 = 0; t3 <= sc[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[31][1],
                                  (sa[t] -
                                   fx) / 100 +
                                      fmaZ + 29 * t3,
                                  (sb[t] - fy) / 100 + fmb);
                    }
                }
                if (sxtype[t] == 3 || sxtype[t] == 4)
                {
                    for (t3 = 0; t3 <= sc[t] / 3000; t3++)
                    {
                        for (t2 = 0; t2 <= sd[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[65]
                                                [1],
                                      (sa[t] -
                                       fx) /
                                              100 +
                                          fmaZ + 29 * t3,
                                      (sb[t] -
                                       fy) /
                                              100 +
                                          29 * t2 + fmb);
                        }
                    }
                }

                if (sxtype[t] == 10)
                {
                    for (t3 = 0; t3 <= sc[t] / 3000; t3++)
                    {
                        drawimage(Sliced_GFX[65][1],
                                  (sa[t] -
                                   fx) / 100 +
                                      fmaZ + 29 * t3,
                                  (sb[t] - fy) / 100 + fmb);
                    }
                }

            } // 51

            // 落ちるやつ (The one that falls)
            if (stype[t] == 52)
            {
                xx[29] = 0;
                if (stagecolor == 2)
                {
                    xx[29] = 30;
                }
                if (stagecolor == 4)
                {
                    xx[29] = 60;
                }
                if (stagecolor == 5)
                {
                    xx[29] = 90;
                }

                for (t3 = 0; t3 <= sc[t] / 3000; t3++)
                {
                    if (sxtype[t] == 0)
                    {
                        drawimage(Sliced_GFX[5 + xx[29]][1],
                                  (sa[t] -
                                   fx) / 100 +
                                      fmaZ + 29 * t3,
                                  (sb[t] - fy) / 100 + fmb);
                        if (stagecolor != 4)
                        {
                            drawimage(Sliced_GFX[6 + xx[29]]
                                                [1],
                                      (sa[t] -
                                       fx) /
                                              100 +
                                          fmaZ + 29 * t3,
                                      (sb[t] -
                                       fy) /
                                              100 +
                                          fmb + 29);
                        }
                        else
                        {
                            drawimage(Sliced_GFX[5 + xx[29]]
                                                [1],
                                      (sa[t] -
                                       fx) /
                                              100 +
                                          fmaZ + 29 * t3,
                                      (sb[t] -
                                       fy) /
                                              100 +
                                          fmb + 29);
                        }
                    }
                    if (sxtype[t] == 1)
                    {
                        for (t2 = 0; t2 <= sd[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[1 + xx[29]]
                                                [1],
                                      (sa[t] -
                                       fx) /
                                              100 +
                                          fmaZ + 29 * t3,
                                      (sb[t] -
                                       fy) /
                                              100 +
                                          fmb + 29 * t2);
                        }
                    }

                    if (sxtype[t] == 2)
                    {
                        for (t2 = 0; t2 <= sd[t] / 3000; t2++)
                        {
                            drawimage(Sliced_GFX[5 + xx[29]]
                                                [1],
                                      (sa[t] -
                                       fx) /
                                              100 +
                                          fmaZ + 29 * t3,
                                      (sb[t] -
                                       fy) /
                                              100 +
                                          fmb + 29 * t2);
                        }
                    }
                }
            }
            // ステージトラップ (Stage Trap)
            if (trap == 1)
            {
                if (stype[t] >= 100 && stype[t] <= 299)
                {
                    if (stagecolor == 1 || stagecolor == 3 || stagecolor == 5)
                        setc0();
                    if (stagecolor == 2 || stagecolor == 4)
                        setc1();
                    drawrect((sa[t] - fx) / 100 +
                                 fmaZ,
                             (sb[t] - fy) / 100 +
                                 fmb,
                             sc[t] / 100, sd[t] / 100);
                }
            }
            // ゴール (Goal)
            if (stype[t] == 300)
            {
                setc1();
                fillrect((sa[t] - fx) / 100 + 10,
                         (sb[t] - fy) / 100, 10, sd[t] / 100 - 8);
                setc0();
                drawrect((sa[t] - fx) / 100 + 10,
                         (sb[t] - fy) / 100, 10, sd[t] / 100 - 8);
                setcolor(250, 250, 0);
                fillarc((sa[t] - fx) / 100 + 15 - 1,
                        (sb[t] - fy) / 100, 10, 10);
                setc0();
                drawarc((sa[t] - fx) / 100 + 15 - 1,
                        (sb[t] - fy) / 100, 10, 10);
            }
            // 中間
            if (stype[t] == 500)
            {
                drawimage(Sliced_GFX[20][4],
                          (sa[t] - fx) / 100, (sb[t] - fy) / 100);
            }
        }
    } // t
}

void RenderOverwritePipe()
{
    // 描画上書き(土管) (Overwrite drawing (pipe)) //+KZ: ??
    for (t = 0; t < smax; t++)
    {
        if (sa[t] - fx + sc[t] >= -10 && sa[t] - fx <= fxmax + 1100)
        {

            // 入る土管(右)
            if (stype[t] == 40)
            {
                setcolor(0, 230, 0);
                fillrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb + 1,
                         sc[t] / 100, sd[t] / 100);
                setc0();
                drawrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb + 1,
                         sc[t] / 100, sd[t] / 100);
            }
            // とぶ土管
            if (stype[t] == 50)
            {
                setcolor(0, 230, 0);
                fillrect((sa[t] - fx) / 100 + fmaZ + 5,
                         (sb[t] - fy) / 100 + fmb + 30,
                         50, sd[t] / 100 - 30);
                setc0();
                drawline((sa[t] - fx) / 100 + 5 + fmaZ,
                         (sb[t] - fy) / 100 + fmb + 30,
                         (sa[t] - fx) / 100 + fmaZ + 5,
                         (sb[t] - fy) / 100 + fmb + sd[t] / 100);
                drawline((sa[t] - fx) / 100 + 5 + fmaZ +
                             50,
                         (sb[t] - fy) / 100 + fmb + 30,
                         (sa[t] - fx) / 100 + fmaZ + 50 +
                             5,
                         (sb[t] - fy) / 100 + fmb + sd[t] / 100);

                setcolor(0, 230, 0);
                fillrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb + 1, 60, 30);
                setc0();
                drawrect((sa[t] - fx) / 100 + fmaZ,
                         (sb[t] - fy) / 100 + fmb + 1, 60, 30);
            }
            // 地面(ブロック)
            if (stype[t] == 200)
            {
                for (t3 = 0; t3 <= sc[t] / 3000; t3++)
                {
                    for (t2 = 0; t2 <= sd[t] / 3000; t2++)
                    {
                        drawimage(Sliced_GFX[65][1],
                                  (sa[t] -
                                   fx) / 100 +
                                      fmaZ + 29 * t3,
                                  (sb[t] - fy) / 100 + 29 * t2 + fmb);
                    }
                }
            }
        }
    } // t
}
