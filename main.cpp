#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "Cola_Cliente.h"

using namespace std;

int Menu(){
	int Opc;
	do{
		cout << "\n\n\nBienvenido al sistema de registro de clientes del banco. \n";
		cout << "\nQue deseas hacer?\n";
		cout << "\n 1-Registrar un nuevo Cliente en la cola (3 espacios). ";
		cout << "\n 2-Asignar Ventanilla (3 espacios) a un Cliente.";
		cout << "\n 3-Analizar ventanillas.";
		cout << "\n 4-Actualizar ventanillas. (eliminar clientes)";
		cout << "\n 5-Mostrar Cola de Lista de espera de clientes.";
		cout << "\n 6-Mostrar Cola de Ventanillas.\n";
		cout << "\n 7-Terminar el dia.";
		cout << "\n 8-Leer desde archivo.";
		cout << "\n 9-Cerrar programa.\n";
		cout << "\nIngresa la opcion elegida: ";
		cin >> Opc;
	}while (Opc > 9 || Opc < 1);
	return Opc;
}

int Menu2(){
	int Opc;
	do{
		cout << "\n1.- Proceder a asignar ventanillas.";
		cout << "\n2.- Continuar";
		cout << "\nIntroduce opcion elegida: ";
		cin >> Opc;
	}while (Opc < 1 || Opc > 2);
	return Opc;    
}

int Menu3(){
	int Opc;
	do{
		cout << "\n1.- Proceder a rectificar ventanillas.";
		cout << "\n2.- Continuar";
		cout << "\nIntroduce opcion elegida: ";
		cin >> Opc;
	}while (Opc < 1 || Opc > 2);
	return Opc;    
}

int Menu4(){
	int Opc;
	do{
		cout << "\n1.- Si. Continuar";
		cout << "\n2.- No. Rectificar";
		cout << "\nIntroduce opcion elegida: ";
		cin >> Opc;
	}while (Opc < 1 || Opc > 2);
	return Opc;    
}

int main(){
	int total=0;
	
	ColaCircular ListaEspera;
	ColaCircular Ventanilla;
	Cliente Clie;
	
	int aux=0, aux2=0, aux3=0;
	      
	int Opc= Menu();
	
	while (Opc >= 1 && Opc <= 8){
		switch (Opc){
			case 1: {
				aux=ListaEspera.ColaCircularLlena();
				if(aux==0){
					cin >> Clie;
					ListaEspera.InsertaColaCircular(Clie);
					int Opc4=Menu4();//confirmar datos
					while (Opc4 == 2 ){
						switch (Opc4){						
							case 2:{
								ListaEspera.EliminaColaCircular(Clie);
								cout<<"Ingrese nuevamente los datos."<<endl;
								cin >> Clie;
								ListaEspera.InsertaColaCircular(Clie);
								break;
							}
						}	
						Opc4= Menu4();
					}
					
				}
				
				if (aux==1){//la cola esta llena
					cout << "\nLa cola de clientes esta llena.";
					if(Ventanilla.ColaCircularLlena()!=1){
						int Opc2=Menu2();
						switch (Opc2){
							case 1:{
							cout << "\nAsignaremos el primer cliente de la cola a una Ventanilla desocupada.";
							aux3=Ventanilla.InsertaColaCircular(Clie);
							cout << "\nEl cliente de la cola va a la Ventanilla: "<<aux3+1<<endl;
							ListaEspera.EliminaColaCircular(Clie);
							break;
							}
						}
					}
					else{
						cout << "\nLas ventanillas estan ocupadas";
						int Opc3=Menu3();
						switch (Opc3){
							case 1:{
								cout << "\nActualizaremos ventanillas.";
								Ventanilla.EliminaColaCircular(Clie);
								aux3=Ventanilla.InsertaColaCircular(Clie);
								cout << "\nEl cliente de la cola va a la Ventanilla: "<<aux3+1<<endl;
								ListaEspera.EliminaColaCircular(Clie);
								break;
							}
						}
					}
				}	
				break;
			}

			case 2: {
				aux=Ventanilla.ColaCircularLlena();
				aux2=ListaEspera.ColaCircularVacia();
				if (aux2==1){//no hay clientes para pasar a ventanilla
					cout << "\nNo hay clientes por asignar a ventanilla.";
					break;
				}
			
				if (aux==1){//las ventanillas estan ocupadas
					cout << "\nLas ventanillas estan ocupadas.";
					int Opc3=Menu3();
					switch (Opc3){
						case 1:{
							cout << "\nActualizaremos ventanillas.";
							Ventanilla.EliminaColaCircular(Clie);
							aux3=Ventanilla.InsertaColaCircular(Clie);	
							cout << "\nEl cliente de la cola debe ir a la Ventanilla: "<<aux3+1<<endl;
							ListaEspera.EliminaColaCircular(Clie);
							break;
						}
					}
					break;
				}
			
				if(aux==0){ //si las ventanillas no estan ocupadas
					cout << "\nAsignaremos el primer cliente de la cola a una Ventanilla desocupada.";
					aux3=Ventanilla.InsertaColaCircular(Clie);
					cout << "\nEl cliente de la cola debe ir a la Ventanilla: "<<aux3+1<<endl;
					ListaEspera.EliminaColaCircular(Clie);//se elimina el cliente de la cola
				}
				break;
			}

			case 3:{
				aux=Ventanilla.ColaCircularLlena();
				if(aux==1){//las ventanillas estan llenas
					cout << "\nLas ventanillas estan ocupadas.";
				}
			
				if(aux==0){//las ventanillas aun no se llenan
					cout << "\nAun hay ventanillas libres.";
				}			
				break;
			}
		
			case 4: {
				aux=Ventanilla.ColaCircularLlena();
				if(aux!=0){
					cout << "\nActualizaremos ventanillas.";
					Ventanilla.EliminaColaCircular(Clie);
					cout << "\nAhora hay ventanillas libres.";
				}
				else{
					cout<<"\nAun hay ventanillas libres, no hace falta actualizar.";
				}
				break;
			}
			
			case 5: {
				aux=ListaEspera.ColaCircularVacia();
				if(aux==0){
					cout << "\nClientes en la Cola de la Lista de espera.\n\n";
					ListaEspera.mostrar();
				}
				else{
					cout<<"\nNo hay clientes.";
					ListaEspera.mostrar();
				}
				break;
			}
			
			case 6: {
				aux=Ventanilla.ColaCircularVacia();
				if(aux!=1){
					cout << "\nClientes en la Cola de la Lista de espera.\n\n";
					Ventanilla.mostrar();
				}
				else{
					cout<<"\nNo hay clientes.";
					Ventanilla.mostrar();				
				}
				break;
			}
		
			case 7:{
				aux=Ventanilla.ColaCircularLlena();
				aux2=ListaEspera.ColaCircularVacia();
				
				cout << "\nHemos terminado el dia laboral.";
	        	total=ListaEspera.total_clientes();
	        	cout << "\nCantidad de clientes atendidos del dia: "<<total<<" clientes";
	        	ListaEspera.imprimir_archivo();
				break;
			}
			
			case 8:{
				aux=ListaEspera.ColaCircularLlena();
				if (aux==0){
					ListaEspera.leer_archivo(Clie);//total de clientes que llegaron a la cola lista de espera
				}
				
				if (aux==1){//la cola esta llena
				cout << "\nLa cola de lista de espera esta llena";
					if(Ventanilla.ColaCircularLlena()!=1){//si hay ventanillas sibres
						int Opc2=Menu2();
						switch (Opc2){
							case 1:{
							cout << "\nAsignaremos el primer cliente de la cola a una Ventanilla desocupada.";
							aux3=Ventanilla.InsertaColaCircular(Clie);
							cout << "\nEl cliente de la cola va a la Ventanilla: "<<aux3+1<<endl;
							ListaEspera.EliminaColaCircular(Clie);
							break;
							}
						}
					}
					else{
						cout << "\nLas ventanillas estan ocupadas";
						int Opc3=Menu3();
						switch (Opc3){
							case 1:{
								cout << "\nActualizaremos ventanillas.";
								Ventanilla.EliminaColaCircular(Clie);
								aux3=Ventanilla.InsertaColaCircular(Clie);
								cout << "\nEl cliente de la cola va a la Ventanilla: "<<aux3+1<<endl;
								ListaEspera.EliminaColaCircular(Clie);
								break;
							}
						}
					}
				}								
				break;
			}
    	}
    Opc= Menu();
	}

	return 0;
}