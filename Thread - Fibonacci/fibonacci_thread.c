/*
Autora: Nath�lia Maria Urenha Machado
Descri��o: Esse programa calcula a sequ�ncia Fibonacci para o intervalo de n�meros
		   de 37 at� 46 utilizando Threads, e registra o tempo que foi gasto para execut�-lo.
*/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int sum; // esses dados s�o compartilhados pela thread
void *runner(void *param); //thread 

int main()
{
	float tempo;
	time_t t_ini, t_fim;
	t_ini = time(NULL);	
	
	int i;
	
	pthread_attr_t attr; //Declarar uma vari�vel de atributo pthread
	pthread_attr_init(&attr); // Inicializa a vari�vel

	for(i=37; i<47; i++)
	{
		pthread_t thread; //pthread_t � o tipo de dados usado para identificar exclusivamente um encadeamento.
		pthread_create(&thread,&attr,runner,(void*)i);
		pthread_join(thread,NULL);	//suspende a execu��o da chamada segmento at� o segmento de destino terminar
		
		printf("Fibonacci do numero %d: %d\n",i, sum);
	}
	
	t_fim = time(NULL);
	tempo = difftime(t_fim, t_ini);
	printf("\nTempo: %.f segundos", tempo);
}	

void *runner(void *param)
{
	sum = fibonacci((int*)param);
	pthread_exit(0); //A fun��o pthread_exit () encerrar� o thread de chamada
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
