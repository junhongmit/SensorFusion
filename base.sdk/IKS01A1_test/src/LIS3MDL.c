/*

 */
#include "myiic.h"
#include "LIS3MDL.h"

static u8 IS_LIS3MDL(void);
static void LIS3MDL_config(void);

void LIS3MDL_Read_MagRawData(s16 *magXYZ){
	u8 rdata[2];
	rdata[0] = i2c_read_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_OUT_X_L, 1);
	rdata[1] = i2c_read_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_OUT_X_H, 1);
	magXYZ[0] =  ((s16) rdata[1] << 8) | ((s16) rdata[0]);
	rdata[0] = i2c_read_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_OUT_Y_L, 1);
	rdata[1] = i2c_read_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_OUT_Y_H, 1);
	magXYZ[1] =  ((s16) rdata[1] << 8) | ((s16) rdata[0]);
	rdata[0] = i2c_read_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_OUT_Z_L, 1);
	rdata[1] = i2c_read_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_OUT_Z_H, 1);
	magXYZ[2] = ((s16) rdata[1] << 8) | ((s16) rdata[0]);
}
static u8 IS_LIS3MDL(void){
	u8 rdata;
	rdata = i2c_read_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_WHO_AM_I, 1);
	if (rdata != 0x3D){
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}
static void LIS3MDL_config(void){
//	iic_write_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_CTRL_REG2, 0x04 );
	i2c_write_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_CTRL_REG1, 0x20 | 0x0C );
	i2c_write_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_CTRL_REG2, 0x60 );/* +- 16 gauss */
	i2c_write_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_CTRL_REG3, 0x20 ); /* Continuous-conversion mode */
	i2c_write_IKS01A1(LIS3MDL_7bit_ADDR, LIS3MDL_CTRL_REG4, 0x04 );/* Z axis ultra-high performance mode*/
}

u8 LIS3MDL_init(void){
	if(IS_LIS3MDL() != XST_SUCCESS){
		return XST_FAILURE;
	}
	LIS3MDL_config();
	return XST_SUCCESS;
}
