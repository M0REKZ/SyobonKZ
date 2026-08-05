#include "levels.h"
#include <player.h>
#include <global_vars.h>
#include <blocks.h>

void HandleSyobonKZCredits()
{
    StageClear();

    scrollx = 0;

    PlayerX = SYOBONKZ_SCREEN_SIZE_X/2 * 100 - 3000;
    PlayerY = (12 * 29 - 12 - 6) * 100;

    for(int x_pos = 0; x_pos < 17; x_pos++)
    {
        BlockCreate(x_pos, 13, EBlockType::GROUND_TOP);
        BlockCreate(x_pos, 14, EBlockType::GROUND_BOTTOM);
    }
}
