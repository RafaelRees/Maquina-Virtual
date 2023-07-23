#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;

//Definição da memória
struct memoria
{
	int operando, operador;
}mem[512];

int SP=512;
int PC;
int CS;
int DS;

//Função que carrega o programa para a memória
void loader()
{
 FILE * f ;
 int i=0;
 char nomeArq [30] ;
 printf("Digite o nome do arquivo: ");
 scanf("%s", nomeArq) ;
 f = fopen(nomeArq, "r");
 PC=0;
 i=0;
 while (!feof(f)){
	fscanf (f, "%d%d", &mem[i].operador, &mem[i].operando);
	i++;
 }
}

//Função que executa o programa da memória
void cpu()
{
	while(mem[PC].operador!=12){ //Programa para de ser executado com o operador "12"
		switch(mem[PC].operador){ //Reconhece a operação a ser executado
		case 0: //PUSH
			SP--;
			mem[SP].operador = mem[mem[PC].operando].operador;
			PC++;
			break;

		case 1: //ADD
			mem[SP+1].operador = mem[SP+1].operador + mem[SP].operador;
			PC++;
			SP++;
			break;

		case 2: //SUB
			mem[SP+1].operador = mem[SP+1].operador - mem[SP].operador;
			PC++;
			SP++;
			break;

		case 3: //MUL
			mem[SP+1].operador = mem[SP+1].operador * mem[SP].operador;
			PC++;
			SP++;
			break;

		case 4: //DIV
			mem[SP+1].operador = mem[SP+1].operador / mem[SP].operador;
			PC++;
			SP++;
			break;

		case 5: //POP e Store
			mem[mem[PC].operando].operador=mem[SP].operador;
			PC++;
			break;

		case 6: //JMP
			PC = mem[PC].operando;
			break;

		case 7: //JEQ
			if (mem[SP].operador == 0){
	 			PC = mem[PC].operando;
			}
			else{
				PC++;
			}
			break;

		case 8: //JGT
			if (mem[SP].operador > 0){
				PC = mem[PC].operando;
			}
			else{
				PC++;
			}
			break;

		case 9: //JLT
			if (mem[SP].operador < 0){
				PC = mem[PC].operando;
			}
			else{
				PC++;
			}
			break;

		case 10: //IN
			cout << "Digite um valor: ";
		    cin >> mem[mem[PC].operando].operador;
		    PC++;
		    break;

		case 11: //OUT
			cout << "Resultado: "<< mem[mem[PC].operando].operador << endl;
			PC++;
			break;
		}
	}
}

int main()
{
    int i;
	loader();
	cpu();
	//Printa a memória
	//for(i=0;i<512;i++){
	//	cout << "mem["<< i << "]\tx=" << mem[i].operador <<"\ty=" << mem[i].operando << endl;
	//}
}
