#include "definiciones.cpp"
using namespace std;
#include <limits.h>

class GrafoLista {
	private:
		Arista ** vertices;
		Arista** vertices2;
		int cantidadV;
		bool dirigido;
		bool ponderado;
		string* ciudades;
	
		void duplicarPesoArista1(int origen, int destino) {
			Arista* actual = vertices[origen];
			while (actual != NULL) {
				if (actual->destino == destino) {
					actual->peso *= 2;
					break;
				}
				actual = actual->sig;
			}

			if (!dirigido) {
				actual = vertices[destino];
				while (actual != NULL) {
					if (actual->destino == origen) {
						actual->peso *= 2;
						break;
					}
					actual = actual->sig;
				}
			}
		}

		void duplicarPesoArista2(int origen, int destino) {
			Arista* actual = vertices2[origen];
			while (actual != NULL) {
				if (actual->destino == destino) {
					actual->peso *= 2;
					break;
				}
				actual = actual->sig;
			}

			if (!dirigido) {
				actual = vertices2[destino];
				while (actual != NULL) {
					if (actual->destino == origen) {
						actual->peso *= 2;
						break;
					}
					actual = actual->sig;
				}
			}
		}

		void mitadPesoArista1(int origen, int destino) {
			Arista* actual = vertices[origen];
			while (actual != NULL) {
				if (actual->destino == destino) {
					actual->peso /= 2;
					break;
				}
				actual = actual->sig;
			}
		}

		void mitadPesoArista2(int origen, int destino) {
			Arista* actual = vertices2[origen];
			while (actual != NULL) {
				if (actual->destino == destino) {
					actual->peso /= 2;
					break;
				}
				actual = actual->sig;
			}
		}
        
	public:
		GrafoLista(int cantV, bool esDirigido, bool esPonderado = true) {
			vertices = new Arista*[cantV + 1]();
			vertices2 = new Arista*[cantV + 1]();
			cantidadV = cantV;
			dirigido = esDirigido;
			ponderado = esPonderado;
			ciudades = new string[cantV + 1];
		}

		~GrafoLista() {
			for (int i = 1; i <= cantidadV; i++) {
				Arista* actual = vertices[i];
				while (actual != nullptr) {
					Arista* temp = actual;
					actual = actual->sig;
					delete temp;
				}
				// Repetir para vertices2
				actual = vertices2[i];
				while (actual != nullptr) {
					Arista* temp = actual;
					actual = actual->sig;
					delete temp;
				}
			}
			delete[] vertices;
			delete[] vertices2;
			delete[] ciudades;
		}

		void agregarArista(int origen, int destino, int peso = 1) {
			Arista *nuevaArista = new Arista();
			nuevaArista->origen = origen;
			nuevaArista->destino = destino;
			nuevaArista->peso = peso;
			nuevaArista->sig = vertices[origen];
			vertices[origen] = nuevaArista;

			if (!dirigido) {
				Arista *inversa = new Arista();
				inversa->origen = destino;
				inversa->destino = origen;
				inversa->peso = peso;
				inversa->sig = vertices[destino];
				vertices[destino] = inversa;
			}

			Arista *nuevaArista2 = new Arista();
			nuevaArista2->origen = origen;
			nuevaArista2->destino = destino;
			nuevaArista2->peso = peso;
			nuevaArista2->sig = vertices2[origen];
			vertices2[origen] = nuevaArista2;

			if (!dirigido) {
				Arista *inversa2 = new Arista();
				inversa2->origen = destino;
				inversa2->destino = origen;
				inversa2->peso = peso;
				inversa2->sig = vertices2[destino];
				vertices2[destino] = inversa2;
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

		Arista* adyacentes2(int vertice) {
			return vertices2[vertice];
		}

		int cantidadVertices() {
			return cantidadV;
		}

		void agregarCiudad(int vertice, string ciudad) {
			ciudades[vertice] = ciudad;
		}

		int** dijkstra(int origen) {
            bool* visitados = new bool[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                visitados[i] = false;
			}
            int * costos = new int[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                costos[i] = INT_MAX;
            }
            costos[origen] = 0;
            int* vengo = new int[cantidadV + 1];
            for (int i = 1; i <= cantidadV; i++) {
                vengo[i] = -1;
            }
			vengo[origen] = origen;
            ColaPrioridadExtendida* cola = new ColaPrioridadExtendida((cantidadV + 1) * (cantidadV + 1));
            cola->insertar(origen, origen, 0);
            while (!cola->estaVacia()) {
                Arista* actual = cola->desencolar();
                visitados[actual->destino] = true;
				Arista* ady = adyacentes(actual->destino);
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

		int** dijkstra2(int origen) {
			bool* visitados = new bool[cantidadV + 1];
			for (int i = 1; i <= cantidadV; i++) {
				visitados[i] = false;
			}
			int * costos = new int[cantidadV + 1];
			for (int i = 1; i <= cantidadV; i++) {
				costos[i] = INT_MAX;
			}
			costos[origen] = 0;
			int* vengo = new int[cantidadV + 1];
			for (int i = 1; i <= cantidadV; i++) {
				vengo[i] = -1;
			}
			vengo[origen] = origen;
			ColaPrioridadExtendida* cola = new ColaPrioridadExtendida((cantidadV + 1) * (cantidadV + 1));
			cola->insertar(origen, origen, 0);
			while (!cola->estaVacia()) {
				Arista* actual = cola->desencolar();
				visitados[actual->destino] = true;
				Arista* ady = adyacentes2(actual->destino);
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
			delete cola;
			return ret;
		}

		void duplicarPesosEnCamino(int* vengo, int origen, int destino) {
			int actual = destino;
			while (actual != origen) {
				int anterior = vengo[actual];
				duplicarPesoArista1(anterior, actual);
				actual = anterior;
			}
		}

		void duplicarPesosEnCamino2(int* vengo, int origen, int destino) {
			int actual = destino;
			while (actual != origen) {
				int anterior = vengo[actual];
				duplicarPesoArista2(anterior, actual);
				actual = anterior;
			}
		}

		void queOrdenEsMejor(int origen, int entidad, int equipo, int extraccion) {
			// Paso 1: Desde el origen hasta la entidad
			int** vecEntidad = dijkstra(origen);
			int* costoEntidad = vecEntidad[0];
			int* vengoEntidad = vecEntidad[1];

			// Duplicar pesos en el camino específico
			duplicarPesosEnCamino(vengoEntidad, origen, entidad);

			// Paso 2: Desde la entidad hasta el equipo
			int** vecEquipo = dijkstra(entidad);
			int* costoEquipo = vecEquipo[0];
			int* vengoEquipo = vecEquipo[1];

			// Duplicar pesos en el camino específico
			duplicarPesosEnCamino(vengoEquipo, entidad, equipo);

			// Paso 3: Desde el equipo hasta la extracción
			int** vecExtraccion = dijkstra(equipo);
			int* costoExtraccion = vecExtraccion[0];
			int* vengoExtraccion = vecExtraccion[1];

			// Duplicar pesos en el camino específico
			duplicarPesosEnCamino(vengoExtraccion, equipo, extraccion);

			// Costo total de la primera opción
			int costoTotal = costoEntidad[entidad] + costoEquipo[equipo] + costoExtraccion[extraccion];

			// Segunda opción: Origen -> Equipo -> Entidad -> Extracción

			// Paso 1: Desde el origen hasta el equipo
			int** vecEquipo2 = dijkstra2(origen);
			int* costoEquipo2 = vecEquipo2[0];
			int* vengoEquipo2 = vecEquipo2[1];

			// Duplicar pesos en el camino específico
			duplicarPesosEnCamino2(vengoEquipo2, origen, equipo);

			// Paso 2: Desde el equipo hasta la entidad
			int** vecEntidad2 = dijkstra2(equipo);
			int* costoEntidad2 = vecEntidad2[0];
			int* vengoEntidad2 = vecEntidad2[1];

			// Duplicar pesos en el camino específico
			duplicarPesosEnCamino2(vengoEntidad2, equipo, entidad);

			// Paso 3: Desde la entidad hasta la extracción
			int** vecExtraccion2 = dijkstra2(entidad);
			int* costoExtraccion2 = vecExtraccion2[0];
			int* vengoExtraccion2 = vecExtraccion2[1];

			// Duplicar pesos en el camino específico
			duplicarPesosEnCamino2(vengoExtraccion2, entidad, extraccion);

			int costoTotal2 = costoEquipo2[equipo] + costoEntidad2[entidad] + costoExtraccion2[extraccion];

			if (costoTotal <= costoTotal2) {
				cout << "BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de " << costoTotal << endl;
				cout << "La otra opcion tiene un costo de " << costoTotal2 << endl;
				cout << "Paso 1: ";
				imprimirEnOrden(vengoEntidad, origen, entidad);
				cout << " -> Desactivar la Entidad" << endl;
				cout << "Paso 2: ";
				imprimirEnOrden(vengoEquipo, entidad, equipo);
				cout << " -> Buscar equipo" << endl;
				cout << "Paso 3: ";
				imprimirEnOrden(vengoExtraccion, equipo, extraccion);
				cout << " -> Ir a Punto de extraccion" << endl;

			} else {
				cout << "BE11, la mejor ruta es buscar equipo, Desactivar la Entidad y punto de extraccion con un costo de " << costoTotal2 << endl;
				cout << "La otra opcion tiene un costo de " << costoTotal << endl;

				// Imprimir los pasos y costos
				cout << "Paso 1: ";
				imprimirEnOrden(vengoEquipo2, origen, equipo);
				cout << " -> Buscar equipo" << endl;
				cout << "Paso 2: ";
				imprimirEnOrden(vengoEntidad2, equipo, entidad);
				cout << " -> Desactivar la Entidad" << endl;
				cout << "Paso 3: ";
				imprimirEnOrden(vengoExtraccion2, entidad, extraccion);
				cout << " -> Ir a Punto de extraccion" << endl;
			}

			delete[] costoEntidad;
			delete[] vengoEntidad;
			delete[] vecEntidad;

			delete[] costoEquipo;
			delete[] vengoEquipo;
			delete[] vecEquipo;

			delete[] costoExtraccion;
			delete[] vengoExtraccion;
			delete[] vecExtraccion;

			delete[] costoEntidad2;
			delete[] vengoEntidad2;
			delete[] vecEntidad2;

			delete[] costoEquipo2;
			delete[] vengoEquipo2;
			delete[] vecEquipo2;

			delete[] costoExtraccion2;
			delete[] vengoExtraccion2;
			delete[] vecExtraccion2;
		}


		void imprimirEnOrden(int* vengoDe, int origen, int fin) {
			if (fin == origen) {
				cout << ciudades[origen];
			} else {
				imprimirEnOrden(vengoDe, origen, vengoDe[fin]);
				cout << " -> " << ciudades[fin];
			}
		}
};