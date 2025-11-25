# Tarea 3 — Protección de Lectura en XV6 (Solo Escritura)
**Integrantes:** Bárbara Céspedes y Antonia Solís
## 1. Objetivo
El objetivo de esta tarea fue implementar las llamadas al sistema `mrdprotect` y `munrdprotect` para permitir la creación de regiones de memoria de "Solo Escritura". [cite_start]Esto es útil para proteger secretos (como claves criptográficas) de ser leídos incluso por el propio proceso, permitiendo solo su modificación[cite: 6].

## 2. Implementación Detallada

### Archivos Modificados
* **kernel/syscall.h & syscall.c:** Se definieron los números de syscall `SYS_mrdprotect` (25) y `SYS_munrdprotect` (26) y se vincularon a sus funciones en el kernel.
* **user/user.h & usys.pl:** Se expusieron las firmas de las funciones para los programas de usuario y se generaron los stubs de ensamblador.
* **kernel/vm.c:** Se implementó la lógica principal en la función `uvm_rdprotect`. Esta función recorre la tabla de páginas (Page Table) y manipula el bit `PTE_R` (Read).
* **kernel/sysproc.c:** Se crearon los manejadores `sys_mrdprotect` y `sys_munrdprotect` para recibir los argumentos desde el espacio de usuario.

### Desafíos y Soluciones
Durante la implementación, nos encontramos con que la versión local de XV6 utiliza funciones `argaddr` y `argint` con retorno `void`.
* **Error:** `void value not ignored as it ought to be`.
* **Solución:** Se modificó la implementación en `sysproc.c` para llamar a estas funciones sin comprobar un valor de retorno, adaptándose a la API específica de esta distribución de XV6.

## 3. Validación y Comportamiento del Hardware (Análisis de scause 0xf)

Para validar la tarea, se creó el programa de prueba `rdprotect_test.c`, el cual:
1.  Protege una página con `mrdprotect` (quitando el permiso de lectura).
2.  Intenta escribir en ella (debería funcionar según la teoría de "Solo Escritura").
3.  Intenta leer de ella (debería fallar).

### Resultado Obtenido
Al ejecutar el test, el sistema arroja inmediatamente una excepción al intentar **escribir** arrojando el error que se aprecia en la evidencia_t3
* `scause 0xf` (15) corresponde a un **Store Page Fault** (Fallo de Página en Escritura).

### Justificación Técnica
Aunque el código eliminó correctamente el bit `PTE_R`, la arquitectura **RISC-V** impone una restricción de hardware: **una página marcada como escribible (W=1) debe ser legible (R=1)**. La combinación "Solo Escritura" (W=1, R=0) es considerada una configuración reservada/inválida por la MMU.

**Conclusión:**
El hecho de que se genere una excepción (`scause 0xf`) al intentar escribir confirma que **la llamada al sistema funcionó y modificó los bits de la página**, ya que una página normal (RW) no generaría este error. La implementación es correcta según lo solicitado, topándose con una limitación de seguridad de la arquitectura del procesador simulado (QEMU).
