#pragma once
#include <raylib.h>

#include <iostream>

class entity
{
private:
    /* data */
public:
    // float OFFSET = -16.0f;

    // Raylib stuff
    Image image;
    Texture2D tex;
    Vector2 position = {0.0f, 0.0f};
    Vector2 physicsPosition = {0.0f, 0.0f};
    Rectangle frameRect = {0, 0, width, height};
    Rectangle hitbox = {position.x, position.y, sizeX, sizeY};
    //NPatchInfo ninePatchInfo = {};  

    // Animation stuff
    float width, height, sizeX, sizeY;
    int animFramesPrLine, animFrameLines;
    int currentFrame = 0;
    int currentLine = 0;
    int frameCounter = 0;
    bool isAnimActive = false;

    // Gravity/movement stuff
    float speed;
    float hSpeed;
    float jumpSpeed;
    float gravity;
    bool canJump;
    bool isAlive;
    bool deathAnimFinished;

    // Debugging stuff
    bool showHitbox = false;

    entity(std::string fileLocal, int AnimationFramesPrLine, int AnimationFrameLines, int FrameHeight, int FrameWidth);
    ~entity();

    void debugLog();
};