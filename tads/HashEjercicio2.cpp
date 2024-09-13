#ifndef TABLA_HASH
#define TABLA_HASH
#include <cassert>
#include <string>
#include <iostream>
using namespace std;

struct Libro {
    string id;
    string titulo;
    bool disponible;
};

class TablaHash
{
private:
    int largo;
    Libro** tabla;
    bool* ocupado;

    int hash1(string clave) {
        int hash = 0;
        for (int i = 0; i < clave.length(); i++) {
            hash += clave[i];
        }
        return hash % largo;
    }

    int hash2(string clave) {
        int hash = 0;
        for (int i = 0; i < clave.length(); i++) {
            hash += clave[i];
        }
        return (hash % (largo - 1)) + 1;
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

    void insertarAux(string id, string titulo) {
        int pos = hash1(id);
        cout << "Posicion: " << pos << endl;
        if (!ocupado[pos]) {
            tabla[pos] = new Libro();
            tabla[pos]->id = id;
            tabla[pos]->titulo = titulo;
            ocupado[pos] = true;
        }
        else {
            if(tabla[pos]->id == id) {
                tabla[pos]->titulo = titulo;
                tabla[pos]->disponible = true;
                return;
            }
            int pos2 = hash2(id);
            cout << "Posicion 2: " << pos2 << endl;
            int intento = 0;
            while (ocupado[pos] && intento < largo) {
                pos = (pos + intento * pos2) % largo;
                cout << "Posicion aux: " << pos << endl;
                intento++;
            }
            if (ocupado[pos]) {
                throw runtime_error("Intento de inserción en tabla llena");
            } else {
                tabla[pos] = new Libro();
                tabla[pos]->id = id;
                tabla[pos]->titulo = titulo;
                ocupado[pos] = true;
            }
        }
    }
    string recuperarAux(string id) {
        int pos = hash1(id);
        if(ocupado[pos] && tabla[pos]->id == id) {
            return tabla[pos]->titulo;
        }
        int pos2 = hash2(id);
        int intento = 0;
        while (ocupado[pos] && intento < largo) {
            pos = (pos + intento * pos2) % largo;
            intento++;
            if(ocupado[pos] && tabla[pos]->id == id) {
                return tabla[pos]->titulo;
            }
        }
        return "libro_no_encontrado";
    }

public:
    TablaHash(int tamano) {
        largo = this->siguientePrimo(tamano);
        tabla = new Libro*[largo];  // Cambiamos 'tamano' por 'largo'
        ocupado = new bool[largo];  // Cambiamos 'tamano' por 'largo'
        for (int i = 0; i < largo; i++) {  // Usamos 'largo' en lugar de 'tamano'
            tabla[i] = nullptr;
            ocupado[i] = false;
        }
    }

    ~TablaHash() {
        for (int i = 0; i < largo; i++) {
            if (tabla[i] != nullptr) {
                delete tabla[i];
            }
        }
        delete[] tabla;
        delete[] ocupado;
    }

    void insertar(string id, string titulo) {
        cout << "Insertando " << id << " - " << titulo << endl;
        insertarAux(id, titulo);
    }

    void imprimir() {
        for (int i = 0; i < largo; i++) {
            if (ocupado[i]) {
                cout << "Posicion " << i << ": " << tabla[i]->id << " - " << tabla[i]->titulo << endl;
            }
        }
    }

    string recuperar(string id) {
        return recuperarAux(id);
    }
};

#endif
