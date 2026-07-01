#include "global_vars.h"
#include "main.h"

void HandleTitleKeys()
{
    SyobonStateTimer++;
    xx[0] = 0;
    if (SyobonStateTimer <= 10)
    {
        SyobonStateTimer = 11;
        SyobonWorld = 1;
        SyobonLevel = 1;
        SyobonSection = 0;
        SyobonRandomMode = 0;
    }

    switch (currentGame)
    {
    case ESyobonActionGame::SYOBON_ACTION_1_AND_2:
        if (CheckHitKey(KEY_INPUT_1) == 1)
        {
            SyobonWorld = 1;
            SyobonLevel = 1;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_2) == 1)
        {
            SyobonWorld = 1;
            SyobonLevel = 2;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_3) == 1)
        {
            SyobonWorld = 1;
            SyobonLevel = 3;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_4) == 1)
        {
            SyobonWorld = 1;
            SyobonLevel = 4;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_5) == 1)
        {
            SyobonWorld = 2;
            SyobonLevel = 1;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_6) == 1)
        {
            SyobonWorld = 2;
            SyobonLevel = 2;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_7) == 1)
        {
            SyobonWorld = 2;
            SyobonLevel = 3;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_8) == 1)
        {
            SyobonWorld = 2;
            SyobonLevel = 4;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_9) == 1)
        {
            SyobonWorld = 3;
            SyobonLevel = 1;
            SyobonSection = 0;
        }
        if (CheckHitKey(KEY_INPUT_0) == 1)
        {
            xx[0] = 1;
            SyobonRandomMode = 1;
        }
        break;
        
    case ESyobonActionGame::SYOBON_ACTION_3:
        break;

    }

    // if (CheckHitKeyAll() == 0){end();}
    if (CheckHitKey(KEY_INPUT_RETURN) == 1)
    {
        xx[0] = 1;
    }
    // if (CheckHitKey(KEY_INPUT_SPACE)==1){xx[0]=1;}
    if (CheckHitKey(KEY_INPUT_Z) == 1)
    {
        xx[0] = 1;
    }

    static bool change_game_key_pressed = false;
    if(CheckHitKey(KEY_INPUT_LEFT))
    {
        if(!change_game_key_pressed)
        {
            currentGame = (ESyobonActionGame)((int)currentGame - 1);
            if(currentGame < ESyobonActionGame::FIRST)
            {
                currentGame = ESyobonActionGame::LAST;
            }
            change_game_key_pressed = true;
        }
    }
    else if(CheckHitKey(KEY_INPUT_RIGHT))
    {
        if(!change_game_key_pressed)
        {
            currentGame = (ESyobonActionGame)((int)currentGame + 1);
            if(currentGame > ESyobonActionGame::LAST)
            {
                currentGame = ESyobonActionGame::FIRST;
            }
            change_game_key_pressed = true;
        }
    }
    else
    {
        change_game_key_pressed = false;
    }

    if (xx[0] == 1)
    {
        SyobonState = ESyobonState::LIVES_SPLASH;
        zxon = 0;
        SyobonStateTimer = 0;
        Lives = 2;

        fast = 0;
        //TrapDisplay = 0;
        CurrentPlayerCheckpoint = 0;
    }
}

void RenderTitleScreen()
{
    if(currentGame == ESyobonActionGame::SYOBON_ACTION_1_AND_2)
    {
        setcolor(160, 180, 250);
        fillrect(0, 0, fxmax, fymax);

        //+KZ
        setcolor(0, 0, 0);
        str(PLUSKZ_EDITION_TEXT, 480 / 2 - (sizeof(PLUSKZ_EDITION_TEXT) * 10) / 2, 120);

        drawimage(Main_GFX[30], 240 - 380 / 2, 60);

        drawimage(Sliced_GFX[0][4], 12 * 30, 10 * 29 - 12);
        drawimage(Sliced_GFX[1][4], 6 * 30, 12 * 29 - 12);

        // プレイヤー (Player)
        drawimage(Sliced_GFX[0][0], 2 * 30, 12 * 29 - 12 - 6);
        for (t = 0; t <= 16; t++)
        {
            drawimage(Sliced_GFX[5][1], 29 * t, 13 * 29 - 12);
            drawimage(Sliced_GFX[6][1], 29 * t, 14 * 29 - 12);
        }

        setcolor(0, 0, 0);
        str("Enterキーを押せ!!", 240 - 8 * 20 / 2, 250);
    }
    else if(currentGame == ESyobonActionGame::SYOBON_ACTION_3)
    {
        setcolor(160, 180, 250);
        fillrect(0, 0, fxmax, fymax);

        drawimage(Main_GFX_KZ[1], 240 - Main_GFX_KZ[1]->w / 2, 60);

        //+KZ
        setcolor(0, 0, 0);
        str(PLUSKZ_EDITION_TEXT, 480 / 2 - (sizeof(PLUSKZ_EDITION_TEXT) * 10) / 2, 120);

        //Player
        drawimage(Sliced_GFX[0][0], 2 * 30, 12 * 29 - 12 - 6);
        for (t = 0; t <= 16; t++)
        {
            drawimage(Sliced_GFX[5][1], 29 * t, 13 * 29 - 12);
            drawimage(Sliced_GFX[6][1], 29 * t, 14 * 29 - 12);
        }
    }
}
