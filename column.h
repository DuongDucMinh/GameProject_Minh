#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "def.h"

#define COLUMN_SPEED 2
#define COLUMN_SPEED_Y 1
#define COLUMN_SPACE 125

class Column {
public:
    Column();
    ~Column();

    void LoadImageColumn(SDL_Renderer* renderer);
    bool isOffScreen();
    void move();
    void move2();
    void render(SDL_Renderer* renderer);
    void SetBatDau(const int& w, const int& h);

    SDL_Rect destRect1;
    SDL_Rect destRect2;

    bool va_cham;
    bool vuot_cot;
    int len_xuong;

private:
    SDL_Texture* col1;
    SDL_Texture* col2;

};




