/*
 * LSM6DS0.h
 *
 *  Created on: 2016��11��1��
 *      Author: mengxian
 */

#ifndef SRC_LSM6DS0_H_
#define SRC_LSM6DS0_H_

#include "xil_types.h"
#include "xstatus.h"
#include "myiic.h"


#define LSM6DS0_7bit_ADDR 0x6B
#define LSM6DS0_WHO_AM_I 0x0F
#define LSM6DS0_CTRL_REG1_G 0x10
#define LSM6DS0_CTRL_REG2_G 0x11
#define LSM6DS0_CTRL_REG3_G 0x12
#define LSM6DS0_CTRL_REG4 0x1E
#define LSM6DS0_CTRL_REG5_XL 0x1F
#define LSM6DS0_CTRL_REG6_XL 0x20
#define LSM6DS0_CTRL_REG7_XL 0x21
#define LSM6DS0_CTRL_REG8 0x22
#define LSM6DS0_CTRL_REG9 0x23
#define LSM6DS0_CTRL_REG10 0x24
#define LSM6DS0_CTRL_StatusReg 0x17
#define LSM6DS0_OUT_X_G_L 0x18
#define LSM6DS0_OUT_X_G_H 0x19
#define LSM6DS0_OUT_Y_G_L 0x1A
#define LSM6DS0_OUT_Y_G_H 0x1B
#define LSM6DS0_OUT_Z_G_L 0x1C
#define LSM6DS0_OUT_Z_G_H 0x1D
#define LSM6DS0_OUT_X_XL_L 0x28
#define LSM6DS0_OUT_X_XL_H 0x29
#define LSM6DS0_OUT_Y_XL_L 0x2A
#define LSM6DS0_OUT_Y_XL_H 0x2B
#define LSM6DS0_OUT_Z_XL_L 0x2C
#define LSM6DS0_OUT_Z_XL_H 0x2D

void LSM6DS0_read_gyroRaw(s16 *gXYZ);
void LSM6DS0_read_gyro(s32 *gyroData);
void LSM6DS0_read_accelRaw(s16 *acXYZ);
void LSM6DS0_read_accel(s32 *accelData);


u8 LSM6DS0_init();
float get_LSM6DS0_gyroRaw_XYZ(u8 xyzSW);
#endif /* SRC_LSM6DS0_H_ */
