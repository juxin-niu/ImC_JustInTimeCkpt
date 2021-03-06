//*****************************************************************************
//
// saph_a.h - Driver for the SAPH_A Module.
//
//*****************************************************************************

#ifndef __MSP430WARE_SAPH_A_H__
#define __MSP430WARE_SAPH_A_H__

#include <lib/driverlib_MSP430FR5xx_6xx/inc/hw_memmap.h>

#ifdef __MSP430_HAS_SAPH_A__

//*****************************************************************************
//
// If building with a C++ compiler, make all of the definitions in this header
// have a C binding.
//
//*****************************************************************************
#ifdef __cplusplus
extern "C"
{
#endif

//*****************************************************************************
//
// The following value specifies how many configurable channels in physcial
// interface.
//
//*****************************************************************************
#define SAPH_A_PHY_CHANNEL_COUNT                                                2

typedef struct _phy_param {
    //! Is the physical output channel to configure.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_CHANNEL_1
    //! - \b SAPH_A_PHY_CHANNEL_2
    uint16_t channel;
    //! Is the channel output value.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_OUTPUT_HIGH 
    //! - \b SAPH_A_PHY_OUTPUT_LOW [Default]
    uint16_t outputValue;
    //! Is the channel output enable.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_OUTPUT_ENABLE 
    //! - \b SAPH_A_PHY_OUTPUT_DISABLE [Default]
    uint16_t enableOutput;
    //! Is the channel output full pull enable.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_FULLPULL_ENABLE 
    //! - \b SAPH_A_PHY_FULLPULL_DISABLE [Default]
    uint16_t enableFullPull;
    //! Is the channel output termination enable.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_TERMINATION_ENABLE 
    //! - \b SAPH_A_PHY_TERMINATION_DISABLE [Default]
    uint16_t enableTermination;
    //! Is the channel output functional select.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_OUTPUT_GENERAL_PURPOSE [Default]
    //! - \b SAPH_A_PHY_OUTPUT_PULSEGENERATOR_SINGLE_DRIVE
    //! - \b SAPH_A_PHY_OUTPUT_PULSEGENERATOR_DIFFERENTIAL_DRIVE
    uint16_t outputFunction;
    //! Is the channel pull up trim pattern.
    uint16_t pullUpTrim;
    //! Is the channel pull down trim pattern.
    uint16_t pullDownTrim;
    //! Is the channel termination trim pattern.
    uint16_t terminationTrim;
} SAPH_A_configPHYParam;

typedef struct _phy_bias {
    //! Selects the channel for excitation bias switch.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_BIAS_SWITCH_OPEN [Default]
    //! - \b SAPH_A_PHY_BIAS_SWITCH_CLOSED 
    uint16_t biasSwitch[SAPH_A_PHY_CHANNEL_COUNT];
    //! Selects PGA bias.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_PGA_BIAS_GROUNDED 
    //! - \b SAPH_A_PHY_PGA_BIAS_LOW_VALUE
    //! - \b SAPH_A_PHY_PGA_BIAS_NOMINAL_VALUE
    //! - \b SAPH_A_PHY_PGA_BIAS_HIGH_VALUE
    uint16_t biasPGA;
    //! Selects excitation bias.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_EXCITATION_BIAS_GROUNDED
    //! - \b SAPH_A_PHY_EXCITATION_BIAS_LOW_VALUE
    //! - \b SAPH_A_PHY_EXCITATION_BIAS_NOMINAL_VALUE
    //! - \b SAPH_A_PHY_EXCITATION_BIAS_HIGH_VALUE
    uint16_t biasExcitation;
    //! Enables charge pump during acquisition.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_MULTIPLEXER_CHARGEPUMP_ENABLE
    //! - \b SAPH_A_PHY_MULTIPLEXER_CHARGEPUMP_DISABLE
    uint16_t enableChargePump;
    //! Enables line input leakage compensation.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_LEAKAGE_COMPENSATION_ENABLE
    //! - \b SAPH_A_PHY_LEAKAGE_COMPENSATION_DISABLE
    uint16_t enableLeakageCompensation;
    //! Selects PGA bias switch open or closed.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_PGA_BIAS_SWITCH_OPEN
    //! - \b SAPH_A_PHY_PGA_BIAS_SWITCH_CLOSED
    uint16_t biasSwitchPGA;
    //! Select ASQ bias switch control.
    //! \n Valid values are:
    //! - \b SAPH_A_PHY_BIAS_SWITCH_CONTROLLED_BY_REGISTER
    //! - \b SAPH_A_PHY_BIAS_SWITCH_CONTROLLED_BY_ASQ
    uint16_t biasSwitchASQ;
} SAPH_A_configPHYBiasParam;

typedef struct _ppg_count
{
    //! Selects high impedance input.
    //! \n Valid values are:
    //! - \b SAPH_A_PPG_HIGH_IMPEDANCE_ON_PAUSE_OUTPUTDRIVE
    //! - \b SAPH_A_PPG_HIGH_IMPEDANCE_ON_PAUSE_PLEV
    uint16_t highImpedance;
    //! Sets the pause level high or low.
    //! \n Valid values are:
    //! - \b SAPH_A_PPG_PAUSE_LEVEL_LOW
    //! - \b SAPH_A_PPG_PAUSE_LEVEL_HIGH
    uint16_t pauseLevel;
    //! Sets the pause polarity high or low.
    //! \n Valid values are:
    //! - \b SAPH_A_PPG_PAUSE_POLARITY_HIGH
    //! - \b SAPH_A_PPG_PAUSE_POLARITY_LOW
    uint16_t pausePolarity;
    //! Sets the stop pulse count.
    uint16_t stopPauseCount;
    //! Sets the excitation pulse count.
    uint16_t excitationPulseCount;
} SAPH_A_configPPGCountParam;

typedef struct _ppg_config
{
    //! Enables PPG prescaler.
    //! \n Valid values are:
    //! - \b SAPH_A_PPG_PRESCALER_ENABLE
    //! - \b SAPH_A_PPG_PRESCALER_DISABLE
    uint16_t enablePrescaler;
    //! Selects PPG trigger source.
    //! \n Valid values are:
    //! - \b SAPH_A_PPG_TRIGGER_SOURCE_SOFTWARE
    //! - \b SAPH_A_PPG_TRIGGER_SOURCE_ASQ
    //! - \b SAPH_A_PPG_TRIGGER_SOURCE_TIMER
    uint16_t triggerSource;
    //! Selects PPG channel.
    //! \n Valid values are:
    //! - \b SAPH_A_PPG_CHANNEL_0
    //! - \b SAPH_A_PPG_CHANNEL_1
    uint16_t channelSelect;
    //! Selects PPG or ASEQ in charge of PHY port.
    //! \n Valid values are:
    //! - \b SAPH_A_PPG_PORT_CHARGED_BY_PPG
    //! - \b SAPH_A_PPG_PORT_CHARGED_BY_ASEQ
    uint16_t portSelect;
} SAPH_A_configPPGParam;

typedef struct _asq_config
{
    //! Enables ASQ abort on errors if the conversion result is outside of expected
    //! value or an overflow/underflow condition occured.
    //! \n Valid values are:
    //! - \b SAPH_A_ASQ_ABORT_ON_ERROR_ENABLE
    //! - \b SAPH_A_ASQ_ABORT_ON_ERROR_DISABLE
    uint16_t abortOnError;
    //! Selects ASQ trigger source.
    //! \n Valid values are:
    //! - \b SAPH_A_ASQ_TRIGGER_SOURCE_SOFTWARE
    //! - \b SAPH_A_ASQ_TRIGGER_SOURCE_P_SEQUENCER
    //! - \b SAPH_A_ASQ_TRIGGER_SOURCE_TIMER
    uint16_t triggerSource;
    //! Selects ASQ channel.
    //! \n Valid values are:
    //! - \b SAPH_A_ASQ_CHANNEL_0
    //! - \b SAPH_A_ASQ_CHANNEL_1
    uint16_t channelSelect;
    //! Selects pwn channel or opposite side channel to receive.
    //! \n Valid values are:
    //! - \b SAPH_A_ASQ_IDENTICAL_CHANNEL
    //! - \b SAPH_A_ASQ_DIFFERENT_CHANNEL
    uint16_t sideOfChannel;
    //! Selects standby indication.
    //! \n Valid values are:
    //! - \b SAPH_A_ASQ_STANDBY_INDICATION_POWEROFF
    //! - \b SAPH_A_ASQ_STANDBY_INDICATION_STANDBY
    uint16_t standByIndication;
    //! Requests OFF in the end of sequence.
    //! \n Valid values are:
    //! - \b SAPH_A_ASQ_END_OF_SEQUENCE_OFF_DISABLE
    //! - \b SAPH_A_ASQ_END_OF_SEQUENCE_OFF_ENABLE
    uint16_t endOfSequence;
    //! Selects early receive bias generating source.
    //! \n Valid values are:
    //! - \b SAPH_A_ASQ_EARLY_RECEIVE_BIAS_BY_TIMEMARK_C
    //! - \b SAPH_A_ASQ_EARLY_RECEIVE_BIAS_BY_TIMEMARK_A
    uint16_t earlyReceiveBias;
    //! Enables channel toggle.
    //! \n Valid values are:
    //! - \b SAPH_A_ASQ_TOGGLE_CHANNEL_ENABLE
    //! - \b SAPH_A_ASQ_TOGGLE_CHANNEL_DISABLE
    uint16_t enableChannelToggle;
} SAPH_A_configASQParam;

typedef struct _asq_ping_config
{
    //! Sets ASQ ping counter for polarity.
    uint16_t polarity;
    //! Sets ASQ ping counter for pause level.
    uint16_t pauseLevel;
    //! Sets ASQ ping counter for high impedance.
    uint16_t pauseHighImpedance;
} SAPH_A_configASQPingParam;

typedef struct _mcnf_config
{
    //! Enables/disables low power bias operation mode.
    //! \n Valid values are:
    //! - \b SAPH_A_LOW_POWER_BIAS_MODE_DISABLE [Default]
    //! - \b SAPH_A_LOW_POWER_BIAS_MODE_ENABLE
    uint16_t lowPowerBiasMode;
    //! Enables/disables charge pump of the input multiplexer.
    //! \n Valid values are:
    //! - \b SAPH_A_CHARGE_PUMP_ON_SDHS_ASQ_REQUESTS_ONLY [Default]
    //! - \b SAPH_A_CHARGE_PUMP_ON_ALWAYS
    uint16_t chargePump;
    //! Sets bias impedance for RxBias and TxBias.
    //! \n Valid values are:
    //! - \b SAPH_A_MCNF_500_OHMS_RXBIAS_450_OHMS_TXBIAS
    //! - \b SAPH_A_MCNF_900_OHMS_RXBIAS_850_OHMS_TXBIAS
    //! - \b SAPH_A_MCNF_1500_OHMS_RXBIAS_1450_OHMS_TXBIAS [Default]
    //! - \b SAPH_A_MCNF_2950_OHMS_RXBIAS_2900_OHMS_TXBIAS
    uint16_t biasImpedance;
} SAPH_A_configModeParam;

typedef struct _xpg_config
{
    //! Selects the type of event generated by dual tone loop mode.
    //! \n Valid values are:
    //! - \b SAPH_A_TIMER_COUNT_EVENT
    //! - \b SAPH_A_DMA_TRIGGER_EVENT
    uint16_t eventType;
    //! Selects extended mode type.
    //! \n Valid values are:
    //! - \b SAPH_A_SINGLE_TONE_GENERATION
    //! - \b SAPH_A_DUAL_TONE_GENERATION
    //! - \b SAPH_A_DUAL_TONE_LOOP
    uint16_t extendedMode;
    //! Selects count of extra excitation pulses excited.
    uint16_t extraPulses;
} SAPH_A_configXPGParam;

//*****************************************************************************
//
// The following are values that can be passed to the mask parameter for
// functions: SAPH_A_clearInterrupt(), SAPH_A_enableInterrupt(), and 
// SAPH_A_disableInterrupt() as well as returned by the 
// SAPH_A_getInterruptStatus() function.
//
//*****************************************************************************
#define SAPH_A_DATA_ERROR_INTERRUPT                                       DATAERR
#define SAPH_A_TIMEMARK_F_TIMEOUT_INTERRUPT                                 TMFTO
#define SAPH_A_ACQUISITION_SEQUENCER_DONE_INTERRUPT                         SEQDN
#define SAPH_A_PING_TRANSMIT_DONE_INTERRUPT                                 PNGDN

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHY().
//
//*****************************************************************************
#define SAPH_A_PHY_CHANNEL_1                                                    0
#define SAPH_A_PHY_CHANNEL_2                                                    1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHY().
//
//*****************************************************************************
#define SAPH_A_PHY_OUTPUT_HIGH                                           CH0OUT_1
#define SAPH_A_PHY_OUTPUT_LOW                                            CH0OUT_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHY().
//
//*****************************************************************************
#define SAPH_A_PHY_OUTPUT_ENABLE                                          CH0OE_1
#define SAPH_A_PHY_OUTPUT_DISABLE                                         CH0OE_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHY().
//
//*****************************************************************************
#define SAPH_A_PHY_FULLPULL_ENABLE                                        CH0FP_1
#define SAPH_A_PHY_FULLPULL_DISABLE                                       CH0FP_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHY().
//
//*****************************************************************************
#define SAPH_A_PHY_TERMINATION_ENABLE                                   CH0TERM_1
#define SAPH_A_PHY_TERMINATION_DISABLE                                  CH0TERM_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHY().
//
//*****************************************************************************
#define SAPH_A_PHY_OUTPUT_GENERAL_PURPOSE                               PCH0SEL_0
#define SAPH_A_PHY_OUTPUT_PULSEGENERATOR_SINGLE_DRIVE                   PCH0SEL_1
#define SAPH_A_PHY_OUTPUT_PULSEGENERATOR_DIFFERENTIAL_DRIVE             PCH0SEL_2

//*****************************************************************************
//
// The following are values that can be passed to the enableDummyLoad parameter
// for functions: SAPH_A_configurePHYMultiplexer().
//
//*****************************************************************************
#define SAPH_A_PHY_DUMMYLOAD_ENABLE                                       DUMEN_1
#define SAPH_A_PHY_DUMMYLOAD_DISABLE                                      DUMEN_0

//*****************************************************************************
//
// The following are values that can be passed to the sourceControl parameter
// for functions: SAPH_A_configurePHYMultiplexer().
//
//*****************************************************************************
#define SAPH_A_PHY_SOURCE_CONTROLLED_BY_REGISTER                         MUXCTL_0
#define SAPH_A_PHY_SOURCE_CONTROLLED_BY_ASQ                              MUXCTL_1

//*****************************************************************************
//
// The following are values that can be passed to the inputChannel parameter
// for functions: SAPH_A_configurePHYMultiplexer().
//
//*****************************************************************************
#define SAPH_A_PHY_INPUT_CHANNEL_0                                  MUXSEL__CH0IN
#define SAPH_A_PHY_INPUT_CHANNEL_1                                  MUXSEL__CH1IN

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHYBias().
//
//*****************************************************************************
#define SAPH_A_PHY_BIAS_SWITCH_OPEN                                     CH0EBSW_0
#define SAPH_A_PHY_BIAS_SWITCH_CLOSED                                   CH0EBSW_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHYBias().
//
//*****************************************************************************
#define SAPH_A_PHY_PGA_BIAS_GROUNDED                                    PGABIAS_0
#define SAPH_A_PHY_PGA_BIAS_LOW_VALUE                                   PGABIAS_1
#define SAPH_A_PHY_PGA_BIAS_NOMINAL_VALUE                               PGABIAS_2
#define SAPH_A_PHY_PGA_BIAS_HIGH_VALUE                                  PGABIAS_3

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHYBias().
//
//*****************************************************************************
#define SAPH_A_PHY_EXCITATION_BIAS_GROUNDED                             EXCBIAS_0
#define SAPH_A_PHY_EXCITATION_BIAS_LOW_VALUE                            EXCBIAS_1
#define SAPH_A_PHY_EXCITATION_BIAS_NOMINAL_VALUE                        EXCBIAS_2
#define SAPH_A_PHY_EXCITATION_BIAS_HIGH_VALUE                           EXCBIAS_3

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHYBias().
//
//*****************************************************************************
#define SAPH_A_PHY_MULTIPLEXER_CHARGEPUMP_ENABLE                           CPDA_1
#define SAPH_A_PHY_MULTIPLEXER_CHARGEPUMP_DISABLE                          CPDA_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHYBias().
//
//*****************************************************************************
#define SAPH_A_PHY_LEAKAGE_COMPENSATION_ENABLE                             LILC_1
#define SAPH_A_PHY_LEAKAGE_COMPENSATION_DISABLE                            LILC_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHYBias().
//
//*****************************************************************************
#define SAPH_A_PHY_PGA_BIAS_SWITCH_OPEN                                  PGABSW_0
#define SAPH_A_PHY_PGA_BIAS_SWITCH_CLOSED                                PGABSW_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePHYBias().
//
//*****************************************************************************
#define SAPH_A_PHY_BIAS_SWITCH_CONTROLLED_BY_REGISTER                    ASQBSC_0
#define SAPH_A_PHY_BIAS_SWITCH_CONTROLLED_BY_ASQ                         ASQBSC_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePPGCount().
//
//*****************************************************************************
#define SAPH_A_PPG_HIGH_IMPEDANCE_ON_PAUSE_HIGH                            PHIZ_1
#define SAPH_A_PPG_HIGH_IMPEDANCE_ON_PAUSE_LOW                             PHIZ_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePPGCount().
//
//*****************************************************************************
#define SAPH_A_PPG_PAUSE_LEVEL_HIGH                                        PLEV_1
#define SAPH_A_PPG_PAUSE_LEVEL_LOW                                         PLEV_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePPGCount().
//
//*****************************************************************************
#define SAPH_A_PPG_PAUSE_POLARITY_HIGH                                     PPOL_0
#define SAPH_A_PPG_PAUSE_POLARITY_LOW                                      PPOL_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePPG().
//
//*****************************************************************************
#define SAPH_A_PPG_PRESCALER_ENABLE                                       PSCEN_1
#define SAPH_A_PPG_PRESCALER_DISABLE                                      PSCEN_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePPG().
//
//*****************************************************************************
#define SAPH_A_PPG_TRIGGER_SOURCE_SOFTWARE                                TRSEL_0
#define SAPH_A_PPG_TRIGGER_SOURCE_ASQ                                     TRSEL_1
#define SAPH_A_PPG_TRIGGER_SOURCE_TIMER                                   TRSEL_2

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePPG().
//
//*****************************************************************************
#define SAPH_A_PPG_CHANNEL_0                                           PPGCHSEL_0
#define SAPH_A_PPG_CHANNEL_1                                           PPGCHSEL_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configurePPG().
//
//*****************************************************************************
#define SAPH_A_PPG_PORT_CHARGED_BY_PPG                                    PGSEL_0
#define SAPH_A_PPG_PORT_CHARGED_BY_ASEQ                                   PGSEL_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureASQ().
//
//*****************************************************************************
#define SAPH_A_ASQ_ABORT_ON_ERROR_ENABLE                                 ERABRT_1
#define SAPH_A_ASQ_ABORT_ON_ERROR_DISABLE                                ERABRT_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureASQ().
//
//*****************************************************************************
#define SAPH_A_ASQ_TRIGGER_SOURCE_SOFTWARE                        TRIGSEL__SWTRIG
#define SAPH_A_ASQ_TRIGGER_SOURCE_P_SEQUENCER                        TRIGSEL__PSQ
#define SAPH_A_ASQ_TRIGGER_SOURCE_TIMER                            TRIGSEL__TIMER

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureASQ().
//
//*****************************************************************************
#define SAPH_A_ASQ_CHANNEL_0                                           ASQCHSEL_0
#define SAPH_A_ASQ_CHANNEL_1                                           ASQCHSEL_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureASQ().
//
//*****************************************************************************
#define SAPH_A_ASQ_DIFFERENT_CHANNEL                                      CHOWN_0
#define SAPH_A_ASQ_IDENTICAL_CHANNEL                                      CHOWN_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureASQ().
//
//*****************************************************************************
#define SAPH_A_ASQ_STANDBY_INDICATION_POWEROFF                      STDBY__PWROFF
#define SAPH_A_ASQ_STANDBY_INDICATION_STANDBY                        STDBY__STDBY

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureASQ().
//
//*****************************************************************************
#define SAPH_A_ASQ_END_OF_SEQUENCE_OFF_DISABLE                            ESOFF_0
#define SAPH_A_ASQ_END_OF_SEQUENCE_OFF_ENABLE                             ESOFF_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureASQ().
//
//*****************************************************************************
#define SAPH_A_ASQ_EARLY_RECEIVE_BIAS_BY_TIMEMARK_C                     EARLYRB_0
#define SAPH_A_ASQ_EARLY_RECEIVE_BIAS_BY_TIMEMARK_A                     EARLYRB_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureASQ().
//
//*****************************************************************************
#define SAPH_A_ASQ_TOGGLE_CHANNEL_ENABLE                                  CHTOG_1
#define SAPH_A_ASQ_TOGGLE_CHANNEL_DISABLE                                 CHTOG_0

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureMode().
//
//*****************************************************************************
#define SAPH_A_LOW_POWER_BIAS_MODE_DISABLE                                 LPBE_0
#define SAPH_A_LOW_POWER_BIAS_MODE_ENABLE                                LPBE_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureMode().
//
//*****************************************************************************
#define SAPH_A_CHARGE_PUMP_ON_SDHS_ASQ_REQUESTS_ONLY                      CPEO_0
#define SAPH_A_CHARGE_PUMP_ON_ALWAYS                                      CPEO_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureMode().
//
//*****************************************************************************
#define SAPH_A_MCNF_500_OHMS_RXBIAS_450_OHMS_TXBIAS                       BIMP_0
#define SAPH_A_MCNF_900_OHMS_RXBIAS_850_OHMS_TXBIAS                       BIMP_1
#define SAPH_A_MCNF_1500_OHMS_RXBIAS_1450_OHMS_TXBIAS                     BIMP_2
#define SAPH_A_MCNF_2950_OHMS_RXBIAS_2900_OHMS_TXBIAS                     BIMP_3

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureExtendedPPG().
//
//*****************************************************************************
#define SAPH_A_TIMER_COUNT_EVENT                                        ETY_0
#define SAPH_A_DMA_TRIGGER_EVENT                                        ETY_1

//*****************************************************************************
//
// The following are values that can be passed to the config parameter for
// functions: SAPH_A_configureExtendedPPG().
//
//*****************************************************************************
#define SAPH_A_SINGLE_TONE_GENERATION                                   XMOD_0
#define SAPH_A_DUAL_TONE_GENERATION                                     XMOD_2
#define SAPH_A_DUAL_TONE_LOOP                                           XMOD_3

//*****************************************************************************
//
// The following are values that can be returned by the 
// SAPH_A_getPPGPhaseStatus() API
//
//*****************************************************************************
#define SAPH_A_PPG_STOP_PHASE                                           XSTAT_0
#define SAPH_A_PPG_PAUSE_PHASE                                          XSTAT_1
#define SAPH_A_PPG_REGULAR_EXCITATION_PHASE                             XSTAT_2
#define SAPH_A_PPG_EXTRA_EXCITATION_PHASE                               XSTAT_3

//*****************************************************************************
//
// Prototypes for the APIs.
//
//*****************************************************************************

//*****************************************************************************
//
//! \brief Unlocks certain SAPH_A registers.
//!
//! Unlock SAPH_A registers with offset address of 0xF or higher. IIDX, MIS, RIS,
//! IMSC, ICR, ISR, DESCLO, and DESCHI registers are not affected and the
//! registers are not locked. Utilize this function if those registers need to
//! be modified.
//! \n\b NOTE: Most of the SAPH_A APIs will not work unless SAPH_A is unlocked.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//
//*****************************************************************************
extern void SAPH_A_unlock(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Locks certain SAPH_A registers.
//!
//! Locks SAPH_A registers with offset address of 0xF or higher. IIDX, MIS, RIS,
//! IMSC, ICR, ISR, DESCLO, and DESCHI registers are not affected and the
//! registers are not locked. Utilize this function after SAPH_A_unlock()
//! after necessary registers have been modified.
//! SAPH_A registers, with the exception of the list in paragraph above, are
//! locked by default.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//
//*****************************************************************************
extern void SAPH_A_lock(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Clears SAPH_A interrupts.
//!
//! The SAPH_A interrupt source is cleared, so that it no longer asserts. If the
//! interrupt is not enabled, the corresponding bit in the RIS register bit will
//! be cleared. If the interrupt is enabled, the corresponding bit both MIS and 
//! RIS registers will be both cleared.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param mask is the logical OR of any of the following:
//!        - \b SAPH_A_DATA_ERROR_INTERRUPT - SAPH_A data error interrupt
//!        - \b SAPH_A_TIMEMARK_F_TIMEOUT_INTERRUPT - SAPH_A TMF time out interrupt
//!        - \b SAPH_A_ACQUISITION_SEQUENCER_DONE_INTERRUPT - SAPH_A acquistion sequencer done interrupt
//!        - \b SAPH_A_PING_TRANSMIT_DONE_INTERRUPT - SAPH_A ping transmit done interrupt
//!
//! \return None
//
//*****************************************************************************
extern void SAPH_A_clearInterrupt(uint16_t baseAddress, uint8_t mask);

//*****************************************************************************
//
//! \brief Enables SAPH_A interrupts.
//!
//! Enables the indicated SAPH_A interrupt sources.  Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor. <b>Does not clear interrupt flags.</b>
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param mask is the logical OR of any of the following:
//!        - \b SAPH_A_DATA_ERROR_INTERRUPT - SAPH_A data error interrupt
//!        - \b SAPH_A_TIMEMARK_F_TIMEOUT_INTERRUPT - SAPH_A TMF time out interrupt
//!        - \b SAPH_A_ACQUISITION_SEQUENCER_DONE_INTERRUPT - SAPH_A acquistion sequencer done interrupt
//!        - \b SAPH_A_PING_TRANSMIT_DONE_INTERRUPT - SAPH_A ping transmit done interrupt
//!
//! \return None
//
//*****************************************************************************
extern void SAPH_A_enableInterrupt(uint16_t baseAddress, uint8_t mask);

//*****************************************************************************
//
//! \brief Disables selected SAPH_A interrupt sources.
//!
//! Disables the indicated SAPH_A interrupt sources. Only the sources that are
//! enabled can be reflected to the processor interrupt; disabled sources have
//! no effect on the processor.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param mask is the logical OR of any of the following:
//!        - \b SAPH_A_DATA_ERROR_INTERRUPT - SAPH_A data error interrupt
//!        - \b SAPH_A_TIMEMARK_F_TIMEOUT_INTERRUPT - SAPH_A TMF time out interrupt
//!        - \b SAPH_A_ACQUISITION_SEQUENCER_DONE_INTERRUPT - SAPH_A acquistion sequencer done interrupt
//!        - \b SAPH_A_PING_TRANSMIT_DONE_INTERRUPT - SAPH_A ping transmit done interrupt
//!
//! \return None
//
//*****************************************************************************
extern void SAPH_A_disableInterrupt(uint16_t baseAddress, uint8_t mask);

//*****************************************************************************
//
//! \brief Gets the current SAPH_A interrupt status.
//!
//! This returns the interrupt status for the SAPH_A module based on which flag
//! is passed.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param mask is the logical OR of any of the following:
//!        - \b SAPH_A_DATA_ERROR_INTERRUPT - SAPH_A data error interrupt
//!        - \b SAPH_A_TIMEMARK_F_TIMEOUT_INTERRUPT - SAPH_A TMF time out interrupt
//!        - \b SAPH_A_ACQUISITION_SEQUENCER_DONE_INTERRUPT - SAPH_A acquistion sequencer done interrupt
//!        - \b SAPH_A_PING_TRANSMIT_DONE_INTERRUPT - SAPH_A ping transmit done interrupt
//!
//! \return Logical OR of any of the following:
//!        - \b SAPH_A_DATA_ERROR_INTERRUPT - SAPH_A data error interrupt
//!        - \b SAPH_A_TIMEMARK_F_TIMEOUT_INTERRUPT - SAPH_A TMF time out interrupt
//!        - \b SAPH_A_ACQUISITION_SEQUENCER_DONE_INTERRUPT - SAPH_A acquistion sequencer done interrupt
//!        - \b SAPH_A_PING_TRANSMIT_DONE_INTERRUPT - SAPH_A ping transmit done interrupt
//
//*****************************************************************************
extern uint8_t SAPH_A_getInterruptStatus(uint16_t baseAddress, uint8_t mask);

//*****************************************************************************
//
//! \brief Configures physical interface output and trim values.
//!
//! This configures SAPH_A physical interface:
//! - channel output 
//! - channel related trim values
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param config is the pointer to the struct for physical interface configuration.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configurePHY(uint16_t baseAddress, SAPH_A_configPHYParam *config);

//*****************************************************************************
//
//! \brief Configures physical interface multiplexer.
//!
//! This configures SAPH_A physical interface mutliplexer for dummy load, channel
//! multiplexer source control and input channel selection.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param enableDummyLoad indicates whether to enable/disable dummy load on non-
//!        selected multiplexer inputs.
//!        Valid values are:
//!        - \b SAPH_A_PHY_DUMMYLOAD_ENABLE
//!        - \b SAPH_A_PHY_DUMMYLOAD_DISABLE [Default]
//! \param sourceControl selects which controls the multiplexer.
//!        Valid values are:
//!        - \b SAPH_A_PHY_SOURCE_CONTROLLED_BY_REGISTER [Default]
//!        - \b SAPH_A_PHY_SOURCE_CONTROLLED_BY_ASQ
//! \param inputChannel selects input channel.
//!        Valid values are:
//!        - \b SAPH_A_PHY_INPUT_CHANNEL_0 [Default]
//!        - \b SAPH_A_PHY_INPUT_CHANNEL_1
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configurePHYMultiplexer(uint16_t baseAddress,
        uint16_t enableDummyLoad, uint16_t sourceControl, uint16_t inputChannel);

//*****************************************************************************
//
//! \brief Configures physical interface bias.
//!
//! This configures SAPH_A physical interface bias parameters:
//! - excitation bias switch
//! - PGA bias
//! - excitation bias
//! - charge pump
//! - line input leakage
//! - compensation
//! - ASQ bias
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param config is the pointer to the struct for physical interface bias configuration.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configurePHYBias(uint16_t baseAddress,
        SAPH_A_configPHYBiasParam *config);

//*****************************************************************************
//
//! \brief Configures pulse generator count.
//!
//! This configures SAPH_A pulse generator count:
//! - high impedance
//! - pause level
//! - pause polarity
//! - stop pulse
//! - excitation pulse
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param config is the pointer to the struct for pulse generator count configuration.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configurePPGCount(uint16_t baseAddress,
        SAPH_A_configPPGCountParam *config);

//*****************************************************************************
//
//! \brief Sets pulse generator low period.
//!
//! The low phase of period of generator pulses defines the length of low phase
//! of the pulses in units of high speed clocks. The minimum count is two regardless
//! of the value set in this register.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param period is the low period value to set.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_setPPGLowPeriod(uint16_t baseAddress, uint16_t period);

//*****************************************************************************
//
//! \brief Sets pulse generator high period.
//!
//! The high phase of period of generator pulses defines the length of high phase
//! of the pulses in units of high speed clocks. The minimum count is two regardless
//! of the value set in this register.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param period is the high period value to set.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_setPPGHighPeriod(uint16_t baseAddress, uint16_t period);

//*****************************************************************************
//
//! \brief Configures pulse generator.
//!
//! This configures SAPH_A pulse generator:
//! - trigger source
//! - prescaler enable
//! - channel select
//! - control select
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param config is the pointer to the struct for pulse generator configuration.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configurePPG(uint16_t baseAddress, SAPH_A_configPPGParam *config);

//*****************************************************************************
//
//! \brief Triggers pulse generator.
//!
//! This function triggers the pulse generator if SAPH_A_PPG_TRIGGER_SOURCE_SOFTWARE
//! is selected as the trigger sourcce.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_triggerPPG(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Stops pulse generator.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_stopPPG(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Configures acquisition sequencer.
//!
//! This configures SAPH_A acquisition sequencer:
//! - trigger source
//! - abort-on-error control
//! - channel select
//! - side of channel to receive
//! - standby indication
//! - OFF at end-of-sequence
//! - early receive bias
//! - channel toggle
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param config is the pointer to the struct for acquisition sequencer configuration.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configureASQ(uint16_t baseAddress, SAPH_A_configASQParam *config);

//*****************************************************************************
//
//! \brief Triggers acquisition sequencer.
//!
//! This function triggers the acquisition sequencer if SAPH_A_ASQ_TRIGGER_SOURCE_SOFTWARE
//! is selected as the trigger sourcce.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_triggerASQ(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Stops acquisition sequencer.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_stopASQ(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Gets ping counter of acquisition sequencer.
//!
//! This function returns ping counter which represents the number of acquistion
//! turns regardless if up/down direction is changed. The acquistion stops if
//! this count decrements from zero.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern uint8_t SAPH_A_getASQPingCounter(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Configures acquisition sequencer ping parameters.
//!
//! This configures SAPH_A acquisition sequencer ping:
//! - output polarity
//! - pause level
//! - pause impedance
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param config is the pointer to the struct for acquisition sequencer ping 
//!        configuration.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configureASQPing(uint16_t baseAddress,
        SAPH_A_configASQPingParam *config);

//*****************************************************************************
//
//! \brief Configures acquisition sequencer time base parameters.
//!
//! This configures SAPH_A acquisition sequencer time base parameters:
//! - power state
//! - prescaler start value
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param prescalerStartValue is the ASQ prescaler start value.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configureASQTimeBase(uint16_t baseAddress,
        uint16_t prescalerStartValue);

//*****************************************************************************
//
//! \brief Starts acquisition timer.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_startASQTimer(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Stops acquisition timer.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_stopASQTimer(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Clears acquisition timer.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_clearASQTimer(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Configures certain mode configuration parameters.
//!
//! This configures SAPH:
//! - bias generator impedance
//! - charge pump enable timing
//! - low power bias mode
//! \b NOTE: This will modify all elements of SAPH_A mode configuration register. If there are elements not specified in the config parameter, the register values will be cleared. There are other SAPH_A functions to modify these features individually.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param config is the pointer to the struct for mode configuration.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configureMode(uint16_t baseAddress,
        SAPH_A_configModeParam *config);

//*****************************************************************************
//
//! \brief Enables low power bias operation mode.
//!
//! In this mode, the SAPH_A acquisition sequencer (ASQ) uses the CHxEBSW and PGABSW as auxiliary values to achieve faster channel setting on reactive input loads. The ASQ has full controls over the bias switch multiplexer.
//! \b NOTE: Avoid changing operation mode unless PSQ is in OFF state. Otherwise, it can cause corrupt measurement results and irregular triggers of sub modules by ASQ.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_enableLowPowerBiasMode(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Disables low power bias operation mode.
//!
//! Enters manual bias mode and regular ASQ bias mode. In this configuration, the user controls by the ASQBSW has full control over TxBias and RxBias switches.
//! \b NOTE: Avoid changing operation mode unless PSQ is in OFF state. Otherwise, it can cause corrupt measurement results and irregular triggers of sub modules by ASQ.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_disableLowPowerBiasMode(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Keeps charge pump of the input multiplexer always on.
//!
//! The charge pump of the input multiplexer is on regardless of SDHS and ASQ requests. This setting will override other USS charge pump settings elsewhere.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_enableChargePumpAlways(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Charge pump of input multiplexer is only turned on by data acquisition.
//!
//! The charge pump of the input multiplexer is turned on by SDHS and ASQ related requests only. This will also require the charge pump to be enabled explicitly through other methods [controlled by CPDA bit or SAPH_A_configurePHYBias()] in the SAPH_A module.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_enableChargePumpOnAcquisitionOnly(uint16_t baseAddress);

//*****************************************************************************
//
//! \brief Sets impedance of the buffers for RxBias and TxBias.
//!
//! While for resistive loads the lowest impedance shows the fastest settling; this is not the case for reactive loads.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param biasImpedance sets bias impedance for RxBias and TxBias.
//!        Valid values are:
//!        - \b SAPH_A_MCNF_500_OHMS_RXBIAS_450_OHMS_TXBIAS
//!        - \b SAPH_A_MCNF_900_OHMS_RXBIAS_850_OHMS_TXBIAS
//!        - \b SAPH_A_MCNF_1500_OHMS_RXBIAS_1450_OHMS_TXBIAS [Default]
//!        - \b SAPH_A_MCNF_2950_OHMS_RXBIAS_2900_OHMS_TXBIAS
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_setBiasGeneratorImpedance(uint16_t baseAddress, uint16_t biasImpedance);

//*****************************************************************************
//
//! \brief Configures extended pulse generator.
//!
//! This configures SAPH_A extended pulse generator:
//! - event type
//! - extended mode select
//! - extra pulse count
//! \n \b NOTE: This API modifies all elements of the extended pulse generator control register. Any values not specified in the config parameter will end up clearing the other settings.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param config is the pointer to the struct for extended pulse generator configuration.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_configureExtendedPPG(uint16_t baseAddress, SAPH_A_configXPGParam *config);

//*****************************************************************************
//
//! \brief Sets extended pulse generator low period.
//!
//! The low phase of period of generator pulses defines the length of low phase of the extra pulses in units of high speed clocks. The minimum count is two regardless of the value set in this register.
//! Reset type: PUC
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param period is the low period value to set.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_setXPGLowPeriod(uint16_t baseAddress, uint16_t period);

//*****************************************************************************
//
//! \brief Sets extended pulse generator high period.
//!
//! The high phase of period of generator pulses defines the length of high phase of the extra pulses in units of high speed clocks. The minimum count is two regardless of the value set in this register.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//! \param period is the high period value to set.
//!
//! \return None
//!
//*****************************************************************************
extern void SAPH_A_setXPGHighPeriod(uint16_t baseAddress, uint16_t period);

//*****************************************************************************
//
//! \brief Returns the phase status of PPG
//!
//! Returns the phase status of PPG. Reads from SAPH_AXPGCTL.XSTAT.
//!
//! \param baseAddress is the base address of the SAPH_A module.
//!
//! \return \b SAPH_A_PPG_PAUSE_PHASE or 
//!         \b SAPH_A_PPG_STOP_PHASE or
//!         \b SAPH_A_PPG_REGULAR_EXCITATION_PHASE or
//!         \b SAPH_A_PPG_EXTRA_EXCITATION_PHASE
//!
//
//*****************************************************************************
extern uint16_t SAPH_A_getPPGPhaseStatus(uint16_t baseAddress);

//*****************************************************************************
//
// Mark the end of the C bindings section for C++ compilers.
//
//*****************************************************************************
#ifdef __cplusplus
}
#endif

#endif
#endif // __MSP430WARE_SAPH_A_H__

