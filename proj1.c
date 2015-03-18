#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAXbanco 1000
#define MAXnome 40
#define MAXinput 100

struct BANCO
{
	char nome[MAXnome];
	int class;
	int referencia;
	int isfull;
}
banco[MAXbanco];

struct PAGAMENTO
{
	int emprestimo;
	int amortizacao;
}
pagamento[MAXbanco][MAXbanco];

void addBank(char nome[MAXnome], int class, int ref)
{
	/*
	 * comando "a" (adiciona um novo banco)
	 * */
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
	/* comando "k" (classifica um banco "mau")
	 * comando "r" (classifica um banco "mau")
	 * */
	int i = 0;
	while(banco[i].referencia != ref)
	{
		i++;
	}
	if(comm == 'k')
		banco[i].class = 0;
	else
		banco[i].class = 1;
}

void addPagamento(char comm, int val, int ref1, int ref2)
{
	/*
	 * comando "e" (adiciona emprestimo)
	 * comando "p" (amortizacao)
	 * */
	int forn = 0;
	int recb = 0;
	while(banco[forn].referencia != ref1)
	{
		forn++;
	}
	while(banco[recb].referencia != ref2)
	{
		recb++;
	}
	if(comm == 'e')
		pagamento[forn][recb].emprestimo += val;
	else
		pagamento[forn][recb].amortizacao = val;
}

void listBanks(int instr)
{
	/*
	 * comando "l"
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
													banco[i].nome, 
													banco[i].class, 
													inP, 
													outP, 
													outV, 
													outVM, 
													inV, 
													inVM);
			i++;
		}
	}
	else if(instr == 2)
	{
		int i = 0;
		int k;
		int j;
		int p = 0;
		int total;
		int count = 0;
		int arr[40] = {[0 ... 39] = -1};
		
		while(banco[i].isfull == 1)
		{
			k = 0;
			total = 0;
			while(banco[k].isfull == 1)
			{
				if(pagamento[i][k].emprestimo > 0 || pagamento[k][i].emprestimo > 0)
				{
					total++;
				}
				k++;
			}
			arr[i] = total;
			i++;
		}
		while(arr[p] != -1)
		{
			j = p;
			count = 0;
			while(arr[j] != -1)
			{
				if(arr[j] == arr[p])
				{
					count++;
				}
				j++;
			 }
			printf("%d %d\n", arr[p], count);
			p++;
		}
		printf("\n");
		total = 0;
	}
}

void getSize()			/*Juntar este com o K*/
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
	char command;
	char input[MAXinput];
	while(1)
	{
		fgets(input, MAXinput, stdin);
		switch(input[0])
		{
			char nome[MAXnome];
			int class;
			int ref;
			int ref1;
			int ref2;
			int valor;
			int instr;
			case 'a':
				sscanf(input, "%s %s %d %d", &command, &nome, &class, &ref);
				addBank(nome, class, ref);
				break;
			case 'k':case 'r':
				sscanf(input, "%s %d", &command, &ref);
				classify(command, ref);
				break;
			case 'e':case 'p':
				sscanf(input, "%s %d %d %d", &command, &ref1, &ref2, &valor);
				addPagamento(command, valor, ref1, ref2);
				break;
			case 'l':			/*falta l 2 --> make it print as it should*/
				instr = -1;
				sscanf(input, "%s %d", &command, &instr);
				if (instr == -1)
				{ 
					break;
				}
				listBanks(instr);
				break;
			case 'x':
				getSize();
				exit(EXIT_SUCCESS);
				break;
			default:
				break;
		}
	}	
	return(0);
}
