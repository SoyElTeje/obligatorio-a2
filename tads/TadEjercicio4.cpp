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
        int largoTabla;
        int largo;
        Posicion** tabla;
        bool* ocupado;
        bool* borrado;
        int cantidad;
        int primeroLibre;
        Pedido** vec;

        int hash1(int id) {
            return id % largoTabla;
        }

        int hash2(int id) {
            return 1 + (id % (largoTabla - 1));
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
            int viejoLargo = largoTabla;
            int nuevoLargo = siguientePrimo(largoTabla * 2);
            Posicion** nueva = new Posicion*[nuevoLargo];
            bool* nuevoOcupado = new bool[nuevoLargo];
            bool* nuevoBorrado = new bool[nuevoLargo];
            for(int i = 0; i < nuevoLargo; i++) {
                nueva[i] = NULL;
                nuevoOcupado[i] = false;
                nuevoBorrado[i] = false;
            }
            for(int i = 0; i < viejoLargo; i++) {
                if(ocupado[i]) {
                    int id = tabla[i]->id;
                    int posicion = tabla[i]->posicion;
                    int pos1 = hash1(id);
                    int pos = pos1;
                    if (!nuevoOcupado[pos]) {
                        nueva[pos] = new Posicion();
                        nueva[pos]->id = id;
                        nueva[pos]->posicion = posicion;
                        nuevoOcupado[pos] = true;
                    }
                    else {
                        int pos2 = hash2(id);
                        int intento = 1;
                        while (nuevoOcupado[pos] && intento < nuevoLargo && nueva[pos]->id != id) {
                            pos = (pos1 + intento * pos2) % nuevoLargo;
                            intento++;
                        }
                        if (nuevoOcupado[pos]) {
                            if (nueva[pos]->id == id) {
                                nueva[pos]->posicion = posicion;
                            } else {
                                throw runtime_error("Intento de inserción en tabla llena");
                            }
                        } else {
                            nueva[pos] = new Posicion();
                            nueva[pos]->id = id;
                            nueva[pos]->posicion = posicion;
                            nuevoOcupado[pos] = true;
                        }
                    }
                }
            }
            for (int i = 0; i < viejoLargo; i++) {
                if (ocupado[i]) {
                    delete tabla[i];
                }
            }
            delete[] tabla;
            delete[] ocupado;
            delete[] borrado;
            tabla = nueva;
            ocupado = nuevoOcupado;
            borrado = nuevoBorrado;
            largoTabla = nuevoLargo;
            imprimirTabla();
        }

        void imprimirTabla() {
            cout << "LARGO TABLA: " << largoTabla << endl;
            for(int i = 0; i < largoTabla; i++) {
                if(ocupado[i]) {
                    cout << "Posicion: " << i << " id: " << tabla[i]->id << " posicion: " << tabla[i]->posicion << endl;
                }
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
                while (ocupado[pos] && intento < largoTabla && tabla[pos]->id != id) {
                    pos = (pos1 + intento * pos2) % largoTabla;
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
            float factorDeCarga = static_cast<float>(cantidad) / largoTabla;
            if (factorDeCarga > 0.7) {
                rehash();
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
            while (intento < largoTabla) {
                pos = (pos1 + intento * pos2) % largoTabla;
                if(ocupado[pos] && tabla[pos]->id == id) {
                    return tabla[pos]->posicion;
                }
                if (!ocupado[pos] && !borrado[pos]) {
                    break;
                }
                intento++;
            }
            throw runtime_error("pedido no encontrado con id " + to_string(id));
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
                while (intento < largoTabla) {
                    pos = (pos1 + intento * pos2) % largoTabla;
                    if (!ocupado[pos] && !borrado[pos]) {
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
                borrado[pos] = true;
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

        bool comparar(int pos1, int pos2){
            Pedido* primero = vec[pos1];
            Pedido* segundo = vec[pos2];
            if(primero->prioridad < segundo->prioridad) {
                return true;
            }
            if(primero->prioridad > segundo->prioridad) {
                return false;
            }
            if(primero->paraLlevar && !segundo->paraLlevar) {
                return true;
            }
            if(!primero->paraLlevar && segundo->paraLlevar) {
                return false;
            }
            if(primero->prioridad == segundo->prioridad) {
                return primero->id < segundo->id;
            }
            return false;
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
            if (comparar(pos, posPadre)) {
                intercambiar(posPadre, pos);
                insertarTablaAux(vec[pos]->id, pos);
                flotar(posPadre);
            }
            else {
                insertarTablaAux(vec[pos]->id, pos);
            }
        }

        void hundir(int pos) {
            int posHijoIzq = pos * 2;
            int posHijoDer = pos * 2 + 1;
            int posMayor = pos;
            if (posHijoIzq < primeroLibre && comparar(posHijoIzq, posMayor)) {
                posMayor = posHijoIzq;
            }
            if (posHijoDer < primeroLibre && comparar(posHijoDer, posMayor)) {
                posMayor = posHijoDer;
            }
            if (posMayor != pos) {
                intercambiar(pos, posMayor);
                insertarTablaAux(vec[pos]->id, pos);
                insertarTablaAux(vec[posMayor]->id, posMayor);
                hundir(posMayor);
            }
            else {
                insertarTablaAux(vec[pos]->id, pos);
            }
        }

        int peak() {
            return vec[1]->id;
        }

    public:

        ColaPrioridad(int tam){
            largo = tam;
            largoTabla = siguientePrimo(tam * 2);
            tabla = new Posicion*[largoTabla];
            ocupado = new bool[largoTabla];
            borrado = new bool[largoTabla];
            cantidad = 0;
            for(int i = 0; i < largoTabla; i++) {
                tabla[i] = NULL;
                ocupado[i] = false;
                borrado[i] = false;
            }
            vec = new Pedido*[tam + 1];
            primeroLibre = 1;
        }

        ~ColaPrioridad(){
            for(int i = 0; i < largoTabla; i++) {
                if(ocupado[i]) {
                    delete tabla[i];
                }
            }
            delete[] tabla;
            delete[] ocupado;
            delete[] vec;
            delete[] borrado;
        }

        void insertar(Pedido* p){
            if(!estaLleno()) {
                vec[primeroLibre] = p;
                flotar(primeroLibre);
                primeroLibre++;
            }
        }

        void entregarPedido(int p) {
            int pos = recuperarPosPedido(p);
            eliminarEnTablaHash(p);
            delete vec[pos];
            vec[pos] = vec[primeroLibre - 1];
            primeroLibre--;
            if(pos < primeroLibre) {
                hundir(pos);
                flotar(pos);
                insertarTablaAux(vec[pos]->id, pos);
            }            
        }

        void hacerParaLlevar(int id) {
            int pos = recuperarPosPedido(id);
            vec[pos]->paraLlevar = true;
            flotar(pos);
        }

        void imprimirLosQueFaltan() {
            while(!estaVacio()) {
                int i = 1;
                cout << vec[i]->id << " " << vec[i]->prioridad << " " << (vec[i]->paraLlevar==1?"true":"false") << " " << vec[i]->items << endl;
                entregarPedido(vec[i]->id);
            }
        }
};