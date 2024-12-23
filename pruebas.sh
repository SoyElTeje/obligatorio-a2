#!/bin/bash
cantEjercicios=10

Color_Off='\033[0m'
Red='\033[0;31m'
Green='\033[0;32m'

java=false
for i in *.java; do
    if [ -f "$i" ]; then
        java=true
    fi
done

existe() {
    if [ ! -f "$1" ]; then
        return 2
    fi
}

compilar() {
    if "$java"; then
        javac Ejercicio"$1".java || {
            echo "Error de compilación. Abortando prueba"
            return 1
        }
    else
        g++ -std=c++11 ejercicio"$1".cpp -o ejercicio"$1".out || {
            echo "Error de compilación. Abortando prueba"
            return 1
        }
    fi
}

comparar() {
    echo '---------------------------'
    echo -n "$2.in.txt: "
    start=$(date +%s.%N)  # Captura el tiempo inicial en segundos con precisión decimal
    if "$java"; then
        java Ejercicio"$1" <tests/Ejercicio"$1"/"$2".in.txt >tests/Ejercicio"$1"/"$2".out.mine.txt || {
            echo "Error de ejecución"
            return 1
        }
    else
        ./ejercicio"$1".out <tests/Ejercicio"$1"/"$2".in.txt >tests/Ejercicio"$1"/"$2".out.mine.txt || {
            echo "Error de ejecución"
            return 1
        }
    fi
    end=$(date +%s.%N)  # Captura el tiempo final en segundos con precisión decimal

    # Calcula la duración en segundos
    duration=$(echo "$end - $start" | bc)

    output=$(diff --strip-trailing-cr tests/Ejercicio"$1"/"$2".out.mine.txt tests/Ejercicio"$1"/"$2".out.txt)
    if [ -z "$output" ]; then
        echo -e "${Green}OK${Color_Off} (${duration}s)"
        rm tests/Ejercicio"$1"/"$2".out.mine.txt 2>/dev/null
    else
        echo -e "${Red}ERROR${Color_Off} (${duration}s)"
    fi
}

correrPrueba() {
    if "$java"; then
        existe Ejercicio"$1".java || return 2
    else
        existe ejercicio"$1".cpp || return 2
    fi
    echo '---------------------------'
    echo "        Ejercicio $1       "
    compilar "$1" || return 1
    for i in $(ls -v tests/Ejercicio"$1"/*.in.txt); do
        nombre=$(basename "$i" .in.txt)
        comparar "$1" "$nombre"
    done
}

if [[ $# -eq 0 ]]; then
    for i in $(eval echo "{1..$cantEjercicios}"); do
        correrPrueba "$i"
    done
fi

while [[ $# -gt 0 ]]; do
    if "$java"; then
        ext="java"
        nombre="Ejercicio"
    else
        nombre="ejercicio"
        ext="cpp"
    fi
    if [[ $1 -lt 1 || $1 -gt $cantEjercicios ]]; then
        echo "Ejercicio $1: inválido / no soportado"
        shift
        continue
    fi
    correrPrueba "$1"
    if [[ $? -eq 2 ]]; then echo "No existe $nombre$1.$ext"; fi
    shift
done

rm ./*.out 2>/dev/null
