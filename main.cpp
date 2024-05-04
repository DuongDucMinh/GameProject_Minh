#include <queue>
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

std::queue<Column*> nyc;

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

    // KHỞI TẠO TIẾNG KÊU KHI NHẢY
    Mix_Chunk *gJump = graphics.loadSound("sound\\flappy_whoosh.mp3");

    // KHỞI TẠO TIẾNG TING KHI CHIM QUA CỘT
    Mix_Chunk *fpass = graphics.loadSound("sound\\sound_ting.mp3");

    // KHỞI TẠO ÂM THANH KHI THUA
    Mix_Chunk *gOver = graphics.loadSound("sound\\sound_gameover.mp3");


    // KHỞI TẠO HẠT GIỐNG NGẪU NHIÊN
    srand(time(NULL));

    // KHỞI TẠO CỘT
    Column* colu = new Column();

    // KHOI TAO ANH
    SDL_Texture* start_fb = graphics.loadTexture("picture\\start_flappy.png");
    SDL_Texture* replay = graphics.loadTexture("picture\\replay.png");
    SDL_Texture* replay_click = graphics.loadTexture("picture\\replay_click.png");
    SDL_Texture* Exit = graphics.loadTexture("picture\\quit.png");
    SDL_Texture* Exit_click = graphics.loadTexture("picture\\quit_click.png");
    SDL_Texture* playAgain= graphics.loadTexture("picture\\playAgain.jpg");
    SDL_Texture* playAgain_click= graphics.loadTexture("picture\\playAgain_click.png");
    SDL_Texture* gameOver = graphics.loadTexture("picture\\gameOver.png");
    SDL_Texture* silver = graphics.loadTexture("picture\\silver.png");
    SDL_Texture* honor = graphics.loadTexture("picture\\honor.png");
    SDL_Texture* gold = graphics.loadTexture("picture\\gold.png");
    SDL_Texture* pause = graphics.loadTexture("picture\\pause.png");
    SDL_Texture* unpause= graphics.loadTexture("picture\\resume.png");

    // KHAI BÁO KHỞI TẠO NỀN TRÔI
    ScrollingBackground background_wait;
    ScrollingBackground background;
    ScrollingBackground land;
    background_wait.setTexture(graphics.loadTexture("picture\\background.png"));
    background.setTexture(graphics.loadTexture("picture\\background_night.png"));
    land.setTexture(graphics.loadTexture("picture\\land.png"));

    // KHAI BÁO CÁI CỘT
    Graphics::col1 = graphics.loadTexture("picture\\pipe_up.png");
    Graphics::col2 = graphics.loadTexture("picture\\pipe_down.jpg");
    Uint32 startTime = SDL_GetTicks();

    // KHAI BÁO CON CHIM
    Sprite flappy_bird;
    SDL_Texture* FL_Bird_Texture = graphics.loadTexture("picture\\bird.png");
    flappy_bird.init(FL_Bird_Texture, FL_BIRD_FRAMES, FL_BIRD_CLIPS);

    // KHAI BÁO CHỮ
    TTF_Font* font = graphics.loadFont("Gameplay Regular.ttf", 35);
    TTF_Font* fontMin = graphics.loadFont("Gameplay Regular.ttf", 22);
    SDL_Color color = {255, 255, 0, 0};
    SDL_Color color1 = {125, 125, 125, 0};

    long maxScore = 0;

    tryAgain:

    // KHỞI TẠO VỊ TRÍ BAN ĐẦU CON CHIM HIỆN RA
    Mouse mouse(SCREEN_WIDTH / 3, SCREEN_HEIGHT / 3);

    //test wait
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

    long Count = 0, dem = 0;

    quit = false;

    while (!quit ) {
        //SDL_GetMouseState(&x, &y);
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 exit(0);
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 if (x > 20 && x < (20+32) && y > 20 && y < (20+34)) quit = true;
                 break;
        }

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
            Uint32 currentTime = SDL_GetTicks();
            Uint32 elapsedTime = currentTime - startTime;
            if (elapsedTime > delayTime) {
                colu = new Column();
                colu->destRect1.y = rand() % 165 - 260;
                colu->destRect2.y = colu->destRect1.y + 500;
                nyc.push(colu);
                startTime = currentTime;
            }

            while (!nyc.empty()) {
                nyc.front()->update();
                if (mouse.touch(nyc.front())) {
                        quit = true; //if (gameOver2(mouse, )) quit = true;
                }

                nyc.front()->render();

                if (nyc.front()->destRect1.x + COLUMN_WIDTH < 0) {
                    nyc.pop();
                } else {
                    break;
                }
            }

            if (nyc.front()->grade()) {
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
        graphics.renderTexture(Grade, 170 , 21 );

        // TẠO CON CHIM
        flappy_bird.tick();
        graphics.render( mouse.rect.x , mouse.rect.y , flappy_bird);

        // TẠO PAUSE
        graphics.renderTexture(pause, 20 , 20 );


        // HIỆU ỨNG KHI CHIM CHẠM ĐẤT || CỘT
        if (gameOver1(mouse)) quit = true;
        if (quit == true ) {
                if (!gameOver1(mouse)) {
                    while (mouse.rect.y < 440) {
                        graphics.render_back(background);
                        nyc.front()->render();
                        graphics.render_back_land(land);
                        graphics.renderTexture(Grade, 170 , 21 );

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
                graphics.renderTexture(GradeMin, 247 , 262 );
                SDL_Texture* MaxScore = graphics.renderText(vers(maxScore), fontMin, color1);
                graphics.renderTexture(MaxScore, 247 , 311);
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
                    if (event.type == SDL_MOUSEBUTTONDOWN) {
                        if (x > 180 && x < (180+110) && y > 370 && y < (370+40)) quit1 = true;
                        if (x > 60 && x < (60+110) && y > 370 && y < (370+40)) {
                                nyc.pop();
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






