#ifndef __UTILITY_H__
#define __UTILITY_H__

#include <stdint.h>
#include <stddef.h>

/* Delays for (count) cycles */
static inline void delay(int32_t count)
{
    asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
                 : "=r"(count) : [count] "0"(count) : "cc");
}

void write_reg(uint32_t reg, uint32_t data);
uint32_t read_reg(uint32_t reg);

#endif