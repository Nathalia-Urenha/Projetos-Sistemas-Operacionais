/*
Autora: Nath�lia Maria Urenha Machado
Descri��o: Esse programa realiza chamadas de sistemas
*/


#include <stdio.h>
#include <time.h>
#include <fcntl.h> 
#include <errno.h> 
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <iostream>

void DataHora() // SystemCall da data e hora do sistema
{
	time_t hora_e_data;
	struct tm * dados;
	
	time( &hora_e_data );
	
	dados = localtime (&hora_e_data); // LocalTime registra a data e a hora atuais
	
	printf("Data e hora locais: %s\n", asctime(dados));
}

//////////////////////////////////////////////////////////////////////////////////////////////
void Abrir_Internet()
{
	HANDLE hProcess;
	HANDLE hThread;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwProcessId = 0;
	DWORD dwThreadId = 0;
	
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	BOOL bCreateProcess = NULL;
	bCreateProcess = CreateProcess("C:\\Program Files\\Internet Explorer\\iexplore.exe", NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);//System Call que cria um processo

	//Primeiro parametro � o diret�rio com o nome do arquivo que dever� ser criado o processo
	
	//Segundo parametro � a linha de comando ser executada
	//Terceiro parametro � um ponteiro referentes aos processos que aponta para a seguran�a de atributos
	//Quarto Parametro � um ponteiro referente as threads que aponta para a seguran�a dos atributos
	//Quinto Parametro � um parametro referente a hereditariedade dos indices
	//Sexto Parametro  s�o as Flags que controlam as classes priorit�rias e de cria��o de processos
	//S�timo Parametro Ponteiro que aponta para o ambiente
	//Oitavo parametro mostra o caminho completo para o diret�rio do processo 
	//Nono Parametro Ponteiro para STARTUPINFO ou STARTUPINFOEX
	//D�cimo Parametro Ponteiro para PROCCESS_INFORMATION estrutura que recebe identifica��o e informa��o sobre o novo processo
	if(bCreateProcess == FALSE)
	{
		printf("Erro!!\n",GetLastError());
	}	
	
	WaitForSingleObject(pi.hProcess, INFINITE);
	
	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess); 
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void criar_Arquivo(char diretorio[200]) // Fun��o da System call que cria um arquivo em um diret�rio especificado pelo usu�rio.
{
	HANDLE hfile;
	hfile = CreateFile(diretorio, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	//Parametros: 
	//diret�rio = Diret�rio que o arquivo ser� criado, com seu nome e extens�o, (EX: C:\\arquivo.png)
	//Generic_Read e Generic_Write: Acesso requerido do arquivo, (Ler, escrever, os dois ou nenhum)
	//File_Share_Read: Permite que outras opera��es abram o arquivo
	//NULL: este parametro � o da seguran�a, para realizar os testes foi deixado NULL
	//Create_New: Cria um novo arquivo apenas se n�o tiver outro com o mesmo nome, caso possua outro arquivo igual, a fun��o da erro
	//File_Attribute_Normal: O arquivo n�o possui nenhum outro atributo "setado"
	//NULL: Este parametro fornece atributos estendidos para o arquivo que est� sendo criado
 	if(hfile == INVALID_HANDLE_VALUE)
 	{
 		printf("Erro!!\n");
	}	
	CloseHandle(hfile); //System Call que fecha o Arquivo.
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void qtd_Nucleos() //SYSTEM_INFO: System call que obtem informa��es sobre o sistema do comutador;
{
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	int numCPU = sysinfo.dwNumberOfProcessors; //Number of Processors: Quantidade de nucleos que o computador possui.
	
	printf("Seu processador possui %d Nucleos\n\n", numCPU);	
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void criar_Diretorio (char lugar[100])
{
	BOOL dir;
	dir = CreateDirectory(lugar, NULL); //System Call que cria o Diret�rio: o primeiro parametro � o lugar e o nome que o diretorio ser� criado
										
	if(dir == FALSE)
	{
		printf("Erro!!\n");
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void apagar_Diretorio(char diretorio[100])
{
	BOOL dir;
	dir = RemoveDirectory(diretorio);//System Call que remove diret�rio: � passado o local e o nome do diretorio que se deseja apagar
	
	if(dir == FALSE)
	{
		printf("Erro !!\n");
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void copiar_Arquivo(char diretorio[100], char nome[100])
{
	BOOL arquivo;
	
	arquivo = CopyFile(diretorio,nome, TRUE); //SystemCall para copiar arquivo: O primeiro parametro � o nome do arquivo com seu diretorio
	                                        // O segundo � o nome do novo arquivo e seu diret�rio 
											// O terceiro verifica se o novo arquivo ja existe
	if(arquivo == FALSE)
	{
		printf("Erro !!\n");	
	}	
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tempo_de_Execucao(clock_t fim, clock_t inicio)
{
	printf("Tempo de Execucao: %4.0f segundos\n\n",(double)(fim-inicio)/(double)(CLOCKS_PER_SEC)); //Inicia um timer enquanto o programa � executado
																						          
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


main()
{
	clock_t inicio, fim;
	inicio = clock();
	char comando[100];
	char nome [100];
	char diretorio[100];
	int op = 0;
	
	while (op != 9)
	{
		printf("[1] Visualizar data e hora\n");
		printf("[2] Criar processo que ira abrir Internet Explorer\n");
		printf("[3] Criar um arquivo\n");
		printf("[4] Visualizar quantos nucleos o computador possui\n");
		printf("[5] Criar um novo diretorio\n");
		printf("[6] Apagar um diretorio\n");
		printf("[7] Fazer copia de um arquivo\n");
		printf("[8] Visualizar tempo de execucao de um programa\n");
		printf("[9] Sair\n");
		scanf("%d", &op);
		switch(op)
		{
			case 1:
				DataHora();
				break;
				
			case 2:
				Abrir_Internet();
				break;
				
				
			case 3:
				printf("Digite o diretorio em que o arquivo sera salvo e o nome do arquivo\n");
				scanf("%s", &diretorio);
				criar_Arquivo(diretorio);
				break;
				
				
			case 4:
				qtd_Nucleos();
				break;
				
				
			case 5:
				printf("Digite o local onde sera criado o diretorio e o nome do diretorio\n");
				scanf("%s",&diretorio);
				criar_Diretorio(diretorio);
				break;
				
				
			case 6:
				printf("Digite o nome e o local do diretorio que sera apagado\n");
				scanf("%s",&diretorio);
				apagar_Diretorio(diretorio);
				break;
				
				
			case 7:
				printf("Digite o nome do arquivo, incluindo seu diretorio, que sera feita a copia\n");
				scanf("%s",&diretorio);
				printf("Digite o nome da copia\n");
				scanf("%s", &nome);
				copiar_Arquivo(diretorio, nome);
				break;
				
				
			case 8:
				fim = clock();
				tempo_de_Execucao(fim, inicio);
				break;
				
		
		}
	}
} 

