
#pragma once

/************************************************************************/

U_BTN_CI :: 
U_BTN_CI ()
{
	_all_btn = 0x0;
}


void 
U_BTN_CI :: 
In ()
{
	_all_btn = __READ_BTN__;
}

/************************************************************************/

void 
F_Set_io_ci ()
{
	DDRA  = 0xff;
	PORTA = 0x00;
	DDRB  = 0x00;
	PORTB = 0xff;
	DDRC  = 0x00;
	PORTC = 0x00;
	DDRD  = 0x00;
	PORTD = 0xff;
}

void 
F_Set_wdt_ci ()
{
	cli();
	
	wdt_reset();
	
	WDTCSR |= ((1 << WDCE) | (1 << WDE));
	WDTCSR  = ((1 << WDE) | (1 << WDP2) | (1 << WDP0));	//wdt0.5[s]
	
	sei();
}

void 
F_Uart_in_bt_rx_ci
(
	C_UART_R &_arg_uart_r, 
	T_DATA_8 _arg_re_data_in[4]
)
{
	wdt_reset();
	
	unsigned char _flag_loup = 0x0f;
	
	while (_flag_loup)
	{
		const char _temp = _arg_uart_r.In(FALSE);
		
		if (_arg_uart_r != EU_ERROR)
		{
			_arg_re_data_in[(_temp >> 6) & 3] = _temp;
			
			_flag_loup &= ~(1 << ((_temp >> 6) & 3));
			
			wdt_reset();
		}
	}
}

void 
F_Uart_out_main_ci
(
	C_UART_T &_arg_uart_t, 
	const T_DATA_8 _arg_data_out[4]
)
{
	for (usint i = 0; i < 4; i++)
	{
		wdt_reset();
		
		_arg_uart_t.Out(_arg_data_out[i]);
		
		_delay_us(20);
	}
	
	wdt_reset();
}

