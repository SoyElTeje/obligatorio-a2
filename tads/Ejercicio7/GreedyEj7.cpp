#include <string>
#include <iostream>
using namespace std;

class GreedyCanciones {
    private:
    int cantidadCanciones;
    int cantidadEstudiantes;
    int* canciones;

    int minimoMaximoCancion() {
        int minimoMaximo = 0;
        for (int i = 0; i < cantidadCanciones; i++) {
            if (canciones[i] > minimoMaximo) {
                minimoMaximo = canciones[i];
            }
        }

        return minimoMaximo;
    }

    int maximaPosibleEscucha() {
        int maximo = 0;
        for (int i = 0; i < cantidadCanciones; i++) {
            maximo += canciones[i];
        }

        return maximo;
    }

    bool esTiempoPosible(int tiempo) {
        int estudiantesNecesarios = 1;
        int tiempoActual = 0;

        for (int i = 0; i < cantidadCanciones; i++) {
            if (tiempoActual + canciones[i] > tiempo) {
                estudiantesNecesarios++;
                tiempoActual = canciones[i];
                if (estudiantesNecesarios > cantidadEstudiantes) {
                    return false;
                }
            } else {
                tiempoActual += canciones[i];
            }
        }
        return true;
    }

    public:
    GreedyCanciones(int cantCanciones, int cantEstudiantes, int* vecCanciones) {
        cantidadCanciones = cantCanciones;
        cantidadEstudiantes = cantEstudiantes;
        canciones = vecCanciones;
    }

    ~GreedyCanciones() {
        delete[] canciones;
    }

    void calcularResultado() {
        int min = minimoMaximoCancion();
        int max = maximaPosibleEscucha();


        while (min < max) {
            int intermedio = (min + max) / 2;

            if (esTiempoPosible(intermedio)) {
                max = intermedio;
            } else {
                min = intermedio + 1;
            }
        }

        int tiempoOptimo = min;

        int tiempoActual = 0;
        int inicio = 1;
        for (int i = 0, estudiantesUsados = 1; i < cantidadCanciones; i++) {
            if (tiempoActual + canciones[i] > tiempoOptimo) {
                cout << tiempoActual << " " << inicio << " " << i << endl;
                estudiantesUsados++;
                inicio = i + 1;
                tiempoActual = canciones[i];
            } else {
                tiempoActual += canciones[i];
            }
        }

        cout << tiempoActual << " " << inicio << " " << cantidadCanciones << endl;
        cout << tiempoOptimo << endl;
    }
};