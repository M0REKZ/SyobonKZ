#include "global_vars.h"

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

    if (xx[0] == 1)
    {
        SyobonState = ESyobonState::LIVES_SPLASH;
        zxon = 0;
        SyobonStateTimer = 0;
        Lives = 2;

        fast = 0;
        TrapDisplay = 0;
        CurrentPlayerCheckpoint = 0;
    }
}
