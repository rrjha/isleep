#! /bin/bash

# install iio overlay
echo cape-bone-iio > /sys/devices/bone_capemgr.*/slots

#install spi-0 overlay
cp overlays/*.dtbo /lib/firmware/
echo BB-SPI0-01 > /sys/devices/bone_capemgr.*/slots
