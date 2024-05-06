#pragma once
#include <queue>
#include <SDL.h>

class Column {
public:
    Column();
    ~Column();

    void update();
    void update_up();
    void update_down();
    void render();
    bool grade();

    SDL_Rect destRect1;
    SDL_Rect destRect2;

};




