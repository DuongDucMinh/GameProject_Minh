#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <cstdlib> // for rand() and srand()
#include <ctime>
#include "graphics.h"
#include "column.h"
#include "Collition.h"

#define INITIAL_SPEED 0.3
#define INITIAL_SPEED_1 2
#define INITIAL_SPEED_2 4

bool inside(int x, int y, SDL_Rect r) {
    return x > r.x && x < r.x+r.w && y > r.y && y < r.y+r.h;
}

bool overlap(const SDL_Rect& r1, const SDL_Rect& r2) {
    return inside(r1.x, r1.y, r2) || inside(r1.x + r1.w, r1.y, r2) ||
            inside(r1.x, r1.y+r1.h, r2) || inside(r1.x+r1.w, r1.y+r1.h, r2);
}

struct Mouse {
    SDL_Rect rect;
    double dx = 0, dy = 0;
    double speed = INITIAL_SPEED;
    double speed1 = INITIAL_SPEED_1;
    double speed2 = INITIAL_SPEED_2;

    Mouse(int x, int y) {
        rect.x = x;
        rect.y = y;
        rect.h = 42;
        rect.w = 60;
    }

    bool touch(const Column* colum) {
        return overlap(rect, colum->destRect1) || overlap(rect, colum->destRect2);
    }

    bool touch_ug(const Mouse mouse) {
        return overlap(rect, mouse.rect);
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
    void turnWest_quai() {
        dy = 0;
        dx = -speed2;
    }
    void turnWest_nor() {
        dy = 0;
        dx = -speed1;
    }

};

bool gameOver1(const Mouse& mouse) {
    return mouse.rect.x < 0 || mouse.rect.x >= SCREEN_WIDTH ||
           mouse.rect.y < 0 || mouse.rect.y >= SCREEN_HEIGHT - 130;
}

bool gameOver2(const Mouse& mouse, const Column* colum) {
    return Collision::Collised(mouse.rect, colum->destRect1) || Collision::Collised(mouse.rect , colum->destRect2) ;
}

void comeBack(int Count, Graphics graphics, Sprite& object, Mouse& mouse) {
    if (Count > 10) {
        object.tick();
        graphics.render( mouse.rect.x , mouse.rect.y , object);
        mouse.turnWest_nor();
        mouse.move();
        if (mouse.rect.x < -44) {
            mouse.rect.x = rand() % SCREEN_WIDTH + SCREEN_WIDTH;
            mouse.rect.y = rand() % (SCREEN_HEIGHT - 180) + 60;
        }
    }
}

void comeBack2(int Count, Graphics graphics, Sprite& object, Mouse& mouse, bool& test4) {
    if (Count > 20) {
        object.tick();
        graphics.render( mouse.rect.x , mouse.rect.y , object);
        mouse.turnWest_quai();
        mouse.move();
        if (mouse.rect.x < -44) {
            test4 = true;
            mouse.rect.x = SCREEN_WIDTH + 20;
            mouse.rect.y = rand() % (SCREEN_HEIGHT - 180) + 60;
        }
    }
}

#endif // GAME_H

