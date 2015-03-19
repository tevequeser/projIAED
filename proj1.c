#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXbanco 1000
#define MAXnome 42
#define MAXinput 100

struct BANCO
{
	char nome[MAXnome];
	int class;
	int referencia;
	int isfull;
} banco[MAXbanco];

struct PAGAMENTO
{
	int emprestimo;
	int amortizacao;
} pagamento[MAXbanco][MAXbanco];

int find(char arg1, int arg2)
{
	int i = 0;
	if(arg1 == 'r')
	{
		while(banco[i].referencia != arg2)
		{
			i++;
		}
	}
	return i;
}

void addBank(char nome[MAXnome], int class, int ref)
{
	/*
	 * comando "a" (adiciona um novo banco)
	 * recebe: dois inteiros (class [0, 1] e a referencia) e o nome
	 * do banco (tamanho maximo de 41 (42 reservado para o \0))
	 * 
	 */
	int i = 0;
	int j = 0;
	int lenNOME = strlen(nome);
	while(banco[i].isfull == 1)
	{
		i++;
	}
	while(j < lenNOME)
	{
		banco[i].nome[j] = nome[j];
		j++;
	}
	banco[i].class = class;
	banco[i].referencia = ref;
	banco[i].isfull = 1;
}

void classify(char comm, int ref)
{
	/*
	 * comando "k" (despromove para um banco "mau")
	 * comando "r" (promove para um banco "bom")
	 * */
	int i = find('r', ref);
	if(comm == 'k')
	{
		banco[i].class = 0;
	}
	else if(comm == 'r')
	{
		banco[i].class = 1;
	}
	else
	{
		printf("Invalid Argument\n");
		exit(1);	/* EXIT_FAILURE */
	}
	
}

void addPagamento(char comm, int val, int ref1, int ref2)
{
	/*
	 * comando "e" (adiciona emprestimo)
	 * comando "p" (amortizacao)
	 * */
	int forn = find('r', ref1);
	int recb = find('r', ref2);
	if(comm == 'e')
	{
		pagamento[forn][recb].emprestimo += val;
	}
	else if(comm == 'p')
	{
		pagamento[forn][recb].amortizacao = val;
	}
	else
	{
		printf("Invalid Argument\n");
		exit(1);	/* EXIT_FAILURE */
	}
}

void listBanks(int instr)
{
	/*
	 * comando "l" (lista os bancos de acordo com a instrucao dada)
	 * */
	int i = 0;
	if(instr == 0)
	{
		while(banco[i].isfull == 1)
		{
			printf("%d %s %d\n", banco[i].referencia, banco[i].nome, banco[i].class);
			i++;
		}
	}
	else if (instr == 1)
	{ 
		int j, inP, inV, inVM, outP, outV, outVM;
		while(banco[i].isfull == 1)
		{
			j = inP = inV = inVM = outP = outV = outVM = 0;
			
			while(banco[j].isfull == 1)
			{
				if(pagamento[i][j].emprestimo > 0)
				{
					outV += pagamento[i][j].emprestimo;
					if(banco[j].class == 0)
					{
						outVM += pagamento[i][j].emprestimo;
					}
					outP++;
				}
				if(pagamento[j][i].emprestimo > 0)
				{
					inV += pagamento[j][i].emprestimo;
					if(banco[j].class == 0)
					{
						inVM += pagamento[j][i].emprestimo;
					}
					inP++;
				}
				j++;
			}
			printf("%d %s %d %d %d %d %d %d %d\n", banco[i].referencia, 
					banco[i].nome, banco[i].class, inP, outP, outV, 
					outVM, inV, inVM);
			i++;
		}
	}
	else if(instr == 2)
	{
		int i = 0 , k, parceiros = 0;
		int arr[MAXbanco-1] = {0};
		
		while(banco[i].isfull == 1) 	
		{
			k = 0;
			while(banco[k].isfull == 1)
			{
				if(pagamento[i][k].emprestimo > 0 || pagamento[k][i].emprestimo > 0)
				{
					parceiros++;
				}
				k++;
			}
			arr[parceiros]++;
			parceiros = 0;
			i++;
		}
		for (i = 0; i < MAXbanco -1; i++)	
		{	
			if (arr[i] > 0)
				printf("%d %d\n", i, arr[i]);
		}
	}
	else
	{
		printf("Invalid Argument\n");
		exit(1);	/* EXIT_FAILURE */
	}
}

void bankNum()			/*Juntar este com o K*/
{
	/*
	 * comando "x" (verifica o numero total de bancos registados, numero de bancos "bons")
	 * */
	int i = 0;
	int j = 0;
	while(banco[i].isfull == 1)
	{
		if(banco[i].class == 1)
		{
			j++;
		}
		i++;
	}
	printf("%d %d\n", i, j);
}

int main()
{
	char command, input[MAXinput];
	while(1)
	{
		fgets(input, MAXinput, stdin);
		switch(input[0])
		{
			char nome[MAXnome];
			int arg, arg1, arg2;
			case 'a':				/*adicionar banco*/
				sscanf(input, "%s %s %d %d", &command, nome, &arg, &arg1);
				addBank(nome, arg, arg1);
				break;
			case 'k':case 'r':		/*upgrade/downgrade banco*/
				sscanf(input, "%s %d", &command, &arg);
				classify(command, arg);
				break;
			case 'e':case 'p':		/*adicionar emprestimo/amortizacao*/
				sscanf(input, "%s %d %d %d", &command, &arg, &arg1, &arg2);
				addPagamento(command, arg2, arg, arg1);
				break;
			case 'l':				/*listar os bancos*/
				sscanf(input, "%s %d", &command, &arg);
				listBanks(arg);
				break;
			case 'x':				/*exit do programa (voluntario)*/
				bankNum();
				exit(0);	/* EXIT_SUCCESS */
				break;
			default:
				break;
		}
	}	
	return(0);
}

/* Usamos sscanf em vez de scanf ou de fcanf + stdin porque nao queremos
 * que leia o mesmo output de linhas diferentes no caso de haver algum
 * erro de input.
 * 
 * Decidimos usar um Bubble sort nosso em vez do qsort() do stdlib.h
 * com o objectivo de reduzir o maximo possivel a utilizacao de libs 
 * e de usar o maximo possivel o nosso codigo. Portanto, embora tenhamos
 * usado o exit(), decidimos usar como argumentos o 0 e o 1 em vez do
 * EXIT_SUCCESS e do EXIT_FAILURE.
 * 
 * Como se pode ver, usamos o estilo de Allman (ou BSD) porque qualquer 
 * outro estilo e objectivamente inferior.
 */
