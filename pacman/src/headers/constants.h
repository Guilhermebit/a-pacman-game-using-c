#ifndef _CONSTANTS_H
#define _CONSTANTS_H


/* Game info
 */
#define GAME_AUTHOR "Guilherme Bitencurt"
#define GAME_VERSION "1.0.0"


/* Player status
 */
#define POINTS_PER_GHOST_KILL 100
#define PLAYER_INITIAL_ROUND 1
#define PLAYER_TOTAL_LIVES 3


/* Keys
 */
#define ESC_KEY 27


/* Map
 */

// Define the possible map paths
#define NUM_PATHS 2

#define PACMAN_ICON '@'
#define EMPTY_SPACE_ICON '.'
#define VERTICAL_WALL_ICON '|'
#define HORIZONTAL_WALL_ICON '-'
#define RED_GHOST_ICON 'F'
#define POWER_PILL_ICON 'P'
#define INVALID_ENTITY_POSITION -1

/* Pacman
 */
#define MAX_PACMANS 1


/* Red Ghosts
 */
#define MAX_RED_GHOSTS 3


/* Pills
 */
#define MAX_PILLS 3
#define EXPLOSION_LIMIT_DISTANCE 1

/* Interface
 */

// drawing dimensions
#define WIDTH 7
#define HEIGHT 4

// Interface commands
#define MOVE_UP 'w'
#define MOVE_DOWN 's'
#define MOVE_RIGHT 'd'
#define MOVE_LEFT 'a'
#define EXPLODE_POWER_PILL 'b'

// ANSI color escape codes
#define ANSI_RESET "\x1b[0m"
#define ANSI_BLACK "\x1b[30m"
#define ANSI_RED "\x1b[31m"
#define ANSI_GREEN "\x1b[32m"
#define ANSI_YELLOW "\x1b[33m"
#define ANSI_BLUE "\x1b[34m"
#define ANSI_WHITE "\x1b[37m"

#define DEFAULT_COLOR ANSI_RESET // "\e[37m" // WHITE

// Interface colors (ANSI)
#define PLAYER_STATUS_COLOR ANSI_YELLOW // "\x1b[33m" // YELLOW
#define MENU_COLOR ANSI_RESET
#define MENU_CREDITS_COLOR ANSI_YELLOW
#define ERROR_MESSAGE_COLOR ANSI_RED // "\x1b[31m" // RED

// Game structure colors
#define WALL_COLOR ANSI_BLUE // "\x1b[34m" // BLUE
#define EMPTY_CELL_COLOR ANSI_BLACK // "\x1b[30m" // BLACK

// Game characteres colors
#define PACMAN_COLOR ANSI_YELLOW // "\x1b[33m" // YELLOW
#define RED_GHOST_COLOR ANSI_RED // "\x1b[31m" // RED
#define POWER_PILL_COLOR ANSI_GREEN // "\x1b[32m" // GREEN

#endif // _CONSTANTS_H