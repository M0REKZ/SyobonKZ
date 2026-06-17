
#ifndef SYOBON_ENTITIES_H
#define SYOBON_ENTITIES_H

//敵キャラ (Enemy character)
// @attention +KZ: void ayobi() is now void CreateEntity()
// @attention +KZ: int xtype is now int EntityType
void CreateEntity(int xa, int xb, int xc, int xd, int xnotm, int EntityType,
	   int xxtype);

// @attention +KZ: void tekizimen() is now void HandleTiles()
void HandleEntitiesBlocks();

//Enemies and other things
void HandleEntities();
void PlaceEntities();
void HandleEnemiesMessages();

void RenderEnemies();
void RenderEnemiesTwo();

//Lifts
void HandleLifts();
void RenderLifts();

#endif
