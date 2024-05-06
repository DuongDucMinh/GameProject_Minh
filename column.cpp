
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

void Column::update_up(long& v, long Count, bool& test2) {
    if (Count > 20) {
        if (Count == 10*v) v++;
        if (destRect1.y >= -260 && test2) {
            destRect1.y -= v;
            destRect2.y -= v;
            if (destRect1.y < -260) test2 = false;
        } else {
            if (destRect1.y <= -95 && !test2) {
                destRect1.y += v;
                destRect2.y += v;
            }
            else test2 = true;
        }
    }
}

void Column::update_down(long& v, long Count, bool& test2) {
    if (Count > 20) {
        if (Count == 10*v) v++;
        if (destRect1.y <= -95 && test2) {
            destRect1.y += v;
            destRect2.y += v;
            if (destRect1.y > -95) test2 = false;
        } else {
            if (destRect1.y >= -260 && !test2) {
                destRect1.y -= v;
                destRect2.y -= v;
            }
            else test2 = true;
        }
    }
}

void Column::render() {
    SDL_RenderCopy(Graphics::renderer, Graphics::col1, NULL, &destRect1);
    SDL_RenderCopy(Graphics::renderer, Graphics::col2, NULL, &destRect2);
}

bool Column::grade() {
    return destRect1.x == 64;
}

