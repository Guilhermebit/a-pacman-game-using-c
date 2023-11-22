#ifndef _BFS_ALGORITHM_H_
#define _BFS_ALGORITHM_H_

#include <stdbool.h>
#include "game_map.h"

// Structure to represent positions in the map
typedef struct {
    int x, y;
} Position;

// Data structure to hold a position and its distance from the source
typedef struct {
    Position pos;
    int distance;
} Node;

// Queue data structure for BFS
typedef struct {
    Node* array;
    int front, rear, capacity;
} Queue;

// BFS Queue
Queue* createQueue(int size);
bool isEmpty(Queue* queue);
void enqueue(Queue* queue, Node data);
Node dequeue(Queue* queue);
void destroyQueue(Queue* queue);

// Visited cells

// Function to create a boolean matrix for visited cells
bool** createVisitedMatrix(int rows, int cols);
// Function to free the memory allocated for the visited matrix
void destroyVisitedMatrix(bool** visited, int rows);

// BFS shortest path function
int bfsFindShortestPath(Map* map, Position start, Position end);

#endif // _BFS_ALGORITHM_H_