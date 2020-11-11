/*
Autora: Nathália Maria Urenha Machado
Descrição: Esse programa calcula a sequência Fibonacci para o intervalo de números
		   de 37 até 46 utilizando Threads, e registra o tempo que foi gasto para executá-lo.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; // esses dados são compartilhados pela thread
void *runner(void *param); //thread 

int main()
{
	float tempo;
	time_t t_ini, t_fim;
	t_ini = time(NULL);	
	
	int i;
	
	pthread_attr_t attr; //Declarar uma variável de atributo pthread
	pthread_attr_init(&attr); // Inicializa a variável

	for(i=37; i<47; i++)
	{
		pthread_t thread; //pthread_t é o tipo de dados usado para identificar exclusivamente um encadeamento.
		pthread_create(&thread,&attr,runner,(void*)i);
		pthread_join(thread,NULL);	//suspende a execução da chamada segmento até o segmento de destino terminar
		
		printf("Fibonacci do numero %d: %d\n",i, sum);
	}
	
	t_fim = time(NULL);
	tempo = difftime(t_fim, t_ini);
	printf("\nTempo: %.f segundos", tempo);
}	

void *runner(void *param)
{
	sum = fibonacci((int*)param);
	pthread_exit(0); //A função pthread_exit () encerrará o thread de chamada
}

int fibonacci (int x)
{
    if(x==0)
	{
		return 0;
	}
	else if(x==1 || x==2)
	{
		return 1;
	}
    return fibonacci(x-1) + fibonacci(x-2);
}
