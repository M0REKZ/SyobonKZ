
#include "global_vars.h"
#include "blocks.h"
#include "levels.h"
#include "main.h"
#include "entities.h"
#include "extra_graphics.h"

void stagecls()
{
	for (t = 0; t < OBJECT_MAX; t++)
	{
		ObjectX[t] = -9000000;
		ObjectY[t] = 1;
		ObjectSizeX[t] = 1;
		ObjectSizeY[t] = 1;
		ObjectAI[t] = 0;
		ObjectType[t] = EObjectType::GREEN_OUTLINE_PIPE_PART;
		ObjectSubType[t] = EObjectSubType::NONE;
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
		LiftDirection[t] = 0;
		LiftON[t] = 0;
		//sree[t] = 0;
		LiftVelX[t] = 0;
		LiftPlayerFatigueX[t] = 0;
		//srmovep[t] = 0;
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

	ObjectCount = 0;
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
			ELegacyStageDate local_xx_10 = NONE;//local_xx_10 = 0;
			if (stagedate[t][tt] >= 1 && stagedate[t][tt] <= 255)
				local_xx_10 = stagedate[t][tt];
			xx[21] = tt * 29;
			xx[22] = t * 29 - 12;
			xx[23] = local_xx_10;
			if (local_xx_10 >= BRICK && local_xx_10 <= BLOCKS_END && local_xx_10 != COIN)
			{
				BlockCreateLegacy(tt * 29, t * 29 - 12, (EBlockType)local_xx_10);
			}
			if (local_xx_10 >= 20 && local_xx_10 <= 29)
			{
				LiftX[LiftCount] = xx[21] * 100;
				LiftY[LiftCount] = xx[22] * 100;
				LiftSizeX[LiftCount] = 3000;
				LiftInteractType[LiftCount] = 0;
				LiftCount++;
				if (LiftCount >= LIFT_MAX)
					LiftCount = 0;
			}
			if (local_xx_10 == CHECKPOINT)
			{
				ObjectX[ObjectCount] = xx[21] * 100;
				ObjectY[ObjectCount] = xx[22] * 100;
				ObjectSizeX[ObjectCount] = 3000;
				ObjectSizeY[ObjectCount] = 6000;
				ObjectType[ObjectCount] = EObjectType::CHECKPOINT;
				ObjectCount++;
				if (ObjectCount >= OBJECT_MAX)
					ObjectCount = 0;
			}
			if (local_xx_10 == VERTICAL_PIPE_HEAD)
			{
				ObjectX[ObjectCount] = xx[21] * 100;
				ObjectY[ObjectCount] = xx[22] * 100;
				ObjectSizeX[ObjectCount] = 6000;
				ObjectSizeY[ObjectCount] = 3000;
				ObjectType[ObjectCount] = EObjectType::BLACK_OUTLINE_PIPE_PART;
				ObjectCount++;
				if (ObjectCount >= OBJECT_MAX)
					ObjectCount = 0;
			}
			if (local_xx_10 == VERTICAL_PIPE_BODY)
			{
				ObjectX[ObjectCount] = xx[21] * 100 + 500;
				ObjectY[ObjectCount] = xx[22] * 100;
				ObjectSizeX[ObjectCount] = 5000;
				ObjectSizeY[ObjectCount] = 3000;
				ObjectType[ObjectCount] = EObjectType::VERTICAL_PIPE_BODY;
				ObjectCount++;
				if (ObjectCount >= OBJECT_MAX)
					ObjectCount = 0;
			}

			if (local_xx_10 == HORIZONTAL_PIPE_HEAD)
			{
				ObjectX[ObjectCount] = xx[21] * 100;
				ObjectY[ObjectCount] = xx[22] * 100 + 500;
				ObjectSizeX[ObjectCount] = 2900;
				ObjectSizeY[ObjectCount] = 5300;
				ObjectType[ObjectCount] = EObjectType::BLACK_OUTLINE_PIPE_PART;
				ObjectCount++;
				if (ObjectCount >= OBJECT_MAX)
					ObjectCount = 0;
			}
			if (local_xx_10 == HORIZONTAL_PIPE_BODY)
			{
				ObjectX[ObjectCount] = xx[21] * 100;
				ObjectY[ObjectCount] = xx[22] * 100 + 700;
				ObjectSizeX[ObjectCount] = 3900;
				ObjectSizeY[ObjectCount] = 5000;
				ObjectType[ObjectCount] = EObjectType::HORIZONTAL_PIPE_BODY;
				ObjectCount++;
				if (ObjectCount >= OBJECT_MAX)
					ObjectCount = 0;
			}
			// これなぜかバグの原因ｗ (For some reason, this is the cause of the bug lol)
			if (local_xx_10 >= BALL && local_xx_10 <= ENEMIES_END)
			{
				EnemyAppearX[EnemyAppearCount] = xx[21] * 100;
				EnemyAppearY[EnemyAppearCount] = xx[22] * 100;
				EnemyAppearType[EnemyAppearCount] = (EEnemyType)(xx[23] - BALL);
				EnemyAppearCount++;
				if (EnemyAppearCount >= ENEMY_APPEAR_MAX)
					EnemyAppearCount = 0;
			}

			if (local_xx_10 >= HILL && local_xx_10 <= BACKGROUNDS_END)
			{
				BackgroundX[BackgroundCount] = xx[21] * 100;
				BackgroundY[BackgroundCount] = xx[22] * 100;
				BackgroundType[BackgroundCount] = (EDecorationType)(xx[23] - HILL);
				BackgroundCount++;
				if (BackgroundCount >= BACKGROUND_MAX)
					BackgroundCount = 0;
			}
			// コイン (Coin)
			if (local_xx_10 == COIN)
			{
				BlockCreateLegacy(tt * 29, t * 29 - 12, EBlockType::COIN);
			}
			if (local_xx_10 == GOAL_POLE)
			{
				ObjectX[ObjectCount] = xx[21] * 100;
				ObjectY[ObjectCount] = xx[22] * 100;
				ObjectSizeX[ObjectCount] = 3000;
				ObjectSizeY[ObjectCount] = (12 - t) * 3000;
				ObjectType[ObjectCount] = EObjectType::GOAL_POLE;
				ObjectCount++;
				if (ObjectCount >= OBJECT_MAX)
					ObjectCount = 0;
			}
		}
	}

	if (CurrentPlayerCheckpoint >= 1)
	{
		xx[17] = 0;
		for (t = 0; t < OBJECT_MAX; t++)
		{
			if (ObjectType[t] == EObjectType::CHECKPOINT && CurrentPlayerCheckpoint >= 1)
			{
				fx = ObjectX[t] - fxmax / 2;
				fzx = fx;
				PlayerX = ObjectX[t] - fx;
				PlayerY = ObjectY[t] - fy;
				CurrentPlayerCheckpoint--;
				xx[17]++;

				ObjectX[t] = -80000000;
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

    switch (currentGame)
    {
    case ESyobonActionGame::SYOBON_ACTION_1_AND_2:
        HandleSyobonActionOneLevels();
		HandleSyobonActionTwoLevels();
        break;
    
    case ESyobonActionGame::SYOBON_ACTION_3:
        HandleSyobonActionThreeLevels();
        break;

    case ESyobonActionGame::KAIZO_SYOBON:
        HandleKaizoSyobonLevels();
        break;
    }

} // stagep

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
            {NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BALL, NONE, NONE, NONE, NONE, NONE, BALL, NONE,
             NONE,GRASS,
            VERTICAL_PIPE_BODY, NONE,
             NONE, NONE, NONE, NONE,GRASS, STAGEDATE_98, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
             NONE, NONE,
             NONE, NONE,
             NONE, NONE,GRASS, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BALL,
             NONE, BALL,
             NONE, NONE,
             BALL_SHELLED, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,GRASS, NONE, NONE, NONE,HARD_BLOCK,HARD_BLOCK,
            HARD_BLOCK, NONE,
             NONE, NONE,
            HARD_BLOCK,HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,VERTICAL_PIPE_BODY, NONE, NONE, NONE, NONE, NONE, BALL, NONE, BALL, NONE,
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
        BlockSubType[BlockCount] = EBlockSubType::ITEM_BLOCK_ENEMY_BALL_NORMAL;
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
        ObjectType[t] = EObjectType::TRIGGER_SEAL_UP;
        ObjectCount++;
        t = ObjectCount;
        ObjectX[t] = 54 * 29 * 100 - 500;
        ObjectY[t] = -6000;
        ObjectSizeX[t] = 7000;
        ObjectSizeY[t] = 70000;
        ObjectType[t] = EObjectType::TRIGGER_SEAL_DOWN;
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
        ObjectType[t] = EObjectType::TRIGGER_SEAL_DOWN;
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
        ObjectType[t] = EObjectType::TRIGGER_SEAL_UP;
        ObjectSubType[t] = EObjectSubType::TRIGGER_SEAL_UP_LEVEL_1_2;
        ObjectCount++;

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
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_BALL_SPIKY_JUMP;
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
        ObjectType[t] = EObjectType::TRIGGER_LAVA_SPAWNER;
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
        ObjectSubType[t] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SEAL_DOWN;
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
        // 追加情報 (Additional information)
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
        ObjectCount = 0;
        ObjectX[ObjectCount] = 30 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 12000 - 1;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 51 * 29 * 100;
        ObjectY[ObjectCount] = (4 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 9000 - 1;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::FALLING_BLOCKS;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_BLOCKS_OVERWORLD_BRICK;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 84 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 9000 - 1;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 105 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 15000 - 1;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        ObjectCount += 1;
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
    { // 2-2(地上) (2-2 (Above ground))
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
        ObjectX[ObjectCount] = 14 * 29 * 100 + 200;
        ObjectY[ObjectCount] = -6000;
        ObjectSizeX[ObjectCount] = 5000;
        ObjectSizeY[ObjectCount] = 70000;
        ObjectType[ObjectCount] = EObjectType::TRIGGER_SEAL_UP;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 12 * 29 * 100 + 1200;
        ObjectY[ObjectCount] = -6000;
        ObjectSizeX[ObjectCount] = 7000;
        ObjectSizeY[ObjectCount] = 70000;
        ObjectType[ObjectCount] = EObjectType::TRIGGER_SEAL_DOWN;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 12 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 6000 - 1;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectAI[ObjectCount] = 0;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 14 * 29 * 100;
        ObjectY[ObjectCount] = (9 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 6000;
        ObjectSizeY[ObjectCount] = 12000 - 200;
        ObjectType[ObjectCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[ObjectCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount += 1;
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
    { // 2-2(地下) (2-2 (Underground))
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
             HORIZONTAL_PIPE_BODY, NONE,
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
             BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, BRICK, BRICK, NONE, NONE, NONE, NONE, HORIZONTAL_PIPE_BODY,
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
        ObjectCount = 0;
        ObjectX[ObjectCount] = 2 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 300000 - 6001;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 3 * 29 * 100;
        ObjectY[ObjectCount] = (7 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 3000;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::TRIGGER_PLATFORM_SPLIT;
        ObjectSubType[ObjectCount] = (EObjectSubType)0; //this is a timer
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 107 * 29 * 100;
        ObjectY[ObjectCount] = (9 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 9000 - 1;
        ObjectSizeY[ObjectCount] = 24000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_BRICK;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 111 * 29 * 100;
        ObjectY[ObjectCount] = (7 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 3000;
        ObjectSizeY[ObjectCount] = 6000 - 200;
        ObjectType[ObjectCount] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        ObjectSubType[ObjectCount] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_KILL_PLAYER_CANNON;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 113 * 29 * 100 + 1100;
        ObjectY[ObjectCount] = (0 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 4700;
        ObjectSizeY[ObjectCount] = 27000 - 1000;
        ObjectType[ObjectCount] = EObjectType::GREEN_OUTLINE_PIPE_PART;
        ObjectSubType[ObjectCount] = EObjectSubType::NONE;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 128 * 29 * 100;
        ObjectY[ObjectCount] = (9 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 9000 - 1;
        ObjectSizeY[ObjectCount] = 24000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_BRICK;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 131 * 29 * 100;
        ObjectY[ObjectCount] = (9 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 3000;
        ObjectSizeY[ObjectCount] = 6000 - 200;
        ObjectType[ObjectCount] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        ObjectSubType[ObjectCount] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 133 * 29 * 100 + 1100;
        ObjectY[ObjectCount] = (0 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 4700;
        ObjectSizeY[ObjectCount] = 32000;
        ObjectType[ObjectCount] = EObjectType::GREEN_OUTLINE_PIPE_PART;
        ObjectSubType[ObjectCount] = EObjectSubType::NONE;
        ObjectCount += 1;
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
            {NONE, NONE, VERTICAL_PIPE_BODY, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
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
        
        ObjectCount = 0;
        EnemyAppearX[ObjectCount] = (102 * 29 - 12) * 100;
        EnemyAppearY[ObjectCount] = (10 * 29 - 12) * 100;
        EnemyAppearType[ObjectCount] = EEnemyType::UNKNOWN_ID_50;
        EnemyAppearSubType[ObjectCount] = EEnemySubType::UNKNOWN_ID_50_1;
        ObjectCount += 1;
        //
        LiftCount = 0;
        LiftX[LiftCount] = 1 * 29 * 100;
        LiftY[LiftCount] = (10 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 5 * 3000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 1;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR;
        LiftCount++;
        //
        LiftX[LiftCount] = 18 * 29 * 100;
        LiftY[LiftCount] = (4 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 3 * 3000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR;
        LiftCount++;
        //
        LiftX[LiftCount] = 35 * 29 * 100;
        LiftY[LiftCount] = (4 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 5 * 3000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR;
        LiftCount++;
        //
        LiftX[LiftCount] = 35 * 29 * 100;
        LiftY[LiftCount] = (8 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 5 * 3000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR;
        LiftCount++;
        //
        LiftX[LiftCount] = 94 * 29 * 100;
        LiftY[LiftCount] = (6 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 3 * 3000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
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
            {GROUND_TOP, LAVA, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, VERTICAL_PIPE_BODY, NONE, GROUND_TOP, LAVA, NONE, NONE, LAVA, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
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
        ObjectCount = 0;
        ObjectX[ObjectCount] = 17 * 29 * 100;
        ObjectY[ObjectCount] = (9 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 21000 - 1;
        ObjectSizeY[ObjectCount] = 3000 - 1;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 27 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 6000;
        ObjectSizeY[ObjectCount] = 6000;
        ObjectType[ObjectCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[ObjectCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_PLUS_10_SECTION;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 34 * 29 * 100;
        ObjectY[ObjectCount] = (5 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 6000;
        ObjectSizeY[ObjectCount] = 30000;
        ObjectType[ObjectCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[ObjectCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount += 1;
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
            {NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, HORIZONTAL_PIPE_BODY, NONE,
             NONE},
            {NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, STAGEDATE_97, NONE, NONE,
             NONE},
            {NONE, VERTICAL_PIPE_HEAD, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP,
             GROUND_TOP},
            {LAVA, VERTICAL_PIPE_BODY, NONE, LAVA, NONE, GROUND_TOP, LAVA, NONE, NONE, LAVA, NONE, GROUND_TOP, LAVA, NONE, NONE, LAVA,
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
        ObjectCount = 0;
        ObjectX[ObjectCount] = 6 * 29 * 100;
        ObjectY[ObjectCount] = (6 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 18000 - 1;
        ObjectSizeY[ObjectCount] = 6000 - 1;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 12 * 29 * 100;
        ObjectY[ObjectCount] = (8 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 9000 - 1;
        ObjectSizeY[ObjectCount] = 3000 - 1;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 15 * 29 * 100;
        ObjectY[ObjectCount] = (11 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 3000;
        ObjectSizeY[ObjectCount] = 6000;
        ObjectType[ObjectCount] = EObjectType::ENTRANCE_HORIZONTAL_PIPE_HEAD;
        ObjectSubType[ObjectCount] = EObjectSubType::ENTRACE_HORIZONTAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 17 * 29 * 100 + 1100;
        ObjectY[ObjectCount] = (0 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 4700;
        ObjectSizeY[ObjectCount] = 38000;
        ObjectType[ObjectCount] = EObjectType::GREEN_OUTLINE_PIPE_PART;
        ObjectSubType[ObjectCount] = EObjectSubType::NONE;
        ObjectCount += 1;
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
            {GROUND_TOP, VERTICAL_PIPE_BODY, NONE, GROUND_TOP, LAVA, NONE, GROUND_TOP, LAVA, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, LAVA, NONE, NONE, LAVA,
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
        ObjectCount = 0;
        ObjectX[ObjectCount] = 13 * 29 * 100;
        ObjectY[ObjectCount] = (8 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 33000 - 1;
        ObjectSizeY[ObjectCount] = 3000 - 1;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 13 * 29 * 100;
        ObjectY[ObjectCount] = (0 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 33000 - 1;
        ObjectSizeY[ObjectCount] = 3000 - 1;
        ObjectType[ObjectCount] = EObjectType::FALLING_BLOCKS;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_BLOCKS_CASTLE_GROUND_TOP;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 10 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 6000;
        ObjectSizeY[ObjectCount] = 6000;
        ObjectType[ObjectCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[ObjectCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_PLUS_10_SECTION;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 46 * 29 * 100;
        ObjectY[ObjectCount] = (12 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 9000 - 1;
        ObjectSizeY[ObjectCount] = 3000 - 1;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 58 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 6000;
        ObjectSizeY[ObjectCount] = 6000;
        ObjectType[ObjectCount] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[ObjectCount] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_PLUS_10_SECTION;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 101 * 29 * 100 - 1500;
        ObjectY[ObjectCount] = (10 * 29 - 12) * 100 - 3000;
        ObjectSizeX[ObjectCount] = 12000;
        ObjectSizeY[ObjectCount] = 12000;
        ObjectType[ObjectCount] = EObjectType::TRIGGER_MULTI_LASER;
        ObjectSubType[ObjectCount] = EObjectSubType::TRIGGER_MULTI_LASER_ACTIVE;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 102 * 29 * 100 + 3000;
        ObjectY[ObjectCount] = (2 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 3000 - 1;
        ObjectSizeY[ObjectCount] = 300000;
        ObjectType[ObjectCount] = EObjectType::TRIGGER_GENERIC_1;
        ObjectSubType[ObjectCount] = EObjectSubType::TRIGGER_GENERIC_1_SUBTYPE_SCROLLING_OFF;
        ObjectCount += 1;
        //
        LiftCount = 0;
        LiftX[LiftCount] = 74 * 29 * 100 - 1500;
        LiftY[LiftCount] = (7 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 2 * 3000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 1;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::YELLOW;
        LiftCount = 20;
        //
        LiftX[LiftCount] = 97 * 29 * 100;
        LiftY[LiftCount] = (12 * 29 - 12) * 100;
        LiftSizeX[LiftCount] = 12 * 3000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
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
        ObjectCount = 0;
        ObjectX[ObjectCount] = 13 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 9000 - 1;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        ObjectCount += 1;
        //
        ObjectX[ObjectCount] = 84 * 29 * 100;
        ObjectY[ObjectCount] = (13 * 29 - 12) * 100;
        ObjectSizeX[ObjectCount] = 9000 - 1;
        ObjectSizeY[ObjectCount] = 3000;
        ObjectType[ObjectCount] = EObjectType::FALLING_FLOOR;
        ObjectSubType[ObjectCount] = EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM;
        ObjectCount += 1;
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
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
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

        CreateBackground(3, 10, EDecorationType::HILL);
        
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
        scrollx = 800000;
        bgmchange(Music[1]);

        //Create all the ground
        for(int grounds = 0; grounds <= 213; grounds++)
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
        ObjectCreate(0.25, 8.75, 0.50, 5, EObjectType::SA3_TRIGGER_FAST_SEAL_UP, EObjectSubType::SA3_TRIGGER_FAST_SEAL_UP_1_SEAL);

        CreateEnemy(12.5, 7.5, 0, 0, EEnemyType::BALL, EEnemySubType::NONE);
        CreateEnemy(6.5, 11.5, 0, 0, EEnemyType::BALL_SPIKY, EEnemySubType::NONE);
        CreateEnemy(15.5, 3.5, 0, 0, EEnemyType::BALL, EEnemySubType::NONE);

        CreateEnemy(27.5, 8, 0, 0, EEnemyType::BALL, EEnemySubType::NONE);

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
                    ObjectCreate(27.25 + (i * 4), 0, 1.5, 8.5, EObjectType::SA3_TRIGGER_FAST_SEAL_UP, EObjectSubType::SA3_TRIGGER_FAST_SEAL_UP_4_SEALS);
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

        CreateEnemy(75.5, 5, 0, 0, EEnemyType::BALL, EEnemySubType::BALL_NORMAL);

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
                    CreateEnemy(x_pos + 0.5, 8.5, 0, 0, EEnemyType::BALL_SPIKY, EEnemySubType::BALL_SPIKY_NORMAL);
                }
                else
                {
                    CreateEnemy(x_pos + 0.5, 8.5, 0, 0, EEnemyType::BALL, EEnemySubType::BALL_NORMAL);
                }
            }

            if(x_pos == 122)
            {
                CreateEnemy(x_pos + 0.5, 8.5, 0, 0, EEnemyType::BALL, EEnemySubType::BALL_NORMAL);
            }
            else if(x_pos == 124)
            {
                CreateEnemy(x_pos + 0.5, 8.5, 0, 0, EEnemyType::BALL_SPIKY, EEnemySubType::BALL_SPIKY_NORMAL);
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

        CreateBackground(114, 1.5, EDecorationType::CLOUD);

        int ind = ObjectCreate(117, 1, 1, 4.5, EObjectType::SA3_TRIGGER_BIG_STONE_BALL_LEVEL_1_1, EObjectSubType::NONE);
        ObjectAI[ind] = first_wall_block;
        ind = ObjectCreate(121, 10.5, 1, 4.5, EObjectType::SA3_TRIGGER_BIG_STONE_BALL_LEVEL_1_1, EObjectSubType::NONE);
        ObjectAI[ind] = -1;

        ObjectCreate(130, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(130 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        BlockCreate(132, 5.5, EBlockType::ITEM_BLOCK_HIDDEN);

        for(int x_coin = 132; x_coin < 140; x_coin++)
        {
            BlockCreate(x_coin, 11.5, EBlockType::COIN);
        }
        //TODO: you should not be able to even touch this floor
        ObjectCreate(132, 13, 8, 2, EObjectType::FALLING_FLOOR, EObjectSubType::FALLING_FLOOR_GROUND_TOP_BOTTOM);

        ObjectCreate(140, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(140 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(140, 0, 2, 11, EObjectType::SA3_TRIGGER_FAST_SEAL_UP, EObjectSubType::SA3_TRIGGER_FAST_SEAL_UP_1_SEAL);

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

        CreateEnemy(168, 12, 0, 0, EEnemyType::BALL_SPIKY, EEnemySubType::BALL_SPIKY_SA3_HIDE_SPIKES);

        ObjectCreate(171, 13, 4, 2, EObjectType::SA3_FALLING_FLOOR, EObjectSubType::NONE);

        BlockCreate(174, 9, EBlockType::ITEM_BLOCK_HIDDEN);
        ObjectCreate(175, 9, 2, 1, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);
        ObjectCreate(175 + GAME_X_POS_TO_DOUBLE(500), 10, 2 - GAME_X_POS_TO_DOUBLE(1000), 3, EObjectType::BLACK_OUTLINE_PIPE_PART, EObjectSubType::NONE);

        CreateEnemy(171, 1.5, 0, 0, EEnemyType::BALL_SHELLED, EEnemySubType::NONE);
        for(int x_pos = 169; x_pos <= 173; x_pos++)
        {
            BlockCreate(x_pos, 2.5, EBlockType::BRICK);
        }
        BlockCreate(169, 1.5, EBlockType::BRICK);
        BlockCreate(174, 1.5, EBlockType::BRICK);
        BlockCreate(174, 2.5, EBlockType::ITEM_BLOCK_HIDDEN);
        for(int x_pos = 176; x_pos <= 184; x_pos++)
        {
            BlockCreate(x_pos, 2.5, EBlockType::ITEM_BLOCK_HIDDEN);
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
        ObjectCreate(197, 1, 1, 11.3, EObjectType::GOAL_POLE, EObjectSubType::NONE);

        BlockCreate(197, 12, EBlockType::HARD_BLOCK);

        for(int x_pos = 188; x_pos <= 196; x_pos++)
        {
            BlockCreate(x_pos, 10.7, EBlockType::ITEM_BLOCK_HIDDEN, EBlockSubType::ITEM_BLOCK_HIDDEN_SA3_NO_SHELL);
        }

        BlockCreate(190.5, 7, EBlockType::ITEM_BLOCK_HIDDEN);

        CreateBackground(204, 10, EDecorationType::CASTLE);

        //REMOVE ME
        ObjectCreate(149, 1, 0, 0, EObjectType::CHECKPOINT, EObjectSubType::NONE);
        CurrentPlayerCheckpoint = 2;
        printf("enemy count %d\n",EnemyCount);
    }
}

//From SA : All Stars
void HandleKaizoSyobonLevels()
{
    StageClear(); //+KZ added

    if(SyobonState == ESyobonGameState::TITLE)
    {
        scrollx = 0;

        PlayerX = (2 * 30) * 100;
        PlayerY = (12 * 29 - 12 - 6) * 100;

        BlockCreate(2, 13, EBlockType::GROUND_TOP);
        BlockCreate(2, 14, EBlockType::GROUND_BOTTOM);

        return;
    }

    scrollx = 360000;

    if (SyobonWorld == 1 && SyobonLevel == 1 && SyobonSection == 0)
    {
        ELegacyStageDate stagedatexKaizo1[17][1001] =
			{
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GOAL_POLE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GOAL_POLE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GOAL_POLE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GOAL_POLE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, SPIKE, SPIKE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, NONE, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, STAGEDATE_98, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, NONE, SPIKE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, NONE, NONE, HARD_BLOCK, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN,
					ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					BALL, NONE, SPIKE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					TREE, NONE, NONE, TREE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, CASTLE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					CHECKPOINT, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GRASS,
					NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, BALL, NONE, BALL, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE,
					NONE, NONE, NONE, HARD_BLOCK, GRASS, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP
				},
				{
					NONE, NONE, NONE, GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_BOTTOM, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, GROUND_BOTTOM, NONE, NONE, NONE,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
					NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, ITEM_BLOCK_OPEN, ITEM_BLOCK_OPEN, ITEM_BLOCK_OPEN, NONE, NONE, ITEM_BLOCK_OPEN, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE
				}
			};

        bgmchange(Music[1]);
        PlayerGroundType = EPlayerGroundType::NORMAL;
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_KAIZO_SYOBON_1;
        BlockCreateLegacy(58, 249, EBlockType::MESSAGE_BLOCK);
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_KAIZO_SYOBON_2;
        BlockCreateLegacy(870, 191, EBlockType::MESSAGE_BLOCK);
        for (int num143 = 0; num143 <= 1000; num143++)
        {
            for (int num144 = 0; num144 <= 16; num144++)
            {
                stagedate[num144][num143] = stagedatexKaizo1[num144][num143];
            }
        }
    }
    if (SyobonWorld == 1 && SyobonLevel == 2 && SyobonSection == 0)
    {
        ELegacyStageDate stagedatexKaizo2[17][1001] =
			{
				{
					SPIKE, SPIKE, SPIKE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
					HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, SPIKE, SPIKE, HARD_BLOCK, SPIKE, SPIKE, SPIKE, HARD_BLOCK,
					SPIKE, SPIKE, HARD_BLOCK, SPIKE, SPIKE, SPIKE, SPIKE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE
				},
				{
					HARD_BLOCK, NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, GOAL_POLE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GOAL_POLE
				},
				{
					SPIKE, NONE, SPIKE, SPIKE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					HORIZONTAL_PIPE_HEAD, HORIZONTAL_PIPE_BODY, HORIZONTAL_PIPE_BODY, HORIZONTAL_PIPE_BODY, HORIZONTAL_PIPE_BODY, HORIZONTAL_PIPE_BODY, HORIZONTAL_PIPE_BODY, HORIZONTAL_PIPE_BODY, HORIZONTAL_PIPE_BODY, HORIZONTAL_PIPE_BODY
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRICK, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE
				},
				{
					GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, BRICK, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP
				},
				{
					GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
					GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_TOP, NONE, NONE,
					NONE
				}
			};

        bgmchange(Music[2]);
        PlayerGroundType = EPlayerGroundType::NORMAL;
        StageColor = ELevelType::UNDERGROUND;
        scrollx = 408000;
        BlockCount = 0;
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_KAIZO_SYOBON_3;
        BlockCreateLegacy(0, 249, EBlockType::MESSAGE_BLOCK);
        ObjectCount = 0;
        int num145 = ObjectCount;
        ObjectX[num145] = 40600;
        ObjectY[num145] = 24900;
        ObjectSizeX[num145] = 6000;
        ObjectSizeY[num145] = 11800;
        ObjectType[num145] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[num145] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount++;
        for (int num146 = 0; num146 <= 1000; num146++)
        {
            for (int num147 = 0; num147 <= 16; num147++)
            {
                stagedate[num147][num146] = stagedatexKaizo2[num147][num146];
            }
        }
    }
    if (SyobonWorld == 1 && SyobonLevel == 2 && SyobonSection == 1)
    {
        ELegacyStageDate stagedatexKaizo3[17][1001] =
			{
				{NONE},
				{NONE},
				{NONE},
				{NONE},
				{NONE},
				{NONE},
				{NONE},
				{NONE},
				{NONE},
				{NONE},
				{
					ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM,
					NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, NONE, NONE, NONE
				},
				{NONE}
			};
        bgmchange(Music[2]);
        PlayerGroundType = EPlayerGroundType::NORMAL;
        scrollx = 0;
        PlayerX = 6000;
        PlayerY = 3000;
        StageColor = ELevelType::UNDERGROUND;
        for (int num148 = 0; num148 <= 1000; num148++)
        {
            for (int num149 = 0; num149 <= 16; num149++)
            {
                stagedate[num149][num148] = stagedatexKaizo3[num149][num148];
            }
        }
    }
    if (SyobonWorld == 1 && SyobonLevel == 3 && SyobonSection == 6)
    {
        SyobonSection = 0;
    }
    if (SyobonWorld == 1 && SyobonLevel == 3 && SyobonSection == 0)
    {
        ELegacyStageDate stagedatexKaizo5[17][1001] =
			{
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
					HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, SPIKE, SPIKE, SPIKE, SPIKE,
					SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, HARD_BLOCK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE,
					ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE,
					GOAL_POLE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, HARD_BLOCK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GOAL_POLE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, BRICK, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, ITEM_BLOCK_COIN, NONE, NONE, HARD_BLOCK,
					HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, BRICK, NONE, NONE, NONE,
					BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					SPIKE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK,
					NONE, HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, HARD_BLOCK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, SPIKE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE,
					NONE, NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{NONE},
				{
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
                    NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, HARD_BLOCK, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, CASTLE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, CASTLE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE
                },
                    {
                    HORIZONTAL_PIPE_HEAD, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE
                },
				{
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE
                },
				{
                    GROUND_TOP, BALL, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
                    NONE, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, HARD_BLOCK, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    GROUND_TOP, NONE, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
                    GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
                    NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE
                },
				{
                    GROUND_BOTTOM, NONE, NONE, NONE, NONE, GROUND_BOTTOM, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    GROUND_BOTTOM, NONE, GROUND_BOTTOM, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE,
                    GROUND_BOTTOM, NONE, NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM,
                    NONE, NONE, NONE, NONE, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, GROUND_BOTTOM, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE
                },
				{
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, HARD_BLOCK,
                    HARD_BLOCK, HARD_BLOCK, NONE, NONE, NONE, NONE, NONE, HARD_BLOCK, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
                    NONE, NONE, NONE, NONE, NONE
                }
			};
        stagedatexKaizo5[9][49] = HARD_BLOCK;
        stagedatexKaizo5[9][57] = HARD_BLOCK;
		

        PlayerGroundType = EPlayerGroundType::SLIP;
        bgmchange(Music[1]);
        StageColor = ELevelType::KAIZO_SYOBON_OVERWORLD_SLIP;
        scrollx = 390000;
        PlayerY = 33720;
        BlockCount = 0;
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_KAIZO_SYOBON_4;
        BlockCreateLegacy(0, 220, EBlockType::MESSAGE_BLOCK);
        BlockCreateLegacy(1566, 278, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1450, 278, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1624, 278, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1450, 191, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1508, 191, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1566, 191, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1450, 104, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1508, 104, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1566, 104, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockCreateLegacy(1624, 104, EBlockType::ITEM_BLOCK_POISON_HIDDEN);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(1711, 133, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(1740, 133, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(1856, 75, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(1885, 75, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(2001, 133, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(2059, 133, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(2146, 104, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(2175, 104, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(2291, 104, EBlockType::BRICK_BRITTLE);
        BlockSubType[BlockCount] = EBlockSubType::BRICK_BRITTLE_BRICK;
        BlockCreateLegacy(2349, 104, EBlockType::BRICK_BRITTLE);
        BlockCreateLegacy(2639, 307, EBlockType::KAIZO_SYOBON_ITEM_BLOCK_105);
        LiftCount = 0;
        LiftX[LiftCount] = 5800;
        LiftY[LiftCount] = 7500;
        LiftSizeX[LiftCount] = 18000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 1;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::KAIZO_SYOBON_UNKNOWN_13;
        LiftY[LiftCount] = false;
        LiftCount++;
        LiftX[LiftCount] = 29000;
        LiftY[LiftCount] = 13300;
        LiftSizeX[LiftCount] = 15000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::PILLAR_BOUNCY;
        LiftY[LiftCount] = false;
        LiftCount++;
        LiftX[LiftCount] = 52200;
        LiftY[LiftCount] = 16200;
        LiftSizeX[LiftCount] = 18000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::KAIZO_SYOBON_UNKNOWN_13;
        LiftY[LiftCount] = false;
        LiftCount++;
        LiftX[LiftCount] = 75400;
        LiftY[LiftCount] = 19100;
        LiftSizeX[LiftCount] = 9000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::BREAKING;
        LiftCount++;
        LiftX[LiftCount] = 90800;
        LiftY[LiftCount] = 13300;
        LiftSizeX[LiftCount] = 9000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::BREAKING;
        LiftCount++;
        LiftX[LiftCount] = 108200;
        LiftY[LiftCount] = 1700;
        LiftSizeX[LiftCount] = 9000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::BREAKING;
        LiftCount++;
        LiftX[LiftCount] = 275500;
        LiftY[LiftCount] = 16200;
        LiftSizeX[LiftCount] = 19000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::KAIZO_SYOBON_UNKNOWN_13;
        LiftY[LiftCount] = false;
        LiftCount++;
        LiftX[LiftCount] = 304500;
        LiftY[LiftCount] = 24900;
        LiftSizeX[LiftCount] = 39000;
        LiftInteractType[LiftCount] = 0;
        LiftMovementType[LiftCount] = 0;
        LiftVelY[LiftCount] = 0;
        LiftType[LiftCount] = ELiftType::KAIZO_SYOBON_UNKNOWN_13;
        LiftY[LiftCount] = false;
        LiftCount++;
        BlockCreateLegacy(522, 394, EBlockType::NOTE_BLOCK);
        BlockCreateLegacy(551, 394, EBlockType::NOTE_BLOCK);
        BlockCreateLegacy(580, 394, EBlockType::NOTE_BLOCK);
        BlockCreateLegacy(2146, 249, EBlockType::ITEM_BLOCK_HIDDEN);
        int num150 = ObjectCount;
        ObjectX[num150] = 26100;
        ObjectY[num150] = 36500;
        ObjectSizeX[num150] = 8999;
        ObjectSizeY[num150] = 3000;
        ObjectType[num150] = EObjectType::FALLING_FLOOR;
        ObjectCount++;
        num150 = ObjectCount;
        ObjectX[num150] = 378400;
        ObjectY[num150] = -1300;
        ObjectSizeX[num150] = 15000;
        ObjectSizeY[num150] = 14000;
        ObjectType[num150] = EObjectType::TRIGGER_MULTI_LASER;
        ObjectCount++;
        EnemyAppearCount = 0;
        EnemyAppearX[EnemyAppearCount] = 258100;
        EnemyAppearY[EnemyAppearCount] = 30700;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::SPIKY_BLOCK;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::SPIKY_BLOCK_HARD_BLOCK;
        EnemyAppearCount++;
        EnemyAppearX[EnemyAppearCount] = 300;
        EnemyAppearY[EnemyAppearCount] = 4600;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::EVIL_CLOUD_NORMAL;
        EnemyAppearCount++;
        if (stagepoint)
        {
            stagepoint = false;
            PlayerX = 4500;
            PlayerY = -3000;
            CurrentPlayerCheckpoint = 0;
        }
        for (int num151 = 0; num151 <= 1000; num151++)
        {
            for (int num152 = 0; num152 <= 16; num152++)
            {
                stagedate[num152][num151] = stagedatexKaizo5[num152][num151];
            }
        }
    }
    if (SyobonWorld == 1 && SyobonLevel == 3 && SyobonSection == 5)
    {
        ELegacyStageDate stagedatexKaizo7[17][1001] =
			{
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE,
					NONE, NONE, NONE, NONE
				},
				{NONE},
				{NONE},
				{
					NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, COIN, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, CLOUD_BLOCK, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, COIN, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, COIN
				},
				{
					NONE, NONE, ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, CLOUD_BLOCK, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, CLOUD_BLOCK
				},
				{
					NONE, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					COIN, NONE, NONE, NONE
				},
				{
					COIN, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					CLOUD_BLOCK, NONE, NONE, NONE
				},
				{
					CLOUD_BLOCK, NONE, COIN, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, CLOUD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{NONE},
				{
					NONE, CLOUD_BLOCK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{NONE},
				{NONE}
			};

        StageColor = ELevelType::KAIZO_SYOBON_OVERWORLD_SLIP;
        PlayerGroundType = EPlayerGroundType::SLIP;
        bgmchange(Music[3]);
        scrollx = 0;
        PlayerX = 3000;
        PlayerY = 33000;
        stagepoint = true;
        ObjectCount = 0;
        int num153 = ObjectCount;
        ObjectX[num153] = 40595;
        ObjectY[num153] = 30700;
        ObjectSizeX[num153] = 6000;
        ObjectSizeY[num153] = 14800;
        ObjectType[num153] = EObjectType::ENTRANCE_VERTICAL_PIPE_HEAD;
        ObjectSubType[num153] = EObjectSubType::ENTRACE_VERTICAL_PIPE_HEAD_GO_NEXT_SECTION;
        ObjectCount++;
        BlockSubType[BlockCount] = EBlockSubType::NONE;
        BlockCreateLegacy(377, 75, EBlockType::ITEM_BLOCK_COINS);
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_KAIZO_SYOBON_5;
        BlockCreateLegacy(377, -12, EBlockType::MESSAGE_BLOCK);
        for (int num154 = 0; num154 <= 1000; num154++)
        {
            for (int num155 = 0; num155 <= 16; num155++)
            {
                stagedate[num155][num154] = stagedatexKaizo7[num155][num154];
            }
        }
    }
    if (SyobonWorld == 1 && SyobonLevel == 4 && SyobonSection == 0)
    {
        ELegacyStageDate stagedatexKaizo8[17][1001] =
			{
				{
					NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, VERTICAL_PIPE_BODY, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE
				},
				{
					NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, GROUND_TOP, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, VERTICAL_PIPE_BODY, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, BRICK, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE
				},
				{
					NONE, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, NONE, NONE, NONE, HORIZONTAL_PIPE_HEAD, HORIZONTAL_PIPE_BODY, VERTICAL_PIPE_BODY, GROUND_TOP, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE
				},
				{
					NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, VERTICAL_PIPE_BODY, GROUND_TOP, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, GOAL_POLE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE
				},
				{
					NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					GROUND_TOP, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE
				},
				{
					NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, ITEM_BLOCK_HIDDEN, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE
				},
				{
					NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE,
					SPIKE, SPIKE, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
					NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, BRICK, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, GROUND_TOP,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, SPIKE, SPIKE,
					SPIKE, SPIKE, ITEM_BLOCK_HIDDEN, SPIKE, SPIKE, SPIKE, SPIKE, GROUND_TOP, GROUND_TOP, NONE,
					NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, SPIKE, SPIKE, NONE,
					NONE, FLAME, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, SUPER_BOON, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, ITEM_BLOCK_HIDDEN, GROUND_TOP, NONE, GROUND_TOP, ITEM_BLOCK_HIDDEN,
					ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, SPIKE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, FLAME, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE,
					GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					ITEM_BLOCK_HIDDEN, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, GROUND_TOP,
					NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, ITEM_BLOCK_HIDDEN, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, FLAME,
					NONE, GROUND_TOP, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, BALL_SHELLED, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, FLAME,
					NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, BRICK,
					BRICK, BRICK, BRICK, BRICK, BRICK, BRICK, ITEM_BLOCK_HIDDEN, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, FLAME,
					NONE, GROUND_TOP, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, GROUND_TOP,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, GROUND_TOP, LAVA, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE, NONE,
					NONE, NONE, NONE, NONE, NONE, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP, GROUND_TOP,
					GROUND_TOP, GROUND_TOP, GROUND_TOP, NONE, NONE, NONE, NONE, NONE, NONE
				},
				{NONE}
			};

        bgmchange(Music[6]);
        scrollx = 440000;
        PlayerX = 12000;
        PlayerY = 6000;
        StageColor = ELevelType::CASTLE;
        ObjectCount = 0;
        int num156 = ObjectCount;
        BlockSubType[BlockCount] = EBlockSubType::MESSAGE_BLOCK_KAIZO_SYOBON_6;
        BlockCreateLegacy(58, 46, EBlockType::MESSAGE_BLOCK);
        EnemyAppearCount = 0;
        EnemyAppearX[EnemyAppearCount] = 8700;
        EnemyAppearY[EnemyAppearCount] = 7500;
        EnemyAppearType[EnemyAppearCount] = EEnemyType::EVIL_CLOUD;
        EnemyAppearSubType[EnemyAppearCount] = EEnemySubType::EVIL_CLOUD_HIDDEN;
        EnemyAppearCount++;
        SyobonSection = 0;
        for (int num157 = 0; num157 <= 1000; num157++)
        {
            for (num156 = 0; num156 <= 16; num156++)
            {
                stagedate[num156][num157] = stagedatexKaizo8[num156][num157];
            }
        }
    }
}

void StageClear()
{
    memset(stagedate, NONE, sizeof(stagedate));

    ClearAllBackgrounds();
    ClearAllExtraGraphics();
    BlockClearAll();
    ClearAllEnemies();
    ObjectClearAll();
}
