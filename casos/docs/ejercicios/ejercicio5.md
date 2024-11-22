# Ejercicio 5 - Impossible Mission Force (el regreso)

## Descripción

Has sido reclutado por el equipo de _Impossible Mission Force (IMF)_ para ayudar en su tarea de _Desactivar la Entidad_.  
Tienes la tarea de ayudar al equipo de IMF a completar una serie de misiones distribuidas en distintas ciudades. Estas misiones tienen un **orden específico de ejecución debido a dependencias entre ellas**. Además, **debes minimizar el tiempo de viaje entre ciudades**, eligiendo siempre la misión más cercana en términos de tiempo de desplazamiento desde la ubicación actual.

Tu misión, en caso de que decidas aceptarla, es determinar el orden de ejecución de las misiones respetando las dependencias y minimizando el tiempo total de viaje. El equipo puede desplazarse entre ciudades a través de conexiones seguras con tiempos de viaje predefinidos.

Para minimizar el desplazamiento, una vez concluida una misión, se deberá optar entre las siguientes misiones posibles (no ejecutadas y sin misiones previas pendientes) por aquella que tenga el menor tiempo de desplazamiento considerando la ubicación actual del equipo hasta la ciudad donde se debe ejecutar dicha misión, de haber dos con el mismo tiempo de desaplazamiento se elige la que tiene idMision más bajo.

Condiciones del problema:

1. **Dependencias entre misiones**
    - Algunas misiones dependen de que otras se completen antes de poder ser ejecutadas.
    - Solo puedes ejecutar una misión que no tenga dependencias pendientes.
    - No existe dependencia circular entre las misiones.
2. **Ciudades y conexiones**
    - Cada ciudad tiene un nombre único y se encuentra conectada con otras ciudades mediante rutas con tiempos de viaje específicos.
    - El tiempo de viaje entre dos ciudades es el mismo en ambos sentidos.
    - No hay ciudades aisladas, siempre existe un camino entre dos ciudades cualesquiera.
    - Si hay un empate en el tiempo de viaje entre dos misiones, elige la misión cuya ciudad tenga el identificador más pequeño.

## Entrada

La entrada se recibe con el siguiente formato:

- La primera línea contiene un entero `M` que representa la cantidad de misiones a realizar;
- A continuación, se reciben `M` líneas, con espacio separando cada valor, compuestas de la siguiente manera:
  - `idMision`, entero;
  - `Nombre_misión_sin_espacios`, string;
  - `idCiudad`, entero; y,
  - `lista de id de misiones` (enteros) –posteriores a la misión de idMision– separada por un espacio y terminada en `0`
- La siguiente linea contiene dos enteros, `C` y `O`, separados por un espacio:
  - `C` representa la cantidad de ciudades; y,
  - `O` representa la ciudad donde el equipo de IMF se encuentra inicialmente (no tiene por qué coincidir con la ciudad de la primera misión, aunque sí puede hacerlo)
- Luego se reciben `C` líneas con el siguiente formato, cada valor separado por un espacio:
  - `idCiudad`, entero; y,
  - `Nombre_Ciudad_Sin_Espacios`, string
- `E` una cantidad de líneas que representan conexiones seguras entre las ciudades con la siguiente composición, cada valor separado por un espacio:
  - `idCiudadOrigen`, entero;
  - `idCiudadDestino`, entero; y,
  - `tiempoDesplazamiento`, entero

## Salida

Se debe imprimir:

- Ciudad Inicial: `Nombre_Ciudad_Inicial`
- Itinerario de misiones a realizar en el orden correcto, cada misión en una línea, con el siguiente formato:
  - `caminoRecorridoEntreCiudades` -> Mision: `Nombre_Misión` - `Nombre_Ciudad_Mision` - Tiempo de viaje: `Tiempo_Viaje`
- Misiones ejecutadas con exito.
- Tiempo total de viaje: `Tiempo_Total`

Donde:

- `caminoRecorridoEntreCiudades` es el camino recorrido entre la ciudad actual y la ciudad de la misión, separado por " -> " (incluye la ciudad inicial, todas las ciudades intermedias y ciudad final);
- `Nombre_Misión` es el nombre de la misión;
- `Nombre_Ciudad_Mision` es el nombre de la ciudad donde se debe ejecutar la misión;
- `Tiempo_Viaje` es el tiempo de viaje desde la ciudad actual hasta la ciudad de la misión;
- `Tiempo_Total` es el tiempo total de viaje desde la ciudad inicial hasta la última ciudad de la última misión ejecutada.

## Restricciones

- Cantidad de misiones a realizar: `5 <= M <= 200`;
- Identificador de la misión: `1 <= idMision <= 200`;
- Identificador de la cuidad: `1 <= idCiudad <= 50`;
- Cantidad de ciudades: `1 <= C <= 50` (hay como máximo 50 ciudades);
- Ciudad origen: `1 <= O <= 50` (puede ser una ciudad asignada a una misión o no);
- Tiempo de desplazamiento entre ciudades: `1 <= Td <= 1000`;
- Se puede asumir que:
  - no existe dependencia circular entre misiones;
  - la cantidad de dependencias entre misiones es aproximadamente el 30% de las dependencias posibles;
  - la cantidad de conexiones entre las ciudades es arbitraria en cada entrada, pero se puede asumir que representan aproximadamente el 30% de las conexiones posibles;
- Orden temporal: `O((M + Dep) + M * ((C + E) * log C))`, donde:
  - `Dep` es la cantidad de dependencias entre misiones;
  - `E` es la cantidad de conexiones entre ciudades;

## Ejemplo

### Input

``` plaintext
5
1 Recuperar_llave 1 5 2 0
2 Desactivar_servidor 2 4 5 0
3 Obtener_informacion_confidencial 3 5 4 0
4 Extraer_codigo_fuente 4 5 0
5 Desactivar_la_Entidad 5 0
6 6
1 Montevideo
2 New_York
3 Roma
4 Tokio
5 Londres
6 Punta_Del_Este
7
1 2 350
1 3 600
2 4 900
2 3 500
3 5 300
6 1 10
6 3 1000
```

### Output

``` plaintext
Ciudad inicial: Punta_Del_Este
Punta_Del_Este -> Montevideo -> Mision: Recuperar_llave - Montevideo - Tiempo de viaje: 10
Montevideo -> New_York -> Mision: Desactivar_servidor - New_York - Tiempo de viaje: 350
New_York -> Roma -> Mision: Obtener_informacion_confidencial - Roma - Tiempo de viaje: 500
Roma -> New_York -> Tokio -> Mision: Extraer_codigo_fuente - Tokio - Tiempo de viaje: 1400
Tokio -> New_York -> Roma -> Londres -> Mision: Desactivar_la_Entidad - Londres - Tiempo de viaje: 1700
Misiones ejecutadas con exito.
Tiempo total de viaje: 3960
```

### Explicación

- El grupo de IMF se encuentra inicialmente en Punta del Este.
- La primera misión a realizar implica ir de Punta del este a Montevideo y el recorrido no tiene ciudades intermedias, la misión es "Recuperar_llave" en Montevideo, con un tiempo de viaje de 10.
- La segunda misión a realizar implica ir de Montevideo a New York y el recorrido no tiene ciudades intermedias, la misión es "Desactivar_servidor" en New York, con un tiempo de viaje de 350.
- La tercera misión a realizar implica ir de New York a Roma y el recorrido no tiene ciudades intermedias, la misión es "Obtener_informacion_confidencial" en Roma, con un tiempo de viaje de 500.
- La cuarta misión a realizar implica ir de Roma a Tokio y el recorrido es Roma -> New York -> Tokio (El camino más corto de Roma a Tokio pasó por New York), la misión es "Extraer_codigo_fuente" en Tokio, con un tiempo de viaje de 1400.
- La quinta misión a realizar implica ir de Tokio a Londres y el recorrido es Tokio -> New York -> Roma -> Londres (El camino más corto de Tokio a Londres pasó por New York y Roma), la misión es "Desactivar_la_Entidad" en Londres, con un tiempo de viaje de 1700.
- Todas las misiones se ejecutaron con éxito y el tiempo total de viaje fue de 3960.
