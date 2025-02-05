.section ".text.boot"   /* boots OS in text-mode */

.globl _start
_start:
	mrs	x0, mpidr_el1		/* Make single-core */
	and	x0, x0,#0xFF		/* Check processor id for primary core */
	cbz	x0, master		    /* Continue if primary core */
	b	proc_hang           /* Is not primary core */

/* Hangs on error */
proc_hang: 
	b 	proc_hang

/* Clears memory 8-bytes at a time, while value of x1 > 0 */
memzero:
	str xzr, [x0], #8   /* Clear value at x0, then increment x0 by 8 */
	subs x1, x1, #8     /* Subtracts counter by 8 */
	b.gt memzero        /* Branch if the subtraction results in > 0 */
	ret                 /* Done clearing memory */

master:
	adr	x0, __bss_start     /* Load the start addr */
	adr	x1, __bss_end       /* Load the end addr */
	sub	x1, x1, x0          /* Subtract to get length of the bss */
	bl 	memzero             /* branch */

	mov	sp, 0x80000     /* Address of Low of Stack */
	bl	kernel_main     /* Branch to the Kernel main function */
	b 	proc_hang		/* Could not branch to kernel_main */


