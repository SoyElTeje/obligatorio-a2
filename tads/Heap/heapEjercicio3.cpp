#include <string>
#include <iostream>
using namespace std;

class Heap {
    private:
    struct nodoHeap {
        int id;
        int precio;
    };

    int largo;
    nodoHeap* vec;
    int ultimaPos;

    void swap(nodoHeap &a, nodoHeap &b) {
        nodoHeap aux = a;
        a = b;
        b = aux;
    }

    void agregarElementoAux(int id, int precio) {
        int posRepetido = estaEnHeap(id);
        vec[ultimaPos].id = id;
        vec[ultimaPos].precio = precio;

        if (posRepetido != 0) {
            if (precio < vec[posRepetido].precio) {
                vec[posRepetido].precio = precio;
                flotar(posRepetido);
            } else if (precio == vec[posRepetido].precio && id > vec[posRepetido].id) {
                vec[posRepetido].id = id;
                flotar(posRepetido);
            }
        } else {
            vec[ultimaPos].id = id;
            vec[ultimaPos].precio = precio;
            flotar(ultimaPos);
            ultimaPos++;
        }
    }

    void flotar(int i) {
        while (i > 1 && (vec[i].precio < vec[i/2].precio || 
            (vec[i].precio == vec[i/2].precio && vec[i].id > vec[i/2].id))) { // precios iguales e ID nuevo mayor que id viejo
            swap(vec[i], vec[i/2]);
            i = i / 2;
        }
    }

    void hundir(int i) {
        while (i * 2 < ultimaPos) {
            int nodoIzq = i * 2;
            int nodoDer = (i * 2) + 1;
            int masChico = i;

            if (nodoIzq < ultimaPos && (vec[nodoIzq].precio < vec[masChico].precio || (vec[nodoIzq].precio == vec[masChico].precio && vec[nodoIzq].id > vec[masChico].id))) {
                masChico = nodoIzq;
            }
            if (nodoDer < ultimaPos && (vec[nodoDer].precio < vec[masChico].precio ||
                (vec[nodoDer].precio == vec[masChico].precio && vec[nodoDer].id > vec[masChico].id))) {
                masChico = nodoDer;
            }
            if (masChico != i) {
                swap(vec[i], vec[masChico]);
                i = masChico;
            } else {
                break;
            }
        }
    }

    int estaEnHeap(int id) {
        for (int i = 1; i < ultimaPos; i++) {
            if (vec[i].id == id) return i;
        }
        return 0;
    }

    void pop(int k) {
        while (k > 0 && ultimaPos > 1) {
            cout << vec[1].id << endl;
            vec[1] = vec[ultimaPos - 1];
            ultimaPos--;
            hundir(1);
            k--;
        }
    }

    public:
    Heap(int k) {
        largo = k;
        vec = new nodoHeap [largo + 1];
        ultimaPos = 1;
    }

    void agregarElemento(int id, int precio){
        agregarElementoAux(id, precio);        
    };

    void mostrtarKelementos(int k) {
        pop(k);
    };
};