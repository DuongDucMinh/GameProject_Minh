
#ifndef _DEFS__H
#define _DEFS__H

const int SCREEN_WIDTH = 350; // 800 350
const int SCREEN_HEIGHT = 570; // 600 480
//const char* WINDOW_TITLE = "FLAPPY BIRD GAME!";
const int COLUMN_WIDTH = 65;
const int delayTime = 2000;

const int FL_BIRD_CLIPS[][4] = {
    {  0, 0, 60, 42},
    { 60, 0, 60, 42},
    {120, 0, 60, 42},
};
const int FL_BIRD_FRAMES = sizeof(FL_BIRD_CLIPS)/sizeof(int)/4;

const int FL_BLUE_BIRD_CLIPS[][4] = {
    {  0, 0, 44, 42},
    { 44, 0, 44, 42},
    { 88, 0, 44, 42},
    {132, 0, 44, 42},
    {  0,42, 44, 42},
    { 44,42, 44, 42},
    { 88,42, 44, 42},
    {132,42, 44, 42},
    {  0,84, 44, 42},
    { 44,84, 44, 42},
    { 88,84, 44, 42},
    {132,84, 44, 42},
};
const int FL_BLUE_BIRD_FRAMES = sizeof(FL_BLUE_BIRD_CLIPS)/sizeof(int)/4;


#endif




