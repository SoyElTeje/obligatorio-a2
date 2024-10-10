#include <cassert>
#include <string>
#include <iostream>
using namespace std;

struct Pedido {
    int id;
    int prioridad;
    bool paraLlevar;
    string items;
};

struct Posicion {
    int id;
    int posicion;
};

class TablaHash
{
    private:
        int largo;
        Posicion** tabla;
        bool* ocupado;
        int cantidad;

        int hash1(int id) {
            const double A = 0.6180339887;
            double hashVal = id * A;
            hashVal = hashVal - int(hashVal);
            return int(hashVal * largo);
        }

        int hash2(int id) {
            return 1 + (id % (largo - 2));
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
            int nuevoLargo = siguientePrimo(largo * 2);
            Posicion** nuevaTabla = new Posicion*[nuevoLargo];
            bool* nuevoOcupado = new bool[nuevoLargo];

            for(int i = 0; i < nuevoLargo; i++) {
                nuevaTabla[i] = NULL;
                nuevoOcupado[i] = false;
            }

            for(int i = 0; i < largo; i++) {
                if(ocupado[i]) {
                    int nuevoPos1 = hash1(tabla[i]->id);
                    int nuevoPos2 = hash2(tabla[i]->id);
                    int intento = 0;
                    int nuevoPos = nuevoPos1;
                    while (nuevoOcupado[nuevoPos] && intento < nuevoLargo) {
                        intento++;
                        nuevoPos = (nuevoPos1 + intento * nuevoPos2) % nuevoLargo;
                    }
                    nuevaTabla[nuevoPos] = tabla[i];
                    nuevoOcupado[nuevoPos] = true;
                }
            }
            delete[] tabla;
            delete[] ocupado;

            tabla = nuevaTabla;
            ocupado = nuevoOcupado;
            largo = nuevoLargo;
        }

        void insertarTablaAux(int id, int posicionDelHeap) {
            double factorCarga = static_cast<double>(cantidad) / largo;
            if (factorCarga > 0.7) rehash();
            int pos1 = hash1(id);
            int pos = pos1;
            if (!ocupado[pos]) {
                tabla[pos] = new Posicion();
                tabla[pos]->id = id;
                tabla[pos]->posicion = posicionDelHeap;
                ocupado[pos] = true;
                cantidad++;
            }
            else {
                int pos2 = hash2(id);
                int intento = 1;
                while (ocupado[pos] && intento < largo && tabla[pos]->id != id) {
                    pos = (pos1 + intento * pos2) % largo;
                    intento++;
                }
                if (ocupado[pos]) {
                    if (tabla[pos]->id == id) {
                    } else {
                        throw runtime_error("Intento de inserción en tabla llena");
                    }
                } else {
                    tabla[pos] = new Posicion();
                    tabla[pos]->id = id;
                    tabla[pos]->posicion = posicionDelHeap;
                    ocupado[pos] = true;
                    cantidad++;
                }
            }
        }

        int recuperarPosPedido(int id) {
            int pos1 = hash1(id);
            int pos = pos1;
            if(ocupado[pos] && tabla[pos]->id == id) {
                return tabla[pos]->posicion;
            }
            int pos2 = hash2(id);
            int intento = 1;
            while (intento < largo) {
                pos = (pos1 + intento * pos2) % largo;
                if(ocupado[pos] && tabla[pos]->id == id) {
                    return tabla[pos]->posicion;
                }
                intento++;
            }
            throw runtime_error("pedido no encontrado");
        }

        void eliminarTablaHash(int id) {
            int pos1 = hash1(id);
            int pos = pos1;
            bool encontrado = false;

            if(ocupado[pos] && tabla[pos]->id == id) {
                encontrado = true;
            } else {
                int pos2 = hash2(id);
                int intento = 1;
                while (intento < largo) {
                    pos = (pos1 + intento * pos2) % largo;
                    if (!ocupado[pos]) {
                        break;
                    }
                    if (tabla[pos]->id == id) {
                        encontrado = true;
                        break;
                    }
                    intento++;
                }
            }

            if (encontrado) {
                delete tabla[pos];
                tabla[pos] = NULL;
                ocupado[pos] = false;
                cantidad--;
            } else {
                throw runtime_error ("pedido no encontrado");
            }
        }

    public:
        TablaHash(int tam) {
            largo = tam;
            tabla = new Posicion*[largo];
            ocupado = new bool[largo];
            cantidad = 0;
            for(int i = 0; i < largo; i++) {
                tabla[i] = NULL;
                ocupado[i] = false;
            }
        }

        ~TablaHash() {
            for(int i = 0; i < largo; i++) {
                if(ocupado[i]) {
                    delete tabla[i];
                }
            }
            delete[] tabla;
            delete[] ocupado;
        }

        void insertarTabla(int id, int posicionDelHeap) {
            insertarTablaAux(id, posicionDelHeap);
        }

        void eliminarPedido(int id) {
            eliminarTablaHash(id);
        }
};


class MinHeap{
    private:
        int capacidad;
        int primeroLibre;
        Pedido** vec;


        bool estaLleno(){
            return primeroLibre > capacidad;
        }

        bool estaVacio(){
            return primeroLibre == 1;
        }

        int padre(int pos){
            return pos / 2;
        }

        bool comparar(int posPadre, int pos){
            Pedido* primero = vec[posPadre];
            Pedido* segundo = vec[pos];
            if(primero->paraLlevar && !segundo->paraLlevar) {
                return true;
            }
            if(!primero->paraLlevar && segundo->paraLlevar) {
                return false;
            }
            if(primero->prioridad < segundo->prioridad) {
                return true;
            }
            if(primero->prioridad > segundo->prioridad) {
                return false;
            }
            if(primero->prioridad == segundo->prioridad) {
                return primero->id < segundo->id;
            }
        }

        void intercambiar(int posPadre, int pos){
            Pedido* aux = vec[posPadre];
            vec[posPadre] = vec[pos];
            vec[pos] = aux;
        }

        void flotar(int pos, int*& posicionFinal){
            if (pos == 1) {
                posicionFinal = &pos;
                return;
            };
            int posPadre = padre(pos);
            if (comparar(posPadre, pos)){
                intercambiar(posPadre, pos);
                flotar(posPadre, posicionFinal);
            }
            else {
                posicionFinal = &pos;
            }
        }

    public:
        MinHeap(int tam){
            vec = new Pedido*[tam + 1];
            primeroLibre = 1;
            capacidad = tam;
        }
        
        ~MinHeap(){
            delete[] vec;
        }

        int* insertar(Pedido* p){
            int* posicionFinal = new int;
            if(!estaLleno()) {
                vec[primeroLibre] = p;
                flotar(primeroLibre, posicionFinal);
                primeroLibre++;
            }
            else {
                posicionFinal = 0;
            }
            return posicionFinal;
        }

        void imprimir(){
            cout << "A ver si funciona" << endl;
            cout << "La capacidad es " << capacidad << endl;
            cout << "Cantidad de elementos " << primeroLibre - 1 << endl;
            for(int i = 1; i < primeroLibre; i++) {
                cout << "[" << vec[i]->id << ": " << vec[i]->items << " " << vec[i]->paraLlevar << " " << vec[i]->prioridad <<  "]" << endl;
            }
        }
};

class ColaPrioridad {
    private:
        MinHeap* heap;
        TablaHash* tabla;

    public:
        ColaPrioridad(int tam) {
            heap = new MinHeap(tam);
            tabla = new TablaHash(tam);
        }

        ~ColaPrioridad() {
            delete heap;
            delete tabla;
        }

        void agregarPedido(int id, int prioridad, bool paraLlevar, string items) {
            Pedido* nuevoPedido = new Pedido();
            nuevoPedido->id = id;
            nuevoPedido->prioridad = prioridad;
            nuevoPedido->paraLlevar = paraLlevar;
            nuevoPedido->items = items;
            int* posicionFinal = heap->insertar(nuevoPedido);
            if (posicionFinal) {
                tabla->insertarTabla(id, *posicionFinal);
            } else {
                throw runtime_error("Heap lleno");
            }
        }

        void imprimir() {
            heap->imprimir();
        }
};



/*
class ColaPrioridad
{
    private:
        Pedido* cola;
        int largo;
        int cantidad;
        Posicion** tabla;
        bool* ocupado;
    
        int hash1(int id) {
            const double A = 0.6180339887;
            double hashVal = id * A;
            hashVal = hashVal - int(hashVal);
            return int(hashVal * largo);
        }

        int hash2(int id) {
            return 1 + (id % (largo - 2));
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
        int nuevoLargo = siguientePrimo(largo * 2);
        Posicion** nuevaTabla = new Posicion*[nuevoLargo];
        bool* nuevoOcupado = new bool[nuevoLargo];

        for(int i = 0; i < nuevoLargo; i++) {
            nuevaTabla[i] = NULL;
            nuevoOcupado[i] = false;
        }

        for(int i = 0; i < largo; i++) {
            if(ocupado[i]) {
                int nuevoPos1 = hash1(tabla[i]->id);
                int nuevoPos2 = hash2(tabla[i]->id);
                int intento = 0;
                int nuevoPos = nuevoPos1;
                while (nuevoOcupado[nuevoPos] && intento < nuevoLargo) {
                    intento++;
                    nuevoPos = (nuevoPos1 + intento * nuevoPos2) % nuevoLargo;
                }
                nuevaTabla[nuevoPos] = tabla[i];
                nuevoOcupado[nuevoPos] = true;
            }
        }
        delete[] tabla;
        delete[] ocupado;

        tabla = nuevaTabla;
        ocupado = nuevoOcupado;
        largo = nuevoLargo;
    }

    void insertarTablaAux(int id, string items, int posicionDelHeap) {
        double factorCarga = static_cast<double>(cantidad) / largo;
        if (factorCarga > 0.7) rehash();
        int pos1 = hash1(id);
        int pos2 = hash2(id);
        int pos = pos1;
        if (!ocupado[pos1]) {
            int intento = 1;
            while(intento < largo && ocupado[pos]) {
                pos = (pos1 + intento * pos2) % largo;
                intento++;
            }
            if(!ocupado[pos]) {
                tabla[pos] = new Posicion();
                tabla[pos]->id = id;
                tabla[pos]->items = items;
                tabla[pos]->posicion = posicionDelHeap;
                ocupado[pos] = true;
                cantidad++;
            }
            else {
                cout << "tabla_llena" << endl;
            }
        }
    }

    void eliminarTablaHash(int id) {
        int pos1 = hash1(id);
        int pos = pos1;
        bool encontrado = false;

        if(ocupado[pos] && tabla[pos]->id == id) {
            encontrado = true;
        } else {
            int pos2 = hash2(id);
            int intento = 1;
            while (intento < largo) {
                pos = (pos1 + intento * pos2) % largo;
                if (!ocupado[pos]) {
                    break;
                }
                if (tabla[pos]->id == id) {
                    encontrado = true;
                    break;
                }
                intento++;
            }
        }

        if (encontrado) {
            delete tabla[pos];
            tabla[pos] = NULL;
            ocupado[pos] = false;
            cantidad--;
        } else {
            throw runtime_error ("pedido no encontrado");
        }
    }

    int recuperarPosicionTabla(int id) {
        int pos1 = hash1(id);
        int pos = pos1;
        if(ocupado[pos] && tabla[pos]->id == id) {
            return tabla[pos]->posicion;
        }
        int pos2 = hash2(id);
        int intento = 1;
        while (intento < largo) {
            pos = (pos1 + intento * pos2) % largo;
            if(ocupado[pos] && tabla[pos]->id == id) {
                return tabla[pos]->posicion;
            }
            intento++;
        }
        throw runtime_error("pedido no encontrado");
    }

    Pedido peek(){
        return cola[1];
    }

    void eliminarHeap() {
        cola[1] = cola[Cantidad];
        cantidad--;

    }

    void insertarHeap(Pedido p) {

    }

    void agregarPedido(int id, int prioridad, bool paraLlevar, string items) {
        Pedido* nuevoPedido = new Pedido();
        nuevoPedido->id = id;
        nuevoPedido->prioridad = prioridad;
        nuevoPedido->paraLlevar = paraLlevar;
        nuevoPedido->items = items;

    }

};
*/