#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "def.h"
#include "column.h"
#include "menu.h"

SDL_Renderer* Graphics::renderer = nullptr;
SDL_Texture* Graphics::col1 = nullptr;
SDL_Texture* Graphics::col2 = nullptr;

using namespace std;

void waitUntilKeyPressed()
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();
    srand(time(NULL));

    Menu menu;

    Mix_Music *gMusic = graphics.loadMusic("sound\\nhacnen.mp3");
    graphics.play(gMusic);
    Mix_Chunk *gJump = graphics.loadSound("sound\\flappy_whoosh.mp3");
    Mix_Chunk *fpass = graphics.loadSound("sound\\sound_ting.mp3");
    Mix_Chunk *gOver = graphics.loadSound("sound\\sound_gameover.mp3");
    Mix_Chunk *touch = graphics.loadSound("sound\\touch_column.mp3");
    Mix_Chunk *pop = graphics.loadSound("sound\\pop_sound.mp3");

    SDL_Texture* pause = graphics.loadTexture("picture\\pause.png");
    SDL_Texture* heart = graphics.loadTexture("picture\\heart.png");

    ScrollingBackground background;
    ScrollingBackground land;
    background.setTexture(graphics.loadTexture("picture\\background_night.png"));
    land.setTexture(graphics.loadTexture("picture\\land.png"));

    Column* colu = new Column();
    colu->LoadImageColumn(graphics.renderer);
    Uint32 startTime = SDL_GetTicks();
    int wcol = colu->destRect1.w;
    int hcol = colu->destRect1.h;

    Sprite flappy_bird;
    SDL_Texture* FL_Bird_Texture = graphics.loadTexture("picture\\bird.png");
    flappy_bird.init(FL_Bird_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
    Sprite flappy_blue_bird;
    SDL_Texture* FL_BLUE_BiRD_Texture = graphics.loadTexture("picture\\blue_bird.png");
    flappy_blue_bird.init(FL_BLUE_BiRD_Texture, FL_BLUE_BIRD_FRAMES, FL_BLUE_BIRD_CLIPS);
    Sprite bat;
    SDL_Texture* BAT_Texture = graphics.loadTexture("picture\\bat_fly.png");
    bat.init(BAT_Texture, BAT_FRAMES, BAT_CLIPS);
    Sprite saw;
    Sprite saw2;
    SDL_Texture* SAW_Texture = graphics.loadTexture("picture\\saw.png");
    saw.init(SAW_Texture, SAW_FRAMES, SAW_CLIPS);
    saw2.init(SAW_Texture, SAW_FRAMES, SAW_CLIPS);
    Sprite bananas;
    SDL_Texture* BANANAS_Texture = graphics.loadTexture("picture\\Bananas.png");
    bananas.init(BANANAS_Texture, BANANAS_FRAMES, BANANAS_CLIPS);
    Sprite melon;
    SDL_Texture* MELON_Texture = graphics.loadTexture("picture\\Melon.png");
    melon.init(MELON_Texture, BANANAS_FRAMES, BANANAS_CLIPS);
    Sprite Collected;
    SDL_Texture* COLLECTED_Texture = graphics.loadTexture("picture\\Collected.png");
    Collected.init(COLLECTED_Texture, COLLECTED_FRAMES, COLLECTED_CLIPS);

    TTF_Font* font = graphics.loadFont("Gameplay Regular.ttf", 35);
    SDL_Color color = {255, 255, 0, 0};

    bool wait = true;
    bool quit = false;
    bool start_ = true;
    bool continue_ = false;
    bool lose_ = false;
    bool volume_on = true;

    SDL_Event event;
    int x, y;

    long Count = 0, die_count = HEART, maxScore;

    ifstream in_file("D:\\C++\\GameProject\\maxScore.txt");
    if (in_file.is_open()) {
        in_file >> maxScore;
    }
    in_file.close();

    while (!quit ) {

        if(start_){
            lose_ = false;
            start_ = false;
            wait = true;
            continue_ = menu.startMenu(graphics.renderer, volume_on);
            Count = 0;
            die_count = HEART;
            flappy_bird.SetPos(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
            flappy_blue_bird.SetPos(SCREEN_WIDTH + 20, rand() % (SCREEN_HEIGHT - 220) + 40);
            bat.SetPos(SCREEN_WIDTH + 20, rand() % (SCREEN_HEIGHT - 220) + 40);
            bananas.SetBatDau();
            melon.SetBatDau();
            saw.SetBatDau();
            saw2.SetBatDau();
            colu->SetBatDau(wcol, hcol);
        }
        else if(continue_){
            start_ = false;
            lose_ = false;

            SDL_PollEvent(&event);
            SDL_GetMouseState(&x, &y);
            if (event.type == SDL_QUIT) exit(0);

            background.scroll(2);
            graphics.render_back(background);

            const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_SPACE]) {
                if (volume_on) graphics.play(gJump);
                flappy_bird.jump();
            }
            flappy_bird.move();

            bool VaManHinh = flappy_bird.VaManHinh();
            if(VaManHinh){
                die_count--;
                if (volume_on) graphics.play(touch);
            }

            if (Count >= 10) colu->move2();
            else colu->move();
            colu->render(graphics.renderer);

            bool VaCot1 = flappy_bird.VaCham(colu->destRect1);
            bool VaCot2 = flappy_bird.VaCham(colu->destRect2);
            if((VaCot1 || VaCot2) && !colu->va_cham){
                die_count--;
                colu->va_cham = true;
                if (volume_on) graphics.play(touch);
            }
            if(flappy_bird.VuotCot(colu)){
                Count++;
                if (volume_on) graphics.play(fpass);
                if (maxScore < Count) maxScore = Count;
            }

            land.scroll(2);
            graphics.render_back_land(land);

            if (Count >= 12) {
                flappy_blue_bird.moveChimXanh();
                flappy_blue_bird.tick();
                flappy_blue_bird.Render(graphics.renderer);
                bool VaChimXanh = flappy_bird.VaCham(flappy_blue_bird.GetRect());
                if(VaChimXanh && !flappy_blue_bird.check){
                    die_count--;
                    flappy_blue_bird.check = true;
                    if (volume_on) graphics.play(touch);
                }
            }

            if (Count >= 15) {
                bat.moveDoi();
                bat.tick();
                bat.Render(graphics.renderer);
                bool VaDoi = flappy_bird.VaCham(bat.GetRect());
                if(VaDoi && !bat.check){
                    die_count--;
                    bat.check = true;
                    if (volume_on) graphics.play(touch);
                }
            }

            if (Count >= 3) {
                saw.moveSaw();
                saw.tick();
                saw.Render(graphics.renderer);
                bool VaSaw = flappy_bird.VaCham(saw.GetRect());
                if(VaSaw && !saw.check){
                    die_count--;
                    saw.check = true;
                    if (volume_on) graphics.play(touch);
                }
                saw2.moveSaw();
                saw2.tick();
                saw2.Render(graphics.renderer);
                bool VaSaw2 = flappy_bird.VaCham(saw2.GetRect());
                if(VaSaw2 && !saw2.check){
                    die_count--;
                    saw2.check = true;
                    if (volume_on) graphics.play(touch);
                }
            }

            if (die_count <= 0){
                lose_ = true;
                continue_ = false;
                start_ = false;
            }

            if (Count >= 5) {
                Collected.SetPos((int)bananas.x, (int)bananas.y);
                bananas.moveSaw();
                bananas.tick();
                bananas.Render(graphics.renderer);
                bool VaBanana = flappy_bird.VaCham(bananas.GetRect());
                if(VaBanana && !bananas.check){
                    if (die_count < HEART) die_count++;
                    bananas.check = true;
                    if (volume_on) graphics.play(pop);
                }
                if(bananas.check){
                    Collected.tick();
                    Collected.Render(graphics.renderer);
                    if(Collected.currentFrame == 5){
                        bananas.check = false;
                        bananas.SetPos(rand() % SCREEN_WIDTH + SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 220) + 40);
                    }
                }
            }

            if (Count >= 10) {
                Collected.SetPos((int)melon.x, (int)melon.y);
                melon.moveSaw();
                melon.tick();
                melon.Render(graphics.renderer);
                bool VaMelon = flappy_bird.VaCham(melon.GetRect());
                if(VaMelon && !melon.check){
                    if (die_count < HEART) die_count++;
                    melon.check = true;
                    if (volume_on) graphics.play(pop);
                }
                if(melon.check){
                    Collected.tick();
                    Collected.Render(graphics.renderer);
                    if(Collected.currentFrame == 5){
                        melon.check = false;
                        melon.SetPos(rand() % SCREEN_WIDTH + SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 220) + 40);
                    }
                }
            }

            flappy_bird.tick();
            flappy_bird.Render(graphics.renderer);

            graphics.renderTexture(pause, 20 , 20 );
            if (event.type == SDL_MOUSEBUTTONDOWN && x > 20 && x < 52 && y > 20 && y < 54) menu.pause(graphics.renderer, volume_on);

            SDL_Texture* Grade = graphics.renderText(vers(Count), font, color);
            graphics.renderTexture(Grade, 170 , 17 );
            for (int i = 1; i <= die_count; i++) {
                graphics.renderTexture( heart , 340 - 30*i , 24);
            }

            graphics.presentScene();

            if(wait){
                wait = false;
                waitUntilKeyPressed();
            }

            SDL_Delay(9);
            }
        else if(lose_){
            lose_ = false;
            continue_ = false;
            if (volume_on) graphics.play(gOver);
            start_ = menu.overMenu(graphics.renderer, Count, maxScore);
        }

        else quit = true;
    }

    ofstream out_file("D:\\C++\\GameProject\\maxScore.txt");
    if (out_file.is_open()) {
        out_file << maxScore;
    }
    out_file.close();

    if (gJump != nullptr) Mix_FreeChunk(gJump);
    if (fpass != nullptr) Mix_FreeChunk(fpass);
    if (gOver != nullptr) Mix_FreeChunk(gOver);
    if (touch != nullptr) Mix_FreeChunk(touch);
    if (pop != nullptr) Mix_FreeChunk(pop);
    if (gMusic != nullptr) Mix_FreeMusic(gMusic);

    graphics.quit();

    return 0;
}






