
#ifndef SYOBON_ENTITIES_H
#define SYOBON_ENTITIES_H

#include "level_enums.hpp"

//敵キャラ (Enemy character)
// @attention +KZ: void ayobi() is now void CreateEntity()
// @attention +KZ: int xa is now int PosX
// @attention +KZ: int xb is now int PosY
// @attention +KZ: int xc is now int VelX
// @attention +KZ: int xd is now int VelY
// @attention +KZ: int xtype is now EEnemyType EntityType
// @attention +KZ: int xxtype is now EEnemySubType EntitySubType
void CreateEntity(int PosX, int PosY, int xc, int xd, int xnotm, EEnemyType EntityType,
	   EEnemySubType EntitySubType);

// @attention +KZ: void tekizimen() is now void HandleTiles()
void HandleEntitiesBlocks();

//Enemies and other things
void HandleEntities();
void PlaceEntities();
void HandleEnemiesMessages();
void CreateEntityMessageCache();

void RenderEnemies();
void RenderEnemiesTwo();

//Lifts
void HandleLifts();
void RenderLifts();

#endif
