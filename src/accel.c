/*
 * spi.c
 *
 *  Created on: May 31, 2015
 *      Author: gijs
 */

#include "spi_example.h"

typedef struct {

int x;
	
int  y;
	
int  z;
}accel_data;

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

/*
 * ADXL345 is a Digital Accelerometer. It can measure movement on 3 axes.
 * This example will probe the axis 20 times every second.
 */
int spiADXL345Example() {
	setup();

	printf("WORK IN PROGRESS\n");
	unsigned char adxl345_setup[] = {};
	unsigned char receive[6];
	signed short data[3];

	spi_properties *spi = malloc(sizeof(spi_properties));
	spi->spi_id = spi0;
	spi->bits_per_word = 8;
	spi->mode = 3;
	spi->speed = 2000000;
	spi->flags = O_RDWR;

	uint8_t isOpen = spi_open(spi);

	if (isOpen == 0) {
		adxl345_setup[0] = 0x31;
		adxl345_setup[1] = 0x08;
		spi_send(spi, adxl345_setup, 2);
		adxl345_setup[0] = 0x2D;
		adxl345_setup[1] = 0x08;
		spi_send(spi, adxl345_setup, 2);
		while(1) {
			adxl345_setup[0] = adxl345_setup[0] = 0x80|0x40|0x32;
			adxl345_setup[1] = 0x00;
			spi_transfer(spi, adxl345_setup, receive, 6);
			data[0] = receive[1]<<8 | receive[0]; // combine MSB and LSB
			data[1] = receive[3]<<8 | receive[2];
			data[2] = receive[5]<<8 | receive[4];
			printf("x = %i \ty = %i\t z = %i\n", data[0], data[1], data[2]);
			data[0] = 0;
			data[1] = 0;
			data[2] = 0;
			usleep(1000000);
		}
	}
	return 0;
}

void dprint(unsigned char value) {
	syslog(LOG_INFO, "0x%02x", value);
}

/*int main(int argc, char **argv) {
	
	spiADXL345Example();
	
	
}*/
