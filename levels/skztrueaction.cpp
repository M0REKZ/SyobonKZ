
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

//+KZ
void HandleSyobonKZTrueActionLevels()
{
    StageClear();

    if(SyobonState == ESyobonGameState::TITLE)
    {
        scrollx = 0;

        PlayerX = (2 * 30) * 100;
        PlayerY = (12 * 29 - 12 - 6) * 100;

        BlockCreate(2, 13, EBlockType::HARD_BLOCK);
        BlockCreate(2, 10, EBlockType::BRICK);
        for(int x_pos = 0; x_pos < 3; x_pos++)
        {
            if(x_pos != 1)
            {
                for(int y_pos = 1; y_pos < 4 ; y_pos++)
                {
                    BlockCreate(1 + x_pos, 13 - y_pos, EBlockType::HARD_BLOCK);
                }
            }
            BlockCreate(1 + x_pos, 13, EBlockType::GROUND_TOP);
            BlockCreate(1 + x_pos, 14, EBlockType::GROUND_BOTTOM);
        }

        CreateEnemy(16, 11.7, -1, 0, EEnemyType::BALL_ROCKET, EEnemySubType::BALL_ROCKET_NORMAL);

        BlockCreate(6, 13, EBlockType::GROUND_TOP);
        BlockCreate(6, 14, EBlockType::GROUND_BOTTOM);

        return;
    }
    if(SyobonWorld == 1)
    {
        if(SyobonLevel == 1)
        {
            bgmchange(Music[1]);

            SyobonSection = 0;
            scrollx = 400000;

            PlayerX = (2 * 30) * 100;
            PlayerY = (12 * 29 - 12 - 6) * 100;

            ObjectCreate(1, 13, 3, 1, EObjectType::SA3_FALLING_FLOOR, EObjectSubType::NONE);
            BlockCreate(2, 10, EBlockType::BRICK);
            for(int x_pos = 0; x_pos < 3; x_pos += 2)
            {
                CreateEnemy(1 + x_pos, 10, 0, 0, EEnemyType::SPIKY_BLOCK, EEnemySubType::SPIKY_BLOCK_HARD_BLOCK);
                for(int y_pos = 1; y_pos < 3 ; y_pos++)
                {
                    BlockCreate(1 + x_pos, 13 - y_pos, EBlockType::HARD_BLOCK);
                }
                
                //BlockCreate(1 + x_pos, 13, EBlockType::GROUND_TOP);
                //BlockCreate(1 + x_pos, 14, EBlockType::GROUND_BOTTOM);
            }

            CreateEnemy(16, 11.7, -1, 0, EEnemyType::BALL_ROCKET, EEnemySubType::BALL_ROCKET_NORMAL);

            CreateEnemy(4, 10, 0, 0, EEnemyType::EVIL_CLOUD, EEnemySubType::EVIL_CLOUD_HIDDEN);
            CreateEnemy(5.6, 8.5, 0, 0, EEnemyType::EVIL_CLOUD, EEnemySubType::EVIL_CLOUD_HIDDEN);

            BlockCreate(6.5, 13, EBlockType::GROUND_TOP);
            BlockCreate(6.5, 14, EBlockType::GROUND_BOTTOM);


            BlockCreate(17, 13, EBlockType::GROUND_TOP);
            BlockCreate(17, 14, EBlockType::GROUND_BOTTOM);

            //avoid triggering trap from below
            BlockCreate(17, 15, EBlockType::GROUND_BOTTOM);
            BlockCreate(17, 16, EBlockType::GROUND_BOTTOM);

            QueueEnemyAppear(22, 11, EEnemyType::BALL_SPIKY, EEnemySubType::BALL_SPIKY_JUMPER);
            ObjectCreate(18, 13, 20, 1, EObjectType::SA3_FALLING_FLOOR, EObjectSubType::NONE);

            //weird thing to avoid that jumping ball glitching through the fake floor
            //i was going to use ID 1000 (invalid id that only enemies can touch) but ill just use coins
            for(int x_pos = 0; x_pos <= 4; x_pos++)
            {
                BlockCreate(18 + x_pos, 13, EBlockType::COIN);
            }

            BlockCreate(27, 10, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_ITEM_BLOCK_OPEN);
            BlockCreate(28, 10, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_ITEM_BLOCK_OPEN);
            BlockCreate(29, 10, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_ITEM_BLOCK_OPEN);
            BlockCreate(30, 10, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_ITEM_BLOCK_OPEN);

            QueueEnemyAppear(31, 8, EEnemyType::BALL_SPIKY, EEnemySubType::BALL_SPIKY_SA3_HIDE_SPIKES);

            BlockCreate(38, 9, EBlockType::SYOBONKZ_HIDDEN_BLOCK, EBlockSubType::SYOBONKZ_HIDDEN_BLOCK_SPIKE_DOWN);
        }
    }
}
