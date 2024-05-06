#pragma once
#include <queue>
#include <SDL.h>

class Column {
public:
    Column();
    ~Column();

    void update();
    void update_up(long& v, long Count, bool& test2);
    void update_down(long& v, long Count, bool& test2);
    void render();
    bool grade();

    SDL_Rect destRect1;
    SDL_Rect destRect2;

};




