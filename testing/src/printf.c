#include "printf.h"
#include "strings.h"
#include "uart.h"


/* fmt is the literal string passed in */
int printk(const char *fmt, ...) {
    va_list args;   /* must declare  object va_list */
    va_start(args, fmt);    /* grab the arguments */
    int print_count = 0;

    for(int i = 0; fmt[i]; i++) {
        if(fmt[i] == '%') {
            i++;
            switch(fmt[i]) {
                case 'd':   /* int */
                    print_count += print_int((int)va_arg(args, int));
                    break;

                case 'u':   /* unsigned int */
                    print_count += print_uint((unsigned int)va_arg(args, unsigned int));
                    break;

                case 'x':   /* int hex */
                    print_count += print_hex((unsigned int)va_arg(args, unsigned int), sizeof(unsigned int));
                    break;
                
                case 'c':   /* char */
                    print_char(va_arg(args, int));
                    print_count++;
                    break;
                
                case 'p':   /* pointer */
                    print_count += print_pointer(va_arg(args, void*));
                    break;

                case 'h':   /* short */
                    i++;
                    switch(fmt[i]) {
                        case 'd':   /* signed short */
                            print_count += print_int((short)va_arg(args, int));
                            break;
                        case 'u':   /* unsigned short */
                            print_count += print_uint((unsigned short)va_arg(args, unsigned int));
                            break;
                        case 'x':   /* short hex */
                            print_count += print_hex((unsigned short)va_arg(args, unsigned int), sizeof(unsigned int));
                            break;
                    }
                    break;
                
                case 'l':   /* long */
                    i++;
                    switch(fmt[i]) {
                        case 'd':   /* signed long */
                            print_count += print_int((long)va_arg(args, long));
                            break;
                        case 'u':   /* unsigned long */
                            print_count += print_uint((unsigned long)va_arg(args, unsigned long));
                            break;
                        case 'x':   /* long hex */
                            print_count += print_hex((unsigned long)va_arg(args, unsigned long), sizeof(unsigned long));  
                            break;
                    }
                    break;

                case 'q': /* long long */
                    i++;
                    switch(fmt[i]) {
                        case 'd':   /* signed long long */
                            print_count += print_int((long long)va_arg(args, long long));
                            break;
                        case 'u':   /* unsigned long long */
                            print_count += print_uint((unsigned long long)va_arg(args, unsigned long long));
                            break;
                        case 'x':   /* long long hex */
                            print_count += print_hex((unsigned long long)va_arg(args, unsigned long long), sizeof(unsigned long long));
                            break;
                    }
                    break;
                case 's':
                    print_count += print_str(va_arg(args, char*));
                    break;
                
                /* %% */
                default:
                    print_char('%');
                    print_count++;
                    break;
            }
        }
        else {
            print_char(fmt[i]);
            print_count++;
        }
    }

    va_end(args);
    return print_count;

}

/* used for short (h), int (d), long (l), and long long (q) datatypes */
int print_int(long long n) {
    int count = 0;
    if(n < 0) {
        uart_putc('-');
        n *= -1;
        count += 1;
    }
    return count + print_uint(n);
}

/* used for unsigned short (hu), unsigned int (u), unsigned long (lu), and unsigned long long (qu) datatypes */
int print_uint(unsigned long long n) {
    int count = 0;
    /* print each digit */
    while(n >= 10) {
        uart_putc('0' + (n % 10));
        count++;
        n/=10;
    }

    /* if only one's place left */
    if(n < 10) {
        uart_putc('0' + (n % 10));
        count++;
    }
    return count;

}


/* difference between unsigned and signed char? */
void print_uchar(unsigned char c) {
    uart_putc(c);
}

void print_char(char c) {
    uart_putc((unsigned char)c);
}


int print_str(const char *s) {
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        uart_putc((unsigned char)s[i]);
    }
    return i;

}


int print_hex(unsigned long long n, int data_size) {
    if(n == 0) {
        uart_putc('0');
        return 1;
    }
    int count = 0;
    int val;
    int flag = 0;

    for(int i = (data_size * 8) - 4; i >= 0; i-=4) {
        val = (n >> i) & 0xF;
        if(val || flag) {
            if(val < 10) {
                uart_putc('0' + val);
            }
            else {
                uart_putc('a' + (val - 10));
            }
            count++;
            flag = 1;
        }

    }
    return count;
}



int print_pointer(void* ptr) {
    int count = 2;

    uart_putc('0');
    uart_putc('x');

    return count + print_hex((unsigned long long)ptr, sizeof(ptr));
    

}