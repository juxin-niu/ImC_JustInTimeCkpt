
#ifndef IMC_TARGET_SPEC_H_
#define IMC_TARGET_SPEC_H_

#define BUTTON_RESISTOR_PULLUP      0x01
#define BUTTON_RESISTOR_PULLDOWN    0x02

#if defined(__MSP430FR5969__) || defined(__MSP430FR5994__)
    #include <lib/driverlib_MSP430FR5xx_6xx/driverlib.h>
#elif defined(__MSP430FR2433__)
    #include <lib/driverlib_MSP430FR2xx_4xx/driverlib.h>
#else
#error "ERROR: UNSUPPORTED MSP TARGET!"
#endif

// =================================================================== //
//                               UART                                  //
#if defined(__MSP430FR5969__)
    #define UART_TX_PORT            GPIO_PORT_P2
    #define UART_TX_PIN             GPIO_PIN5
    #define UART_TX_FUNCTION        GPIO_SECONDARY_MODULE_FUNCTION
    #define UART_BASEADDR           EUSCI_A1_BASE
#elif defined(__MSP430FR5994__)
    #define UART_TX_PORT            GPIO_PORT_P6
    #define UART_TX_PIN             GPIO_PIN0
    #define UART_TX_FUNCTION        GPIO_PRIMARY_MODULE_FUNCTION
    #define UART_BASEADDR           EUSCI_A3_BASE
#elif defined(__MSP430FR2433__)
    #define UART_TX_PORT            GPIO_PORT_P2
    #define UART_TX_PIN             GPIO_PIN6
    #define UART_TX_FUNCTION        GPIO_PRIMARY_MODULE_FUNCTION
    #define UART_BASEADDR           EUSCI_A1_BASE
#else
#error "ERROR: UNSUPPORTED MSP TARGET!"
#endif

// =================================================================== //
//                              RAM_ADDR                               //
#if defined(__MSP430FR5994__)
    #define TARGET_RAM_ORIGIN       0x1C00
    #define TARGET_RAM_LENGTH       0x1000
#elif defined(__MSP430FR5969__)
    #define TARGET_RAM_ORIGIN       0x1C00
    #define TARGET_RAM_LENGTH       0x0800
#elif defined(__MSP430FR2433__)

#else
#error "ERROR: UNSUPPORTED MSP TARGET!"
#endif

// =================================================================== //
//                                 LED                                 //
#if defined(__MSP430FR5994__)
#define turn_on_red_led             P1OUT |= BIT0
#define turn_off_red_led            P1OUT &= ~BIT0
#define turn_on_green_led           P1OUT |= BIT1
#define turn_off_green_led          P1OUT &= ~BIT1
#elif defined(__MSP430FR5969__)

#elif defined(__MSP430FR2433__)

#else
#error "ERROR: UNSUPPORTED MSP TARGET!"
#endif

// =================================================================== //
//                                BUTTON                               //
#if defined(__MSP430FR5994__)
#define left_button_init                GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN6)
#define check_button_press              (GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN6) == GPIO_INPUT_PIN_LOW)
#define left_button_disable             GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN6); \
                                        GPIO_setOutputLowOnPin(GPIO_PORT_P5, GPIO_PIN6)
#elif defined(__MSP430FR5969__)

#elif defined(__MSP430FR2433__)

#else
#error "ERROR: UNSUPPORTED MSP TARGET!"
#endif

#endif /* IMC_TARGET_SPEC_H_ */
