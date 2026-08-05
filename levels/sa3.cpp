
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

// WIP
void HandleSyobonActionThreeLevels()
{
    StageClear();

    //SA3 Title Screen
    if(SyobonState == ESyobonGameState::TITLE)
    {
        scrollx = 0;

        PlayerX = (2 * 29) * 100 - 350;
        PlayerY = (12 * 29 - 12 - 6) * 100;

        for(int grounds = 0; grounds < 20; grounds++)
        {
            BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
            BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
        }

        ObjectCreate(3, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(3 + GAME_X_POS_TO_DOUBLE(500), 9, 2 - GAME_X_POS_TO_DOUBLE(1000), 5, EObjectType::SA3_FAKE_PIPE_BODY, EObjectSubType::NONE);

        CreateBackground(3, 10, EBackgroundType::HILL);
        
        //Poison mushroom
        BlockCreate(9, 9, EBlockType::ITEM_BLOCK_OPEN);
        int entity_index = CreateEnemy(9, 9, 0, 0, EEnemyType::MUSHROOM_POISONOUS, EEnemySubType::NONE);
        if(entity_index >= 0)
            EnemyBlockAppearTimer[entity_index] = 16;

        //here originally Syobon Action 3 hides the real player xd
        BlockCreate(11, 12, EBlockType::HARD_BLOCK);
        BlockCreate(12, 12, EBlockType::HARD_BLOCK);
        BlockCreate(13, 12, EBlockType::HARD_BLOCK);
        BlockCreate(11, 11, EBlockType::HARD_BLOCK);
        BlockCreate(12, 11, EBlockType::HARD_BLOCK);
        BlockCreate(13, 11, EBlockType::HARD_BLOCK);
        BlockCreate(12, 10, EBlockType::HARD_BLOCK);

        CreateBackground(14, 12, EBackgroundType::GRASS);
        CreateBackground(12, 10 - 5.724, EBackgroundType::CLOUD);
        CreateBackground(2, 3, EBackgroundType::CLOUD);
        CreateBackground(7, 2.5, EBackgroundType::CLOUD_SMALL);
        CreateBackground(15, 1.2, EBackgroundType::CLOUD_SMALL);

        return;
    }
    //has code from SA:All Stars (though i deleted and modified it a lot)
    else if (SyobonWorld == 1 && SyobonLevel == 1 && SyobonSection == 0)
    {
        scrollx = 800000;
        bgmchange(Music[1]);

        //Create all the ground
        for(int grounds = 0; grounds <= 214; grounds++)
        {
            //holes
            if(
                (grounds >= 3 && grounds <= 6)
            )
            {
                BlockCreate(grounds, 7.5, EBlockType::ITEM_BLOCK_HIDDEN);
                BlockCreate(grounds, 13, EBlockType::ITEM_BLOCK_HIDDEN);
                continue;
            }

            if(
                (grounds >= 50 && grounds <= 54) ||
                (grounds >= 69 && grounds <= 77) ||
                (grounds >= 83 && grounds <= 94) ||
                (grounds >= 132 && grounds < 140) ||
                (grounds >= 171 && grounds <= 174) ||
                (grounds >= 154 && grounds <= 157) ||
                (grounds >= 188 && grounds <= 196)
            )
            {
                continue;
            }

            BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
            BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
        }

        //the first blocks in Syobon Action 3 have a weird 0.5 Y offset
        BlockCreate(0, 8.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(1, 8.5, EBlockType::HARD_BLOCK);
        BlockCreate(2, 8.5, EBlockType::BRICK);

        BlockCreate(6, 9.5, EBlockType::HARD_BLOCK);
        BlockCreate(6, 10.5, EBlockType::HARD_BLOCK);

        BlockCreate(9, 8.5, EBlockType::BRICK);
        BlockCreate(10, 8.5, EBlockType::ITEM_BLOCK_COIN);
        BlockCreate(11, 8.5, EBlockType::BRICK);
        BlockCreate(12, 8.5, EBlockType::ITEM_BLOCK_MUSHROOM, EBlockSubType::ITEM_BLOCK_MUSHROOM_SA3_TRAP);
        BlockCreate(13, 8.5, EBlockType::BRICK);
        BlockCreate(14, 8.5, EBlockType::BRICK);

        BlockCreate(15, 4.5, EBlockType::HARD_BLOCK);
        BlockCreate(16, 4.5, EBlockType::BRICK);
        BlockCreate(17, 4.5, EBlockType::BRICK);
        
        //replace the copyright plant trap with a seal
        ObjectCreate(0.25, 8.75, 0.50, 5, EObjectType::SA3_TRIGGER_FAST_ARAMAKI_UP, EObjectSubType::SA3_TRIGGER_FAST_ARAMAKI_UP_1_ARAMAKI);

        CreateEnemy(12.5, 7.5, 0, 0, EEnemyType::JIEN, EEnemySubType::NONE);
        CreateEnemy(6.5, 11.5, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::NONE);
        CreateEnemy(15.5, 3.5, 0, 0, EEnemyType::JIEN, EEnemySubType::NONE);

        CreateEnemy(27.5, 8, 0, 0, EEnemyType::JIEN, EEnemySubType::NONE);

        CreateBackground(1, 2.5, EBackgroundType::CLOUD);
        CreateBackground(10, 2.5, EBackgroundType::CLOUD_SMALL);
        CreateBackground(9, 10, EBackgroundType::HILL);
        CreateBackground(23, 1.5, EBackgroundType::CLOUD);
        CreateBackground(32, 2.5, EBackgroundType::CLOUD_SMALL);
        CreateBackground(33.24, 12, EBackgroundType::GRASS);
        CreateBackground(42, 2.5, EBackgroundType::CLOUD_SMALL);
        CreateBackground(44, 10, EBackgroundType::HILL);

        //pipes for each 4 blocks
        for(int i = 0; i < 5; i++)
        {
            if(i == 0)
            {
                ObjectCreate(27 + (i * 4) + GAME_X_POS_TO_DOUBLE(500), 9, 2 - GAME_X_POS_TO_DOUBLE(1000), 4, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
            }
            else
            {
                ObjectCreate(27 + (i * 4) + GAME_X_POS_TO_DOUBLE(500), 9, 2 - GAME_X_POS_TO_DOUBLE(1000), 4, EObjectType::SA3_FAKE_PIPE_BODY, EObjectSubType::NONE);
        
                if(i != 4)
                {
                    CreateEnemy(29 + (i * 4), 10, 0, 0, EEnemyType::EVIL_CLOUD, EEnemySubType::EVIL_CLOUD_HIDDEN);
                }
                else
                {
                    ObjectCreate(27.25 + (i * 4), 0, 1.5, 8.5, EObjectType::SA3_TRIGGER_FAST_ARAMAKI_UP, EObjectSubType::SA3_TRIGGER_FAST_ARAMAKI_UP_4_ARAMAKIS);
                }
            }

            ObjectCreate(27 + (i * 4), 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        }

        //remaining code from all stars xd
        int t_9 = ObjectCount;
        ObjectX[t_9] = 8700; //n地面[t_9].a = 8700;
        ObjectY[t_9] = 36500; //n地面[t_9].b = 36500;
        ObjectSizeX[t_9] = 11999; //n地面[t_9].c = 11999;
        ObjectSizeY[t_9] = 3000; //n地面[t_9].d = 3000;
        ObjectType[t_9] = EObjectType::FALLING_FLOOR; //n地面[t_9].type = 52;
        ObjectCount++; //ObjectCount++;



        //after the pipes

        BlockCreate(51, 8.5, EBlockType::HARD_BLOCK);
        BlockCreate(53, 4.5, EBlockType::HARD_BLOCK);

        //spikes trap
        for(int i = 6; i <= 12; i++)
        {
            if(i == 6)
            {
                //save first block index for the trap
                int trap_index = ObjectCreate(56, 12.5, 7.5, 0.5, EObjectType::SA3_TRIGGER_SPIKES_LEVEL_1_1, EObjectSubType::SA3_TRIGGER_SPIKES_LEVEL_1_1_WAITING);
                if(trap_index >= 0)
                    ObjectAI[trap_index] = BlockCreate(55, i, EBlockType::ITEM_BLOCK_OPEN);
            }
            else
            {
                BlockCreate(55, i, EBlockType::ITEM_BLOCK_OPEN);
            }
            BlockCreate(64, i + 7, EBlockType::ITEM_BLOCK_OPEN);
        }

        ObjectCreate(65, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(65 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(67, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(67 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);


        BlockCreate(69, 4.75, EBlockType::ITEM_BLOCK_HIDDEN);

        for(int i = 72; i <= 76; ++i)
        {
            BlockCreate(i, 6, EBlockType::BRICK);
        }

        CreateEnemy(75.5, 5, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);

        BlockCreate(80.9, 12, EBlockType::TRAMPOLINE, EBlockSubType::TRAMPOLINE_VISIBLE);

        BlockCreate(83, 9, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(84, 6, EBlockType::ITEM_BLOCK_HIDDEN);

        BlockCreate(85, 3.5, EBlockType::BRICK);
        BlockCreate(86, 3.5, EBlockType::BRICK);
        BlockCreate(87, 3.5, EBlockType::BRICK);

        ObjectCreate(91, 13, 4, 2, EObjectType::SA3_FALLING_FLOOR, EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM);
        BlockCreate(91, 13, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(92, 13, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(93, 13, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(94, 13, EBlockType::ITEM_BLOCK_HIDDEN);
        ObjectCreate(98, 11, 1, 2, EObjectType::CHECKPOINT, EObjectSubType::NONE);

        // tunnel thing
        BlockCreate(103, 11.5, EBlockType::HARD_BLOCK);
        BlockCreate(103, 10.5, EBlockType::HARD_BLOCK);
        BlockCreate(103, 9.5, EBlockType::HARD_BLOCK);
        int first_wall_block = -1;
        for(int x_pos = 104; x_pos <= 125; x_pos++)
        {
            if(
                (
                    x_pos % 2 &&
                    (
                        x_pos >= 105 && x_pos <= 111
                    )
                )
                ||
                (
                    x_pos == 114 || x_pos == 115
                )
                ||
                (
                    x_pos == 122
                )
            )
            {
                BlockCreate(x_pos, 9.5, EBlockType::ITEM_BLOCK_COIN);
            }
            else if(x_pos == 119)
            {
                BlockCreate(x_pos, 9.5, EBlockType::ITEM_BLOCK_HIDDEN);
            }
            else if(x_pos != 125)
            {
                BlockCreate(x_pos, 9.5, EBlockType::HARD_BLOCK);
            }

            if(x_pos >= 107 && (x_pos % 2) && x_pos <= 119)
            {
                if(x_pos == 107 || x_pos == 111 || x_pos == 113 || x_pos == 117)
                {
                    CreateEnemy(x_pos + 0.5, 8.5, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_NORMAL);
                }
                else
                {
                    CreateEnemy(x_pos + 0.5, 8.5, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);
                }
            }

            if(x_pos == 122)
            {
                CreateEnemy(x_pos + 0.5, 8.5, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);
            }
            else if(x_pos == 124)
            {
                CreateEnemy(x_pos + 0.5, 8.5, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_NORMAL);
            }

            if(x_pos >= 106)
            {
                BlockCreate(x_pos, 5.5, EBlockType::HARD_BLOCK);

                if(!(x_pos % 2) && (x_pos >= 108))
                {
                    BlockCreate(x_pos - 0.2, 4.5, EBlockType::COIN);
                }

                if(x_pos > 107)
                {
                    BlockCreate(x_pos, 0.5, EBlockType::ITEM_BLOCK_HIDDEN);
                    if(x_pos == 111 || x_pos == 116 || x_pos == 120 || x_pos == 123)
                    {
                        BlockCreate(x_pos, 2.5, EBlockType::ITEM_BLOCK_COIN);
                    }
                    else
                    {
                        BlockCreate(x_pos, 2.5, EBlockType::BRICK);
                    }
                }
            }

            if(x_pos == 107)
            {
                for(double y_pos = -2.5; y_pos < 3; y_pos++)
                {
                    if(y_pos < -2.0)
                    {
                        first_wall_block = BlockCreate(x_pos, y_pos, EBlockType::ITEM_BLOCK_OPEN);
                    }
                    else
                    {
                        BlockCreate(x_pos, y_pos, EBlockType::ITEM_BLOCK_OPEN);
                    }
                }
            }
        }

        CreateBackground(114, 1.5, EBackgroundType::CLOUD);

        int ind = ObjectCreate(117, 1, 1, 4.5, EObjectType::SA3_TRIGGER_BIG_STONE_BALL_LEVEL_1_1, EObjectSubType::NONE);
        ObjectAI[ind] = first_wall_block;
        ObjectVelY[ind] = 6;
        ind = ObjectCreate(121, 10.5, 1, 4.5, EObjectType::SA3_TRIGGER_BIG_STONE_BALL_LEVEL_1_1, EObjectSubType::NONE);
        ObjectAI[ind] = -1;

        ObjectCreate(130, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(130 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        BlockCreate(132, 5.5, EBlockType::ITEM_BLOCK_HIDDEN);

        for(int x_coin = 132; x_coin < 140; x_coin++)
        {
            BlockCreate(x_coin, 11.5, EBlockType::COIN);
        }
        ObjectCreate(132, 13, 8, 2, EObjectType::SA3_UNTOUCHABLE_FALLING_FLOOR, EObjectSubType::SA3_UNTOUCHABLE_FALLING_FLOOR_GROUND_TOP_BOTTOM);

        ObjectCreate(140, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(140 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(140, 0, 2, 11, EObjectType::SA3_TRIGGER_FAST_ARAMAKI_UP, EObjectSubType::SA3_TRIGGER_FAST_ARAMAKI_UP_1_ARAMAKI);

        //plant
        BlockCreate(148, 12, EBlockType::HARD_BLOCK);

        BlockCreate(149, 12, EBlockType::HARD_BLOCK);
        BlockCreate(149, 11, EBlockType::HARD_BLOCK);

        BlockCreate(150, 12, EBlockType::HARD_BLOCK);
        BlockCreate(150, 11, EBlockType::HARD_BLOCK);
        BlockCreate(150, 10, EBlockType::HARD_BLOCK);

        BlockCreate(151, 12, EBlockType::HARD_BLOCK);
        BlockCreate(151, 11, EBlockType::HARD_BLOCK);
        BlockCreate(151, 10, EBlockType::HARD_BLOCK);
        BlockCreate(151, 9, EBlockType::HARD_BLOCK);

        CreateEnemy(152.5, 9, 0, 0, EEnemyType::SA3_JUMPSCARE_PLANT, EEnemySubType::NONE);
        ObjectCreate(152, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(152 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        ObjectCreate(154, 13, 4, 2, EObjectType::SA3_FALLING_FLOOR, EObjectSubType::NONE);

        CreateEnemy(168, 12, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_SA3_HIDE_SPIKES);

        ObjectCreate(171, 13, 4, 2, EObjectType::SA3_FALLING_FLOOR, EObjectSubType::NONE);

        BlockCreate(173, 9, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(174, 9, EBlockType::ITEM_BLOCK_HIDDEN);
        ObjectCreate(175, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(175 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        CreateEnemy(171, 1.5, 0, 0, EEnemyType::SHELL_JIEN, EEnemySubType::NONE);
        for(int x_pos = 169; x_pos <= 173; x_pos++)
        {
            BlockCreate(x_pos, 2.5, EBlockType::BRICK);
        }
        BlockCreate(169, 1.5, EBlockType::BRICK);
        BlockCreate(174, 1.5, EBlockType::BRICK);
        BlockCreate(174, 2.5, EBlockType::ITEM_BLOCK_HIDDEN);
        for(int x_pos = 176; x_pos <= 184; x_pos++)
        {
            BlockCreate(x_pos, 2.5, EBlockType::ITEM_BLOCK_HIDDEN, EBlockSubType::ITEM_BLOCK_HIDDEN_SA3_NO_SHELL);
        }
        
        BlockCreate(175, 5.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(177, 5.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(180, 6.5, EBlockType::ITEM_BLOCK_HIDDEN);


        //goal thing
        BlockCreate(179, 12, EBlockType::HARD_BLOCK);

        BlockCreate(180, 12, EBlockType::HARD_BLOCK);
        BlockCreate(180, 11, EBlockType::HARD_BLOCK);

        BlockCreate(181, 12, EBlockType::HARD_BLOCK);
        BlockCreate(181, 11, EBlockType::HARD_BLOCK);
        BlockCreate(181, 10, EBlockType::HARD_BLOCK);

        BlockCreate(182, 12, EBlockType::HARD_BLOCK);
        BlockCreate(182, 11, EBlockType::HARD_BLOCK);
        BlockCreate(182, 10, EBlockType::HARD_BLOCK);
        BlockCreate(182, 9, EBlockType::HARD_BLOCK);

        BlockCreate(183, 12, EBlockType::HARD_BLOCK);
        BlockCreate(183, 11, EBlockType::HARD_BLOCK);
        BlockCreate(183, 10, EBlockType::HARD_BLOCK);
        BlockCreate(183, 9, EBlockType::HARD_BLOCK);
        BlockCreate(183, 8, EBlockType::HARD_BLOCK);

        BlockCreate(184, 12, EBlockType::HARD_BLOCK);
        BlockCreate(184, 11, EBlockType::HARD_BLOCK);
        BlockCreate(184, 10, EBlockType::HARD_BLOCK);
        BlockCreate(184, 9, EBlockType::HARD_BLOCK);
        BlockCreate(184, 8, EBlockType::HARD_BLOCK);
        BlockCreate(184, 7, EBlockType::HARD_BLOCK);

        BlockCreate(185, 12, EBlockType::HARD_BLOCK);
        BlockCreate(185, 11, EBlockType::HARD_BLOCK);
        BlockCreate(185, 10, EBlockType::HARD_BLOCK);
        BlockCreate(185, 9, EBlockType::HARD_BLOCK);
        BlockCreate(185, 8, EBlockType::HARD_BLOCK);
        BlockCreate(185, 7, EBlockType::HARD_BLOCK);
        BlockCreate(185, 6, EBlockType::HARD_BLOCK);

        BlockCreate(186, 12, EBlockType::HARD_BLOCK);
        BlockCreate(186, 11, EBlockType::HARD_BLOCK);
        BlockCreate(186, 10, EBlockType::HARD_BLOCK);
        BlockCreate(186, 9, EBlockType::HARD_BLOCK);
        BlockCreate(186, 8, EBlockType::HARD_BLOCK);
        BlockCreate(186, 7, EBlockType::HARD_BLOCK);
        BlockCreate(186, 6, EBlockType::HARD_BLOCK);
        BlockCreate(186, 5, EBlockType::HARD_BLOCK);

        BlockCreate(187, 12, EBlockType::HARD_BLOCK);
        BlockCreate(187, 11, EBlockType::HARD_BLOCK);
        BlockCreate(187, 10, EBlockType::HARD_BLOCK);
        BlockCreate(187, 9, EBlockType::HARD_BLOCK);
        BlockCreate(187, 8, EBlockType::HARD_BLOCK);
        BlockCreate(187, 7, EBlockType::HARD_BLOCK);
        BlockCreate(187, 6, EBlockType::HARD_BLOCK);
        BlockCreate(187, 5, EBlockType::HARD_BLOCK);

        BlockCreate(188, 1, EBlockType::ITEM_BLOCK_TRAP_HIDDEN, EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_SA3_1UP);

        ObjectCreate(188, 13, 9, 2, EObjectType::SA3_FALLING_FLOOR, EObjectSubType::NONE);
        ObjectCreate(197, 1, 1, 11.3, EObjectType::GOAL_POLE, EObjectSubType::GOAL_POLE_NEED_CASTLE);

        BlockCreate(197, 12, EBlockType::HARD_BLOCK);

        for(int x_pos = 188; x_pos <= 196; x_pos++)
        {
            BlockCreate(x_pos, 10.7, EBlockType::ITEM_BLOCK_HIDDEN, EBlockSubType::ITEM_BLOCK_HIDDEN_SA3_NO_SHELL);
        }

        BlockCreate(190.5, 7, EBlockType::ITEM_BLOCK_HIDDEN);

        for(double y_pos = -6.5; y_pos < 3; y_pos++)
        {
            if(y_pos < -6.0)
            {
                first_wall_block = BlockCreate(196, y_pos - 5, EBlockType::ITEM_BLOCK_OPEN);
            }
            else
            {
                BlockCreate(196, y_pos - 5, EBlockType::ITEM_BLOCK_OPEN);
            }
        }

        ind = ObjectCreate(192, -15, 1, 16, EObjectType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1, EObjectSubType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_WAITING);
        ObjectAI[ind] = first_wall_block;
        ObjectVelY[ind] = 9;

        //the rest of backgrounds
        CreateBackground(125.5, 3, EBackgroundType::CLOUD_SMALL);
        CreateBackground(125.4, 12, EBackgroundType::GRASS);
        CreateBackground(137, 2.9, EBackgroundType::CLOUD);

        CreateBackground(142.5, 1, EBackgroundType::CLOUD_SMALL);
        CreateBackground(149, 1, EBackgroundType::CLOUD_SMALL);
        CreateBackground(160, 12, EBackgroundType::GRASS);
        CreateBackground(162, 0.5, EBackgroundType::CLOUD);
        CreateBackground(164, 10.7, EBackgroundType::HILL);

        CreateBackground(176.5, 0.5, EBackgroundType::CLOUD_SMALL);

        CreateBackground(195, 1.9, EBackgroundType::CLOUD);

        CreateBackground(199, 10, EBackgroundType::HILL);

        CreateBackground(209, 12, EBackgroundType::GRASS);

        CreateBackground(209, 2.9, EBackgroundType::CLOUD_SMALL);

        //CreateBackground(204, 10, EBackgroundType::CASTLE);
        ObjectCreate(204, 10, 3, 3, EObjectType::GOAL_CASTLE, EObjectSubType::GOAL_CASTLE_NORMAL);
    }
    else if (SyobonWorld == 1 && SyobonLevel == 2 && SyobonSection == 0)
    {
        scrollx = 577900;
        bgmchange(Music[2]);

        LevelType = ELevelType::UNDERGROUND;

        PlayerX = DOUBLE_TO_GAME_X_POS(2);
        PlayerY = DOUBLE_TO_GAME_Y_POS(2);

        //Create all the ground
        for(int grounds = 0; grounds <= 215; grounds++)
        {
            if(
                (grounds >= 32 && grounds <= 47) ||
                (grounds == 68) ||
                (grounds >= 133 && grounds <= 147) ||
                (grounds >= 182 && grounds <= 187) ||
                grounds == 199 ||
                grounds == 201 ||
                grounds == 196 ||
                (grounds <= 206 && grounds >= 204)
            )
            {
                continue;
            }

            if(
                grounds == 159 ||
                grounds == 170 ||
                grounds == 190 ||
                grounds == 195 ||
                grounds == 172 ||
                grounds == 173
            )
            {
                BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
                continue;
            }

            if(
                grounds == 200 ||
                grounds == 202 ||
                grounds == 203 ||
                (grounds >= 207 && grounds <= 210)
            )
            {
                BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
                continue;
            }

            if(
                (grounds >= 10 && grounds <= 18)
            )
            {
                BlockCreate(grounds, 9, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_BRICK);
                continue;
            }

            if(grounds == 0)
            {
                for(int y_pos = 0; y_pos < 13; y_pos++)
                {
                    BlockCreate(grounds, y_pos, EBlockType::BRICK);
                }
            }

            if(
                grounds >= 1 && grounds <= 4
            )
            {
                BlockCreate(grounds, 13, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_SA3_GROUND_TOP);
                BlockCreate(grounds, 14, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_SA3_GROUND_BOTTOM);
                continue;
            }

            if(grounds >= 81 && grounds <= 96)
            {
                if(grounds != 81 && grounds <= 91)
                {
                    BlockCreate(grounds, 13, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_SA3_GROUND_TOP);
                    BlockCreate(grounds, 14, EBlockType::BRICK_BRITTLE, EBlockSubType::BRICK_BRITTLE_SA3_GROUND_BOTTOM);
                }
                continue;
            }

            BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
            BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
        }

        for(int roofs = 4; roofs <= 205; roofs++)
        {
            if(
                roofs == 98 ||
                roofs == 151
            )
            {
                continue;
            }

            if(roofs == 68)
            {
                BlockCreate(roofs, 1.5, EBlockType::SA3_BRICK_BRITTLE);
                continue;
            }
            BlockCreate(roofs, 1.5, EBlockType::BRICK);
        }

        BlockCreate(2, 11.5, EBlockType::COIN);
        BlockCreate(3, 11.5, EBlockType::COIN);

        BlockCreate(9, 9, EBlockType::HARD_BLOCK);
        BlockCreate(9, 10, EBlockType::HARD_BLOCK);
        BlockCreate(9, 11, EBlockType::HARD_BLOCK);
        BlockCreate(9, 12, EBlockType::HARD_BLOCK);

        BlockCreate(19, 9, EBlockType::HARD_BLOCK);
        BlockCreate(19, 10, EBlockType::HARD_BLOCK);
        BlockCreate(19, 11, EBlockType::HARD_BLOCK);
        BlockCreate(19, 12, EBlockType::HARD_BLOCK);

        CreateBackground(10, 13.8, EBackgroundType::LAVA);
        CreateBackground(10, 13, EBackgroundType::LAVA);
        CreateBackground(13, 13.8, EBackgroundType::LAVA);
        CreateBackground(13, 13, EBackgroundType::LAVA);
        CreateBackground(16, 13.8, EBackgroundType::LAVA);
        CreateBackground(16, 13, EBackgroundType::LAVA);

        CreateEnemy(24, 7.5, 0, 0, EEnemyType::CANNON_JIEN, EEnemySubType::CANNON_JIEN_NORMAL);

        for(int x_pos = 28; x_pos <= 34; x_pos++)
        {
            BlockCreate(x_pos, 2.5, EBlockType::SA3_WHITE_SPIKE_DOWN);
        }

        BlockCreate(30.9, 12, EBlockType::TRAMPOLINE);

    
        CreateBackground(32, 13, EBackgroundType::SA3_FAKE_GROUND_TOP);
        BlockCreate(32, 14, EBlockType::GROUND_BOTTOM);
        for(int x_pos = 33; x_pos <= 46; x_pos++)
        {
            BlockCreate(x_pos, 11.5, EBlockType::BRICK);
            CreateBackground(x_pos, 13, EBackgroundType::SA3_FAKE_GROUND_TOP);
            BlockCreate(x_pos, 14, EBlockType::GROUND_BOTTOM);
        }
        CreateBackground(47, 13, EBackgroundType::SA3_FAKE_GROUND_TOP);
        ObjectCreate(47, 14, 1, 2, EObjectType::SA3_FALLING_FLOOR, EObjectSubType::SA3_FALLING_FLOOR_GROUND_BOTTOM);

        CreateEnemy(45, 3.5, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);

        BlockCreate(46, 4.5, EBlockType::HARD_BLOCK);
        BlockCreate(46, 5.5, EBlockType::HARD_BLOCK);
        BlockCreate(46, 6.5, EBlockType::HARD_BLOCK);
        BlockCreate(46, 7.5, EBlockType::HARD_BLOCK);
        BlockCreate(46, 8.5, EBlockType::HARD_BLOCK);
        BlockCreate(46, 9.5, EBlockType::HARD_BLOCK);
        BlockCreate(46, 10.5, EBlockType::HARD_BLOCK);

        BlockCreate(47, 8.5, EBlockType::ITEM_BLOCK_HIDDEN);

        BlockCreate(48, 12, EBlockType::HARD_BLOCK);
        BlockCreate(48, 11, EBlockType::HARD_BLOCK);
        BlockCreate(49, 12, EBlockType::HARD_BLOCK);
        BlockCreate(49, 11, EBlockType::HARD_BLOCK);
        BlockCreate(50, 12, EBlockType::HARD_BLOCK);
        BlockCreate(50, 11, EBlockType::HARD_BLOCK);

        CreateEnemy(52, 12, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_NORMAL);
        CreateEnemy(54, 12, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_NORMAL);
        CreateEnemy(56, 11, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_NORMAL);
        CreateEnemy(58, 10, 0, 0, EEnemyType::SUPER_JIEN, EEnemySubType::SUPER_JIEN_NORMAL);

        BlockCreate(56, 12, EBlockType::BRICK);
        BlockCreate(57, 12, EBlockType::BRICK);
        BlockCreate(57, 11, EBlockType::BRICK);
        BlockCreate(58, 12, EBlockType::BRICK);
        BlockCreate(58, 11, EBlockType::BRICK);
        BlockCreate(59, 10, EBlockType::BRICK);

        CreateEnemy(61, 12, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);
        CreateEnemy(63, 12, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);

        BlockCreate(67, 12, EBlockType::SA3_WHITE_SPIKE_UP);
        BlockCreate(68, 13, EBlockType::SA3_WHITE_SPIKE_UP);
        BlockCreate(68, 14, EBlockType::GROUND_BOTTOM);
        BlockCreate(69, 12, EBlockType::SA3_WHITE_SPIKE_UP);

        BlockCreate(67, 5.5, EBlockType::SA3_WHITE_SPIKE_UP);
        BlockCreate(69, 5.5, EBlockType::SA3_WHITE_SPIKE_UP);
        BlockCreate(67, 6.5, EBlockType::HARD_BLOCK);
        BlockCreate(69, 6.5, EBlockType::HARD_BLOCK);
        BlockCreate(68, 7.5, EBlockType::ITEM_BLOCK_HIDDEN);

        for(int y_pos = 12; y_pos >= 5; y_pos--)
        {
            BlockCreate(79, y_pos, EBlockType::HARD_BLOCK);
        }

        BlockCreate(70, 6.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(71, 6.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(72, 6.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(73, 6.5, EBlockType::ITEM_BLOCK_HIDDEN);



        BlockCreate(77, 6.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(78, 6.5, EBlockType::ITEM_BLOCK_HIDDEN);

        CreateEnemy(94, 12, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);

        BlockCreate(81, 9, EBlockType::ITEM_BLOCK_HIDDEN);

        ObjectCreate(92, 13, 4, 2, EObjectType::SA3_UNTOUCHABLE_FALLING_FLOOR, EObjectSubType::SA3_UNTOUCHABLE_FALLING_FLOOR_GROUND_TOP_BOTTOM);

        ObjectCreate(98, 11, 1, 2, EObjectType::CHECKPOINT, EObjectSubType::NONE);

        BlockCreate(97, 2.5, EBlockType::BRICK);
        BlockCreate(99, 2.5, EBlockType::BRICK);
        BlockCreate(98, 4.2, EBlockType::COIN);

        BlockCreate(99, -6.5, EBlockType::ITEM_BLOCK_OPEN);
        BlockCreate(99, -5.5, EBlockType::ITEM_BLOCK_OPEN);
        BlockCreate(99, -4.5, EBlockType::ITEM_BLOCK_OPEN);
        BlockCreate(99, -3.5, EBlockType::ITEM_BLOCK_OPEN);
        BlockCreate(99, -2.5, EBlockType::ITEM_BLOCK_OPEN);
        BlockCreate(99, -1.5, EBlockType::ITEM_BLOCK_OPEN);
        BlockCreate(99, 0.5, EBlockType::ITEM_BLOCK_OPEN);

        CreateEnemy(97.4, 3.9, 0, 0, EEnemyType::EVIL_CLOUD, EEnemySubType::EVIL_CLOUD_HIDDEN);

        ObjectCreate(101, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(101 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        CreateEnemy(121, 7, 0, 0, EEnemyType::CANNON_JIEN, EEnemySubType::CANNON_JIEN_SA3_GIANT);

        BlockCreate(109, 8.5, EBlockType::ITEM_BLOCK_HIDDEN);

        {
            int start = BlockCreate(103, -10.5, EBlockType::INVISIBLE_BLOCK);
            BlockCreate(103, -9.5, EBlockType::INVISIBLE_BLOCK);
            int countblocks = 2;
            for(double y_pos = 2.5; y_pos >= -8; y_pos--)
            {
                if(BlockCreate(103, y_pos, EBlockType::SA3_ITEM_BLOCK_OPEN_OVERWORLD) >= 0)
                {
                    countblocks++;
                }
            }
            if(start >= 0)
            {
                int obj_ind = ObjectCreate(108, 0, 1, 14, EObjectType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1, EObjectSubType::SA3_TRIGGER_STONE_BALL_WALL_LEVEL_1_1_WAITING);
                if(obj_ind >= 0)
                {
                    ObjectAI[obj_ind] = start;
                    ObjectVelY[obj_ind] = countblocks;
                }
            }
        }

        BlockCreate(143, 6, EBlockType::COIN);

        CreateEnemy(140, 9, 0, 0, EEnemyType::SA3_FLYING_SHELL_JIEN, EEnemySubType::NONE);

        ObjectCreate(151, 2, 1, 10.35, EObjectType::GOAL_POLE, EObjectSubType::GOAL_POLE_NEED_CASTLE);

        BlockCreate(151, 12, EBlockType::HARD_BLOCK);

        BlockCreate(147, 8.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(148, 4, EBlockType::ITEM_BLOCK_HIDDEN);

        
        CreateEnemy(159, 13, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);

        BlockCreate(160, 12, EBlockType::TRAMPOLINE, EBlockSubType::TRAMPOLINE_SYOBONKZ_STRONG);

        CreateBackground(161.9, 10, EBackgroundType::CASTLE);

        BlockCreate(162, 2.5, EBlockType::ITEM_BLOCK_HIDDEN);

        BlockCreate(162, 8, EBlockType::BRICK);
        BlockCreate(163, 8, EBlockType::BRICK);
        BlockCreate(164, 8, EBlockType::BRICK);

        BlockCreate(165, 12, EBlockType::BRICK);
        CreateEnemy(166.3, 11, 0, 0, EEnemyType::SHELL_JIEN, EEnemySubType::SHELL_JIEN_INSTANT_KICK);
        BlockCreate(167.5, 12, EBlockType::BRICK);
        BlockCreate(168.2, 12, EBlockType::ITEM_BLOCK_HIDDEN);

        BlockCreate(170, 13, EBlockType::TRAMPOLINE, EBlockSubType::TRAMPOLINE_SYOBONKZ_STRONG);

        BlockCreate(171, 12, EBlockType::HARD_BLOCK);
        BlockCreate(171, 11, EBlockType::HARD_BLOCK);

        BlockCreate(172, 10, EBlockType::INVISIBLE_BLOCK);
        BlockCreate(173, 10, EBlockType::INVISIBLE_BLOCK);
        ObjectCreate(172, 10, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(172 + GAME_X_POS_TO_DOUBLE(500), 11, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        BlockCreate(174, 12, EBlockType::HARD_BLOCK);
        BlockCreate(174, 11, EBlockType::HARD_BLOCK);
        BlockCreate(175, 12, EBlockType::HARD_BLOCK);
        BlockCreate(175, 11, EBlockType::HARD_BLOCK);

        BlockCreate(176, 12, EBlockType::HARD_BLOCK);
        BlockCreate(177, 12, EBlockType::HARD_BLOCK);
        BlockCreate(178, 12, EBlockType::HARD_BLOCK);
        BlockCreate(179, 12, EBlockType::HARD_BLOCK);
        CreateEnemy(180, 12, 0, 0, EEnemyType::JIEN, EEnemySubType::JIEN_NORMAL);
        BlockCreate(181, 12, EBlockType::HARD_BLOCK);

        CreateEnemy(182, 9, 0, 0, EEnemyType::SA3_FLYING_SHELL_JIEN, EEnemySubType::NONE);
        CreateEnemy(183.5, 9, 0, 0, EEnemyType::SA3_FLYING_SHELL_JIEN, EEnemySubType::NONE);
        CreateEnemy(184.8, 9, 0, 0, EEnemyType::SA3_FLYING_SHELL_JIEN, EEnemySubType::NONE);
        CreateEnemy(186, 9, 0, 0, EEnemyType::SA3_FLYING_SHELL_JIEN, EEnemySubType::NONE);

        CreateBackground(182, 13.7, EBackgroundType::LAVA);
        CreateBackground(185, 13.7, EBackgroundType::LAVA);

        BlockCreate(190, 13, EBlockType::TRAMPOLINE, EBlockSubType::TRAMPOLINE_SYOBONKZ_STRONG);
        BlockCreate(195, 13, EBlockType::TRAMPOLINE, EBlockSubType::TRAMPOLINE_SYOBONKZ_STRONG);
        BlockCreate(201, 13, EBlockType::TRAMPOLINE, EBlockSubType::TRAMPOLINE_SYOBONKZ_STRONG);

        //BRICK SPAM!!!!!!!!!!!!!!!!!1111!!1!!!!
        for(int y_pos = 11; y_pos >= 8; y_pos--)
        {
            BlockCreate(192, y_pos, EBlockType::BRICK);
            BlockCreate(193, y_pos, EBlockType::BRICK);
        }

        BlockCreate(196, 11.5, EBlockType::BRICK);
        BlockCreate(196, 10.5, EBlockType::BRICK);

        for(double y_pos = 10.5; y_pos > 1; y_pos--)
        {
            if(y_pos > 2)
            {
                if(y_pos < 5)
                {
                    BlockCreate(193, y_pos, EBlockType::BRICK);
                    BlockCreate(194, y_pos, EBlockType::BRICK);
                } 
                if(y_pos < 6)
                {
                    BlockCreate(195, y_pos, EBlockType::BRICK);
                    BlockCreate(196, y_pos, EBlockType::BRICK);
                } 
                if(y_pos < 8)
                {
                    BlockCreate(197, y_pos, EBlockType::BRICK);
                } 
                BlockCreate(198, y_pos, EBlockType::BRICK);
                BlockCreate(199, y_pos, EBlockType::BRICK);
                BlockCreate(200, y_pos, EBlockType::BRICK);
            }

            BlockCreate(213, y_pos, EBlockType::BRICK);
            BlockCreate(214, y_pos, EBlockType::BRICK);
            BlockCreate(215, y_pos, EBlockType::BRICK);
        }

        BlockCreate(199, 11.5, EBlockType::ITEM_BLOCK_HIDDEN);
        BlockCreate(199, 13, EBlockType::COIN);
        BlockCreate(199, 14, EBlockType::COIN);

        ObjectCreate(202, 9, 2, 1, EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD, EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION);
        ObjectCreate(202 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        CreateEnemy(206, 14, 0, 0, EEnemyType::CANNON_JIEN, EEnemySubType::CANNON_JIEN_NORMAL);

        BlockCreate(206, 8.5, EBlockType::ITEM_BLOCK_HIDDEN);
    }
    else if (SyobonWorld == 1 && SyobonLevel == 2 && SyobonSection == 1)
    {
        scrollx = 200000;
        bgmchange(Music[1]);

        LevelType = ELevelType::OVERWORLD;

        PlayerX = DOUBLE_TO_GAME_X_POS(10.5);
        PlayerY = DOUBLE_TO_GAME_Y_POS(7);

        //Create all the ground
        for(int grounds = 0; grounds <= 100; grounds++)
        {
            BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
            BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
        }

        ObjectCreate(10, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(10 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        for(int hardblocks = 13, altitude = 12; hardblocks <= 21; hardblocks++, altitude--)
        {
            for(int y_pos = 12; y_pos >= altitude && y_pos >= 5; y_pos--)
            {
                BlockCreate(hardblocks, y_pos, EBlockType::HARD_BLOCK);
            }
        }

        ObjectCreate(31, 2, 1, 10.35, EObjectType::GOAL_POLE, EObjectSubType::GOAL_POLE_NEED_CASTLE);
        BlockCreate(31, 12, EBlockType::HARD_BLOCK);

        ObjectCreate(38, 10, 3, 3, EObjectType::GOAL_CASTLE, EObjectSubType::GOAL_CASTLE_NORMAL);
    }
}
