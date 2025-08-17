#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <UART_BASE_ADDR_HEX> <DEVICE_MODEL_STRING> <BOOT_DEBUG 0|1>\n", argv[0]);
        return 1;
    }

    const char *uart_addr_str = argv[1];
    const char *device_model = argv[2];
    const char *boot_debug_str = argv[3];

    int boot_debug = atoi(boot_debug_str);
    if (boot_debug != 0 && boot_debug != 1) {
        printf("BOOT_DEBUG must be 0 or 1.\n");
        return 1;
    }

    FILE *f = fopen("device.h", "w");
    if (!f) {
        perror("fopen");
        return 1;
    }

    fprintf(f, "#ifndef DEVICE_H\n");
    fprintf(f, "#define DEVICE_H\n\n");
    fprintf(f, "#include <stdint.h>\n\n");
    fprintf(f, "#define UART_BASE_ADDR %s\n", uart_addr_str);
    fprintf(f, "#define DEVICE_MODEL_STR \"%s\"\n", device_model);
    fprintf(f, "#define BOOT_DEBUG %d\n\n", boot_debug);
    fprintf(f, "#endif\n");

    fclose(f);

    printf("device.h generated successfully with BOOT_DEBUG=%d.\n", boot_debug);

    return 0;
}
