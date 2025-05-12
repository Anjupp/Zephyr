# Custome zephyr function that imports the ad74416h/ subdirectory if the Kconfig 
# option AD74416H is defined. 
add_subdirectory_ifdef(CONFIG_AD74416H ad74416h)