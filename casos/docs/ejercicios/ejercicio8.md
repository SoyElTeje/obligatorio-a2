# Ejercicio 8 - Construcción de Centro de Comunicación entre Ciudades

## Descripción

Tienes un conjunto de `n` ciudades, cada una representada como un punto en un plano 2D, con coordenadas (x, y) y una población asociada. Se desea construir un centro de comunicación entre dos de estas ciudades. El objetivo es encontrar el par de ciudades entre las cuales se debe construir este centro, de manera que la suma de las distancias desde el centro hacia todas las ciudades, ponderada por sus poblaciones, sea mínima.

En este problema, la "distancia" no es simplemente la distancia euclidiana, sino una "distancia efectiva" entre dos ciudades modificada por la diferencia de población entre las ciudades. La fórmula de la distancia efectiva entre dos ciudades es la siguiente:

$$
\text{Distancia Efectiva} = \sqrt{(x2 - x1)^2 + (y2 - y1)^2} + \frac{|P2 - P1|}{\max(P2, P1)}
$$

Donde $P1$ y $P2$ son las poblaciones de las dos ciudades.

### Reglas de desempate

En caso de que dos pares de ciudades tengan la misma distancia efectiva mínima, se debe seleccionar el par con la mayor suma de poblaciones.

## Entrada

La entrada consiste en:

- Un número entero `n` que indica la cantidad de ciudades.
- `n` líneas siguientes, cada una conteniendo tres enteros: las coordenadas `x`, `y` y la población `P` de cada ciudad.

## Salida

Debes devolver el par de ciudades que minimiza la distancia efectiva en el siguiente formato:

- Primero, imprime las coordenadas `x`, `y` y la población `P` de la primera ciudad.
- Luego, imprime las coordenadas `x`, `y` y la población `P` de la segunda ciudad.

El orden en el que se imprimen las ciudades debe seguir estas reglas:
- La ciudad con menor `x` debe imprimirse primero.
- Si ambas ciudades tienen la misma `x`, se debe imprimir primero la ciudad con menor `y`.


## Restricciones

- `2 <= n <= 10^6`
- Las coordenadas `x` y `y` son números enteros entre `0` y `10^4`.
- Las poblaciones `P` son números enteros entre `1` y `10^6`.
- Se debe resolver utilizando un algoritmo de **Divide & Conquer**.