#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "def.h"
#include "column.h"

using namespace std;

const char* vers (long c) {
    string a = to_string(c);
    return a.c_str();
}

// THÊM PHẦN HOẠT HÌNH - NHÂN VẬT HOẠT ĐỘNG
struct Sprite
{
    double x = 0, dx = 0;
    double y = 0, dy = 0;
    double width = 0;
    double height = 0;

    bool check = false;

    SDL_Texture* texture;
    vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, const int _clips [][4]) {
        texture = _texture;
        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
        width = clips[0].w;
        height = clips[0].h;
    }
    void tick() {
        currentFrame = (currentFrame + 1) % clips.size();
    }
    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
    void SetPos(const int& x_, const int& y_){
        x = x_;
        y= y_;
    }
    void SetBatDau(){
        x = SCREEN_WIDTH + 20;
        y = rand() % (SCREEN_HEIGHT - 40);
    }
    SDL_Rect GetRect(){
        SDL_Rect rect = {x, y, width, height};
        return rect;
    }
    void jump(){
        dy = -INITIAL_SPEED_BIRD;
    }
    void move(){
        dy += INITIAL_SPEED;
        y += dy;
    }
    bool VaManHinh(){
        if (y <= 0) {
            y = 0;
            return true;
        }
        if( y + width >= SCREEN_HEIGHT ) {
            y = SCREEN_HEIGHT - width;
            return true;;
        }
        return false;
    }
    void Render(SDL_Renderer* renderer){
        const SDL_Rect* clip = getCurrentClip();
        SDL_Rect renderquad = {x, y, width, height};
        SDL_RenderCopy(renderer, texture, clip, &renderquad);
    }
    bool VaCham(const SDL_Rect& object){
        double left = object.x;
        double right = object.x +object.w;
        double top = object.y;
        double bottom = object.y + object.h;

        if((x <= right && ( x + width >= left)) && ( y <= bottom && (y + width) >= top ) ) return true;
        return false;
    }
    bool VuotCot(Column* col){
        if(x > (col->destRect1.x + col->destRect1.w) && !col->vuot_cot){
            col->vuot_cot = true;
            return true;
        }
        return false;
    }
    //Chim xanh
    void moveChimXanh(){
        x -= BLUE_BIRD_SPEED;
        if( x < -width ){
            check = false;
            x = SCREEN_WIDTH*2;
            y = rand() % (SCREEN_HEIGHT - 200) + 80;
        }
    }
    //Saw
    void moveSaw(){
        x -= SAW_SPEED;
        if( x < -width ){
            check = false;
            x = SCREEN_WIDTH*2;
            y = rand() % (SCREEN_HEIGHT - 200) + 80;
        }
    }
};

// THÊM PHẦN NỀN TRÔI
struct ScrollingBackground
{
    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset -= distance;
        if( scrollingOffset < 0 ) { scrollingOffset = width; }
    }
};

struct Graphics {
    static SDL_Renderer *renderer;
    static SDL_Texture* col1;
    static SDL_Texture* col2;
	SDL_Window *window;

	void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

	void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow("FLAPPY BIRD GAME!", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
        }
        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
        }

    }

    void prepareScene()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 256);
        SDL_RenderClear(renderer);
    }

	void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void quit()
    {
        TTF_Quit();
        Mix_Quit();
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    // THÊM PHẦN NẠP TEXT
    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
        }
    }

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor)
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

    // THÊM HÀM PHẦN BACKGROUND TRÔI
    void render_back (const ScrollingBackground& background)
    {
        renderTexture(background.texture, background.scrollingOffset, 0);
        renderTexture(background.texture, background.scrollingOffset - background.width, 0);
    }
    void render_back_land (const ScrollingBackground& background)
    {
        renderTexture(background.texture, background.scrollingOffset, 480);
        renderTexture(background.texture, background.scrollingOffset - background.width, 480);
    }


    // THÊM PHẦN HOẠT HÌNH NHÂN VẬT HOẠT ĐỘNG
    void render (int x, int y, const Sprite& sprite)
    {
        const SDL_Rect* clip = sprite.getCurrentClip();
        SDL_Rect renderQuad = {x, y, clip->w, clip->h};
        SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
    }

    // THÊM PHẦN MUSIC
    Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                           "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }

    Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
    }
    void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel( -1, gChunk, 0 );
        }
    }

};


#endif // _GRAPHICS__H

