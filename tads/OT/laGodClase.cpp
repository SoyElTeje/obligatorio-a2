#include <string>
#include <iostream>

using namespace std;

struct nodoHeap {
    int idNodo ;
    int costoLlegada; // Costo de la posicion actual de IMF en llegar a la ciudad de la misión
};

struct nodoLista {
    int idMision;
    nodoLista* sig;
};

class Lista {
    private:
    nodoLista* cabeza;

    public:
    Lista () {
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
        nuevo->sig = NULL;

        nodoLista* aux = cabeza;
        nuevo->sig = aux;
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

    int getIdMision() {
        if (cabeza != NULL) {
            return cabeza->idMision;
        }
        return -1;
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
        while (i > 1 && heap[i].costoLlegada < heap[i/2].costoLlegada || (heap[i].costoLlegada == heap[i/2].costoLlegada && heap[i].idNodo  < heap[i/2].idNodo )) {
            swap(i, i/2);
            i = i / 2;
        }
    }

    void hundir(int i) {
        int menor = i;
        int izq = i * 2;
        int der = i * 2 + 1;

        if (izq < ultimoElemento && (heap[izq].costoLlegada < heap[menor].costoLlegada || (heap[izq].costoLlegada == heap[menor].costoLlegada && heap[izq].idNodo < heap[menor].idNodo))) {
            menor = izq;
        }
        if (der < ultimoElemento && (heap[der].costoLlegada < heap[menor].costoLlegada || (heap[der].costoLlegada == heap[menor].costoLlegada && heap[der].idNodo < heap[menor].idNodo))) {
            menor = der;
        }
        if (menor != i) {
            swap(i, menor);
            hundir(menor);
        }
    }

    public:
    Heap(int cantidadElementos) {
        heap = new nodoHeap[cantidadElementos + 2];
        ultimoElemento = 1;
    }

    ~Heap() {
        delete[] heap;
    }

    void insertar(int idNodo, int costoLlegada) {
        heap[ultimoElemento].idNodo  = idNodo ;
        heap[ultimoElemento].costoLlegada = costoLlegada;
        
        flotar(ultimoElemento);
        ultimoElemento++;
    }

    //PRE: el heap no está vacío
    nodoHeap minimo() {
        nodoHeap min = heap[1];
        heap[1] = heap[ultimoElemento - 1];
        ultimoElemento--;
        hundir(1);
        return min;
    }

    bool estaVacio() {
        return ultimoElemento == 1;
    }
};

class GrafoCiudad {
    private:
    struct ciudadAdyacente {
        int idMision;
        int peso; // Peso de ir de la ciudad a este adyacente
        ciudadAdyacente* sig;
    };

    struct nodoCiudad {
        string nombreCiudad;
        ciudadAdyacente* adyacentes;
    };
    
    int cantCiudades;
    nodoCiudad* vecCiudades;

    void insertarAdy (nodoCiudad* ciudadSalida, int idLlegada, int peso) {
        ciudadAdyacente* nuevoAdyacente = new ciudadAdyacente;
        nuevoAdyacente->idMision = idLlegada;
        nuevoAdyacente->peso = peso;
        nuevoAdyacente->sig = NULL;
        

        if (ciudadSalida->adyacentes == NULL) {
            ciudadSalida->adyacentes = nuevoAdyacente;
        } else {
            ciudadAdyacente* aux = ciudadSalida->adyacentes;
            nuevoAdyacente->sig = aux;
            ciudadSalida->adyacentes = nuevoAdyacente;
        }
    }

    public:
    GrafoCiudad (int cantidadElementos) {
        cantCiudades = cantidadElementos;
        vecCiudades = new nodoCiudad [cantCiudades + 1];
        for (int i = 1; i <= cantCiudades; i++) {
            vecCiudades[i].nombreCiudad = "";
            vecCiudades[i].adyacentes = NULL;
        }
    }

    ~GrafoCiudad () {
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

    void insertarCiudad (string nombreCiu, int idCiudad) {
        vecCiudades[idCiudad].nombreCiudad = nombreCiu;
    }

    void agregarConexionCiudad (int idSalida, int idLlegada, int peso) {
        insertarAdy(&vecCiudades[idSalida], idLlegada, peso);
    }

    ciudadAdyacente* ciudadesAdyacentes (int idCiudad) {
        return vecCiudades[idCiudad].adyacentes;
    }

    string obtenerNombreCiudad(int posIMF) {
        return vecCiudades[posIMF].nombreCiudad;
    }

    int* dijkstra(int posIMF) {
        bool* visitados = new bool [cantCiudades + 1];
        int* costos = new int [cantCiudades + 1];
        int* vengoDe = new int [cantCiudades + 1]; // No es necesario pero lo dejo por si hay que implementar algo en la defensa

        for (int i = 1; i <= cantCiudades; i++) {
            visitados[i] = false;
            costos[i] = INT_MAX;
            vengoDe[i] = -1;
        }
        
        costos[posIMF] = 0;

        Heap* cp = new Heap(cantCiudades);
        cp->insertar(posIMF, 0);

        while (!cp->estaVacio()) {
            nodoHeap actual = cp->minimo();
            int ciudadActual = actual.idNodo;

            visitados[ciudadActual] = true;

            ciudadAdyacente* adyacente = vecCiudades[ciudadActual].adyacentes;
            while (adyacente != NULL) {
                int ciudadAdyacente = adyacente->idMision;
                int peso = adyacente->peso;

                if (!visitados[ciudadAdyacente] && costos[ciudadAdyacente] > costos[ciudadActual] + peso) {
                    costos[ciudadAdyacente] = costos[ciudadActual] + peso;
                    vengoDe[ciudadAdyacente] = ciudadActual;
                    cp->insertar(ciudadAdyacente, costos[ciudadAdyacente]);
                }

                adyacente = adyacente->sig;
            }
        }

        delete[] visitados;
        delete[] vengoDe;
        delete cp;

        return costos;
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
    GrafoMision (int cantidadElementos) {
        cantMisiones = cantidadElementos;
        vecMisiones = new nodoMision[cantMisiones + 1];
        for (int i = 1; i <= cantMisiones; i++) {
            vecMisiones[i].idCiudad = 0;
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


    void agregarMision (int idMision, string nombreMision, int idCiudad) {
        vecMisiones[idMision].nombreMision = nombreMision;
        vecMisiones[idMision].idCiudad = idCiudad;
    }

    void agregarDependientes (int idMision, int idDependiente) {
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

    string getNombreMision (int idMision) {
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
        int* costos = grafoCiudades->dijkstra(posicionIMF);
        Heap* misionesSinDependencias = grafoMisiones->noEntrantes(costos);

        while (!misionesSinDependencias->estaVacio()) {
            nodoHeap misionActual = misionesSinDependencias->minimo();
            int idMision = misionActual.idNodo;
            int idCiudadMision = grafoMisiones->getCiudad(idMision);
            
            ordenTopologico->insertar(idMision);

            posicionIMF = idCiudadMision;
            delete[] costos;
            costos = grafoCiudades->dijkstra(posicionIMF);

            Lista* dependientes = grafoMisiones->nodosDependientes(idMision);
            
            while (!dependientes->estaVacia()) {
                int misionDependiente = dependientes->quitar();
                grafoMisiones->decrementarGrado(misionDependiente);
                if (grafoMisiones->gradoEntrada(misionDependiente) == 0) {
                    int costoViaje = costos[grafoMisiones->getCiudad(misionDependiente)];
                    misionesSinDependencias->insertar(misionDependiente, costoViaje);
                }
            }

        }

        delete[] costos;
        delete misionesSinDependencias;
        return ordenTopologico;
    }

    nodoLista* obtenerCabeza() {
        return ordenTopologico->getCabeza();
    }
};