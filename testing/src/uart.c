#include "uart.h"
#include "util.h"

/* UART uses GPIO pins 14 & 15 */
void init_uart() {

    put32(UART0_CR, 0x00000000); /* disable UART */

    put32(GPPUD, 0x00000000); /* set PUD reg to what we want */
    delay(150);

    put32(GPPUDCLK0, 
               ((1 << 14) | /* clock PUD14 */
                (1 << 15))  /* clock PUD15 */
    );
    delay(150);

    put32(GPPUD, 0x00000000);     /* clear PUD reg */
    put32(GPPUDCLK0, 0x00000000); /* clear PUD clock */

    put32(GPFSEL1, 
               ((1 << 14) | /* alt func 0 pin 14 */
                (1 << 17))  /* alt func 0 pin 15*/
    );

    put32(UART0_ICR, 0x7FF); /* clears pending interrupt */

    put32(UART0_IBRD, 26); /* integer portion of baudrate divisor */
    put32(UART0_FBRD, 2);  /* decimal portion of baudrate divisor */

    put32(UART0_LCRH, 
               ((1 << 4) |   /* enable FIFOs */
                (0b11 << 5)) /* 8-bit words */
    );

    put32(UART0_CR, 
               ((1 << 0) | /* enable UART */
                (1 << 8) | /* enable TXE */
                (1 << 9))  /* enable RXE */
    );
}

/* puts a character to the TXE buffer */
void uart_putc(unsigned char c) {
    while (get32(UART0_FR) & (1 << 5));    /* TXE fifo is full */
    put32(UART0_DR, c);                   /* write character */
}

/* gets a character from the RXE buffer*/
unsigned char uart_getc() {
    while (get32(UART0_FR) & (1 << 4));    /* RXE fifo is empty */
    return get32(UART0_DR);                /* read character */
}

/* prints a string */
void uart_print(const char *str) {
    for (int i = 0; str[i] != '\0'; i++) {
        uart_putc((unsigned char)str[i]);
    }
}

void putc(void* p, char c) {
    uart_putc(c);
}

void print_intro() {
    uart_print("\x1B[2J");
    uart_print("\x1B[H");
    uart_print("   __     __   __     ______        ______     ______    \n");
    uart_print("  /\\ \\   /\\ \"-.\\ \\   /\\  ___\\      /\\  __ \\   /\\  ___\\   \n");
    uart_print(" _\\_\\ \\  \\ \\ \\-.  \\  \\ \\ \\____     \\ \\ \\/\\ \\  \\ \\___  \\  \n");
    uart_print("/\\_____\\  \\ \\_\\ \"\\_\\  \\ \\_____\\     \\ \\_____\\  \\/\\_____\\ \n");
    uart_print("\\/_____/   \\/_/ \\/_/   \\/_____/      \\/_____/   \\/_____/ \n");
    uart_print("\r\nHello, World!\r\n");
}