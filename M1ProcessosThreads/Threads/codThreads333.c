#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#define NUMTHREADS 2	// Define numero fixo de threads
#define VETSIZE 5000	// Define tamanho do vetor

typedef struct {
	int fromidx, length;
}thread_arg, *ptr_thread_arg;

pthread_t threads[NUMTHREADS];
thread_arg arguments[NUMTHREADS];
// É passado o valor definido anteriormente de quantidade
// de threads para o codigo.

int nums[VETSIZE];
int sum;


// Declara função que será utilizada depois
void *thread_func(void *arg);

int main(int argc, char **argv){
	int i, length, remainder;
	sum = 0; 
	length = VETSIZE / NUMTHREADS;

	// Defino alguns valores para melhor
	// exemplificar o codigo.
	nums[10] = 1;
	nums[1567] = 20;
	nums[3000] = 300;
	nums[4500] = 4000;


	// A variavel "remainder" recebe uma possivel sobra
	// da divisão feita para a variavel "lenght"
	remainder = VETSIZE % NUMTHREADS;

	// Laco de repeticao que rodara pelo numero 
	// de threads utilizadas.
	for(i=0; i<NUMTHREADS; i++) {

		// É definido o inicio do vetor 
		arguments[i].fromidx = i * length;

		// É definido o tamanho do vetor
		arguments[i].length = length;

		// Caso for a ultima thread(vetor) recebera o resto
		if(i == (NUMTHREADS - 1)){
			arguments[i].length += remainder;
		}
		// Função para criar manualmente a thread.
		pthread_create(&(threads[i]), NULL, thread_func, &(arguments[i]));
	}
	// Laco de repeticao para executar o pthread_join
	for(i=0; i<NUMTHREADS; i++) pthread_join(threads[i], NULL);
	printf("A soma dos numeros do vetor eh %d \n ", sum);
}


	// Funcao onde é recebido os valores do argumentos
	// e onde é feita a soma para ser apresentada ao usuario.
void *thread_func(void *arg) {
	ptr_thread_arg argument = (ptr_thread_arg)arg;
	int i, localsum = 0, endidx;
	
	endidx = argument->fromidx + argument->length;
	
	for(i=argument->fromidx; i<endidx; i++){
		localsum += nums[i];
	}
	sum += localsum;
}