# Ejercicio 3 - Amueblando la casa

## Descripción

Usted esta en el proceso de amueblar su casa. Compro una estanteria pero quedó muy vacia. Entonces decide comprar objetos para decorarla. Dado que amueblar una casa es muy costoso, usted decide comprar objetos que sean baratos. Pero no quiere repetir objetos. El problema es que la tienda lista los objetos varias veces (por ejemplo, si hay un objeto de 3 colores distintos, lo lista 3 veces, y no necesariamente con el mismo precio).

Dada una lista de objetos con sus precios y sus identificadores, usted debe seleccionar los K objetos más baratos y mostrarlos en orden de precio ascendente.

## Entrada

La entrada comienza con un entero `N` que indica la cantidad de objetos en la tienda. Luego siguen `N` lineas, cada una con un entero `id` y un entero `precio` separados por un espacio. `id` es el identificador del objeto y `precio` es el precio del objeto. Luego sigue un entero `K` que indica la cantidad de objetos que usted debe seleccionar.

En caso de que haya mas de un objeto con el mismo precio, se debe seleccionar el objeto con el `id` más grande.

## Salida

Debe mostrar los `K` objetos más baratos en orden de precio ascendente. Cada `id` debe ser mostrado en una linea distinta.

## Restricciones

- 1 <= N <= 10^5
- 1 <= K <= 100
- K siempre será menor o igual a la cantidad de objetos unicos
- 1 <= id <= N
- $O(N\ logN)_{pc}$

## Ejemplo

### Input

```plaintext
5
1 10
2 5
3 5
4 15
3 2
3
```

### Output

```plaintext
3
2
1
```

### Explicación

El objeto 3 es el más barato, la opción de 2 pesos. Luego viene el objeto 2 por 5 pesos y finalmente el objeto 1 por 10 pesos.
