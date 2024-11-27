# Ejercicio 10 - Jardín de flores


## Descripción:
- Se debe diseñar un jardín en una cuadrícula de tamaño N×N plantando diferentes tipos de flores. Las flores se diferencian por colores (se tiene infinitas flores de cada color). El objetivo es plantar la mayor cantidad de flores posible cumpliendo con una serie de restricciones.


## Restricciones:
- **Colores Adyacentes:** Las flores del mismo color no pueden estar en posiciones adyacentes (horizontal, vertical, diagonal).
- **Posiciones Específicas:** Algunas flores pueden ser plantadas unicamente en una fila específica.
- **Backtracking:** El algoritmo utilizado debe ser una implementación de backtracking.


## Objetivo:
- Maximizar el número de flores plantadas en la cuadrícula cumpliendo con las restricciones de colores y posiciones.


## Input:
- **int N:** Tamaño de la cuadrícula N×N.
- **int F:** Cantidad de flores diferentes.
- F tuplas (Color, fila en la que debe ser plantada en base 0) siendo -1 que no tiene restricción de posición.


## Output:
- Cantidad máxima de flores que se pueden colocar.


## Ejemplo
### Entrada
    3  
    1  
    Rojo -1

### Salida
    4
