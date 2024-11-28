#include <iostream>
#include "definiciones.cpp"
using namespace std;

class GrafoLista {
	private:
		Arista ** vertices;
		int cantidadV;
		bool dirigido;
		bool ponderado;

	public:
		GrafoLista(int cantV, bool esDirigido, bool esPonderado) {
			vertices = new Arista*[cantV + 1]();
			cantidadV = cantV;
			dirigido = esDirigido;
			ponderado = esPonderado;
		}

		~GrafoLista() {
			delete[] vertices;
		}

		void agregarArista(int origen, int destino, int peso = 1) {
			Arista * nuevaArista = new Arista();
			nuevaArista->destino = destino;
			nuevaArista->peso = peso;
			nuevaArista->sig = vertices[origen];
			vertices[origen] = nuevaArista;
			if (!dirigido) {
				Arista * inversa = new Arista();
				inversa->destino = origen;
				inversa->peso = peso;
				inversa->sig = vertices[destino];
				vertices[destino] = inversa;
			}
		}

		void imprimir() {
			cout << endl << "Lista de adyacencia:" << endl;
			for (int i = 1; i <= cantidadV; i++) {
				cout << i << ": ";
				Arista * actual = adyacentes(i);
				while (actual!= NULL) {
					cout << actual->destino << " ";
					if (ponderado) {
						cout << "(" << actual->peso << ") ";
					}
					if(actual->sig->sig) {
						cout << "-> ";
					}
					actual = actual->sig;
				}
				cout << endl;
			}
		}

		Arista* adyacentes(int vertice) {
			return vertices[vertice];
		}

		int cantidadVertices() {
			return cantidadV;
		}
};