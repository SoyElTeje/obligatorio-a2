# Ejercicio 2 - Gestión de Inventario de Biblioteca con Hash Cerrado

## Descripción

Este ejercicio es similar al [**Ejercicio 1**](/ejercicios/ejercicio1), pero en esta ocasión, utilizarás una tabla hash con hashing cerrado (también conocido como hashing con encadenamiento abierto) y resolución de colisiones mediante **doble hash**.

El sistema para gestionar el inventario de libros de una biblioteca almacenará cada libro con un número de identificación único (ID), un título, y un estado de disponibilidad (habilitado o deshabilitado). Las operaciones que se deben implementar son las mismas que en el Ejercicio 1.

## Entrada

[Idem al Ejercicio 1](/ejercicios/ejercicio1?id=entrada).

## Salida

[Idem al Ejercicio 1](/ejercicios/ejercicio1?id=salida).

## Restricciones

- `1 <= N <= 10^6`
- `1 <= ID del libro <= 10^8`
- Cada título de libro tiene una longitud máxima de 100 caracteres (sin espacios).
- La estructura de datos debe ser una tabla hash cerrada con resolución de colisiones mediante **doble hash**.
- La complejidad esperada para las operaciones de inserción, búsqueda y actualización de estado es $O(1)_{cp}$.
- La consulta (operación `COUNT`) debe realizarse en tiempo $O(1)_{pc}$.