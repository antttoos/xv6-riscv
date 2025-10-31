# Tarea 2 — Lottery Scheduler (xv6 RISC-V)
**Integrantes:** Bárbara Céspedes y Antonia Solís

---

## 1. Funcionamiento y lógica de la implementación

El **Lottery Scheduler** asigna a cada proceso una cantidad de *tickets*, los cuales representan su “porción de probabilidad” de ser elegido por el CPU.  
En cada ciclo del *scheduler*:

1. Se suman todos los *tickets* de los procesos en estado **RUNNABLE**.  
2. Se genera un número aleatorio entre `0` y `total_tickets - 1`.  
3. El proceso cuya suma acumulada de *tickets* sobrepase el número aleatorio es el **ganador** y obtiene el CPU.  
4. Cada vez que un proceso se ejecuta, su contador `cpu_slices` aumenta, permitiendo observar la proporción de CPU efectivamente recibida.

De esta forma, los procesos con más *tickets* tienen **mayor probabilidad estadística** de recibir más tiempo de CPU, aunque la planificación sigue siendo aleatoria y no determinista.

---

## 2. Modificaciones realizadas

### `kernel/proc.h`
Se agregaron dos nuevos campos a la estructura `proc` para soportar el algoritmo de planificación:
- `tickets`: almacena la cantidad de *tickets* asignados a cada proceso.
- `cpu_slices`: registra la cantidad de veces que el proceso ha sido ejecutado.

### `kernel/proc.c`
- En la función `allocproc()` se inicializaron los nuevos campos `tickets` y `cpu_slices` con valores por defecto, garantizando coherencia entre procesos creados.  
- En la función `scheduler()` se reemplazó la lógica **Round Robin** original por la implementación del algoritmo **Lottery Scheduling**, que selecciona aleatoriamente un proceso de acuerdo con la cantidad de *tickets* de cada uno.  
  - Se calcula el total de *tickets* de los procesos listos.  
  - Se elige un número aleatorio dentro del rango total.  
  - Se selecciona el proceso cuyo intervalo de *tickets* contiene el número ganador.  
  - Se ejecuta dicho proceso y se actualiza su contador `cpu_slices`.  
- Además, se añadió una función auxiliar `random_at_most(int max)` para la generación de números pseudoaleatorios.

### `kernel/syscall.h` y `kernel/syscall.c`
Se definió la nueva *system call* `settickets` asignándole un número de identificación y registrándola en la tabla de llamadas al sistema.

### `kernel/sysproc.c`
Se implementó la lógica de la *system call* `settickets`, permitiendo que un proceso establezca su cantidad de *tickets* a través de una llamada desde el espacio de usuario.

### `user/user.h` y `user/usys.pl`
Se incorporó la declaración de la función `settickets(int n)` para habilitar su uso desde programas de usuario.

---

## 3. Dificultades encontradas y soluciones implementadas

- **Inicialización incorrecta de tickets:**  
  Al comienzo, los procesos hijos heredaban valores de *tickets* inconsistentes.  
  **Solución:** Inicializar explícitamente `tickets = 1` en la función `allocproc()` para mantener coherencia en los procesos creados.

- **Generación de número aleatorio:**  
  `xv6` no incluye funciones de generación aleatoria.  
  **Solución:** Implementar una función auxiliar `random_at_most()` basada en un generador lineal congruencial, utilizando la expresión:  
  `randseed = randseed * 1103515245 + 12345;`

- **Desbalance de CPU entre procesos pequeños y grandes:**  
  Algunos procesos terminaban monopolizando CPU por acumulación de *tickets*.  
  **Solución:** Testear con distintos valores y establecer un límite mínimo de `≥ 1` *ticket* por proceso para garantizar una distribución equitativa.

- **Depuración del scheduler:**  
  Fue necesario insertar `printf` dentro de la función `scheduler()` para observar y verificar el comportamiento del reparto de CPU en distintas ejecuciones.

---

## 4. Posibles problemas del algoritmo Lottery Scheduling

- **Variabilidad estadística:**  
  En el corto plazo puede no reflejar la proporción esperada de asignación de CPU.

- **No determinista:**  
  Dificulta la depuración y la reproducción exacta de los resultados.

- **Overhead:**  
  El cálculo del total de *tickets* y la generación de números aleatorios introducen un costo mayor que el algoritmo **Round Robin**.

- **Injusticia temporal:**  
  Procesos con pocos *tickets* pueden experimentar largos tiempos de espera antes de ser seleccionados.

- **Sin prioridades estrictas:**  
  El algoritmo maneja probabilidades, no garantías, por lo que no es adecuado para sistemas de tiempo real estricto.

---

## 5. Conclusión

La implementación del **Lottery Scheduler** permitió comprender los fundamentos de un planificador **basado en probabilidades** y cómo modificar el comportamiento del kernel de **xv6**.  
El resultado es un sistema más flexible, donde la asignación de CPU depende de los *tickets* de cada proceso, reflejando un **balance dinámico entre equidad y aleatoriedad**.

