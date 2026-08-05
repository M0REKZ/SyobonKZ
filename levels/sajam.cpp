
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

void HandleSyobonActionJAMLevels()
{
    if(SyobonState == ESyobonGameState::TITLE)
    {
        scrollx = 0;

        PlayerX = (2.4 * 30) * 100;
        PlayerY = (12 * 29 - 12 - 6) * 100;

        for(int grounds = 0; grounds < 20; grounds++)
        {
            BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
            BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
        }

        CreateBackground(GAME_X_POS_TO_DOUBLE(6 * 30 * 100), 12, EBackgroundType::GRASS);
        CreateBackground(0, 10, EBackgroundType::HILL);

        CreateEnemy(18, 12, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_NORMAL);

        return;
    }
    else if(SyobonWorld == 1 && SyobonLevel == 1)
    {
        if(SyobonSection == 0)
        {
            scrollx = 300000;

            PlayerX = (2.4 * 30) * 100;
            PlayerY = (12 * 29 - 12 - 6) * 100;

            LevelType = ELevelType::OVERWORLD;

            bgmchange(Music[1]);

            for(int grounds = 0; grounds < 100; grounds++)
            {
                BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
                BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
            }

            CreateBackground(0, 10, EBackgroundType::HILL);
            CreateBackground(11, 12, EBackgroundType::GRASS);

            CreateEnemy(18, 12, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_NORMAL);

            BlockCreate(16, 9, EBlockType::ITEM_BLOCK_COIN);

            BlockCreate(20, 9, EBlockType::BRICK);
            BlockCreate(21, 9, EBlockType::ITEM_BLOCK_ENEMY, EBlockSubType::ITEM_BLOCK_ENEMY_SAJAM_JIEN_NORMAL_BELOW);
            BlockCreate(22, 9, EBlockType::BRICK);
            BlockCreate(23, 9, EBlockType::ITEM_BLOCK_COIN);
            BlockCreate(24, 9, EBlockType::BRICK);

            ObjectCreate(28 + GAME_X_POS_TO_DOUBLE(500), 11, 2 - GAME_X_POS_TO_DOUBLE(1000), 2, EObjectType::VERTICAL_PIPE_BODY, EObjectSubType::NONE);
            ObjectCreate(28, 11, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
            ObjectCreate(28, 0, 2, 10.5, EObjectType::TRIGGER_ARAMAKI_UP, EObjectSubType::NONE);
        }
    }

}
