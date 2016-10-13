#pragma once






void SPI_master_init();

void SPI_slave_init();



void send_master_SPI(char data);

char read_master_SPI();



void send_slave_SPI();

char read_slave_SPI();

void spi_chipselect_activate();
void spi_chipselect_deactivate();