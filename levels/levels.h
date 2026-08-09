
#ifndef SYOBON_LEVELS_H
#define SYOBON_LEVELS_H

void stagecls();
void stage();
void stagep();

//Syobon Action 1 & 2
void HandleSyobonActionOneLevels();
void HandleSyobonActionTwoLevels();

//Syobon Action 3
void HandleSyobonActionThreeLevels();

//Kaizo Syobon
void HandleKaizoSyobonLevels();

//Syobon Action JAM
void HandleSyobonActionJAMLevels();

//+KZ
void ClearOtherGamesGlobalData(); //some globals may keep their value through levels
void StageClear();
void HandleSyobonKZTrueActionLevels();
void HandleSyobonKZCredits();

#endif
