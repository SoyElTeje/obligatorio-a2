#include <string>
#include <iostream>
using namespace std;

struct jugador {
    int ritmo;
    int tiro;
    int pase;
    int regate;
    int defensa;
    int fisico;
    string formaFisica;
    int salario;
    string extranjero;
    string confianza;
    int valoracion;
};

class DP {
    private:
    int cantidadJugadores;
    jugador* jugadores;
    int jugadoresInsertados = 0;
    int presupuesto;
    int maxExtranjeros;

    public:
    DP(int cantJugadores) {
        cantidadJugadores = cantJugadores;
        jugadores = new jugador [cantidadJugadores];
    }

    void agregarJugador(int ritmo, int tiro, int pase, int regate, int defensa, int fisico, string formaFisica, int salario, string extranjero, string confianza) {
        jugadores[jugadoresInsertados].ritmo = ritmo;
        jugadores[jugadoresInsertados].tiro = tiro;
        jugadores[jugadoresInsertados].pase = pase;
        jugadores[jugadoresInsertados].regate = regate;
        jugadores[jugadoresInsertados].defensa = defensa;
        jugadores[jugadoresInsertados].fisico = fisico;
        jugadores[jugadoresInsertados].formaFisica = formaFisica;
        jugadores[jugadoresInsertados].salario = salario;
        jugadores[jugadoresInsertados].extranjero = extranjero;
        jugadores[jugadoresInsertados].confianza = confianza;
        jugadores[jugadoresInsertados].valoracion = (ritmo + tiro + pase + regate + defensa + fisico) / 6;
        if (confianza == "Baja") {
            jugadores[jugadoresInsertados].valoracion -= 5;
        } else if (confianza == "Regular") {
            jugadores[jugadoresInsertados].valoracion -= 0;
        } else if (confianza == "Alta") {
            jugadores[jugadoresInsertados].valoracion += 5;
        }

        if (formaFisica == "Lesionado") {
            jugadores[jugadoresInsertados].valoracion = 0;
        } else if (formaFisica == "Mala") {
            jugadores[jugadoresInsertados].valoracion -= 5;
        } else if (formaFisica == "Buena") {
            jugadores[jugadoresInsertados].valoracion += 5;
        }
        jugadoresInsertados++;
    }

    int calcularValoracion(int presupuesto, int maxExtranjeros) {
        int**** dp = new int*** [cantidadJugadores + 1]; // Mochila de 4 dimensiones
        for (int i = 0; i <= cantidadJugadores; i++) {
            dp[i] = new int** [presupuesto + 1];
            for (int j = 0; j <= presupuesto; j++) {
                dp[i][j] = new int* [maxExtranjeros + 1];
                for (int k = 0; k <= maxExtranjeros; k++) {
                    dp[i][j][k] = new int[12];
                    for (int n = 0; n <= 11; n++) {
                        dp[i][j][k][n] = 0;
                    }
                }
            }
        }

        // Caso base: 0 jugadores seleccionados tienen valor 0
        for (int pActual = 0; pActual <= presupuesto; pActual++) {
            for (int eActual = 0; eActual <= maxExtranjeros; eActual++) {
                dp[0][pActual][eActual][0] = 0;
            }
        }

        // Llenamos la tabla DP
        for (int i = 1; i <= cantidadJugadores; i++) {
            int valor = jugadores[i - 1].valoracion;
            int salario = jugadores[i - 1].salario;
            int esExtranjero = (jugadores[i - 1].extranjero == "Si") ? 1 : 0;

            for (int pActual = 0; pActual <= presupuesto; pActual++) {
                for (int eActual = 0; eActual <= maxExtranjeros; eActual++) {
                    for (int n = 0; n <= 11; n++) {
                        // Caso 1: No seleccionamos al jugador actual
                        dp[i][pActual][eActual][n] = dp[i - 1][pActual][eActual][n];

                        // Caso 2: Seleccionamos al jugador actual (si cumple restricciones)
                        if (n > 0 && pActual >= salario && eActual >= esExtranjero) {
                            dp[i][pActual][eActual][n] = max(dp[i][pActual][eActual][n],
                                dp[i - 1][pActual - salario][eActual - esExtranjero][n - 1] + valor);
                        }
                    }
                }
            }
        }

        // La respuesta es el mejor valor para 11 jugadores seleccionados
        int maxValoracion = 0;
        for (int pActual = 0; pActual <= presupuesto; pActual++) {
            for (int eActual = 0; eActual <= maxExtranjeros; eActual++) {
                maxValoracion = max(maxValoracion, dp[cantidadJugadores][pActual][eActual][11]);
            }
        }
        // Retornamos el promedio de valoración
        return maxValoracion / 11;
    }
};