
#include <ImC/target_spec.h>

void ref_volt_init()
{
    Ref_A_setReferenceVoltage(REF_A_BASE, REF_A_VREF1_2V);
    //!        Valid values are:
    //!        - \b REF_A_VREF1_2V [Default]
    //!        - \b REF_A_VREF2_0V
    //!        - \b REF_A_VREF2_5V
}

void adc_timer_init(uint16_t timePeriod)
{
    // TimerA0 run in continuous mode.
    Timer_A_initUpModeParam timerAInitParam = {0};
    timerAInitParam.clockSource = TIMER_A_CLOCKSOURCE_SMCLK;
    timerAInitParam.clockSourceDivider = TIMER_A_CLOCKSOURCE_DIVIDER_1;
    timerAInitParam.startTimer = false;
    timerAInitParam.timerClear = TIMER_A_DO_CLEAR;
    timerAInitParam.timerInterruptEnable_TAIE = TIMER_A_TAIE_INTERRUPT_DISABLE;
    timerAInitParam.captureCompareInterruptEnable_CCR0_CCIE = TIMER_A_CCIE_CCR0_INTERRUPT_DISABLE;
    timerAInitParam.timerPeriod = timePeriod;   // ADC interval

    Timer_A_initUpMode(TIMER_A0_BASE, &timerAInitParam);

    // CCR0 run in compare mode and generate interrupt.
    Timer_A_initCompareModeParam compareModeParam = {0};
    compareModeParam.compareInterruptEnable = TIMER_A_CAPTURECOMPARE_INTERRUPT_DISABLE;
    compareModeParam.compareOutputMode = TIMER_A_OUTPUTMODE_TOGGLE_SET;
                                        // CCR1 trigger every time TA0R reach TA0CCR0.
    compareModeParam.compareRegister = TIMER_A_CAPTURECOMPARE_REGISTER_1;
    compareModeParam.compareValue = timePeriod >> 1;

    Timer_A_initCompareMode(TIMER_A0_BASE, &compareModeParam);
}

void adc_init()
{
    P1SEL0 |= BIT2;                           // configure P1.2/A2 for ADC function
    P1SEL1 |= BIT2;                           //

    ADC12_B_initParam initParam = {0};
    initParam.clockSourceDivider = ADC12_B_CLOCKDIVIDER_1;
    initParam.clockSourcePredivider = ADC12_B_CLOCKPREDIVIDER__1;
    initParam.clockSourceSelect = ADC12_B_CLOCKSOURCE_ADC12OSC;
    initParam.internalChannelMap = ADC12_B_NOINTCH;
    initParam.sampleHoldSignalSourceSelect = ADC12_B_SAMPLEHOLDSOURCE_1;    // TA0 CCR1 output

    ADC12_B_init(ADC12_B_BASE, &initParam);
    ADC12_B_enable(ADC12_B_BASE);
    ADC12_B_setupSamplingTimer(ADC12_B_BASE,
                               ADC12_B_CYCLEHOLD_64_CYCLES,
                               ADC12_B_CYCLEHOLD_8_CYCLES,
                               ADC12_B_MULTIPLESAMPLESDISABLE
                               );

    ADC12_B_enableInterrupt(ADC12_B_BASE,
                            ADC12_B_IE0,    // Interrupt enabled.
                            0,
                            0);

    ADC12_B_configureMemoryParam configureMemoryParam = {0};
    configureMemoryParam.memoryBufferControlIndex = ADC12_B_MEMORY_0;
    configureMemoryParam.refVoltageSourceSelect = ADC12_B_VREFPOS_INTBUF_VREFNEG_VSS;
    configureMemoryParam.endOfSequence = ADC12_B_NOTENDOFSEQUENCE;
    configureMemoryParam.windowComparatorSelect = ADC12_B_WINDOW_COMPARATOR_DISABLE;
    configureMemoryParam.differentialModeSelect = ADC12_B_DIFFERENTIAL_MODE_DISABLE;
    configureMemoryParam.inputSourceSelect = ADC12_B_INPUT_A2;
    //!        P1.2 A2

    ADC12_B_configureMemory(ADC12_B_BASE, &configureMemoryParam);
}
