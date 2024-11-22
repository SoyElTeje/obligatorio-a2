# Ejercicio 7 - Distribución Óptima de Canciones

## Descripción

Luego de un semestre agotador, su profesor decide invitar al grupo completo a una estadía en una finca. Sin embargo, al llegar se dan cuenta de que el verdadero propósito del viaje es someterlos a una prueba: tendrán que escuchar una larga lista de canciones. 

Para minimizar el sufrimiento colectivo, el profesor les permite distribuir las canciones entre los estudiantes, siguiendo ciertas reglas:

- Recibirán una lista de canciones, representadas por la duración en segundos de cada una.
- Cada estudiante puede elegir la cantidad de canciones que quiera, pero deben ser canciones **contiguas** en la lista y deben escucharse completamente.
- Los estudiantes pueden escuchar las canciones en paralelo (simultáneamente).

El objetivo es dividir las canciones entre los estudiantes de tal manera que el tiempo máximo del desafio sea mínimo.

> nota: Es posible que algunos estudiantes no necesiten escuchar ninguna canción si se logra una distribución óptima.

### Entrada

La entrada está compuesta por dos líneas:

- La primera línea contiene un enteros: `N` con la cantidad de canciones en la lista.
- Luego siguen `N` lineas, cada una con un entero: `t` que representa la duración en segundos de cada canción.
- Por último, un entero: `E` con la cantidad de estudiantes.

### Salida

El programa debe devolver:

- Para cada estudiante que escuche canciones, imprimir tres valores: el **tiempo total** que ese estudiante pasa escuchando, la **posición inicial** y la **posición final** (1-indexado) de las canciones asignadas.
- En la última línea, imprimir el **tiempo máximo mínimo** de escucha de cualquier estudiante.

### Restricciones

- $1 \leq N \leq 10^6$
- $1 \leq E \leq 10^4$
- La duración de cada canción está entre 1 y $10^9$.
- Es posible que algunos estudiantes no necesiten escuchar canciones si se logra la asignación óptima.
- Orden temporal de ejecución: $O(\log(T) \dot N )$, siendo $T$ la suma de las duraciones de las canciones.

### Ejemplo

#### Entrada

```plaintext
4
10
20
30
40
2
```

#### Salida

```plaintext
60 1 3
40 4 4
60
```

### Explicación

En este caso, hay 4 canciones con duraciones 10, 20, 30 y 40 segundos, y 2 estudiantes.
Las diferentes asignaciones posibles son:

- [10] - [20, 30, 40] -> duración máxima: 90
- [10, 20] - [30, 40] -> duración máxima: 70
- [10, 20, 30] - [40] -> duración máxima: 60 **óptimo**
- [10, 20, 30, 40] - [] -> duración máxima: 100
