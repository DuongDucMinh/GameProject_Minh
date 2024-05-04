
#include "column.h"
#include "graphics.h"
#include <queue>

Column::Column() {
    destRect1.w = 65;
    destRect1.h = 373;
    destRect1.x = 350;
    destRect1.y ;
    destRect2.w = 65;
    destRect2.h = 373;
    destRect2.x = 350;
    destRect2.y ;
}

Column:: ~Column() {}

void Column::update() {
    destRect1.x -= 2;
    destRect2.x -= 2;
}

void Column::render() {
    SDL_RenderCopy(Graphics::renderer, Graphics::col1, NULL, &destRect1);
    SDL_RenderCopy(Graphics::renderer, Graphics::col2, NULL, &destRect2);
}

bool Column::grade() {
    return destRect1.x == 114-50;
}
