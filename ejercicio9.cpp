#include <cassert>
#include <string>
#include <iostream>
#include <limits>
#include "tads/ProgramacionDinamica/dpEj9.cpp"

using namespace std;

int main()
{
    int cantJugadores;
    cin >> cantJugadores;

    DP* jugadores = new DP(cantJugadores);

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

    for (int i = 0; i < cantJugadores; i++) {
        cin >> ritmo;
        cin >> tiro;
        cin >> pase;
        cin >> regate;
        cin >> defensa;
        cin >> fisico;
        cin >> formaFisica;
        cin >> salario;
        cin >> extranjero;
        cin >> confianza;
        jugadores->agregarJugador(ritmo, tiro, pase, regate, defensa, fisico, formaFisica, salario, extranjero, confianza);
    }


    int presupuesto;
    cin >> presupuesto;
    int maxExtranjeros;
    cin >> maxExtranjeros;

    cout << jugadores->calcularValoracion(presupuesto, maxExtranjeros) << endl;

    return 0;
}