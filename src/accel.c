#include "accel.h"

int accel_ready = 0;
spi_properties *accel_spi;

void dprint(unsigned char value) {
	syslog(LOG_INFO, "0x%02x", value);
}

int setup() {
	init_bbc_lib();
	overlay *ol = malloc(sizeof(overlay));
	ol->file_name = "BBCLIB-SPI0";
	ol->board_name = "BBCLib";
	ol->manufacturer = "BBCLIB";
	ol->part_number = "BBCLIB-SPI0";
	ol->version = "00A0";
	load_device_tree_overlay(ol);
	printf("loaded device tree");
	return 1;
}

void accel_read(accel_data *dataPtr) {
	short data[3];
	spiADXL345_read(data);
	dataPtr->x = data[0];
	dataPtr->y = data[1];
	dataPtr->z = data[2];
}

void accel_init() {
	setup();

	unsigned char adxl345_setup[2];

	accel_spi = malloc(sizeof(spi_properties));
	accel_spi->spi_id = spi0;
	accel_spi->bits_per_word = 8;
	accel_spi->mode = 3; //cpol, cpha
	accel_spi->speed = 2000000;
	accel_spi->flags = O_RDWR;

	uint8_t isOpen = spi_open(accel_spi);

	if (isOpen == 0) {
		adxl345_setup[0] = DATA_FORMAT;
		adxl345_setup[1] = FULL_RES;
		spi_send(accel_spi, adxl345_setup, 2);
		adxl345_setup[0] = POWER_CTL;
		adxl345_setup[1] = MEASURE;
		spi_send(accel_spi, adxl345_setup, 2);
		accel_ready = 1;
	}
}

/*
 * ADXL345 is a Digital Accelerometer. It can measure movement on 3 axes.
 * This example will probe the axis 20 times every second.
 */
int spiADXL345_read(short data[]) {
	unsigned char adxl345_setup[2];
	unsigned char receive[6];

	if(accel_ready) {
			adxl345_setup[0] = adxl345_setup[0] = READ_MASK|MB_MASK|DATAX0;
			adxl345_setup[1] = 0x00;
			spi_transfer(accel_spi, adxl345_setup, receive, 6);
			data[0] = receive[1]<<8 | receive[0]; // combine MSB and LSB
			data[1] = receive[3]<<8 | receive[2];
			data[2] = receive[5]<<8 | receive[4];
			return 0;
	}
	return -1;
}
