
/*
 * maze_game.c
 *
 *  Created on: Nov. 30, 2024
 *      Author: masuma
 */
/*  SDK Included Files */
#include "pin_mux.h"
#include "clock_config.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include <stdio.h>
#include "peripherals.h"
#include "accelerometer.h"
#include "MazeGame.h"


void setupResetButton(void);
void SW2_GPIOD_IRQHANDLER(void);

/*!
 * @brief Main function
 */

int main(void)
{

    bool isThereAccel = false; //Variable to check if the accelerometer is present
    BOARD_InitBootPins(); // Initialize pins for peripherals
    BOARD_InitBootClocks(); // Set up the clock configurations
    BOARD_I2C_ReleaseBus(); // Release the I2C bus if locked
    BOARD_I2C_ConfigurePins(); // Configure I2C pins
    BOARD_InitDebugConsole(); // Initialize debug console for output

    PRINTF("\r\nI2C example -- Read Accelerometer Value\r\n");
    //SW2_GPIOD_IRQHANDLER(); // Handle reset button press (called to simulate initial setup)

    // Initialize I2C handle for communication with accelerometer
    I2C_MasterTransferCreateHandle(BOARD_ACCEL_I2C_BASEADDR, &g_m_handle, i2c_master_callback, NULL);

    // Check for accelerometer presence and initialize
    isThereAccel = I2C_ReadAccelWhoAmI();

    if (isThereAccel)
    {
        uint8_t readBuff[7]; // Buffer to store accelerometer data
        int16_t x, y; // Variables to store X and Y tilt values
        uint8_t databyte = 0; // Temporary variable for accelerometer configuration
        uint8_t write_reg = 0; // Variable to store register address

        // Put the accelerometer into standby mode (low-power state)
        write_reg = ACCEL_CTRL_REG1; // Control register (A special memory location used to configure and control the operation of a accelerometer.)
        databyte = 0; // Value to put the device into standby mode
        I2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);

        // Configure the accelerometer range to +/-4g
        //(Note: Configuring the accelerometer range to ±4g sets its measurement capacity to detect accelerations from -4g to +4g, where 1g equals 9.8 m/s².
        //This range is suitable for applications involving moderate dynamic movements, ensuring accurate detection without signal saturation.)
        write_reg = ACCEL_XYZ_DATA_CFG;
        databyte = 0x01;
        I2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);

        // Set data rate to 200Hz and activate the accelerometer (Setting the data rate to 200 Hz configures the accelerometer to sample acceleration data 200 times per second, enabling the detection of rapid movements. )
        write_reg = ACCEL_CTRL_REG1;
        databyte = 0x0D;
        I2C_WriteAccelReg(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, write_reg, databyte);

        //Our Code
        //Led setup
        LedSetup();
        PRINTF("Reading accelerometer values continuously:\r\n");
        // Show the initial maze state
        // Setup reset button
        setupResetButton();
        //Initial Maze state
        PRINTF("Let's explore this maze!\r\n");
        showMaze(playerX, playerY);
        // Continuous reading loop
        while (1)
        {
            uint8_t status0_value = 0;
            // Wait for new data to be ready
            while (!(status0_value & 0x08))
            {
                I2C_ReadAccelRegs(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, ACCEL_STATUS, &status0_value, 1);
            }
            // Read multiple bytes from the STATUS register
            I2C_ReadAccelRegs(BOARD_ACCEL_I2C_BASEADDR, g_accel_addr_found, ACCEL_STATUS, readBuff, 7);

            //Our code
            // Calibrate accelerometer offsets
             CalibrateAccelerometer();
//            // Extract acceleration data
//            x = ((int16_t)(((readBuff[1] << MSBshift) | readBuff[2]))) >> LSBshift;
//            y = ((int16_t)(((readBuff[3] << MSBshift) | readBuff[4]))) >> LSBshift;
//            z = ((int16_t)(((readBuff[5] << MSBshift) | readBuff[6]))) >> LSBshift;

             // Calculate X and Y tilt values based on accelerometer data and offsets
            x = (((int16_t)(((readBuff[1] << MSBshift) | readBuff[2]))) >> LSBshift) - x_offset;
            y = (((int16_t)(((readBuff[3] << MSBshift) | readBuff[4]))) >> LSBshift) - y_offset;

            // Print the accelerometer values
            //PRINTF("x = %5d, y = %5d, z = %5d\r\n", x, y, z);

            // Delay to control the reading rate
            //SDK_DelayAtLeastUs(50000, CLOCK_GetFreq(kCLOCK_CoreSysClk)); // 50 ms delay
            //Our code
            // Move player based on tilt
            MovePlayer(x, y);
            // Delay to control the reading rate
            SDK_DelayAtLeastUs(70000, CLOCK_GetFreq(kCLOCK_CoreSysClk)); // 50 ms delay
        }
    }
    else
    {
        PRINTF("Accelerometer not found.\r\n");
    }

    while (1)
    {
    }
}

void setupResetButton(void)
{
    // Enable clock for PORTD (SW2)
    CLOCK_EnableClock(kCLOCK_PortD);

    gpio_pin_config_t button_config = {
        kGPIO_DigitalInput,
        0, // No pull-up or pull-down resistor
    };

    // Configure pin PTD11 (SW2)
    PORT_SetPinInterruptConfig(PORTD, 11U, kPORT_InterruptFallingEdge); // Falling edge for active LOW
    GPIO_PinInit(GPIOD, 11U, &button_config);

    // Enable IRQ for SW2 (monitor and respond to interrupt signals generated by events on PORTD)
    EnableIRQ(PORTD_IRQn);
}

void SW2_GPIOD_IRQHANDLER(void)
{
    PRINTF("\r\n --- Reset Button Pressed --- \r\n");
    // Clear interrupt flag for pin PTD11
    GPIO_PortClearInterruptFlags(GPIOD, 1U << 11U);

    // Reset the game state
    resetGame();
}

