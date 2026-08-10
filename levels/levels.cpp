
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
		EnemyType[t] = EEnemyType::JIEN;
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
	for (t = 0; t < EFFECT_MAX; t++)
	{
		EffectX[t] = -9000000;
		EffectY[t] = 1;
		EffectVelX[t] = 1;
		EffectVelY[t] = 1;
		EffectType[t] = EEffectType::COIN;
	}
	for (t = 0; t < BACKGROUND_MAX; t++)
	{
		BackgroundX[t] = -9000000;
		BackgroundY[t] = 1;
		//BackgroundWidth[t] = 1;
		//BackgroundHeight[t] = 1;
		BackgroundType[t] = EBackgroundType::HILL;
	}
	// for (t=0;t<cmax;t++){ca[t]=-9000000;cb[t]=1;contm[t]=0;ctype[t]=0;ce[t]=0;cf[t]=0;}
	// for (t=0;t<vmax;t++){va[t]=-9000000;vtype[t]=0;vb[t]=0;vc[t]=1;vd[t]=1;}
	// for (t=0;t<gmax;t++){ga[t]=-9000000;gx[t]=0;gstring[t]="";}

	ObjectCount = 0;
	BlockCount = 0;
	EnemyCount = 0;
	EnemyAppearCount = 0;
	EffectCount = 0;
	BackgroundCount = 0;
	// haikeitouroku();
} // stagecls()

// ステージロード (Stage Load)
void stage()
{
	//some globals may keep their value through levels, which may not be wanted
	ClearOtherGamesGlobalData();

	// fzx=6000*100;
	scrollx = 3600 * 100;

	// byte LegacyStageDate[16][801];
	// byte stagedate2[16][801];

	// 1-レンガ,2-コイン,3-空,4-土台//5-6地面//7-隠し// (1-Brick, 2-Coin, 3-Empty, 4-Foundation // 5-6 Ground // 7-Hidden //)

	stagep();

	for (tt = 0; tt <= 1000; tt++)
	{
		for (t = 0; t <= 16; t++)
		{
			ELegacyStageDate local_xx_10 = NONE;//local_xx_10 = 0;
			if (LegacyStageDate[t][tt] >= 1 && LegacyStageDate[t][tt] <= 255)
				local_xx_10 = LegacyStageDate[t][tt];
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
				LiftInteractType[LiftCount] = ELiftInteractType::NONE;
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
			if (local_xx_10 >= JIEN && local_xx_10 <= ENEMIES_END)
			{
				EnemyAppearX[EnemyAppearCount] = xx[21] * 100;
				EnemyAppearY[EnemyAppearCount] = xx[22] * 100;
				EnemyAppearType[EnemyAppearCount] = (EEnemyType)(xx[23] - JIEN);
				EnemyAppearCount++;
				if (EnemyAppearCount >= ENEMY_APPEAR_MAX)
					EnemyAppearCount = 0;
			}

			if (local_xx_10 >= HILL && local_xx_10 <= BACKGROUNDS_END)
			{
				BackgroundX[BackgroundCount] = xx[21] * 100;
				BackgroundY[BackgroundCount] = xx[22] * 100;
				BackgroundType[BackgroundCount] = (EBackgroundType)(xx[23] - HILL);
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

	// byte LegacyStageDate[16][801];
	// byte stagedate2[16][801];

	// 1-レンガ,2-コイン,3-空,4-土台//5-6地面//7-隠し//

    switch (currentGame)
    {
    case ESyobonActionGame::SHOBON_NO_ACTION_1_AND_2:
        HandleSyobonActionOneLevels();
		HandleSyobonActionTwoLevels();
        break;
    
    case ESyobonActionGame::SYOBON_ACTION_3:
        HandleSyobonActionThreeLevels();
        break;

    case ESyobonActionGame::KAIZO_SYOBON:
        HandleKaizoSyobonLevels();
        break;

    case ESyobonActionGame::SYOBON_ACTION_JAM:
        HandleSyobonActionJAMLevels();
        break;

    case ESyobonActionGame::SYOBONKZ_TRUE_ACTION:
        HandleSyobonKZTrueActionLevels();
        break;

	case ESyobonActionGame::SYOBONKZ_CREDITS:
		HandleSyobonKZCredits();
		break;
    }

} // stagep

void ClearOtherGamesGlobalData()
{
	static ESyobonActionGame prevgame = ESyobonActionGame::SYOBONKZ_CREDITS;

	if(prevgame != currentGame)
	{
		stagepoint = 0; //used for red note block trap

		prevgame = currentGame;
	}
}

void StageClear()
{
    memset(LegacyStageDate, NONE, sizeof(LegacyStageDate));

    ClearAllBackgrounds();
    ClearAllEffects();
    BlockClearAll();
    ClearAllEnemies();
    ObjectClearAll();
    ClearAllLifts();
}
