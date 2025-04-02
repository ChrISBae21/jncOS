#include <stddef.h>
#include <stdint.h>
#include "uart.h"
#include "printf.h"
#include "util.h"
#include "irq.h"
#include "timer.h"
// #include <limits.h>

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
    /* cast to void types */
    (void)r0;
    (void)r1;
    (void)atags;
    // unsigned char c;

    // init_uart();
    // print_intro();
    // init_printf(0, putc);
    // int el = get_el();
	// printf("Exception level: %d \r\n", el);
    // irq_vector_init();
	// timer_init();
	// enable_interrupt_controller();
	// enable_irq();

    // // testPrint();

    // /* print input */
    // while (1) {
    //     c = uart_getc();
    //     if (c == '\r') {
    //         uart_putc('\n');
    //     }
    //     else if (c == 127) {
    //         uart_print("\b \b");
    //     }
    //     else {
    //         uart_putc(c);
    //     }
    // }

	init_uart();
	init_printf(0, putc);
	irq_vector_init();
	timer_init();
	enable_interrupt_controller();
	enable_irq();

	while (1){
		uart_putc(uart_getc());
	}	

}