#include <stdarg.h>

int printk(const char *fmt, ...);
int print_int(long long n);
int print_uint(unsigned long long n);
void print_uchar(unsigned char c);
void print_char(char c);
int print_str(const char *s);
int print_hex(unsigned long long n);
int print_pointer(void* ptr);
void testPrint();

#define HEX_CHAR(val) ((val < 10) ? ('0' + val) : ('a' + val - 10))
