#include "global_vars.h"
#include "main.h"
#include "title.h"
#include "levels.h"
#include "player.h"
#include "entities.h"
#include "extra_graphics.h"

static ESyobonActionGame prevGame = (ESyobonActionGame)-1;
static std::string author = "";

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
            if(!SA3Enabled)
                currentGame = ESyobonActionGame::SYOBON_ACTION_1_AND_2;
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
            if(!SA3Enabled)
                currentGame = ESyobonActionGame::SYOBON_ACTION_1_AND_2;
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
        InGameInitialized = 0;
        SyobonStateTimer = 0;
        Lives = 2;

        //fast = 0;
        //TrapDisplay = 0;
        CurrentPlayerCheckpoint = 0;
    }
}

void UpdateTitleScreen()
{
    //HandleTitleKeys() may have changed the state
    if(SyobonState != ESyobonState::TITLE)
        return;

    if(prevGame != currentGame)
    {
        switch (currentGame)
        {
        case ESyobonActionGame::SYOBON_ACTION_1_AND_2:
            author = "Originally by Chiku & Bluvel";
            break;
        
        case ESyobonActionGame::SYOBON_ACTION_3:
            author = "Originally by DakaArts";
            break;
        }

        prevGame = currentGame;

        InGameInitialized = 0;
    }

    if (InGameInitialized == 0)
    {
        InGameInitialized = 1;
        WarpZoneMessageState = 0;

        StageColor = ELevelType::OVERWORLD;
        PlayerX = 5600;
        PlayerY = 32000;
        PlayerLookingDirection = LOOKING_RIGHT;
        Health = 1;
        PlayerVelX = 0;
        PlayerVelY = 0;
        PlayerSizeX = 3000;
        PlayerSizeY = 3600;

        PlayerState = 0;

        fx = 0;
        fy = 0;
        fzx = 0;
        stageonoff = 0;

        StageClear();
        stage();
    }

    HandlePlayer();

    actaon[0] = 0;
    actaon[4] = 0;

    HandleLifts();

    HandleExtraGraphics();

    PlaceEntities();
    HandleEntities();
}

void RenderTitleScreen()
{
    int author_y = 30;
    if(currentGame == ESyobonActionGame::SYOBON_ACTION_1_AND_2)
    {
        //setcolor(160, 180, 250);
        //fillrect(0, 0, fxmax, fymax);

        //+KZ
        setcolor(0, 0, 0);
        str(PLUSKZ_EDITION_TEXT, 480 / 2 - (sizeof(PLUSKZ_EDITION_TEXT) * 9) / 2, 120);

        drawimage(Main_GFX[30], 240 - 380 / 2, 60);

        setcolor(0, 0, 0);
        str("Enterキーを押せ!!", 240 - 8 * 20 / 2, 250);
    }
    else if(currentGame == ESyobonActionGame::SYOBON_ACTION_3)
    {
        //setcolor(160, 180, 250);
        //fillrect(0, 0, fxmax, fymax);

        drawimage(Main_GFX_KZ[1], 240 - Main_GFX_KZ[1]->w / 2, 20);

        //+KZ
        setcolor(0, 0, 0);
        str(PLUSKZ_REMAKE_TEXT, 480 / 2 - (sizeof(PLUSKZ_REMAKE_TEXT) * 9) / 2, 120);

        author_y = 100;
    }

    setc0();
    str(author, 480 / 2 - (author.length() * 9) / 2, author_y);
}
