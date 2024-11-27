#include <string>
#include <iostream>

struct nodoHeap {
    int idNodo ;
    int costoLlegada; // Costo de la posicion actual de IMF en llegar a la ciudad de la misión
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

        if (izq < ultimoElemento && heap[izq].costoLlegada < heap[menor].costoLlegada || (heap[izq].costoLlegada == heap[menor].costoLlegada && heap[izq].idNodo  < heap[menor].idNodo )) {
            menor = izq;
        }
        if (der < ultimoElemento && heap[der].costoLlegada < heap[menor].costoLlegada || (heap[der].costoLlegada == heap[menor].costoLlegada && heap[der].idNodo  < heap[menor].idNodo )) {
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