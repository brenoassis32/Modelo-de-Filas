#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define TAM 100000
#define m 2147483647
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

unsigned long int valor;

double GeraPseudoAleatorio(unsigned long int valor){
	int i,a;
	unsigned long int sequencia[10]; 
	 
	a=16807;
	i=0;
	sequencia[0] = valor;

	sequencia[i+1] = (a*sequencia[i]) % m;
	//cout<< "Semente : "<<sequencia[i]<<endl;
	//cout<< "Valor : "<<sequencia[i+1]<<endl;
	
	return sequencia[i+1];	
}

double GeraPseudoAleatorio01(unsigned long int sequencia){
	double u;
	u = (double) (sequencia)/(m-1);	
	return u;
}

int CriptJulioCesar(int valor){
	int cript;
	return cript=(valor+3)%26;	
}

int UnCriptJulioCesar(int valor){
	int uncript;
	return uncript=(valor-3)%26;	
}

double GeraTeste(unsigned long int valor){
	int i,a;
	unsigned long int sequencia[10]; 
	 
	a=16807;
	i=0;
	sequencia[0] = valor;

	sequencia[i+1] = (sequencia[i]/a) % m;
	//cout<< "Semente : "<<sequencia[i]<<endl;
	//cout<< "Valor : "<<sequencia[i+1]<<endl;
	
	return sequencia[i+1];	
}

double Exponencial(double media,unsigned long int &valor){
	double u;
/*	
	u = rand() % 101;
	u = u/100;
*/	valor = GeraPseudoAleatorio(valor);
	u = GeraPseudoAleatorio01(valor);

	return -1*media*log(u);
}

int Uniforme(unsigned long int &valor){
	double u;
	int a,b;
	a = 1;
	b = 60;
	
	valor = GeraPseudoAleatorio(valor);
	u = GeraPseudoAleatorio01(valor);

	return (a + u*(b - a));
}

double Inv_Uniforme(double unif){
	double u;
	int a,b;
	a = 1;
	b = 60;
	
	//valor = GeraPseudoAleatorio(valor);
	//u = GeraPseudoAleatorio01(valor);

	return (unif-a)/(b - a);
}

unsigned long int RetornaPseudoAleatorio(double valor){
	int i,a;
	unsigned long int sequencia[10]; 
	 
	a=16807;
	i=0;
	sequencia[0] = valor*(m-1);

	sequencia[i+1] = (sequencia[i]/a) % m;
	//cout<< "Semente : "<<sequencia[i]<<endl;
	//cout<< "Valor : "<<sequencia[i+1]<<endl;
	
	return sequencia[i+1];	
}


int main() {
	
	FILE *arquivo;
	arquivo = fopen("Gerador.txt","wt");
	
/*	
	unsigned long int valor,semente;
	srand(time(NULL));
	semente=rand();
	int i;
	while(i<6){
		valor = Uniforme(semente);
		cout<< "Valor sorteado i = [" <<i+1<<"] : "<<valor<<endl;
		fprintf(arquivo, "%d\n", valor);
		i++;
	}
*/
	unsigned long int valor,valor1;
	double semente;
	double valor01;
	int valorU;
	//srand(time(NULL));
	valor=23534456543;
//	valor=rand();
	int i=0;
	cout<<"Semente: "<<valor<<endl;
	while(i<6){
//		valor1 = GeraPseudoAleatorio(valor);
	//	valor01 = GeraPseudoAleatorio01(valor);
		valorU = Uniforme(valor);
		semente = RetornaPseudoAleatorio(Inv_Uniforme(valorU));
//		semente = RetornaPseudoAleatorio(valor1);
		cout<<valor<< "\t"<< valorU << "\t"<< semente <<endl;
		fprintf(arquivo, "%d\t%lf\t%d\n", valor,valor01,valorU);
		i++;
	}

	
	fclose(arquivo);
	double cript = CriptJulioCesar(12);
	int uncript = UnCriptJulioCesar(cript);
	
//	cout<< " Valor Criptografado : "<< cript <<endl;
//	cout<< " Valor Descriptografado : "<< uncript <<endl;
	
	system ("pause");
	return 0;
}
