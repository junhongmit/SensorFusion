/*
 * LSM6DS0.c
 *
 *  Created on: 2016��11��1��
 *      Author: mengxian
 */

#include "LSM6DS0.h"

static u8 IS_LSM6DS0(void);
static u8 LSM6DS0_conf();
void LSM6DS0_read_gyroRaw(s16 *gXYZ){
	u8 rdata[2] = {0, 0};
	rdata[0] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_X_G_L, 1);
	rdata[1] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_X_G_H, 1);
	gXYZ[0] = ((s16)rdata[1] << 8) + ((s16)rdata[0]);
	rdata[0] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_Y_G_L, 1);
	rdata[1] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_Y_G_H, 1);
	gXYZ[1] = ((s16)rdata[1] << 8) + ((s16)rdata[0]);
	rdata[0] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_Z_G_L, 1);
	rdata[1] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_Z_G_H, 1);
	gXYZ[2] = ((s16)rdata[1] << 8) + ((s16)rdata[0]);
}
//void LSM6DS0_read_gyro(s32 *gyroData){
//	s16 gyroRaw[3];
//	float coeff = 2000/32767;
//	LSM6DS0_read_gyroRaw(gyroRaw);
//	gyroData[0] = (s32)(gyroRaw[0] * coeff);
//	gyroData[1] = (s32)(gyroRaw[1] * coeff);
//	gyroData[2] = (s32)(gyroRaw[2] * coeff);
//}
void LSM6DS0_read_accelRaw(s16 *acXYZ){
	u8 rdata[2] = {0, 0};
	rdata[0] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_X_XL_L, 1);
	rdata[1] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_X_XL_H, 1);
	acXYZ[0] = ((s16)rdata[1] << 8) + ((s16)rdata[0]);
	rdata[0] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_Y_XL_L, 1);
	rdata[1] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_Y_XL_H, 1);
	acXYZ[1] = ((s16)rdata[1] << 8) + ((s16)rdata[0]);
	rdata[0] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_Z_XL_L, 1);
	rdata[1] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_OUT_Z_XL_H, 1);
	acXYZ[2] = ((s16)rdata[1] << 8) + ((s16)rdata[0]);
}
//void LSM6DS0_read_accel(s32 *accelData){
//	s16 accelRaw[3];
//	float coeff = 16*10/32767; //XL_FS_2G:0.061f; XL_FS_4G:0.122f; XL_FS_8G:0.244f; XL_FS_16G:0.732f.
//	LSM6DS0_read_accelRaw(accelRaw);
//	accelData[0] = (s32)(accelRaw[0] * coeff);
//	accelData[1] = (s32)(accelRaw[1] * coeff);
//	accelData[2] = (s32)(accelRaw[2] * coeff);
//}
static u8 IS_LSM6DS0(void){
	 if((i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_WHO_AM_I, 1)) != 0x68){
		 return XST_FAILURE;
	 }
	 return XST_SUCCESS;
}
static u8 LSM6DS0_conf(){
	u8 tmpData[2];
	i2c_write_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_CTRL_REG1_G, 0xBB);
	tmpData[0] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_CTRL_REG1_G, 1);
	i2c_write_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_CTRL_REG6_XL, 0xC8);
	tmpData[1] = i2c_read_IKS01A1(LSM6DS0_7bit_ADDR, LSM6DS0_CTRL_REG6_XL, 1);
	if(tmpData[0] != 0xBB || tmpData[1] != 0xC8){
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}

u8 LSM6DS0_init(){
	if(IS_LSM6DS0() != XST_SUCCESS){
		return XST_FAILURE;
	}
	if(LSM6DS0_conf() != XST_SUCCESS){
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}
