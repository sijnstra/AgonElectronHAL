/*
 * Title:           Electron - HAL
 *                  a playful alternative to Quark
 *                  quarks and electrons combined are matter.
 * Author:          Mario Smit (S0urceror)
*/

// Hardware Abstraction Layer

#include "hal.h"

HardwareSerial host_serial(0);
fabgl::Terminal* fabgl_terminal=nullptr;

void hal_ez80_serial_init ()
{
	ez80_serial.end();
    ez80_serial.begin(UART_BR, SERIAL_8N1, UART_RX, UART_TX);
	ez80_serial.setPins(UART_RX, UART_TX, UART_CTS, UART_RTS);	// Must be called after begin
	ez80_serial.setHwFlowCtrlMode(HW_FLOWCTRL_CTS_RTS);			// Can be called whenever
}

void hal_hostpc_serial_init ()
{
	//host_serial.begin(115200, SERIAL_8N1, 3, 1);
	//host_serial.begin(460800, SERIAL_8N1, 3, 1);
	host_serial.begin(500000, SERIAL_8N1, 3, 1);
}
void hal_set_terminal (fabgl::Terminal* term)
{   
    fabgl_terminal = term;
}
char hal_hostpc_serial_read ()
{
	if (host_serial.available()) {
		return host_serial.read();
	}
	return 0;
}

void _hal_printf (uint8_t dest, const char* format, va_list ap) {
	char buf[255];
	vsnprintf(buf, sizeof(buf), format, ap);
	// print to host PC and/or fabgl terminal
	if (dest & 0b00000010)
		host_serial.print(buf);
	if (fabgl_terminal!=nullptr && (dest & 0b00000001))
		fabgl_terminal->write (buf);
}

// print both on the Terminal and the connecting Host via serial (if any)
void hal_printf (const char* format, ...) {
	va_list args;
	va_start(args,format);
	_hal_printf (0b11,format,args);
	va_end (args);
}

void hal_hostpc_printf (const char* format, ...) {
	va_list args;
	va_start(args,format);
	_hal_printf (0b10,format,args);
	va_end (args);
}

void hal_terminal_printf (const char* format, ...) {
	va_list args;
	va_start(args,format);
	_hal_printf (0b01,format,args);
	va_end (args);
}