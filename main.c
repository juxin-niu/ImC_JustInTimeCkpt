#include <ImC/nv.h>
#include <ImC/target_spec.h>
#include <ImC/target.h>
#include <ImC/volt_monit.h>
#include <ImC/analysis/hamming8.h>
#include <ImC/analysis/uart2target.h>

#include <app/app.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

/* ========================================== GLOBAL MACRO ========================================== */
#define TESTBENCH_NEVEREND 1 /* Loop execution or sequential execution */
#define VOLT_MONIT_INTERVAL_IN_US 55000 /* Voltage measurement interval */
/* ========================================== GLOBAL MACRO ========================================== */

__nv uint8_t first_run = 1;
__nv uint8_t hamming_scode[8];
__nv uint8_t hamming_ecode[8];
const TASKMAIN testbench[] = {AR_main, BC_main, CEM_main, CRC_main, CUCKOO_main, DIJKSTRA_main, RSA_main, SORT_main};

void jit_scheduler();


int main()
{
    power_on_init();
    clock_sys_init();
    dma_init();
    uart2target_init();
    ref_volt_init();
    adc_timer_init();
    adc_init();

    if (first_run == 1) {
        for (uint16_t i = 0; i < 8; ++i) {
            hamming_scode[i] = hamming_enc(2 * i);
            hamming_ecode[i] = hamming_enc(2 * i + 1);
        }
        /* The SR register is restored when the program resumes
         * from the saved state (ie, leaves the ISR), so there is
         * no need to repeatedly set the GIE bit.
         */
        __bis_SR_register(GIE);
        first_run = 0;
    }

    __bis_SR_register(GIE); // TODO: DEBUG ONLY

    TA0CCR0 = VOLT_MONIT_INTERVAL_IN_US * WORKING_FREQUENCY_IN_MHZ;     // Initialize CCR0
    HWREG16(TIMER_A0_BASE + OFS_TAxCTL) &= ~MC_3;                       // Start timer
    HWREG16(TIMER_A0_BASE + OFS_TAxCTL) |= TIMER_A_CONTINUOUS_MODE;     //


#if TESTBENCH_NEVEREND
    while (1) {
#endif
        for (uint16_t i = 0; i < 8; ++i) {
            EUSCI_A_UART_transmitData(UART_BASEADDR, hamming_scode[i]);
            (* testbench[i])();  // run testbench
            EUSCI_A_UART_transmitData(UART_BASEADDR, hamming_ecode[i]);
        }
#if TESTBENCH_NEVEREND
    }
#endif

}



#pragma vector = TIMER0_A0_VECTOR
__interrupt void ADC_TIMER_ISR(void)
{
    volatile uint16_t rlt;

    ADC12_B_startConversion(ADC12_B_BASE, ADC12_B_MEMORY_0, ADC12_B_SINGLECHANNEL);
    while (! (HWREG16(ADC12_B_BASE + OFS_ADC12IFGR0) & ADC12_B_IFG0) ) {/* Wait for ADC */}
    rlt = HWREG16(ADC12_B_BASE + OFS_ADC12MEM0);

    // TODO: backup or something.
    P1OUT |= BIT1;
    __delay_cycles(100);
    P1OUT &= ~BIT1;

    TA0CCR0 += VOLT_MONIT_INTERVAL_IN_US * WORKING_FREQUENCY_IN_MHZ;
}

