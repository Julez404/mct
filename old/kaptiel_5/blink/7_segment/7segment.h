#pragma once

#define seg_a_pin 0
#define seg_a_port _SFR_IO8(0x05)
#define seg_b_pin 1
#define seg_b_port _SFR_IO8(0x05)
#define seg_c_pin 2
#define seg_c_port _SFR_IO8(0x05)
#define seg_d_pin 3
#define seg_d_port _SFR_IO8(0x05)
#define seg_e_pin 4
#define seg_e_port _SFR_IO8(0x05)
#define seg_f_pin 5
#define seg_f_port _SFR_IO8(0x05)
#define seg_g_pin 7
#define seg_g_port _SFR_IO8(0x0B)
#define seg_dp_pin 6
#define seg_dp_port _SFR_IO8(0x0B)


void segment_clearAll(void);

void segment_printNumber(uint8_t _number);