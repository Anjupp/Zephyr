// Ties to the compatible= "adi,adt74416h" node in the devicetree
#define DT_DRV_COMPAT adi_ad74416h

#include <errno.h>
#include <zephyr/drivers/spi.h>
#include <zephyr/sys/byteorder.h>
#include <zephyr/logging/log.h>

#include "ad74416h.h"

#include <zephyr/sys/util_macro.h> 
#include <zephyr/sys/util.h>
#include <zephyr/sys/crc.h>

//Enable logging at a given level
LOG_MODULE_REGISTER(AD74416H, CONFIG_SENSOR_LOG_LEVEL);


#define AD74416H_CRC_POLYNOMIAL     0x7
#define AD74416H_DIN_DEBOUNCE_LEN   BIT(5)
#define AD77416H_DEV_ADDRESS_MSK    GENMASK(5, 4)

/********************************declaration*****************************/
static int ad74416h_init(const struct device *dev);
static int ad74416h_reg_access1(const struct device *dev, uint8_t cmd,
                  uint8_t reg_addr, void *data, size_t length);
static int ad74416h_reg_access(const struct device *dev, uint8_t cmd,
                  uint8_t reg_addr, void *data, size_t length);
static int ad74416h_reg_read(const struct device *dev, uint8_t *read_buf,
                  uint8_t register_address, uint8_t count);
static int ad74416h_reg_read1(const struct device *dev, uint8_t *read_buf,
                  uint8_t register_address, uint8_t count);






/********************************Functions*****************************/

static int ad74416h_reg_access1(const struct device *dev, uint8_t cmd,
                  uint8_t reg_addr, void *data, size_t length)
{
    const struct ad74416h_config *cfg = dev->config;
    uint8_t access[5] = { cmd,0x00,0x00 , reg_addr, 0x00  };
    const struct spi_buf buf[2] = {{.buf = access,.len = 5},{.buf = data, .len = length}};

    // struct spi_buf_set tx = {
    //     .buffers = buf,
    // };
    // if (cmd == ADXL362_READ_REG) {
    struct spi_buf_set rx = {
    .buffers = buf,
    .count = 1
    };
    // tx.count = 0;
    spi_read_dt(&cfg->spi, &rx);
    // spi_transceive_dt(&cfg->spi, &tx, &rx);
    printf ("Read RX");
    return 0;
    // }
    // tx.count = 2;
    // return spi_write_dt(&cfg->bus, &tx);
}

static int ad74416h_reg_access(const struct device *dev, uint8_t cmd,
                  uint8_t reg_addr, void *data, size_t length)
{
    const struct ad74416h_config *cfg = dev->config;
    uint8_t access[5] = { cmd,0x6e,0x00 , reg_addr, 0x48  };
    const struct spi_buf buf[2] = {{.buf = access, .len = 5},{.buf = data,.len = length}};
    // const struct spi_buf buf[2];
    // buf[0] = {.buf = access, .len = 5};
    // buf[1]= {.buf = data,.len = length}};

    struct spi_buf_set tx = {
        .buffers = buf,
    };
    // if (cmd == ADXL362_READ_REG) {
    //  const struct spi_buf_set rx = {
    //      .buffers = buf,
    //      .count = 2
    //  };
    //  tx.count = 1;
    //  return spi_transceive_dt(&cfg->bus, &tx, &rx);
    // }
    tx.count = 1;
    return spi_write_dt(&cfg->spi, &tx);
}

// static inline int ad74416h_reg_read(const struct device *dev, uint8_t *read_buf,
//                   uint8_t register_address, uint8_t count)
// {
//     return ad74416h_reg_access(dev, 0x00,
//                   register_address, read_buf, count);
// }
// static inline int ad74416h_reg_read1(const struct device *dev, uint8_t *read_buf,
//                   uint8_t register_address, uint8_t count)
// {
//     return ad74416h_reg_access1(dev, 0x00,
//                   register_address, read_buf, count);
// }


static int ad74416h_reg_read(const struct device *dev, uint8_t *read_buf,
                  uint8_t register_address, uint8_t count)
{
    return ad74416h_reg_access(dev, 0x00,
                  register_address, read_buf, count);
}
static int ad74416h_reg_read1(const struct device *dev, uint8_t *read_buf,
                  uint8_t register_address, uint8_t count)
{
    return ad74416h_reg_access1(dev, 0x00,
                  register_address, read_buf, count);
}




//Initialize the ad74416h
static int ad74416h_init(const struct device *dev)
{
    const struct ad74416h_config *cfg = dev->config;
    int ret = 0;
    uint8_t val;
    //print to console
    // LOG_DBG("Initializing");
    // check the bus us ready 
    if (!device_is_ready(cfg->spi.bus)){
        // LOG_ERR("Bus device is not ready");
        return -ENODEV;
    }
    //Scratch test
    // while(1){
    // ad74416h_scratch_test(dev);
    ret = ad74416h_reg_read(dev, &val,AD74416H_WTD_CONFIG,5);
    k_busy_wait(100);
    // ad74416h_reg_read1(dev, &val,0x00,5);
    // k_busy_wait(1000);
    // }

    return ret;
}


// Expansion macro to define the driver instances
#define AD74416H_DEFINE(inst)                                                                                   \
                                                                                                                \
    /*  Create an instance of the config struct and populate with DT value*/                                    \
    static const struct ad74416h_config ad74416h_config_##inst = {                                              \
        .spi = SPI_DT_SPEC_INST_GET(inst, AD74416H_OP_MODE, 0),                                                 \
        .dev_addr = DT_INST_PROP(inst, dev_addr),                                                               \
    };                                                                                                          \
                                                                                                                \
    /*create device instances from the devicetree*/                                                             \
    DEVICE_DT_INST_DEFINE(inst,                                                                                 \
                        ad74416h_init,                                                                          \
                        NULL,                                                                                   \
                        NULL,                                                                                   \
                        &ad74416h_config_##inst,                                                                \
                        POST_KERNEL,                                                                            \
                        CONFIG_SPI_INIT_PRIORITY,                                                               \
			            NULL);                                                                                  \

DT_INST_FOREACH_STATUS_OKAY(AD74416H_DEFINE)

