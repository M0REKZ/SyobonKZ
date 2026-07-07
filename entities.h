
#ifndef SYOBON_ENTITIES_H
#define SYOBON_ENTITIES_H

#include "level_enums.hpp"

//Enemies and other things
void HandleEnemies();
void PlaceEnemies();
void HandleEnemiesMessages();
void CreateEnemyMessageCache();
void DestroyEnemyMessageCache();

void RenderEnemies();
void RenderEnemiesTwo();

//Lifts
void HandleLifts();
void RenderLifts();

//+KZ: new functions for easy use.
// use index -1 to let this function choose enemy index
// returns the enemy index if its created successfully
// NOTE: It does not use EnemyAppear!!
int CreateEnemy(double PosX, double PosY, double VelX, double VelY, EEnemyType EntityType,
	   EEnemySubType EntitySubType, ELookingDirection LookingDirection = LOOKING_LEFT, int PlayerNoInteractTimer = 0, int index = -1);

//+KZ: clear all entities from memory
void ClearAllEnemies();

//+KZ: for new entities
void HandleEnemiesBlocksKZ();

//敵キャラ (Enemy character)
// @attention +KZ: void ayobi() is now void CreateEnemyLegacy(), but prefer using CreateEnemy() instead
// @attention +KZ: int xa is now int PosX
// @attention +KZ: int xb is now int PosY
// @attention +KZ: int xc is now int VelX
// @attention +KZ: int xd is now int VelY
// @attention +KZ: int xnotm is now int PlayerNoInteractTimer
// @attention +KZ: int xtype is now EEnemyType EntityType
// @attention +KZ: int xxtype is now EEnemySubType EntitySubType
void CreateEnemyLegacy(int PosX, int PosY, int VelX, int VelY, int PlayerNoInteractTimer, EEnemyType EntityType,
	   EEnemySubType EntitySubType);

// @attention +KZ: void tekizimen() is now void HandleTiles()
void HandleEnemiesBlocks();

#endif
