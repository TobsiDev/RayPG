// TODO:
    // SOMETIMES THE PLAY DEATH ANIMATION IS GETTING CALLED 2 TIMES ( I THINK ). EDIT: It might be because of the pipes being moved back to their starting position.
    // THIS RESULTS IN THE ANIMATION BEING PLAYED RIGHT AFTER THE PLAYER PRESSES THE RESET BUTTON

#include "window.h"

// Starts the game loop and initializes the window
void makeWindow(){

    // bool showDBM = false;

    // sets the window size and text.
    InitWindow(1280, 720, "Tobsi's Raylib Project");
    SetTargetFPS(60); // Sets the targeted FPS (The FPS we're going for)
    
    // Loads and sets the window icon
    Image icon = LoadImage("./res/img/player/Icon-0001.png");
    SetWindowIcon(icon);
    
    // Player texture 
    entity player("./res/img/player/SussyFlap-0001T.png", 1, 16, 16, 16);

    // Init player position and variables
    player.position = (Vector2){100, 200};
    player.sizeX = 84; // Player sprite width size is being set // a size 4 looks nice. but it's not visible.
    player.sizeY = 84; // Player sprite height size is being set
    player.hitbox.width = player.sizeX; // Makes the hitbox and sprite width fit
    player.hitbox.height = player.sizeY; // Makes the hitbox and sprite height fit
    player.speed = 0;
    player.hSpeed = 330.0f;
    player.jumpSpeed = 395.0f;
    player.gravity = 0;
    player.isAlive = true;
    player.canJump = true;
    player.deathAnimFinished = false;
    player.showHitbox = false;

    // Test Pipes
    float pipeWidth = 120, pipeHeight = 245, pipeXPosition = 400;
    float topPipeWidth = 160, spaceBetween = 134;

    // The death triger at the bottom (Currently visible for debugging.)
    // EnvItem deathFloor = {{-40, 710, 1360, 20}, 1, (Color){255, 255, 255, 128}};

    // Length of the environment items array
    //int envItemsLength = sizeof(pipes.pipeItem)/sizeof(pipes.pipeItem[0]);
    
    // Test animation
    entity testAnim("./res/img/player/Test_anim-0003.png", 1, 16, 16, 16);

    // Main game loop
    while (!WindowShouldClose())
    {
        // Delta
        float deltaT = GetFrameTime();

        // Updates the player and checks for collision under
        updatePlayer(&player, deltaT);
        //updatePlayerCollision(&player, &deathFloor, 1);

        // Checks if the player is alive and updates the pipes
        if (player.isAlive != false)
        {
            /* code */
        }

        BeginDrawing();

        // Checks if the player is alive and plays the death animation if the player is dead
        if (player.isAlive == false)
        {
            playDeathAnim(player, 0, 11);
        }
        
        // Reset key
        if (IsKeyPressed(KEY_R))
        {
            resetPlayer(&player);
        }
        

        ///             TESTING ANIMATIONS AND PIPES Y POSITION             ///
        if(IsKeyDown(KEY_KP_1)){
            DrawText("Key 1 is down", 10, 70, 28, PURPLE);

            testAnim.isAnimActive = true;
            playAnimLineRe(testAnim, 0, 16);

            // std::string PipeYOffsetStr = {"pipes.plusY: " + std::to_string(pipes.plusY)};
            // DrawText(PipeYOffsetStr.c_str(), 100, 100, 24, RED);
            // pipes.plusY -= 5;
        }
        else if (IsKeyDown(KEY_KP_2)){
            DrawText("Key 2 is down", 10, 70, 28, PURPLE);
            testAnim.isAnimActive = true;
            playAnimLineRe(testAnim, 1, 16);

            // std::string PipeYOffsetStr = {"pipes.plusY: " + std::to_string(pipes.plusY)};
            // DrawText(PipeYOffsetStr.c_str(), 100, 100, 24, RED);
            // pipes.plusY += 5;
        }
        else if (testAnim.isAnimActive == false && (testAnim.frameCounter != 0 || testAnim.currentFrame != 0)){testAnim.frameCounter = 0; testAnim.currentFrame = 0;/*testAnim.frameRect.x = 0; testAnim.frameRect.y = 0;*/}
        else {DrawText("None of the TestKeys are down", 10, 70, 28, PURPLE); testAnim.isAnimActive = false; testAnim.frameRect.x = 0; testAnim.frameRect.y = 0; /*std::string PipeYOffsetStr = {"pipes.plusY: " + std::to_string(pipes.plusY)}; DrawText(PipeYOffsetStr.c_str(), 100, 100, 24, RED);*/}        
        ///             TESTING ANIMATIONS AND PIPES Y POSITION             ///

        // Clears the background and sets it to a specific color
        ClearBackground((Color){12, 109, 199, 255});

        // TODO:
            // MAKE THIS WORK WITH AN ENTITY LIST
        // // Draws the pipes
        // for (int i = 0; i < envItemsLength; i++) {
        //     DrawRectangleRec(pipes.pipeItem[i].rect, pipes.pipeItem[i].color); 
        //     DrawRectangleRec(pipes2.pipeItem[i].rect, pipes2.pipeItem[i].color);
        //     // std::cout << "pipes.pipeItem[i].rect.x : " << pipes.pipeItem[i].rect.x << std::endl;

        // }

        // Draws the death floor
        //DrawRectangleRec(deathFloor.rect, deathFloor.color);

        // Draws the player, test animation and the player hitbox
        DrawTextureNPatch(player.tex, 
                            (NPatchInfo){(Rectangle){player.frameRect.x, player.frameRect.y, 16.0f, 16.0f}, 0, 0, 0, 0, NPATCH_NINE_PATCH}, // NPatchInfo (NPatchInfo){(Rectangle){SpriteXPosition, SpriteYPosition, SizeX, SizeY}, leftBorderOffset, topBorderOffset, rightBorderOffset, bottomBorderOffset, LayoutOfTheN-patch)
                            (Rectangle) {player.position.x, player.position.y, player.sizeX, player.sizeY}, // PositionX, PositionY, SizeX, SizeY
                            (Vector2){0, 0}, 
                            0.0f, 
                            WHITE);
        //DrawTextureRec(player.tex, player.frameRect, player.position, WHITE);
        DrawTextureRec(testAnim.tex, testAnim.frameRect, testAnim.position, WHITE);
        // DrawRectangleLines(player.hitbox.x, player.hitbox.y, player.hitbox.width, player.hitbox.height, RED);
        
        // Shows the FPS
        DrawFPS(10, 10);
        EndDrawing();
    }

    // Destroys the texture and entity
    player.~entity();
    testAnim.~entity();

    // Closes the window
    CloseWindow();     
}

// Plays a animation line
void playAnimLineRe(entity& inst, int lineNumb, int animFramesPrLine){
    ///             DEBUGS THE ANIMATION                ///
    std::cout << "Bool: " << inst.isAnimActive << std::endl;
    std::cout << "lineNumb: " << lineNumb << std::endl;
    std::cout << "animFramesPrLine: " << animFramesPrLine << std::endl;
    std::cout << "currentFrame: " << inst.currentFrame << std::endl;
    std::cout << "frameCounter: " << inst.frameCounter << std::endl;
    ///             DEBUGS THE ANIMATION                ///

    // plays the animation
    if (inst.isAnimActive)
    {
        inst.frameCounter++;
        if (inst.frameCounter > 4)
        {
            inst.currentFrame++;
            if (inst.currentFrame > animFramesPrLine)
            {
                inst.currentFrame = 0;
            }
            inst.frameCounter = 0;
        }
    }

    // Sets the position on the texture (If the next frame is 16px to the right, it will move 16px to the right)
    inst.frameRect.x = lineNumb*inst.width;
    inst.frameRect.y = inst.currentFrame*inst.height; 
}

// Plays the death animation
void playDeathAnim(entity& inst, int lineNumb, int animFramesPrLine){

    ///             DEBUGS THE ANIMATION                ///
    std::cout << "==========================================" << std::endl;
    std::cout << "lineNumb: " << lineNumb << std::endl;
    std::cout << "animFramesPrLine: " << animFramesPrLine << std::endl;
    std::cout << "currentFrame: " << inst.currentFrame << std::endl;
    std::cout << "frameCounter: " << inst.frameCounter << std::endl;
    std::cout << "\ninst.frameRect.x: " << inst.frameRect.x << std::endl;
    std::cout << "inst.frameRect.y: " << inst.frameRect.y << std::endl;
    ///             DEBUGS THE ANIMATION                ///

    // plays the animation
    if (inst.deathAnimFinished != true && inst.currentFrame < animFramesPrLine)
    {
        inst.frameCounter++;
        if (inst.frameCounter > 4 && inst.deathAnimFinished != true)
        {
            inst.currentFrame++;
            if (inst.currentFrame > animFramesPrLine)
            {
                inst.currentFrame = 0;
                inst.deathAnimFinished = true;
            }
            inst.frameCounter = 0;
        }
    }

    // Sets the position on the texture (If the next frame is 16px to the right, it will move 16px to the right)
    inst.frameRect.x = lineNumb*inst.width;
    inst.frameRect.y = inst.currentFrame*inst.height;
}

// Updates the player collision box, position and handles the player movement
void updatePlayer(entity* player, float deltaTime){
    if (IsKeyDown(KEY_LEFT)){player->position.x -= player->hSpeed*deltaTime;} // Moves the player to the left if the left arrow key is being held down
    if (IsKeyDown(KEY_RIGHT)){player->position.x += player->hSpeed*deltaTime;} // Moves the player to the right if the right arrow key is being held down
    if (IsKeyDown(KEY_UP)){player->position.y -= player->hSpeed*deltaTime;} // Moves the player to the up if the top arrow key is being held down
    if (IsKeyDown(KEY_DOWN)){player->position.y += player->hSpeed*deltaTime;} // Moves the player to the down if the bottom arrow key is being held down
    /*if (IsKeyPressed(KEY_SPACE) && player->canJump && player->isAlive) // Player jumps
    {
        player->speed = -player->jumpSpeed;
    }*/

    if(IsKeyPressed(KEY_K)){
        player->isAlive = false;
    }

    // Sets the player position, hitbox and gravity (It makes the player fall down if there is nothing blocking them)
    player->position.y += player->speed*deltaTime;
    player->hitbox.y += player->speed*deltaTime;
    // player->speed += player->gravity*deltaTime;
    player->hitbox.x = player->position.x;
    player->hitbox.y = player->position.y;
}

/*
    // Checks for player collision
    void updatePlayerCollision(entity* player, EnvItem* enviromentItems, int envItemsLength){
    int hitObst = 0;
    for (int i = 0; i < envItemsLength; i++) // Goes thru every collision and checks if the player is hitting it
    {
        EnvItem *ei = enviromentItems + i;
        if (CheckCollisionRecs(player->hitbox, ei->rect) && ei->blocking == 1) // Checks if the player is hitting a deadly object.
        {   
            // If the player is dead it will not move. That's why everything is being turned to 0 or false
            player->speed = 0.0f;
            player->isAlive = false;
            player->canJump = false;
            player->gravity = 0;
            player->speed = 0;
            player->hSpeed = 0;
            player->jumpSpeed = 0;
        }

        if (!hitObst)
        {
        }
        else{
            player->canJump = true;
        }
        
        
    }
}*/

// Resets the player variables
void resetPlayer(entity* player){
            // Player variables are being reset
            player->position = (Vector2){100, 200};
            player->hitbox.x = 100;
            player->hitbox.y = 200;
            player->speed = 0;
            player->isAlive = true;
            player->canJump = true;
            // player->gravity = 850;
            player->speed = 0;
            player->hSpeed = 330.0f;
            player->jumpSpeed = 395.0f;

            // The player animation variables are being reset
            player->currentFrame = 0;
            player->currentLine = 0;
            player->frameCounter = 0;
            player->deathAnimFinished = false;
            player->frameRect.x = 0;
            player->frameRect.y = 0;
}

// Used to debug the player variables
// It displays the variables and I'm able to edit them with a button press
// Whats being read/edited can be found in the string variable
void debugPlayerPhysics(entity* player){
    if(IsKeyPressed(KEY_KP_9)) // Toggle for showing the hitbox
        {
            if (showDBM == true)
            {
                showDBM = false;
            }
            else
            {
                showDBM = true;
            }
        }
    
    if (showDBM == true)
    {
        if (IsKeyPressed(KEY_Q)) // Key being used ( This will be on the left of the other key and decrease the value of the variable )
            {
                player->hSpeed -= 5; // What and how much the variables is being changed
                std::string str = {"player-hSpeed: " + std::to_string(player->hSpeed)}; // The string is being used to write it to the screen
                DrawText(str.c_str(), 960, 20, 24, PURPLE); // Writes the string to the screen in purple
            }
            else if (IsKeyPressed(KEY_W)) // The other key being used. This key is right next to the first key and increses the variable
            {
                player->hSpeed += 5;
                std::string str = {"player-hSpeed: " + std::to_string(player->hSpeed)};
                DrawText(str.c_str(), 960, 20, 24, PURPLE);
            }
            else // This keeps the variable on the screen so we can read it.
            {
                std::string str = {"player-hSpeed: " + std::to_string(player->hSpeed)};
                DrawText(str.c_str(), 960, 20, 24, PURPLE);
            }

        if (IsKeyPressed(KEY_A))
            {
                player->jumpSpeed -= 5;
                std::string str = {"player-jumpSpeed: " + std::to_string(player->jumpSpeed)};
                DrawText(str.c_str(), 960, 45, 24, PURPLE);
            }
            else if (IsKeyPressed(KEY_S))
            {
                player->jumpSpeed += 5;
                std::string str = {"player-jumpSpeed: " + std::to_string(player->jumpSpeed)};
                DrawText(str.c_str(), 960, 45, 24, PURPLE);
            }
            else
            {
                std::string str = {"player-jumpSpeed: " + std::to_string(player->jumpSpeed)};
                DrawText(str.c_str(), 960, 45, 24, PURPLE);
            }
            
        if (IsKeyPressed(KEY_Z))
            {
                player->gravity -= 5;
                std::string str = {"player-gravity: " + std::to_string(player->gravity)};
                DrawText(str.c_str(), 960, 70, 24, PURPLE);
            }
            else if (IsKeyPressed(KEY_X))
            {
                player->gravity += 5;
                std::string str = {"player-gravity: " + std::to_string(player->gravity)};
                DrawText(str.c_str(), 960, 70, 24, PURPLE);
            }
            else
            {
                std::string str = {"player-gravity: " + std::to_string(player->gravity)};
                DrawText(str.c_str(), 960, 70, 24, PURPLE);
            }

        if (IsKeyDown(KEY_KP_4))
            {
                player->hitbox.width = player->sizeX -= 1;
                player->hitbox.height = player->sizeY -= 1;
                std::string str = {"player.sizeX: " + std::to_string(player->sizeX)};
                DrawText(str.c_str(), 960, 145, 24, PURPLE);

                std::string str2 = {"player.sizeY: " + std::to_string(player->sizeY)};
                DrawText(str2.c_str(), 960, 170, 24, PURPLE);
            }
            else if (IsKeyDown(KEY_KP_5))
            {
                player->hitbox.width = player->sizeX += 1;
                player->hitbox.height = player->sizeY += 1;
                std::string str = {"player.sizeX: " + std::to_string(player->sizeX)};
                DrawText(str.c_str(), 960, 145, 24, PURPLE);

                std::string str2 = {"player.sizeY: " + std::to_string(player->sizeY)};
                DrawText(str2.c_str(), 960, 170, 24, PURPLE);
            }
            else
            {
                std::string str = {"player.sizeX: " + std::to_string(player->sizeX)};
                DrawText(str.c_str(), 960, 145, 24, PURPLE);

                std::string str2 = {"player.sizeY: " + std::to_string(player->sizeY)};
                DrawText(str2.c_str(), 960, 170, 24, PURPLE);
            }

            if(IsKeyPressed(KEY_KP_6)) // Toggle for showing the hitbox
            {
                if (player->showHitbox == true)
                {
                    player->showHitbox = false;
                }
                else
                {
                    player->showHitbox = true;
                }
            }

            if (player->showHitbox == true)
            {
                DrawRectangleLines(player->hitbox.x, player->hitbox.y, player->hitbox.width, player->hitbox.height, RED);
            }
            

            std::string canJump = {"player canJump: " + std::to_string(player->canJump)};
            DrawText(canJump.c_str(), 960, 95, 24, PURPLE);

            std::string alive = {"player alive: " + std::to_string(player->isAlive)};
            DrawText(alive.c_str(), 960, 120, 24, PURPLE);
    }
}