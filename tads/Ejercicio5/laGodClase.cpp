#include <string>
#include <iostream>
#include <climits>

using namespace std;

struct nodoHeap {
    int idNodo;
    int costoLlegada; // Costo de la posición actual de IMF en llegar a la ciudad de la misión
};

struct nodoLista {
    int idMision;
    nodoLista* sig;
};

class Lista {
private:
    nodoLista* cabeza;

public:
    Lista() {
        cabeza = NULL;
    }

    ~Lista() {
        while (cabeza) {
            nodoLista* aux = cabeza;
            cabeza = cabeza->sig;
            delete aux;
        }
    }

    void insertar(int idMision) {
        nodoLista* nuevo = new nodoLista;
        nuevo->idMision = idMision;
        nuevo->sig = cabeza;
        cabeza = nuevo;
    }

    int quitar() {
        if (!cabeza) {
            return -1;
        }

        int id = cabeza->idMision;
        nodoLista* aux = cabeza;
        cabeza = cabeza->sig;
        delete aux;
        return id;
    }

    bool estaVacia() {
        return cabeza == NULL;
    }

    nodoLista* getCabeza() {
        return cabeza;
    }
};

class Heap {
private:
    nodoHeap* heap;
    int ultimoElemento;

    void swap(int a, int b) {
        nodoHeap aux = heap[a];
        heap[a] = heap[b];
        heap[b] = aux;
    }

    void flotar(int i) {
        while (i > 1 && (heap[i].costoLlegada < heap[i / 2].costoLlegada ||
            (heap[i].costoLlegada == heap[i / 2].costoLlegada && heap[i].idNodo < heap[i / 2].idNodo))) {
            swap(i, i / 2);
            i = i / 2;
        }
    }

    void hundir(int i) {
        int menor = i;
        int izq = 2 * i;
        int der = 2 * i + 1;

        if (izq <= ultimoElemento && (heap[izq].costoLlegada < heap[menor].costoLlegada ||
            (heap[izq].costoLlegada == heap[menor].costoLlegada && heap[izq].idNodo < heap[menor].idNodo))) {
            menor = izq;
        }
        if (der <= ultimoElemento && (heap[der].costoLlegada < heap[menor].costoLlegada ||
            (heap[der].costoLlegada == heap[menor].costoLlegada && heap[der].idNodo < heap[menor].idNodo))) {
            menor = der;
        }
        if (menor != i) {
            swap(i, menor);
            hundir(menor);
        }
    }

public:
    Heap(int cantidadElementos) {
        heap = new nodoHeap[cantidadElementos + 1];
        ultimoElemento = 0;
    }

    ~Heap() {
        delete[] heap;
    }

    void insertar(int idNodo, int costoLlegada) {
        ultimoElemento++;
        heap[ultimoElemento].idNodo = idNodo;
        heap[ultimoElemento].costoLlegada = costoLlegada;
        flotar(ultimoElemento);
    }

    nodoHeap minimo() {
        nodoHeap min = heap[1];
        heap[1] = heap[ultimoElemento];
        ultimoElemento--;
        hundir(1);
        return min;
    }

    bool estaVacio() {
        return ultimoElemento == 0;
    }
};

class GrafoCiudad {
private:
    struct ciudadAdyacente {
        int idCiudad;
        int peso; // Peso de ir de la ciudad a este adyacente
        ciudadAdyacente* sig;
    };

    struct nodoCiudad {
        string nombreCiudad;
        ciudadAdyacente* adyacentes;
    };

    int cantCiudades;
    nodoCiudad* vecCiudades;

    void insertarAdy(nodoCiudad* ciudadSalida, int idLlegada, int peso) {
        ciudadAdyacente* nuevoAdyacente = new ciudadAdyacente;
        nuevoAdyacente->idCiudad = idLlegada;
        nuevoAdyacente->peso = peso;
        nuevoAdyacente->sig = ciudadSalida->adyacentes;
        ciudadSalida->adyacentes = nuevoAdyacente;
    }

public:
    GrafoCiudad(int cantidadElementos) {
        cantCiudades = cantidadElementos;
        vecCiudades = new nodoCiudad[cantCiudades + 1];
        for (int i = 1; i <= cantCiudades; i++) {
            vecCiudades[i].nombreCiudad = "";
            vecCiudades[i].adyacentes = NULL;
        }
    }

    ~GrafoCiudad() {
        for (int i = 1; i <= cantCiudades; i++) {
            ciudadAdyacente* adyacente = vecCiudades[i].adyacentes;
            while (adyacente != NULL) {
                ciudadAdyacente* aux = adyacente;
                adyacente = adyacente->sig;
                delete aux;
            }
        }
        delete[] vecCiudades;
    }

    void insertarCiudad(string nombreCiu, int idCiudad) {
        vecCiudades[idCiudad].nombreCiudad = nombreCiu;
    }

    void agregarConexionCiudad(int idSalida, int idLlegada, int peso) {
        insertarAdy(&vecCiudades[idSalida], idLlegada, peso);
        insertarAdy(&vecCiudades[idLlegada], idSalida, peso); // Como el tiempo es el mismo en ambos sentidos
    }

    ciudadAdyacente* ciudadesAdyacentes(int idCiudad) {
        return vecCiudades[idCiudad].adyacentes;
    }

    string obtenerNombreCiudad(int idCiudad) {
        return vecCiudades[idCiudad].nombreCiudad;
    }

    void imprimirCamino(int origen, int destino, int* vengoDe) {
        if (destino == origen) {
            cout << obtenerNombreCiudad(origen);
        } else if (vengoDe[destino] == -1) {
            cout << "No hay camino";
        } else {
            imprimirCamino(origen, vengoDe[destino], vengoDe);
            cout << " -> " << obtenerNombreCiudad(destino);
        }
    }

    void dijkstra(int origen, int* costos, int* vengoDe) {
        bool* visitados = new bool[cantCiudades + 1];
        for (int i = 1; i <= cantCiudades; i++) {
            visitados[i] = false;
            costos[i] = INT_MAX;
            vengoDe[i] = -1;
        }

        costos[origen] = 0;
        vengoDe[origen] = origen;

        Heap cp(cantCiudades);
        cp.insertar(origen, 0);

        while (!cp.estaVacio()) {
            nodoHeap actual = cp.minimo();
            int ciudadActual = actual.idNodo;

            if (visitados[ciudadActual]) continue;
            visitados[ciudadActual] = true;

            ciudadAdyacente* ady = vecCiudades[ciudadActual].adyacentes;
            while (ady != NULL) {
                int ciudadAdyacente = ady->idCiudad;
                int peso = ady->peso;

                if (!visitados[ciudadAdyacente] && costos[ciudadAdyacente] > costos[ciudadActual] + peso) {
                    costos[ciudadAdyacente] = costos[ciudadActual] + peso;
                    vengoDe[ciudadAdyacente] = ciudadActual;
                    cp.insertar(ciudadAdyacente, costos[ciudadAdyacente]);
                }

                ady = ady->sig;
            }
        }

        delete[] visitados;
    }

    int getCantCiudades() const {
        return cantCiudades;
    }
};

class GrafoMision {
private:
    struct nodoMision {
        string nombreMision;
        int gradoEntrada;
        int idCiudad;
        Lista* misionesDependientes;
    };

    int cantMisiones;
    nodoMision* vecMisiones;

public:
    GrafoMision(int cantidadElementos) {
        cantMisiones = cantidadElementos;
        vecMisiones = new nodoMision[cantMisiones + 1];
        for (int i = 1; i <= cantMisiones; i++) {
            vecMisiones[i].idCiudad = 0;
            vecMisiones[i].gradoEntrada = 0;
            vecMisiones[i].misionesDependientes = new Lista();
            vecMisiones[i].nombreMision = "";
        }
    }

    ~GrafoMision() {
        for (int i = 1; i <= cantMisiones; i++) {
            delete vecMisiones[i].misionesDependientes;
        }
        delete[] vecMisiones;
    }

    void agregarMision(int idMision, string nombreMision, int idCiudad) {
        vecMisiones[idMision].nombreMision = nombreMision;
        vecMisiones[idMision].idCiudad = idCiudad;
    }

    void agregarDependientes(int idMision, int idDependiente) {
        vecMisiones[idMision].misionesDependientes->insertar(idDependiente);
        vecMisiones[idDependiente].gradoEntrada++;
    }

    Heap* noEntrantes(int* costos) {
        Heap* grados = new Heap(cantMisiones);
        for (int i = 1; i <= cantMisiones; i++) {
            if (vecMisiones[i].gradoEntrada == 0) {
                int costoViaje = costos[vecMisiones[i].idCiudad];
                grados->insertar(i, costoViaje);
            }
        }
        return grados;
    }

    Lista* nodosDependientes(int idMision) {
        return vecMisiones[idMision].misionesDependientes;
    }

    void decrementarGrado(int idMision) {
        vecMisiones[idMision].gradoEntrada--;
    }

    int getCiudad(int idMision) {
        return vecMisiones[idMision].idCiudad;
    }

    int gradoEntrada(int idMision) {
        return vecMisiones[idMision].gradoEntrada;
    }

    string getNombreMision(int idMision) {
        return vecMisiones[idMision].nombreMision;
    }
};

class OT {
private:
    Lista* ordenTopologico;

public:
    OT() {
        ordenTopologico = new Lista;
    }

    ~OT() {
        delete ordenTopologico;
    }

    Lista* orden(GrafoMision* grafoMisiones, GrafoCiudad* grafoCiudades, int posicionIMF) {
        int numCiudades = grafoCiudades->getCantCiudades();
        int* costos = new int[numCiudades + 1];
        int* vengoDe = new int[numCiudades + 1];
        grafoCiudades->dijkstra(posicionIMF, costos, vengoDe);

        Heap* misionesSinDependencias = grafoMisiones->noEntrantes(costos);

        while (!misionesSinDependencias->estaVacio()) {
            nodoHeap misionActual = misionesSinDependencias->minimo();
            int idMision = misionActual.idNodo;
            int idCiudadMision = grafoMisiones->getCiudad(idMision);

            ordenTopologico->insertar(idMision);

            posicionIMF = idCiudadMision;
            grafoCiudades->dijkstra(posicionIMF, costos, vengoDe);

            Lista* dependientes = grafoMisiones->nodosDependientes(idMision);

            nodoLista* actual = dependientes->getCabeza();
            while (actual != NULL) {
                int misionDependiente = actual->idMision;
                grafoMisiones->decrementarGrado(misionDependiente);
                if (grafoMisiones->gradoEntrada(misionDependiente) == 0) {
                    int costoViaje = costos[grafoMisiones->getCiudad(misionDependiente)];
                    misionesSinDependencias->insertar(misionDependiente, costoViaje);
                }
                actual = actual->sig;
            }
            // No eliminamos 'dependientes' aquí ya que forma parte de 'vecMisiones'
        }

        delete[] costos;
        delete[] vengoDe;
        delete misionesSinDependencias;
        return ordenTopologico;
    }

    nodoLista* obtenerCabeza() {
        return ordenTopologico->getCabeza();
    }
};

int main() {
    // Lectura de la entrada y construcción de las estructuras de datos
    int M;
    cin >> M;

    GrafoMision* grafoMisiones = new GrafoMision(M);

    for (int i = 0; i < M; i++) {
        int idMision, idCiudad;
        string nombreMision;
        cin >> idMision >> nombreMision >> idCiudad;

        grafoMisiones->agregarMision(idMision, nombreMision, idCiudad);

        int dependencia;
        while (cin >> dependencia && dependencia != 0) {
            grafoMisiones->agregarDependientes(idMision, dependencia);
        }
    }

    int C, O;
    cin >> C >> O;

    GrafoCiudad* grafoCiudades = new GrafoCiudad(C);

    for (int i = 0; i < C; i++) {
        int idCiudad;
        string nombreCiudad;
        cin >> idCiudad >> nombreCiudad;
        grafoCiudades->insertarCiudad(nombreCiudad, idCiudad);
    }

    int idSalida, idLlegada, tiempo;
    while (cin >> idSalida >> idLlegada >> tiempo) {
        grafoCiudades->agregarConexionCiudad(idSalida, idLlegada, tiempo);
    }

    OT ot;
    Lista* ordenMisiones = ot.orden(grafoMisiones, grafoCiudades, O);

    // Salida de los resultados
    cout << "Ciudad inicial: " << grafoCiudades->obtenerNombreCiudad(O) << endl;

    int posicionIMF = O;
    int tiempoTotal = 0;

    nodoLista* actualMision = ordenMisiones->getCabeza();
    while (actualMision != NULL) {
        int idMision = actualMision->idMision;
        int idCiudadMision = grafoMisiones->getCiudad(idMision);
        string nombreMision = grafoMisiones->getNombreMision(idMision);
        string nombreCiudad = grafoCiudades->obtenerNombreCiudad(idCiudadMision);

        int numCiudades = grafoCiudades->getCantCiudades();
        int* costos = new int[numCiudades + 1];
        int* vengoDe = new int[numCiudades + 1];
        grafoCiudades->dijkstra(posicionIMF, costos, vengoDe);

        grafoCiudades->imprimirCamino(posicionIMF, idCiudadMision, vengoDe);
        cout << " -> Mision: " << nombreMision << " - " << nombreCiudad << " - Tiempo de viaje: " << costos[idCiudadMision] << endl;

        tiempoTotal += costos[idCiudadMision];
        posicionIMF = idCiudadMision;

        delete[] costos;
        delete[] vengoDe;

        actualMision = actualMision->sig;
    }

    cout << "Misiones ejecutadas con exito." << endl;
    cout << "Tiempo total de viaje: " << tiempoTotal << endl;

    // Liberación de memoria
    delete grafoMisiones;
    delete grafoCiudades;

    return 0;
}
