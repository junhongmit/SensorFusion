/*
 * LIS3MDL.h
 *
 *  Created on: 2016��7��26��
 *      Author: xinyuc
 */

#ifndef SRC_LIS3MDL_H_
#define SRC_LIS3MDL_H_

#include "xil_types.h"
#include "xstatus.h"

#define LIS3MDL_7bit_ADDR 0x1E
//#define LIS3MDL_I2C_ADDR_V 0x1E /* SA1 -> VDD */
//#define LIS3MDL_I2C_ADDR_G 0x1C /* SA1 -> GND */
#define LIS3MDL_I2C_ADDR_R 0x3D
#define LIS3MDL_I2C_ADDR_W 0x3C
#define LIS3MDL_WHO_AM_I 0x0F
#define LIS3MDL_CTRL_REG1 0x20
#define LIS3MDL_CTRL_REG2 0x21
#define LIS3MDL_CTRL_REG3 0x22
#define LIS3MDL_CTRL_REG4 0x23
#define LIS3MDL_CTRL_REG5 0x24
#define LIS3MDL_CTRL_StatusReg 0x27
#define LIS3MDL_OUT_X_L 0x28
#define LIS3MDL_OUT_X_H 0x29
#define LIS3MDL_OUT_Y_L 0x2A
#define LIS3MDL_OUT_Y_H 0x2B
#define LIS3MDL_OUT_Z_L 0x2C
#define LIS3MDL_OUT_Z_H 0x2D
#define LIS3MDL_TEMP_OUT_L 0x2E
#define LIS3MDL_TEMP_OUT_H 0x2F



void LIS3MDL_Read_MagRawData(s16 *magXYZ);
u8 LIS3MDL_init(void);

#endif /* SRC_LIS3MDL_H_ */
