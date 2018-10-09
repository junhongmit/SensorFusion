
#include "myiic.h"
#include "HTS221.h"

static u8 IS_HTS221(void);
static u8 HTS221_conf(void);

void HTS221_read_TemperaData(s16 *TEMP){
	u8 rdata[2];
	rdata[0] = i2c_read_IKS01A1(HTS221_7bit_ADDR, HTS221_Temp_OUT_L, 1);
	rdata[1] = i2c_read_IKS01A1(HTS221_7bit_ADDR, HTS221_Temp_OUT_H, 1);
	*TEMP = ((s16) rdata[1] << 8) | (s16) rdata[0];
}
void HTS221_read_HumidData(s16 *Humid){
	u8 rdata[2];
	rdata[0] = i2c_read_IKS01A1(HTS221_7bit_ADDR, HTS221_Humidity_OUT_L, 1);
	rdata[1] = i2c_read_IKS01A1(HTS221_7bit_ADDR, HTS221_Humidity_OUT_H, 1);
	*Humid = ((s16) rdata[1] << 8) | (s16) rdata[0];
}
static u8 IS_HTS221(void){
	if((i2c_read_IKS01A1(HTS221_7bit_ADDR, HTS221_WHO_AM_I, 1)) != 0xBC){
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}
static u8 HTS221_conf(void){
	u8 tmpData[2];
	i2c_write_IKS01A1(HTS221_7bit_ADDR, HTS221_CTRL_REG1, 0x82);
	tmpData[0] = i2c_read_IKS01A1(HTS221_7bit_ADDR, HTS221_CTRL_REG1, 1);
	i2c_write_IKS01A1(HTS221_7bit_ADDR, HTS221_CTRL_REG3, 0x04);
	tmpData[1] = i2c_read_IKS01A1(HTS221_7bit_ADDR, HTS221_CTRL_REG3, 1);
	if(tmpData[0] != 0x82 || tmpData[1] != 0x04){
		return XST_FAILURE;
	}
	return XST_SUCCESS;

}

u8 HTS221_init(){
	if(IS_HTS221() != XST_SUCCESS){
		return XST_FAILURE;
	}
	if(HTS221_conf() != XST_SUCCESS){
		return XST_FAILURE;
	}
	return XST_SUCCESS;
}
