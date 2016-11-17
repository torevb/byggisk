#pragma once




void MCP2515_init();

char read_MCP2515(char read_address);

void write_MCP2515(char write_address, char write_data);

void request_to_send_MCP2515(char RTS_in);

char read_status_MCP2515();

void bit_modify_MCP2515(char address, char mask_byte, char data);

void reset_MCP2515();






