/*
 * maze_game.h
 *
 *  Created on: Dec. 2, 2024
 *      Author: masum
 */

#ifndef MAZEGAME_H_
#define MAZEGAME_H_

#include <stdint.h>
#include <stdbool.h>

// Maze configuration
#define MAZE_SIZE 4
#define X_TILT_THRESHOLD 200
#define Y_TILT_THRESHOLD 130

// Maze grid and player position
extern int maze[MAZE_SIZE][MAZE_SIZE];
extern int playerX; // Current player position X
extern int playerY; // Current player position Y


// Function declarations
void showMaze(int x, int y);
void MovePlayer(int x_tilt, int y_tilt);
void setupResetButton(void);
void resetGame(void);
void SW2_GPIOD_IRQHANDLER(void);

// LED functions
void LedSetup(void);
void RedLedBlink(void);
void GreenLedBlink(void);
void BlueLedBlink(void);

void red_led_setup(void);
void green_led_setup(void);
void blue_led_setup(void);
void func_red_led_on(void);
void func_red_led_off(void);
void func_green_led_on(void);
void func_green_led_off(void);
void func_blue_led_on(void);
void func_blue_led_off(void);


#endif /* MAZEGAME_H_ */
