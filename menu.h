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
    void optionMenu (SDL_Renderer* renderer, Sprite& flappy_bird, ScrollingBackground& background, SDL_Texture*& bg_prev, ScrollingBackground& land, SDL_Texture*& land_prev, long& choose, long& choose_bird) {
        SDL_Texture* bird_yell = IMG_LoadTexture(renderer, "picture\\bird\\bird_yell_pic.png");
        SDL_Texture* bird_red = IMG_LoadTexture(renderer, "picture\\bird\\bird_red_pic.png");
        SDL_Texture* bird_blue = IMG_LoadTexture(renderer, "picture\\bird\\bird_blue_pic.png");
        SDL_Texture* bg1 = IMG_LoadTexture(renderer, "picture\\map\\bg1_prev.png");
        SDL_Texture* bg2 = IMG_LoadTexture(renderer, "picture\\map\\bg2_prev.png");
        SDL_Texture* bg3 = IMG_LoadTexture(renderer, "picture\\map\\bg3_prev.png");
        SDL_Texture* background_1 = IMG_LoadTexture(renderer, "picture\\map\\background_1.png");
        SDL_Texture* background_2 = IMG_LoadTexture(renderer, "picture\\map\\background_2.png");
        SDL_Texture* background_3 = IMG_LoadTexture(renderer, "picture\\map\\background_3.png");
        SDL_Texture* land1 = IMG_LoadTexture(renderer, "picture\\land\\land1.jpg");
        SDL_Texture* land2 = IMG_LoadTexture(renderer, "picture\\land\\land2.png");
        SDL_Texture* land3 = IMG_LoadTexture(renderer, "picture\\land\\land3.jpg");

        SDL_Texture* Back = IMG_LoadTexture(renderer, "picture\\back.png");
        SDL_Texture* Vien = IMG_LoadTexture(renderer, "picture\\vien_green.png");

        SDL_Texture* FL_Bird_Yell_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird.png");
        SDL_Texture* FL_Bird_Blue_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird_blue.png");
        SDL_Texture* FL_Bird_Red_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird_red.png");

        TTF_Font* font = loadFont("Gameplay Regular.ttf", 30);
        SDL_Color color = {0, 0, 0, 0};
        SDL_Texture* choose_char = renderText("CHOOSE CHARACTER", font, color, renderer);
        SDL_Texture* choose_map = renderText("CHOOSE MAP", font, color, renderer);

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
                        choose_bird = 1;
                    }
                    if (x > (SCREEN_WIDTH/2 - 29) && x < (SCREEN_WIDTH/2 + 29) && y > 200 && y < 242) {
                        flappy_bird.init(FL_Bird_Red_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
                        choose_bird = 2;
                    }
                    if (x > (SCREEN_WIDTH/2 + 180) && x < (SCREEN_WIDTH/2 + 238) && y > 200 && y < 242) {
                        flappy_bird.init(FL_Bird_Blue_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
                        choose_bird = 3;
                    }
                    if (x > (SCREEN_WIDTH/2 - 266) && x < (SCREEN_WIDTH/2 - 155) && y > 350 && y < 550) {
                        bg_prev = background_1;
                        land_prev = land1;
                        choose = 1;
                    }
                    if (x > (SCREEN_WIDTH/2 - 55) && x < (SCREEN_WIDTH/2 + 56) && y > 350 && y < 550) {
                        bg_prev = background_2;
                        land_prev = land2;
                        choose = 2;
                    }
                    if (x > (SCREEN_WIDTH/2 + 156) && x < (SCREEN_WIDTH/2 + 267) && y > 350 && y < 550) {
                        bg_prev = background_3;
                        land_prev = land3;
                        choose = 3;
                    }
                    break;
            }

            renderTexture(bg_prev, 0, 0, renderer);
            renderTexture(land_prev, 0, 485, renderer);
            renderTexture(Back, 20, 20, renderer);

            renderTexture(choose_char, SCREEN_WIDTH/2 - 175 , 20, renderer );
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

        switch (choose) {
            case 1:
                background.setTexture(IMG_LoadTexture(renderer, "picture\\map\\background_1.png"));
                land.setTexture(IMG_LoadTexture(renderer, "picture\\land\\land1.jpg"));
                break;
            case 2:
                background.setTexture(IMG_LoadTexture(renderer, "picture\\map\\background_2.png"));
                land.setTexture(IMG_LoadTexture(renderer, "picture\\land\\land2.png"));
                break;
            case 3:
                background.setTexture(IMG_LoadTexture(renderer, "picture\\map\\background_3.png"));
                land.setTexture(IMG_LoadTexture(renderer, "picture\\land\\land3.jpg"));
                break;
        }
        renderTexture(bg_prev, 0, 0, renderer);
        renderTexture(land_prev, 0, 485, renderer);
        SDL_RenderPresent(renderer);

        SDL_DestroyTexture(FL_Bird_Yell_Texture); FL_Bird_Yell_Texture = NULL;
        SDL_DestroyTexture(FL_Bird_Blue_Texture); FL_Bird_Blue_Texture = NULL;
        SDL_DestroyTexture(FL_Bird_Red_Texture); FL_Bird_Red_Texture = NULL;
        SDL_DestroyTexture(bird_yell); bird_yell = NULL;
        SDL_DestroyTexture(bird_red); bird_red = NULL;
        SDL_DestroyTexture(bird_blue); bird_blue = NULL;
        SDL_DestroyTexture(bg1); bg1 = NULL;
        SDL_DestroyTexture(bg2); bg2 = NULL;
        SDL_DestroyTexture(bg3); bg3 = NULL;
        SDL_DestroyTexture(land1); land1 = NULL;
        SDL_DestroyTexture(land2); land2 = NULL;
        SDL_DestroyTexture(land3); land3 = NULL;
        SDL_DestroyTexture(background_1); background_1 = NULL;
        SDL_DestroyTexture(background_2); background_2 = NULL;
        SDL_DestroyTexture(background_3); background_3 = NULL;
        SDL_DestroyTexture(choose_char); choose_char = NULL;
        SDL_DestroyTexture(choose_map); choose_map = NULL;
        SDL_DestroyTexture(Back); Back = NULL;
        SDL_DestroyTexture(Vien); Vien = NULL;
        TTF_CloseFont( font );
    }

    bool startMenu (SDL_Renderer* renderer, bool& volume, Sprite& flappy_bird, ScrollingBackground& background, SDL_Texture*& bg_prev, ScrollingBackground& land, SDL_Texture*& land_prev, long& choose, long& choose_bird) {
        SDL_Texture* start_fb = IMG_LoadTexture(renderer, "picture\\start_flappy.png");
        SDL_Texture* play = IMG_LoadTexture(renderer, "picture\\click\\play.png");
        SDL_Texture* play_click = IMG_LoadTexture(renderer, "picture\\click\\play_click.png");
        SDL_Texture* option = IMG_LoadTexture(renderer, "picture\\click\\option.png");
        SDL_Texture* option_click = IMG_LoadTexture(renderer, "picture\\click\\option_click.png");
        SDL_Texture* volume_on = IMG_LoadTexture(renderer, "picture\\volume_on.png");
        SDL_Texture* volume_off = IMG_LoadTexture(renderer, "picture\\volume_off.png");
        SDL_Texture* background_1 = IMG_LoadTexture(renderer, "picture\\map\\background_1.png");
        SDL_Texture* background_2 = IMG_LoadTexture(renderer, "picture\\map\\background_2.png");
        SDL_Texture* background_3 = IMG_LoadTexture(renderer, "picture\\map\\background_3.png");
        SDL_Texture* land1 = IMG_LoadTexture(renderer, "picture\\land\\land1.jpg");
        SDL_Texture* land2 = IMG_LoadTexture(renderer, "picture\\land\\land2.png");
        SDL_Texture* land3 = IMG_LoadTexture(renderer, "picture\\land\\land3.jpg");
        SDL_Texture* FL_Bird_Yell_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird.png");
        SDL_Texture* FL_Bird_Blue_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird_blue.png");
        SDL_Texture* FL_Bird_Red_Texture = IMG_LoadTexture(renderer, "picture\\bird\\bird_red.png");

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
                     if (x > (SCREEN_WIDTH/2 - 75) && x < (SCREEN_WIDTH/2 + 75) && y > 300 && y < 355) quit = true;
                     if (x > (SCREEN_WIDTH/2 - 75) && x < (SCREEN_WIDTH/2 + 75) && y > 400 && y < 455) {
                        optionMenu(renderer, flappy_bird, background, bg_prev, land, land_prev, choose, choose_bird);
                     }
                     break;
            }

            background.scroll(2);
            render_back(background, renderer);
            land.scroll(2);
            render_back_land(land, renderer);

            switch (choose_bird) {
            case 1:
                flappy_bird.init(FL_Bird_Yell_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
                break;
            case 2:
                flappy_bird.init(FL_Bird_Red_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
                break;
            case 3:
                flappy_bird.init(FL_Bird_Blue_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
                break;
            }
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

            switch (choose) {
                case 1:
                    bg_prev = background_1;
                    land_prev = land1;
                    break;
                case 2:
                    bg_prev = background_2;
                    land_prev = land2;
                    break;
                case 3:
                    bg_prev = background_3;
                    land_prev = land3;
                    break;
            }

        }

        SDL_DestroyTexture(start_fb); start_fb = NULL;
        SDL_DestroyTexture(play); play = NULL;
        SDL_DestroyTexture(play_click); play_click = NULL;
        SDL_DestroyTexture(option); option = NULL;
        SDL_DestroyTexture(option_click); option_click = NULL;
        SDL_DestroyTexture(volume_on); volume_on = NULL;
        SDL_DestroyTexture(volume_off); volume_off = NULL;
        SDL_DestroyTexture(FL_Bird_Yell_Texture); FL_Bird_Yell_Texture = NULL;
        SDL_DestroyTexture(land1); land1 = NULL;
        SDL_DestroyTexture(land2); land2 = NULL;
        SDL_DestroyTexture(land3); land3 = NULL;
        SDL_DestroyTexture(background_1); background_1 = NULL;
        SDL_DestroyTexture(background_2); background_2 = NULL;
        SDL_DestroyTexture(background_3); background_3 = NULL;
        SDL_DestroyTexture(FL_Bird_Yell_Texture); FL_Bird_Yell_Texture = NULL;
        SDL_DestroyTexture(FL_Bird_Blue_Texture); FL_Bird_Blue_Texture = NULL;
        SDL_DestroyTexture(FL_Bird_Red_Texture); FL_Bird_Red_Texture = NULL;

        return quit;
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

        bool quit = false, over = false;
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

            if (x > (SCREEN_WIDTH/2 - 115) && x < (SCREEN_WIDTH/2 - 5) && y > 380 && y < 420)
                renderTexture(playAgain_click, SCREEN_WIDTH/2 - 115, 380, renderer);
            else renderTexture(playAgain, SCREEN_WIDTH/2 - 115, 380, renderer);
            if (x > (SCREEN_WIDTH/2 + 5) && x < (SCREEN_WIDTH/2 + 115) && y > 380 && y < 420)
                renderTexture(Exit_click, SCREEN_WIDTH/2 + 5, 380, renderer);
            else renderTexture(Exit, SCREEN_WIDTH/2 + 5, 380, renderer);

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (x > (SCREEN_WIDTH/2 + 5) && x < (SCREEN_WIDTH/2 + 115) && y > 380 && y < 420) {
                    over = false;
                    quit = true;
                }
                if (x > (SCREEN_WIDTH/2 - 115) && x < (SCREEN_WIDTH/2 - 5) && y > 380 && y < 420) {
                    over = true;
                    quit = true;
                }
            }
            SDL_RenderPresent(renderer);

            SDL_DestroyTexture(GradeMin); GradeMin = NULL;
            SDL_DestroyTexture(MaxScore); MaxScore = NULL;
        }
        SDL_DestroyTexture(Exit); Exit = NULL;
        SDL_DestroyTexture(Exit_click); Exit_click = NULL;
        SDL_DestroyTexture(playAgain); playAgain = NULL;
        SDL_DestroyTexture(playAgain_click); playAgain_click = NULL;
        SDL_DestroyTexture(gameOver); gameOver = NULL;
        SDL_DestroyTexture(silver); silver = NULL;
        SDL_DestroyTexture(honor); honor = NULL;
        SDL_DestroyTexture(gold); gold = NULL;
        TTF_CloseFont( font );

        return over;
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
        SDL_DestroyTexture(unpause); unpause = NULL;
    }
};
#endif // MENU_H

