#ifndef SIMULATION_H
#define SIMULATION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 
#include  "simulation.c"

extern int disk_semaphore;

extern int cpu_exec_time;
extern int disk_exec_time;

extern int *exec;
extern int exec_size;
extern int disk_instruction;


//Realiza o up no semaforo referente ao disco
void up_disk_semaphore();

//Realiza o dow no semaforo referente ao disco
void down_disk_semaphore();

//Função que simula o funcionamento do disco
void *diskFunct(void *aux);

//Função que simula o funcionamento da cpu
void *cpuFunct(void *aux);

//Função que simula o funcionamento de IO
void *ioFunct(void *aux);

#endif //SIMULATION_H