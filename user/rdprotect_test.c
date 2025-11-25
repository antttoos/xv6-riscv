#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void) {
    char *addr = sbrk(0);      // start of heap
    if (sbrk(PGSIZE) < 0) {
        printf("sbrk fallo\n");
        exit(1);
    }

    addr[0] = 'Z';             // write OK

    if (mrdprotect(addr, 1) < 0) {
        printf("mrdprotect fallo\n");
        exit(1);
    }

    // write should still work
    addr[0] = 'A';

    int pid = fork();
    if (pid == 0) {
        // hijo intenta leer -> debe morir por page fault si proteccion funcionó
        volatile char c = addr[0];
        // si llega aquí, lectura NO fue protegida
        printf("LECTURA_OK: %c\n", c);
        exit(1);
    } else {
        int status;
        wait(&status);
        // En xv6, si el hijo fue 'killed' por fault, el status puede variar.
        // Nosotros sólo informamos:
        printf("Hijo terminó con status: %d\n", status);
    }

    if (munrdprotect(addr, 1) < 0) {
        printf("munrdprotect fallo\n");
        exit(1);
    }

    // ahora leer debería ser posible: comprobación rápida
    char rr = addr[0];
    printf("Lectura tras munrdprotect: %c\n", rr);

    printf("rdprotect_test finalizado\n");
    exit(0);
}
