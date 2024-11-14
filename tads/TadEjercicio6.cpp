#include "definiciones.cpp"
using namespace std;
#include <limits.h>

class GrafoLista {
	private:
		Arista ** vertices;
		int cantidadV;
		bool dirigido;
		bool ponderado;

        
	public:
		GrafoLista(int cantV, bool esDirigido, bool esPonderado = true) {
			vertices = new Arista*[cantV + 1]();
			cantidadV = cantV;
			dirigido = esDirigido;
			ponderado = esPonderado;
		}

		~GrafoLista() {
			delete[] vertices;
		}

		void agregarArista(int origen, int destino, int peso = 1) {
			cout << "Es dirigido: " << (dirigido ? "si" : "no") << endl;

			Arista *nuevaArista = new Arista();
			nuevaArista->origen = origen;
			nuevaArista->destino = destino;
			nuevaArista->peso = peso;
			nuevaArista->sig = vertices[origen]; // Conectar con la lista de adyacencia actual
			vertices[origen] = nuevaArista;

			if (!dirigido) {
				Arista *inversa = new Arista();
				inversa->origen = destino;
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
				Arista* actual = adyacentes(i);
				while (actual != NULL) {
					cout << actual->destino;
					if (ponderado) {
						cout << " (" << actual->peso << ")";
					}
					if (actual->sig != NULL) {
						cout << " -> ";
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

		int** dijkstra(int origen) {
            bool* visitados = new bool[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                visitados[i] = false;
            }
            visitados[origen] = false;
            int * costos = new int[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                costos[i] = INT_MAX;
            }
            costos[origen] = 0;
            int* vengo = new int[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                vengo[i] = -1;
            }
            ColaPrioridadExtendida* cola = new ColaPrioridadExtendida(cantidadV + 1);
            cola->insertar(origen, origen, 0);
            while (!cola->estaVacia()) {
                Arista* actual = cola->desencolar();
                visitados[actual->destino] = true;
				Arista* ady = adyacentes(actual->destino);
				Arista* imprimirAdy = adyacentes(actual->destino);
				while (imprimirAdy->sig != NULL) {
					cout << imprimirAdy->destino << " ";
					imprimirAdy = imprimirAdy->sig;
				}
				while (ady != NULL) {
					if(!visitados[ady->destino] && costos[actual->destino] + ady->peso < costos[ady->destino]) {
						costos[ady->destino] = costos[actual->destino] + ady->peso;
						vengo[ady->destino] = actual->destino;
						cola->insertar(actual->destino, ady->destino, costos[ady->destino]);
					}
					ady = ady->sig;
				}
            }
            int ** ret = new int*[2];
			ret[0] = costos;
			ret[1] = vengo;
			delete[] visitados;
			return ret;
        }



};