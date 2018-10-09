
#include "myiic.h"
#include "LPS25HB.h"

static u8 IS_LPS25HB(void);
static void LPS25HB_conf(void);

void LPS25HB_ReadBaroRawData(s32 *PressValue){
	u8 rdata[3];
	rdata[0] = iic_read_IKS01A1(LPS25HB_7bit_ADDR, LPS25HB_PRESS_OUT_XL, 1);
	rdata[1] = iic_read_IKS01A1(LPS25HB_7bit_ADDR, LPS25HB_PRESS_OUT_L, 1);
	rdata[2] = iic_read_IKS01A1(LPS25HB_7bit_ADDR, LPS25HB_PRESS_OUT_H, 1);
	*PressValue = ((( (s32) rdata[2] << 8) | (s32) rdata[1]) << 8)  | (s32) rdata[0];
}
static u8 IS_LPS25HB(void){
	 if((iic_read_IKS01A1(LPS25HB_7bit_ADDR, LPS25HB_WHO_AM_I, 1)) != 0xBD){
		 return XST_FAILURE;
	 }
	 return XST_SUCCESS;
}
static void LPS25HB_conf(void){
	iic_write_IKS01A1(LPS25HB_7bit_ADDR, LPS25HB_CTRL_REG1, 0xa0);
}
u8 LPS25HB_init(void){
	if(IS_LPS25HB() != XST_SUCCESS){
		return XST_FAILURE;
	}
	LPS25HB_conf();
	return XST_SUCCESS;
}


