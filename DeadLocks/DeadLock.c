/*
Autora: Nathália Maria Urenha Machado
Descrição: Esse programa realiza o tratamento de DeadLocks
*/
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

	int atendido;
	int numero_atendimento = 0;
	bool verifica_deadlock = false;
	int i;
	int j;
	int k;
	
	void tenta_atender_processos_nao_atendidos(int num_processo, int P, int R, int *RecursosDisponiveis, int *MatrizAlocacao, int *MatrizRequisicao, bool *verifica_atendido, int *ordem_atendimento) 
	{
		atendido = 0;
		for(j = 0; j < R; j++) {
			if(MatrizRequisicao[num_processo * R + j] <= RecursosDisponiveis[j]) 
			{
				printf("%d => %d\n", MatrizRequisicao[num_processo * R + j], RecursosDisponiveis[j]);
				atendido++;
			}
		}
	
		if(atendido == R) 
		{
			int z;
			for(z = 0; z < R; z++) {
				RecursosDisponiveis[z] = RecursosDisponiveis[z] + MatrizAlocacao[num_processo * R + z];
				MatrizAlocacao[num_processo * R + z] = 0;
			}
			
			// Verifica atendimento e armazena se o processo foi atendido com uma flag true ou false
			verifica_atendido[num_processo] = true;
			ordem_atendimento[numero_atendimento] = num_processo;
			numero_atendimento++;
			printf("Processo p%d atendido!\n", num_processo);
		}
	}


int main(void)
{
	int P = 0;
	int R = 0;
	int somatorio = 0;
	int contador = 0;

	
	printf("Digite o numero de processos: ");
	scanf("%d", &P);
	printf("\nDigite o numero de tipos de recursos: ");
	scanf("%d", &R);
	

	
	int RecursosExistentes[R];
	int RecursosDisponiveis[R];
	int MatrizAlocacao[P][R];
	int MatrizRequisicao[P][R];
	int vetSoma[R];
	int vetAux[R];
	
	for(i=0; i<R; i++)
	{
		printf("\nQuantas instancias o recurso %d possui?", i);
		scanf("%d", &RecursosExistentes[i]);
	}

	for(i=0; i<P; i++)
	{
		for(j=0; j<R; j++)
		{
			printf("\nQuantos recursos %d o processo %d necessita?",j, i);
			scanf ("%d", &MatrizAlocacao[ i ][ j ]);
		}
		
	}
	//////////////////ALOCAÇÕES///////////////////////
	printf("\nMatriz de Alocacao: \n");
	for(i=0; i<P; i++)
	{
		if (i != 0) printf("\n");
		for(j=0; j<R; j++)
		{
			printf ("\t%d", MatrizAlocacao[ i ][ j ]);
		}
	}
	
	for(j=0; j<R; j++)
	{
		for(i=0; i<P; i++)
		{
			somatorio = somatorio + MatrizAlocacao[i][j];
		}
		vetSoma[j] = somatorio;
		
		for(k=0; k<R; k++)
		{
			if(somatorio > RecursosExistentes[k])
			{
				printf("\nDEADLOCK!!\nOs processos nunca podem requisitar mais recursos que existentes no sistema!!!!");
				return(0);
			}
		}
		
		somatorio = 0;
	}
	
	printf("\nVetor de Recursos Disponiveis: ");
	for(k = 0; k<R; k++)
	{
		RecursosDisponiveis[k] = RecursosExistentes[k] - vetSoma[k];
		printf("%d ", RecursosDisponiveis[k]);	
	}	
	//////////////////REQUISIÇÕES///////////////////////
	for(i=0; i<P; i++)
	{
		for(j=0; j<R; j++)
		{
			printf("\nQuantos recursos %d o processo %d esta requisitando?",j, i);
			scanf ("%d", &MatrizRequisicao[ i ][ j ]);
		}
		
	}
		
	printf("\nMatriz de Requisicao: \n");
	for(i=0; i<P; i++)
	{
		if (i != 0) printf("\n");
		for(j=0; j<R; j++)
		{
			printf ("\t%d", MatrizRequisicao[ i ][ j ]);
		}
	}
		
	
	//////////////////DETECÇÃO DE DEADLOCKS///////////////////////
	bool verifica_atendido[P];
	int ordem_atendimento[P];
	
	for(i=0; i<P; i++)
	{
		verifica_atendido[i] = true;
	}

	for(i = 0; i < P; i++) 
	{
		atendido = 0;
		for(j = 0; j < R; j++) {
			if(MatrizRequisicao[i][j] <= RecursosDisponiveis[j]) {
				printf("\n%d => %d", MatrizRequisicao[i][j], RecursosDisponiveis[j]);
				atendido++;
			}
		}
		//se a condicao for verdadeira, significa que o processo pode ser atendido com os recursos requisitados
		if(atendido == R) 
		{
			for(k = 0; k < R; k++) 
			{
				RecursosDisponiveis[k] = RecursosDisponiveis[k] + MatrizAlocacao[i][k];
				MatrizAlocacao[i][k] = 0;
			}
			
			verifica_atendido[i] = true;
			ordem_atendimento[numero_atendimento] = i;
			numero_atendimento++;
			
			printf("\nProcesso p%d atendido!\n", i);
			//Verificar se um processo que não foi atendido pode ser atendido agora
			for(k = 0; k < P; k++) 
			{
				if(verifica_atendido[k] == false)
				{
					tenta_atender_processos_nao_atendidos(k, P, R, RecursosDisponiveis, MatrizAlocacao[0], MatrizRequisicao[0], verifica_atendido, ordem_atendimento);	
				}
								
			}

		}
		else 
		{
			verifica_atendido[i] = false;
		}
		
	}
	for(i = 0; i < P; i++)
		if(!verifica_atendido[i])
			verifica_deadlock = true;

	if(verifica_deadlock) { 
		printf("Houve deadlock com os processos: ");
		for(i = 0; i < P; i++)
			if(verifica_atendido[i] == false)
				printf("p%d ", i);
	}
	else {
		printf("Nao houve deadlock. Os processos podem ser atendidos na seguinte ordem:");
		for(i = 0; i < P; i++)
			printf("p%d, ", ordem_atendimento[i]);
	}
	
	getch();
	return(0);
}

