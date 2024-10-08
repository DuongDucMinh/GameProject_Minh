#include <bits/stdc++.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
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
    SDL_Texture* bg_prev = graphics.loadTexture("picture\\map\\background_1.png");
    SDL_Texture* land_prev = graphics.loadTexture("picture\\land\\land1.jpg");

    ScrollingBackground background;
    ScrollingBackground land;
    background.setTexture(graphics.loadTexture("picture\\map\\background_1.png"));
    land.setTexture(graphics.loadTexture("picture\\land\\land1.jpg"));

    Column* colu1 = new Column();
    colu1->LoadImageColumn(graphics.renderer, 1);
    int wcol = colu1->destRect1.w;
    int hcol = colu1->destRect1.h;
    Column* colu2 = new Column();
    colu2->LoadImageColumn(graphics.renderer, 1);
    Column* colu3 = new Column();
    colu3->LoadImageColumn(graphics.renderer, 1);

    Sprite flappy_bird;
    SDL_Texture* FL_Bird_Yell_Texture = graphics.loadTexture("picture\\bird\\bird.png");
    SDL_Texture* FL_Bird_Blue_Texture = graphics.loadTexture("picture\\bird\\bird_blue.png");
    SDL_Texture* FL_Bird_Red_Texture = graphics.loadTexture("picture\\bird\\bird_red.png");

    Sprite monster;
    SDL_Texture* MONSTER_Texture = graphics.loadTexture("picture\\sprite\\monster.png");
    monster.init(MONSTER_Texture, MONSTER_FRAMES, MONSTER_CLIPS);
    Sprite bat;
    SDL_Texture* BAT_Texture = graphics.loadTexture("picture\\sprite\\bat_fly.png");
    bat.init(BAT_Texture, BAT_FRAMES, BAT_CLIPS);
    Sprite saw;
    Sprite saw2;
    SDL_Texture* SAW_Texture = graphics.loadTexture("picture\\sprite\\saw.png");
    saw.init(SAW_Texture, SAW_FRAMES, SAW_CLIPS);
    saw2.init(SAW_Texture, SAW_FRAMES, SAW_CLIPS);
    Sprite bananas;
    SDL_Texture* BANANAS_Texture = graphics.loadTexture("picture\\sprite\\Bananas.png");
    bananas.init(BANANAS_Texture, BANANAS_FRAMES, BANANAS_CLIPS);
    Sprite melon;
    SDL_Texture* MELON_Texture = graphics.loadTexture("picture\\sprite\\Melon.png");
    melon.init(MELON_Texture, BANANAS_FRAMES, BANANAS_CLIPS);
    Sprite Collected;
    SDL_Texture* COLLECTED_Texture = graphics.loadTexture("picture\\sprite\\Collected.png");
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

    long Count = 0, die_count = HEART, maxScore, choose = 1, choose_bird = 1;

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
            continue_ = menu.startMenu(graphics.renderer, volume_on, flappy_bird, background, bg_prev, land, land_prev, choose, choose_bird);
            Count = 0;
            die_count = HEART;
            flappy_bird.SetPos(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
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
            monster.SetPos(SCREEN_WIDTH + 20, rand() % (SCREEN_HEIGHT - 220) + 40);
            bat.SetPos(SCREEN_WIDTH + 20, rand() % (SCREEN_HEIGHT - 220) + 40);
            bananas.SetBatDau();
            melon.SetBatDau();
            saw.SetBatDau();
            saw2.SetBatDau();
            colu1->LoadImageColumn(graphics.renderer, choose);
            colu2->LoadImageColumn(graphics.renderer, choose);
            colu3->LoadImageColumn(graphics.renderer, choose);
            colu1->SetBatDau(wcol, hcol, SCREEN_WIDTH);
            colu2->SetBatDau(wcol, hcol, SCREEN_WIDTH + COLUMN_DISTANCE);
            colu3->SetBatDau(wcol, hcol, SCREEN_WIDTH + 2*COLUMN_DISTANCE);
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

            if (Count >= 7) {
                colu1->move2();
                colu2->move2();
                colu3->move2();
            }
            else {
                colu1->move();
                colu2->move();
                colu3->move();
            }
            colu1->render(graphics.renderer);
            colu2->render(graphics.renderer);
            colu3->render(graphics.renderer);

            bool VaCot1a = flappy_bird.VaCham(colu1->destRect1);
            bool VaCot1b = flappy_bird.VaCham(colu1->destRect2);
            if((VaCot1a || VaCot1b) && !colu1->va_cham){
                die_count--;
                colu1->va_cham = true;
                if (volume_on) graphics.play(touch);
            }

            bool VaCot2a = flappy_bird.VaCham(colu2->destRect1);
            bool VaCot2b = flappy_bird.VaCham(colu2->destRect2);
            if((VaCot2a || VaCot2b) && !colu2->va_cham){
                die_count--;
                colu2->va_cham = true;
                if (volume_on) graphics.play(touch);
            }

            bool VaCot3a = flappy_bird.VaCham(colu3->destRect1);
            bool VaCot3b = flappy_bird.VaCham(colu3->destRect2);
            if((VaCot3a || VaCot3b) && !colu3->va_cham){
                die_count--;
                colu3->va_cham = true;
                if (volume_on) graphics.play(touch);
            }

            if(flappy_bird.VuotCot(colu1) || flappy_bird.VuotCot(colu2) || flappy_bird.VuotCot(colu3) ){
                Count++;
                if (volume_on) graphics.play(fpass);
                if (maxScore < Count) maxScore = Count;
            }

            land.scroll(2);
            graphics.render_back_land(land);

            if (Count >= 9) {
                monster.moveMonster();
                monster.tick();
                monster.Render(graphics.renderer);
                bool VaMonster = flappy_bird.VaCham(monster.GetRect());
                if(VaMonster && !monster.check){
                    die_count--;
                    monster.check = true;
                    if (volume_on) graphics.play(touch);
                }

            }

            if (Count >= 10) {
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
            }
            if (Count >= 8) {
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

            if (Count >= 4) {
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

            if (Count >= 8) {
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

            SDL_Texture* Grade = graphics.renderText(vers(Count), font, color);
            graphics.renderTexture(Grade, SCREEN_WIDTH/2 - 10 , 17 );
            for (int i = 1; i <= die_count; i++) {
                graphics.renderTexture( heart , SCREEN_WIDTH - 20 - 30*i , 24);
            }

            graphics.renderTexture(pause, 20 , 20 );
            if ((event.type == SDL_MOUSEBUTTONDOWN && x > 20 && x < 58 && y > 20 && y < 60) ) menu.pause(graphics.renderer, volume_on);

            graphics.presentScene();

            SDL_DestroyTexture(Grade); Grade = NULL;

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

    SDL_DestroyTexture(pause); pause = NULL;
    SDL_DestroyTexture(heart); heart = NULL;
    SDL_DestroyTexture(bg_prev); bg_prev = NULL;
    SDL_DestroyTexture(land_prev); land_prev = NULL;
    SDL_DestroyTexture(FL_Bird_Yell_Texture); FL_Bird_Yell_Texture = NULL;
    SDL_DestroyTexture(FL_Bird_Blue_Texture); FL_Bird_Blue_Texture = NULL;
    SDL_DestroyTexture(FL_Bird_Red_Texture); FL_Bird_Red_Texture = NULL;
    SDL_DestroyTexture(MONSTER_Texture); MONSTER_Texture = NULL;
    SDL_DestroyTexture(BAT_Texture); BAT_Texture = NULL;
    SDL_DestroyTexture(SAW_Texture); SAW_Texture = NULL;
    SDL_DestroyTexture(BANANAS_Texture); BANANAS_Texture = NULL;
    SDL_DestroyTexture(MELON_Texture); MELON_Texture = NULL;
    SDL_DestroyTexture(COLLECTED_Texture); COLLECTED_Texture = NULL;
    TTF_CloseFont( font );

    if (gJump != nullptr) Mix_FreeChunk(gJump);
    if (fpass != nullptr) Mix_FreeChunk(fpass);
    if (gOver != nullptr) Mix_FreeChunk(gOver);
    if (touch != nullptr) Mix_FreeChunk(touch);
    if (pop != nullptr) Mix_FreeChunk(pop);
    if (gMusic != nullptr) Mix_FreeMusic(gMusic);

    graphics.quit();

    return 0;
}






