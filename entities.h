
#ifndef SYOBON_ENTITIES_H
#define SYOBON_ENTITIES_H

//敵キャラ (Enemy character)
// @attention +KZ: void ayobi() is now void CreateEntity()
// @attention +KZ: int xtype is now int EntityType
void CreateEntity(int xa, int xb, int xc, int xd, int xnotm, int EntityType,
	   int xxtype);

//Enemies and other things
void HandleEntities();
void PlaceEntities();

//Lifts
void HandleLifts();

#endif
