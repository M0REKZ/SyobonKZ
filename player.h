
#ifndef SYOBON_PLAYER_H
#define SYOBON_PLAYER_H

void HandlePlayer();
void HandlePlayerInput();
void HandlePlayerBlocks();
void HandlePlayerWalls();
void HandlePlayerMessage();
void CreatePlayerMessageCache();
void DestroyPlayerMessageCache();

void RenderPlayer();

#endif
