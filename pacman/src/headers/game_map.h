#ifndef _MAP_H_
#define _MAP_H_

// Map data
typedef struct {
	char** grid;
	int rows; // 7
	int columns; // 15
} Map;

typedef struct {
    int x;
    int y;
    char type;
} EntityPosition;


void readMap(Map *map);
void copyMap(Map *targetCopy, Map *sourceCopy);
void allocateMap(Map *map);
void releaseMap(Map *map);

// Initialize an array of EntityPosition
void initializeEntityArray(EntityPosition entities[], int size);

// Gets the positions of entities on the map
void getEntityPositions(Map *map, EntityPosition entities[], int maxSize, int *numEntities, char entityType);

// Handle the movement on the map
void moveTheCharacter(Map *map, int xsource, int ysource, int xtarget, int ytarget);

// Other checks
int isOutsideTheMapLimits(Map *map, int x, int y);
int isInsideTheTunnels(Map *map, char entityIcon, int *x, int *y);
int canMove(Map *map, char entityIcon, int x, int y);
int isValidPosition(Map *map, int x, int y);
int isCharacter(Map *map, char entityIcon , int x, int y);
int isWall(Map *map, int x, int y);

#endif // _MAP_H_