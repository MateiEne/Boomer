#pragma once

#define NL 14
#define NC 26

#define CELL_WIDTH 49.f
#define CELL_HEIGHT 49.f

// MAP TILES
#define TILE_WIDTH 196.f
#define TILE_HEIGHT 196.f

#define TILE_WALL_L 1
#define TILE_WALL_C 0

#define TILE_BOX_L 4
#define TILE_BOX_C 2

#define TILE_FLOOR_L 2
#define TILE_FLOOR_C 2

// MAP NAMES
#define WALL 'x'
#define BOX	 'o'
#define FLOOR '.'

// COLORS
#define BG_COLOR sf::Color(186, 155, 112)

// PLAYER
#define PLAYER_WIDTH 64.f
#define PLAYER_HEIGHT 64.f

#define PLAYER_DEFAULT_POS_L 10
#define PLAYER_DEFAULT_POS_C 0

#define PLAYER_MOVE_DOWN_L 10
#define PLAYER_MOVE_DOWN_FRAMES 9

#define PLAYER_CHANGE_ANIMATION 0.1f