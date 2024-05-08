#include <bits/stdc++.h>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"
#include "def.h"
#include "game.h"
#include "column.h"
#include "Collition.h"
#include "menu.h"

SDL_Renderer* Graphics::renderer = nullptr;
SDL_Texture* Graphics::col1 = nullptr;
SDL_Texture* Graphics::col2 = nullptr;

//deque<Column*> nyc;

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

const char* vers (long c) {
    string a = to_string(c);
    return a.c_str();
}

int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    // KHỞI TẠO ÂM THANH
    Mix_Chunk *gJump = graphics.loadSound("sound\\flappy_whoosh.mp3");
    Mix_Chunk *fpass = graphics.loadSound("sound\\sound_ting.mp3");
    Mix_Chunk *gOver = graphics.loadSound("sound\\sound_gameover.mp3");
    Mix_Chunk *touch = graphics.loadSound("sound\\touch_column.mp3");

    // KHỞI TẠO HẠT GIỐNG NGẪU NHIÊN
    srand(time(NULL));

    // KHỞI TẠO ẢNH
    SDL_Texture* start_fb = graphics.loadTexture("picture\\start_flappy.png");
    SDL_Texture* replay = graphics.loadTexture("picture\\replay.png");
    SDL_Texture* replay_click = graphics.loadTexture("picture\\replay_click.png");
    SDL_Texture* Exit = graphics.loadTexture("picture\\quit.png");
    SDL_Texture* Exit_click = graphics.loadTexture("picture\\quit_click.png");
    SDL_Texture* playAgain= graphics.loadTexture("picture\\playAgain.jpg");
    SDL_Texture* playAgain_click= graphics.loadTexture("picture\\playAgain_click.png");
    SDL_Texture* Continue= graphics.loadTexture("picture\\continue.jpg");
    SDL_Texture* Continue_click= graphics.loadTexture("picture\\continue_click.png");
    SDL_Texture* pauseTab = graphics.loadTexture("picture\\pauseTab.png");
    SDL_Texture* gameOver = graphics.loadTexture("picture\\gameOver.png");
    SDL_Texture* silver = graphics.loadTexture("picture\\silver.png");
    SDL_Texture* honor = graphics.loadTexture("picture\\honor.png");
    SDL_Texture* gold = graphics.loadTexture("picture\\gold.png");
    SDL_Texture* pause = graphics.loadTexture("picture\\pause.png");
    SDL_Texture* unpause= graphics.loadTexture("picture\\resume.png");
    SDL_Texture* heart = graphics.loadTexture("picture\\heart.png");


    // KHAI BÁO KHỞI TẠO NỀN TRÔI
    ScrollingBackground background_wait;
    ScrollingBackground background;
    ScrollingBackground land;
    background_wait.setTexture(graphics.loadTexture("picture\\background.png"));
    background.setTexture(graphics.loadTexture("picture\\background_night.png"));
    land.setTexture(graphics.loadTexture("picture\\land.png"));

    // KHAI BÁO CÁI CỘT
    Column* colu = new Column();
    colu->destRect1.y = rand() % 165 - 260;
    colu->destRect2.y = colu->destRect1.y + 500;
    Graphics::col1 = graphics.loadTexture("picture\\pipe_up.png");
    Graphics::col2 = graphics.loadTexture("picture\\pipe_down.jpg");
    Uint32 startTime = SDL_GetTicks();

    // KHAI BÁO CON CHIM VÀ QUÁI
    Sprite flappy_bird;
    SDL_Texture* FL_Bird_Texture = graphics.loadTexture("picture\\bird.png");
    flappy_bird.init(FL_Bird_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);
    Sprite flappy_blue_bird;
    SDL_Texture* FL_BLUE_BiRD_Texture = graphics.loadTexture("picture\\blue_bird.png");
    flappy_blue_bird.init(FL_BLUE_BiRD_Texture, FL_BLUE_BIRD_FRAMES, FL_BLUE_BIRD_CLIPS);
    Sprite saw;
    SDL_Texture* SAW_Texture = graphics.loadTexture("picture\\saw.png");
    saw.init(SAW_Texture, SAW_FRAMES, SAW_CLIPS);
    Sprite bananas;
    SDL_Texture* BANANAS_Texture = graphics.loadTexture("picture\\Bananas.png");
    bananas.init(BANANAS_Texture, BANANAS_FRAMES, BANANAS_CLIPS);
    Sprite Collected;
    SDL_Texture* COLLECTED_Texture = graphics.loadTexture("picture\\Collected.png");
    Collected.init(COLLECTED_Texture, COLLECTED_FRAMES, COLLECTED_CLIPS);

    // KHAI BÁO CHỮ
    TTF_Font* font = graphics.loadFont("Gameplay Regular.ttf", 35);
    TTF_Font* fontMin = graphics.loadFont("Gameplay Regular.ttf", 22);
    SDL_Color color = {255, 255, 0, 0};
    SDL_Color color1 = {125, 125, 125, 0};

    long maxScore = 0;
    int a, b;

    tryAgain:

    // KHỞI TẠO VỊ TRÍ CON CHIM
    Mouse mouse(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);
    Mouse quai1(SCREEN_WIDTH + 20, rand() % (SCREEN_HEIGHT - 200) + 80);
    Mouse Saw(rand() % SCREEN_WIDTH + SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 200) + 80);
    Mouse Banana(rand() % SCREEN_WIDTH + SCREEN_WIDTH, rand() % (SCREEN_HEIGHT - 200) + 80);
    Mouse Collect(a, b);

    // MÀN HÌNH CHỜ
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

        background_wait.scroll(2);
        graphics.render_back(background_wait);
        land.scroll(2);
        graphics.render_back_land(land);
        graphics.renderTexture(start_fb, 0, 100);
        if (x > 125 && x < 225 && y > 300 && y < 356) graphics.renderTexture(replay_click, 125, 300);
        else graphics.renderTexture(replay, 125, 300);
        flappy_bird.tick();
        graphics.render( 145 , 230 , flappy_bird);

        graphics.presentScene();
        SDL_Delay(17);
    }

    long Count = 0, dem = 0, die_count = 3, v = 1;
    bool test_column = true , test_rand = true, test2 = true, test_quai1 = true, test_saw = true;

    quit = false;

    // VÒNG LẶP CHÍNH
    while (!quit ) {

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        mouse.turnSouth();
        mouse.move();

        if (currentKeyStates[SDL_SCANCODE_UP] || currentKeyStates[SDL_SCANCODE_SPACE]) {
            graphics.play(gJump);
            mouse.jump();
            mouse.move();
        }

        // TẠO NỀN TRÔI
        background.scroll(2);
        graphics.render_back(background);

        // TẠO CỘT
        if (dem >= 50) {
            comeBack_column(Count, graphics, colu, v, test2, test_rand, test_column);

            // CHIM VA CỘT
            if (mouse.touch(colu) ) {
                graphics.play(touch);
                if (test_column) {
                    test_column = false;
                    die_count--;
                    if (die_count == 0) quit = true; //if (gameOver2(mouse, )) quit = true;
                }
            }

            // VƯỢT CỘT
            if (colu->grade()) {
                    graphics.play(fpass);
                    Count++;
                    if (Count >= maxScore) maxScore = Count;
            }
        }

        // TẠO LAND
        land.scroll(2);
        graphics.render_back_land(land);

        // TẠO ĐIỂM
        SDL_Texture* Grade = graphics.renderText(vers(Count), font, color);
        graphics.renderTexture(Grade, 170 , 17 );

        // TẠO TIM
        for (int i = 1; i <= die_count; i++) {
            graphics.renderTexture( heart , 340 - 30*i , 24);
        }

        // TẠO QUÁI
        comeBack2(Count, graphics, flappy_blue_bird, quai1, test_quai1);
        comeBack (Count, graphics, saw, Saw, colu, test_saw);

        // TẠO QUẢ
        //comeBack1(Count, graphics, bananas, Banana, colu);

        // TẠO CON CHIM
        flappy_bird.tick();
        graphics.render( mouse.rect.x , mouse.rect.y , flappy_bird);

        // TẠO PAUSE
        graphics.renderTexture(pause, 20 , 20 );

        // KHI ẤN PAUSE
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


        // KHI CHIM ĂN QUẢ
        /*if (mouse.touch_ug(Banana)) {
            graphics.play(fpass);
            Collected.tick();
            graphics.render( Banana.rect.x , Banana.rect.y , Collected);
            if (Collected.currentFrame == 5) {
                Banana.rect.x  = -45;
                Collect.rect.x = -10;
                Collect.rect.y = -10;
                if (die_count < 3) {
                    die_count++;
                }
            }
        }*/

        // KHI CHIM CHẠM ĐẤT || CỘT || QUÁI
        if (mouse.touch_ug(quai1)) {
            graphics.play(touch);
            if (test_quai1) {
                test_quai1 = false;
                die_count--;
                if (die_count == 0) quit = true;
            }
        }
        if (mouse.touch_ug(Saw)) {
            graphics.play(touch);
            if (test_saw) {
                test_saw = false;
                die_count--;
                if (die_count == 0) quit = true;
            }
        }
        if (gameOver1(mouse)) quit = true;
        if (quit == true ) {
                if (!gameOver1(mouse)) {
                    while (mouse.rect.y < 440) {
                        graphics.render_back(background);
                        colu->render();
                        graphics.render_back_land(land);
                        graphics.renderTexture(Grade, 170 , 17 );
                        graphics.render( quai1.rect.x , quai1.rect.y , flappy_blue_bird);
                        graphics.render( Saw.rect.x, Saw.rect.y, saw);
                        graphics.render( Banana.rect.x, Banana.rect.y, bananas);

                        mouse.turnSouth();
                        mouse.move();
                        flappy_bird.tick();
                        graphics.render( mouse.rect.x , mouse.rect.y , flappy_bird);

                        graphics.presentScene();
                    }
                }
                graphics.play(gOver);
                graphics.renderTexture(gameOver, 50, 150);
                SDL_Texture* GradeMin = graphics.renderText(vers(Count), fontMin, color1);
                graphics.renderTexture(GradeMin, 244 , 262 );
                SDL_Texture* MaxScore = graphics.renderText(vers(maxScore), fontMin, color1);
                graphics.renderTexture(MaxScore, 244 , 311);
                if (Count <= 20) graphics.renderTexture(silver, 75 , 270);
                else {
                    if (Count <= 40) graphics.renderTexture(honor, 75 , 270);
                    else graphics.renderTexture(gold, 75 , 270);
                }

                graphics.presentScene();

                bool quit1 = false;
                while (!quit1) {
                    SDL_GetMouseState(&x, &y);
                    SDL_PollEvent(&event);
                    if (event.type == SDL_QUIT ) exit(0);
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        if (x > 180 && x < (180+110) && y > 370 && y < (370+40)) quit1 = true;
                        if (x > 60 && x < (60+110) && y > 370 && y < (370+40)) {
                                //****
                                goto tryAgain;
                        }
                    }
                    if (x > 180 && x < (180+110) && y > 370 && y < (370+40)) graphics.renderTexture(Exit_click, 180, 370);
                    else graphics.renderTexture(Exit, 180, 370);
                    if (x > 60 && x < (60+110) && y > 370 && y < (370+40)) graphics.renderTexture(playAgain_click, 60, 370);
                    else graphics.renderTexture(playAgain, 60, 370);
                    graphics.presentScene();
                }
        }

        graphics.presentScene();

        if (Count <= 10) SDL_Delay(9);
        else {
            SDL_Delay(2);
        }
        if (dem < 50) dem++;
    }

    //if (gMusic != nullptr) Mix_FreeMusic( gMusic );
    if (gJump != nullptr) Mix_FreeChunk(gJump);
    if (fpass != nullptr) Mix_FreeChunk(fpass);
    if (gOver != nullptr) Mix_FreeChunk(gOver);

    // PHÁ HỦY CON CHIM
    SDL_DestroyTexture ( FL_Bird_Texture );
    FL_Bird_Texture = nullptr;

    SDL_DestroyTexture ( gameOver );
    gameOver = nullptr;

    // PHÁ HỦY NỀN TRÔI
    SDL_DestroyTexture( background.texture );
    background.texture = nullptr;
    SDL_DestroyTexture( land.texture );
    land.texture = nullptr;

    // PHÁ HỦY CHỮ
    TTF_CloseFont( font );

    // PHÁ HỦY ẢNH
    SDL_DestroyTexture( start_fb);
    start_fb = nullptr;
    SDL_DestroyTexture( replay);
    replay = nullptr;
    SDL_DestroyTexture( background_wait.texture );
    background_wait.texture = nullptr;

    graphics.quit();
    return 0;
}






