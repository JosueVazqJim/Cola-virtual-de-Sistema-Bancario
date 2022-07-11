#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <fstream>
#include <iomanip>

using namespace std;

#define MAX 3

class Cliente{
	private:
		char NombreCompleto[64], Tramite[64], ID[64], NumeroCuenta[64];
	public:
		Cliente();
		Cliente(char[], char[], char[], char[]);
		friend ostream &operator<<(ostream &Escribe, Cliente &ObjClie);
		friend istream &operator>>(istream &Lee, Cliente &ObjClie);
		
		friend ifstream &operator>>(ifstream &Lee,Cliente & ObjClie); //estos sirven para imprimir en el archivo
	    friend ofstream &operator<<(ofstream &Escribe,Cliente & ObjClie);
};

class ColaCircular{
	private:
		Cliente Cola[MAX];
		Cliente registro[100];
		int Frente, Final, totalClientes, aux_registro;
	public:
		ColaCircular();
		int InsertaColaCircular(Cliente Dato);
		int EliminaColaCircular(Cliente Dato);
		int ColaCircularLlena();
		int ColaCircularVacia();
		int total_clientes();
		void imprimir_archivo();
		void auto_eliminacion(Cliente Dato);
		
		void leer_archivo(Cliente Clie);
		void mostrar();
};