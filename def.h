
#ifndef _DEFS__H
#define _DEFS__H

#define INITIAL_SPEED 0.25
#define INITIAL_SPEED_1 2
#define INITIAL_SPEED_2 4
#define INITIAL_SPEED_BIRD 3.5
#define BLUE_BIRD_SPEED 3
#define DOI_SPEED 4
#define SAW_SPEED 2
#define HEART 3

const int SCREEN_WIDTH = 350; // 800 350
const int SCREEN_HEIGHT = 570; // 600 480
//const char* WINDOW_TITLE = "FLAPPY BIRD GAME!";
const int COLUMN_WIDTH = 65;

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

const int BAT_CLIPS[][4] = {
    {  0, 0, 46, 30},
    { 46, 0, 46, 30},
    { 92, 0, 46, 30},
    {138, 0, 46, 30},
    {184, 0, 46, 30},
    {230, 0, 46, 30},
    {276, 0, 46, 30},
};
const int BAT_FRAMES = sizeof(BAT_CLIPS)/sizeof(int)/4;

const int SAW_CLIPS[][4] = {
    {  0, 0, 38, 38},
    { 38, 0, 38, 38},
    { 76, 0, 38, 38},
    {114, 0, 38, 38},
    {152, 0, 38, 38},
    {190, 0, 38, 38},
    {228, 0, 38, 38},
    {266, 0, 38, 38},
};
const int SAW_FRAMES = sizeof(SAW_CLIPS)/sizeof(int)/4;

const int BANANAS_CLIPS[][4] = {
    {  0, 0, 32, 32},
    { 32, 0, 32, 32},
    { 64, 0, 32, 32},
    { 96, 0, 32, 32},
    {128, 0, 32, 32},
    {160, 0, 32, 32},
    {192, 0, 32, 32},
    {224, 0, 32, 32},
    {256, 0, 32, 32},
    {288, 0, 32, 32},
    {320, 0, 32, 32},
    {352, 0, 32, 32},
    {284, 0, 32, 32},
    {416, 0, 32, 32},
    {448, 0, 32, 32},
    {480, 0, 32, 32},
    {512, 0, 32, 32},
};
const int BANANAS_FRAMES = sizeof(BANANAS_CLIPS)/sizeof(int)/4;

const int COLLECTED_CLIPS[][4] = {
    {  0, 0, 32, 32},
    { 32, 0, 32, 32},
    { 64, 0, 32, 32},
    { 96, 0, 32, 32},
    {128, 0, 32, 32},
    {160, 0, 32, 32},
};
const int COLLECTED_FRAMES = sizeof(COLLECTED_CLIPS)/sizeof(int)/4;


#endif




