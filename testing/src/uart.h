#ifndef __UART_H__
#define __UART_H__

#include <stddef.h>
#include <stdint.h>
#include "utility.h"

enum
{
    // The GPIO registers base address for BCM2700
    // GPIO_BASE = 0x3F200000,
    GPIO_BASE = 0xFE200000, // BCM2711

    GPFSEL0 = (GPIO_BASE + 0x00),
    GPFSEL1 = (GPIO_BASE + 0x04),
    GPFSEL2 = (GPIO_BASE + 0x08),
    GPFSEL3 = (GPIO_BASE + 0x0C),
    GPFSEL4 = (GPIO_BASE + 0x10),
    GPFSEL5 = (GPIO_BASE + 0x14),
    GPPUD = (GPIO_BASE + 0x94),
    GPPUDCLK0 = (GPIO_BASE + 0x98)
};

enum
{
    // The base address for UART for BCM2700
    // UART0_BASE = 0x3F201000,
    UART0_BASE = 0xFE201000, // BCM2711

    UART0_DR = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR = (UART0_BASE + 0x18),
    UART0_ILPR = (UART0_BASE + 0x20),
    UART0_IBRD = (UART0_BASE + 0x24),
    UART0_FBRD = (UART0_BASE + 0x28),
    UART0_LCRH = (UART0_BASE + 0x2C),
    UART0_CR = (UART0_BASE + 0x30),
    UART0_IFLS = (UART0_BASE + 0x34),
    UART0_IMSC = (UART0_BASE + 0x38),
    UART0_RIS = (UART0_BASE + 0x3C),
    UART0_MIS = (UART0_BASE + 0x40),
    UART0_ICR = (UART0_BASE + 0x44),
    UART0_DMACR = (UART0_BASE + 0x48),
    UART0_ITCR = (UART0_BASE + 0x80),
    UART0_ITIP = (UART0_BASE + 0x84),
    UART0_ITOP = (UART0_BASE + 0x88),
    UART0_TDR = (UART0_BASE + 0x8C)
};

/* UART uses GPIO pins 14 & 15 */
void init_uart();

/* puts a character to the TXE buffer */
void uart_putc(void *p, char c);

/* gets a character from the RXE buffer*/
unsigned char uart_getc();

/* prints a string */
void uart_print(const char *str);

/* prints JNC intro */
void print_intro();

/* print invalid vector table entry */
void invalid_vector_entry();

#endif