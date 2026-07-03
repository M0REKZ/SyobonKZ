
#include "global_vars.h"
#include "blocks.h"
#include "levels.h"
#include "main.h"
#include "entities.h"
#include "extra_graphics.h"

void stagecls()
{
	for (t = 0; t < GROUND_MAX; t++)
	{
		GroundX[t] = -9000000;
		GroundY[t] = 1;
		GroundSizeX[t] = 1;
		GroundSizeY[t] = 1;
		GroundAI[t] = 0;
		GroundType[t] = EObjectType::VERTICAL_PIPE_BODY;
		GroundSubType[t] = EObjectSubType::NONE;
	}
	// for (t=0;t<spmax;t++){spa[t]=-9000000;szyunni[t]=t;spb[t]=1;spc[t]=1;spd[t]=1;sptype[t]=0;spgtype[t]=0;}
	for (t = 0; t < BLOCK_MAX; t++)
	{
		BlockX[t] = -9000000;
		BlockY[t] = 1;
		BlockItemCount[t] = 0;
		BlockSubType[t] = EBlockSubType::NONE;
	}
	for (t = 0; t < LIFT_MAX; t++)
	{
		LiftX[t] = -9000000;
		LiftY[t] = 1;
		LiftSizeX[t] = 1;
		LiftVelY[t] = 0;
		LiftFrictionY[t] = 0;
		srmuki[t] = 0;
		sron[t] = 0;
		sree[t] = 0;
		srsok[t] = 0;
		srmove[t] = 0;
		srmovep[t] = 0;
		LiftType[t] = ELiftType::YELLOW;
	}
	// for (t=0;t<sqmax;t++){sqa[t]=-9000000;sqb[t]=1;sqc[t]=1;sqd[t]=1;sqgtype[t]=0;sqtype[t]=0;}
	// for (t=0;t<kmax;t++){ka[t]=-9000000;kmuki[t]=0;ksoka[t]=0;ksokb[t]=0;kxsoka[t]=0;kxsokb[t]=0;}
	// for (t=0;t<imax;t++){ia[t]=-9000000;ib[t]=1;ic[t]=1;id[t]=1;}
	for (t = 0; t < ENEMY_MAX; t++)
	{
		EnemyX[t] = -9000000;
		EnemyY[t] = 1;
		EnemyVelX[t] = 0;
		EnemyVelY[t] = 1;
		EnemyMovementType[t] = 0;
		EnemyType[t] = EEnemyType::BALL;
		EnemySubType[t] = EEnemySubType::NONE;
		EnemyFloatingTimer[t] = 0;
		EnemyAITimer[t] = 0;
		EnemyBlockAppearTimer[t] = 0;
		EnemyMessageTimer[t] = 0;
	}
	for (t = 0; t < ENEMY_APPEAR_MAX; t++)
	{
		EnemyAppearX[t] = -9000000;
		EnemyAppearY[t] = 1;
		EnemyAppearMustPlace[t] = 1;
		EnemyAppearTimer[t] = 0;
		EnemyAppearSubType[t] = EEnemySubType::NONE;
	}
	for (t = 0; t < EXTRA_GRAPHIC_MAX; t++)
	{
		ExtraGraphicX[t] = -9000000;
		ExtraGraphicY[t] = 1;
		ExtraGraphicVelX[t] = 1;
		ExtraGraphicVelY[t] = 1;
		ExtraGraphicType[t] = EExtraGraphicType::COIN;
	}
	for (t = 0; t < BACKGROUND_MAX; t++)
	{
		BackgroundX[t] = -9000000;
		BackgroundY[t] = 1;
		//BackgroundWidth[t] = 1;
		//BackgroundHeight[t] = 1;
		BackgroundType[t] = EDecorationType::HILL;
	}
	// for (t=0;t<cmax;t++){ca[t]=-9000000;cb[t]=1;contm[t]=0;ctype[t]=0;ce[t]=0;cf[t]=0;}
	// for (t=0;t<vmax;t++){va[t]=-9000000;vtype[t]=0;vb[t]=0;vc[t]=1;vd[t]=1;}
	// for (t=0;t<gmax;t++){ga[t]=-9000000;gx[t]=0;gstring[t]="";}

	GroundCount = 0;
	BlockCount = 0;
	EnemyCount = 0;
	EnemyAppearCount = 0;
	ExtraGraphicCount = 0;
	BackgroundCount = 0;
	// haikeitouroku();
} // stagecls()

// ステージロード (Stage Load)
void stage()
{

	// fzx=6000*100;
	scrollx = 3600 * 100;

	// byte stagedate[16][801];
	// byte stagedate2[16][801];

	// 1-レンガ,2-コイン,3-空,4-土台//5-6地面//7-隠し// (1-Brick, 2-Coin, 3-Empty, 4-Foundation // 5-6 Ground // 7-Hidden //)

	stagep();

	for (tt = 0; tt <= 1000; tt++)
	{
		for (t = 0; t <= 16; t++)
		{
			xx[10] = 0;
			if (stagedate[t][tt] >= 1 && stagedate[t][tt] <= 255)
				xx[10] = (int)stagedate[t][tt];
			xx[21] = tt * 29;
			xx[22] = t * 29 - 12;
			xx[23] = xx[10];
			if (xx[10] >= 1 && xx[10] <= 19 && xx[10] != 9)
			{
				BlockCreateLegacy(tt * 29, t * 29 - 12, (EBlockType)xx[10]);
			}
			if (xx[10] >= 20 && xx[10] <= 29)
			{
				LiftX[LiftCount] = xx[21] * 100;
				LiftY[LiftCount] = xx[22] * 100;
				LiftSizeX[LiftCount] = 3000;
				srtype[LiftCount] = 0;
				LiftCount++;
				if (LiftCount >= LIFT_MAX)
					LiftCount = 0;
			}
			if (xx[10] == 30)
			{
				GroundX[GroundCount] = xx[21] * 100;
				GroundY[GroundCount] = xx[22] * 100;
				GroundSizeX[GroundCount] = 3000;
				GroundSizeY[GroundCount] = 6000;
				GroundType[GroundCount] = EObjectType::CHECKPOINT;
				GroundCount++;
				if (GroundCount >= GROUND_MAX)
					GroundCount = 0;
			}
			if (xx[10] == 40)
			{
				GroundX[GroundCount] = xx[21] * 100;
				GroundY[GroundCount] = xx[22] * 100;
				GroundSizeX[GroundCount] = 6000;
				GroundSizeY[GroundCount] = 3000;
				GroundType[GroundCount] = EObjectType::VERTICAL_PIPE_HEAD;
				GroundCount++;
				if (GroundCount >= GROUND_MAX)
					GroundCount = 0;
			}
			if (xx[10] == 41)
			{
				GroundX[GroundCount] = xx[21] * 100 + 500;
				GroundY[GroundCount] = xx[22] * 100;
				GroundSizeX[GroundCount] = 5000;
				GroundSizeY[GroundCount] = 3000;
				GroundType[GroundCount] = EObjectType::HORIZONTAL_PIPE_BODY;
				GroundCount++;
				if (GroundCount >= GROUND_MAX)
					GroundCount = 0;
			}

			if (xx[10] == 43)
			{
				GroundX[GroundCount] = xx[21] * 100;
				GroundY[GroundCount] = xx[22] * 100 + 500;
				GroundSizeX[GroundCount] = 2900;
				GroundSizeY[GroundCount] = 5300;
				GroundType[GroundCount] = EObjectType::VERTICAL_PIPE_HEAD;
				GroundCount++;
				if (GroundCount >= GROUND_MAX)
					GroundCount = 0;
			}
			if (xx[10] == 44)
			{
				GroundX[GroundCount] = xx[21] * 100;
				GroundY[GroundCount] = xx[22] * 100 + 700;
				GroundSizeX[GroundCount] = 3900;
				GroundSizeY[GroundCount] = 5000;
				GroundType[GroundCount] = EObjectType::HORIZONTAL_PIPE_HEAD;
				GroundCount++;
				if (GroundCount >= GROUND_MAX)
					GroundCount = 0;
			}
			// これなぜかバグの原因ｗ (For some reason, this is the cause of the bug lol)
			if (xx[10] >= 50 && xx[10] <= 79)
			{
				EnemyAppearX[EnemyAppearCount] = xx[21] * 100;
				EnemyAppearY[EnemyAppearCount] = xx[22] * 100;
				EnemyAppearType[EnemyAppearCount] = (EEnemyType)(xx[23] - 50);
				EnemyAppearCount++;
				if (EnemyAppearCount >= ENEMY_APPEAR_MAX)
					EnemyAppearCount = 0;
			}

			if (xx[10] >= 80 && xx[10] <= 89)
			{
				BackgroundX[BackgroundCount] = xx[21] * 100;
				BackgroundY[BackgroundCount] = xx[22] * 100;
				BackgroundType[BackgroundCount] = (EDecorationType)(xx[23] - 80);
				BackgroundCount++;
				if (BackgroundCount >= BACKGROUND_MAX)
					BackgroundCount = 0;
			}
			// コイン (Coin)
			if (xx[10] == 9)
			{
				BlockCreateLegacy(tt * 29, t * 29 - 12, EBlockType::COIN);
			}
			if (xx[10] == 99)
			{
				GroundX[GroundCount] = xx[21] * 100;
				GroundY[GroundCount] = xx[22] * 100;
				GroundSizeX[GroundCount] = 3000;
				GroundSizeY[GroundCount] = (12 - t) * 3000;
				GroundType[GroundCount] = EObjectType::GOAL_POLE;
				GroundCount++;
				if (GroundCount >= GROUND_MAX)
					GroundCount = 0;
			}
		}
	}

	if (CurrentPlayerCheckpoint >= 1)
	{
		xx[17] = 0;
		for (t = 0; t < GROUND_MAX; t++)
		{
			if (GroundType[t] == EObjectType::CHECKPOINT && CurrentPlayerCheckpoint >= 1)
			{
				fx = GroundX[t] - fxmax / 2;
				fzx = fx;
				PlayerX = GroundX[t] - fx;
				PlayerY = GroundY[t] - fy;
				CurrentPlayerCheckpoint--;
				xx[17]++;

				GroundX[t] = -80000000;
			}
		}
		CurrentPlayerCheckpoint += xx[17];
	}
	// BlockCreate(1,2,3);

} // stage()

void stagep()
{

	// ステージロード
	// void stage(){

	// fzx=6000*100;
	scrollx = 3600 * 100;

	// byte stagedate[16][801];
	// byte stagedate2[16][801];

	// 1-レンガ,2-コイン,3-空,4-土台//5-6地面//7-隠し//

	if (currentGame == ESyobonActionGame::SYOBON_ACTION_1_AND_2)
	{
		HandleSyobonActionOneLevels();
		HandleSyobonActionTwoLevels();
	}
	else if (currentGame == ESyobonActionGame::SYOBON_ACTION_3)
	{
		HandleSyobonActionThreeLevels();
	}

} // stagep

void HandleSyobonActionOneLevels()
{
    if(SyobonState == ESyobonState::TITLE)
    {
        scrollx = 0;

        PlayerX = (2 * 30) * 100;
        PlayerY = (12 * 29 - 12 - 6) * 100;

        for(int grounds = 0; grounds < 20; grounds++)
        {
            BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
            BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
        }

        CreateBackground(GAME_X_POS_TO_DOUBLE(6 * 30 * 100), 12, EDecorationType::GRASS);
        CreateBackground(GAME_X_POS_TO_DOUBLE(12 * 30 * 100), 10, EDecorationType::HILL);

        return;
    }
    // 1-1
    if (SyobonWorld == 1 && SyobonLevel == 1 && SyobonSection == 0)
    {
        bgmchange(Music[1]);
        // new byte stagedate[16][801]={

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
             NONE, NONE, NONE, NONE, NONE, NONE, BALL, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
             NONE, NONE, BALL, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
            HORIZONTAL_PIPE_BODY, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,HARD_BLOCK,HARD_BLOCK, NONE, NONE,
             NONE,HARD_BLOCK,HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE,HORIZONTAL_PIPE_BODY, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,VERTICAL_PIPE_HEAD, NONE, NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BALL, NONE, NONE, NONE, NONE, NONE, BALL, NONE,
             NONE,GRASS,
            HORIZONTAL_PIPE_BODY, NONE,
             NONE, NONE, NONE, NONE,GRASS, STAGEDATE_98, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE,
             NONE, NONE,GRASS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BALL,
             NONE, BALL,
             NONE, NONE,
             BALL_SHELLED, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,GRASS, NONE, NONE, NONE,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK, NONE,
             NONE, NONE,
            HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,HORIZONTAL_PIPE_BODY, NONE, NONE, NONE, NONE, NONE, BALL, NONE, BALL, NONE,
             NONE,HORIZONTAL_PIPE_BODY,
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
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_BALL_NORMAL;
        BlockCreateLegacy(14 * 29, 5 * 29 - 12, EBlockType::ITEM_BLOCK_ENEMY);
        BlockCreateLegacy(35 * 29, 8 * 29 - 12, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(47 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_MUSHROOM_2);
        BlockCreateLegacy(59 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_COINS);
        BlockCreateLegacy(67 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_STAR);

        GroundCount = 0;
        t = GroundCount;
        GroundX[t] = 20 * 29 * 100 + 500;
        GroundY[t] = -6000;
        GroundSizeX[t] = 5000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_SEAL_UP;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 54 * 29 * 100 - 500;
        GroundY[t] = -6000;
        GroundSizeX[t] = 7000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_SEAL_DOWN;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 112 * 29 * 100 + 1000;
        GroundY[t] = -6000;
        GroundSizeX[t] = 3000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 117 * 29 * 100;
        GroundY[t] = (2 * 29 - 12) * 100 - 1500;
        GroundSizeX[t] = 15000;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::TRIGGER_LASER;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 125 * 29 * 100;
        GroundY[t] = -6000;
        GroundSizeX[t] = 9000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_SEAL_DOWN;
        GroundCount++;
        // t=sco;sa[t]=77*29*100;sb[t]=(6*29-12)*100-1500;sc[t]=12000;sd[t]=3000;stype[t]=103;sco++;
        t = 28;
        GroundX[t] = 29 * 29 * 100 + 500;
        GroundY[t] = (9 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 12000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 49 * 29 * 100;
        GroundY[t] = (5 * 29 - 12) * 100;
        GroundSizeX[t] = 9000 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_BLOCKS;
        GroundAI[t] = 0;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 72 * 29 * 100;
        GroundY[t] = (13 * 29 - 12) * 100;
        GroundSizeX[t] = 3000 * 5 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_FLOOR;
        GroundCount++;

        EnemyAppearCount = 0;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 27 * 29 * 100;
        EnemyAppearY[t] = (9 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::BALL;
        EnemyAppearSubType[t] = EEnemySubType::BALL_UNSTOMPABLE; //+KZ: In Syobon Action by Chiku you can not stomp this enemy
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
                stagedate[t][tt] = ELegacyStageDate::NONE;
                stagedate[t][tt] = stagedatex[t][tt];
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
                HORIZONTAL_PIPE_HEAD,
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
        GroundCount = 0;
        t = GroundCount;
        GroundX[t] = 14 * 29 * 100 + 500;
        GroundY[t] = (9 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 12000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 12 * 29 * 100;
        GroundY[t] = (11 * 29 - 12) * 100;
        GroundSizeX[t] = 3000;
        GroundSizeY[t] = 6000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_KILL_PLAYER_CANNON;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 14 * 29 * 100 + 1000;
        GroundY[t] = -6000;
        GroundSizeX[t] = 5000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_SEAL_UP;
        GroundSubType[t] = EObjectSubType::TRIGGER_SEAL_UP_LEVEL_1_2;
        GroundCount++;

        // ブロックもどき
        // t=bco;ba[t]=7*29*100;bb[t]=(9*29-12)*100;btype[t]=82;bxtype[t]=0;bco++;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
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
        StageColor = ELevelType::UNDERGROUND;

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
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, STAGEDATE_97, HORIZONTAL_PIPE_HEAD,NONE,NONE,
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
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,NONE,NONE,BALL_SPIKY,NONE,BRICK,
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
            NONE,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE, BALL_SHELLED,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
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
            {BRICK,NONE, ITEM_BLOCK_HIDDEN,NONE,NONE,NONE,NONE,NONE,NONE,NONE, BALL,NONE, BALL,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,
            HARD_BLOCK,NONE,
            HARD_BLOCK,NONE,
             BALL,NONE,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE, BALL, BALL, BALL,
             ITEM_BLOCK_HIDDEN,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, HORIZONTAL_PIPE_BODY,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
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

        GroundCount = 0;
        t = GroundCount;
        GroundX[t] = 2 * 29 * 100;
        GroundY[t] = (13 * 29 - 12) * 100;
        GroundSizeX[t] = 3000 * 1 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_FLOOR;
        GroundCount++;
        // t=sco;sa[t]=19*29*100;sb[t]=(13*29-12)*100;sc[t]=3000*1-1;sd[t]=3000;stype[t]=52;sco++;
        t = GroundCount;
        GroundX[t] = 24 * 29 * 100;
        GroundY[t] = (13 * 29 - 12) * 100;
        GroundSizeX[t] = 3000 * 1 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_FLOOR;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 43 * 29 * 100 + 500;
        GroundY[t] = -6000;
        GroundSizeX[t] = 3000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_BALL_SPIKY_JUMP;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 53 * 29 * 100 + 500;
        GroundY[t] = -6000;
        GroundSizeX[t] = 3000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_FIRST_KUMA;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 129 * 29 * 100;
        GroundY[t] = (7 * 29 - 12) * 100;
        GroundSizeX[t] = 3000;
        GroundSizeY[t] = 6000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_GO_NEXT_SECTION;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 154 * 29 * 100;
        GroundY[t] = 3000;
        GroundSizeX[t] = 9000;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_WARP_ZONE;
        GroundCount++;

        // ブロックもどき

        t = 27;
        GroundX[t] = 69 * 29 * 100;
        GroundY[t] = (1 * 29 - 12) * 100;
        GroundSizeX[t] = 9000 * 2 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_BLOCKS;
        GroundSubType[t] = EObjectSubType::FALLING_BLOCKS_OVERWORLD_BRICK;
        GroundAI[t] = 0;
        GroundCount++;
        t = 28;
        GroundX[t] = 66 * 29 * 100;
        GroundY[t] = (1 * 29 - 12) * 100;
        GroundSizeX[t] = 9000 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_BLOCKS;
        GroundSubType[t] = EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK;
        GroundAI[t] = 0;
        GroundCount++;
        t = 29;
        GroundX[t] = 66 * 29 * 100;
        GroundY[t] = (-2 * 29 - 12) * 100;
        GroundSizeX[t] = 9000 * 3 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_BLOCKS;
        GroundSubType[t] = EObjectSubType::FALLING_BLOCKS_UNDERGROUND_BRICK_LEVEL_1_2;
        GroundAI[t] = 0;
        GroundCount++;

        // 26 ファイアー土管
        t = 26;
        GroundX[t] = 103 * 29 * 100 - 1500;
        GroundY[t] = (9 * 29 - 12) * 100 - 2000;
        GroundSizeX[t] = 3000;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::TRIGGER_LAVA_SPAWNER;
        GroundSubType[t] = EObjectSubType::NONE;
        GroundVelY[t] = 0;
        GroundAI[t] = 48;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 102 * 29 * 100;
        GroundY[t] = (9 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 12000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_LAVA;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 123 * 29 * 100;
        GroundY[t] = (9 * 29 - 12) * 100;
        GroundSizeX[t] = 3000 * 5 - 1;
        GroundSizeY[t] = 3000 * 5;
        GroundType[t] = EObjectType::FALLING_FLOOR;
        GroundSubType[t] = EObjectSubType::FALLING_FLOOR_BRICK;
        GroundCount++;

        t = GroundCount;
        GroundX[t] = 131 * 29 * 100;
        GroundY[t] = (1 * 29 - 12) * 100;
        GroundSizeX[t] = 4700;
        GroundSizeY[t] = 3000 * 8 - 700;
        GroundType[t] = EObjectType::VERTICAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::NONE;
        GroundCount++;

        // t=sco;sa[t]=44*29*100;sb[t]=-6000;sc[t]=9000;sd[t]=70000;stype[t]=102;sco++;

        // オワタゾーン
        t = GroundCount;
        GroundX[t] = 143 * 29 * 100;
        GroundY[t] = (9 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 12000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_WARP_ZONE;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 148 * 29 * 100;
        GroundY[t] = (9 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 12000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_WARP_ZONE;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 153 * 29 * 100;
        GroundY[t] = (9 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 12000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_KILL_PLAYER_WARP_ZONE;
        GroundCount++;

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
        srtype[t] = 0;
        sracttype[t] = 5;
        LiftVelY[t] = -300;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 111 * 29 * 100;
        LiftY[t] = (0 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        srtype[t] = 0;
        sracttype[t] = 5;
        LiftVelY[t] = -300;
        LiftCount++;
        t = 10;
        LiftX[t] = 116 * 29 * 100;
        LiftY[t] = (4 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        srtype[t] = 1;
        sracttype[t] = 5;
        LiftVelY[t] = 300;
        LiftCount++;
        t = 11;
        LiftX[t] = 116 * 29 * 100;
        LiftY[t] = (12 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        srtype[t] = 1;
        sracttype[t] = 5;
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
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
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
                HORIZONTAL_PIPE_BODY,
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

        t = GroundCount;
        GroundX[t] = 5 * 29 * 100 + 500;
        GroundY[t] = -6000;
        GroundSizeX[t] = 3000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_THIRD_KUMA;
        GroundCount++;
        // 空飛ぶ土管
        t = 28;
        GroundX[t] = 44 * 29 * 100 + 500;
        GroundY[t] = (10 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 9000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundCount++;

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
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
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
                                     NONE,NONE,NONE,NONE,BALL_ROCKET,NONE,NONE,NONE,CLOUD_SMALL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,CLOUD_SMALL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE},
                                     {NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
                                     NONE,NONE,NONE,
                                     NONE,NONE,
                                     NONE,NONE,NONE,BALL_SPIKY,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
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
                                     NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, BALL_SHELLED,NONE,NONE,NONE,CLOUD_SMALL,
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
                                     NONE,NONE,NONE,NONE,BALL_ROCKET,NONE,NONE,NONE,NONE,NONE,NONE,NONE,STAGEDATE_97,NONE,NONE,NONE,NONE,NONE,
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
                                     NONE,BALL,NONE,BALL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
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
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_BALL_SPIKY_NORMAL;
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
        EnemyAppearType[t] = EEnemyType::BALL_SPIKY;
        EnemyAppearSubType[t] = EEnemySubType::BALL_SPIKY_JUMPER;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 146 * 29 * 100;
        EnemyAppearY[t] = (10 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::DEFRAG;
        EnemyAppearSubType[t] = EEnemySubType::DEFRAG_GRAB_POLE;
        EnemyAppearCount++;

        t = GroundCount;
        GroundX[t] = 9 * 29 * 100;
        GroundY[t] = (13 * 29 - 12) * 100;
        GroundSizeX[t] = 9000 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_FLOOR;
        GroundCount++;
        // t=sco;sa[t]=58*29*100;sb[t]=(13*29-12)*100;sc[t]=9000-1;sd[t]=3000;stype[t]=52;sco++;

        // 土管
        t = GroundCount;
        GroundX[t] = 65 * 29 * 100 + 500;
        GroundY[t] = (10 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 9000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        GroundCount++;
        // t=28;sa[t]=65*29*100;sb[t]=(10*29-12)*100;sc[t]=6000;sd[t]=9000-200;stype[t]=50;sco++;

        // トラップ
        t = GroundCount;
        GroundX[t] = 74 * 29 * 100;
        GroundY[t] = (8 * 29 - 12) * 100 - 1500;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::TRIGGER_LASER;
        GroundSubType[t] = EObjectSubType::TRIGGER_LASER_LEVEL_1_3;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 96 * 29 * 100 - 3000;
        GroundY[t] = -6000;
        GroundSizeX[t] = 9000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SEAL_DOWN;
        GroundCount++;
        // ポール砲
        t = GroundCount;
        GroundX[t] = 131 * 29 * 100 - 1500;
        GroundY[t] = (1 * 29 - 12) * 100 - 3000;
        GroundSizeX[t] = 15000;
        GroundSizeY[t] = 14000;
        GroundType[t] = EObjectType::TRIGGER_MULTI_LASER;
        GroundCount++;

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
        srtype[t] = 0;
        sracttype[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::BREAKING;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 39 * 29 * 100 - 2000;
        LiftY[t] = (6 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        srtype[t] = 0;
        sracttype[t] = 1;
        LiftVelY[t] = 0;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 45 * 29 * 100 + 1500;
        LiftY[t] = (10 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        srtype[t] = 0;
        sracttype[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PUSH_LEFT;
        LiftCount++;

        t = LiftCount;
        LiftX[t] = 95 * 29 * 100;
        LiftY[t] = (7 * 29 - 12) * 100;
        LiftSizeX[t] = 180 * 100;
        srtype[t] = 0;
        sracttype[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PILLAR;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 104 * 29 * 100;
        LiftY[t] = (9 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        srtype[t] = 0;
        sracttype[t] = 0;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PILLAR_BOUNCY;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 117 * 29 * 100;
        LiftY[t] = (3 * 29 - 12) * 100;
        LiftSizeX[t] = 90 * 100;
        srtype[t] = 0;
        sracttype[t] = 1;
        LiftVelY[t] = 0;
        LiftType[t] = ELiftType::PILLAR_BRICKS;
        LiftCount++;
        t = LiftCount;
        LiftX[t] = 124 * 29 * 100;
        LiftY[t] = (5 * 29 - 12) * 100;
        LiftSizeX[t] = 210 * 100;
        srtype[t] = 0;
        sracttype[t] = 0;
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
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
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
        StageColor = ELevelType::UNDERGROUND;

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
               BALL_SPIKY,
               NONE,
               BALL_SPIKY,
               NONE,
               BALL_SPIKY,
               NONE,
               BALL_SPIKY,
               NONE,
               BALL_SPIKY,
               NONE,
               BALL_SPIKY,
               NONE,
               BALL_SPIKY,
               NONE,
               BALL_SPIKY,
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
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta3

    // 1-3(空中)
    if (SyobonWorld == 1 && SyobonLevel == 3 && SyobonSection == 5)
    {

        StageColor = ELevelType::SKY;
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

        GroundCount = 0;
        t = GroundCount;
        GroundX[t] = 14 * 29 * 100 - 5;
        GroundY[t] = (11 * 29 - 12) * 100;
        GroundSizeX[t] = 6000;
        GroundSizeY[t] = 15000 - 200;
        GroundType[t] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[t] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        GroundCount++;
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
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
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
        StageColor = ELevelType::CASTLE;

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
                                     NONE,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BALL,NONE,GROUND_TOP,NONE,NONE,
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
                                     GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,HORIZONTAL_PIPE_BODY,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
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
                                     HORIZONTAL_PIPE_BODY,NONE,
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

        GroundCount = 0; // sco=140;
        t = GroundCount;
        GroundX[t] = 35 * 29 * 100 - 1500 + 750;
        GroundY[t] = (8 * 29 - 12) * 100 - 1500;
        GroundSizeX[t] = 1500;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::TRIGGER_PLATFORM_SPLIT;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 67 * 29 * 100;
        GroundY[t] = (4 * 29 - 12) * 100;
        GroundSizeX[t] = 9000 - 1;
        GroundSizeY[t] = 3000 * 1 - 1;
        GroundType[t] = EObjectType::FALLING_BLOCKS;
        GroundSubType[t] = EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP;
        GroundAI[t] = 0;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 73 * 29 * 100;
        GroundY[t] = (13 * 29 - 12) * 100;
        GroundSizeX[t] = 3000 * 1 - 1;
        GroundSizeY[t] = 3000;
        GroundType[t] = EObjectType::FALLING_FLOOR;
        GroundCount++;
        // t=sco;sa[t]=79*29*100;sb[t]=(13*29-12)*100;sc[t]=30*3*100-1;sd[t]=6000-200;stype[t]=51;sxtype[t]=4;sco++;
        // t=sco;sa[t]=83*29*100;sb[t]=(-2*29-12)*100;sc[t]=30*5*100-1;sd[t]=3000-200;stype[t]=51;sxtype[t]=4;sco++;
        t = GroundCount;
        GroundX[t] = 123 * 29 * 100;
        GroundY[t] = (1 * 29 - 12) * 100;
        GroundSizeX[t] = 30 * 6 * 100 - 1 + 0;
        GroundSizeY[t] = 3000 - 200;
        GroundType[t] = EObjectType::FALLING_BLOCKS;
        GroundSubType[t] = EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP_X_ONLY;
        GroundCount++;
        // スクロール消し
        t = GroundCount;
        GroundX[t] = 124 * 29 * 100 + 3000;
        GroundY[t] = (2 * 29 - 12) * 100;
        GroundSizeX[t] = 3000 * 1 - 1;
        GroundSizeY[t] = 300000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SCROLLING_OFF;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 148 * 29 * 100 + 1000;
        GroundY[t] = (-12 * 29 - 12) * 100;
        GroundSizeX[t] = 3000 * 1 - 1;
        GroundSizeY[t] = 300000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_CLEAR_GAME;
        GroundCount++;

        // 3連星
        t = GroundCount;
        GroundX[t] = 100 * 29 * 100 + 1000;
        GroundY[t] = -6000;
        GroundSizeX[t] = 3000;
        GroundSizeY[t] = 70000;
        GroundType[t] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SURPRISE_MAGMA;
        GroundCount++;

        // 地面1
        t = GroundCount;
        GroundX[t] = 0 * 29 * 100 - 0;
        GroundY[t] = 9 * 29 * 100 + 1700;
        GroundSizeX[t] = 3000 * 7 - 1;
        GroundSizeY[t] = 3000 * 5 - 1;
        GroundType[t] = EObjectType::CASTLE_BRICKS;
        GroundSubType[t] = EObjectSubType::NONE;
        GroundCount++;
        t = GroundCount;
        GroundX[t] = 11 * 29 * 100;
        GroundY[t] = -1 * 29 * 100 + 1700;
        GroundSizeX[t] = 3000 * 8 - 1;
        GroundSizeY[t] = 3000 * 4 - 1;
        GroundType[t] = EObjectType::CASTLE_BRICKS;
        GroundSubType[t] = EObjectSubType::NONE;
        GroundCount++;

        EnemyAppearCount = 0;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 8 * 29 * 100 - 1400;
        EnemyAppearY[t] = (2 * 29 - 12) * 100 + 500;
        EnemyAppearType[t] = EEnemyType::FALLING_CAT;
        EnemyAppearSubType[t] = EEnemySubType::NONE;
        EnemyAppearCount++;
        t = EnemyAppearCount;
        EnemyAppearX[t] = 42 * 29 * 100 - 1400;
        EnemyAppearY[t] = (-2 * 29 - 12) * 100 + 500;
        EnemyAppearType[t] = EEnemyType::FALLING_CAT;
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

        // ステルスうめぇ
        t = EnemyAppearCount;
        EnemyAppearX[t] = 57 * 29 * 100;
        EnemyAppearY[t] = (2 * 29 - 12 + 10) * 100 - 500;
        EnemyAppearType[t] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[t] = EEnemySubType::EVIL_CLOUD_HIDDEN;
        EnemyAppearCount++;
        // ブロックもどき
        t = EnemyAppearCount;
        EnemyAppearX[t] = 77 * 29 * 100;
        EnemyAppearY[t] = (5 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[t] = EEnemySubType::SPIKY_BLOCK_MESSAGE_BLOCK;
        EnemyAppearCount++;
        // ボス
        t = EnemyAppearCount;
        EnemyAppearX[t] = 130 * 29 * 100;
        EnemyAppearY[t] = (8 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::MOLALLA;
        EnemyAppearSubType[t] = EEnemySubType::MOLALLA_ALIVE;
        EnemyAppearCount++;
        // クックル
        t = EnemyAppearCount;
        EnemyAppearX[t] = 142 * 29 * 100;
        EnemyAppearY[t] = (10 * 29 - 12) * 100;
        EnemyAppearType[t] = EEnemyType::KUKURRU;
        EnemyAppearSubType[t] = EEnemySubType::NONE;
        EnemyAppearCount++;

        // マグマ
        BackgroundCount = 0;
        BackgroundX[BackgroundCount] = 7 * 29 * 100 - 300;
        BackgroundY[BackgroundCount] = 14 * 29 * 100 - 1200;
        BackgroundType[BackgroundCount] = EDecorationType::LAVA;
        BackgroundCount++;
        if (BackgroundCount >= BACKGROUND_MAX)
            BackgroundCount = 0;
        BackgroundX[BackgroundCount] = 41 * 29 * 100 - 300;
        BackgroundY[BackgroundCount] = 14 * 29 * 100 - 1200;
        BackgroundType[BackgroundCount] = EDecorationType::LAVA;
        BackgroundCount++;
        if (BackgroundCount >= BACKGROUND_MAX)
            BackgroundCount = 0;
        BackgroundX[BackgroundCount] = 149 * 29 * 100 - 1100;
        BackgroundY[BackgroundCount] = 10 * 29 * 100 - 600;
        BackgroundType[BackgroundCount] = EDecorationType::TEXT_51;
        BackgroundCount++;
        if (BackgroundCount >= BACKGROUND_MAX)
            BackgroundCount = 0;

        BlockCount = 0;
        // ON-OFFブロック
        BlockSubType[BlockCount] = EBlockSubType::ON_BLOCK_LOCKED;
        BlockCreateLegacy(29 * 29, 3 * 29 - 12, EBlockType::ON_BLOCK);
        // 1-2
        BlockCreateLegacy(34 * 29, 9 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCreateLegacy(35 * 29, 9 * 29 - 12, EBlockType::GROUND_TOP);
        // 隠し
        BlockCreateLegacy(55 * 29 + 15, 6 * 29 - 12, EBlockType::ITEM_BLOCK_HIDDEN);
        // BlockCreate(62*29,9*29-12,2);
        // 隠しON-OFF
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_FIREBAR_SWITCH;
        BlockCreateLegacy(50 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_TRAP_HIDDEN);
        // ヒント3
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_1_4_0;
        BlockCreateLegacy(1 * 29, 5 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        // ファイア
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_BURNING_FLOWER;
        BlockCreateLegacy(86 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_ENEMY);
        // キノコなし　普通
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
        srtype[t] = 0;
        sracttype[t] = 1;
        LiftVelY[t] = 0;
        LiftCount++;
        t = 20;
        LiftX[t] = 119 * 29 * 100 + 300;
        LiftY[t] = (10 * 29 - 12) * 100;
        LiftSizeX[t] = 12 * 30 * 100 + 1000;
        srtype[t] = 0;
        sracttype[t] = 0;
        LiftType[t] = ELiftType::GRAY;
        LiftVelY[t] = 0;
        LiftCount++;

        SyobonSection = 0;

        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }

    } // sta4
}

void HandleSyobonActionTwoLevels()
{
    if (SyobonWorld == 2 && SyobonLevel == 1 && SyobonSection == 0)
    { // 2-1
        PlayerX = 5600;
        PlayerY = 32000;
        bgmchange(Music[1]);
        StageColor = ELevelType::OVERWORLD;
        scrollx = 2900 * (113 - 19);
        //
        ELegacyStageDate stagedatex[17][1001] = {
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
             CLOUD,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,NONE,NONE,HARD_BLOCK,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE, CLOUD,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, GOAL_POLE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,NONE,
             CLOUD,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,
            NONE,NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,HARD_BLOCK,
            HARD_BLOCK,NONE,
            NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            HARD_BLOCK,NONE,
            NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,HARD_BLOCK,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,NONE,NONE,NONE,NONE,NONE,NONE,ITEM_BLOCK_HIDDEN,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BRICK,BRICK,BRICK,BRICK,NONE,NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,NONE,NONE,
            HARD_BLOCK,ITEM_BLOCK_HIDDEN,
            ITEM_BLOCK_HIDDEN,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,ITEM_BLOCK_COIN,ITEM_BLOCK_COIN, STAGEDATE_98,ITEM_BLOCK_COIN,HARD_BLOCK,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,SPIKE,SPIKE,SPIKE,SPIKE,NONE,NONE,SPIKE,SPIKE,
            SPIKE,SPIKE,
            HARD_BLOCK,BRICK,
            BRICK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,HARD_BLOCK,NONE,
            NONE,NONE,
            NONE,NONE,NONE,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,ITEM_BLOCK_HIDDEN,NONE,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE, STAGEDATE_98,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,ITEM_BLOCK_HIDDEN,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,
            HILL,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HILL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,HILL,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,
            NONE,NONE,NONE,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
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
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,ITEM_BLOCK_HIDDEN,
            NONE,NONE,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,NONE},
            {NONE,NONE,NONE,NONE,NONE,GRASS,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE,NONE,GRASS,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,
            NONE,NONE,
            NONE,NONE,NONE,
            GRASS,NONE,NONE,NONE,GRASS,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,BALL,NONE,NONE,BALL,
            NONE,NONE,
            BALL,GRASS,
            NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,GRASS,NONE,NONE,NONE,NONE,NONE,NONE,
            HARD_BLOCK,NONE,
            NONE,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,HARD_BLOCK,NONE,NONE,NONE,NONE,NONE,NONE,NONE,NONE,HARD_BLOCK,NONE,NONE,NONE,
            NONE,NONE,NONE,
            NONE,NONE},

            {GROUND_TOP,GROUND_TOP,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,
            NONE,NONE,NONE,
            NONE,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,
            GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_TOP,GROUND_TOP,NONE,NONE,NONE,NONE,NONE,
            GROUND_TOP,GROUND_TOP,GROUND_TOP},
            {GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,
            NONE,NONE,NONE,
            NONE,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,NONE,NONE,NONE,GROUND_BOTTOM,GROUND_BOTTOM,NONE,NONE,NONE,NONE,NONE,
            GROUND_BOTTOM,GROUND_BOTTOM,GROUND_BOTTOM},
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
            NONE,NONE,NONE}};
        // 追加情報
        BlockCount = 0;
        //
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_2_1_0_1;
        BlockCreateLegacy(1 * 29, 9 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(40 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_2_1_0_2;
        BlockCreateLegacy(79 * 29, 7 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_MUSHROOM_GROW;
        BlockCreateLegacy(83 * 29, 7 * 29 - 12, EBlockType::ITEM_BLOCK_MUSHROOM);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_TRAP_HIDDEN_NORMAL;
        BlockCreateLegacy(83 * 29, 2 * 29 - 12, EBlockType::ITEM_BLOCK_TRAP_HIDDEN);
        BlockCount += 1;
        //
        for (int i = -1; i > -7; i -= 1)
        {
            BlockCreateLegacy(85 * 29, i * 29 - 12, EBlockType::HARD_BLOCK);
            BlockCount += 1;
        }
        //
        GroundCount = 0;
        GroundX[GroundCount] = 30 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 12000 - 1;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 51 * 29 * 100;
        GroundY[GroundCount] = (4 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 9000 - 1;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::FALLING_BLOCKS;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_BLOCKS_OVERWORLD_BRICK;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 84 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 9000 - 1;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 105 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 15000 - 1;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        GroundCount += 1;
        //
        EnemyAppearCount = 0;
        //
        EnemyAppearX[EnemyAppearCount] = 6 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (3 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::EVIL_CLOUD_NORMAL;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 13 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::BALL_SPIKY;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 23 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::EVIL_CLOUD_NORMAL;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 25 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::EVIL_CLOUD_HIDDEN;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 27 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::EVIL_CLOUD_NORMAL;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 88 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (12 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }

    if (SyobonWorld == 2 && SyobonLevel == 2 && SyobonSection == 0)
    { // 2-2(地上)
        bgmchange(Music[1]);
        StageColor = ELevelType::OVERWORLD;
        scrollx = 2900 * (19 - 19);
        //
        ELegacyStageDate stagedatex[17][1001] = {
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, CLOUD, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE},
            {NONE, HILL, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}};
        //
        GroundX[GroundCount] = 14 * 29 * 100 + 200;
        GroundY[GroundCount] = -6000;
        GroundSizeX[GroundCount] = 5000;
        GroundSizeY[GroundCount] = 70000;
        GroundType[GroundCount] = EObjectType::TRIGGER_SEAL_UP;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 12 * 29 * 100 + 1200;
        GroundY[GroundCount] = -6000;
        GroundSizeX[GroundCount] = 7000;
        GroundSizeY[GroundCount] = 70000;
        GroundType[GroundCount] = EObjectType::TRIGGER_SEAL_DOWN;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 12 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 6000 - 1;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundAI[GroundCount] = 0;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 14 * 29 * 100;
        GroundY[GroundCount] = (9 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 6000;
        GroundSizeY[GroundCount] = 12000 - 200;
        GroundType[GroundCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[GroundCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        GroundCount += 1;
        //
        BlockCreateLegacy(6 * 29, 9 * 29 - 12, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }

    if (SyobonWorld == 2 && SyobonLevel == 2 && SyobonSection == 1)
    { // 2-2(地下)
        bgmchange(Music[2]);
        StageColor = ELevelType::UNDERGROUND;
        PlayerX = 7500;
        PlayerY = 9000;
        scrollx = 2900 * (137 - 19);
        //
        ELegacyStageDate stagedatex[17][1001] = {
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, STAGEDATE_98,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, STAGEDATE_98, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE,
             SPIKE, SPIKE,
             SPIKE, SPIKE,
             SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             SPIKE, SPIKE,
             SPIKE, SPIKE,
             SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, NONE, NONE, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, NONE,
             NONE, NONE,
             SPIKE, SPIKE,
             SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, NONE, NONE, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE,
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
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE,
             NONE, NONE, NONE,
             NONE, ITEM_BLOCK_HIDDEN,
             NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BALL_SHELLED, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, SPIKE, SPIKE, SPIKE, SPIKE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_OPEN, NONE, NONE,
             NONE, ITEM_BLOCK_OPEN, NONE,
             NONE, NONE,
             ITEM_BLOCK_OPEN, NONE, NONE, NONE, NONE, NONE, CHECKPOINT, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, BALL_ROCKET,
             NONE, NONE, NONE,
             NONE, NONE, BALL_ROCKET, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, BRICK, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, ITEM_BLOCK_HIDDEN,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, SPIKE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             HORIZONTAL_PIPE_HEAD, NONE,
             NONE, BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN,
             NONE, STAGEDATE_97,
             NONE, NONE, NONE,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, BRICK},
            {HARD_BLOCK, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, BRICK, BRICK, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, BRICK, NONE, NONE, NONE,
             BRICK, BRICK, BRICK,
             BRICK, BRICK,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, BRICK, BRICK, NONE, NONE, NONE, NONE, HORIZONTAL_PIPE_HEAD,
             NONE, NONE, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, BRICK, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, BRICK, NONE, NONE, NONE,
             BRICK, BRICK, BRICK,
             BRICK, BRICK,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, NONE, NONE, NONE, NONE, BRICK, BRICK, NONE, NONE, NONE, STAGEDATE_97, NONE,
             NONE, NONE, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, BRICK, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, BRICK, NONE, NONE, NONE,
             BRICK, BRICK, BRICK,
             BRICK, BRICK,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, NONE, NONE, NONE, NONE, BRICK, BRICK, NONE, NONE, NONE, BRICK, BRICK,
             BRICK, BRICK, BRICK},
            {HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, BRICK, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, BRICK, NONE, NONE, NONE,
             BRICK, BRICK, BRICK,
             BRICK, BRICK,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, NONE, NONE, NONE, NONE, BRICK, BRICK, NONE, NONE, NONE, BRICK, BRICK,
             BRICK, BRICK, BRICK},
            {GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, BRICK, NONE, NONE, NONE,
             BRICK, BRICK, BRICK,
             BRICK, BRICK,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, BRICK, BRICK, NONE, NONE, NONE, BRICK, BRICK,
             BRICK, BRICK, BRICK},
            {GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
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
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, BRICK, NONE, NONE, NONE,
             BRICK, BRICK, BRICK,
             BRICK, BRICK,
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, BRICK, BRICK, NONE, NONE, NONE, BRICK, BRICK,
             BRICK, BRICK, BRICK},
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
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE}};
        //
        EnemyAppearCount = 0;
        EnemyAppearX[EnemyAppearCount] = 32 * 29 * 100 - 1400;
        EnemyAppearY[EnemyAppearCount] = (-2 * 29 - 12) * 100 + 500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FALLING_CAT;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::NONE;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = (31 * 29 - 12) * 100;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::BALL_ROCKET;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::BALL_ROCKET_0;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 38 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 38 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 42 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 42 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 46 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 46 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 58 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 66 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 76 * 29 * 100 - 1400;
        EnemyAppearY[EnemyAppearCount] = (-2 * 29 - 12) * 100 + 500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FALLING_CAT;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::NONE;
        EnemyAppearCount += 1;
        //
        GroundCount = 0;
        GroundX[GroundCount] = 2 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 300000 - 6001;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 3 * 29 * 100;
        GroundY[GroundCount] = (7 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 3000;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::TRIGGER_PLATFORM_SPLIT;
        GroundSubType[GroundCount] = (EObjectSubType)0; //this is a timer
        GroundCount += 1;
        //
        GroundX[GroundCount] = 107 * 29 * 100;
        GroundY[GroundCount] = (9 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 9000 - 1;
        GroundSizeY[GroundCount] = 24000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_BRICK;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 111 * 29 * 100;
        GroundY[GroundCount] = (7 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 3000;
        GroundSizeY[GroundCount] = 6000 - 200;
        GroundType[GroundCount] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        GroundSubType[GroundCount] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_KILL_PLAYER_CANNON;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 113 * 29 * 100 + 1100;
        GroundY[GroundCount] = (0 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 4700;
        GroundSizeY[GroundCount] = 27000 - 1000;
        GroundType[GroundCount] = EObjectType::VERTICAL_PIPE_BODY;
        GroundSubType[GroundCount] = EObjectSubType::NONE;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 128 * 29 * 100;
        GroundY[GroundCount] = (9 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 9000 - 1;
        GroundSizeY[GroundCount] = 24000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_BRICK;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 131 * 29 * 100;
        GroundY[GroundCount] = (9 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 3000;
        GroundSizeY[GroundCount] = 6000 - 200;
        GroundType[GroundCount] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        GroundSubType[GroundCount] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_GO_NEXT_SECTION;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 133 * 29 * 100 + 1100;
        GroundY[GroundCount] = (0 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 4700;
        GroundSizeY[GroundCount] = 32000;
        GroundType[GroundCount] = EObjectType::VERTICAL_PIPE_BODY;
        GroundSubType[GroundCount] = EObjectSubType::NONE;
        GroundCount += 1;
        //
        BlockCount = 0;
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(0 * 29, 0 * 29 - 12, EBlockType::HARD_BLOCK);
        BlockCount = 1;
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(2 * 29, 9 * 29 - 12, EBlockType::HARD_BLOCK);
        BlockCount = 2;
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(3 * 29, 9 * 29 - 12, EBlockType::HARD_BLOCK);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(5 * 29, 9 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(6 * 29, 9 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(5 * 29, 10 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(6 * 29, 10 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(5 * 29, 11 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(6 * 29, 11 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(5 * 29, 12 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(6 * 29, 12 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(70 * 29, 7 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(71 * 29, 7 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }

    if (SyobonWorld == 2 && SyobonLevel == 2 && SyobonSection == 2)
    { // 2-2 地上
        //
        bgmchange(Music[1]);
        StageColor = ELevelType::OVERWORLD;
        scrollx = 2900 * (36 - 19);
        PlayerX = 7500;
        PlayerY = 3000 * 9;
        //
        ELegacyStageDate stagedatex[17][1001] = {
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, CLOUD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, GOAL_POLE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BALL,
             BALL_SHELLED, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BALL, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, VERTICAL_PIPE_HEAD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, HORIZONTAL_PIPE_BODY, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE,
             NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, BALL_SPIKY, NONE, NONE},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             NONE, NONE,
             NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
             GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
             NONE, NONE,
             NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}};
        //
        EnemyAppearCount = 0;
        EnemyAppearX[EnemyAppearCount] = 9 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (12 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 10 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (11 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 11 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (10 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 12 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (9 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 13 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (8 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 14 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 15 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 16 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (5 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 17 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (5 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 18 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (5 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 19 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (5 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 20 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (5 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }
    //
    if (SyobonWorld == 2 && SyobonLevel == 3 && SyobonSection == 0)
    { // 2-3
        PlayerX = 7500;
        PlayerY = 3000 * 8;
        bgmchange(Music[1]);
        StageColor = ELevelType::OVERWORLD;
        scrollx = 2900 * (126 - 19);
        //
        ELegacyStageDate stagedatex[17][1001] = {
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             CLOUD, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE,
             NONE, NONE, NONE,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, CLOUD, NONE, NONE,
             NONE, NONE,
             NONE, NONE,
             DEFRAG, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE,
             SPIKE, SPIKE,
             SPIKE,
             SPIKE, SPIKE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, GOAL_POLE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, NONE, BALL_SHELLED, NONE, BRICK, NONE,
             NONE, NONE,
             NONE, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, CLOUD, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, CLOUD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             BALL, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, BRICK, NONE, NONE, NONE, BRICK,
             ITEM_BLOCK_HIDDEN, NONE, NONE,
             NONE, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, SPIKE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, BALL_SPIKY, NONE,
             BALL_SPIKY, NONE, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, SUPER_BOON, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             ITEM_BLOCK_HIDDEN, HARD_BLOCK,
             ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, SUPER_BOON, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, SHELL, NONE, NONE, NONE, NONE, HARD_BLOCK, BRICK, BRICK, BRICK, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, SPIKE, SPIKE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, ITEM_BLOCK_HIDDEN,
             NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, CHECKPOINT, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, ITEM_BLOCK_OPEN,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, BRICK, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
             GROUND_BOTTOM, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, HARD_BLOCK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_BOTTOM, GROUND_BOTTOM, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM},
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
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}};
        //
        BlockCount = 0;
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        for (int i = -1; i > -7; i -= 1)
        {
            BlockCreateLegacy(55 * 29, i * 29 - 12, EBlockType::HARD_BLOCK);
            BlockCount += 1;
        }
        //
        BlockSubType[BlockCount] = EBlockSubType::TRAMPOLINE_VISIBLE;
        BlockCreateLegacy(64 * 29, 12 * 29 - 12, EBlockType::TRAMPOLINE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(66 * 29, 3 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(67 * 29, 3 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(68 * 29, 3 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_2_3_0;
        BlockCreateLegacy(60 * 29, 6 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        BlockCount += 1;
        
        EnemyAppearCount = 1;
        EnemyAppearX[EnemyAppearCount]=(54*29-12)*100;
        EnemyAppearY[EnemyAppearCount]=(1*29-12)*100;
        EnemyAppearType[EnemyAppearCount]= EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount]= EEnemySubType::EVIL_CLOUD_NORMAL;
        EnemyAppearCount += 1;
        
        GroundCount = 0;
        EnemyAppearX[GroundCount] = (102 * 29 - 12) * 100;
        EnemyAppearY[GroundCount] = (10 * 29 - 12) * 100;
        EnemyAppearType[GroundCount] = EEnemyType::UNKNOWN_ID_50;
        EnemyAppearSubType[GroundCount] = EEnemySubType::UNKNOWN_ID_50_1;
        GroundCount += 1;
        //
        LiftCount = 0;
        LiftX[LiftCount] = 1 * 29 * 100;
        LiftY[LiftCount] = (10 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 5 * 3000;
        srtype[LiftCount] = 0;
        sracttype[LiftCount] = 1;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR;
        LiftCount++;
        //
        LiftX[LiftCount] = 18 * 29 * 100;
        LiftY[LiftCount] = (4 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 3 * 3000;
        srtype[LiftCount] = 0;
        sracttype[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR;
        LiftCount++;
        //
        LiftX[LiftCount] = 35 * 29 * 100;
        LiftY[LiftCount] = (4 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 5 * 3000;
        srtype[LiftCount] = 0;
        sracttype[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR;
        LiftCount++;
        //
        LiftX[LiftCount] = 35 * 29 * 100;
        LiftY[LiftCount] = (8 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 5 * 3000;
        srtype[LiftCount] = 0;
        sracttype[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR;
        LiftCount++;
        //
        LiftX[LiftCount] = 94 * 29 * 100;
        LiftY[LiftCount] = (6 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 3 * 3000;
        srtype[LiftCount] = 0;
        sracttype[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::BREAKING;
        LiftCount++;
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }
    //
    if (SyobonWorld == 2 && SyobonLevel == 4 && (SyobonSection == 0 || SyobonSection == 10 || SyobonSection == 12))
    { // 2-4(1番)
        if (SyobonSection == 0)
        {
            PlayerX = 7500;
            PlayerY = 3000 * 4;
        }
        else
        {
            PlayerX = 19500;
            PlayerY = 3000 * 11;
            SyobonSection = 0;
        }
        bgmchange(Music[4]);
        StageColor = ELevelType::CASTLE;
        scrollx = 2900 * (40 - 19);
        //
        ELegacyStageDate stagedatex[17][1001] = {
            {GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, SPIKE,
             NONE, NONE,
             NONE, SPIKE,
             SPIKE, SPIKE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, SPIKE, SPIKE, SPIKE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, ITEM_BLOCK_HIDDEN,
             ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_OPEN,
             ITEM_BLOCK_HIDDEN, NONE,
             ITEM_BLOCK_HIDDEN, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, SUPER_BOON, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, MAGMA, MAGMA, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
             NONE, NONE,
             NONE, NONE,
             NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, MAGMA, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, VERTICAL_PIPE_HEAD, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, MAGMA, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, LAVA, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, HORIZONTAL_PIPE_BODY, NONE, GROUND_TOP, LAVA, NONE, NONE, LAVA, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             LAVA, NONE,
             NONE, LAVA,
             NONE, NONE, LAVA, GROUND_TOP, NONE, LAVA, GROUND_TOP, GROUND_TOP, GROUND_TOP, LAVA, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, MAGMA, MAGMA, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, MAGMA, NONE, NONE, NONE, NONE, NONE}};
        //
        BlockCount = 0;
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(0 * 29, -1 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(4 * 29, -1 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(1 * 29, 14 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(6 * 29, 14 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(7 * 29, 14 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCount += 1;
        //
        EnemyAppearCount = 0;
        EnemyAppearX[EnemyAppearCount] = 2 * 29 * 100 - 1400;
        EnemyAppearY[EnemyAppearCount] = (-2 * 29 - 12) * 100 + 500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FALLING_CAT;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::NONE;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 20 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (5 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        GroundCount = 0;
        GroundX[GroundCount] = 17 * 29 * 100;
        GroundY[GroundCount] = (9 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 21000 - 1;
        GroundSizeY[GroundCount] = 3000 - 1;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 27 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 6000;
        GroundSizeY[GroundCount] = 6000;
        GroundType[GroundCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[GroundCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_PLUS_10_SECTION;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 34 * 29 * 100;
        GroundY[GroundCount] = (5 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 6000;
        GroundSizeY[GroundCount] = 30000;
        GroundType[GroundCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[GroundCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        GroundCount += 1;
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }

    if (SyobonWorld == 2 && SyobonLevel == 4 && SyobonSection == 1)
    { // 2-4(2番)
        PlayerX = 4500;
        PlayerY = 3000 * 11;
        bgmchange(Music[4]);
        StageColor = ELevelType::CASTLE;
        scrollx = 2900 * (21 - 19);
        //
        ELegacyStageDate stagedatex[17][1001] = {
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             STAGEDATE_98},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {NONE, SPIKE, SPIKE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE},
            {NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, HORIZONTAL_PIPE_HEAD, NONE,
             NONE},
            {NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, STAGEDATE_97, NONE, NONE,
             NONE},
            {NONE, VERTICAL_PIPE_HEAD, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP},
            {LAVA, HORIZONTAL_PIPE_BODY, NONE, LAVA, NONE, GROUND_TOP, LAVA, NONE, NONE, LAVA, NONE, GROUND_TOP, LAVA, NONE, NONE, LAVA,
             NONE, NONE,
             LAVA},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}};
        //
        BlockCount = 0;
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(12 * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(13 * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(14 * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        GroundCount = 0;
        GroundX[GroundCount] = 6 * 29 * 100;
        GroundY[GroundCount] = (6 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 18000 - 1;
        GroundSizeY[GroundCount] = 6000 - 1;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 12 * 29 * 100;
        GroundY[GroundCount] = (8 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 9000 - 1;
        GroundSizeY[GroundCount] = 3000 - 1;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 15 * 29 * 100;
        GroundY[GroundCount] = (11 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 3000;
        GroundSizeY[GroundCount] = 6000;
        GroundType[GroundCount] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        GroundSubType[GroundCount] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_GO_NEXT_SECTION;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 17 * 29 * 100 + 1100;
        GroundY[GroundCount] = (0 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 4700;
        GroundSizeY[GroundCount] = 38000;
        GroundType[GroundCount] = EObjectType::VERTICAL_PIPE_BODY;
        GroundSubType[GroundCount] = EObjectSubType::NONE;
        GroundCount += 1;
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }

    if (SyobonWorld == 2 && SyobonLevel == 4 && SyobonSection == 2)
    { // 2-4(3番)
        PlayerX = 4500;
        PlayerY = 3000 * 11;
        bgmchange(Music[4]); // 6
        StageColor = ELevelType::CASTLE;
        scrollx = 2900 * (128 - 19);
        //
        ELegacyStageDate stagedatex[17][1001] = {
            {GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, GROUND_TOP, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             FLAME, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, GROUND_TOP, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             FLAME, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, GROUND_TOP, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             FLAME, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, ITEM_BLOCK_HIDDEN,
             ITEM_BLOCK_HIDDEN, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
             NONE, GROUND_TOP, NONE,
             NONE, GROUND_TOP,
             NONE, GROUND_TOP, NONE, SPIKE, SPIKE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE,
             NONE, FLAME, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, GROUND_TOP, NONE,
             NONE, GROUND_TOP,
             NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             GROUND_TOP, GROUND_TOP,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, GROUND_TOP, ITEM_BLOCK_OPEN,
             NONE, GROUND_TOP,
             NONE, ITEM_BLOCK_OPEN, NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             GROUND_TOP, GROUND_TOP,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, GROUND_TOP, NONE,
             NONE, GROUND_TOP,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             GROUND_TOP, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {ITEM_BLOCK_OPEN, NONE, NONE, ITEM_BLOCK_OPEN, NONE, NONE, ITEM_BLOCK_OPEN, ITEM_BLOCK_HIDDEN, NONE, ITEM_BLOCK_OPEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE,
             GROUND_TOP, NONE, NONE,
             NONE, GROUND_TOP,
             NONE, GROUND_TOP, SPIKE, SPIKE, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             GROUND_TOP, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, GROUND_TOP,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, GROUND_TOP,
             NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             GROUND_TOP, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, ITEM_BLOCK_OPEN, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, GROUND_TOP,
             NONE, NONE, NONE, CHECKPOINT, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, GROUND_TOP, NONE, NONE, NONE,
             GROUND_TOP, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, GROUND_TOP, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE},
            {GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, NONE,
             NONE, GROUND_TOP,
             NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             GROUND_TOP, NONE, NONE,
             NONE, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE,
             NONE, GROUND_TOP, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, GROUND_TOP,
             NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             GROUND_TOP, MAGMA,
             NONE, MAGMA,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, VERTICAL_PIPE_HEAD, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, GROUND_TOP,
             NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
             GROUND_TOP, NONE,
             MAGMA, NONE, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {GROUND_TOP, HORIZONTAL_PIPE_BODY, NONE, GROUND_TOP, LAVA, NONE, GROUND_TOP, LAVA, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, LAVA, NONE, NONE, LAVA,
             NONE, NONE,
             LAVA, NONE,
             NONE, LAVA, NONE, NONE, LAVA, NONE, NONE, LAVA, NONE, NONE, LAVA, NONE, NONE, LAVA, NONE, NONE, GROUND_TOP,
             LAVA, NONE,
             NONE, LAVA,
             NONE, NONE, LAVA, GROUND_TOP, NONE, LAVA, NONE, GROUND_TOP, LAVA, GROUND_TOP, NONE, GROUND_TOP, LAVA, NONE, NONE, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             LAVA, NONE,
             NONE, GROUND_TOP, LAVA, MAGMA, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, LAVA, NONE, NONE, LAVA, GROUND_TOP, GROUND_TOP, LAVA,
             NONE, NONE,
             LAVA, NONE,
             NONE, LAVA, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, LAVA, NONE, NONE, LAVA,
             NONE, NONE,
             LAVA, NONE, NONE,
             LAVA, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             MAGMA, NONE,
             NONE, NONE, NONE, NONE, MAGMA, NONE, MAGMA, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, MAGMA,
             NONE, MAGMA,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE}};
        //
        BlockCount = 0;
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(1 * 29, 14 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(2 * 29, 14 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_2_4_2;
        BlockCreateLegacy(3 * 29, 4 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(32 * 29, 9 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(76 * 29, 14 * 29 - 12, EBlockType::GROUND_TOP);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(108 * 29, 11 * 29 - 12, EBlockType::BRIDGE_ROPE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(109 * 29, 10 * 29 - 12 - 3, EBlockType::SWORD);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(121 * 29, 10 * 29 - 12, EBlockType::MELON);
        BlockCount += 1;
        //
        EnemyAppearCount = 0;
        EnemyAppearX[EnemyAppearCount] = 0 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (8 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)105;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 2 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (0 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::EVIL_CLOUD_HIDDEN;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 3 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (8 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)105;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 6 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (8 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 9 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (8 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)107;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 25 * 29 * 100 - 1400;
        EnemyAppearY[EnemyAppearCount] = (2 * 29 - 12) * 100 - 400;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FALLING_CAT;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::NONE;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 40 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (8 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_GROUND_TOP;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 42 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (8 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_GROUND_TOP;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 43 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)105;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 47 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)105;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 57 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_GROUND_TOP;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 77 * 29 * 100 - 1400;
        EnemyAppearY[EnemyAppearCount] = (2 * 29 - 12) * 100 - 400;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FALLING_CAT;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::NONE;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 83 * 29 * 100 - 1400;
        EnemyAppearY[EnemyAppearCount] = (2 * 29 - 12) * 100 - 400;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FALLING_CAT;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::NONE;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 88 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (9 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)105;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 88 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (9 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)105;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 90 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (9 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_GROUND_TOP;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 107 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (10 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::MOLALLA;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::MOLALLA_ALIVE;
        EnemyAppearCount += 1;
        //
        GroundCount = 0;
        GroundX[GroundCount] = 13 * 29 * 100;
        GroundY[GroundCount] = (8 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 33000 - 1;
        GroundSizeY[GroundCount] = 3000 - 1;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 13 * 29 * 100;
        GroundY[GroundCount] = (0 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 33000 - 1;
        GroundSizeY[GroundCount] = 3000 - 1;
        GroundType[GroundCount] = EObjectType::FALLING_BLOCKS;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 10 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 6000;
        GroundSizeY[GroundCount] = 6000;
        GroundType[GroundCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[GroundCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_PLUS_10_SECTION;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 46 * 29 * 100;
        GroundY[GroundCount] = (12 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 9000 - 1;
        GroundSizeY[GroundCount] = 3000 - 1;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 58 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 6000;
        GroundSizeY[GroundCount] = 6000;
        GroundType[GroundCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        GroundSubType[GroundCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_PLUS_10_SECTION;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 101 * 29 * 100 - 1500;
        GroundY[GroundCount] = (10 * 29 - 12) * 100 - 3000;
        GroundSizeX[GroundCount] = 12000;
        GroundSizeY[GroundCount] = 12000;
        GroundType[GroundCount] = EObjectType::TRIGGER_MULTI_LASER;
        GroundSubType[GroundCount] = EObjectSubType::TRIGGER_MULTI_LASER_ACTIVE;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 102 * 29 * 100 + 3000;
        GroundY[GroundCount] = (2 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 3000 - 1;
        GroundSizeY[GroundCount] = 300000;
        GroundType[GroundCount] = EObjectType::TRIGGER_GENERIC_1;
        GroundSubType[GroundCount] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SCROLLING_OFF;
        GroundCount += 1;
        //
        LiftCount = 0;
        LiftX[LiftCount] = 74 * 29 * 100 - 1500;
        LiftY[LiftCount] = (7 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 2 * 3000;
        srtype[LiftCount] = 0;
        sracttype[LiftCount] = 1;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::YELLOW;
        LiftCount = 20;
        //
        LiftX[LiftCount] = 97 * 29 * 100;
        LiftY[LiftCount] = (12 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 12 * 3000;
        srtype[LiftCount] = 0;
        sracttype[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::GRAY;
        LiftCount += 1;
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }

    if (SyobonWorld == 3 && SyobonLevel == 1 && SyobonSection == 0)
    { // 3-1
        PlayerX = 5600;
        PlayerY = 32000;
        bgmchange(Music[6]);
        StageColor = ELevelType::ICY;
        scrollx = 2900 * (112 - 19);
        ELegacyStageDate stagedatex[17][1001] = {
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, ITEM_BLOCK_HIDDEN,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             CLOUD, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, ITEM_BLOCK_HIDDEN,
             ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN,
             ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN,
             ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, GOAL_POLE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, CLOUD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, ITEM_BLOCK_HIDDEN, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, HARD_BLOCK, NONE,
             NONE, CLOUD,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, SPIKE, SPIKE, NONE, NONE, SPIKE, SPIKE,
             HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE},
            {NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_OPEN, NONE, ITEM_BLOCK_OPEN, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, ITEM_BLOCK_HIDDEN, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK},
            {NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, HARD_BLOCK, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             NONE, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE,
             NONE, NONE, NONE,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, CHECKPOINT,
             NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK},
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             BRICK, NONE,
             BALL_SHELLED, BRICK, NONE, GRASS, NONE, NONE, BRICK, BRICK, BRICK, BRICK, BRICK, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
             NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN,
             NONE, NONE, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK, HARD_BLOCK,
             HARD_BLOCK},
            {NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, NONE,
             NONE, BRICK, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, ITEM_BLOCK_HIDDEN,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP, GROUND_TOP},
            {NONE, NONE, GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             GROUND_BOTTOM, GROUND_BOTTOM,
             GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, NONE,
             GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
             GROUND_BOTTOM, GROUND_BOTTOM,
             GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
             GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
             GROUND_BOTTOM, GROUND_BOTTOM},
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
             NONE, NONE}};
        // 追加情報
        BlockCount = 0;
        //
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_3_1_0;
        BlockCreateLegacy(2 * 29, 9 * 29 - 12, EBlockType::MESSAGE_BLOCK);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(63 * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(64 * 29, 13 * 29 - 12, EBlockType::BRICK_BRITTLE);
        BlockCount += 1;
        //
        GroundCount = 0;
        GroundX[GroundCount] = 13 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 9000 - 1;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        GroundCount += 1;
        //
        GroundX[GroundCount] = 84 * 29 * 100;
        GroundY[GroundCount] = (13 * 29 - 12) * 100;
        GroundSizeX[GroundCount] = 9000 - 1;
        GroundSizeY[GroundCount] = 3000;
        GroundType[GroundCount] = EObjectType::FALLING_FLOOR;
        GroundSubType[GroundCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        GroundCount += 1;
        //
        EnemyAppearCount = 0;
        EnemyAppearX[EnemyAppearCount] = 108 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (6 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::DEFRAG;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::DEFRAG_GRAB_POLE;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 33 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (10 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 36 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (0 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::EVIL_CLOUD_HIDDEN;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 78 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_COUNTERCLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)105;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 80 * 29 * 100 + 1500;
        EnemyAppearY[EnemyAppearCount] = (7 * 29 - 12) * 100 + 1500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::FIREBAR_CLOCKWISE;
        EnemyAppearSubType[EnemyAppearCount] = (EEnemySubType)105;
        EnemyAppearCount += 1;
        //
        EnemyAppearX[EnemyAppearCount] = 85 * 29 * 100;
        EnemyAppearY[EnemyAppearCount] = (11 * 29 - 12) * 100;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount += 1;
        //
        LiftCount = 0;
        LiftX[LiftCount] = 41 * 29 * 100;
        LiftY[LiftCount] = (3 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 3 * 3000;
        srtype[LiftCount] = 0;
        sracttype[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PUSH_RIGHT;
        LiftCount = 0;
        //
        for (tt = 0; tt <= 1000; tt++)
        {
            for (t = 0; t <= 16; t++)
            {
                stagedate[t][tt] = NONE;
                stagedate[t][tt] = stagedatex[t][tt];
            }
        }
    }
}

// WIP
void HandleSyobonActionThreeLevels()
{
    StageClear();

    //SA3 Title Screen
    if(SyobonState == ESyobonState::TITLE)
    {
        scrollx = 0;

        PlayerX = (2 * 29) * 100 - 350;
        PlayerY = (12 * 29 - 12 - 6) * 100;

        for(int grounds = 0; grounds < 20; grounds++)
        {
            BlockCreate(grounds, 13, EBlockType::GROUND_TOP);
            BlockCreate(grounds, 14, EBlockType::GROUND_BOTTOM);
        }

        GroundCreate(3, 9, 2, 1, EObjectType::VERTICAL_PIPE_HEAD, EObjectSubType::NONE);
        GroundCreate(3 + GAME_X_POS_TO_DOUBLE(500), 9, 2 - GAME_X_POS_TO_DOUBLE(1000), 5, EObjectType::SA3_FAKE_PIPE_BODY, EObjectSubType::NONE);

        CreateBackground(3, 10, EDecorationType::HILL);
        
        //Poison mushroom
        BlockCreate(9, 9, EBlockType::ITEM_BLOCK_OPEN);
        int entity_index = CreateEntity(9, 9, 0, 0, EEnemyType::MUSHROOM_POISONOUS, EEnemySubType::NONE);
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

        CreateBackground(14, 12, EDecorationType::GRASS);
        CreateBackground(12, 10 - 5.724, EDecorationType::CLOUD);
        CreateBackground(2, 3, EDecorationType::CLOUD);
        CreateBackground(7, 2.5, EDecorationType::CLOUD_SMALL);
        CreateBackground(15, 1.2, EDecorationType::CLOUD_SMALL);

        return;
    }
    //has code from SA:All Stars (though i deleted and modified it a lot)
    else if (SyobonWorld == 1 && SyobonLevel == 1 && SyobonSection == 0)
    {
        scrollx = 240000;
        bgmchange(Music[1]);

        //Create all the ground
        for(int grounds = 0; grounds < 100; grounds++)
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
                (grounds >= 83 && grounds <= 93)
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
        GroundCreate(0.25, 8.75, 0.50, 5, EObjectType::SA3_TRIGGER_FAST_SEAL_UP, EObjectSubType::SA3_TRIGGER_FAST_SEAL_UP_1_SEAL);

        CreateEntity(12.5, 7.5, 0, 0, EEnemyType::BALL, EEnemySubType::NONE);
        CreateEntity(6.5, 11.5, 0, 0, EEnemyType::BALL_SPIKY, EEnemySubType::NONE);
        CreateEntity(15.5, 3.5, 0, 0, EEnemyType::BALL, EEnemySubType::NONE);

        CreateEntity(27.5, 8, 0, 0, EEnemyType::BALL, EEnemySubType::NONE);

        CreateBackground(1, 2.5, EDecorationType::CLOUD);
        CreateBackground(10, 2.5, EDecorationType::CLOUD_SMALL);
        CreateBackground(9, 10, EDecorationType::HILL);
        CreateBackground(23, 1.5, EDecorationType::CLOUD);
        CreateBackground(32, 2.5, EDecorationType::CLOUD_SMALL);
        CreateBackground(33.24, 12, EDecorationType::GRASS);
        CreateBackground(42, 2.5, EDecorationType::CLOUD_SMALL);
        CreateBackground(44, 10, EDecorationType::HILL);

        //pipes for each 4 blocks
        for(int i = 0; i < 5; i++)
        {
            if(i == 0)
            {
                GroundCreate(27 + (i * 4) + GAME_X_POS_TO_DOUBLE(500), 9, 2 - GAME_X_POS_TO_DOUBLE(1000), 4, EObjectType::VERTICAL_PIPE_HEAD, EObjectSubType::NONE);
            }
            else
            {
                GroundCreate(27 + (i * 4) + GAME_X_POS_TO_DOUBLE(500), 9, 2 - GAME_X_POS_TO_DOUBLE(1000), 4, EObjectType::SA3_FAKE_PIPE_BODY, EObjectSubType::NONE);
        
                if(i != 4)
                {
                    CreateEntity(29 + (i * 4), 10, 0, 0, EEnemyType::EVIL_CLOUD, EEnemySubType::EVIL_CLOUD_HIDDEN);
                }
                else
                {
                    GroundCreate(27.25 + (i * 4), 0, 1.5, 8.5, EObjectType::SA3_TRIGGER_FAST_SEAL_UP, EObjectSubType::SA3_TRIGGER_FAST_SEAL_UP_4_SEALS);
                }
            }

            GroundCreate(27 + (i * 4), 9, 2, 1, EObjectType::VERTICAL_PIPE_HEAD, EObjectSubType::NONE);
        }

        //remaining code from all stars xd
        int t_9 = GroundCount;
        GroundX[t_9] = 8700; //n地面[t_9].a = 8700;
        GroundY[t_9] = 36500; //n地面[t_9].b = 36500;
        GroundSizeX[t_9] = 11999; //n地面[t_9].c = 11999;
        GroundSizeY[t_9] = 3000; //n地面[t_9].d = 3000;
        GroundType[t_9] = EObjectType::FALLING_FLOOR; //n地面[t_9].type = 52;
        GroundCount++; //n地面co++;



        //after the pipes

        BlockCreate(51, 8.5, EBlockType::HARD_BLOCK);
        BlockCreate(53, 4.5, EBlockType::HARD_BLOCK);

        //spikes trap
        for(int i = 6; i <= 12; i++)
        {
            if(i == 6)
            {
                //save first block index for the trap
                int trap_index = GroundCreate(56, 12.5, 7.5, 0.5, EObjectType::SA3_TRIGGER_SPIKES_LEVEL_1_1, EObjectSubType::SA3_TRIGGER_SPIKES_LEVEL_1_1_WAITING);
                if(trap_index >= 0)
                    GroundAI[trap_index] = BlockCreate(55, i, EBlockType::ITEM_BLOCK_OPEN);
            }
            else
            {
                BlockCreate(55, i, EBlockType::ITEM_BLOCK_OPEN);
            }
            BlockCreate(64, i + 7, EBlockType::ITEM_BLOCK_OPEN);
        }

        GroundCreate(65, 9, 2, 1, EObjectType::VERTICAL_PIPE_HEAD, EObjectSubType::NONE);
        GroundCreate(65 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::VERTICAL_PIPE_HEAD, EObjectSubType::NONE);
        GroundCreate(67, 9, 2, 1, EObjectType::VERTICAL_PIPE_HEAD, EObjectSubType::NONE);
        GroundCreate(67 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::VERTICAL_PIPE_HEAD, EObjectSubType::NONE);


        BlockCreate(69, 5, EBlockType::ITEM_BLOCK_HIDDEN);

        for(int i = 72; i <= 76; ++i)
        {
            BlockCreate(i, 6.5, EBlockType::BRICK);
        }

        BlockCreate(81, 12, EBlockType::TRAMPOLINE, EBlockSubType::TRAMPOLINE_VISIBLE);
    }
}

void StageClear()
{
    memset(stagedate, NONE, sizeof(stagedate));

    ClearAllBackgrounds();
    ClearAllExtraGraphics();
    BlockClearAll();
    ClearAllEntities();
    GroundClearAll();
}
