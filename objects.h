#ifndef SYOBONKZ_OBJECTS_H
#define SYOBONKZ_OBJECTS_H

#include "level_enums.hpp"

//地面 (Ground)
// @attention +KZ: smax is now OBJECT_MAX
// +KZ: had to increase it to support SA3
#define LEGACY_OBJECT_MAX 31
#define OBJECT_MAX 64
//extern int sx; //+KZ: unused
// @attention +KZ: int sco is now ObjectCount
extern int ObjectCount;
// @attention +KZ: int sa[smax] is now ObjectX[smax]
extern int ObjectX[OBJECT_MAX];
// @attention +KZ: int sb[smax] is now ObjectY[smax]
extern int ObjectY[OBJECT_MAX];
// @attention +KZ: int sc[smax] is now ObjectSizeX[smax]
extern int ObjectSizeX[OBJECT_MAX];
// @attention +KZ: int sd[smax] is now ObjectSizeY[smax]
extern int ObjectSizeY[OBJECT_MAX];
// @attention +KZ: int stype[smax] is now EObjectType ObjectType[smax]
extern EObjectType ObjectType[OBJECT_MAX];
// @attention +KZ: int sxtype[smax] is now ObjectSubType[smax]
extern EObjectSubType ObjectSubType[OBJECT_MAX];
// @attention +KZ: int sr[smax] is now ObjectVelY[smax]
extern int ObjectVelY[OBJECT_MAX];
// @attention +KZ: int sgtype[smax] is now ObjectAI[smax]
extern int ObjectAI[OBJECT_MAX];

void RenderWalls();
void RenderOverwritePipe();

//+KZ: added in SyobonKZ
void RenderObjectsBehind();

//+KZ: like BlockCreate but for Objects
int ObjectCreate(double x, double y, double size_x, double size_y, EObjectType type, EObjectSubType subtype, int index = -1);

//+KZ: clear all objects from memory
void ObjectClearAll();

#endif
