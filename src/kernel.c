// #include <stddef.h>
// #include <stdint.h>


// enum
// {
//     // The GPIO registers base address for BCM2835
//     GPIO_BASE = 0x3F200000,

//     GPFSEL0     = (GPIO_BASE + 0x00),
//     GPFSEL1     = (GPIO_BASE + 0x04),
//     GPFSEL2     = (GPIO_BASE + 0x08),
//     GPFSEL3     = (GPIO_BASE + 0x0C),
//     GPFSEL4     = (GPIO_BASE + 0x10),
//     GPFSEL5     = (GPIO_BASE + 0x14),
//     GPPUD       = (GPIO_BASE + 0x94),
//     GPPUDCLK0   = (GPIO_BASE + 0x98)
// };


// enum
// {
//     // The base address for UART for BCM2835
//     UART0_BASE = 0x3F201000,

//     UART0_DR     = (UART0_BASE + 0x00),
//     UART0_RSRECR = (UART0_BASE + 0x04),
//     UART0_FR     = (UART0_BASE + 0x18),
//     UART0_ILPR   = (UART0_BASE + 0x20),
//     UART0_IBRD   = (UART0_BASE + 0x24),
//     UART0_FBRD   = (UART0_BASE + 0x28),
//     UART0_LCRH   = (UART0_BASE + 0x2C),
//     UART0_CR     = (UART0_BASE + 0x30),
//     UART0_IFLS   = (UART0_BASE + 0x34),
//     UART0_IMSC   = (UART0_BASE + 0x38),
//     UART0_RIS    = (UART0_BASE + 0x3C),
//     UART0_MIS    = (UART0_BASE + 0x40),
//     UART0_ICR    = (UART0_BASE + 0x44),
//     UART0_DMACR  = (UART0_BASE + 0x48),
//     UART0_ITCR   = (UART0_BASE + 0x80),
//     UART0_ITIP   = (UART0_BASE + 0x84),
//     UART0_ITOP   = (UART0_BASE + 0x88),
//     UART0_TDR    = (UART0_BASE + 0x8C)
// };


// // Loop <delay> times in a way that the compiler won't optimize away
// static inline void delay(int32_t count) {
//     asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
//             : "=r"(count): [count]"0"(count) : "cc");
// }


// /* writes data to a register address in memory */
// static void write_reg(uint32_t reg, uint32_t data) {
//     *(volatile uint32_t*)reg = data;
// }

// static uint32_t read_reg(uint32_t reg) {
//     return *(volatile uint32_t*) reg;
// }

// /* UART uses GPIO pins 14 & 15 */
// void init_uart() {

//     write_reg(UART0_CR, 0x00000000);    /* disable UART */

//     write_reg(GPPUD, 0x00000000);      /* set PUD reg to what we want */
//     delay(150); 

//     write_reg(GPPUDCLK0, ((1 << 14)|   /* clock PUD14 */
//                            (1 << 15))   /* clock PUD15 */
//     );   
//     delay(150);

//     write_reg(GPPUD, 0x00000000);      /* clear PUD reg */
//     write_reg(GPPUDCLK0, 0x00000000);  /* clear PUD clock */

//     write_reg(GPFSEL1, ((1 << 14)|  /* alt func 0 pin 14 */
//                          (1 << 17))  /* alt func 0 pin 15*/
//     ); 

//     write_reg(UART0_ICR, 0x7FF);    /* clears pending interrupt */

//     write_reg(UART0_IBRD, 1);       /* integer portion of baudrate divisor */
//     write_reg(UART0_FBRD, 40);      /* decimal portion of baudrate divisor */

//     write_reg(UART0_LCRH, ((1 << 4)|        /* enable FIFOs */
//                            (0b11 << 5))     /* 8-bit words */
//     );

//     write_reg(UART0_CR, ((1 << 0)|   /* enable UART */ 
//                          (1 << 8)|   /* enable TXE */
//                          (1 << 9))   /* enable RXE */
//     );
    

// }


// void uart_putc(unsigned char c) {
//     while ( read_reg(UART0_FR) & (1 << 5) );    /* TXE fifo is full */
//     write_reg(UART0_DR, c);                     /* write character */
// }

// unsigned char uart_getc() {
//     while ( read_reg(UART0_FR) & (1 << 4) );    /* RXE fifo is empty */
//     return read_reg(UART0_DR);                  /* read character */
// }

// void uart_print(const char* str) {
//     for (size_t i = 0; str[i] != '\0'; i ++) {
//         uart_putc((unsigned char)str[i]);
//     }
// }


// void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
// {
//     (void) r0;
//     (void) r1;
//     (void) atags;

//     init_uart();
//     uart_print("Hello, kernel World!\r\n");

//     while (1) {
//         uart_putc(uart_getc());
//         uart_putc('\n');
//     }
// }

#include <stddef.h>
#include <stdint.h>

static inline void mmio_write(uint32_t reg, uint32_t data)
{
    *(volatile uint32_t*)reg = data;
}

static inline uint32_t mmio_read(uint32_t reg)
{
    return *(volatile uint32_t*)reg;
}

// Loop <delay> times in a way that the compiler won't optimize away
static inline void delay(int32_t count)
{
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
            : "=r"(count): [count]"0"(count) : "cc");
}

enum
{
    // The GPIO registers base address.
    GPIO_BASE = 0x3F200000, // for raspi2 & 3, 0x20200000 for raspi1

    GPPUD = (GPIO_BASE + 0x94),
    GPPUDCLK0 = (GPIO_BASE + 0x98),

    // The base address for UART.
    UART0_BASE = 0x3F201000, // for raspi2 & 3, 0x20201000 for raspi1

    UART0_DR     = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR     = (UART0_BASE + 0x18),
    UART0_ILPR   = (UART0_BASE + 0x20),
    UART0_IBRD   = (UART0_BASE + 0x24),
    UART0_FBRD   = (UART0_BASE + 0x28),
    UART0_LCRH   = (UART0_BASE + 0x2C),
    UART0_CR     = (UART0_BASE + 0x30),
    UART0_IFLS   = (UART0_BASE + 0x34),
    UART0_IMSC   = (UART0_BASE + 0x38),
    UART0_RIS    = (UART0_BASE + 0x3C),
    UART0_MIS    = (UART0_BASE + 0x40),
    UART0_ICR    = (UART0_BASE + 0x44),
    UART0_DMACR  = (UART0_BASE + 0x48),
    UART0_ITCR   = (UART0_BASE + 0x80),
    UART0_ITIP   = (UART0_BASE + 0x84),
    UART0_ITOP   = (UART0_BASE + 0x88),
    UART0_TDR    = (UART0_BASE + 0x8C),
};

void uart_init()
{
    mmio_write(UART0_CR, 0x00000000);

    mmio_write(GPPUD, 0x00000000);
    delay(150);

    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);

    mmio_write(GPPUDCLK0, 0x00000000);

    mmio_write(UART0_ICR, 0x7FF);

    mmio_write(UART0_IBRD, 1);
    mmio_write(UART0_FBRD, 40);

    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));

    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));

    mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void uart_putc(unsigned char c)
{
    while ( mmio_read(UART0_FR) & (1 << 5) ) { }
    mmio_write(UART0_DR, c);
}

unsigned char uart_getc()
{
    while ( mmio_read(UART0_FR) & (1 << 4) ) { }
    return mmio_read(UART0_DR);
}

void uart_puts(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; i ++)
        uart_putc((unsigned char)str[i]);
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    (void) r0;
    (void) r1;
    (void) atags;

    uart_init();
    uart_puts("Hello, kernel World!\r\n");

    while (1) {
        uart_putc(uart_getc());
        uart_putc('\n');
    }
}