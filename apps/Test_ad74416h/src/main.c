#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

int main(void)
{

    const struct device *const dev = DEVICE_DT_GET_ONE(adi_ad74416h);

	if (!device_is_ready(dev)) {
		printk("device not ready.\n");
		return 0;
	}



	// const struct device *const mcp = DEVICE_DT_GET(DT_ALIAS(ad74416h-nod));
    // const struct device *const mcp = DEVICE_DT_GET(DT_ALIAS(ad74416h));
	// int ret;

    // // Check if the MCP9808 has been initialized (init function called)
	// if (!device_is_ready(mcp)) {
	// 	printf("Device %s is not ready.\n", mcp->name);
	// 	return 0;
	// }

    printf("init\r\n");

    // Loop
    // while (1) 
    // {
    //     struct sensor_value tmp;

    //     // Fetch the temperature value from the sensor into the device's data structure
    //     ret = sensor_sample_fetch(mcp);
    //     if (ret != 0) {
    //         printf("Sample fetch error: %d\n", ret);
    //         return 0;
    //     }

    //     // Copy the temperature value from the device's data structure into the tmp struct
    //     ret = sensor_channel_get(mcp, SENSOR_CHAN_AMBIENT_TEMP, &tmp);
    //     if (ret != 0) {
    //         printf("Channel get error: %d\n", ret);
    //         return 0;
    //     }

    //     // Print the temperature value
    //     printf("Temperature: %d.%06d\n", tmp.val1, tmp.val2);

    //     // Sleep for 1 second
    //     k_sleep(K_SECONDS(1));
    // }
    
    return 0;
}