#include <stddef.h>
#include <stdint.h>
#include "uart.h"
#include "kernel.h"
#include "irq.h"
#include "printf.h"

const unsigned int timer1_int = 3 * CLOCKHZ;
unsigned int timer1_val = 0;
void timer_init()
{
    timer1_val = REGS_TIMER->counter_lo;
    timer1_val += timer1_int;
    REGS_TIMER->compare[1] = timer1_val;
}

void handle_timer_1()
{
    timer1_val += timer1_int;
    REGS_TIMER->compare[1] = timer1_val;
    REGS_TIMER->control_status |= SYS_TIMER_IRQ_1;

    printf("timer triggered\n");
}

static inline uint64_t read_vbar_el1(void)
{
    uint64_t val;
    asm volatile("mrs %0, VBAR_EL1" : "=r"(val));
    return val;
}

static inline uint64_t get_label_address()
{
    uint64_t addr;
    asm volatile("adr %0, vectors" : "=r"(addr));
    return addr;
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
    (void)r0;
    (void)r1;
    (void)atags;
    unsigned char c;

    init_uart();
    print_intro();
    init_printf(NULL, uart_putc);
    irq_vector_init();
    timer_init();
    enable_interrupt_controller();
    enable_irq();

    printf("%d\n", REGS_TIMER->control_status);
    uint64_t vector_addr = get_label_address();

    uint64_t vbar = read_vbar_el1();
    // printf("%d, %d\n", vbar, vector_addr);

    printf("%d\n", REGS_IRQ->irq0_enable_0);

    int el = get_el();
    printf("exception level: %d\n", el);

    /* print input */
    while (1)
    {

        printf("%d\n", REGS_TIMER->control_status);
        //  c = uart_getc();
        //  if (c == '\r')
        //  {
        //      uart_putc(NULL, '\n');
        //  }
        //  else if (c == 127)
        //  {
        //      uart_print("\b \b");
        //  }
        //  else
        //  {
        //      uart_putc(NULL, c);
        //  }
    }
}