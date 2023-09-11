#ifndef __HAL_H_
#define __HAL_H_

#include "Arduino.h"
#include "HardwareSerial.h"
#include "fabgl.h"

#define ez80_serial Serial2

#define UART_BR         1152000
#define UART_NA         -1
#define UART_TX         2
#define UART_RX         34
#define UART_RTS        13 // The ESP32 RTS pin
#define UART_CTS        14 // The ESP32 CTS pin
#define UART_RX_THRESH	64 // Point at which RTS is toggled

#define GPIO_ITRP       17 // VSync Interrupt Pin - for reference only

extern HardwareSerial hal_serial;

void hal_printf (const char* format, ...);
void hal_hostpc_printf (const char* format, ...);
void hal_terminal_printf (const char* format, ...);
void hal_hostpc_serial_init ();
void hal_set_terminal (fabgl::Terminal*);
char hal_hostpc_serial_read ();
void hal_ez80_serial_init ();

#define	HAL_major		0
#define	HAL_minor		1
#define	HAL_revision 	0


#endif