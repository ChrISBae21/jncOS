#include <stdint.h>
#include <stddef.h>
#include "utility.h"

/* writes data to a register address in memory */
void write_reg(uint32_t reg, uint32_t data)
{
    *(volatile uint32_t *)(uintptr_t)reg = data;
}

/* reads data from a register address in memory */
uint32_t read_reg(uint32_t reg)
{
    return *(volatile uint32_t *)(uintptr_t)reg;
}