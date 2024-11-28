#include <string>
#include <iostream>
using namespace std;

class Heap {
    private:
    struct nodoHeap {
        int id;
        int costo;
    };

    int largo;
    nodoHeap* vec;
    int ultimaPos;
    int* posPorId;
    
    void swap(int a, int b) {
        nodoHeap aux = vec[a];
        vec[a] = vec[b];
        vec[b] = aux;
        posPorId[vec[a].id] = a;
        posPorId[vec[b].id] = b;
    }

    void agregarElementoAux(int id, int costo) {
        int posRepetido = posPorId[id];
        vec[ultimaPos].id = id;
        vec[ultimaPos].costo = costo;

        if (posRepetido != 0) {
            if (costo < vec[posRepetido].costo) {
                vec[posRepetido].costo = costo;
                flotar(posRepetido);
            } else if (costo == vec[posRepetido].costo && id > vec[posRepetido].id) {
                vec[posRepetido].id = id;
                flotar(posRepetido);
            }
        } else {
            vec[ultimaPos].id = id;
            vec[ultimaPos].costo = costo;
            posPorId[id] = ultimaPos;
            flotar(ultimaPos);
            ultimaPos++;
        }
    }

    void flotar(int i) {
        while (i > 1 && (vec[i].costo < vec[i/2].costo || 
            (vec[i].costo == vec[i/2].costo && vec[i].id > vec[i/2].id))) { // costos iguales e ID nuevo mayor que id viejo
            swap(i, i/2);
            i = i / 2;
        }
    }

    void hundir(int i) {
        while (i * 2 < ultimaPos) {
            int nodoIzq = i * 2;
            int nodoDer = (i * 2) + 1;
            int masChico = i;

            if (nodoIzq < ultimaPos && (vec[nodoIzq].costo < vec[masChico].costo || (vec[nodoIzq].costo == vec[masChico].costo && vec[nodoIzq].id > vec[masChico].id))) {
                masChico = nodoIzq;
            }
            if (nodoDer < ultimaPos && (vec[nodoDer].costo < vec[masChico].costo || (vec[nodoDer].costo == vec[masChico].costo && vec[nodoDer].id > vec[masChico].id))) {
                masChico = nodoDer;
            }
            if (masChico != i) {
                swap(i, masChico);
                i = masChico;
            } else {
                break;
            }
        }
    }

    public:
    Heap(int k) {
        largo = k;
        vec = new nodoHeap [largo + 1];
        ultimaPos = 1;
        posPorId = new int [k];
    }
    
    ~Heap() {
        delete[] vec;
        delete[] posPorId;
    }

    void agregarElemento(int id, int costo){
        agregarElementoAux(id, costo);        
    };

    void pop(int k) {
        while (k > 0 && ultimaPos > 1) {
            cout << vec[1].id << endl;
            posPorId[vec[1].id] = 0;
            vec[1] = vec[ultimaPos - 1];
            posPorId[vec[1].id] = 1;
            ultimaPos--;
            hundir(1);
            k--;
        }
    }
};