#include  "simulation.h"

int disk_semaphore = 1;

int cpu_exec_time = 1;
int disk_exec_time = 10;

int *exec;
int exec_size = 0;
int disk_instruction = 3;

//Realiza o up no semaforo referente ao disco
void up_disk_semaphore(){
	while(1){
		//Quando o semaforo estiver disponível, decrementa seu valor
		if(disk_semaphore == 0){
			disk_semaphore++;
			break;
		}
	}
}

//Realiza o dow no semaforo referente ao disco
void down_disk_semaphore(){
	//Incrementa o semaforo
	disk_semaphore--;
}

//Função que simula o funcionamento do disco
void *diskFunct(void *aux){

	down_disk_semaphore();

	//Informa inicio da execução da thread
	printf("DISK - Starting DISK thread\n");

	while(1){
		//Espera o semaforo indicar uma requisição
		while(disk_semaphore == 0);

		//Imprime informando inicio da leitura do disco
		printf("\nDisk - Starting Disk Communication\n");
		//Aguarda 10s, afim de simular lentidão da execução da memória secundaria
		sleep(disk_exec_time);
		//Imprime informando fim da leitura do disco
		printf("\nDisk - Ending Disk Communication\n");

		down_disk_semaphore();
	}

	return NULL;
}

//Função que simula o funcionamento da cpu
void *cpuFunct(void *aux){

	//Informa inicio da execução da thread
	printf("CPU - Starting CPU thread\n");
	int PC = 0, read;

	while(1){
		sleep(cpu_exec_time);

		//Percorre lista de instruções
		read = exec[PC++ % exec_size];

		//Imprime informando qual instrução está sendo executada
		printf("\nCPU - Executing (%d)\n", read);

		//Caso a instrução de número 3 seja lida, será lido um valor do disco
		if(read == disk_instruction)
			up_disk_semaphore();
	}

	return NULL;
}

//Função que simula o funcionamento de IO
void *ioFunct(void *aux){

	//Informa inicio da execução da thread
	printf("IO - Starting IO thread\n");

	while(1){
		//Quando ler um \n do entrada padrão 'stdin', imprime indicando input do usuário
		if(getchar_unlocked() == '\n'){
			printf("IO - %s - User input\n", (char *)aux);
		}
	}

	return NULL;
}
