    
    .macro	ventry	label
	.align	7
	b	\label
	.endm

    .macro handle_invalid_entry
	bl	invalid_vector_entry
	b	err_hang
	.endm


/*
 * Exception vector table.
 */
.align	11
.globl vectors 
vectors:
	ventry	sync_invalid_el1t			// Synchronous EL1t
	ventry	irq_invalid_el1t			// IRQ EL1t
	ventry	fiq_invalid_el1t			// FIQ EL1t
	ventry	error_invalid_el1t			// Error EL1t

	ventry	sync_invalid_el1h			// Synchronous EL1h
	ventry	el1_irq					// IRQ EL1h
	ventry	fiq_invalid_el1h			// FIQ EL1h
	ventry	error_invalid_el1h			// Error EL1h

	ventry	sync_invalid_el0_64			// Synchronous 64-bit EL0
	ventry	irq_invalid_el0_64			// IRQ 64-bit EL0
	ventry	fiq_invalid_el0_64			// FIQ 64-bit EL0
	ventry	error_invalid_el0_64			// Error 64-bit EL0

	ventry	sync_invalid_el0_32			// Synchronous 32-bit EL0
	ventry	irq_invalid_el0_32			// IRQ 32-bit EL0
	ventry	fiq_invalid_el0_32			// FIQ 32-bit EL0
	ventry	error_invalid_el0_32			// Error 32-bit EL0

sync_invalid_el1t:
	handle_invalid_entry

irq_invalid_el1t:
	handle_invalid_entry

fiq_invalid_el1t:
	handle_invalid_entry

error_invalid_el1t:
	handle_invalid_entry

sync_invalid_el1h:
	handle_invalid_entry

fiq_invalid_el1h:
	handle_invalid_entry

error_invalid_el1h:
	handle_invalid_entry

sync_invalid_el0_64:
	handle_invalid_entry

irq_invalid_el0_64:
	handle_invalid_entry

fiq_invalid_el0_64:
	handle_invalid_entry

error_invalid_el0_64:
	handle_invalid_entry

sync_invalid_el0_32:
	handle_invalid_entry

irq_invalid_el0_32:
	handle_invalid_entry

fiq_invalid_el0_32:
	handle_invalid_entry

error_invalid_el0_32:
	handle_invalid_entry

el1_irq: 
	bl	handle_irq

.globl err_hang
err_hang: b err_hang


.globl irq_vector_init
irq_vector_init:
	adr	x0, vectors		// load VBAR_EL1 with virtual
	msr	vbar_el1, x0		// vector table address
	ret

.globl enable_irq
enable_irq:
	msr    daifclr, #2 
	ret

.globl disable_irq
disable_irq:
	msr	daifset, #2
	ret

.global get_el
get_el: 
	mrs x0, CurrentEL
	lsr x0, x0, #2
	ret