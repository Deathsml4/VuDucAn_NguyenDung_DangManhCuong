#pragma once


#define MAX_CREATURES 20
#define MAX_ENTITIES 30

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 760
#define LIMIT_FPS 60

#define CHAR_W 40
#define CHAR_H 50

#define GRID_UNITS 50

#define CHUNK_UNITS 11
#define CHUNK_HEIGHT CHUNK_UNITS*GRID_UNITS
#define CHUNK_SIZE CHUNK_UNITS*CHUNK_UNITS
#define PLAYER_START (CHUNK_UNITS/2)*GRID_UNITS

#define MAP_START_X SCREEN_WIDTH/2-PLAYER_START
#define MAP_START_Y SCREEN_HEIGHT/2-PLAYER_START

#define MOB_DENSITY CHUNK_SIZE / 40