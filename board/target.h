
#ifndef BOARD_TARGET_H_
#define BOARD_TARGET_H_

#define WORKING_FREQUENCY_IN_MHZ    1
//!                                -1 (in 1MHz)
//!                                -2 (in 2MHz)
//!                                -4 (in 4MHz)
//!                                -8 (in 8MHz)

void power_on_init();
void clock_sys_init();
void dma_init();

#endif /* BOARD_TARGET_H_ */
