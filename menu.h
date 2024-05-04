#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"

struct Play {
    SDL_Event event;
    int x, y;
    void setEvent (SDL_Event &_event) {
        event = _event;
    }
    bool OpenMenu () {
        bool quit = false;
        while (!quit) {
            while (SDL_PollEvent(&event)) {
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    SDL_GetMouseState(&x, &y);
                    if (x > 125 && x < 225 && y > 300 && y < 356) quit = true;
                }
            }
        }
        return quit;
    }
};


