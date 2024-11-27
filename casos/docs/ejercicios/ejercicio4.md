# Ejercicio 4 - Comida rápida

## Descripción

Una cadena de comida rapida le pide implementar el sistema para gestionar los pedidos y que cada uno se entregue en tiempo y forma. Para ello se pide un algoritmo que permita ordenar los pedidos de mas importante a menos importante.

Algo que hay que tener en cuenta es que no todos los pedidos son iguales. Si le piden una hamburguesa `BigORT`, dado que es más popular se espera que esta salga antes que una `ORTastySignature`. Ademas de esto, si un cliente decide que el pedido sea para llevar, este pedido se debe priorizar frente a otros que sean para comer en el lugar, y puede tomar esta decisión en cualquier momento. Es decir, si dos pedidos tienen la misma prioridad, se debe entregar primero el que sea para llevar. En caso que dos pedidos tengan la misma prioridad y sean para llevar (o para comer en el lugar), se debe entregar primero el que tenga id más bajo.

Se le pide que implemente una función que reciba una lista de pedidos y los ordene de acuerdo a las reglas mencionadas anteriormente. Teniendo en cuenta que los pedidos se pueden ir entregando, con lo que hay que tener en cuenta que si un pedido se entrega, este debe ser eliminado de la lista de pedidos.

Se pide que implemente el sistema de tal forma que al final de la operacion, se sepa qué pedidos faltan por entregar, desde el más importante al menos importante.

## Entrada

La entrada consiste en una lista de operaciones, estas son de tres tipos:

- Ingresar pedido: `I <id> <prioridad> <para-llevar> <items>`
- Entregar pedido: `E <id>`
- Cambiar pedido a "para llevar": `C <id>`

De tal forma que la entrada esta compuesta por un `N` que indica la cantidad de pedidos, seguido de un `O` que indica la cantidad de operaciones a realizar, seguido de `O` operaciones.

```plaintext
N
O
Operacion1
Operacion2
...
OperacionO
```

## Salida

La salida debe ser una lista de pedidos que faltan por entregar, ordenados de más importante a menos importante.

```plaintext
<id> <prioridad> <para-llevar> <items>
<id> <prioridad> <para-llevar> <items>
...
<id> <prioridad> <para-llevar> <items>
```

## Restricciones

- $1 \leq N \leq 10^5$
- $1 \leq id \leq 10^5$
- $1 \leq O \leq 2*10^5$
- Caso promedio: $O(N\ log N)$
- Caso peor: $O(N^2)$

## Ejemplo

### Input

```plaintext
4
7
I 1 1 true BigORT
I 2 2 false ORTastySignature_PapasChicas
I 3 4 true BigORT
E 1
C 2
I 4 2 false BigORT
E 3
```

### Output

```plaintext
2 2 true ORTastySignature_PapasChicas
4 2 false BigORT
```
