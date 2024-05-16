#include "column.h"

using namespace std;

Column::Column() {
    destRect1.x = SCREEN_WIDTH;
    destRect1.y = rand() % 200 - 300;
    destRect1.w = 0;
    destRect1.h = 0;

    destRect2.x = SCREEN_WIDTH;
    destRect2.y = destRect1.y + destRect1.h + COLUMN_SPACE;
    destRect2.w = 0;
    destRect2.h = 0;

    len_xuong = rand() % 2;
    vuot_cot = false;
    va_cham = false;
}

Column:: ~Column() {}

void Column::SetBatDau(const int& w, const int& h, const int& x){
    destRect1.x = x;
    destRect1.y = rand() % 200 - 300;
    destRect1.w = w;
    destRect1.h = h;

    destRect2.x = x;
    destRect2.y = destRect1.y + destRect1.h + COLUMN_SPACE;
    destRect2.w = w;
    destRect2.h = h;

    len_xuong = rand() % 2;
    vuot_cot = false;
    va_cham = false;
}

void Column::LoadImageColumn(SDL_Renderer* renderer, int choose_pipe){
    if (choose_pipe == 1) {
        col1 = IMG_LoadTexture(renderer, "picture\\pipe\\pipe_up.png");
        col2 = IMG_LoadTexture(renderer, "picture\\pipe\\pipe_down.jpg");
    }
    if (choose_pipe == 2) {
        col1 = IMG_LoadTexture(renderer, "picture\\pipe\\pipe_house_up.jpg");
        col2 = IMG_LoadTexture(renderer, "picture\\pipe\\pipe_house_down.jpg");
    }
    if (choose_pipe == 3) {
        col1 = IMG_LoadTexture(renderer, "picture\\pipe\\pipe_block_up.jpg");
        col2 = IMG_LoadTexture(renderer, "picture\\pipe\\pipe_block_down.jpg");
    }
    SDL_Rect dest;
    SDL_QueryTexture(col1, NULL, NULL, &dest.w, &dest.h);
    destRect1.w = dest.w;
    destRect1.h = dest.h;
    destRect2.w = destRect1.w;
    destRect2.h = destRect1.h;
    destRect2.y = destRect1.y + destRect1.h + COLUMN_SPACE;
}

void Column::move() {
    destRect1.x -= COLUMN_SPEED;
    destRect2.x = destRect1.x;
    if(destRect1.x <= -(destRect1.w) || destRect2.x <= -(destRect2.w)){
        destRect1.x = SCREEN_WIDTH;
        destRect2.x = SCREEN_WIDTH;
        destRect1.y = rand() % 200 - 300;
        destRect2.y = destRect1.y + destRect1.h + COLUMN_SPACE;

        va_cham = false;
        vuot_cot = false;
    }
}

void Column::move2(){
    destRect1.x -= COLUMN_SPEED;
    destRect2.x = destRect1.x;
    if(destRect1.x <= -(destRect1.w) || destRect2.x <= -(destRect2.w)){
        destRect1.x = SCREEN_WIDTH;
        destRect2.x = SCREEN_WIDTH;
        destRect1.y = rand() % 200 - 300;
        destRect2.y = destRect1.y + destRect1.h + COLUMN_SPACE;

        len_xuong = rand() % 2;
        va_cham = false;
        vuot_cot = false;
    }

    if(len_xuong){
        destRect1.y -= COLUMN_SPEED_Y;
        destRect2.y = destRect1.y + destRect1.h + COLUMN_SPACE;
        if(destRect2.y <= 200 ) len_xuong = (len_xuong + 1)%2;
    }
    else{
        destRect1.y += COLUMN_SPEED_Y;
        destRect2.y = destRect1.y + destRect1.h + COLUMN_SPACE;
        if(destRect2.y >= SCREEN_HEIGHT - 130) len_xuong = (len_xuong + 1)%2;
    }
}


void Column::render(SDL_Renderer* renderer) {
    SDL_RenderCopy(renderer, col1, NULL, &destRect1);
    SDL_RenderCopy(renderer, col2, NULL, &destRect2);
}
