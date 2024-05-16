#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "def.h"

struct Menu {
    void renderTexture(SDL_Texture *texture, int x, int y, SDL_Renderer* renderer)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }
    void render_back (const ScrollingBackground& background, SDL_Renderer* renderer)
    {
        renderTexture(background.texture, background.scrollingOffset, 0, renderer);
        renderTexture(background.texture, background.scrollingOffset - background.width, 0, renderer);
    }
    void render_back_land (const ScrollingBackground& background, SDL_Renderer* renderer)
    {
        renderTexture(background.texture, background.scrollingOffset, 485, renderer);
        renderTexture(background.texture, background.scrollingOffset - background.width, 485, renderer);
    }
    // TEXT
    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
        }
    }

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor, SDL_Renderer* renderer)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
        }

        SDL_FreeSurface( textSurface );
        return texture;
    }
    void optionMenu (SDL_Renderer* renderer, Sprite& flappy_bird, ScrollingBackground& background, SDL_Texture*& bg_prev, ScrollingBackground& land, SDL_Texture*& land_prev, Column* colu1, Column* colu2, Column* colu3, long& choose) {
        SDL_Texture* bird_yell = IMG_LoadTexture(renderer, "picture\\bird\\bird_yell_pic.png");
        SDL_Texture* bird_red = IMG_LoadTexture(renderer, "picture\\bird\\bird_red_pic.png");
        SDL_Texture* bird_blue = IMG_LoadTexture(renderer, "picture\\bird\\bird_blue_pic.png");
        SDL_Texture* bg1 = IMG_LoadTexture(renderer, "picture\\map\\bg1_prev.png");
        SDL_Texture* bg2 = IMG_LoadTexture(renderer, "picture\\map\\bg2_prev.png");
        SDL_Texture* bg3 = IMG_LoadTexture(renderer, "picture\\map\\bg3_prev.png");

        SDL_Texture* Back = IMG_LoadTexture(renderer, "picture\\back.png");
        SDL_Texture* Vien = IMG_LoadTexture(renderer, "picture\\vien_green.png");

        SDL_Texture* FL_Bird_Yell_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird.png");
        SDL_Texture* FL_Bird_Blue_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird_blue.png");
        SDL_Texture* FL_Bird_Red_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird_red.png");

        TTF_Font* font = loadFont("Gameplay Regular.ttf", 30);
        SDL_Color color = {0, 0, 0, 0};

        flappy_bird.SetPos(SCREEN_WIDTH/2 - 29, 100);
        bool quit = false;
        SDL_Event event;
        int x, y;
        while (!quit) {
            SDL_GetMouseState (&x, &y);
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                     exit(0);
                     break;
                case SDL_MOUSEBUTTONDOWN:
                    if (x > 20 && x < 80 && y > 20 && y < 58) quit = true;
                    if (x > (SCREEN_WIDTH/2 - 238) && x < (SCREEN_WIDTH/2 - 180) && y > 200 && y < 242) {
                        flappy_bird.init(FL_Bird_Yell_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
                    }
                    if (x > (SCREEN_WIDTH/2 - 29) && x < (SCREEN_WIDTH/2 + 29) && y > 200 && y < 242) {
                        flappy_bird.init(FL_Bird_Red_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
                    }
                    if (x > (SCREEN_WIDTH/2 + 180) && x < (SCREEN_WIDTH/2 + 238) && y > 200 && y < 242) {
                        flappy_bird.init(FL_Bird_Blue_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
                    }
                    if (x > (SCREEN_WIDTH/2 - 266) && x < (SCREEN_WIDTH/2 - 155) && y > 350 && y < 550) {
                        bg_prev = IMG_LoadTexture(renderer, "picture\\map\\background_1.png");
                        land_prev = IMG_LoadTexture(renderer, "picture\\land\\land1.jpg");
                        background.setTexture(IMG_LoadTexture(renderer, "picture\\map\\background_1.png"));
                        land.setTexture(IMG_LoadTexture(renderer, "picture\\land\\land1.jpg"));
                        choose = 1;
                    }
                    if (x > (SCREEN_WIDTH/2 - 55) && x < (SCREEN_WIDTH/2 + 56) && y > 350 && y < 550) {
                        bg_prev = IMG_LoadTexture(renderer, "picture\\map\\background_2.png");
                        land_prev = IMG_LoadTexture(renderer, "picture\\land\\land2.png");
                        background.setTexture(IMG_LoadTexture(renderer, "picture\\map\\background_2.png"));
                        land.setTexture(IMG_LoadTexture(renderer, "picture\\land\\land2.png"));
                        choose = 2;
                    }
                    if (x > (SCREEN_WIDTH/2 + 156) && x < (SCREEN_WIDTH/2 + 267) && y > 350 && y < 550) {
                        bg_prev = IMG_LoadTexture(renderer, "picture\\map\\background_3.png");
                        land_prev = IMG_LoadTexture(renderer, "picture\\land\\land3.jpg");
                        background.setTexture(IMG_LoadTexture(renderer, "picture\\map\\background_3.png"));
                        land.setTexture(IMG_LoadTexture(renderer, "picture\\land\\land3.jpg"));
                        choose = 3;
                    }
                    break;
            }
            colu1->LoadImageColumn(renderer, choose);
            colu2->LoadImageColumn(renderer, choose);
            colu3->LoadImageColumn(renderer, choose);

            renderTexture(bg_prev, 0, 0, renderer);
            renderTexture(land_prev, 0, 485, renderer);
            renderTexture(Back, 20, 20, renderer);

            SDL_Texture* choose_char = renderText("CHOOSE CHARACTER", font, color, renderer);
            renderTexture(choose_char, SCREEN_WIDTH/2 - 175 , 20, renderer );
            SDL_Texture* choose_map = renderText("CHOOSE MAP", font, color, renderer);
            renderTexture(choose_map, SCREEN_WIDTH/2 - 105 , 280, renderer );

            renderTexture(bird_yell, SCREEN_WIDTH/2 - 238, 200, renderer);
            renderTexture(bird_red, SCREEN_WIDTH/2 - 29, 200, renderer);
            renderTexture(bird_blue, SCREEN_WIDTH/2 + 180, 200, renderer);

            renderTexture(bg1, SCREEN_WIDTH/2 - 266, 350, renderer);
            renderTexture(bg2, SCREEN_WIDTH/2 - 55, 350, renderer);
            renderTexture(bg3, SCREEN_WIDTH/2 + 156, 350, renderer);

            switch (choose) {
                case 1:
                    renderTexture(Vien, SCREEN_WIDTH/2 - 269, 347, renderer);
                    break;
                case 2:
                    renderTexture(Vien, SCREEN_WIDTH/2 - 58, 347, renderer);
                    break;
                case 3:
                    renderTexture(Vien, SCREEN_WIDTH/2 + 153, 347, renderer);
                    break;
            }

            flappy_bird.tick();
            flappy_bird.Render(renderer);

            SDL_RenderPresent(renderer);
        }
        renderTexture(bg_prev, 0, 0, renderer);
        renderTexture(land_prev, 0, 485, renderer);
        SDL_RenderPresent(renderer);
    }

    bool startMenu (SDL_Renderer* renderer, bool& volume, Sprite& flappy_bird, ScrollingBackground& background, SDL_Texture*& bg_prev, ScrollingBackground& land, SDL_Texture*& land_prev, Column* colu1, Column* colu2, Column* colu3, long& choose) {
        SDL_Texture* start_fb = IMG_LoadTexture(renderer, "picture\\start_flappy.png");
        SDL_Texture* play = IMG_LoadTexture(renderer, "picture\\click\\play.png");
        SDL_Texture* play_click = IMG_LoadTexture(renderer, "picture\\click\\play_click.png");
        SDL_Texture* option = IMG_LoadTexture(renderer, "picture\\click\\option.png");
        SDL_Texture* option_click = IMG_LoadTexture(renderer, "picture\\click\\option_click.png");
        SDL_Texture* volume_on = IMG_LoadTexture(renderer, "picture\\volume_on.png");
        SDL_Texture* volume_off = IMG_LoadTexture(renderer, "picture\\volume_off.png");
        SDL_Texture* FL_Bird_Yell_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird.png");

        bool quit = false;
        SDL_Event event;
        int x, y;
        while (!quit) {
            SDL_GetMouseState (&x, &y);
            SDL_PollEvent(&event);
            switch (event.type) {
                case SDL_QUIT:
                     exit(0);
                     break;
                case SDL_MOUSEBUTTONDOWN:
                     if (x > (SCREEN_WIDTH/2 - 75) && x < (SCREEN_WIDTH/2 + 75) && y > 300 && y < 355) return true;
                     if (x > (SCREEN_WIDTH/2 - 75) && x < (SCREEN_WIDTH/2 + 75) && y > 400 && y < 455) {
                        optionMenu(renderer, flappy_bird, background, bg_prev, land, land_prev, colu1, colu2, colu3, choose);
                     }
                     break;
            }

            background.scroll(2);
            render_back(background, renderer);
            land.scroll(2);
            render_back_land(land, renderer);

            flappy_bird.SetPos(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 60);
            flappy_bird.tick();
            flappy_bird.Render(renderer);

            renderTexture(start_fb, SCREEN_WIDTH/2 - 175, 100, renderer);

            if (event.type == SDL_MOUSEBUTTONDOWN && x > (SCREEN_WIDTH - 80) && x < (SCREEN_WIDTH - 40) && y > 40 && y < 80)
                volume = (volume + 1)%2;

            if (volume) {
                Mix_VolumeMusic(128);
                renderTexture( volume_on, SCREEN_WIDTH - 80 , 40 , renderer);
            } else {
                Mix_VolumeMusic(0);
                renderTexture (volume_off, SCREEN_WIDTH - 80 , 40 , renderer );
            }

            if (x > (SCREEN_WIDTH/2 - 75) && x < (SCREEN_WIDTH/2 + 75) && y > 300 && y < 355)
                renderTexture(play_click, SCREEN_WIDTH/2 - 75, 300, renderer);
            else renderTexture(play, SCREEN_WIDTH/2 - 75, 300, renderer);
            if (x > (SCREEN_WIDTH/2 - 75) && x < (SCREEN_WIDTH/2 + 75) && y > 400 && y < 455)
                renderTexture(option_click, SCREEN_WIDTH/2 - 75, 400, renderer);
            else renderTexture(option, SCREEN_WIDTH/2 - 75, 400, renderer);


            SDL_RenderPresent(renderer);

        }
        return false;
    }

    bool overMenu (SDL_Renderer* renderer, long Score, long maxScore) {
        SDL_Texture* Exit = IMG_LoadTexture(renderer, "picture\\click\\quit.png");
        SDL_Texture* Exit_click = IMG_LoadTexture(renderer, "picture\\click\\quit_click.png");
        SDL_Texture* playAgain= IMG_LoadTexture(renderer, "picture\\click\\playAgain.jpg");
        SDL_Texture* playAgain_click= IMG_LoadTexture(renderer, "picture\\click\\playAgain_click.png");
        SDL_Texture* gameOver = IMG_LoadTexture(renderer, "picture\\gameOver.png");
        SDL_Texture* silver = IMG_LoadTexture(renderer, "picture\\icon\\silver.png");
        SDL_Texture* honor = IMG_LoadTexture(renderer, "picture\\icon\\honor.png");
        SDL_Texture* gold = IMG_LoadTexture(renderer, "picture\\icon\\gold.png");

        TTF_Font* font = loadFont("Gameplay Regular.ttf", 22);
        SDL_Color color = {125, 125, 125, 0};

        bool quit = false;
        SDL_Event event;
        int x, y;
        while (!quit) {
            SDL_GetMouseState (&x, &y);
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            renderTexture(gameOver, SCREEN_WIDTH/2 - 125 , 150, renderer);

            SDL_Texture* GradeMin = renderText(vers(Score), font, color, renderer);
            renderTexture(GradeMin, SCREEN_WIDTH/2 + 69 , 264, renderer );
            SDL_Texture* MaxScore = renderText(vers(maxScore), font, color, renderer);
            renderTexture(MaxScore, SCREEN_WIDTH/2 + 69 , 311, renderer);

            if (Score <= 20) renderTexture(silver, SCREEN_WIDTH/2 - 100 , 270, renderer);
                else {
                    if (Score <= 40) renderTexture(honor, SCREEN_WIDTH/2 - 100 , 270, renderer);
                    else renderTexture(gold, SCREEN_WIDTH/2 - 100 , 270, renderer);
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (x > (SCREEN_WIDTH/2 + 5) && x < (SCREEN_WIDTH/2 + 115) && y > 380 && y < 420) return false;
                    if (x > (SCREEN_WIDTH/2 - 115) && x < (SCREEN_WIDTH/2 - 5) && y > 380 && y < 420) {
                          return true;
                }
            }

            if (x > (SCREEN_WIDTH/2 - 115) && x < (SCREEN_WIDTH/2 - 5) && y > 380 && y < 420)
                renderTexture(playAgain_click, SCREEN_WIDTH/2 - 115, 380, renderer);
            else renderTexture(playAgain, SCREEN_WIDTH/2 - 115, 380, renderer);
            if (x > (SCREEN_WIDTH/2 + 5) && x < (SCREEN_WIDTH/2 + 115) && y > 380 && y < 420)
                renderTexture(Exit_click, SCREEN_WIDTH/2 + 5, 380, renderer);
            else renderTexture(Exit, SCREEN_WIDTH/2 + 5, 380, renderer);

            SDL_RenderPresent(renderer);
        }
        return false;
    }

    void pause (SDL_Renderer* renderer, bool& volume) {
        SDL_Texture* unpause = IMG_LoadTexture(renderer, "picture\\resume.png");
        Mix_VolumeMusic(0);

        bool quit = false;
        SDL_Event event;
        int x, y;
        while (!quit) {
            SDL_GetMouseState (&x, &y);
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) {
                exit(0);
            }
            if ( event.type == SDL_MOUSEBUTTONDOWN) {
                if (x > 20 && x < 58 && y > 20 && y < 50) {
                    SDL_Delay(100);
                    if (volume) Mix_VolumeMusic(128);
                    quit = true;
                }
            }
            renderTexture (unpause, 20, 20, renderer);
            SDL_RenderPresent(renderer);
        }
    }
};
#endif // MENU_H

