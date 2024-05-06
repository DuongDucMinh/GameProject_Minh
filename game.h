#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "graphics.h"
#include "column.h"
#include "Collition.h"

#define INITIAL_SPEED 0.3

bool inside(int x, int y, SDL_Rect r) {
    return x > r.x && x < r.x+r.w && y > r.y && y < r.y+r.h;
}

bool overlap(const SDL_Rect& r1, const SDL_Rect& r2) {
    return inside(r1.x, r1.y, r2) || inside(r1.x + r1.w, r1.y, r2) ||
            inside(r1.x, r1.y+r1.h, r2) || inside(r1.x+r1.w, r1.y+r1.h, r2);
}

struct Mouse {
    SDL_Rect rect;
    //int x, y;
    double dx = 0, dy = 0;
    double speed = INITIAL_SPEED;

    Mouse(int x, int y) {
        rect.x = x;
        rect.y = y;
        rect.h = 42;
        rect.w = 60;
    }

    bool touch(const Column* colum) {
        return overlap(rect, colum->destRect1) || overlap(rect, colum->destRect2);
    }

    void move() {
        rect.x += dx;
        rect.y += dy;
    }
    void turnNorth() {
        dy = -speed;
        dx = 0;
    }
    void turnSouth() {
        dy += speed ;
        dx = 0;

    }
    void turnWest() {
        dy = 0;
        dx = -speed;
    }
    void turnEast() {
        dy = 0;
        dx = speed;
    }

    void jump () {
        dy = -speed * 8 ;
        dx = 0;
    }

};

bool gameOver1(const Mouse& mouse) {
    return mouse.rect.x < 0 || mouse.rect.x >= SCREEN_WIDTH ||
           mouse.rect.y < 0 || mouse.rect.y >= SCREEN_HEIGHT - 130;
}

bool gameOver2(const Mouse& mouse, const Column* colum) {
    return Collision::Collised(mouse.rect, colum->destRect1) || Collision::Collised(mouse.rect , colum->destRect2) ;
}


#endif // GAME_H

