#pragma once
#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <string>

#include "entity.h"

bool showDBM = false;

// Starts the game loop and initializes the window
void makeWindow();

// Plays a animation line
void playAnimLineRe(entity& inst, int lineNumb, int animFramesPrLine);

// Plays the death animation
void playDeathAnim(entity& inst, int lineNumb, int animFramesPrLine);

// Updates the player collision box, position and handles the player movement
void updatePlayer(entity* player, float deltaTime);

// Updates the player collision box, position and handles the player movement
// void updatePlayerCollision(entity* player, EnvItem* enviromentItems, int envItemsLength);

// Resets the player variables
void resetPlayer(entity* player);

// Used to debug the player variables
// It displays the variables and I'm able to edit them with a button press
// Whats being read/edited can be found in the string variable
void debugPlayerPhysics(entity* player);