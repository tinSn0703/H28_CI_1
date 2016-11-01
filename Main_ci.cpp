/*
 * H28_CI_1.cpp
 *
 * Created: 2016/11/01 9:07:24
 * Author : sn
 */ 

#include "Func_ci.h"

int main(void)
{
    F_Set_io_ci();
	
	C_UART_R _uart_r_bt_rx0(EU_UART0);
	C_UART_R _uart_r_bt_rx1(EU_UART1);
	
	C_UART_T _uart_t_main(EU_UART0);
	
	U_BTN_CI _btn_dip;
	
	const T_DATA_8 _temp_data[4] = {0x3f, 0x7f, 0x8f, 0xc0};
	
	F_Set_wdt_ci();
	
	INI_LCD();
	
    while (1) 
    {
		__LOW_LED(0xff);
		
		T_DATA_8 _data_in_bt_rx0[4] = {};
		T_DATA_8 _data_in_bt_rx1[4] = {};
		
		const BOOL _nf_link0 = __READ_LINK0__;
		const BOOL _nf_link1 = __READ_LINK1__;
		
		_btn_dip.In();
		
		if (_nf_link0)	__HIGH_LED4__;
		if (_nf_link1)	__HIGH_LED6__;
		
		if (_btn_dip.Ret_btn_0() & ~_btn_dip.Ret_btn_1())
		{
			if (_nf_link0)
			{
				F_Uart_in_bt_rx_ci(_uart_r_bt_rx0, _data_in_bt_rx0);
				F_Uart_out_main_ci(_uart_t_main, _data_in_bt_rx0);
				
				__HIGH_LED5__;
				
				if (_nf_link1)	F_Uart_in_bt_rx_ci(_uart_r_bt_rx1, _data_in_bt_rx1);
			}
			else if (_nf_link1)
			{
				F_Uart_in_bt_rx_ci(_uart_r_bt_rx1, _data_in_bt_rx1);
				F_Uart_out_main_ci(_uart_t_main, _data_in_bt_rx1);
				
				__HIGH_LED7__;
			}
			else
			{
				F_Uart_out_main_ci(_uart_t_main, _temp_data);
			}
		}
		else if (_btn_dip.Ret_btn_1() & ~_btn_dip.Ret_btn_0())
		{
			if (_nf_link1)
			{
				F_Uart_in_bt_rx_ci(_uart_r_bt_rx1, _data_in_bt_rx1);
				F_Uart_out_main_ci(_uart_t_main, _data_in_bt_rx1);
				
				__HIGH_LED7__;
				
				if (_nf_link1)	F_Uart_in_bt_rx_ci(_uart_r_bt_rx0, _data_in_bt_rx0);
			}
			else if (_nf_link0)
			{
				F_Uart_in_bt_rx_ci(_uart_r_bt_rx0, _data_in_bt_rx0);
				F_Uart_out_main_ci(_uart_t_main, _data_in_bt_rx0);
				
				__HIGH_LED5__;
			}
			else
			{
				F_Uart_out_main_ci(_uart_t_main, _temp_data);
			}
		}
		else
		{
			if (_nf_link0)
			{
				F_Uart_in_bt_rx_ci(_uart_r_bt_rx0, _data_in_bt_rx0);
				F_Uart_out_main_ci(_uart_t_main, _data_in_bt_rx0);
				
				__HIGH_LED5__;
				
				if (_nf_link1)	F_Uart_in_bt_rx_ci(_uart_r_bt_rx1, _data_in_bt_rx1);
			}
			else if (_nf_link1)
			{
				F_Uart_in_bt_rx_ci(_uart_r_bt_rx1, _data_in_bt_rx1);
				F_Uart_out_main_ci(_uart_t_main, _data_in_bt_rx1);
				
				__HIGH_LED7__;
			}
			else
			{
				F_Uart_out_main_ci(_uart_t_main, _temp_data);
			}
		}
		
		if (_btn_dip.Ret_btn_2() & _btn_dip.Ret_btn_3())
		{
			if (_nf_link0)	Lcd_put_str(0x00, "BT_0 Connect    ");
			else			Lcd_put_str(0x00, "BT_0 Disconnect ");
			
			if (_nf_link1)	Lcd_put_str(0x40, "BT_1 Connect    ");
			else			Lcd_put_str(0x40, "BT_1 Disconnect ");
			
			__HIGH_LED2__;	__HIGH_LED3__;
		}
		else if (_btn_dip.Ret_btn_2() & ~_btn_dip.Ret_btn_3())
		{
			if (_nf_link1)	Lcd_put_str(0x00, "BT_1 Connect    ");
			else			Lcd_put_str(0x00, "BT_1 Disconnect ");
			
			Lcd_put_str(0x40, "DATA xx xx xx xx");
			
			for (usint i = 0; i < 4; i ++)
			{
				Lcd_put_num(0x45 + i * 3, _data_in_bt_rx1[i], 2, ED_16);
			}
			
			__HIGH_LED2__;
		}
		else if (~_btn_dip.Ret_btn_2() & _btn_dip.Ret_btn_3())
		{
			if (_nf_link0)	Lcd_put_str(0x00, "BT_0 Connect    ");
			else			Lcd_put_str(0x00, "BT_0 Disconnect ");
			
			Lcd_put_str(0x40, "DATA xx xx xx xx");
			
			for (usint i = 0; i < 4; i ++)
			{
				Lcd_put_num(0x45 + i * 3, _data_in_bt_rx0[i], 2, ED_16);
			}
			
			__HIGH_LED3__;
		}
		else
		{
			Lcd_put_str(0x00, "BT_0 xx xx xx xx");
			Lcd_put_str(0x40, "BT_1 xx xx xx xx");
			
			for (usint i = 0; i < 4; i ++)
			{
				Lcd_put_num(0x05 + i * 3, _data_in_bt_rx0[i], 2, ED_16);
				Lcd_put_num(0x45 + i * 3, _data_in_bt_rx1[i], 2, ED_16);
			}
		}
		
		if ((_nf_link0 | _nf_link1) == FALSE)	_delay_ms(100);
	}
	
	return 0;
}

