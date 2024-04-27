#pragma once


#define MAX_CREATURES 20
#define MAX_ENTITIES 30

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 720
#define LIMIT_FPS 60

#define CHAR_W 70
#define CHAR_H 80

#define GRID_UNITS 90

#define CHUNK_UNITS 55
#define CHUNK_HEIGHT CHUNK_UNITS*GRID_UNITS
#define CHUNK_SIZE CHUNK_UNITS*CHUNK_UNITS
#define PLAYER_START (CHUNK_UNITS/2)*GRID_UNITS

#define MAP_START_X SCREEN_WIDTH/2-PLAYER_START
#define MAP_START_Y SCREEN_HEIGHT/2-PLAYER_START

#define MOB_DENSITY CHUNK_SIZE / 10
#define MOB_SPAWN_CD 1000

#define ITEM_SIZE 30
#define HOLDING_ITEM_SIZE 40

#define INTERACT_CD 20
#define ATTACK_RANGE CHAR_W*2
#define ATTACK_CD 50
#define ATTACK_ANIMATION_DURATION 10
#define HOLD_ITEM_CD 10
#define HUNGER_DURATION 180
#define THIRST_DURATION 300
#define HEAL_DURATION 50

#define MOB_BASE_HP 80
#define MOB_ATTACK_CD 100
#define MOB_MOVE_DURATION 100
#define MOB_VISION 500

#define S_BG_SOUND "Data/Sounds/Swstyletheme.wav"
#define S_GAMEOVER "Data/Sounds/Werepig_of_London.wav"