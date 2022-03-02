#include "window.h"

void makeWindow(){
    InitWindow(1280, 720, "Tobsi's Raylib Project");
    SetTargetFPS(60); 
    while (!WindowShouldClose()){
        BeginDrawing();
        DrawFPS(10, 10);
        EndDrawing();
    }
}