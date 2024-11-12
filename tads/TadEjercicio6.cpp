#include "definiciones.cpp"
using namespace std;
#include <limits.h>

class GrafoLista {
	private:
		Arista ** vertices;
		int cantidadV;
		bool dirigido;
		bool ponderado;

        int* dijkstra(int origen) {
            int* visitados = new int[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                visitados[i] = INT_MAX;
            }
            visitados[origen] = 0;
            int * costos = new int[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                costos[i] = INT_MAX;
            }
            costos[origen] = 0;
            int* vengo = new int[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                vengo[i] = -1;
            }
            ColaPrioridadExtendida* cola = new ColaPrioridadExtendida(cantidadV);
            cola->insertar(origen, origen, 0);
            while (!cola->estaVacia()) {
                Arista* actual = cola->desencolar();
                if (costos[actual->destino] > costos[actual->origen] + actual->peso) {
                    costos[actual->destino] = costos[actual->origen] + actual->peso;
                    vengo[actual->destino] = actual->origen;
                    Arista* ady = adyacentes(actual->destino);
                    while (ady->sig != NULL) {
                        cola->insertar(actual->destino, ady->destino, ady->peso + costos[actual->destino]);
                        ady = ady->sig;
                    }
                }
            }
            return vengo;
        }

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
				while (actual->sig != NULL) {
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