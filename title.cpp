#include "global_vars.h"
#include "main.h"
#include "title.h"
#include "levels.h"
#include "player.h"
#include "entities.h"
#include "extra_graphics.h"
#include "pause.h"

static ESyobonActionGame prevGame = (ESyobonActionGame)-1;
static std::string author = "";

bool MustWaitReleaseKey = false;

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

    if(MustWaitReleaseKey)
    {
        if(CheckHitKey(KEY_INPUT_Z) || CheckHitKey(KEY_INPUT_RETURN))
            return;
        else
            MustWaitReleaseKey = false;
    }

    switch (currentGame)
    {
    case ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2:
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
            SyobonStartGame = true; //+KZ
        }
        break;
        
    default:
        break;

    }

    // if (CheckHitKeyAll() == 0){end();}
    if (CheckHitKey(KEY_INPUT_RETURN) == 1)
    {
        //xx[0] = 1; replaced by togglepausestate
        TogglePauseState(EPauseState::LEVEL_SELECT);
    }
    // if (CheckHitKey(KEY_INPUT_SPACE)==1){xx[0]=1;}
    if (CheckHitKey(KEY_INPUT_Z) == 1)
    {
        //xx[0] = 1; replaced by togglepausestate
        TogglePauseState(EPauseState::LEVEL_SELECT);
    }

    #define ISGAMEALLOWED(game) (   \
        (currentGame == ESyobonActionGame::SYOBON_ACTION_3 && SADevGamesEnabled) ||  \
        currentGame == ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2 ||   \
        (currentGame == ESyobonActionGame::SYOBON_ACTION_JAM && SADevGamesEnabled) ||  \
        currentGame == ESyobonActionGame::KAIZO_SYOBON ||   \
        (currentGame == ESyobonActionGame::SYOBONKZ_TRUE_ACTION && SADevGamesEnabled)  \
    )

    static bool change_game_key_pressed = false;
    if(CheckHitKey(KEY_INPUT_LEFT))
    {
        if(!change_game_key_pressed)
        {
            do
            {
                currentGame = (ESyobonActionGame)((int)currentGame - 1);
                if(currentGame < ESyobonActionGame::FIRST)
                {
                    currentGame = ESyobonActionGame::LAST;
                }
            } while(!ISGAMEALLOWED(currentGame));
            change_game_key_pressed = true;
        }
    }
    else if(CheckHitKey(KEY_INPUT_RIGHT))
    {
        if(!change_game_key_pressed)
        {
            do
            {
                currentGame = (ESyobonActionGame)((int)currentGame + 1);
                if(currentGame > ESyobonActionGame::LAST)
                {
                    currentGame = ESyobonActionGame::FIRST;
                }
            } while(!ISGAMEALLOWED(currentGame));
            change_game_key_pressed = true;
        }
    }
    else
    {
        change_game_key_pressed = false;
    }

    #undef ISGAMEALLOWED

    //+KZ: before it checked for xx[0], replaced with SyobonStartGame for new menu
    if (SyobonStartGame)
    {
        SyobonState = ESyobonGameState::LIVES_SPLASH;
        InGameInitialized = 0;
        SyobonStateTimer = 0;
        Lives = 2;

        //fast = 0;
        //TrapDisplay = 0;
        CurrentPlayerCheckpoint = 0;

        SyobonStartGame = false;
    }
}

void UpdateTitleScreen()
{
    //HandleTitleKeys() may have changed the state
    if(SyobonState != ESyobonGameState::TITLE)
        return;

    if(prevGame != currentGame)
    {
        switch (currentGame)
        {
        case ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2:
            author = "Originally by Chiku & Bluvel";
            break;
        
        case ESyobonActionGame::SYOBON_ACTION_3:
            author = "Originally by DakaArts";
            break;

        case ESyobonActionGame::KAIZO_SYOBON:
            author = "Originally by Zokalal";
            break;

        case ESyobonActionGame::SYOBON_ACTION_JAM:
            author = "StudsX";
            break;

        case ESyobonActionGame::SYOBONKZ_TRUE_ACTION:
            author = "By +KZ";
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

    PlaceEnemies();
    HandleEnemies();
}

void RenderTitleScreen()
{
    int author_y = 30;
    switch(currentGame)
    {
    case ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2:
        //+KZ
        setcolor(0, 0, 0);
        str(PLUSKZ_EDITION_TEXT, SYOBONKZ_SCREEN_SIZE_X / 2 - (sizeof(PLUSKZ_EDITION_TEXT) * 9) / 2, 120);

        drawimage(Main_GFX[30], 240 - 380 / 2, 60);

        setcolor(0, 0, 0);
        if(GetNowCount() % 5000 >= 2500)
        {
            SetFontSize(20);
            str("Prece Enter Key ",240 - 8 * 20 / 2, 250); //Chiku
            str("Prece Enter Key ",(240 - 8 * 20 / 2) + 1, 250); //+KZ: (me trying to make a fake thickness effect)
            //str("Prece Enter Key ",240 - 8 * 20 / 2, 250 - 1);
            //str("Prece Enter Key ",(240 - 8 * 20 / 2) - 1, 250 - 1);
            SetFontSize(16);
        }
        else
            str("Enterキーを押せ!!", 240 - 8 * 20 / 2, 250); //Bluvel

        setc0();
        str(author, SYOBONKZ_SCREEN_SIZE_X / 2 - (author.length() * 9) / 2, author_y);
        break;
    case ESyobonActionGame::SYOBON_ACTION_3:
        drawimage(Main_GFX_KZ[1], 240 - Main_GFX_KZ[1]->w / 2, 20);

        //+KZ
        setcolor(0, 0, 0);
        str(PLUSKZ_REMAKE_TEXT, SYOBONKZ_SCREEN_SIZE_X / 2 - (sizeof(PLUSKZ_REMAKE_TEXT) * 9) / 2, 120);

        author_y = 100;
        setc0();
        str(author, SYOBONKZ_SCREEN_SIZE_X / 2 - (author.length() * 9) / 2, author_y);
        break;
    case ESyobonActionGame::KAIZO_SYOBON:
        
        //+KZ
        setcolor(0, 0, 0);
        str(PLUSKZ_EDITION_TEXT, SYOBONKZ_SCREEN_SIZE_X / 2 - (sizeof(PLUSKZ_EDITION_TEXT) * 9) / 2, 120);

        drawimage(Main_GFX_KZ[12], 240 - Main_GFX_KZ[12]->w / 2, 20);

        setcolor(170, 0, 0);
        str("Prece Enter For Hell.", 240 - 8 * 20 / 2, 250);

        author_y = 100;
        setc0();
        str(author, SYOBONKZ_SCREEN_SIZE_X / 2 - (author.length() * 9) / 2, author_y);
        break;
    case ESyobonActionGame::SYOBON_ACTION_JAM:
    
        SyobonKZSetFontFile(1);

        SyobonKZDrawGraphScaled(240 - (Main_GFX_KZ[14]->w * 2) / 2, 100, 2, 2, Main_GFX_KZ[14]);

        setc1();
        str("Play Game", SYOBONKZ_SCREEN_SIZE_X / 2 - ((sizeof("Play Game")) * 9) / 2, 250);

        DrawGraphZ(SYOBONKZ_SCREEN_SIZE_X / 2 - ((sizeof("Play Game")) * 9) / 2 - (Sliced_GFX[1][2]->w * 1.5f), 240, Sliced_GFX[1][2]);

        author_y = 125;
        setcolor(231, 147, 31);
        str(author, SYOBONKZ_SCREEN_SIZE_X / 2 - (author.length() * 9) / 2, author_y);
        DrawString(SYOBONKZ_SCREEN_SIZE_X / 2 - (author.length() * 9) / 2, author_y + 15, "SMBJAM", color);
        DrawString(SYOBONKZ_SCREEN_SIZE_X / 2 - (author.length() * 9) / 2, author_y + 15 * 2, "2―0―2―1", color);
        //+KZ
        setcolor(0, 0, 0);
        str(PLUSKZ_REMAKE_TEXT, SYOBONKZ_SCREEN_SIZE_X / 2 - (sizeof(PLUSKZ_REMAKE_TEXT) * 9) / 2, author_y + 15 * 4);
        break;
    case ESyobonActionGame::SYOBONKZ_TRUE_ACTION:

        drawimage(Main_GFX_KZ[13], 240 - Main_GFX_KZ[13]->w / 2, 20);

        setcolor(170, 0, 0);
        if(PlayerState != 200)
            str("Press Enter to save Shobon!", 240 - 8 * 20 / 2, 250);
        else
            str("You're too slow... ._.", 240 - 8 * 20 / 2, 250);

        author_y = 130;
        setc0();
        str(author, SYOBONKZ_SCREEN_SIZE_X / 2 - (author.length() * 9) / 2, author_y);
        break;
    }

    SyobonKZSetFontFile(0);
}

void TitleWaitToReleaseKey()
{
    MustWaitReleaseKey = true;
}

void GoToTitleScreen()
{
    SyobonState = ESyobonGameState::TITLE;
    InGameInitialized = 0;
    SyobonKZHaltMusic();
}
