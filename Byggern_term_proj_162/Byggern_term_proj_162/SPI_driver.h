#pragma once


void SPI_init();

void send_SPI(char data);

char read_SPI();

void spi_chipselect_activate();
void spi_chipselect_deactivate();