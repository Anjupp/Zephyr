#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>
#include <stdio.h>

int main(void)
{
    const struct device *const ad744 = DEVICE_DT_GET(DT_ALIAS(my_ad74416h));
    int ret;

    if (ad744 == NULL) {
        printf ("AD74416H not found \n");
        return 0;
    }
    printf ("AD74416H is found\n");

    if (!device_is_ready(ad744)) {
        printf("Device %s is not ready\n", ad744->name);
        return 0;
    }

    // while(1){
        printf("inside while loop\n");
        // ret = ad74416h_reg_write(dev, AD74416H_SCRATCH(0), test_val);
        // if (ret)
            return ret;
    // }

    return 0;
}