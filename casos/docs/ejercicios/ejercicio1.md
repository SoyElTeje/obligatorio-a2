# Ejercicio 1 - Gestión de Inventario de Biblioteca con AVL

## Descripción

Estás desarrollando un sistema para gestionar el inventario de libros de una biblioteca. Cada libro tiene un número de identificación único (ID), un título y un estado de disponibilidad (habilitado o deshabilitado). El sistema utiliza un Árbol AVL para almacenar y gestionar la información de los libros. Las operaciones que se deben implementar son las siguientes:

1. **Agregar o actualizar un libro**: Insertar un libro con un ID y un título en el árbol AVL. Si el ID ya existe, el título del libro se actualiza con el nuevo nombre proporcionado y se habilita si estaba deshabilitado. El árbol debe mantenerse balanceado después de cada inserción o actualización.

2. **Buscar un libro por su ID**: Consultar si un libro con un ID específico existe en la biblioteca. Si el libro existe, se debe devolver su título y H o D dependiendo de si está habilitado o deshabilitado; si no, devolver "libro_no_encontrado".

3. **Habilitar o deshabilitar un libro**: Cambiar el estado de un libro a habilitado si está deshabilitado, o a deshabilitado si está habilitado, basándose en su ID. Si el ID no existe, devolver "libro_no_encontrado".

4. **Consultar la cantidad de libros habilitados y deshabilitados**: Proporcionar una consulta que devuelva la cantidad total de libros, así como la cantidad de libros habilitados y deshabilitados.

## Entrada

La entrada recibe el siguiente formato:

- La primera línea contiene un entero `N`, que representa la cantidad de operaciones a realizar.
- Las siguientes `N` líneas contienen las operaciones, que pueden ser de cuatro tipos:

  - `ADD <ID del libro> <Título del libro>`: para agregar un nuevo libro con su ID y título. En caso de que el ID ya exista, se debe actualizar el título del libro y habilitarlo en caso que esté deshabilitado.
  - `FIND <ID del libro>`: para buscar un libro por su ID.
  - `TOGGLE <ID del libro>`: para cambiar el estado de un libro a habilitado si está deshabilitado, o a deshabilitado si está habilitado. Si el libro no existe, devolver "libro_no_encontrado".
  - `COUNT`: para consultar la cantidad total de libros, así como la cantidad de libros habilitados y deshabilitados.

## Salida

- Para cada operación de búsqueda `FIND`, imprimir el título del libro si existe y si está habilitado o deshabilitado (`H` o `D`), o "libro_no_encontrado" si no existe.
- Para cada operación `TOGGLE`, si el libro no existe, imprimir "libro_no_encontrado". Si el libro existe, no imprimir nada.
- Para la operación `COUNT`, imprimir en una sola línea tres enteros: el número total de libros, el número de libros habilitados y el número de libros deshabilitados. Formato de salida: `{total} {habilitados} {deshabilitados}`.

## Restricciones

- `1 <= N <= 10^5`
- `1 <= ID del libro <= 10^8`
- Cada título de libro tiene una longitud máxima de 100 caracteres (sin espacios).
- La estructura de datos debe ser un árbol AVL para asegurar que las operaciones de inserción, búsqueda, y actualización de estado se realicen en tiempo $O(\log N)$.
- La consulta (operación `COUNT`) debe realizarse en tiempo $O(1)_{pc}$.

## Ejemplo

### Input

```
11
ADD 15 Don_Quijote
ADD 23 La_Casa_de_los_Espiritus
FIND 15
FIND 88
TOGGLE 15
FIND 15
ADD 25 Cien_Años_de_Soledad
COUNT
TOGGLE 99
TOGGLE 23
COUNT
```

### Output

```
Don_Quijote H
libro_no_encontrado
Don_Quijote D
3 2 1
libro_no_encontrado
3 1 2
```
