#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "def.h"

class Column {
public:
    Column();
    ~Column();

    void LoadImageColumn(SDL_Renderer* renderer);
    void move();
    void move2();
    void render(SDL_Renderer* renderer);
    void SetBatDau(const int& w, const int& h, const int& x);

    SDL_Rect destRect1;
    SDL_Rect destRect2;

    bool va_cham;
    bool vuot_cot;
    int len_xuong;

private:
    SDL_Texture* col1;
    SDL_Texture* col2;

};




