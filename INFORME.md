Tarea 2 — Lottery Scheduler (xv6 RISC-V)- Bárbara Céspedes y Antonia Solís 

1. Objetivo
Implementar un planificador de procesos basado en Lottery Scheduling en el sistema operativo xv6-riscv.
Cada proceso posee una cantidad de tickets que determinan la probabilidad de ser elegido por el CPU en cada turno.

2. Cambios realizados en el kernel:

Archivos modificados

- kernel/proc.h:
Se agregaron dos campos a la estructura proc:

int tickets;     // Cantidad de tickets asignados al proceso
int cpu_slices;  // Cantidad de veces que ha sido ejecutado


- kernel/proc.c:

  * Inicialización de tickets y cpu_slices en allocproc().

  * Modificación de scheduler() para implementar la selección aleatoria ponderada según los tickets.

  * Ajustes de consistencia en la estructura proc.

- kernel/syscall.h y kernel/syscall.c:
Se agregó el número y la entrada para la nueva syscall:
#define SYS_settickets 24
- kernel/sysproc.c:
Implementación de la syscall:
uint64 sys_settickets(void) {
    int n;
    argint(0, &n);
    struct proc *p = myproc();
    if (n < 1) n = 1;
    p->tickets = n;
    return 0;
}

- user/user.h y user/usys.pl:
Declaración y generación de la syscall settickets() para el espacio de usuario.

- Makefile:
Se agregó el nuevo programa de usuario lotto_demo a la variable UPROGS.

3. Nuevo programa: lotto_demo

Este programa crea tres procesos hijos con distintas cantidades de tickets:

  * Proceso 1 → 10 tickets

  * Proceso 2 → 20 tickets

  * Proceso 3 → 90 tickets

Cada proceso realiza una carga de trabajo simulada (bucle) y finaliza. 

4. Evidencia de ejecución 
Archivo adjunto: evidencia_t2.png 
La salida puede aparecer desordenada (caracteres superpuestos) debido a que los procesos imprimen concurrentemente en la consola del kernel.
Esto confirma el correcto funcionamiento del scheduler con múltiples procesos ejecutándose en paralelo.

5. Conclusión 
Se logró implementar correctamente el Lottery Scheduler, integrando una nueva syscall (settickets) y modificando el planificador.
La ejecución concurrente de múltiples procesos demuestra la aleatoriedad proporcional al número de tickets asignados.
El sistema compila, ejecuta y muestra resultados coherentes con la política de planificación propuesta.


