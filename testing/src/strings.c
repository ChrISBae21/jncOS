#include "strings.h"

void *memset(void *dst, int c, size_t n) {
    unsigned char *tmp = (unsigned char*)dst;
    for(int i = 0; i < n; i++) {
        *tmp++ = (unsigned char)c;
    }
    return dst;
}
void *memcpy(void *dest, const void *src, size_t n) {
    unsigned char *to = (unsigned char*)dest;
    unsigned char *from = (unsigned char*)src;
    
    for(int i = 0; i < n; i++) {
        *to++ = *from++;
    }
    return dest;
}
size_t strlen(const char *s) {
    size_t len = 0;
    while(*s != '\0') {
        s++;
        len++;
    }
    return len;
}
char *strcpy(char *dest, const char *src) {

    char *original = dest;
    while(*src != '\0') {
        *dest++ = *src++;
    }

    /* null terminator */
    *dest++ = *src++;
    return original;

}
int strcmp(const char *s1, const char *s2) {
    
    while( (*s1 != '\0' || *s2 != '\0') && (*s1 == *s2) ) {
        s1++;
        s2++;
    }
    return (int)(*(const unsigned char*)s1 - *(const unsigned char*)s2);

}
const char *strchr(const char *s, int c) {

    while (*s != '\0') {
        if (*s == (char)c) {
          return s;
        }
        s++;
    }

    if ((char)c == '\0') {
        return s;
    }
    return NULL;

}

/* needs to use malloc? */
char *strdup(const char *s) {
    return NULL;

}
