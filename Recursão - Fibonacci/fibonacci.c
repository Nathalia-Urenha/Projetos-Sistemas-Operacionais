/*
Autora: Nathália Maria Urenha Machado
Descrição: Esse programa calcula a sequência Fibonacci para o intervalo de números
		   de 37 até 46 utilizando recursão, e registra o tempo que foi gasto para executá-lo.
*/

#include<stdio.h>
#include<math.h>
#include<time.h>

double fibonacci(double n)
{
	if(n==0)
	{
		return 0;
	}
	else if(n==1 || n==2)
	{
		return 1;
	}

	return fibonacci (n-1) + fibonacci(n-2);
	
}
main()
{
	float tempo;
	time_t t_ini, t_fim;
	t_ini = time(NULL);	
	
	int i;
	for(i=37; i<47;i++)
	{
		printf("Fibonacci do numero %d: %.lf\n", i, fibonacci(i));
	}
	
	t_fim = time(NULL);
	tempo = difftime(t_fim, t_ini);
	printf("\n\nTempo: %.f segundos", tempo);
}
