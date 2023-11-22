#include <stdio.h>
#include <stdlib.h>
#include "headers/game_map.h"
#include "configs/debug_macros.h"
#include "string.h"
#include "headers/constants.h"

const char *possibleGameMapPaths[NUM_PATHS] = {
    "../data/game_map.txt", 
    "data/game_map.txt"
};

void initializeEntityArray(EntityPosition entities[], int size) {
    for(int i = 0; i < size; i++) {
        entities[i].x = INVALID_ENTITY_POSITION;  // Set to an invalid x value
        entities[i].y = INVALID_ENTITY_POSITION;  // Set to an invalid y value
        entities[i].type = '\0';  // Set to a null character
    }
}

void getEntityPositions(Map *map, EntityPosition entities[], int maxSize, int *numEntities, char entityType) {

	int i, j;
	*numEntities = 0;
	initializeEntityArray(entities, maxSize);

    for (i = 0; i < map->rows; i++) {
        for (j = 0; j < map->columns; j++) {
            if (map->grid[i][j] == entityType) {
                entities[*numEntities].x = i;
                entities[*numEntities].y = j;
                entities[*numEntities].type = entityType;
                (*numEntities)++;
            }
        }
    }
}

void readMap(Map *map) {
	
	FILE* f;

	for(int i = 0; i < NUM_PATHS; ++i) {
	    f = fopen(possibleGameMapPaths[i], "r");
		if(f != NULL)
		   break; // map found
	}

#ifdef DEBUG	
	debug_assert(f != NULL, "Map file not found");
#endif

	if(f == NULL) {
	   fprintf(stderr, "Error reading the map\n");
	   exit(EXIT_FAILURE);
	}
	
	// read the number of rows and columns
	int result = fscanf(f, "%d %d", &(map->rows), &(map->columns));
	if(result != 2) {
	   fprintf(stderr, "Error reading map rows and columns\n");
	   fclose(f);
	   exit(EXIT_FAILURE);
	}
	
	allocateMap(map);
	
	// reads each row from the file and stores it in the map->grid
	for(int j = 0; j < map->columns; j++) {
		if(fscanf(f, "%s", map->grid[j]) == EOF)
           break;

#ifdef DEBUG
	// Print the content of map->grid[j]
	debug_print("map->grid[%d]: %s\n", j, map->grid[j]);
#endif

	}

	fclose(f); // Close the file after reading
	
}

void allocateMap(Map *map) {

	map->grid = (char**)malloc(sizeof(char*)* map->rows);

#ifdef DEBUG
	debug_assert(map->grid != NULL, "grid should not be null");
#endif

	if(map->grid == NULL) {
	  fprintf(stderr, "Failed to allocate memory for map->grid\n");
	  exit(EXIT_FAILURE);
	}
	
	int i;
	for(i = 0; i< map->rows; i++) {
		map->grid[i] = (char*)malloc(sizeof(char) * (map->columns + 1)); // +1 ensures that there is enough space for the null terminator "\0".	

#ifdef DEBUG
	debug_assert(map->grid[i] != NULL, "grid should not be null");
#endif

		if(map->grid[i] == NULL) {

		  fprintf(stderr, "Failed to allocate memory for map->grid[%d]", i);
		  releaseMap(map);
		  exit(EXIT_FAILURE);	

		}
	}	
}

void copyMap(Map *targetCopy, Map *sourceCopy) {
	
	targetCopy->rows = sourceCopy->rows;
	targetCopy->columns = sourceCopy->columns;
	
	allocateMap(targetCopy);
	int i;
	for(i = 0; i< sourceCopy->rows; i++) {
		strcpy(targetCopy->grid[i], sourceCopy->grid[i]);
	}
	
}

void releaseMap(Map *map) {
	
	int i;
	for(i = 0; i< map->rows;i++) {
		free(map->grid[i]);
	}
	free(map->grid);
}

void moveTheCharacter(Map *map, int xsource, int ysource, int xtarget, int ytarget) {
	
	// Save the character from the source cell
	char personagem = map->grid[xsource][ysource];

	// Move the character to the destination cell
	map->grid[xtarget][ytarget] = personagem;

	// Set the source cell to empty
	map->grid[xsource][ysource] = EMPTY_SPACE_ICON;
	
}

int isOutsideTheMapLimits(Map *map, int x, int y) {

	if(x < 0 || x >= map->rows || y < 0 || y >= map->columns)
	   return 1; // Outside the map limits
	
	return 0; // Inside the map limits

}

int isInsideTheTunnels(Map *map, char entityIcon, int *x, int *y) {

	if(entityIcon != PACMAN_ICON)
	   return 0;

	int leftTunnel = *x == 3 && *y < 0;
	int rightTunnel = *x == 3 && *y >= map->columns;

	if(leftTunnel) {
       *y = map->columns -1; // pacman appears in the tunnel on the right
	   return 1;
    } else if (rightTunnel) {
	   *y = 0; // pacman appears in the tunnel on the left
	   return 1;
    }

	return 0;

}

int canMove(Map *map, char entityIcon ,int x, int y) {
	return 
	    isValidPosition(map, x, y) &&
	    !isWall(map, x, y) &&
	    !isCharacter(map, entityIcon, x, y);
	
}

int isValidPosition(Map *map, int x, int y) {
	
	if(x >= map->rows || y >= map->columns)
	   return 0; // invalid position
	
	return 1; // valid position

}

int isCharacter(Map *map, char entityIcon , int x, int y) {
	
	return map->grid[x][y] == entityIcon;
	
}

int isWall(Map *map, int x, int y) {
	
	return map->grid[x][y] == VERTICAL_WALL_ICON ||
	       map->grid[x][y] == HORIZONTAL_WALL_ICON;
	       
}
