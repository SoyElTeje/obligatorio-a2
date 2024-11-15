#include <iostream>
#include <stdexcept>
#include <vector>
#include <limits>

struct Arista {
    int origen;
    int destino;
    int peso;
    Arista *sig;
};

struct Posicion {
    int destino;
    int origen;
    int posicion;
};

class ColaPrioridadExtendida {
private:
    int largoTabla;
    int largo;
    Posicion** tabla;
    bool* ocupado;
    bool* borrado;
    int cantidad;
    int primeroLibre;
    Arista** vec;

    int hash1(int origen, int destino) {
        return (origen + destino) % largoTabla;
    }

    int hash2(int origen, int destino) {
        return 1 + ((origen + destino) % (largoTabla - 1));
    }

    int siguientePrimo(int n) {
        int primo = n + 1;
        while (true) {
            bool esPrimo = true;
            for (int i = 2; i * i <= primo; i++) {
                if (primo % i == 0) {
                    esPrimo = false;
                    break;
                }
            }
            if (esPrimo) {
                return primo;
            }
            primo++;
        }
    }

    void rehash() {
        int nuevoLargoTabla = siguientePrimo(largoTabla * 2);
        Posicion** nuevaTabla = new Posicion*[nuevoLargoTabla];
        bool* nuevoOcupado = new bool[nuevoLargoTabla];
        bool* nuevoBorrado = new bool[nuevoLargoTabla];

        for (int i = 0; i < nuevoLargoTabla; i++) {
            nuevaTabla[i] = nullptr;
            nuevoOcupado[i] = false;
            nuevoBorrado[i] = false;
        }

        int viejaLargoTabla = largoTabla;
        Posicion** viejaTabla = tabla;
        bool* viejoOcupado = ocupado;
        bool* viejoBorrado = borrado;

        tabla = nuevaTabla;
        ocupado = nuevoOcupado;
        borrado = nuevoBorrado;
        largoTabla = nuevoLargoTabla;
        cantidad = 0;

        for (int i = 0; i < viejaLargoTabla; i++) {
            if (viejoOcupado[i] && !viejoBorrado[i]) {
                insertarTabla(viejaTabla[i]->origen, viejaTabla[i]->destino, viejaTabla[i]->posicion);
                delete viejaTabla[i];
            }
        }

        delete[] viejaTabla;
        delete[] viejoOcupado;
        delete[] viejoBorrado;
    }

    bool estaLleno() {
        return primeroLibre > largo;
    }

    void insertarTabla(int origen, int destino, int posHeap) {
        if (cantidad > largoTabla * 0.7) {
            rehash();
        }
        int pos1 = hash1(origen, destino);
        int pos = pos1;
        int pos2 = hash2(origen, destino);
        int intento = 0;
        while (intento < largoTabla) {
            pos = (pos1 + intento * pos2) % largoTabla;
            if (ocupado[pos]) {
                if (tabla[pos]->origen == origen && tabla[pos]->destino == destino) {
                    // Actualiza la posición existente
                    tabla[pos]->posicion = posHeap;
                    return;
                }
            } else {
                // Inserta nueva entrada
                tabla[pos] = new Posicion();
                tabla[pos]->origen = origen;
                tabla[pos]->destino = destino;
                tabla[pos]->posicion = posHeap;
                ocupado[pos] = true;
                borrado[pos] = false;
                cantidad++;
                return;
            }
            intento++;
        }
        throw std::runtime_error("Tabla hash llena");
    }

    int recuperarPos(int origen, int destino) {
        int pos1 = hash1(origen, destino);
        int pos = pos1;
        int pos2 = hash2(origen, destino);
        int intento = 0;
        while (intento < largoTabla) {
            pos = (pos1 + intento * pos2) % largoTabla;
            if (ocupado[pos]) {
                if (tabla[pos]->origen == origen && tabla[pos]->destino == destino) {
                    return tabla[pos]->posicion;
                }
            } else if (!ocupado[pos] && !borrado[pos]) {
                // Clave no encontrada
                break;
            }
            intento++;
        }
        throw std::runtime_error("Clave no encontrada en la tabla hash");
    }

    bool comparar(int pos1, int pos2) {
        Arista* primero = vec[pos1];
        Arista* segundo = vec[pos2];
        if (primero->peso < segundo->peso) {
            return true;
        }
        if (primero->peso > segundo->peso) {
            return false;
        }
        if (primero->origen < segundo->origen) {
            return true;
        }
        if (primero->origen > segundo->origen) {
            return false;
        }
        if (primero->destino < segundo->destino) {
            return true;
        }
        if (primero->destino > segundo->destino) {
            return false;
        }
        return false;
    }

    void intercambiar(int pos1, int pos2) {
        Arista* aux = vec[pos1];
        vec[pos1] = vec[pos2];
        vec[pos2] = aux;
    }

    int padre(int pos) {
        return pos / 2;
    }

    void flotar(int pos) {
        if (pos == 1) {
            insertarTabla(vec[pos]->origen, vec[pos]->destino, pos);
            return;
        }
        int posPadre = padre(pos);
        if (comparar(pos, posPadre)) {
            intercambiar(posPadre, pos);
            // Actualiza las posiciones en la tabla hash
            insertarTabla(vec[pos]->origen, vec[pos]->destino, pos);
            insertarTabla(vec[posPadre]->origen, vec[posPadre]->destino, posPadre);
            flotar(posPadre);
        } else {
            insertarTabla(vec[pos]->origen, vec[pos]->destino, pos);
        }
    }

    void hundir(int pos) {
        int posHijoIzq = pos * 2;
        int posHijoDer = pos * 2 + 1;
        int posMenor = pos;
        if (posHijoIzq < primeroLibre && comparar(posHijoIzq, posMenor)) {
            posMenor = posHijoIzq;
        }
        if (posHijoDer < primeroLibre && comparar(posHijoDer, posMenor)) {
            posMenor = posHijoDer;
        }
        if (posMenor != pos) {
            intercambiar(pos, posMenor);
            // Actualiza las posiciones en la tabla hash
            insertarTabla(vec[pos]->origen, vec[pos]->destino, pos);
            insertarTabla(vec[posMenor]->origen, vec[posMenor]->destino, posMenor);
            hundir(posMenor);
        } else {
            insertarTabla(vec[pos]->origen, vec[pos]->destino, pos);
        }
    }

public:
    ColaPrioridadExtendida(int tam) {
        largo = tam;
        largoTabla = siguientePrimo(tam * 2);
        tabla = new Posicion*[largoTabla];
        ocupado = new bool[largoTabla];
        borrado = new bool[largoTabla];
        cantidad = 0;
        for (int i = 0; i < largoTabla; i++) {
            tabla[i] = nullptr;
            ocupado[i] = false;
            borrado[i] = false;
        }
        vec = new Arista*[tam + 1];
        primeroLibre = 1;
    }

    ~ColaPrioridadExtendida() {
        for (int i = 0; i < largoTabla; i++) {
            if (ocupado[i]) {
                delete tabla[i];
            }
        }
        delete[] tabla;
        delete[] ocupado;
        delete[] borrado;
        for (int i = 1; i < primeroLibre; i++) {
            delete vec[i];
        }
        delete[] vec;
    }

    void insertar(int origen, int destino, int peso) {
        if (estaLleno()) {
            throw std::runtime_error("Intento de inserción en tabla llena");
        }
        Arista* nuevaArista = new Arista();
        nuevaArista->origen = origen;
        nuevaArista->destino = destino;
        nuevaArista->peso = peso;
        vec[primeroLibre] = nuevaArista;
        flotar(primeroLibre);
        primeroLibre++;
    }

    void imprimirEnOrden() {
        for (int i = 1; i < primeroLibre; i++) {
            std::cout << vec[i]->origen << " " << vec[i]->destino << " " << vec[i]->peso << std::endl;
        }
    }


    void duplicarPeso(int origen, int destino) {
        int pos = recuperarPos(origen, destino);
        vec[pos]->peso *= 2;
        hundir(pos);
    }

    bool estaVacia() {
        return primeroLibre == 1;
    }

    Arista* desencolar() {
        if (estaVacia()) {
            throw std::runtime_error("Cola vacía");
        }
        Arista* resultado = vec[1];
        primeroLibre--;
        vec[1] = vec[primeroLibre];
        hundir(1);
        return resultado;
    }
};
