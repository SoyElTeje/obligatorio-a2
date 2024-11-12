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


    void agregarElementoAux(int id, int precio) {
        vec[ultimaPos].id = id;
        vec[ultimaPos].precio = precio;

        int i = ultimaPos;
        while (i > 1 && precio < vec[i/2].precio) {
            nodoHeap aux = vec[i];
            vec[i] = vec[i/2];
            vec[i/2] = aux;
            i = i / 2;
        }
        ultimaPos++;
    }

    bool noEstaEnHeap(int id) {
        for (int i = 0; i < largo; i++) {
            if (vec[i].id == id) return false;
        }
        return true;
    }

    void pop() {
        cout << vec[1].id << endl;
        if (ultimaPos < 1) {
            return;
        }

        vec[1] = vec[ultimaPos];
        ultimaPos--;
        
        int i = 1;

        while (true) {
            int nodoIzq = i * 2;
            int nodoDer = (i * 2) + 1;
            int masChico = i;
            
            if (nodoIzq <= ultimaPos && vec[nodoIzq].precio < vec[nodoDer].precio) {
                masChico = nodoIzq;
            }
            if (nodoDer <= ultimaPos && vec[nodoIzq].precio > vec[nodoDer].precio) {
                masChico = nodoDer;
            }
            if (masChico != i) {
                nodoHeap aux = vec[i];
                vec[i] = vec[masChico];
                vec[masChico] = aux;
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
    }

    void agregarElemento(int id, int precio){
        if (noEstaEnHeap(id)) {
            agregarElementoAux(id, precio);
        }
        
    };

    void mostrtarKelementos(int k) {
        for (int i = 1; i <= k && i <= ultimaPos; i++) {
            pop();
        }
    };
};