/* Use ecample code from IDE For only accelerometer reading setup
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017,2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
//Example code
#ifndef I2C_READ_ACCEL_VALUE_TRANSFER_H
#define I2C_READ_ACCEL_VALUE_TRANSFER_H

#include "fsl_i2c.h"

// I2C configuration
#define ACCEL_I2C_CLK_SRC I2C0_CLK_SRC
#define ACCEL_I2C_CLK_FREQ CLOCK_GetFreq(I2C0_CLK_SRC)
#define I2C_BAUDRATE 100000
#define BOARD_ACCEL_I2C_BASEADDR I2C0

// Accelerometer configuration
#define FXOS8700_WHOAMI 0xC7U
#define MMA8451_WHOAMI 0x1AU
#define MMA8652_WHOAMI 0x4AU
#define ACCEL_XYZ_DATA_CFG 0x0EU
#define ACCEL_CTRL_REG1 0x2AU
#define ACCEL_WHOAMI_REG 0x0DU
#define ACCEL_STATUS 0x00U
#define ACCEL_READ_TIMES 10U


// I2C Pins
#define I2C_RELEASE_SDA_PORT PORTD
#define I2C_RELEASE_SCL_PORT PORTD
#define I2C_RELEASE_SDA_GPIO GPIOD
#define I2C_RELEASE_SDA_PIN 9U
#define I2C_RELEASE_SCL_GPIO GPIOD
#define I2C_RELEASE_SCL_PIN 8U
#define I2C_RELEASE_BUS_COUNT 100U

// Extern variables
extern volatile bool completionFlag;
extern volatile bool nakFlag;
extern uint8_t g_accel_addr_found;
extern i2c_master_handle_t g_m_handle;
extern int16_t x_offset, y_offset;
extern const uint8_t g_accel_address[];

extern uint8_t MSBshift; // Shift for most significant bits
extern uint8_t LSBshift; // Shift for least significant bits

extern int16_t x_offset, y_offset, z_offset;



// Function prototypes
/**
 * @brief Releases the I2C bus by toggling the SCL and SDA lines manually.
 *        This function is useful when the I2C bus is locked or stuck.
 */
void BOARD_I2C_ReleaseBus(void);
/**
 * @brief Introduces a delay during I2C bus release operation to ensure proper timing.
 */
void i2c_release_bus_delay(void);
/**
 * @brief Initializes the I2C module with the specified configuration.
 *        Sets up the baud rate, clock source, and enables the I2C peripheral.
 */
void I2C_InitModule(void);
/**
 * @brief Reads the WHO_AM_I register of the accelerometer to verify the device's identity.
 * @return True if a known accelerometer is detected, false otherwise.
 */
bool I2C_ReadAccelWhoAmI(void);
/**
 * @brief Reads data from the specified register of the accelerometer over I2C.
 * @param base The base address of the I2C peripheral.
 * @param device_addr The I2C address of the accelerometer.
 * @param reg_addr The register address to read from.
 * @param rxBuff Pointer to the buffer where the data will be stored.
 * @param rxSize The number of bytes to read.
 * @return True if the operation is successful, false otherwise.
 */
bool I2C_ReadAccelRegs(I2C_Type *base, uint8_t device_addr, uint8_t reg_addr, uint8_t *rxBuff, uint32_t rxSize);
/**
 * @brief Writes data to the specified register of the accelerometer over I2C.
 * @param base The base address of the I2C peripheral.
 * @param device_addr The I2C address of the accelerometer.
 * @param reg_addr The register address to write to.
 * @param value The value to write to the register.
 * @return True if the operation is successful, false otherwise.
 */
bool I2C_WriteAccelReg(I2C_Type *base, uint8_t device_addr, uint8_t reg_addr, uint8_t value);
/**
 * @brief Callback function for I2C master transfer events.
 *        This function is called by the I2C driver upon completion or error during a transfer.
 * @param base The base address of the I2C peripheral.
 * @param handle Pointer to the I2C master handle.
 * @param status The status of the transfer.
 * @param userData Pointer to user-defined data (not used here).
 */
void i2c_master_callback(I2C_Type *base, i2c_master_handle_t *handle, status_t status, void *userData);
//Our code
/**
 * @brief Calibrates the accelerometer by reading multiple samples and calculating the offsets.
 *        Offsets are subtracted from raw data to normalize the accelerometer output.
 */
void CalibrateAccelerometer(void);

#endif // I2C_READ_ACCEL_VALUE_TRANSFER_H
