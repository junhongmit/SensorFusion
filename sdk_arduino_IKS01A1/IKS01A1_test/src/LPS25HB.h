/*
 * LPS25HB.h
 *
 *  Created on: 2016Äê7ÔÂ26ÈÕ
 *      Author: xinyuc
 */

#ifndef SRC_LPS25HB_H_
#define SRC_LPS25HB_H_

#define LPS25HB_7bit_ADDR 0x5D
//#define LPS25HB_I2C_ADDR_R 0xBB
//#define LPS25HB_I2C_ADDR_W 0xBA
#define LPS25HB_WHO_AM_I 0x0F
#define LPS25HB_CTRL_REG1 0x20
#define LPS25HB_CTRL_REG2 0x21
#define LPS25HB_CTRL_REG3 0x22
#define LPS25HB_CTRL_REG4 0x23
#define LPS25HB_PRESS_OUT_XL 0x28
#define LPS25HB_PRESS_OUT_L 0x29
#define LPS25HB_PRESS_OUT_H 0x2A

void LPS25HB_ReadBaroRawData(s32 *PressValue);
u8 LPS25HB_init(void);


#endif /* SRC_LPS25HB_H_ */
