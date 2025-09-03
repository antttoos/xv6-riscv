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
