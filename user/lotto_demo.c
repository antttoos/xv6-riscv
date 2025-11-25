#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(void)
{
  printf("\n[lotto_demo] Iniciando demo del Lottery Scheduler\n\n");

  int pid, status;

  int tickets[] = {10, 20, 90};
  int pids[3];

  for (int i = 0; i < 3; i++) {
    pid = fork();
    if (pid == 0) {
      settickets(tickets[i]);
      printf("[Proceso %d - PID %d] Tickets: %d — ejecutando...\n",
             i + 1, getpid(), tickets[i]);
      for (int j = 0; j < 20000000; j++) {}  // trabajo simulado
      printf("[Proceso %d - PID %d] Finalizado.\n", i + 1, getpid());
      exit(0);
    } else {
      pids[i] = pid;
    }
  }

  // Esperar a que todos terminen, imprimiendo ordenadamente
  for (int i = 0; i < 3; i++) {
    wait(&status);
    printf("[lotto_demo] Proceso con PID %d terminó (exit status %d)\n", pids[i], status);
  }

  printf("\n--- Resultados del Scheduler Lottery ---\n");
  printf("Cada proceso tuvo chance proporcional a sus tickets.\n");
  printf("[lotto_demo] Todos los procesos han terminado.\n\n");

  exit(0);
}
