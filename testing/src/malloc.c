#include <stdint.h>

extern uint8_t __heap_start;
extern uint8_t __heap_end;

static uint8_t *heap_ptr = &__heap_start;

void *static_malloc(uint64_t size) {
    /* Align to 16 bytes */
    heap_ptr = (uint8_t *)(((uintptr_t)heap_ptr + 15) & ~((uintptr_t)15));
    
    uint8_t *result = heap_ptr;
    heap_ptr += size;

    if (heap_ptr >= &__heap_end) {
        return 0;
    }

    return result;
}
