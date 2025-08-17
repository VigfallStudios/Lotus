#include <stdint.h>
#include "device.h"

volatile uint8_t *uart = (uint8_t *)UART_BASE_ADDR;

void earlyputc(char c)
{
#ifdef BOOT_DEBUG
    *uart = c;
#endif
}

void earlyprintk(const char *s)
{
#ifdef BOOT_DEBUG
    while(*s != '\0') {
        earlyputc(*s);
        s++;
    }
#endif
}

void *memset(void *ptr, int value, uint64_t num) {
    unsigned char *p = (unsigned char *)ptr;
    for (uint64_t i = 0; i < num; i++) {
        p[i] = (unsigned char)value;
    }
    return ptr;
}

int strcmp(const char *s1, const char *s2) {
    while (*s1 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return (unsigned char)*s1 - (unsigned char)*s2;
}

static uint32_t be32(uint32_t x) { return __builtin_bswap32(x); }

void putc(char c)
{
	 *uart = c;
}

void printk(const char *str)
{
	while(*str != '\0') {
        putc(*str);
        str++;
    }
}

static void print_nibble(unsigned int v) {
    char c = (v < 10) ? ('0' + v) : ('a' + (v - 10));
    earlyputc(c);
}

void print_hex64(uint64_t v) {
    earlyprintk("0x");
    for (int i = 15; i >= 0; --i) {
        unsigned int nibble = (v >> (i * 4)) & 0xF;
        print_nibble(nibble);
    }
}

static void print_reg_name(int idx) {
    char buf[6];
    int n = 0;
    buf[n++] = 'x';
    if (idx >= 10) {
        buf[n++] = '0' + (idx / 10);
        buf[n++] = '0' + (idx % 10);
    } else {
        buf[n++] = '0' + idx;
    }
    buf[n++] = ':';
    buf[n++] = ' ';
    buf[n] = '\0';
    earlyprintk(buf);
}

void dump_regs(uint64_t *regs, const char *msg) {
    earlyprintk("\npanic(cpu 0 caller): ");
    if (msg) {
        earlyprintk(msg);
        earlyputc('\n');
    }
    else {
    	earlyprintk("unknown\n");
    }

    // print x0..x30
    for (int i = 0; i <= 30; ++i) {
        print_reg_name(i);
        earlyprintk("     ");
        print_hex64(regs[i]); // regs array holds the saved values
        earlyprintk("  ");
        if ((i + 1) % 4 == 0) {
			earlyputc('\n');
		}
    }

    // original SP value was stored at byte offset 248 -> index 31
    earlyprintk("sp: ");
    print_hex64(regs[31]);

    earlyprintk("\npanic: We are hanging here...\n");
}

extern void panic_asm(const char *msg);

void panic(const char *msg) {
    panic_asm(msg);
}

void kmain()
{
    earlyprintk("[earlyboot] Booting Lotus on CPU 0\n[earlyboot] Lotus Version v0.01.1-lotus (no-smp)\n");
    earlyprintk("[earlyboot] Machine model: ");
    earlyprintk(DEVICE_MODEL_STR);
    earlyprintk("\n");

    printk("Lotus\n...\n");

	while(1);
}
