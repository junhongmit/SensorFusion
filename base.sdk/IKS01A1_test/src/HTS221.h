
#ifndef SRC_HTS221_H_
#define SRC_HTS221_H_

#include "xil_types.h"
#include "xstatus.h"

#define HTS221_7bit_ADDR 0x5F
//#define HTS221_I2C_ADDR_R 0xBF
//#define HTS221_I2C_ADDR_W 0xBE
#define HTS221_WHO_AM_I 0x0F
#define HTS221_CTRL_REG1 0x20
#define HTS221_CTRL_REG2 0x21
#define HTS221_CTRL_REG3 0x22

#define HTS221_CTRL_StatusReg 0x27
#define HTS221_Humidity_OUT_L 0x28
#define HTS221_Humidity_OUT_H 0x29
#define HTS221_Temp_OUT_L 0x2A
#define HTS221_Temp_OUT_H 0x2B
#define HTS221_T0_degC_x8 0x32
#define HTS221_T1_degC_x8 0x33
#define HTS221_T0T1_H 0x35
#define HTS221_H0_rH_x2 0x30
#define HTS221_H1_rH_x2 0x31

void HTS221_read_TemperaData(s16 *TEMP);
void HTS221_read_HumidData(s16 *Humid);
u8 HTS221_init();

#endif /* SRC_HTS221_H_ */
