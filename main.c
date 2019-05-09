#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>
#include "simulation.h"

//Trata um ctrl+c, para liberar a memória corretamente
void INThandler(int sig){
	signal(sig,SIG_IGN);
	if(exec){
		free(exec);
	}
	printf("\nEncerrando execução\n");
	exit(0);
}

int main(int argc, char const *argv[]){

	//Handler de um sinal de interrupção
	signal(SIGINT, INThandler);

	//Verifica se foram passados parâmetros ao iniciar a execução do programa
	//Caso não, a lista de execução será inicializada com valores padrão
	if(argc > 3){

		cpu_exec_time = atoi(argv[1]);
		disk_exec_time = atoi(argv[2]);

		if(disk_exec_time < cpu_exec_time){
			printf("O tempo de execução da cpu deve ser menos que do disco\n");
			return 1;
		}

		disk_instruction = atoi(argv[3]);

		exec = malloc(sizeof(int) * argc-4);
		exec_size = argc-4;

		for (int i = 4; i < argc; ++i){
			exec[i-4] = atoi(argv[i]);
		}

	}
	else{
		exec = malloc(sizeof(int) * 11);
		exec_size = 11;

		exec[0] = 1;
		exec[1] = 4;
		exec[2] = 9;
		exec[3] = 3;
		exec[4] = 2;
		exec[5] = 14;
		exec[6] = 2;
		exec[7] = 1;
		exec[8] = 3;
		exec[9] = 7;
		exec[10] = 7;

	}

	pthread_t thread_disk;
	pthread_t thread_cpu;
	pthread_t thread_mem;

	char *k = "Keyboard\0";

	//Inicializa threads
	pthread_create(&thread_mem,NULL,diskFunct,NULL);
	pthread_create(&thread_cpu,NULL,cpuFunct,NULL);
	pthread_create(&thread_disk,NULL,ioFunct,(void *)k);

	//Espera as threads acabarem
	pthread_join(thread_disk, NULL);
	pthread_join(thread_cpu, NULL);
	pthread_join(thread_mem, NULL);
	
	return 0;
}