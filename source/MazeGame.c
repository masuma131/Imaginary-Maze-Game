/*
 * maze_game.c
 *
 *  Created on: Dec. 2, 2024
 *      Author: masuma
 */

#include "MazeGame.h"
#include "fsl_gpio.h"        // For GPIO configurations and operations
#include "fsl_port.h"        // For port configurations and interrupt setup
#include "fsl_debug_console.h" // For PRINTF
#include "clock_config.h"    // For clock configurations (e.g., SDK_DelayAtLeastUs)
// Maze grid
int maze[MAZE_SIZE][MAZE_SIZE] = {
    {0, 1, 1, 2},
    {0, 0, 0, 0},
    {1, 0, 1, 1},
    {1, 1, 1, 0}
};

// Player position
int playerX = 0; // Start at (0,0)
int playerY = 0;

void showMaze(int x, int y) {
    for (int i = 0; i < MAZE_SIZE; i++) {
        for (int j = 0; j < MAZE_SIZE; j++) {
            if (x == j && y == i) {
                PRINTF("[ P ]");
            } else if (maze[i][j] == 1) {
                PRINTF("[ # ]");
            } else if (maze[i][j] == 2) {
                PRINTF("[ E ]");
            } else {
                PRINTF("[   ]");
            }
        }
        PRINTF("\r\n");
    }
    PRINTF("\r\n");
}

void MovePlayer(int x_tilt, int y_tilt) {
    int newX = playerX;
    int newY = playerY;

    bool isUpdated = false;


    if (x_tilt > X_TILT_THRESHOLD) {
        newX += 1;
        isUpdated = true;
        PRINTF("You tried moving RIGHT\r\n");
    } else if (x_tilt < -X_TILT_THRESHOLD) {
        newX -= 1;
        isUpdated = true;
        PRINTF("You tried moving LEFT\r\n");
    }

    if (y_tilt > Y_TILT_THRESHOLD && !isUpdated) {
        newY -= 1;
        PRINTF("You tried moving UP\r\n");
    } else if (y_tilt < -Y_TILT_THRESHOLD && !isUpdated) {
        newY += 1;
        PRINTF("You tried moving DOWN\r\n");
    }

    if (newX >= 0 && newX < MAZE_SIZE && newY >= 0 && newY < MAZE_SIZE && maze[newY][newX] != 1) {
        if (newX != playerX || newY != playerY) {
            playerX = newX;
            playerY = newY;


            GreenLedBlink();

            PRINTF("Not a wall! You have successfully moved to the position\r\n");
            showMaze(playerX, playerY);

            if (maze[playerY][playerX] == 2) {
                PRINTF("You reached the endpoint! Game over!\r\n");
                BlueLedBlink();
            }
        }
    } else {
        //PRINTF("Hit a wall at position: (%d, %d)\r\n", newX, newY);
    	PRINTF("Hit a wall!\r\n");
        RedLedBlink();
    }
}

// LED setup function
void LedSetup(void) {
    red_led_setup();
    green_led_setup();
    blue_led_setup();
}

// Red LED blink function
void RedLedBlink(void) {
    func_red_led_on();
    SDK_DelayAtLeastUs(1000000, CLOCK_GetFreq(kCLOCK_CoreSysClk)); // 1-second delay
    func_red_led_off();
}

// Green LED blink function
void GreenLedBlink(void) {
    func_green_led_on();
    SDK_DelayAtLeastUs(500000, CLOCK_GetFreq(kCLOCK_CoreSysClk)); // 0.5-second delay
    func_green_led_off();
}

// Blue LED blink function
void BlueLedBlink(void) {
    for (int i = 0; i < 5; i++) { // Blink 5 times
        func_blue_led_on();
        SDK_DelayAtLeastUs(500000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
        func_blue_led_off();
        SDK_DelayAtLeastUs(500000, CLOCK_GetFreq(kCLOCK_CoreSysClk));
    }
}


void resetGame(void)
{
    playerX = 0; // Reset player X position
    playerY = 0; // Reset player Y position

    // Reset LEDs
    func_red_led_off();
    func_green_led_off();
    func_blue_led_off();


    PRINTF("Game reset! Starting at position: (0, 0)\r\n");
    // Clear the resetRequested flag
}



