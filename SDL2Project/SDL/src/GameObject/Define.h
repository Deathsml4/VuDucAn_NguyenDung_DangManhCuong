#pragma once

#define GAME_TITLE "Dig It Up"

#define MAX_CREATURES 20
#define MAX_ENTITIES 30

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 700
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
#define S_MENU "Data/Sounds/01_Main.wav"

#define S_PLAYER_WALK "Data/Sounds/Deerclops_Footstep.wav"
#define S_PLAYER_ATTACK "Data/Sounds/Deerclops_Swipe.wav"
#define S_PLAYER_BREAK_ROCK "Data/Sounds/Deerclops_Ice_Big.wav"
#define S_PLAYER_EAT "Data/Sounds/nom-nom-nom.wav"

#define S_OBJECT_FALL "Data/Sounds/Deerclops_Fall_Snow.wav"

#define S_MOB_SLEEP "Data/Sounds/Deerclops_Distant_Voice.wav"
#define S_MOB_ATTACK "Data/Sounds/Deerclops_Attack_Voice.wav"
#define	S_MOB_DEATH "Data/Sounds/Deerclops_Death_Voice.wav"

#define S_BACKGROUND_MUSIC_1 "Data/Sounds/17_Working_Through_Winter.wav"

#define T_BACKGROUND_1 "Ship_Graveyard_Terrain_Texture.png"

#define T_MOB_INVALID "sprite/DST_Steam_Animated_Sticker_Chester.png"
#define T_MOB_SLEEP_TEXTURE "sprite/Splumonkey_Sleep.png"
#define T_MOB_ATTACK_TEXTURE "sprite/Splumonkey_Attack.png"
#define T_MOB_CHASE_TEXTURE "sprite/Splumonkey_Run.png"

#define T_CHARACTER_WEBBER_DOWN "sprite/351px-Frog_Webber_jump_down.png"
#define T_CHARACTER_WEBBER_UP "sprite/342px-Frog_Webber_jump_up2.png"
#define T_CHARACTER_WEBBER_SIDE "sprite/357px-Frog_Webber_jump_side2.png"
#define T_CHARACTER_WILSON_DOWN "sprite/375px-Player_Sneaky-down.png"
#define T_CHARACTER_WILSON_UP "sprite/375px-Player_Sneaky-up.png"
#define T_CHARACTER_WILSON_SIDE "sprite/375px-Player_Sneaky-side.png"
#define T_CHARACTER_ATTACK "fire-sword-attack.png"

#define T_ITEM_INVALID "Star.png"
#define T_ITEM_LOG "CD_log.png"
#define T_ITEM_BERRIES "CD_berries.png"
#define T_ITEM_ROPE "CD_rope.png"
#define T_ITEM_GRASS "CD_cutgrass.png"
#define T_ITEM_TWIGS "CD_twigs.png"
#define T_ITEM_FRUIT "CD_pumpkin.png"
#define T_ITEM_ROCKS "Rocks.png"

#define T_MAP_INVALID "Blue_Fungus_Turf_Texture.png"
#define T_MAP_PLAIN "Wild_Plains_Turf_Texture.png"
#define T_MAP_WATER "Ship_Graveyard_Terrain_Texture.png"

#define T_OBJECT_INVALID ""
#define T_OBJECT_TREE "300px-A_Lumpy_Evergreen.png"
#define T_OBJECT_BUSH "300px-Berry_Bush_Build.png"
#define T_OBJECT_GRASS "300px-Tall_Grass.png"
#define T_OBJECT_CROP "Grass_Tuft.png"
#define T_OBJECT_DEATHBUSH "300px-Sapling.png"
#define T_OBJECT_ROCK "Boulder.png"
#define T_OBJECT_CHESS "Chest_Build.png"
#define T_OBJECT_GATE "Celestial_Portal_Build.png"

#define T_BUTTON_CLOSE "btn_close.png"
#define T_BUTTON_HELP "btn_help.png"
#define T_BUTTON_MUSIC_ON "Music_on.png"
#define T_BUTTON_MUSIC_OFF "Music_off.png"
#define T_BUTTON_TRY_AGAIN "Try_again.png"
#define T_BUTTON_BACK_TO_MENU "Back_to_menu.png"

#define T_HITBOX_CORNER "l.png"
#define T_HITBOX_TARGET "star.png"

#define F_CONSOLAS "Data/Text/Consolas.ttf"