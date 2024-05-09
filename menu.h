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
        renderTexture(background.texture, background.scrollingOffset, 480, renderer);
        renderTexture(background.texture, background.scrollingOffset - background.width, 480, renderer);
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

    bool startMenu (SDL_Renderer* renderer, bool& volume) {
        SDL_Texture* start_fb = IMG_LoadTexture(renderer, "picture\\start_flappy.png");
        SDL_Texture* replay = IMG_LoadTexture(renderer, "picture\\replay.png");
        SDL_Texture* replay_click = IMG_LoadTexture(renderer, "picture\\replay_click.png");
        ScrollingBackground background_wait;
        ScrollingBackground land;
        background_wait.setTexture(IMG_LoadTexture(renderer, "picture\\background.png"));
        land.setTexture(IMG_LoadTexture(renderer,"picture\\land.png"));
        SDL_Texture* volume_on = IMG_LoadTexture(renderer, "picture\\volume_on.png");
        SDL_Texture* volume_off = IMG_LoadTexture(renderer, "picture\\volume_off.png");
        Sprite flappy_bird;
        SDL_Texture* FL_Bird_Texture = IMG_LoadTexture(renderer, "picture\\bird.png");
        flappy_bird.init(FL_Bird_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);

        flappy_bird.SetPos(SCREEN_WIDTH / 2 - 30, SCREEN_HEIGHT / 2 - 60);
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
                     if (x > 125 && x < 225 && y > 300 && y < 356) return true;
                     break;
            }

            background_wait.scroll(2);
            render_back(background_wait, renderer);
            land.scroll(2);
            render_back_land(land, renderer);

            flappy_bird.tick();
            flappy_bird.Render(renderer);

            renderTexture(start_fb, 0, 100, renderer);

            renderTexture(volume_on, SCREEN_WIDTH - 80 , 30 , renderer );

            if (event.type == SDL_MOUSEBUTTONDOWN && x > (SCREEN_WIDTH - 80) && x < (SCREEN_WIDTH - 30) && y > 30 && y < 80) volume = (volume + 1)%2;

            if (volume) {
                Mix_VolumeMusic(128);
                renderTexture( volume_on, SCREEN_WIDTH - 80 , 30 , renderer);
            } else {
                Mix_VolumeMusic(0);
                renderTexture (volume_off, SCREEN_WIDTH - 80 , 30 , renderer );
            }

            if (x > 125 && x < 225 && y > 300 && y < 356) renderTexture(replay_click, 125, 300, renderer);
            else renderTexture(replay, 125, 300, renderer);

            SDL_RenderPresent(renderer);

        }
        return false;
    }

    bool overMenu (SDL_Renderer* renderer, long Score, long maxScore) {
        SDL_Texture* Exit = IMG_LoadTexture(renderer, "picture\\quit.png");
        SDL_Texture* Exit_click = IMG_LoadTexture(renderer, "picture\\quit_click.png");
        SDL_Texture* playAgain= IMG_LoadTexture(renderer, "picture\\playAgain.jpg");
        SDL_Texture* playAgain_click= IMG_LoadTexture(renderer, "picture\\playAgain_click.png");
        SDL_Texture* gameOver = IMG_LoadTexture(renderer, "picture\\gameOver.png");
        SDL_Texture* silver = IMG_LoadTexture(renderer, "picture\\silver.png");
        SDL_Texture* honor = IMG_LoadTexture(renderer, "picture\\honor.png");
        SDL_Texture* gold = IMG_LoadTexture(renderer, "picture\\gold.png");

        TTF_Font* fontMin = loadFont("Gameplay Regular.ttf", 22);
        SDL_Color color1 = {125, 125, 125, 0};

        bool quit = false;
        SDL_Event event;
        int x, y;
        while (!quit) {
            SDL_GetMouseState (&x, &y);
            SDL_PollEvent(&event);
            if (event.type == SDL_QUIT) {
                quit = true;
            }

            renderTexture(gameOver, 50, 150, renderer);

            SDL_Texture* GradeMin = renderText(vers(Score), fontMin, color1, renderer);
            renderTexture(GradeMin, 244 , 264, renderer );
            SDL_Texture* MaxScore = renderText(vers(maxScore), fontMin, color1, renderer);
            renderTexture(MaxScore, 244 , 311, renderer);

            if (Score <= 20) renderTexture(silver, 75 , 270, renderer);
                else {
                    if (Score <= 40) renderTexture(honor, 75 , 270, renderer);
                    else renderTexture(gold, 75 , 270, renderer);
            }

            if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (x > 180 && x < (180+110) && y > 370 && y < (370+40)) return false;
                    if (x > 60 && x < (60+110) && y > 370 && y < (370+40)) {
                          return true;
                }
            }

            if (x > 180 && x < (180+110) && y > 370 && y < (370+40)) renderTexture(Exit_click, 180, 370, renderer);
            else renderTexture(Exit, 180, 370, renderer);
            if (x > 60 && x < (60+110) && y > 370 && y < (370+40)) renderTexture(playAgain_click, 60, 370, renderer);
            else renderTexture(playAgain, 60, 370, renderer);

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
                if ((x > 20 && x < 52 && y > 20 && y < 54) ||
                        (x > 120 && x < (120+110) && y > 300 && y < (300+40))) {
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

