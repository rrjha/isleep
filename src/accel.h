#include <stdio.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "include/core.h"
#include "include/spi.h"

/* Some useful registers */
#define DEVID 0x0
#define POWER_CTL 0x2D	//Power Control Register
#define DATA_FORMAT 0x31
#define DATAX0 0x32	//X-Axis Data 0
#define DATAX1 0x33	//X-Axis Data 1
#define DATAY0 0x34	//Y-Axis Data 0
#define DATAY1 0x35	//Y-Axis Data 1
#define DATAZ0 0x36	//Z-Axis Data 0
#define DATAZ1 0x37	//Z-Axis Data

#define READ_MASK 0x80
#define MB_MASK 0x40
#define SB_WRITE_MASK 0x3F
#define DEVICEID 0xE5
#define RANGE_2G 0x00
#define RANGE_4G 0x01
#define RANGE_8G 0x02
#define RANGE_16G 0x03
#define FULL_RES 0x08
#define MEASURE 0x08

typedef struct accelrometer_data{
	int x;
	int  y;
	int  z;
}accel_data;

void accel_read(accel_data *dataPtr);
