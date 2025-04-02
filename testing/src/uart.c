#include <stddef.h>
#include <stdint.h>
#include "uart.h"
#include "utility.h"

/* UART uses GPIO pins 14 & 15 */
void init_uart()
{

    write_reg(UART0_CR, 0x00000000); /* disable UART */

    write_reg(GPPUD, 0x00000000); /* set PUD reg to what we want */
    delay(150);

    write_reg(GPPUDCLK0, ((1 << 14) | /* clock PUD14 */
                          (1 << 15))  /* clock PUD15 */
    );
    delay(150);

    write_reg(GPPUD, 0x00000000);     /* clear PUD reg */
    write_reg(GPPUDCLK0, 0x00000000); /* clear PUD clock */

    write_reg(GPFSEL1, ((1 << 14) | /* alt func 0 pin 14 */
                        (1 << 17))  /* alt func 0 pin 15*/
    );

    write_reg(UART0_ICR, 0x7FF); /* clears pending interrupt */

    write_reg(UART0_IBRD, 26); /* integer portion of baudrate divisor */
    write_reg(UART0_FBRD, 2);  /* decimal portion of baudrate divisor */

    write_reg(UART0_LCRH, ((1 << 4) |   /* enable FIFOs */
                           (0b11 << 5)) /* 8-bit words */
    );

    write_reg(UART0_CR, ((1 << 0) | /* enable UART */
                         (1 << 8) | /* enable TXE */
                         (1 << 9))  /* enable RXE */
    );
}

/* puts a character to the TXE buffer */
void uart_putc(void *p, char c)
{
    while (read_reg(UART0_FR) & (1 << 5))
        ;                   /* TXE fifo is full */
    write_reg(UART0_DR, c); /* write character */
}

/* gets a character from the RXE buffer*/
unsigned char uart_getc()
{
    while (read_reg(UART0_FR) & (1 << 4))
        ;                      /* RXE fifo is empty */
    return read_reg(UART0_DR); /* read character */
}

/* prints a string */
void uart_print(const char *str)
{
    for (size_t i = 0; str[i] != '\0'; i++)
    {
        uart_putc(NULL, (unsigned char)str[i]);
    }
}

void print_intro()
{
    uart_print("\x1B[2J");
    uart_print("\x1B[H");
    uart_print("   __     __   __     ______        ______     ______    \n");
    uart_print("  /\\ \\   /\\ \"-.\\ \\   /\\  ___\\      /\\  __ \\   /\\  ___\\   \n");
    uart_print(" _\\_\\ \\  \\ \\ \\-.  \\  \\ \\ \\____     \\ \\ \\/\\ \\  \\ \\___  \\  \n");
    uart_print("/\\_____\\  \\ \\_\\ \"\\_\\  \\ \\_____\\     \\ \\_____\\  \\/\\_____\\ \n");
    uart_print("\\/_____/   \\/_/ \\/_/   \\/_____/      \\/_____/   \\/_____/ \n");
    uart_print("\r\nHello, World!\r\n");
}

void invalid_vector_entry()
{
    uart_print("Invalid Vector Interrupt\r\n");
}