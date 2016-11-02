
#pragma once

/************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <H28_AVR/H28_AVR.h>
#include <FallMoon/akilcd_ci.h>

/************************************************************************/

#define __NUM_DATA__ 4

#define __LED0__ PA0 //DIP_SW 0 ON/OFF
#define __LED1__ PA1 //DIP_SW 1 ON/OFF
#define __LED2__ PA2 //DIP_SW 2 ON/OFF
#define __LED3__ PA3 //DIP_SW 3 ON/OFF
#define __LED4__ PA4 //BT_RX 0 LINK HIGH/LOW
#define __LED5__ PA5 //BT_RX 0 -> MAIN
#define __LED6__ PA6 //BT_RX 1 LINK HIGH/LOW
#define __LED7__ PA7 //BT_RX 1 -> MAIN

#define __PORT_LED__ PORTA

#define __LINK0__ PD4
#define __LINK1__ PD5

#define __PIN_LINK__ PIND

#define __PIN_BTN__ PINB

#define __BIT_LED0__ (1 << __LED0__)
#define __BIT_LED1__ (1 << __LED1__)
#define __BIT_LED2__ (1 << __LED2__)
#define __BIT_LED3__ (1 << __LED3__)
#define __BIT_LED4__ (1 << __LED4__)
#define __BIT_LED5__ (1 << __LED5__)
#define __BIT_LED6__ (1 << __LED6__)
#define __BIT_LED7__ (1 << __LED7__)

#define __WRITE_LED(_def_write_led)	(__PORT_LED__ = _def_write_led)

#define __HIGH_LED(_def_high_led)	(__PORT_LED__ |= _def_high_led)

#define __HIGH_LED0__ (__PORT_LED__ |= __BIT_LED0__)
#define __HIGH_LED1__ (__PORT_LED__ |= __BIT_LED1__)
#define __HIGH_LED2__ (__PORT_LED__ |= __BIT_LED2__)
#define __HIGH_LED3__ (__PORT_LED__ |= __BIT_LED3__)
#define __HIGH_LED4__ (__PORT_LED__ |= __BIT_LED4__)
#define __HIGH_LED5__ (__PORT_LED__ |= __BIT_LED5__)
#define __HIGH_LED6__ (__PORT_LED__ |= __BIT_LED6__)
#define __HIGH_LED7__ (__PORT_LED__ |= __BIT_LED7__)

#define __LOW_LED(_def_low_led)	(__PORT_LED__ &= ~_def_low_led)

#define __LOW_LED0__ (__PORT_LED__ &= ~__BIT_LED0__)
#define __LOW_LED1__ (__PORT_LED__ &= ~__BIT_LED1__)
#define __LOW_LED2__ (__PORT_LED__ &= ~__BIT_LED2__)
#define __LOW_LED3__ (__PORT_LED__ &= ~__BIT_LED3__)
#define __LOW_LED4__ (__PORT_LED__ &= ~__BIT_LED4__)
#define __LOW_LED5__ (__PORT_LED__ &= ~__BIT_LED5__)
#define __LOW_LED6__ (__PORT_LED__ &= ~__BIT_LED6__)
#define __LOW_LED7__ (__PORT_LED__ &= ~__BIT_LED7__)

#define __READ_BTN__ ((__PIN_BTN__ >> 1) & 0x0f)

#define __READ_LINK0__ ((BOOL)((__PIN_LINK__ >> __LINK0__) & 1))
#define __READ_LINK1__ ((BOOL)((__PIN_LINK__ >> __LINK1__) & 1))

/************************************************************************/

/*
	DIPスイッチを読み取るための共用体
*/
union U_BTN_CI
{
	
private:
	
	struct S_BTN_CI	
	{
		/*
		_btn_0 , _btn_1 -> メインに優先して送信するデータの選択
			_btn_0 == TRUE	-> 0番を送信
			_btn_1 == TRUE	-> 1番を送信
			その他			-> 0番を送信
			
		_btn_2 , _btn_3 -> LCDの表示の選択
			  2  |  3  |
			------------------------------- 
			  T  |  T  | 0 , 1のリンク
			  T  |  F  | 1のリンク、データ
			  F  |  T  | 0のリンク、データ
			  F  |  F  | 0 ，1のデータ
		*/
		
		BOOL _btn_0 :1;
		BOOL _btn_1 :1;
		BOOL _btn_2 :1;
		BOOL _btn_3 :1;
	};
	
	S_BTN_CI _divi_btn	  ;
	T_DATA_8 _all_btn	:4;
	
public:
	
	U_BTN_CI ();
	
	void In();
	
	T_DATA_8 Ret_btn_all()	{	return _all_btn;	}
	
	BOOL Ret_btn_0()	{	return _divi_btn._btn_0;	}
	BOOL Ret_btn_1()	{	return _divi_btn._btn_1;	}
	BOOL Ret_btn_2()	{	return _divi_btn._btn_2;	}
	BOOL Ret_btn_3()	{	return _divi_btn._btn_3;	}
};

/************************************************************************/

/**
 * \brief 
 *	IOレジスタの設定を行う
 */
void F_Set_io_ci();

/**
 * \brief 
 *	ウォッチドックタイマの設定を行う
 */
void F_Set_wdt_ci();

/**
 * \brief 
 *	BT_RXからの受信を行う 
 *
 * \param _arg_uart_r		: 受信するUART
 * \param _arg_re_data_in	: 受信したデータが格納される場所
 */
void F_Uart_in_bt_rx_ci(C_UART_R &_arg_uart_r, char _arg_re_data_in[__NUM_DATA__]);

/**
 * \brief 
 *	 メイン回路への送信を行う
 *
 * \param _arg_uart_t	: 送信するUART
 * \param _arg_data_out	: 送信するデータ
 */
void F_Uart_out_main_ci(C_UART_T &_arg_uart_t, const char _arg_data_out[__NUM_DATA__]);

/************************************************************************/

#include "Func_ci.cpp"
