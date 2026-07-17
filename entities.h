
#ifndef SYOBON_ENTITIES_H
#define SYOBON_ENTITIES_H

#include "level_enums.hpp"

//敵キャラ (Enemy character)
// @attention +KZ: amax is now ENEMY_MAX
#define ENEMY_MAX 24
// @attention +KZ: int aco[amax] is now int EnemyCount[amax]
extern int EnemyCount;
// @attention +KZ: int aa[amax] is now int EnemyX[amax]
extern int EnemyX[ENEMY_MAX];
// @attention +KZ: int ab[amax] is now int EnemyY[amax]
extern int EnemyY[ENEMY_MAX];
// @attention +KZ: int anobia[amax] is now int EnemySizeX[amax]
extern int EnemySizeX[ENEMY_MAX];
// @attention +KZ: int anobib[amax] is now int EnemySizeY[amax]
extern int EnemySizeY[ENEMY_MAX];
// @attention +KZ: int ac[amax] is now int EnemyVelX[amax]
extern int EnemyVelX[ENEMY_MAX];
// @attention +KZ: int ad[amax] is now int EnemyVelY[amax]
extern int EnemyVelY[ENEMY_MAX];
//extern int ae[amax]; //+KZ: unused, always set to 0
// @attention +KZ: int af[amax] is now int EnemyFloatingTimer[amax]
// in Syobon Action 1 & 2 it is only used in SUPER_BOON
extern int EnemyFloatingTimer[ENEMY_MAX];
// @attention +KZ: int abrocktm[amax] is now int EnemyBlockAppearTimer[amax]
extern int EnemyBlockAppearTimer[ENEMY_MAX];
// @attention +KZ: int aacta[amax] is now int EnemyActionX[amax]
// it works like a Second kind of VelX, it is set depending of the looking direction by the enemy itself
extern int EnemyActionX[ENEMY_MAX];
// @attention +KZ: int aactb[amax] is now int EnemyActionY[amax]
// unused, seems like the Y axis version of EnemyActionX
extern int EnemyActionY[ENEMY_MAX];
// @attention +KZ: int azimentype[amax] is now int EnemyMovementType[amax]
// affects enemy movement and gravity, if your enemy is floating try using "EnemyMovementType = 1"
extern int EnemyMovementType[ENEMY_MAX];
// @attention +KZ int axzimen[amax] is now int EnemyGrounded[amax]
extern int EnemyGrounded[ENEMY_MAX];
// @attention +KZ: int atype[amax] is now EEnemyType EnemyType[amax]
extern EEnemyType EnemyType[ENEMY_MAX];
// @attention +KZ: int axtype[amax] is now EEnemySubType EnemySubType[amax]
extern EEnemySubType EnemySubType[ENEMY_MAX];
// @attention +KZ: int amuki[amax] is now ELookingDirection EnemyLookingDirection[amax]
extern ELookingDirection EnemyLookingDirection[ENEMY_MAX];
//extern int ahp[amax]; //+KZ: unused
// @attention +KZ: int anotm[amax] is now EnemyPlayerNoInteractTimer[amax]
extern int EnemyPlayerNoInteractTimer[ENEMY_MAX];
// @attention +KZ: int anx[160] is now int EnemyDefaultSizeX[160]
extern int EnemyDefaultSizeX[160];
// @attention +KZ: int any[160] is now int EnemyDefaultSizeY[160]
extern int EnemyDefaultSizeY[160];
// @attention +KZ: int atm[amax] is now int EnemyAITimer[amax]
extern int EnemyAITimer[ENEMY_MAX];
//extern int a2tm[amax]; //+KZ: unused
// @attention +KZ: int amsgtm[amax] is now int EnemyMessageTimer[amax]
extern int EnemyMessageTimer[ENEMY_MAX];
// @attention +KZ: int amsgtype[amax] is now int EnemyMessageType[amax]
extern int EnemyMessageType[ENEMY_MAX];

//敵出現 (Enemy Appearance)
// @attention +KZ: bmax is now ENEMY_APPEAR_MAX
#define ENEMY_APPEAR_MAX 81
// @attention +KZ: int bco is now int EnemyAppearCount[bmax]
extern int EnemyAppearCount;
// @attention +KZ: int ba[bmax] is now int EnemyAppearX[bmax]
extern int EnemyAppearX[ENEMY_APPEAR_MAX];
// @attention +KZ: int bb[bmax] is now int EnemyAppearY[bmax]
extern int EnemyAppearY[ENEMY_APPEAR_MAX];
// @attention +KZ: int btm[bmax] is now int EnemyAppearTimer[bmax]
extern int EnemyAppearTimer[ENEMY_APPEAR_MAX];
// @attention +KZ: int btype[bmax] is now EEnemyType EnemyAppearType[bmax]
extern EEnemyType EnemyAppearType[ENEMY_APPEAR_MAX];
// @attention +KZ: int bxtype[bmax] is now EEnemySubType EnemyAppearSubType[bmax]
extern EEnemySubType EnemyAppearSubType[ENEMY_APPEAR_MAX];
// @attention +KZ: int bz[bmax] is now int EnemyAppearMustPlace[bmax]
extern int EnemyAppearMustPlace[ENEMY_APPEAR_MAX];

//Enemies and other things
void HandleEnemies();
void PlaceEnemies();
void HandleEnemiesMessages();
void CreateEnemyMessageCache();
void DestroyEnemyMessageCache();

void RenderEnemies();
void RenderEnemiesTwo();

//+KZ: new functions for easy use.
// use index -1 to let this function choose enemy index
// returns the enemy index if its created successfully
// NOTE: It does not use EnemyAppear!!
int CreateEnemy(double PosX, double PosY, double VelX, double VelY, EEnemyType EntityType,
	   EEnemySubType EntitySubType, ELookingDirection LookingDirection = LOOKING_LEFT, int PlayerNoInteractTimer = 0, int index = -1);

// like CreateEnemy but it uses EnemyAppear and PlaceEnemies()
// NOT MEMORY SAFE: Enemy types higher or equal to 160 will read memory out of range
int QueueEnemyAppear(double PosX, double PosY, EEnemyType EntityType, EEnemySubType EntitySubType, int Timer = 0, int index = -1);

//+KZ: clear all entities from memory
void ClearAllEnemies();

//+KZ: for new entities
void HandleEnemiesBlocksKZ();

//Legacy functions for compatibility
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
