#include<stdio.h>
#include<string.h>

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

int find(int arg1)
{
	int i = 0;
	while(banco[i].referencia != arg1)
	{
		i++;
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
	int i = find(ref);
	switch(comm)
	{
		case 'k':
			banco[i].class = 0;
			break;
		case 'r':
			banco[i].class = 1;
		default:
			break;
	}
}

void addPagamento(char comm, int val, int ref1, int ref2, int pagamento[MAXbanco][MAXbanco])
{
	/*
	 * comando "e" (adiciona emprestimo)
	 * comando "p" (amortizacao)
	 * */
	int forn = find(ref1);
	int recb = find(ref2);
	switch(comm)
	{
		case 'e':
			pagamento[forn][recb] += val;
			break;
		case 'p':
			if(pagamento[recb][forn] >= val)
			{
				pagamento[recb][forn] -= val;
			}
			break;
		default:
			break;
	}
}

void killBom(int pagamento[MAXbanco][MAXbanco])
{
	/*
	 * comando 'K' (mostra os dados de um banco 'bom' com maior divida)
	 * */
	int i, x, j, check, inP, inV, inVM, outP, outV, outVM, 
	inPt, inVt, inVMt, outPt, outVt, outVMt;
	outVM = i = x = check = 0;
	while(banco[i].isfull == 1)
	{
		j = inPt = inVt = inVMt = outPt = outVt = outVMt = 0;
		while(banco[j].isfull == 1)
		{
			if(pagamento[i][j] > 0)
			{
				outVt += pagamento[i][j];
				if(banco[j].class == 0)
				{
					outVMt += pagamento[i][j];
				}
				outPt++;
			}
			if(pagamento[j][i] > 0)
			{
				inVt += pagamento[j][i];
				if(banco[j].class == 0)
				{
					inVMt += pagamento[j][i];
				}
				inPt++;
			}
			j++;
		}
		if(banco[i].class == 1 && outVMt >= outVM && outVMt > 0)
		{
			inP = inPt;
			inV = inVt;
			inVM = inVMt;
			outP = outPt;
			outV = outVt;
			outVM = outVMt;
			x = i;
			check = 1;
		}
		i++;
	}
	if(check == 1)
	{
		banco[x].class = 0;
	}
	else
	{
		return;
	}
	printf("*%d %s %d %d %d %d %d %d %d\n", banco[x].referencia, 
					banco[x].nome, banco[x].class, inP, outP, outV, 
					outVM, inV, inVM);
}
	
void listBanks(int instr, int pagamento[MAXbanco][MAXbanco])
{
	/*
	 * comando "l" (lista os bancos de acordo com a instrucao dada)
	 * */
	int i, j, inP, inV, inVM, outP, outV, outVM;
	int k, parceiros = i = 0;
	int arr[MAXbanco-1] = {0};
	switch(instr)
	{
		case 0:
			while(banco[i].isfull == 1)
			{
				printf("%d %s %d\n", banco[i].referencia, banco[i].nome, banco[i].class);
				i++;
			}
			break;
		case 1:
			while(banco[i].isfull == 1)
			{
				j = inP = inV = inVM = outP = outV = outVM = 0;
				
				while(banco[j].isfull == 1)
				{
					if(pagamento[i][j] > 0)
					{
						outV += pagamento[i][j];
						if(banco[j].class == 0)
						{
							outVM += pagamento[i][j];
						}
						outP++;
					}
					if(pagamento[j][i] > 0)
					{
						inV += pagamento[j][i];
						if(banco[j].class == 0)
						{
							inVM += pagamento[j][i];
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
			break;
		case 2:
			while(banco[i].isfull == 1) 	
			{
				k = 0;
				while(banco[k].isfull == 1)
				{
					if(pagamento[i][k] > 0 || pagamento[k][i] > 0)
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
				{
					printf("%d %d\n", i, arr[i]);
				}
			}
			break;
		default:
			break;
	}
}

void bankNum()
{
	/*
	 * comando "x" (verifica o numero total de bancos registados,
	 * numero de bancos "bons")
	 * */
	int Ntotal = 0, Nbons = 0;
	while(banco[Ntotal].isfull == 1)
	{
		if(banco[Ntotal].class == 1)
		{
			Nbons++;
		}
		Ntotal++;
	}
	printf("%d %d\n", Ntotal, Nbons);
}

int main()
{
	char command, input[MAXinput];
	static int pagamento[MAXbanco][MAXbanco];
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
				addPagamento(command, arg2, arg, arg1, pagamento);
				break;
			case 'l':				/*listar os bancos*/
				sscanf(input, "%s %d", &command, &arg);
				listBanks(arg, pagamento);
				break;
			case 'K':
				killBom(pagamento);
				bankNum();
				break;
			case 'x':				/*exit do programa (voluntario)*/
				bankNum();
				return(0);
				break;
			default:
				break;
		}
	}	
	return(0);
}
