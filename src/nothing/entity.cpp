#include "entity.h"

// (Constructor) Initializes and sets the entity variables
entity::entity(std::string fileLocal, int AnimationFramesPrLine, int AnimationFrameLines, int FrameHeight, int FrameWidth)
{
    width = FrameWidth; // The width of a frame
    height = FrameHeight; // The height of a frame
    sizeX = width; // Used to set the size of the sprite and hitbox (width)
    sizeY = height; // Used to set the size of the sprite and hitbox (height)
    image = LoadImage(fileLocal.c_str()); // Loads the image
    tex = LoadTextureFromImage(image); // Loads the texture
    position = {0.0f, 0.0f}; // Entity position
    frameRect = {0, 0, width, height}; // The frame rectangle (This is used to display the texture)
    hitbox = {position.x, position.y, sizeX, sizeY}; // This rectangle is used as a hitbox
    animFramesPrLine = AnimationFramesPrLine; // How many frames of animation there are pr line (Think of this as the Y axis) 
    animFrameLines = AnimationFrameLines; // How many lines of animation there are (Think of this as the X axis)
    currentFrame = 0; // We're on frame 0
    currentLine = 0; // We're on line 0
    frameCounter = 0; // The frame counter is only used when the animation is running
    bool isAnimActive = false; // Is used to find out when to play the animation
}

// (Destructor) Unloads everything the entity uses
entity::~entity()
{
    UnloadImage(image);
    UnloadTexture(tex);
}

// A debugging function
void entity::debugLog(){
    std::cout << "Image: " << image.data << std::endl; 
    std::cout << "Texture2D: " << tex.format << std::endl; 
    std::cout << "position: " << position.x << " ; " << position.y << std::endl; 
    std::cout << "frameRect height: " << frameRect.height << std::endl; 
    std::cout << "frameRect width: " << frameRect.width << std::endl; 
    std::cout << "Width: " << width << std::endl; 
    std::cout << "Height: " << height << std::endl; 
    std::cout << "animFramesPrLine ; animFrameLines: " << animFramesPrLine << " ; " << animFrameLines << std::endl; 
}