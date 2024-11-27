# Ejercicio 6 - Orden última misión

## Descripción

En la ejecución de la última misión, Morfeo está afectado y no puede decidir el orden en que se deben realizar las acciones. Te solicita ayuda para decidir el orden en que se deben realizar las acciones para que la misión sea un éxito. Las acciones a realizar son:

- **A** - Desactivar la Entidad
- **B** - Reunirse con el equipo
- **C** - Ir al punto de extracción

El problema radica en que Morfeo no está seguro si primero debe desactivar la entidad o reunirse con el equipo.
El equipo dispone de conexiones seguras entre ciudades que utiliza para desplazarse entre ellas, pero, luego de utilizar una, la Entidad aumenta la cantidad de secuaces que hay en ella y se vuelve más insegura, por lo que el costo de utilizarla es 2 veces mayor.

Puntualmente, tu algoritmo debe determinar el orden en que se deben realizar las acciones para que el costo total sea el menor posible. Es decir, si se debe primero desactivar la entidad o reunirse con el equipo. En caso de que el costo sea el mismo, se debe desactivar la entidad.

## Entrada

La entrada se recibe con el siguiente formato:

- La primera línea contiene un entero `C` que representa la cantidad de ciudades para las que se dispone de rutas seguras;
- A continuación se reciben `C` líneas, cada una con los siguientes valores separados entre sí por un espacio:
  - `idCiudad`, entero; y,
  - `Nombre_Ciudad_Sin_Espacios`, string
- La siguiente línea contiene un entero `S` (Start), que representa el id de la ciudad donde se encuentra la Morfeo inicialmente;
- La siguiente línea contiene un entero `E` (Entity), que representa el id de la ciudad donde se encuentra la Entidad;
- La siguiente línea contiene un entero `T` (Team), que representa el id de la ciudad se encuentra el resto del equipo;
- La siguiente línea contiene un entero `P` (Point), que representa el id de la ciudad donde se encuentra el punto de extracción.
- `E` la cantidad de líneas que representan las conexiones entre ciudades. Cada línea contiene los siguientes valores separados por un espacio:
  - `idCiudadOrigen`, entero;
  - `idCiudadDestino`, entero; y,
  - `Costo`, entero.

## Salida

La salida debe contener:

BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de _Costo_Total_  
La otra opcion tiene un costo de _Costo_Otra_Opción_  
Paso 1: _Camino_Del_Paso_1_ -> Desactivar la Entidad
Paso 2: _Camino_Del_Paso_2_ -> Buscar equipo
Paso 3: _Camino_Del_Paso_3_ -> Ir a Punto de extraccion

Donde:

- _Costo_Total_ es el costo total de la mejor opción (en este caso fue Desactivar la Entidad, buscar equipo e ir al punto de extracción);
- _Costo_Otra_Opción_ es el costo total de la otra opción (Buscar equipo, desactivar la entidad e ir al punto de extraccion);
- _Camino_Del_Paso_1_ es el camino que se debe seguir para realizar la acción del paso 1 imprimiendo todas las ciudades intermedias;
- _Camino_Del_Paso_2_ es el camino que se debe seguir para realizar la acción del paso 2 imprimiendo todas las ciudades intermedias;
- _Camino_Del_Paso_3_ es el camino que se debe seguir para realizar la acción del paso 3 imprimiendo todas las ciudades intermedias.

## Restricciones

- `5 <= C <= 300`
- `1 <= S, E, T, P <= C`
- `1 <= Costo <= 100`, esta restricción representa el costo inicial de una conexión segura, luego de utilizarla el costo se duplica y puede superar el valor 100
- Orden temporal: `(C + Con) * log C)`, donde:
  - `Con` es la cantidad de conexiones entre ciudades;

## Ejemplo

### Input

```plaintext
5
1 Montevideo
2 Nueva_York
3 Roma
4 Tokio
5 Moscu
3
2
5
4
6
1 2 20
1 3 10
1 5 5
3 4 10
3 5 8
4 5 10
```

### Output

BE11, la mejor ruta es Desactivar la Entidad, buscar equipo y punto de extraccion con un costo de 85  
La otra opcion tiene un costo de 93  
Paso 1: Roma -> Montevideo -> Nueva_York -> Desactivar la Entidad  
Paso 2: Nueva_York -> Montevideo -> Moscu -> Buscar equipo  
Paso 3: Moscu -> Tokio -> Ir a Punto de extraccion  

### Explicación

La opción de menor costo es Desactivar la Entidad, buscar equipo e ir al punto de extracción. El costo total es 85. La otra opción tiene un costo de 93.  
Los pasos se dividen en tres partes:

1. Desactivar la Entidad: Se debe ir de Roma a Montevideo y luego a Nueva York.
2. Buscar equipo: Se debe ir de Nueva York a Montevideo y luego a Moscú.
3. Ir a Punto de extracción: Se debe ir de Moscú a Tokio.
