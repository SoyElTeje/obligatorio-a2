#include <iostream>
#include <climits>
#include "grafoListaAdy.cpp"
#include "grafoMatrizAdy.cpp"
using namespace std;

int main(){
	GrafoLista * grafoLista = new GrafoLista(5, false, true);
	GrafoMatriz * grafoMatriz = new GrafoMatriz(5, false, true);
	grafoLista->agregarArista(1, 2, 5);
	grafoMatriz->agregarArista(1, 2, 5);
	grafoLista->agregarArista(1, 3, 3);
	grafoMatriz->agregarArista(1, 3, 3);
	grafoLista->agregarArista(2, 3, 2);
	grafoMatriz->agregarArista(2, 3, 2);
	grafoLista->agregarArista(3, 4, 7);
	grafoMatriz->agregarArista(3, 4, 7);
	grafoLista->agregarArista(4, 5, 1);
	grafoMatriz->agregarArista(4, 5, 1);
	grafoLista->agregarArista(5, 1, 4);
	grafoMatriz->agregarArista(5, 1, 4);
	grafoLista->imprimir();
	grafoMatriz->imprimir();

	return 0;
}