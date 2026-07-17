
#ifndef SYOBON_PLAYER_H
#define SYOBON_PLAYER_H

//プレイヤー (Player)
// mainmsgtype is not really player related, moved above (and renamed)
// @attention +KZ: int ma is now int PlayerX
extern int PlayerX;
// @attention +KZ: int mb is now int PlayerY
extern int PlayerY;
// @attention +KZ: int mnobia is now int PlayerSizeX
extern int PlayerSizeX;
// @attention +KZ: int mnobib is now int PlayerSizeY
extern int PlayerSizeY;
// Condition "PlayerHealth <= 0 && PlayerHealth >= -9" makes the player die
// @attention +KZ: int mhp is now int PlayerHealth
extern int PlayerHealth;
// @attention +KZ: int mc is now int PlayerVelX
extern int PlayerVelX;
// @attention +KZ: int md is now int PlayerVelY
extern int PlayerVelY;
//extern int macttype, atkon; //+KZ unused
extern int atktm; //+KZ: never set, but still read?
//extern int mactsok, msstar;//+KZ unused
// @attention +KZ: int mactp is now int PlayerWalkAnimTimer
extern int PlayerWalkAnimTimer;
// @attention +KZ: int mact is now int PlayerWalkAnim
extern int PlayerWalkAnim;
// @attention +KZ: int nokori is now int PlayerLives;
extern int PlayerLives;

// @attention +KZ: int mactp is now int PlayerState
extern int PlayerState;
// @attention +KZ: int mactp is now int PlayerSubState
extern int PlayerSubState;
// @attention +KZ: int mactp is now int PlayerAITimer
extern int PlayerAITimer;
// @attention +KZ int mzz is now int PlayerRocketPipeTrapVelY
// This variable is specific for the rocket pipe trap from 1-1
extern int PlayerRocketPipeTrapVelY;
// @attention +KZ: int mzimen is now int PlayerGrounded
extern int PlayerGrounded;
enum class EPlayerGroundType
{
    NORMAL = 0,
    SLIP = 1,
};
// @attention +KZ: int mrzimen is now EGroundType GroundType
extern EPlayerGroundType PlayerGroundType;
// @attention +KZ: int mmuki is now ELookingDirection PlayerLookingDirection
extern ELookingDirection PlayerLookingDirection;

//+KZ: following player variables were unused:
//  * mmukitm
//  * mcleartm
//the following were used but also were useless:
//  * mkasok

extern int mjumptm, mkeytm;
// @attention +KZ: int mmutekitm is now int PlayerNoDamageTimer
// +KZ: It is enabled for 5 ticks after kicking a shell
extern int PlayerNoDamageTimer;
// @attention +KZ: int mmutekion is now int PlayerInvincibleON
// +KZ: It is never initialized, but if PlayerInvincibleON == 1 player will kill any enemy it touches
extern int PlayerInvincibleON;

//+KZ: these are never set, but are read?
extern int mztm, mztype;

extern int actaon[7];
//メッセージ (Message)
// @attention +KZ: int mmsgtm is now int PlayerMessageTimer
extern int PlayerMessageTimer;
// @attention +KZ: int mmsgtype is now int PlayerMessageType
extern int PlayerMessageType;

// @attention +KZ: int mascrollmax is now int PlayerScrollCenterX
// +KZ: Keeps the player/camera centered in screen
extern int PlayerScrollCenterX;	//9000

void HandlePlayer();
void HandlePlayerInput();
void HandlePlayerBlocks();
void HandlePlayerWalls();
void HandlePlayerMessage();
void CreatePlayerMessageCache();
void DestroyPlayerMessageCache();

void RenderPlayer();

#endif
