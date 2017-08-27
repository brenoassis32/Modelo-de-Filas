#include <iostream>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#define TAM 100000
#define m 2147483647
//#define m 2147483647
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

using namespace std;

double relogio, tempo_p_chegada, tempo_p_termino, t_max;
int n_clientes_fila;
double utilizacao_atendente, tec, ta, soma, soma2; // ta = tempo de atendimento -> Lambda ; tec = tempo entre chegadas -> mi
int status_atendente;
double r, numero_m_sistema, numero_m_fila, numero_m_servico, tempo_m_fila, tempo_m_perman;

double GeraPseudoAleatorio(unsigned long int valor){
	int i,a;
	unsigned long int sequencia[10]; 	 
	a=16807;
	i=0;
	sequencia[0] = valor;
	sequencia[i+1] = (a*sequencia[i]) % m;

	return sequencia[i+1];	
}

double GeraPseudoAleatorio01(unsigned long int sequencia){
	double u;
	u = (double) (sequencia)/(m-1);	
	
	return u;
}


double Exponencial(double media, unsigned long int &valor){
	double u;
	valor = GeraPseudoAleatorio(valor);
	u = GeraPseudoAleatorio01(valor);
	
	return -1*media*log(u);
}

double Const(double media){
	return media;
}

void SimulacaoMM1(double v1, double v2, unsigned long int &semente1, unsigned long int &semente2){
	//cout << endl << "\t---------- {-----Inicializacao-----} ----------" << endl << endl;
	double lambda=v1, mi=v2;
	double utm, utm2, nms, nmf, tms, tmf;
	unsigned long int indice_ta=semente1, indice_tec=semente2;
	int i=0,j=0, contador = 0, n1=0, n2=0;
	double aux_fila[TAM], tempo_espera_fila[TAM], ta1=0, ta2=0;
	relogio=0; 
	tempo_p_chegada = 0;
	t_max=100000;
	tempo_p_termino = t_max + 1;
	soma=0;
	soma2 = 0;
	n_clientes_fila=0;
	status_atendente=0;
	aux_fila[0]=0;

	for (int w=0; w<=TAM; w++ ){
			tempo_espera_fila[w] = 0;
			aux_fila[w]=0;
	}

	
	//cout << endl << "\t---------- {-----Simulacao-----} ----------" << endl << endl;
	while(relogio <= t_max){
		if(tempo_p_chegada < tempo_p_termino){ 
	//		cout << endl << "\t---------- {-----Trata eventos de chegada-----} ----------" << endl << endl;
			relogio = tempo_p_chegada;
	//		cout << "Nova chegada em t = : " << relogio << endl;
			if(status_atendente == 0){
	//			cout << "Inicia o atendimento em t = : " << relogio << endl;
				status_atendente = 1;
				ta = Exponencial(mi,indice_ta);
				if (ta>0 && ta<=t_max){
	//				cout << "Tempo de Atendimento (ta): " << ta << endl;
					soma = soma + ta;
					tempo_p_termino = relogio + ta;
					n1++;
					ta1=ta1+ta;
	//				cout << "ta1  =  " << ta1 << endl;											
				}else{
					//rand();
					ta = Exponencial(mi,indice_ta);
	//				cout << "Tempo de Atendimento (ta): " << ta << endl;
					soma = soma + ta;
					tempo_p_termino = relogio + ta;
					n1++;
					ta1=ta1+ta;
	//				cout << "ta1  =  " << ta1 << endl;
				}									 
			} else {
			n_clientes_fila = n_clientes_fila + 1;
			aux_fila[i] = relogio;
			i++;
			}
			tec = Exponencial(lambda,indice_tec);
			if (tec>0 && tec<=t_max){
	//			cout << "Tempo entre Chegadas (tec): " << tec << endl;
				tempo_p_chegada = relogio + tec;
	//			cout << "Tempo para a proxima chegada: " << tempo_p_chegada << endl << endl;								
			}else{
				rand();
				tec = Exponencial(lambda,indice_tec);
	//			cout << "Tempo entre Chegadas (tec): " << tec << endl;
				tempo_p_chegada = relogio + tec;
	//			cout << "Tempo para a proxima chegada: " << tempo_p_chegada << endl << endl;							
			}			
		}else{
	//		cout << endl << "\t---------- {-----Trata eventos de atendimento-----} ----------" << endl << endl;
			relogio = tempo_p_termino;
	//		cout << "Status do atendente : " << status_atendente << endl;
			if (n_clientes_fila > 0){
	//			cout << "Inicia atendimento em t = : " << relogio << endl;
				tempo_espera_fila[j]= relogio - aux_fila[j];
				j++;
				n_clientes_fila = n_clientes_fila - 1;
				ta = Exponencial(mi,indice_ta);
				if (ta>0 && ta<=t_max){
	//				cout << "Tempo de Atendimento (ta): " << ta << endl;
					soma = soma + ta;
					tempo_p_termino = relogio + ta;
					n2++;
					ta2=ta2+ta;
	//				cout << "ta2  =  " << ta2 << endl;
	//				cout << "Termino do atendimento: " << tempo_p_termino << endl;
	//				cout << "Soma: " << soma << endl << endl;					
				}else{
					//rand();
					ta = Exponencial(mi,indice_ta);
	//				cout << "Tempo de Atendimento (ta): " << ta << endl;
					soma = soma + ta;
					tempo_p_termino = relogio + ta;
					n2++;
					ta2=ta2+ta;
	//				cout << "ta2  =  " << ta2 << endl;
	//				cout << "Termino do atendimento: " << tempo_p_termino << endl;
	//				cout << "Soma: " << soma << endl << endl;
				}				
			}else{
				status_atendente = 0;
				tempo_p_termino = t_max +1;
	//			cout << "Termino do atendimento: " << tempo_p_termino << endl << endl;
			}					
		}
	//	cout << endl << "\t---------- {-----Verfica Loop-----} ----------" << endl << endl;
		contador++;
	//	cout << "Tempo para Chegada: " << tempo_p_chegada << endl;
	//	cout << "Tempo para Termino: " << tempo_p_termino << endl;
	//	cout << "Clientes na Fila : " << n_clientes_fila << endl;
	//	cout << endl<< "k =  " << contador<< endl << endl;
		
	}
	//cout << endl << "\t---------- {-----Relatorios-----} ----------" << endl << endl;
	
	
	utilizacao_atendente = 100*(soma/t_max);

	for (int w=0; w<j; w++ ){
		if( w == 0 ){
			tempo_espera_fila[1] = tempo_espera_fila[1]+tempo_espera_fila[0];
		}else{
			tempo_espera_fila[w+1] = tempo_espera_fila[w+1]+tempo_espera_fila[w];			
		}
	}
	
	//Variáveis de Controle da Simulação
	tempo_m_fila = tempo_espera_fila[j]/(n1+n2);
	r=(ta1+ta2)/(n1+n2);
	tempo_m_perman = r+tempo_m_fila;
	numero_m_servico = soma/t_max; 
	numero_m_fila = tempo_espera_fila[j]/t_max;
	numero_m_sistema = numero_m_fila + numero_m_servico;
	
	//Variáveis de Controle Teóricos
	utm = mi/lambda;
	utm2 = utm*100;
	nms = utm/(1-utm);
	nmf = (utm*utm)/(1-utm);
	tms = utm/((1/lambda)*(1-utm));
	tmf = utm/((1/mi)*(1-utm));
		
	cout << endl << " ------- { Parametros Simulados } -------- " << "\t\t|\t ------- { Parametros Modelados (MM1) } -------- " << endl << "\t\t\t\t\t\t\t|\t" << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Utilizacao media do sistema            =  " << utilizacao_atendente << "\t|\t Utilizacao media do sistema            = " << utm2 << endl << "\t\t\t\t\t\t\t|\t" << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Numero medio de clientes no sistema    =  " << numero_m_sistema << "\t|\t Numero medio de clientes no sistema    = " << nms << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Numero medio de clientes em filas      =  " << numero_m_fila << "\t|\t Numero medio de clientes em filas      = " << nmf << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Numero medio de clientes em servico    =  " << numero_m_servico << "\t|\t Numero medio de clientes em servico    = " << utm << endl << "\t\t\t\t\t\t\t|\t" << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Tempo medio de atendimento             =  " << r << "\t|\t Tempo medio de atendimento             = " << mi << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Tempo medio de espera em filas         =  " << tempo_m_fila << "\t|\t Tempo medio de espera em filas         = " << tmf << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Tempo medio de permanencia no sistema  =  " << tempo_m_perman << "\t|\t Tempo medio de permanencia no sistema  = " << tms << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Tempo total de processamento           =  " << relogio << "\t|\t" << endl <<"\t\t\t\t\t\t\t|\t" << endl << "\t\t\t\t\t\t\t|\t";
	cout << endl << "Ultimo aleatorio gerado (TA)           =  " << indice_ta <<"\t|\t" << endl <<"\t\t\t\t\t\t\t|\t";
	cout << endl << "Ultimo aleatorio gerado (TEC)          =  " << indice_tec <<"\t|\t" << endl;
	
	semente1=indice_ta; 
	semente2=indice_tec;
}

int main(int argc, char** argv) {
	system("mode con:cols=120 lines=2000");
	double lambda, mi;
	unsigned long int semente1, semente2;
	
	lambda=6; //Tempo Médio de Chegadas (horas, minutos, segundos)
	mi=4; //Tempo Médio de Atendimento (horas, minutos, segundos)
	semente1=12435; // Semente para gerar tempo entre chegadas
	semente2=43575423; // Semente para gerar tempo entre chegadas
	
	for(int i=0; i<=10; i++){
		//Sleep(500);
		cout << "Simulacao i = " << i <<" do sistema" << endl;
		//rand();
		SimulacaoMM1(lambda, mi, semente1, semente2);
		//Sleep(500);
		cout << endl << endl;		
	}
	
	cout << endl;
    cout << "-- Modelagem e Simulacao de Eventos Discretos --" << endl;
    cout << "-- Modelo de Filas MM1 --" << endl;
    cout << "-- Por Breno Assis (C) 2016 - brenoassis_rj@hotmail.com --" << endl;
    cout << endl << endl;

	
	system ("pause");
	return 0;
}
