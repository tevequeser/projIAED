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
}
banco[MAXbanco];

struct PAGAMENTO
{
	int emprestimo;
	int amortizacao;
}
pagamento[MAXbanco][MAXbanco];

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
	/* comando "k" (classifica um banco como "mau")
	 * comando "r" (classifica um banco como "bom")
	 * */
	char com = comm;
	int i = find('r', ref);
	if(com == 'k')
	{
		banco[i].class = 0;
	}
	else if(com == 'r')
	{
		banco[i].class = 1;
	}
	else
	{
		printf("Invalid Instruction\n");
		exit(1);
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
		printf("Invalid Instruction\n");
		exit(1);
	}
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
					banco[i].nome, banco[i].class, inP, outP, outV, 
					outVM, inV, inVM);
			i++;
		}
	}
	else if(instr == 2)
	{
		int arr[50] = {[0 ... 49] = -1};
		int c, tmp, i, k, j, p, total, count;
		c = i = p = count = 0;
		
		while(banco[i].isfull == 1)
		{
			k = total = 0;
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
		for (p = 0; p < i; ++p)
		{	
			for (j = p + 1; j < i; ++j)
			{
				if (arr[p] > arr[j])
				{
					tmp =  arr[p];
					arr[p] = arr[j];
					arr[j] = tmp;
				}
			}
		}
		while(c < i)
		{
			count = 1;
			while(arr[c] == arr[c+1])
			{
				count++;
				c++;
			}
			printf("%d %d\n", arr[c], count);
			c++;
		}
	}
	else
	{
		printf("Invalid Argument\n");
		exit(1);
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
			case 'a':
				sscanf(input, "%s %s %d %d", &command, nome, &arg, &arg1);
				addBank(nome, arg, arg1);
				break;
			case 'k':case 'r':
				sscanf(input, "%s %d", &command, &arg);
				classify(command, arg);
				break;
			case 'e':case 'p':
				sscanf(input, "%s %d %d %d", &command, &arg, &arg1, &arg2);
				addPagamento(command, arg2, arg, arg1);
				break;
			case 'l':
				sscanf(input, "%s %d", &command, &arg);
				listBanks(arg);
				break;
			case 'x':
				bankNum();
				exit(0);
				break;
			default:
				break;
		}
	}	
	return(0);
}
