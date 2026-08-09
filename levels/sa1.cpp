#include <global_vars.h>
#include <blocks.h>
#include <main.h>
#include <entities.h>
#include <effects.h>
#include <loadg.h>
#include <backgrounds.h>
#include <objects.h>
#include <lifts.h>
#include <player.h>

#include "levels.h"

void HandleSyobonActionOneLevels()
{
    if(SyobonState == ESyobonGameState::TITLE)
    {
        scrollx = 0;

        PlayerX = (2 * 30) * 100;
        PlayerY = (12 * 29 - 12 - 6) * 100;

        for(int grounds = 0; grounds < 20; grounds++)
        {
            BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
            BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
        }

        CreateBackground(GAME_X_POS_TO_DOUBLE(6 * 30 * 100), 12, EBackgroundType::GRASS);
        CreateBackground(GAME_X_POS_TO_DOUBLE(12 * 30 * 100), 10, EBackgroundType::HILL);

        return;
    }
    // 1-1
    if (SyobonWorld == 1 && SyobonLevel == 1 && SyobonSection == 0)
    {
        bgmchange(Music[1]);
        // new byte LegacyStageDate[16][801]={

        //                                                                                                                                                                                     中間
        ELegacyStageDate stagedatex[17][1001] = {
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             CLOUD, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, CLOUD,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             STAGEDATE_98, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GOAL_POLE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, CLOUD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, JIEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, STAGEDATE_98, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, STAGEDATE_98, STAGEDATE_98, STAGEDATE_98,BRICK,BRICK, NONE, NONE, NONE,BRICK,BRICK,BRICK, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE,ITEM_BLOCK_COIN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, STAGEDATE_98, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE,HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,ITEM_BLOCK_HIDDEN,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, JIEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
            CHECKPOINT, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, STAGEDATE_98, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, STAGEDATE_98, NONE, NONE, NONE,BRICK, STAGEDATE_98,BRICK,ITEM_BLOCK_COIN,BRICK, NONE,
             NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
            ITEM_BLOCK_HIDDEN, NONE, NONE,
             NONE, NONE,
             NONE,BRICK, STAGEDATE_98,BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, STAGEDATE_98, NONE, NONE, NONE,
             NONE, NONE,
             NONE,BRICK,
             STAGEDATE_98, NONE, NONE, NONE,ITEM_BLOCK_COIN, NONE, NONE,ITEM_BLOCK_COIN, NONE, NONE,ITEM_BLOCK_COIN, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,BRICK,BRICK,ITEM_BLOCK_COIN,BRICK, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE},
            {NONE, HILL, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
             NONE, NONE,
            VERTICAL_PIPE_HEAD, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HILL, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,HARD_BLOCK, NONE,
             NONE, NONE,HARD_BLOCK,
             NONE,ITEM_BLOCK_HIDDEN,
            ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,VERTICAL_PIPE_HEAD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, CASTLE, NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
            VERTICAL_PIPE_BODY, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,HARD_BLOCK,HARD_BLOCK, NONE, NONE,
             NONE,HARD_BLOCK,HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE,VERTICAL_PIPE_BODY, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,VERTICAL_PIPE_HEAD, NONE, NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, JIEN, NONE, NONE, NONE, NONE, NONE, JIEN, NONE,
             NONE,GRASS,
            VERTICAL_PIPE_BODY, NONE,
             NONE, NONE, NONE, NONE,GRASS, STAGEDATE_98, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE,
             NONE, NONE,GRASS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, JIEN,
             NONE, JIEN,
             NONE, NONE,
             SHELL_JIEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,GRASS, NONE, NONE, NONE,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK, NONE,
             NONE, NONE,
            HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,VERTICAL_PIPE_BODY, NONE, NONE, NONE, NONE, NONE, JIEN, NONE, JIEN, NONE,
             NONE,VERTICAL_PIPE_BODY,
             NONE,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,HARD_BLOCK,GRASS, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE},
            {GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP, NONE,
             NONE, NONE,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP, NONE, NONE, NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP, NONE, NONE, NONE, NONE, NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP, NONE, NONE,
             NONE,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP, NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP, NONE,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP},
            {GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM, NONE,
             NONE, NONE,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM, NONE, NONE, NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM, NONE, NONE,
             NONE,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM, NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM, NONE,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}};

        // 追加情報
        BlockCreateLegacy(8 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_DODGE);
        //BlockSubType[BlockCount] = 2; //+KZ: In Syobon Action by Chiku this block gives a useless mushroom
        BlockCreateLegacy(13 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_MUSHROOM);
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_JIEN_NORMAL;
        BlockCreateLegacy(14 * 29, 5 * 29 - 12, EBlockType::ITEM_BLOCK_ENEMY);
        BlockCreateLegacy(35 * 29, 8 * 29 - 12, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(47 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_MUSHROOM_2);
        BlockCreateLegacy(59 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_COINS);
        BlockCreateLegacy(67 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_STAR);

        ObjectCount = 0;
        t = ObjectCount;
        ObjectX[t] = 20 * 29 * 100 + 500;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 5000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_ARAMAKI_UP;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 54 * 29 * 100 - 500;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 7000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_ARAMAKI_DOWN;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 112 * 29 * 100 + 1000;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 3000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 117 * 29 * 100;
        ObjectY[t] = (2 * 29 - 12) * 100 - 1500;
        ObjectSizeX[t] = 15000;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::TRIGGER_LASER;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 125 * 29 * 100;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 9000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_ARAMAKI_DOWN;
        ObjectCount++;
        // t=sco;sa[t]=77*29*100;sb[t]=(6*29-12)*100-1500;sc[t]=12000;sd[t]=3000;stype[t]=103;sco++;
        t = 28;
        ObjectX[t] = 29 * 29 * 100 + 500;
        ObjectY[t] = (9 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 12000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 49 * 29 * 100;
        ObjectY[t] = (5 * 29 - 12) * 100;
        ObjectSizeX[t] = 9000 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_BLOCKS;
        ObjectAI[t] = 0;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 72 * 29 * 100;
        ObjectY[t] = (13 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000 * 5 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_FLOOR;
        ObjectCount++;

        EnemyAppearCount = 0;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 27 * 29 * 100;
        EnemyAppearY[t] = (9 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::JIEN;
        EnemyAppearSubType[t] = EEnemySubType::JIEN_UNSTOMPABLE; //+KZ: In Syobon Action by Chiku you can not stomp this enemy
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 103 * 29 * 100;
        EnemyAppearY[t] = (5 * 29 - 12 + 10) * 100;
        EnemyAppearType[t] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[t] = EEnemySubType::EVIL_CLOUD_NORMAL;
        EnemyAppearCount++;
        // t=bco;ba[t]=13*29*100;bb[t]=(5*29-12)*100;btype[t]=81;bxtype[t]=0;bco++;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                LegacyStageDate[t][tt] = ELegacyStageDate::NONE;
                LegacyStageDate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta1

    // 1-2(地上)
    if (SyobonWorld == 1 && SyobonLevel == 2 && SyobonSection == 0)
    {

        // マリ　地上　入れ
        // Mix_HaltMusic();
        bgmchange(Music[1]);
        // PlaySoundMem(oto[0],DX_PLAYTYPE_LOOP) ;

        scrollx = 0 * 100;
        // ma=3000;mb=3000;

        ELegacyStageDate stagedatex[17][1001] = {
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, ITEM_BLOCK_HIDDEN,NONE,NONE,NONE,NONE, ITEM_BLOCK_HIDDEN},
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
                CASTLE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
                HORIZONTAL_PIPE_BODY,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,
            NONE,NONE,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,
            NONE,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,NONE,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP},
            {GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,
            NONE,NONE,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,
            NONE,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,NONE,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE}};

        BlockCount = 0;
        // ヒント1
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_1_2_0;
        BlockCreateLegacy(4 * 29, 9 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        // BlockCreate(7*29,9*29-12,300);

        // 毒1
        BlockCreateLegacy(13 * 29, 8 * 29 - 12, EBlockType::ITEM_BLOCK_TRAP_HIDDEN);

        // t=28;
        ObjectCount = 0;
        t = ObjectCount;
        ObjectX[t] = 14 * 29 * 100 + 500;
        ObjectY[t] = (9 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 12000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 12 * 29 * 100;
        ObjectY[t] = (11 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000;
        ObjectSizeY[t] = 6000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_KILL_PLAYER_CANNON;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 14 * 29 * 100 + 1000;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 5000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_ARAMAKI_UP;
        ObjectSubType[t] = EObjectSubType::TRIGGER_ARAMAKI_UP_LEVEL_1_2;
        ObjectCount++;

        // ブロックもどき
        // t=bco;ba[t]=7*29*100;bb[t]=(9*29-12)*100;btype[t]=82;bxtype[t]=0;bco++;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                LegacyStageDate[t][tt] = NONE;
                LegacyStageDate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta2

    // 1-2-1(地下)
    if (SyobonWorld == 1 && SyobonLevel == 2 && SyobonSection == 1)
    {

        // マリ　地下　入れ
        bgmchange(Music[2]);

        scrollx = 4080 * 100;
        PlayerX = 6000;
        PlayerY = 3000;
        LevelType = ELevelType::UNDERGROUND;

        ELegacyStageDate stagedatex[17][1001] = {
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, STAGEDATE_97,NONE,NONE,NONE,NONE,NONE,NONE},
            {BRICK,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,NONE,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,BRICK,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,BRICK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK, STAGEDATE_98,NONE,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,BRICK,NONE,NONE,
            NONE,BRICK,NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,BRICK,NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,BRICK,NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,BRICK,NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,ITEM_BLOCK_HIDDEN,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, ITEM_BLOCK_COIN,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,BRICK,NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,BRICK,NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, STAGEDATE_97, HORIZONTAL_PIPE_BODY,NONE,NONE,
            BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,BRICK,
            NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,ITEM_BLOCK_HIDDEN,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,SUPER_JIEN,NONE,BRICK,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, STAGEDATE_97,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,NONE,NONE,NONE,NONE,NONE,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,BRICK,NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE, STAGEDATE_98, ITEM_BLOCK_COIN, ITEM_BLOCK_COIN, STAGEDATE_98,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,
            HARD_BLOCK,ITEM_BLOCK_HIDDEN,
            ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE, STAGEDATE_98,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
            BRICK,BRICK,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,BRICK,
            NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,HARD_BLOCK,
            NONE,NONE,
            NONE,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE, SHELL_JIEN,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,ITEM_BLOCK_HIDDEN,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,BRICK,
            BRICK,BRICK,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,BRICK,NONE},
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            HARD_BLOCK,NONE,HARD_BLOCK,
            NONE,NONE,
            NONE,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,VERTICAL_PIPE_HEAD,NONE,NONE,NONE,NONE,NONE,NONE, CHECKPOINT,NONE,NONE,
            NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
            BRICK,BRICK,BRICK,
            BRICK,NONE,
            NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,BRICK,
            NONE},
            {BRICK,NONE, ITEM_BLOCK_HIDDEN,NONE,NONE,NONE,NONE,NONE,NONE,NONE, JIEN,NONE, JIEN,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,
            HARD_BLOCK,NONE,
            HARD_BLOCK,NONE,
             JIEN,NONE,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE, JIEN, JIEN, JIEN,
             ITEM_BLOCK_HIDDEN,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, VERTICAL_PIPE_BODY,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,
            BRICK,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            BRICK,NONE},
            {GROUND_TOP,GROUND_TOP,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,NONE,
            NONE,NONE,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,
            NONE,NONE,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,NONE},
            {GROUND_BOTTOM,GROUND_BOTTOM,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,NONE,
            NONE,NONE,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,
            NONE,NONE,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,BRICK,
            BRICK,BRICK,BRICK,
            BRICK,BRICK,
            BRICK,BRICK,BRICK,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,NONE,
            NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
        };
        //{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}

        BlockCount = 0;
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_MUSHROOM_GROW;
        BlockCreateLegacy(7 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_MUSHROOM);
        BlockCreateLegacy(10 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_ENEMY);

        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_BRITTLE;
        BlockCreateLegacy(49 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_TRAP_HIDDEN);

        for (t = 0; t >= -7; t--)
        {
            BlockCreateLegacy(53 * 29, t * 29 - 12, EBlockType::BRICK);
        }

        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_STAR_NORMAL;
        BlockCreateLegacy(80 * 29, 5 * 29 - 12, EBlockType::ITEM_BLOCK_STAR);
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_MUSHROOM_GROW;
        BlockCreateLegacy(78 * 29, 5 * 29 - 12, EBlockType::ITEM_BLOCK_MUSHROOM);

        // txtype[tco]=1;BlockCreate(11*29,9*29-12,114);//毒1

        ObjectCount = 0;
        t = ObjectCount;
        ObjectX[t] = 2 * 29 * 100;
        ObjectY[t] = (13 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000 * 1 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_FLOOR;
        ObjectCount++;
        // t=sco;sa[t]=19*29*100;sb[t]=(13*29-12)*100;sc[t]=3000*1-1;sd[t]=3000;stype[t]=52;sco++;
        t = ObjectCount;
        ObjectX[t] = 24 * 29 * 100;
        ObjectY[t] = (13 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000 * 1 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_FLOOR;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 43 * 29 * 100 + 500;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 3000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SUPER_JIEN_JUMP;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 53 * 29 * 100 + 500;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 3000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_FIRST_KUMA;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 129 * 29 * 100;
        ObjectY[t] = (7 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000;
        ObjectSizeY[t] = 6000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 154 * 29 * 100;
        ObjectY[t] = 3000;
        ObjectSizeX[t] = 9000;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_WARP_ZONE;
        ObjectCount++;

        // ブロックもどき

        t = 27;
        ObjectX[t] = 69 * 29 * 100;
        ObjectY[t] = (1 * 29 - 12) * 100;
        ObjectSizeX[t] = 9000 * 2 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_BLOCKS;
        ObjectSubType[t] = EObjectSubType::FALLING_BLOCKS_OVERWORLD_BRICK;
        ObjectAI[t] = 0;
        ObjectCount++;
        t = 28;
        ObjectX[t] = 66 * 29 * 100;
        ObjectY[t] = (1 * 29 - 12) * 100;
        ObjectSizeX[t] = 9000 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_BLOCKS;
        ObjectSubType[t] = EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK;
        ObjectAI[t] = 0;
        ObjectCount++;
        t = 29;
        ObjectX[t] = 66 * 29 * 100;
        ObjectY[t] = (-2 * 29 - 12) * 100;
        ObjectSizeX[t] = 9000 * 3 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_BLOCKS;
        ObjectSubType[t] = EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK_LEVEL_1_2;
        ObjectAI[t] = 0;
        ObjectCount++;

        // 26 ファイアー土管
        t = 26;
        ObjectX[t] = 103 * 29 * 100 - 1500;
        ObjectY[t] = (9 * 29 - 12) * 100 - 2000;
        ObjectSizeX[t] = 3000;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::LAVA_SPAWNER;
        ObjectSubType[t] = EObjectSubType::NONE;
        ObjectVelY[t] = 0;
        ObjectAI[t] = 48;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 102 * 29 * 100;
        ObjectY[t] = (9 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 12000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_LAVA;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 123 * 29 * 100;
        ObjectY[t] = (9 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000 * 5 - 1;
        ObjectSizeY[t] = 3000 * 5;
        ObjectType[t] = EObjectType::FALLING_FLOOR;
        ObjectSubType[t] = EObjectSubType::FALLING_FLOOR_BRICK;
        ObjectCount++;

        t = ObjectCount;
        ObjectX[t] = 131 * 29 * 100;
        ObjectY[t] = (1 * 29 - 12) * 100;
        ObjectSizeX[t] = 4700;
        ObjectSizeY[t] = 3000 * 8 - 700;
        ObjectType[t] = EObjectType::BLACK_OUTLINE_PIPE_PART;
        ObjectSubType[t] = EObjectSubType::NONE;
        ObjectCount++;

        // t=sco;sa[t]=44*29*100;sb[t]=-6000;sc[t]=9000;sd[t]=70000;stype[t]=102;sco++;

        // オワタゾーン
        t = ObjectCount;
        ObjectX[t] = 143 * 29 * 100;
        ObjectY[t] = (9 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 12000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_WARP_ZONE;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 148 * 29 * 100;
        ObjectY[t] = (9 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 12000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_WARP_ZONE;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 153 * 29 * 100;
        ObjectY[t] = (9 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 12000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_WARP_ZONE;
        ObjectCount++;

        EnemyAppearCount = 0;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 18 * 29 * 100;
        EnemyAppearY[t] = (10 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[t] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount++;
        // t=bco;ba[t]=52*29*100;bb[t]=(2*29-12)*100;btype[t]=82;bxtype[t]=1;bco++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 51 * 29 * 100 + 1000;
        EnemyAppearY[t] = (2 * 29 - 12 + 10) * 100;
        EnemyAppearType[t] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[t] = EEnemySubType::EVIL_CLOUD_HIDDEN;
        EnemyAppearCount++;

        // ？ボール
        t = EnemyAppearCount;
        EnemyAppearX[t] = 96 * 29 * 100 + 100;
        EnemyAppearY[t] = (10 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::MYSTERY_BALL;
        EnemyAppearSubType[t] = EEnemySubType::MYSTERY_BALL_LEVEL_1_2;
        EnemyAppearCount++;

        // リフト
        LiftCount = 0;
        t = LiftCount;
        LiftX[t] = 111 * 29 * 100;
        LiftY[t] = (8 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 5;
        LiftVelY[t] = -300;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 111 * 29 * 100;
        LiftY[t] = (0 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 5;
        LiftVelY[t] = -300;
        LiftCount++;
        t = 10;
        LiftX[t] = 116 * 29 * 100;
        LiftY[t] = (4 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 1;
        LiftMovementType[t] = 5;
        LiftVelY[t] = 300;
        LiftCount++;
        t = 11;
        LiftX[t] = 116 * 29 * 100;
        LiftY[t] = (12 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 1;
        LiftMovementType[t] = 5;
        LiftVelY[t] = 300;
        LiftCount++;

        // ヒント1
        // BlockCreate(4*29,9*29-12,300);
        // BlockCreate(7*29,9*29-12,300);

        // 毒1
        // BlockCreate(13*29,8*29-12,114);

        // t=28;
        // sco=0;
        // t=sco;
        // sa[t]=14*29*100+500;sb[t]=(9*29-12)*100;sc[t]=6000;sd[t]=12000-200;stype[t]=50;sxtype[t]=1;sco++;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                LegacyStageDate[t][tt] = NONE;
                LegacyStageDate[t][tt] = stagedatex[t][tt];
            }
        }
        // stagedatex[0][0];

    } // sta1-2-1

    // 1-2(地上)
    if (SyobonWorld == 1 && SyobonLevel == 2 && SyobonSection == 2)
    {

        // マリ　地上　入れ
        // Mix_HaltMusic();
        bgmchange(Music[1]);
        // PlaySoundMem(oto[0],DX_PLAYTYPE_LOOP) ;

        scrollx = 900 * 100;
        PlayerX = 7500;
        PlayerY = 3000 * 9;

        ELegacyStageDate stagedatex[17][1001] = {
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
                CLOUD,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE, GOAL_POLE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, CLOUD,NONE,NONE,NONE,NONE,
            NONE},
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               HARD_BLOCK,
               HARD_BLOCK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
                CASTLE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
                VERTICAL_PIPE_HEAD,
               NONE,
               NONE,
               NONE,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
                VERTICAL_PIPE_BODY,
               NONE,
               NONE,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               HARD_BLOCK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
                BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
                GRASS,
            },
            {GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,
            NONE,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,NONE,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP},
            {GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,
            NONE,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,NONE,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE}};

        /*
        //毒1
        BlockCreate(13*29,8*29-12,114);

        //t=28;
        sco=0;
        t=sco;sa[t]=14*29*100+500;sb[t]=(9*29-12)*100;sc[t]=6000;sd[t]=12000-200;stype[t]=50;sxtype[t]=1;sco++;
        t=sco;sa[t]=12*29*100;sb[t]=(11*29-12)*100;sc[t]=3000;sd[t]=6000-200;stype[t]=40;sxtype[t]=0;sco++;
        t=sco;sa[t]=14*29*100+1000;sb[t]=-6000;sc[t]=5000;sd[t]=70000;stype[t]=100;sxtype[t]=1;sco++;
        */

        t = ObjectCount;
        ObjectX[t] = 5 * 29 * 100 + 500;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 3000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_THIRD_KUMA;
        ObjectCount++;
        // 空飛ぶ土管
        t = 28;
        ObjectX[t] = 44 * 29 * 100 + 500;
        ObjectY[t] = (10 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 9000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectCount++;

        // ポールもどき
        EnemyAppearCount = 0;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 19 * 29 * 100;
        EnemyAppearY[t] = (2 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::FAKE_POLE;
        EnemyAppearSubType[t] = EEnemySubType::FAKE_POLE_STAY;
        EnemyAppearCount++;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                LegacyStageDate[t][tt] = NONE;
                LegacyStageDate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta2

    // 必要BGM+SE

    // 1-3(地上)
    if (SyobonWorld == 1 && SyobonLevel == 3 && SyobonSection == 6)
    {
        SyobonSection = 0;
    }
    if (SyobonWorld == 1 && SyobonLevel == 3 && SyobonSection == 0)
    {

        // Mix_HaltMusic();
        bgmchange(Music[1]);
        // PlaySoundMem(oto[0],DX_PLAYTYPE_LOOP) ;

        scrollx = 3900 * 100;
        // ma=3000;mb=3000;

        ELegacyStageDate stagedatex[17][1001] = {//                                                                                                                                                                                     中間
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,STAGEDATE_97,
                                     NONE,NONE,NONE,
                                     NONE,NONE,STAGEDATE_97,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,CLOUD,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,STAGEDATE_97,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,CLOUD_SMALL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,CANNON_JIEN,NONE,NONE,NONE,CLOUD_SMALL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,CLOUD_SMALL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,SUPER_JIEN,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     CLOUD,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,CLOUD_SMALL,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, SHELL_JIEN,NONE,NONE,NONE,CLOUD_SMALL,
                                     NONE,NONE,
                                     NONE,NONE,
                                     NONE, GOAL_POLE,NONE,NONE,NONE,NONE,NONE,NONE,CLOUD,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     STAGEDATE_97,NONE,NONE,
                                     NONE,NONE,NONE,NONE,CANNON_JIEN,NONE,NONE,NONE,NONE,NONE,NONE,NONE,STAGEDATE_97,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, SUPER_BOON,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,BRICK,
                                     BRICK,BRICK,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, DEFRAG,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                      CHECKPOINT,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                      ITEM_BLOCK_HIDDEN,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,BRICK,NONE, ITEM_BLOCK_COIN,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     CLOUD_SMALL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE, CASTLE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,CLOUD_SMALL,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     BRICK,BRICK,BRICK,
                                     BRICK,BRICK,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE, CASTLE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,STAGEDATE_97,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,STAGEDATE_97,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,NONE, CHECKPOINT,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,
                                     TREE,TREE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,STAGEDATE_97,NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,GRASS,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GRASS,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,GRASS,NONE,NONE,NONE,NONE,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,
                                     GRASS,NONE,
                                     NONE,NONE,
                                     NONE,JIEN,NONE,JIEN,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
                                     NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     GRASS,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE},
                                     {GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,NONE,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        NONE,
                                        NONE,
                                        NONE,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        NONE,
                                        NONE,
                                        NONE,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        NONE,
                                        NONE,
                                        NONE,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        NONE,
                                        NONE,
                                        NONE,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        NONE,
                                        NONE,
                                        NONE,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        GROUND_BOTTOM,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                        NONE,
                                     },
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE}};

        BlockCount = 0;
        BlockCreateLegacy(22 * 29, 3 * 29 - 12, EBlockType::BRICK);
        // 毒1
        BlockCreateLegacy(54 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_PSWITCH);
        // 音符+ (Musical note+)
        BlockCreateLegacy(18 * 29, 14 * 29 - 12, EBlockType::NOTE_BLOCK);
        BlockCreateLegacy(19 * 29, 14 * 29 - 12, EBlockType::NOTE_BLOCK);
        BlockCreateLegacy(20 * 29, 14 * 29 - 12, EBlockType::NOTE_BLOCK);
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_SUPER_JIEN_NORMAL;
        BlockCreateLegacy(61 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_ENEMY); // 5
        BlockCreateLegacy(74 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_HIDDEN);   // 6

        // ヒント2 (Hint 2)
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_1_3_0_1;
        BlockCreateLegacy(28 * 29, 9 * 29 - 12, EBlockType::MESSAGE_BLOCK); // 7
        // ファイア
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_BURNING_FLOWER;
        BlockCreateLegacy(7 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_ENEMY);
        // ヒント3
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_1_3_0_2;
        BlockCreateLegacy(70 * 29, 8 * 29 - 12, EBlockType::MESSAGE_BLOCK); // 9

        // もろいぶろっく×３
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(58 * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(59 * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(60 * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);

        // ヒントブレイク (Hint Break)
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(111 * 29, 6 * 29 - 12, EBlockType::MESSAGE_BLOCK_BREAKABLE);
        // ジャンプ
        BlockSubType[BlockCount] = EBlockSubType::TRAMPOLINE_VISIBLE;
        BlockCreateLegacy(114 * 29, 9 * 29 - 12, EBlockType::TRAMPOLINE);

        // ファイア
        // BlockCreate(7*29,9*29-12,101);

        EnemyAppearCount = 0;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 101 * 29 * 100;
        EnemyAppearY[t] = (5 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::SUPER_JIEN;
        EnemyAppearSubType[t] = EEnemySubType::SUPER_JIEN_JUMPER;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 146 * 29 * 100;
        EnemyAppearY[t] = (10 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::DEFRAG;
        EnemyAppearSubType[t] = EEnemySubType::DEFRAG_GRAB_POLE;
        EnemyAppearCount++;

        t = ObjectCount;
        ObjectX[t] = 9 * 29 * 100;
        ObjectY[t] = (13 * 29 - 12) * 100;
        ObjectSizeX[t] = 9000 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_FLOOR;
        ObjectCount++;
        // t=sco;sa[t]=58*29*100;sb[t]=(13*29-12)*100;sc[t]=9000-1;sd[t]=3000;stype[t]=52;sco++;

        // 土管
        t = ObjectCount;
        ObjectX[t] = 65 * 29 * 100 + 500;
        ObjectY[t] = (10 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 9000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount++;
        // t=28;sa[t]=65*29*100;sb[t]=(10*29-12)*100;sc[t]=6000;sd[t]=9000-200;stype[t]=50;sco++;

        // トラップ
        t = ObjectCount;
        ObjectX[t] = 74 * 29 * 100;
        ObjectY[t] = (8 * 29 - 12) * 100 - 1500;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::TRIGGER_LASER;
        ObjectSubType[t] = EObjectSubType::TRIGGER_LASER_LEVEL_1_3;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 96 * 29 * 100 - 3000;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 9000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_ARAMAKI_DOWN;
        ObjectCount++;
        // ポール砲
        t = ObjectCount;
        ObjectX[t] = 131 * 29 * 100 - 1500;
        ObjectY[t] = (1 * 29 - 12) * 100 - 3000;
        ObjectSizeX[t] = 15000;
        ObjectSizeY[t] = 14000;
        ObjectType[t] = EObjectType::TRIGGER_MULTI_LASER;
        ObjectCount++;

        // ？ボール
        t = EnemyAppearCount;
        EnemyAppearX[t] = 10 * 29 * 100 + 100;
        EnemyAppearY[t] = (11 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::MYSTERY_BALL;
        EnemyAppearSubType[t] = EEnemySubType::MYSTERY_BALL_LEVEL_1_3;
        EnemyAppearCount++;
        // ブロックもどき
        t = EnemyAppearCount;
        EnemyAppearX[t] = 43 * 29 * 100;
        EnemyAppearY[t] = (11 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[t] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount++;
        // t=bco;ba[t]=146*29*100;bb[t]=(12*29-12)*100;btype[t]=82;bxtype[t]=1;bco++;
        // うめぇ
        t = EnemyAppearCount;
        EnemyAppearX[t] = 1 * 29 * 100;
        EnemyAppearY[t] = (2 * 29 - 12 + 10) * 100 - 1000;
        EnemyAppearType[t] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[t] = EEnemySubType::EVIL_CLOUD_NORMAL;
        EnemyAppearCount++;

        // リフト
        LiftCount = 0;
        t = LiftCount;
        LiftX[t] = 33 * 29 * 100;
        LiftY[t] = (3 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::BREAKING;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 39 * 29 * 100 - 2000;
        LiftY[t] = (6 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 1;
        LiftVelY[t] = 0;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 45 * 29 * 100 + 1500;
        LiftY[t] = (10 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PUSH_LEFT;
        LiftCount++;

        t = LiftCount;
        LiftX[t] = 95 * 29 * 100;
        LiftY[t] = (7 * 29 - 12) * 100;
        LiftSizeX[t] = 180 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PILLAR;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 104 * 29 * 100;
        LiftY[t] = (9 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PILLAR_BOUNCY;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 117 * 29 * 100;
        LiftY[t] = (3 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 1;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PILLAR_BRICKS;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 124 * 29 * 100;
        LiftY[t] = (5 * 29 - 12) * 100;
        LiftSizeX[t] = 210 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PILLAR;
        LiftCount++;

        if (stagepoint == 1)
        {
            stagepoint = 0;
            PlayerX = 4500;
            PlayerY = -3000;
            CurrentPlayerCheckpoint = 0;
        }

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                LegacyStageDate[t][tt] = NONE;
                LegacyStageDate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta3

    // 1-3(地下)
    if (SyobonWorld == 1 && SyobonLevel == 3 && SyobonSection == 1)
    {

        // マリ　地上　入れ
        // Mix_HaltMusic();
        bgmchange(Music[2]);
        // PlaySoundMem(oto[0],DX_PLAYTYPE_LOOP) ;

        scrollx = 0 * 100;
        PlayerX = 6000;
        PlayerY = 6000;
        LevelType = ELevelType::UNDERGROUND;

        ELegacyStageDate stagedatex[17][1001] = {
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               BRICK,
               NONE,
               NONE,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
               BRICK,
            },
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
            },
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
            },
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
            },
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
            },
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
            },
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
            },
            {BRICK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,
            NONE,NONE},
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
               NONE,
            },
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
               NONE,
            },
            {
               BRICK,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               BRICK,
               NONE,
            },
            {
               BRICK,
               SUPER_JIEN,
               NONE,
               SUPER_JIEN,
               NONE,
               SUPER_JIEN,
               NONE,
               SUPER_JIEN,
               NONE,
               SUPER_JIEN,
               NONE,
               SUPER_JIEN,
               NONE,
               SUPER_JIEN,
               NONE,
               SUPER_JIEN,
               BRICK,
               NONE,
            },
            {
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               GROUND_TOP,
               BRICK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
            },
            {GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,BRICK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE}};

        BlockCount = 0;
        // BlockCreate(15*29,12*29-12,111);

        SyobonSection = 0;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                LegacyStageDate[t][tt] = NONE;
                LegacyStageDate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta3

    // 1-3(空中)
    if (SyobonWorld == 1 && SyobonLevel == 3 && SyobonSection == 5)
    {

        LevelType = ELevelType::SKY;
        bgmchange(Music[3]);

        scrollx = 0 * 100;
        PlayerX = 3000;
        PlayerY = 33000;

        stagepoint = 1;

        ELegacyStageDate stagedatex[17][1001] = {
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {NONE,NONE,COIN,NONE,COIN,NONE,COIN,NONE,COIN,NONE,COIN,NONE,NONE,NONE,NONE,NONE,NONE},
            {
               NONE,
               NONE,
               NONE,
               COIN,
               NONE,
               COIN,
               NONE,
               COIN,
               NONE,
               COIN,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               COIN,
               NONE,
               COIN,
               NONE,
               COIN,
               NONE,
               COIN,
               NONE,
               COIN,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
               NONE,
            },
            {
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               NONE,
               NONE,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
               CLOUD_BLOCK,
            },
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE}};

        ObjectCount = 0;
        t = ObjectCount;
        ObjectX[t] = 14 * 29 * 100 - 5;
        ObjectY[t] = (11 * 29 - 12) * 100;
        ObjectSizeX[t] = 6000;
        ObjectSizeY[t] = 15000 - 200;
        ObjectType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount++;
        // t=sco;sa[t]=12*29*100;sb[t]=(11*29-12)*100;sc[t]=3000;sd[t]=6000-200;stype[t]=40;sxtype[t]=0;sco++;
        // t=sco;sa[t]=14*29*100+1000;sb[t]=-6000;sc[t]=5000;sd[t]=70000;stype[t]=100;sxtype[t]=1;sco++;

        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(12 * 29, 4 * 29 - 12, EBlockType::ITEM_BLOCK_COINS);
        // ヒント3
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_1_3_5;
        BlockCreateLegacy(12 * 29, 8 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        // txtype[tco]=0;BlockCreate(13*29,4*29-12,110);

        // stc=0;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                LegacyStageDate[t][tt] = NONE;
                LegacyStageDate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta5

    // 1-4(地下)
    if (SyobonWorld == 1 && SyobonLevel == 4 && SyobonSection == 0)
    {

        // マリ　地上　入れ
        // Mix_HaltMusic();
        bgmchange(Music[4]);
        // PlaySoundMem(oto[0],DX_PLAYTYPE_LOOP) ;

        scrollx = 4400 * 100;
        PlayerX = 12000;
        PlayerY = 6000;
        LevelType = ELevelType::CASTLE;

        ELegacyStageDate stagedatex[17][1001] = {//                                                                                                                                                                                     中間
                                     {GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,GROUND_TOP,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,GROUND_TOP,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE},
                                     {GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,GROUND_TOP,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,GROUND_TOP,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     FLAME,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,FLAME,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,ITEM_BLOCK_OPEN,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,FLAME,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,FLAME,NONE,NONE,NONE,NONE,NONE,FLAME,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,JIEN,NONE,GROUND_TOP,NONE,NONE,
                                     GROUND_TOP,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,FLAME,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,GROUND_TOP,ITEM_BLOCK_OPEN,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,CHECKPOINT,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,
                                     GROUND_TOP,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,FLAME,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     ITEM_BLOCK_COIN,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     GROUND_TOP,GROUND_TOP,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,ITEM_BLOCK_HIDDEN,NONE,NONE,NONE,FLAME,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,
                                     NONE,ITEM_BLOCK_OPEN,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_COIN,ITEM_BLOCK_COIN,ITEM_BLOCK_HIDDEN,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,
                                     NONE,ITEM_BLOCK_OPEN,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,
                                     NONE,NONE,NONE,
                                     MAGMA,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,MAGMA,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,MAGMA,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,VERTICAL_PIPE_HEAD,NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,VERTICAL_PIPE_BODY,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,LAVA,NONE,NONE,LAVA,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     LAVA,NONE,
                                     NONE,LAVA,NONE,NONE,LAVA,NONE,NONE,LAVA,NONE,NONE,LAVA,NONE,NONE,LAVA,NONE,NONE,
                                     LAVA,NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,LAVA,NONE,NONE,LAVA,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,LAVA,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,LAVA,NONE,NONE,
                                     LAVA,NONE,NONE,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,LAVA,NONE,NONE,LAVA,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,LAVA,NONE,NONE,LAVA,
                                     NONE,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,LAVA,NONE,GROUND_TOP,GROUND_TOP,LAVA,NONE,NONE,LAVA,NONE,NONE,LAVA,
                                     NONE,NONE,
                                     LAVA,NONE,
                                     NONE,LAVA,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     VERTICAL_PIPE_BODY,NONE,
                                     GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
                                     GROUND_TOP,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE}};

        ObjectCount = 0; // sco=140;
        t = ObjectCount;
        ObjectX[t] = 35 * 29 * 100 - 1500 + 750;
        ObjectY[t] = (8 * 29 - 12) * 100 - 1500;
        ObjectSizeX[t] = 1500;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::TRIGGER_PLATFORM_SPLIT;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 67 * 29 * 100;
        ObjectY[t] = (4 * 29 - 12) * 100;
        ObjectSizeX[t] = 9000 - 1;
        ObjectSizeY[t] = 3000 * 1 - 1;
        ObjectType[t] = EObjectType::FALLING_BLOCKS;
        ObjectSubType[t] = EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP;
        ObjectAI[t] = 0;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 73 * 29 * 100;
        ObjectY[t] = (13 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000 * 1 - 1;
        ObjectSizeY[t] = 3000;
        ObjectType[t] = EObjectType::FALLING_FLOOR;
        ObjectCount++;
        // t=sco;sa[t]=79*29*100;sb[t]=(13*29-12)*100;sc[t]=30*3*100-1;sd[t]=6000-200;stype[t]=51;sxtype[t]=4;sco++;
        // t=sco;sa[t]=83*29*100;sb[t]=(-2*29-12)*100;sc[t]=30*5*100-1;sd[t]=3000-200;stype[t]=51;sxtype[t]=4;sco++;
        t = ObjectCount;
        ObjectX[t] = 123 * 29 * 100;
        ObjectY[t] = (1 * 29 - 12) * 100;
        ObjectSizeX[t] = 30 * 6 * 100 - 1 + 0;
        ObjectSizeY[t] = 3000 - 200;
        ObjectType[t] = EObjectType::FALLING_BLOCKS;
        ObjectSubType[t] = EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_X_ONLY;
        ObjectCount++;
        // スクロール消し (Scrolling OFF)
        t = ObjectCount;
        ObjectX[t] = 124 * 29 * 100 + 3000;
        ObjectY[t] = (2 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000 * 1 - 1;
        ObjectSizeY[t] = 300000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SCROLLING_OFF;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 148 * 29 * 100 + 1000;
        ObjectY[t] = (-12 * 29 - 12) * 100;
        ObjectSizeX[t] = 3000 * 1 - 1;
        ObjectSizeY[t] = 300000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_CLEAR_GAME;
        ObjectCount++;

        // 3連星
        t = ObjectCount;
        ObjectX[t] = 100 * 29 * 100 + 1000;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 3000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SURPRISE_MAGMA;
        ObjectCount++;

        // 地面1 (Ground 1)
        t = ObjectCount;
        ObjectX[t] = 0 * 29 * 100 - 0;
        ObjectY[t] = 9 * 29 * 100 + 1700;
        ObjectSizeX[t] = 3000 * 7 - 1;
        ObjectSizeY[t] = 3000 * 5 - 1;
        ObjectType[t] = EObjectType::CASTLE_BRICKS;
        ObjectSubType[t] = EObjectSubType::NONE;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 11 * 29 * 100;
        ObjectY[t] = -1 * 29 * 100 + 1700;
        ObjectSizeX[t] = 3000 * 8 - 1;
        ObjectSizeY[t] = 3000 * 4 - 1;
        ObjectType[t] = EObjectType::CASTLE_BRICKS;
        ObjectSubType[t] = EObjectSubType::NONE;
        ObjectCount++;

        EnemyAppearCount = 0;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 8 * 29 * 100 - 1400;
        EnemyAppearY[t] = (2 * 29 - 12) * 100 + 500;
        EnemyAppearType[t] = EEnemyType::NYASSUN;
        EnemyAppearSubType[t] = EEnemySubType::NONE;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 42 * 29 * 100 - 1400;
        EnemyAppearY[t] = (-2 * 29 - 12) * 100 + 500;
        EnemyAppearType[t] = EEnemyType::NYASSUN;
        EnemyAppearSubType[t] = EEnemySubType::NONE;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 29 * 29 * 100 + 1500;
        EnemyAppearY[t] = (7 * 29 - 12) * 100 + 1500;
        EnemyAppearType[t] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[t] = (EEnemySubType)105;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 47 * 29 * 100 + 1500;
        EnemyAppearY[t] = (9 * 29 - 12) * 100 + 1500;
        EnemyAppearType[t] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[t] = (EEnemySubType)110;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 70 * 29 * 100 + 1500;
        EnemyAppearY[t] = (9 * 29 - 12) * 100 + 1500;
        EnemyAppearType[t] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[t] = (EEnemySubType)105;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 66 * 29 * 100 + 1501;
        EnemyAppearY[t] = (4 * 29 - 12) * 100 + 1500;
        EnemyAppearType[t] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[t] = (EEnemySubType)101;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 85 * 29 * 100 + 1501;
        EnemyAppearY[t] = (4 * 29 - 12) * 100 + 1500;
        EnemyAppearType[t] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[t] = (EEnemySubType)105;
        EnemyAppearCount++;

        // ステルスうめぇ (Stealth is awesome)
        t = EnemyAppearCount;
        EnemyAppearX[t] = 57 * 29 * 100;
        EnemyAppearY[t] = (2 * 29 - 12 + 10) * 100 - 500;
        EnemyAppearType[t] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[t] = EEnemySubType::EVIL_CLOUD_HIDDEN;
        EnemyAppearCount++;
        // ブロックもどき (Block lookalike)
        t = EnemyAppearCount;
        EnemyAppearX[t] = 77 * 29 * 100;
        EnemyAppearY[t] = (5 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[t] = EEnemySubType::SPIKY_BLOCK_MESSAGE_BLOCK;
        EnemyAppearCount++;
        // ボス (Boss)
        t = EnemyAppearCount;
        EnemyAppearX[t] = 130 * 29 * 100;
        EnemyAppearY[t] = (8 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::MOLALLA;
        EnemyAppearSubType[t] = EEnemySubType::MOLALLA_ALIVE;
        EnemyAppearCount++;
        // クックル (Kukkuru)
        t = EnemyAppearCount;
        EnemyAppearX[t] = 142 * 29 * 100;
        EnemyAppearY[t] = (10 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::KUKKURU;
        EnemyAppearSubType[t] = EEnemySubType::NONE;
        EnemyAppearCount++;

        // マグマ (Magma)
        BackgroundCount = 0;
        BackgroundX[BackgroundCount] = 7 * 29 * 100 - 300;
        BackgroundY[BackgroundCount] = 14 * 29 * 100 - 1200;
        BackgroundType[BackgroundCount] = EBackgroundType::LAVA;
        BackgroundCount++;
        if (BackgroundCount >= BACKGROUND_MAX)
            BackgroundCount = 0;
        BackgroundX[BackgroundCount] = 41 * 29 * 100 - 300;
        BackgroundY[BackgroundCount] = 14 * 29 * 100 - 1200;
        BackgroundType[BackgroundCount] = EBackgroundType::LAVA;
        BackgroundCount++;
        if (BackgroundCount >= BACKGROUND_MAX)
            BackgroundCount = 0;
        BackgroundX[BackgroundCount] = 149 * 29 * 100 - 1100;
        BackgroundY[BackgroundCount] = 10 * 29 * 100 - 600;
        BackgroundType[BackgroundCount] = EBackgroundType::TEXT_51;
        BackgroundCount++;
        if (BackgroundCount >= BACKGROUND_MAX)
            BackgroundCount = 0;

        BlockCount = 0;
        // ON-OFFブロック (ON-OFF Block)
        BlockSubType[BlockCount] = EBlockSubType::ON_BLOCK_LOCKED;
        BlockCreateLegacy(29 * 29, 3 * 29 - 12, EBlockType::ON_BLOCK);
        // 1-2
        BlockCreateLegacy(34 * 29, 9 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCreateLegacy(35 * 29, 9 * 29 - 12, EBlockType::GROUND_TOP);
        // 隠し (Hidden)
        BlockCreateLegacy(55 * 29 + 15, 6 * 29 - 12, EBlockType::ITEM_BLOCK_HIDDEN);
        // BlockCreate(62*29,9*29-12,2);
        // 隠しON-OFF (Hidden ON-OFF)
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_FIREBAR_SWITCH;
        BlockCreateLegacy(50 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_TRAP_HIDDEN);
        // ヒント3 (Hint 3)
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_1_4_0;
        BlockCreateLegacy(1 * 29, 5 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        // ファイア (Fire)
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_BURNING_FLOWER;
        BlockCreateLegacy(86 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_ENEMY);
        // キノコなし　普通 (No mushrooms, normal)
        // txtype[tco]=2;BlockCreate(81*29,1*29-12,5);
        // 音符
        BlockSubType[BlockCount] = EBlockSubType::NOTE_BLOCK_WHITE_HIDDEN;
        BlockCreateLegacy(86 * 29, 6 * 29 - 12, EBlockType::NOTE_BLOCK);

        // もろいぶろっく×３ (Fragile Block x 3)
        for (t = 0; t <= 2; t++)
        {
            BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK_3;
            BlockCreateLegacy((79 + t) * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);
        }

        // ジャンプ (Jump)
        BlockSubType[BlockCount] = EBlockSubType::TRAMPOLINE_VISIBLE_3;
        BlockCreateLegacy(105 * 29, 11 * 29 - 12, EBlockType::TRAMPOLINE);
        // 毒1
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_MUSHROOM_POISONOUS_FASTER;
        BlockCreateLegacy(109 * 29, 7 * 29 - 12, EBlockType::ITEM_BLOCK_MUSHROOM);
        // デフラグ (Defrag)
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_DEFRAG_NORMAL;
        BlockCreateLegacy(111 * 29, 7 * 29 - 12, EBlockType::ITEM_BLOCK_ENEMY);
        // 剣 (Sword)
        BlockCreateLegacy(132 * 29, 8 * 29 - 12 - 3, EBlockType::SWORD);
        BlockCreateLegacy(131 * 29, 9 * 29 - 12, EBlockType::BRIDGE_ROPE);
        // メロン (Melon)
        //+KZ: wait what, google translates it as "melon" but everyone thinks it is a artichoke? xDDDD
        //  It does not even look like a artichoke... I can't trust people anymore
        BlockCreateLegacy(161 * 29, 12 * 29 - 12, EBlockType::MELON);
        // ファイアバー強化 (Fire Bar Enhancement)
        BlockCreateLegacy(66 * 29, 4 * 29 - 12, EBlockType::FIREBAR_GROW);

        // リフト (Lift)
        LiftCount = 0;
        t = LiftCount;
        LiftX[t] = 93 * 29 * 100;
        LiftY[t] = (10 * 29 - 12) * 100;
        LiftSizeX[t] = 60 * 100;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 1;
        LiftVelY[t] = 0;
        LiftCount++;
        t = 20;
        LiftX[t] = 119 * 29 * 100 + 300;
        LiftY[t] = (10 * 29 - 12) * 100;
        LiftSizeX[t] = 12 * 30 * 100 + 1000;
        LiftInteractType[t] = 0;
        LiftMovementType[t] = 0;
        LiftType[t] = ELiftType::GRAY;
        LiftVelY[t] = 0;
        LiftCount++;

        SyobonSection = 0;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                LegacyStageDate[t][tt] = NONE;
                LegacyStageDate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta4
}
