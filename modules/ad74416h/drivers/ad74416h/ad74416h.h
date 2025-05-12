#ifndef ZEPHYR_DRIVERS_ADI_AD74416H
#define ZEPHYR_DRIVERS_ADI_AD74416H

#include <zephyr/drivers/sensor.h>


#define AD74416H_N_CHANNELS             4

#define AD74416H_CH_A                   0
#define AD74416H_CH_B                   1
#define AD74416H_CH_C                   2
#define AD74416H_CH_D                   3

/** The value of the sense resistor in ohms */
#define AD74416H_RSENSE                 12
/** 16 bit ADC */
#define AD74416H_ADC_MAX_VALUE		16777215

/** Register map */
#define AD74416H_NOP				0x00
#define AD74416H_CH_FUNC_SETUP(x)               (0x01 + (x * 12))
#define AD74416H_ADC_CONFIG(x)                  (0x02 + (x * 12))
#define AD74416H_DIN_CONFIG0(x)			(0x03 + (x * 12))
#define AD74416H_DIN_CONFIG1(x)			(0x04 + (x * 12))
#define AD74416H_OUTPUT_CONFIG(x)               (0x05 + (x * 12))
#define AD74416H_RTD_CONFIG(x)			(0x06 + (x * 12))
#define AD74416H_FET_LKG_COMP(x)		(0x07 + (x * 12))
#define AD74416H_DO_EXT_CONFIG(x)		(0x08 + (x * 12))
#define AD74416H_I_BURNOUT_CONFIG(x)		(0x09 + (x * 12))
#define AD74416H_DAC_CODE(x)			(0x0A + (x * 12))
#define AD74416H_DAC_ACTIVE(x)			(0x0C + (x * 12))
#define AD74416H_GPIO_CONFIG(x)			(0x32 + x)
#define AD74416H_PWR_OPTIM_CONFIG		0x38
#define AD74416H_ADC_CONV_CTRL			0x39
#define AD74416H_DIAG_ASSIGN			0x3A
#define AD74416H_WTD_CONFIG			0x3B
#define AD74416H_DIN_COMP_OUT			0x3E
#define AD74416H_ALERT_STATUS			0x3F
#define AD74416H_LIVE_STATUS			0x40
#define AD74416H_ADC_RESULT_UPR(x)		(0x41 + (x * 2))
#define AD74416H_ADC_RESULT(x)			(0x42 + (x * 2))
#define AD74416H_ADC_DIAG_RESULT(x)		(0x49 + x)
#define AD74416H_LAST_ADC_RESULT_UPR		0x4D
#define AD74416H_LAST_ADC_RESULT		0x4E
#define AD74416H_DIN_COUNTER(x)			(0x50 + (x * 2))
#define AD74416H_SUPPLY_ALERT_STATUS		0x57
#define AD74416H_CHANNEL_ALERT_STATUS(x)	(0x58 + x)
#define AD74416H_ALERT_MASK			0x5C
#define AD74416H_SUPPLY_ALERT_MASK		0x5D
#define AD74416H_CHANNEL_ALERT_MASK(x)		(0x5E + x)
#define AD74416H_READ_SELECT			0x6E
#define AD74416H_BURST_READ_SEL			0x6F
#define AD74416H_THERM_RST			0x73
#define AD74416H_CMD_KEY			0x74
#define AD74416H_BORADCAST_CMD_KEY		0x75
#define AD74416H_SCRATCH(x)			(0x76 + x)
#define AD74416H_GENERIC_ID			0x7A
#define AD74416H_SILICON_REV			0x7B
#define AD74416H_SILICON_ID0			0x7D
#define AD74416H_SILICON_ID1			0x7E
#define AD74416H_HART_ALERT_STATUS(x)		(0x80 + (x * 16))
#define AD74416H_HART_RX(x)			(0x81 + (x * 16))
#define AD74416H_HART_TX(x)			(0x82 + (x * 16))
#define AD74416H_HART_FCR(x)			(0x83 + (x * 16))
#define AD74416H_HART_MCR(x)			(0x84 + (x * 16))
#define AD74416H_HART_RFC(x)			(0x85 + (x * 16))
#define AD74416H_HART_TFC(x)			(0x86 + (x * 16))
#define AD74416H_HART_ALERT_MASK(x)		(0x87 + (x * 16))
#define AD74416H_HART_CONFIG(x)			(0x88 + (x * 16))
#define AD74416H_HART_TX_PREM(x)		(0x89 + (x * 16))
#define AD74416H_HART_EVDET(x)			(0x8A + (x * 16))
#define AD74416H_HART_TX_GAIN(x)		(0x8B + (x * 16))
#define AD74416H_HART_GPIO_IF_CONFIG		0xC0
#define AD74416H_HART_GPIO_MON_CONFIG(x)	(0xC1 + x)



#define AD74416H_FRAME_SIZE 			5
#define AD74416H_THRESHOLD_DAC_RANGE		98
#define AD74416H_THRESHOLD_RANGE		30000
#define AD74416H_DAC_RANGE			12000
#define AD74416H_DAC_CURRENT_RANGE		25000
#define AD74416H_DAC_RESOLUTION			16
#define AD74414H_DAC_RESOLUTION			14
#define AD74116H_CONV_TIME_US			1000000

/** Software reset sequence */
#define AD74416H_CMD_KEY_RESET_1                0x15FA
#define AD74416H_CMD_KEY_RESET_2                0xAF51


#define AD74416H_DATA_BYTE_OFFSET       3

#define AD74416H_OP_MODE    ( SPI_MODE_CPOL | SPI_WORD_SET(8) | SPI_TRANSFER_MSB | SPI_LINES_SINGLE | SPI_OP_MODE_MASTER) //setting SPI mode here either Mode 1 or Mode 2

//configuration data
struct ad74416h_config{
    struct spi_dt_spec spi;
    uint8_t dev_addr;
    struct gpio_dt_spec reset_gpio;

};

#endif //ZEPHYR_DRIVERS_aDI_AD74416H