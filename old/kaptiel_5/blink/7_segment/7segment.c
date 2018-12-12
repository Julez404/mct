#include <avr/io.h>
#include "7segment.h"

void segment_printNumber(uint8_t _number)
{
	segment_clearAll();
	switch(_number)
	{
		case 0:
		seg_a_port |= (1 << seg_a_pin);
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_f_port |= (1 << seg_f_pin);
		break;

		case 1:
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		break;

		case 2:
		seg_a_port |= (1 << seg_a_pin);
		seg_b_port |= (1 << seg_b_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 3:
		seg_a_port |= (1 << seg_a_pin);
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;
		case 4:
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 5:
		seg_a_port |= (1 << seg_a_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 6:
		seg_a_port |= (1 << seg_a_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 7:
		seg_a_port |= (1 << seg_a_pin);
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		break;

		case 8:
		seg_a_port |= (1 << seg_a_pin);
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;
		
		case 9:
		seg_a_port |= (1 << seg_a_pin);
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 10:
		seg_a_port |= (1 << seg_a_pin);
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 11:
		seg_c_port |= (1 << seg_c_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 12:
		seg_a_port |= (1 << seg_a_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_f_port |= (1 << seg_f_pin);
		break;

		case 13:
		seg_b_port |= (1 << seg_b_pin);
		seg_c_port |= (1 << seg_c_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 14:
		seg_a_port |= (1 << seg_a_pin);
		seg_d_port |= (1 << seg_d_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;

		case 15:
		seg_a_port |= (1 << seg_a_pin);
		seg_e_port |= (1 << seg_e_pin);
		seg_f_port |= (1 << seg_f_pin);
		seg_g_port |= (1 << seg_g_pin);
		break;
	}
}

void segment_clearAll(void)
{
	seg_a_port &= ~(1 << seg_a_pin);
	seg_b_port &= ~(1 << seg_b_pin);
	seg_c_port &= ~(1 << seg_c_pin);
	seg_d_port &= ~(1 << seg_d_pin);
	seg_e_port &= ~(1 << seg_e_pin);
	seg_f_port &= ~(1 << seg_f_pin);
	seg_g_port &= ~(1 << seg_g_pin);
	seg_dp_port &= ~(1 << seg_dp_pin);
}