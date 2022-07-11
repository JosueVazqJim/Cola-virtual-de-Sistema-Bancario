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

#define MAX 3

Cliente::Cliente()
{}

Cliente::Cliente(char NC[], char T[], char id[], char NDC[]){
	strcpy(NombreCompleto, NC);
	strcpy(Tramite, T);
	strcpy(ID, id);
	strcpy(NumeroCuenta, NDC);
}

istream &operator>>(istream &Lee, Cliente &ObjClie){
	cout << "\n\nIngresa nombre del cliente: ";
	Lee >> ObjClie.NombreCompleto;
	cout <<"\n\nTramite: ";
	Lee >> ObjClie.Tramite;
	cout << "\n\nIdentificacion: ";
	Lee >> ObjClie.ID;
	cout << "\n\nNumero de cuenta: ";
	Lee >> ObjClie.NumeroCuenta;
   
   return Lee;
}

ostream &operator<< (ostream &Escribe, Cliente &ObjClie){
   Escribe << ObjClie.NombreCompleto << "\t" << ObjClie.Tramite << "\t" << ObjClie.ID << "\t" << ObjClie.NumeroCuenta << endl;
   return Escribe;
}

ofstream &operator<<(ofstream &Escribe,Cliente & ObjClie){// Salida a archivo
    Escribe << ObjClie.NombreCompleto << "\t" << ObjClie.Tramite << "\t" << ObjClie.ID << "\t" << ObjClie.NumeroCuenta << endl;
   return Escribe; 
}

ifstream &operator>>(ifstream &Lee,Cliente & ObjClie){// Entrada de archivo a objeto
    Lee>>ObjClie.NombreCompleto;
    Lee>>ObjClie.Tramite;
    Lee>>ObjClie.ID;
    Lee>>ObjClie.NumeroCuenta;
    return Lee;
}

ColaCircular::ColaCircular(){
	Frente= -1;
	Final= -1;
	totalClientes=0;
	aux_registro=0;
}

int ColaCircular::InsertaColaCircular(Cliente Dato){
	int Resp= 0, vent=0;
	if (!ColaCircularLlena()){
		Resp= 1;
		Final= (Final +1) % MAX;
		Cola[Final]= Dato;
		registro[aux_registro]=Cola[Final];
	  	if (Frente == -1){
	  		Frente= 0;
		}
		totalClientes++;
		aux_registro++; 	
	}
	vent=Final;
	return vent;
}

int ColaCircular::EliminaColaCircular(Cliente Dato){
	int Resp= 0;
	if (!ColaCircularVacia()){
		Resp= 1;
		Dato= Cola[Frente];
		if (Frente == Final){
	    	Frente= -1;
	    	Final= -1;
		}
		else{
			Frente= (Frente + 1) % MAX;
		} 	
	}
	return Resp;
}

int ColaCircular::ColaCircularLlena(){
	if ((Final + 1) % MAX == Frente){
		return 1;
	}
	else{
		return 0;
	}
}

int ColaCircular::ColaCircularVacia(){
	if (Frente == -1){
		return 1;
	}
	else{
		return 0;
	}
}

int ColaCircular::total_clientes(){
	return 	totalClientes;
}

void ColaCircular::imprimir_archivo(){
	int i=0;
	
	time_t now;
    struct tm *now_tm;
    now = time(NULL);
    now_tm = localtime(&now);
 
	int day, mouth, year;
   	day = now_tm->tm_mday;
   	mouth = now_tm->tm_mon + 1;
   	year = now_tm->tm_year;
   	year += 1900;
 
   	string fecha;
   	string aux="_";
	string dia(std::to_string(day));
	string mes(std::to_string(mouth));
	string anio(std::to_string(year));
	
	fecha+=(anio+=aux)+=(mes+=aux)+=dia;	

	ofstream salida;
	salida.open(fecha , ios::out);//si no hay un archivo llamado asi se crea uno
	
	if(salida.fail()){
		cout<<"No se pudo abrir archivo"<<endl;
		exit(1);
	}
	
	while(i<aux_registro+1){
		salida << registro[i];
		cout<<"\n";
		i++;
	}
	salida.close();
}

void ColaCircular::mostrar(){
	if(ColaCircularVacia()==0){
		for(int i=0; i<MAX; i++){
		cout<<Cola[i];
		}
	}
	else{
		cout<<"\nCola vacia."<<endl;
	}	
}

void ColaCircular::auto_eliminacion(Cliente Dato){
	int x=0;
	srand((unsigned)time(0));
	x=(rand()%10)+5;//generacion de un numero acotado	
	sleep(x);//son 5 segundos
	EliminaColaCircular(Dato);
	cout<<"se ha eliminado un cliente de ventanilla"<<endl;
}

void ColaCircular::leer_archivo(Cliente Clie){	
	int aux=0;
	ifstream Entrada("registro.txt");
    if (!Entrada){
        cout<<"Error al abrir el archivo"<<endl;
        exit(0);
    }
	
	if(ColaCircularLlena()==1){
		cout<<"Cola llena"<<endl;
	}
	else{
		while(ColaCircularLlena()==0){
			cout<<"Insertaremos un dato del archivo a la cola"<<endl;
			Entrada>>Clie;
			InsertaColaCircular(Clie);
			if(ColaCircularLlena()==1){
				cout<<"\nCola llena\n"<<endl;
			}
		}
	}
    Entrada.close();	
}