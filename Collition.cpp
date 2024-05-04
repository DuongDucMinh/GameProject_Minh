#include "Collition.h"

bool Collision::Collised(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    return SDL_HasIntersection(&rectA, &rectB);
}

