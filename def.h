
#ifndef _DEFS__H
#define _DEFS__H

#define INITIAL_SPEED 0.25
#define INITIAL_SPEED_1 2
#define INITIAL_SPEED_2 4
#define INITIAL_SPEED_BIRD 3.5
#define MONSTER_SPEED 3
#define DOI_SPEED 4
#define SAW_SPEED 2
#define COLUMN_SPEED 2
#define COLUMN_SPEED_Y 1
#define COLUMN_SPACE 125
#define COLUMN_DISTANCE 255
#define HEART 3

#define COLUMN_INTERVAL 5000

const int SCREEN_WIDTH = 700; // 800 350 700
const int SCREEN_HEIGHT = 570; // 600 480
const int COLUMN_WIDTH = 65;

const int FL_BIRD_CLIPS[][4] = {
    {  0, 0, 60, 42},
    { 60, 0, 60, 42},
    {120, 0, 60, 42},
};
const int FL_BIRD_FRAMES = sizeof(FL_BIRD_CLIPS)/sizeof(int)/4;

const int MONSTER_CLIPS[][4] = {
    {  0, 0, 64, 41},
    { 64, 0, 64, 41},
    {128, 0, 64, 41},
    {192, 0, 64, 41},
    {256, 0, 64, 41},
    {320, 0, 64, 41},
};
const int MONSTER_FRAMES = sizeof(MONSTER_CLIPS)/sizeof(int)/4;

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




