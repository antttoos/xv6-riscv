# INFORME – Tarea 0: Instalación y Ejecución de xv6

## 1. Entorno
- SO / Distro: Windows 11 + WSL2 (Ubuntu 24.04)
- Versiones:
  - QEMU: (salida de `qemu-system-riscv64 --version`)
  - Toolchain: (salida de `riscv64-unknown-elf-gcc --version`)
  - git: (salida de `git --version`)

## 2. Pasos seguidos
1) Instalé WSL2 y Ubuntu desde Microsoft Store.
2) Instalé dependencias (`build-essential`, `qemu-system-misc`, `gcc-riscv64-unknown-elf`, etc.).
3) Hice fork del repo `xv6-riscv` en mi GitHub y lo cloné.
4) Compilé con `make clean && make`.
5) Ejecuté xv6 con `make qemu`.
6) Dentro de xv6 probé: `ls`, `echo Hola xv6`, `cat README`.
7) Captura guardada como `evidencia_xv6.png`.

## 3. Problemas y soluciones
- `exec echo failed`: se resolvió ejecutando `echo Hola xv6` sin comillas o `/echo Hola xv6`.
- Instalación de WSL requirió reinicio y configuración inicial.

## 4. Confirmación
- xv6 arrancó en QEMU y respondió correctamente a los comandos solicitados (ver captura).

## 5. Enlace a la rama
- (se completa después del push)




# INFORME – Tarea 1: Nuevas Llamadas al Sistema en xv6

## 1. Funcionamiento
- **getppid()**: retorna el PID del proceso padre del proceso llamante.  
- **getancestor(n)**: retorna el PID del ancestro `n`:
  - `getancestor(0)` → PID propio.
  - `getancestor(1)` → PID del padre.
  - `getancestor(2)` → PID del abuelo.
  - Si no existe ese ancestro → retorna `-1`.

## 2. Archivos modificados
- `kernel/syscall.h`: se agregaron las constantes `SYS_getppid` y `SYS_getancestor`.
- `kernel/syscall.c`: se declararon `extern uint64 sys_getppid(void);` y `extern uint64 sys_getancestor(void);`, y se mapearon en la tabla de syscalls.
- `kernel/sysproc.c`: se implementaron las funciones `sys_getppid()` y `sys_getancestor()`.
- `user/usys.pl`: se agregaron las entradas `entry("getppid");` y `entry("getancestor");`.
- `user/user.h`: se agregaron los prototipos `int getppid(void);` y `int getancestor(int n);`.
- `user/yosoytupadre.c`: se creó el programa de prueba.
- `Makefile`: se agregó `$U/_yosoytupadre` a `UPROGS`.

## 3. Dificultades encontradas y soluciones
- **Error con `argint`**: en esta versión de xv6, `argint` es `void` y no retorna valor. Se resolvió inicializando la variable y llamando `argint(0, &n);` sin comparación.
- **Errores de compilación por comentarios mal puestos en `syscall.c`**: se corrigió eliminando una línea sobrante en los comentarios de `fetchstr`.
- **Función duplicada en `sys_getancestor`**: se corrigió dejando solo una implementación.
- **`exec failed` al correr el binario**: se resolvió agregando correctamente `$U/_yosoytupadre` en el `Makefile`.

## 4. Pruebas

En xv6 se compiló y ejecutó el programa `yosoytupadre`:

$ yosoytupadre
Mi PID: 4
PID de mi padre: 2
getancestor(0): 4
getancestor(1): 2
getancestor(2): 1
getancestor(10): -1


### Interpretación
- `getppid()` devolvió correctamente el PID del padre (2).
- `getancestor(0)` devolvió el PID del proceso actual (4).
- `getancestor(1)` devolvió el PID del padre (2).
- `getancestor(2)` devolvió el PID del abuelo (1).
- `getancestor(10)` devolvió -1 al no existir ese ancestro.

La ejecución confirma que las nuevas llamadas al sistema funcionan según lo requerido.
