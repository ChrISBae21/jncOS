#include <stddef.h>
#include <stdint.h>
#include "uart.h"
#include "printf.h"
#include "util.h"
#include "timer.h"
#include "malloc.h"

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags) {
    /* cast to void types */

    (void)r0;
    (void)r1;
    (void)atags;
    unsigned char c;

    init_uart();
    print_intro();
    init_printf(0, putc);
    timer_init();

    int el = get_el();
	printf("Exception level: %d \r\n", el);


    void* ptr = static_malloc(4096);
    printf("Malloc ptr: 0x%x\n", (uint64_t)ptr);
    ptr = static_malloc(4096);
    printf("Malloc ptr: 0x%x\n", (uint64_t)ptr);
    ptr = static_malloc(4096);
    printf("Malloc ptr: 0x%x\n", (uint64_t)ptr);
    /* print input */
    while (1) {
        // while(!(get32(TIMER_CS) & TIMER_CS_M1));
        // handle_timer_irq();
    }
}