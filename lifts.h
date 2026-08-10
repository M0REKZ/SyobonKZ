#ifndef SYOBONKZ_LIFTS_H
#define SYOBONKZ_LIFTS_H

//リフト (Lift)
// @attention +KZ: srmax is now LIFT_MAX
#define LIFT_MAX 21
// @attention +KZ int srco renamed to LiftCount
extern int LiftCount;
// @attention +KZ int sra[srmax] renamed to LiftX[srmax]
extern int LiftX[LIFT_MAX];
// @attention +KZ int srb[srmax] renamed to LiftY[srmax]
extern int LiftY[LIFT_MAX];
// @attention +KZ int src[srmax] renamed to LiftSizeX[srmax]
extern int LiftSizeX[LIFT_MAX];
//extern int srd[srmax]; //+KZ: useless
// @attention +KZ int sre[srmax] renamed to LiftVelY[srmax]
extern int LiftVelY[LIFT_MAX];
// @attention +KZ int srf[srmax] renamed to LiftFrictionY[srmax]
extern int LiftFrictionY[LIFT_MAX];
// @attention +KZ int srtype[srmax] is now int LiftInteractType[srmax]
// +KZ: Only type 0 and 1 are used, seems that 2 kills the player but is not used anywhere
extern ELiftInteractType LiftInteractType[LIFT_MAX];
//extern int srgtype[srmax]; //+KZ: unused
// @attention +KZ int sracttype[srmax] is now int LiftMovementType[srmax]
extern ELiftMovementType LiftMovementType[LIFT_MAX];
// @attention +KZ int srsp[srmax] is now ELiftType LiftType[srmax]
// +KZ: This is confusing, there are like 3 or more variables indicating the type of the lifts,
extern ELiftType LiftType[LIFT_MAX];
// @attention +KZ int srmuki[srmax] is now int LiftDirection[srmax]
extern int LiftDirection[LIFT_MAX];
// @attention +KZ int sron[srmax] is now int LiftON[srmax]
extern int LiftON[LIFT_MAX];
//extern int sree[LIFT_MAX]; //+KZ: unused
// @attention +KZ int srsok[srmax] renamed to LiftVelX[srmax]
// +KZ: note that this is directly affected by LiftDirection
extern int LiftVelX[LIFT_MAX];
//extern int srmovep[LIFT_MAX]; //+KZ: unused
// @attention +KZ int srmove[srmax] renamed to LiftPlayerFatigueX[srmax]
// +KZ: kills the player if he has high speed in the green lift for too much time, probably to avoid softlocks
extern int LiftPlayerFatigueX[LIFT_MAX];

//from SA: All Stars
// tm
extern int LiftTimer[LIFT_MAX];
// tmmax
extern int LiftTimerMax[LIFT_MAX];
// b落ちる
extern bool LiftTouchSpeedUp[LIFT_MAX];

//Lifts
void HandleLifts();
void RenderLifts();

int CreateLift(double PosX, double PosY, double Width, double VelY, ELiftType Type, ELiftMovementType MovementType ,int index = -1);

//+KZ: clear all lifts from memory
void ClearAllLifts();

#endif
