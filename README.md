# PacMan Game
[![Build Pacman Game with Make](https://github.com/Guilhermebit/a-pacman-game-using-c-tests/actions/workflows/build-pacman.yml/badge.svg)](https://github.com/Guilhermebit/a-pacman-game-using-c-tests/actions/workflows/build-pacman.yml)
[![licence mit](https://img.shields.io/badge/licence-MIT-blue.svg)](https://github.com/Guilhermebit/a-pacman-game-using-c/blob/master/LICENSE)

A **Pac-Man** Game developed in **C** language

## Screenshots

### Pac-Man Game

![screenshot_pacman_game](https://github.com/user-attachments/assets/aabc40db-845c-446d-a0e4-af8c828ab52a)


### Debug Mode
![screenshot_pacman_debug](https://github.com/user-attachments/assets/878a56fd-2f57-478c-a2f0-e3af331cc71d)

![screenshot_pacman_assert](https://github.com/user-attachments/assets/5c4d60f9-c89b-4164-8734-c348b3ad116e)


## :cloud: Overview
This project was developed with the aim of obtaining a better understanding of some concepts in the C language, such as:
+ Basic Input and Output 
+ Arrays and Strings
+ Dynamic Memory Allocation
+ Pointers
+ Asserts
+ Macros
+ Debug

## :video_game: Game Features

### AI Ghosts and Pathfinding

One of the key features of this Pac-Man game is the implementation of a Breadth-First Search (BFS) algorithm in the artificial intelligence (AI) of the ghosts. The BFS algorithm enhances gameplay by allowing ghosts to intelligently navigate the maze and pursue the Pac-Man through the shortest possible path.

### Resource Management

The game incorporates resource management techniques, including efficient memory allocation.

## :rocket: Installation
1. **Clone the repository:**
```
$ git clone https://github.com/Guilhermebit/a-pacman-game-using-c.git
```
2. **Navigate to the project directory:**
```
$ cd a-pacman-game-using-c\pacman
```
3. **Build the game:**

+ For Windows

Download the MinGW: https://sourceforge.net/projects/mingw/

Run the following command:
```
mingw32-make all
```
+ For Linux

Run the commands:
```
sudo apt update

sudo apt install make

sudo apt install gcc
```
Run the following command:
```
make all
```
4. **Have Fun!** 😎

