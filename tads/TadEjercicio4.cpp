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

class ColaPrioridad {
    private:
        int largo;
        Posicion** tabla;
        bool* ocupado;
        int cantidad;
        int primeroLibre;
        Pedido** vec;

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

        void insertarTablaAux(int id, int posicionDelHeap) {
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
                        tabla[pos]->posicion = posicionDelHeap;
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

        void eliminarEnTablaHash(int id) {
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

        bool estaLleno(){
            return primeroLibre > largo;
        }

        bool estaVacio(){
            return primeroLibre == 1;
        }

        int padre(int pos){
            return pos / 2;
        }

        bool comparar(int posPadre, int pos){
            Pedido* padre = vec[posPadre];
            Pedido* hijo = vec[pos];
            if(padre->paraLlevar && !padre->paraLlevar) {
                return false;
            }
            if(!padre->paraLlevar && hijo->paraLlevar) {
                return true;
            }
            if(padre->prioridad < hijo->prioridad) {
                return true;
            }
            if(padre->prioridad > hijo->prioridad) {
                return false;
            }
            if(padre->prioridad == hijo->prioridad) {
                return padre->id > hijo->id;
            }
        }

        void intercambiar(int posPadre, int pos){
            Pedido* aux = vec[posPadre];
            vec[posPadre] = vec[pos];
            vec[pos] = aux;
        }

        void flotar(int pos){
            if (pos == 1) {
                insertarTablaAux(vec[pos]->id, pos);
                return;
            };
            int posPadre = padre(pos);
            if (comparar(posPadre, pos)){
                intercambiar(posPadre, pos);
                insertarTablaAux(vec[pos]->id, pos);
                flotar(posPadre);
            }
            else {
                insertarTablaAux(vec[pos]->id, pos);
            }
        }

        void hundir(int pos){
            int posHijoIzq = pos * 2;
            int posHijoDer = pos * 2 + 1;
            if (posHijoIzq >= primeroLibre) {
                return;
            }
            if (posHijoDer >= primeroLibre) {
                if (comparar(pos, posHijoIzq)) {
                    intercambiar(pos, posHijoIzq);
                    insertarTablaAux(vec[pos]->id, pos);
                    insertarTablaAux(vec[posHijoIzq]->id, posHijoIzq);
                    hundir(posHijoIzq);
                }
                else {
                    insertarTablaAux(vec[pos]->id, pos);
                }
                return;
            }
            if (comparar(posHijoIzq, posHijoDer)) {
                if (comparar(pos, posHijoIzq)) {
                    intercambiar(pos, posHijoIzq);
                    insertarTablaAux(vec[pos]->id, pos);
                    insertarTablaAux(vec[posHijoIzq]->id, posHijoIzq);
                    hundir(posHijoIzq);
                }
                else {
                    insertarTablaAux(vec[pos]->id, pos);
                }
            }
            else {
                if (comparar(pos, posHijoDer)) {
                    intercambiar(pos, posHijoDer);
                    insertarTablaAux(vec[pos]->id, pos);
                    insertarTablaAux(vec[posHijoDer]->id, posHijoDer);
                    hundir(posHijoDer);
                }
                else {
                    insertarTablaAux(vec[pos]->id, pos);
                }
            }
        }

    public:

        ColaPrioridad(int tam){
            largo = tam;
            tabla = new Posicion*[largo];
            ocupado = new bool[largo];
            cantidad = 0;
            for(int i = 0; i < largo; i++) {
                tabla[i] = NULL;
                ocupado[i] = false;
            }
            vec = new Pedido*[tam + 1];
            primeroLibre = 1;
        }

        ~ColaPrioridad(){
            for(int i = 0; i < largo; i++) {
                if(ocupado[i]) {
                    delete tabla[i];
                }
            }
            delete[] tabla;
            delete[] ocupado;
            delete[] vec;
        }

        void insertar(Pedido* p){
            if(!estaLleno()) {
                vec[primeroLibre] = p;
                flotar(primeroLibre);
                primeroLibre++;
            }
        }

        void imprimir() {
            cout << "La capacidad es " << largo << endl;
            cout << "Cantidad de elementos " << primeroLibre - 1 << endl;
            for(int i = 1; i < primeroLibre; i++) {
                cout << "[posicion del heap: " << i << " posicion en hash: " << recuperarPosPedido(vec[i]->id) << " " << vec[i]->id << ": " << vec[i]->items << " " << (vec[i]->paraLlevar?"true":"false") << " " << vec[i]->prioridad <<  "]" << endl;
            }
        }

        void entregarPedido() {
            Pedido* p = vec[1];
            cout << p->id << " " << p->prioridad << " " << (p->paraLlevar? "true" : "false") << " " << p->items << endl;
            eliminarEnTablaHash(p->id);
            vec[1] = vec[primeroLibre - 1];
            primeroLibre--;
            hundir(1);
        }

        void hacerParaLlevar(int id) {
            int pos = recuperarPosPedido(id);
            vec[pos]->paraLlevar = true;
            flotar(pos);
        }
};