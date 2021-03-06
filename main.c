#include <app/app_api.h>

#include <board/driverlib_include.h>
#include <board/led_button.h>
#include <board/nv.h>
#include <board/target.h>
#include <board/uart2target.h>
#include <board/volt_monit.h>

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

__nv uint8_t snapshot_taking_error_flag = false;
__nv uint8_t data_consistency_error_flag = false;
__nv uint8_t task_success_flag = false;

__nv uint8_t recovery_needed = 0;
__nv uint8_t system_in_lpm = 0;

typedef void (*TBFUNCPTR)();
__nv TBFUNCPTR tb_main[8] = {AR_main, BC_main, CEM_main, CRC_main, CUCKOO_main,
                             DIJKSTRA_main, RSA_main, SORT_main};

const uint8_t status_code[8][2] = {
    {0, 15}, {51, 60}, {85, 90}, {102, 105},
    {150, 153}, {165, 170}, {195, 204}, {240, 255}
};

extern void take_snapshot();
extern void recovery();

#define VOLT_MONIT_INTERVAL_IN_US         1000  // TODO: choose a proper value
#define SNAPSHOT_VOLT_THRESHOLD           2500  // in mV, TODO: choose a proper value
#define RECOVERY_VOLT_THRESHOLD           3000  // in mV, TODO: choose a proper value

int main()
{
    power_on_init();
    clock_sys_init();
    dma_init();
    uart2target_init();

    ref_volt_init();
    adc_timer_init(VOLT_MONIT_INTERVAL_IN_US * WORKING_FREQUENCY_IN_MHZ);
    adc_init();

    // DEBUG ONLY.
    /* This flag is only used in Debug tests. We found that when the CCS project was in Flash,
     * it would run for a short period of time before it was completed. This makes what we expect
     * the first run to actually be the second run for the program. Therefore, the program will
     * only start running if the button is pressed manually.
     * */
    static __nv uint8_t running_flag = 0;
    if (running_flag == 0) {
        turn_on_green_led;  // System ready.
        left_button_init;
        while (!check_button_press) {/* empty */}
        left_button_disable;
        turn_off_green_led;
        running_flag = 1;
    }

    // SYSTEM STATE FLAGS.
    /* These flags are used to indicate the successful operation or exception of the system.
     * -- If the RED light is on, it means that the system has a data consistency error.
     *    Data-consistency error flag is set in every testbench.
     * -- If the GREEN light is on, it means that there is not enough power to complete the snapshot,
     *    which means that the capacitor capacity needs to be increased and the snapshot voltage
     *    threshold needs to be increased.
     *
     * -- If the RED and GREEN lights are on at the same time, the system has successfully completed
     *    all tasks.
     *
     * The green light has a higher priority than the red light, which means that we can detect data
     * consistency errors due to backup failures.
     */
    if (snapshot_taking_error_flag == true)     { turn_on_green_led;                  LPM1; }
    if (data_consistency_error_flag == true)    { turn_on_red_led;                    LPM1; }
    if (task_success_flag == true)              { turn_on_green_led; turn_on_red_led; LPM1; }

    /* Start ADC and its TimerA */
//    adc_start;

//    system_in_lpm = 1;                      // System Enter LPM01.
//    __bis_SR_register(GIE | LPM1_bits);     // After initialization, Enable Interrupt and enter LPM1;
//    recovery_needed = 1;

    // TODO: Tasks here.
    uint16_t repeat_time = 10;
    while ((repeat_time--) != 0) {
        for (uint16_t i = 0; i < 8; ++i) {
            EUSCI_A_UART_transmitData(UART_BASEADDR, status_code[i][0]);
            (* tb_main[i] )();
            EUSCI_A_UART_transmitData(UART_BASEADDR, status_code[i][1]);
        }
    }

    task_success_flag = 1;      // Tasks success.
    __bic_SR_register(GIE);     // Disable interrupt.

}

#if defined(__MSP430FR5994__) || defined(__MSP430FR5969__)
#pragma vector = ADC12_VECTOR
#elif defined(__MSP430FR2433__)
#pragma vector=ADC_VECTOR
#endif
__interrupt void ADC12_ISR(void)
{
    uint16_t mem_read = adc_read_memory;

#if defined(__MSP430FR5994__) || defined(__MSP430FR5969__)
    // mem_read * ((2.0 / 4.096 * 2.2) * 1024)[=1100] / 1024
    uint16_t volt = (uint16_t)( ((uint32_t)mem_read * 1100) >> 10 );
#elif defined(__MSP430FR2433__)
    // mem_erad * ((1.5 / 1.024 * 2.2) * 1024)[=3300] / 1024
    uint16_t volt = (uint16_t)( ((uint32_t)mem_read * 3300) >> 10 );
#endif

    if (system_in_lpm == 1 && volt > RECOVERY_VOLT_THRESHOLD) {
        if (recovery_needed == 0) {
            recovery_needed = 1;
            goto safe_exit_and_running;
        }
        recovery();
    }

    else if (system_in_lpm == 0 && volt < SNAPSHOT_VOLT_THRESHOLD) {
        snapshot_taking_error_flag = true;
        take_snapshot();
        asm("  nop");   // Recovery here.

        /* The branch the program enters after the snapshot is taken */
        if (snapshot_taking_error_flag == true) {
            snapshot_taking_error_flag = false;
            goto sleep;
        }
        /* The branch the program enters after the system is recovery */
        else goto safe_exit_and_running;
    }

    else goto default_exit;

    safe_exit_and_running:
    system_in_lpm = 0;
    __bic_SR_register_on_exit(LPM1_bits);
    // Go on to dafault_exit.

    default_exit:
    adc_clear_interrupt;
    return;

    sleep:
    system_in_lpm = 1;
    adc_clear_interrupt;
    __bis_SR_register(GIE | LPM1_bits);     // LPM1 and nested interrupt enabled.
}
