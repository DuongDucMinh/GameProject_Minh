#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "def.h"

// MÀN HÌNH CHỜ
void wait_screen (Graphics graphics, ScrollingBackground bg, ScrollingBackground land, SDL_Texture* word_fb, Sprite& fb, SDL_Texture* replay, SDL_Texture* replay_click) {
    bool quit = false;
    SDL_Event event;
    int x, y;
    while (!quit) {
        SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 if (x > 125 && x < 225 && y > 300 && y < 356) quit = true;
                 break;
        }

        bg.scroll(2);
        graphics.render_back(bg);
        land.scroll(2);
        graphics.render_back_land(land);
        graphics.renderTexture(word_fb, 0, 100);
        if (x > 125 && x < 225 && y > 300 && y < 356) graphics.renderTexture(replay_click, 125, 300);
        else graphics.renderTexture(replay, 125, 300);
        fb.tick();
        graphics.render( 145 , 230 , fb);

        graphics.presentScene();
        SDL_Delay(17);
    }
}

// MÀN HÌNH PAUSE
/*
void pause_screen (Graphics graphics, SDL_Texture* unpause, ) {
    SDL_Event event;
    int x, y;
    SDL_PollEvent(&event);
    SDL_GetMouseState(&x, &y);
    if (event.type == SDL_QUIT) exit(0);
    else {
        if (event.type == SDL_MOUSEBUTTONDOWN && x > 20 && x < 52 && y > 20 && y < 54) {
                graphics.renderTexture(unpause, 20 , 20 );
                graphics.presentScene();
                while (true) {
                    SDL_Event e;
                    SDL_PollEvent(&e);
                    SDL_GetMouseState(&x, &y);

                    if ( e.type == SDL_QUIT ) exit(0);
                    if ( e.type == SDL_MOUSEBUTTONDOWN) {
                        if ((x > 20 && x < 52 && y > 20 && y < 54) ||
                                (x > 120 && x < (120+110) && y > 300 && y < (300+40))) {
                            SDL_Delay(100);
                            break;
                        }
                        if (x > 180 && x < (180+110) && y > 370 && y < (370+40)) exit(0);
                        if (x > 60 && x < (60+110) && y > 370 && y < (370+40)) {
                                //***
                                goto tryAgain;
                        }
                    }

                    if (x > 120 && x < (120+110) && y > 300 && y < (300+40)) graphics.renderTexture(Continue_click, 120, 300);
                    else graphics.renderTexture(Continue, 120, 300);
                    if (x > 180 && x < (180+110) && y > 370 && y < (370+40)) graphics.renderTexture(Exit_click, 180, 370);
                    else graphics.renderTexture(Exit, 180, 370);
                    if (x > 60 && x < (60+110) && y > 370 && y < (370+40)) graphics.renderTexture(playAgain_click, 60, 370);
                    else graphics.renderTexture(playAgain, 60, 370);
                    graphics.presentScene();
                }
                graphics.renderTexture(pause, 20 , 20 );
        }
    }
}
*/

#endif // MENU_H
