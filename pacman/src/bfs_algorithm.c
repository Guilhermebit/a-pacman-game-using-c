#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "configs/debug_macros.h"
#include "headers/bfs_algorithm.h"
#include "headers/constants.h"

Queue* createQueue(int size) {
    
    Queue* queue = (Queue*)malloc(sizeof(Queue));

#ifdef DEBUG
	// Assertions to guarantee queue integrity
    debug_assert(queue != NULL, "Queue should not be null");
#endif   

    if(queue == NULL) {
	  fprintf(stderr, "Error: Failed to allocate memory for queue\n");
	  exit(EXIT_FAILURE);
	}

    queue->capacity = size;
    queue->front = queue->rear = -1;
    queue->array = (Node*)malloc(size * sizeof(Node));

#ifdef DEBUG
    debug_assert(queue->array != NULL, "Queue array should not be null");
	debug_assert(queue->capacity > 0, "Invalid queue size");
#endif

    return queue;
}

bool isEmpty(Queue* queue) {
    return queue->front == -1;
}

void enqueue(Queue* queue, Node data) {
    if (queue->rear == queue->capacity - 1) {
        printf("Queue is full. Cannot enqueue more elements.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear++;
    queue->array[queue->rear] = data;
}

Node dequeue(Queue* queue) {
    Node emptyNode = { { -1, -1 }, -1 };
    if (isEmpty(queue)) {
        return emptyNode;
    }
    Node data = queue->array[queue->front];
    if (queue->front == queue->rear) {
        queue->front = queue->rear = -1;
    } else {
        queue->front++;
    }
    return data;
}

void destroyQueue(Queue* queue) {
    free(queue->array);
    free(queue);
}

bool** createVisitedMatrix(int rows, int cols) {

    bool** visited = (bool**)malloc(rows * sizeof(bool*));

#ifdef DEBUG
    debug_assert(visited != NULL, "Visited matrix should not be null");
#endif

    for (int i = 0; i < rows; i++) {
        visited[i] = (bool*)malloc(cols * sizeof(bool));
        memset(visited[i], false, cols * sizeof(bool));
    }

    return visited;
}

void destroyVisitedMatrix(bool** visited, int rows) {
    for (int i = 0; i < rows; i++) {
        free(visited[i]);
    }
    free(visited);
}

// Define the BFS function to find the shortest path
int bfsFindShortestPath(Map* map, Position start, Position end) {

    // Check if start and end positions are the same
    if (start.x == end.x && start.y == end.y) {
        return 0;
    }

    // Create a queue for BFS
    int rows = map->rows;
    int cols = map->columns;
    Queue* queue = createQueue(rows * cols);

    bool** visited = createVisitedMatrix(rows, cols);

    // Define possible moves (up, down, left, right)
    int moves[4][2] = { {0, -1}, {0, 1}, {1, 0}, {-1, 0} };

    // Initialize the start node
    Node startNode = { start, 0 };
    enqueue(queue, startNode);
    visited[start.x][start.y] = true;

    // Perform BFS Algorithm
    while (!isEmpty(queue)) {

        Node currentNode = dequeue(queue);

        // Check if the current node is the destination
        if (currentNode.pos.x == end.x && currentNode.pos.y == end.y) {
            destroyQueue(queue);
            for (int i = 0; i < rows; i++) {
                free(visited[i]);
            }
            free(visited);
            return currentNode.distance;
        }

        // Explore neighboring cells
        for (int i = 0; i < 4; i++) {
            
            int newX = currentNode.pos.x + moves[i][0];
            int newY = currentNode.pos.y + moves[i][1];

            int validRow = newX >= 0 && newX < rows;
            int validColumn = newY >= 0 && newY < cols;

            // Check if the new position is valid
            if ((validRow && validColumn && !visited[newX][newY]) && !isWall(map, newX, newY)) {
                Node newNode = { {newX, newY}, currentNode.distance + 1 };
                enqueue(queue, newNode);
                visited[newX][newY] = true;
            }
        }
    }

    destroyQueue(queue);
    destroyVisitedMatrix(visited, rows);
 
    // If no path is found, return a large value to indicate failure
    return INT_MAX;
}