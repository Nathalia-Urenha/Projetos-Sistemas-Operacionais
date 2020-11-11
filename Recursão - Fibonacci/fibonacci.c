/*
Autora: Nath�lia Maria Urenha Machado
Descri��o: Esse programa calcula a sequ�ncia Fibonacci para o intervalo de n�meros
		   de 37 at� 46 utilizando recurs�o, e registra o tempo que foi gasto para execut�-lo.
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
