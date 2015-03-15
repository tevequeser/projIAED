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

int * sort(int list[])
{
	int i = 0;
	int j = 0;
	int tmp;
	while (i < 100)
	{
		while(j < 100 - i)
		{
			if(list[j] > list[j+1])
			{
				tmp = list[j+1];
				list[j+1] = list[j];
				list[j] = tmp;
			}
			j++;
		}
		i++;
	}
	return(list);
}


void addBank(char nome[MAXnome], int class, int ref)
{
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

void downgrade(int ref)
{
	int i = 0;
	while(banco[i].referencia != ref)
	{
		i++;
	}
	banco[i].class = 0;
}								/*yes these, i was talking about merging these*/

void upgrade(int ref)
{
	int i = 0;
	while(banco[i].referencia != ref)
	{
		i++;
	}
	banco[i].class = 1;
}

void addLoan(int val, int ref1, int ref2)
{
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
	pagamento[forn][recb].emprestimo += val;
}

void addMortgage(int val, int ref1, int ref2)
{
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
	pagamento[forn][recb].amortizacao = val;
}

void listBanks(int instr)
{
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
		while(banco[i].isfull == 1)
		{
			int j = 0;
			int k = 0;
			int inP = 0;
			int inV = 0;
			int inVM = 0;
			int outP = 0;
			int outV = 0;
			int outVM = 0;
			
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
				j++;
			}
			while(banco[k].isfull == 1)
			{
				if(pagamento[k][i].emprestimo > 0)
				{
					inV += pagamento[k][i].emprestimo;
					if(banco[k].class == 0)
					{
						inVM += pagamento[k][i].emprestimo;
					}
					inP++;
				}
				k++;
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
		int total;
		
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
			i++;
			printf("[%d] ", total);
		}
		printf("\n");
		
	}
}

void getSize()			/*Juntar este com o K*/
{
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
			case 'k':
				sscanf(input, "%s %d", &command, &ref);
				downgrade(ref);
				break;					/*merge these two at the top*/
			case 'r':
				sscanf(input, "%s %d", &command, &ref);
				upgrade(ref);
				break;
			case 'e':
				sscanf(input, "%s %d %d %d", &command, &ref1, &ref2, &valor);
				addLoan(valor, ref1, ref2);
				break;
			case 'p':
				sscanf(input, "%s %d %d %d", &command, &ref1, &ref2, &valor);
				addMortgage(valor, ref1, ref2);
				break;
			case 'l':			/*falta l 2 --> its not working as it should exactly*/
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
