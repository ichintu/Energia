/*
 * defines.h
 *
 *  Created on: Oct 13, 2013
 *      Author: RobG
 */

#ifndef DEFINES_H_
#define DEFINES_H_

#include "msp430.h"
//
//#define RESPONSE_TYPE_HTML
//
#define TX_MAX_BUF_SIZE	0x7F // we can go up to 256, but we would have to decrease RX down to 64, 256/64 (G2553 chip)
#define RX_MAX_BUF_SIZE	0x7F //
//
#define WIZ_SCLK_PIN			BIT5
#define WIZ_SCLK_PORT			P1OUT
#define WIZ_MISO_PIN			BIT6
#define WIZ_MISO_PORT			P1OUT
#define WIZ_MOSI_PIN			BIT7
#define WIZ_MOSI_PORT			P1OUT
#define WIZ_CS_PIN				BIT3
#define WIZ_CS_PORT				P2OUT
#define WIZ_INT_PIN				BIT4
#define WIZ_INT_PORT			P2IE
#define WIZ_RST_PIN				BIT5
#define WIZ_RST_PORT			P2OUT

#define WIZ_RESET_0				WIZ_RST_PORT &= ~WIZ_RST_PIN
#define WIZ_RESET_1				WIZ_RST_PORT |= WIZ_RST_PIN
#define WIZ_SELECT				WIZ_CS_PORT &= ~WIZ_CS_PIN
#define WIZ_DESELECT			WIZ_CS_PORT |= WIZ_CS_PIN
#define WIZ_IE_ENABLE			WIZ_INT_PORT |= WIZ_INT_PIN
#define WIZ_IE_DISABLE			WIZ_INT_PORT &= ~WIZ_INT_PIN
//
#define wizPowerUp()			WIZ_POWER_UP
#define wizPowerDown()			WIZ_POWER_DOWN
#define wizSelect()				WIZ_SELECT
#define wizDeselect()			WIZ_DESELECT
#define wizEnableInterrupt()	WIZ_IE_ENABLE
#define wizDisableInterrupt()	WIZ_IE_DISABLE
//
#define SOCK_CONFIG				2	// UDP
#define SOCK_DNS				2	// UDP
#define SOCK_DHCP				3	// UDP
#define MAX_BUF_SIZE			1460
#define KEEP_ALIVE_TIME			30	// 30 sec
#define	MAX_SOCK_NUM			8
//
#define WINDOWFULL_FLAG_ON 		1
#define WINDOWFULL_FLAG_OFF 	0
#define WINDOWFULL_MAX_RETRY_NUM 3
#define WINDOWFULL_WAIT_TIME 	1000
//
#define REQ_ACTION				0x01
#define REQ_UNIVERSE			0x02
#define REQ_CHANNEL				0x03
#define REQ_VALUE				0x04
#define REQ_IGNORE				0x05
#define PARAM_NAME				0x06
#define PARAM_VALUE				0x07
//

#endif /* DEFINES_H_ */
