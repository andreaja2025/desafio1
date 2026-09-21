# Sweet Crush

**Sweet Crush** es un juego desarrollado en **C++** para ejecutarse desde la terminal. El programa trabaja con un tablero dinámico de fichas y utiliza memoria dinámica, punteros y operaciones a nivel de bits como parte de su implementación.

El jugador puede modificar el tablero, realizar eliminaciones y observar las estadísticas generadas durante la partida.

---

## ¿Cómo jugar?

Al iniciar el programa, se solicitan las dimensiones iniciales del tablero. El programa valida que los valores ingresados sean números enteros y que se encuentren dentro de los límites permitidos.

Una vez creado el tablero, las fichas son generadas aleatoriamente. Si existen combinaciones desde el inicio, estas son detectadas, eliminadas y procesadas mediante el sistema de cascadas antes de comenzar las jugadas del usuario.

Las fichas se representan mediante diferentes **símbolos**, lo que permite identificar fácilmente su estado dentro del tablero.

Cuando el usuario realiza una jugada, el programa verifica si existen combinaciones de tres o más fichas iguales en sentido horizontal o vertical. Las fichas que forman parte de una combinación son eliminadas y posteriormente se ejecuta la cascada, haciendo que las fichas superiores ocupen los espacios vacíos y generando nuevas fichas cuando sea necesario.

El proceso continúa mientras se produzcan nuevas combinaciones.

### Acciones disponibles

<table>
  <tr>
    <th>#</th>
    <th>Tipo</th>
    <th>Acción</th>
    <th>Descripción</th>
  </tr>
  <tr>
    <td>1</td>
    <td>Eliminación</td>
    <td>Eliminar ficha</td>
    <td>Elimina una ficha seleccionada por el usuario.</td>
  </tr>
  <tr>
    <td>2</td>
    <td>Eliminación</td>
    <td>Eliminar fila</td>
    <td>Elimina una fila seleccionada por el usuario del tablero.</td>
  </tr>
  <tr>
    <td>3</td>
    <td>Eliminación</td>
    <td>Eliminar columna</td>
    <td>Elimina una columna seleccionada por el usuario del tablero.</td>
  </tr>
  <tr>
    <td>4</td>
    <td>Modificación</td>
    <td>Agregar fila</td>
    <td>Añade una nueva fila en la ubicación seleccionada por el usuario.</td>
  </tr>
  <tr>
    <td>5</td>
    <td>Modificación</td>
    <td>Agregar columna</td>
    <td>Añade una nueva columna en la ubicación seleccionada por el usuario.</td>
  </tr>
  <tr>
    <td>6</td>
    <td>Finalización</td>
    <td>Terminar juego</td>
    <td>Finaliza la partida y libera la memoria dinámica utilizada.</td>
  </tr>
</table>

Las posiciones ingresadas por el usuario son validadas de acuerdo con las dimensiones actuales del tablero.

---

## Validación de entrada y dimensiones

El programa incorpora validaciones para evitar entradas incorrectas y problemas relacionados con las dimensiones del tablero.

### Validación de datos

Las entradas realizadas por el usuario se reciben inicialmente como texto y se verifica que estén compuestas únicamente por dígitos.

Si el usuario introduce caracteres que no corresponden a un número entero, el programa muestra un mensaje de error y solicita nuevamente el valor.

También se verifica que el número ingresado se encuentre dentro del rango permitido para cada operación.

### Cálculo de dimensiones

Las dimensiones iniciales del tablero se calculan teniendo en cuenta dos restricciones principales:

* **Capacidad de visualización de la consola:** se establece un máximo de columnas que permite mostrar el tablero sin superar el ancho seguro definido.
* **Capacidad de memoria:** se calcula la cantidad máxima de casillas que pueden almacenarse considerando que cada ficha utiliza **3 bits** y que el tablero se almacena utilizando un bloque de memoria representado mediante `unsigned short`.

El número máximo de columnas se determina de acuerdo con las filas seleccionadas y la capacidad disponible de memoria.

Antes de crear el tablero se calcula la cantidad de bits y bytes necesarios. Si las dimensiones seleccionadas superan la capacidad establecida, el programa informa el error y evita realizar la asignación.

Estas validaciones permiten evitar desbordamientos relacionados con las dimensiones y con la memoria utilizada por el tablero.

---

## Puntuación y estadísticas

Durante la partida se muestran diferentes estadísticas que permiten conocer el resultado de cada jugada y el progreso acumulado.

La información presentada incluye:

* **Puntuación obtenida en este turno:** puntos generados durante la jugada actual.
* **Puntuación total acumulada:** total de puntos obtenidos durante la partida.
* **Fichas destruidas en este turno:** cantidad de fichas eliminadas como resultado de la jugada actual y sus combinaciones.
* **Total histórico de fichas destruidas:** cantidad acumulada de fichas eliminadas durante toda la partida.
* **Rondas de combinación en este turno:** cantidad de rondas en las que se detectaron combinaciones durante la jugada.
* **Combos detectados en este turno:** cantidad de grupos independientes de tres o más fichas iguales detectados durante la jugada.

La puntuación se calcula a partir de las fichas eliminadas. Cada ficha destruida aporta **10 puntos**.

Por lo tanto, una combinación de tres fichas genera **30 puntos**, mientras que las combinaciones con más fichas generan una puntuación proporcional al número de fichas eliminadas.

Las cascadas permiten que las fichas ocupen los espacios vacíos y que se generen nuevas fichas. Si estas nuevas fichas forman combinaciones, el proceso continúa y las fichas eliminadas siguen acumulándose en las estadísticas.

---
## Visualización del tablero

El programa permite visualizar el tablero de dos formas:

### Tablero de fichas

Muestra las fichas mediante sus **símbolos**, facilitando la interacción y lectura del tablero por parte del usuario.

### Tablero de bits

Muestra la representación del tablero desde la perspectiva de la memoria utilizada, permitiendo observar los bits almacenados y la forma en que se distribuye la información de las fichas.

Estas dos representaciones permiten diferenciar entre la visualización utilizada para jugar y la representación interna de los datos en memoria.

---

## Estructura del proyecto

```text
sweetrush/
│
├── CMakeLists.txt
├── README.md
│
├── codigo_sweetcrush/
│   ├── main.cpp
│   ├── juego.cpp
│   ├── juego.h
│   ├── tablero.cpp
│   ├── tablero.h
│   ├── interfaz.cpp
│   ├── interfaz.h
│   ├── modificaciones.cpp
│   ├── modificaciones.h
│   ├── validaciones.cpp 
│   ├── validaciones.h
│
│
└── informe/
    ├── README.md
    ├── imagenes/
    └── informe_final.pdf
```

### Módulos principales

**`main.cpp`**

Contiene el punto de entrada del programa, la lectura de las dimensiones iniciales, el cálculo de los límites y la memoria necesaria, y el flujo general de ejecución del juego.

**`tablero.cpp` / `tablero.h`**

Gestionan la creación y manipulación del tablero, incluyendo la lectura, escritura y eliminación de fichas mediante operaciones a nivel de bits.

**`juego.cpp` / `juego.h`**

Contienen la lógica principal del juego, incluyendo la detección de combinaciones, las cascadas, la eliminación de fichas y el cálculo de puntuación y estadísticas.

**`interfaz.cpp` / `interfaz.h`**

Gestionan la interacción con el usuario, la presentación del menú, el monitor de memoria, las estadísticas y el resumen final.

**`modificaciones.cpp` / `modificaciones.h`**

Contienen las operaciones que permiten agregar o eliminar filas y columnas y realizar las modificaciones correspondientes sobre el tablero.

**`validaciones.cpp` / `validaciones.h`**

Contienen las funciones encargadas de validar los valores ingresados por el usuario, verificando que correspondan a números enteros y que se encuentren dentro de los límites establecidos para cada operación.

---

## Requisitos

Para compilar y ejecutar el proyecto se requiere:

* **C++17** o superior.
* **CMake 3.16** o superior.
* Un compilador compatible con C++17.
* Un entorno de desarrollo compatible con CMake, como **Qt Creator**.

El estándar utilizado se encuentra configurado en `CMakeLists.txt`.

---

## Compilación y ejecución

### Desde Qt Creator

1. Abrir el proyecto mediante `CMakeLists.txt`.
2. Seleccionar un kit compatible con C++17.
3. Configurar el proyecto.
4. Compilar mediante **Build**.
5. Ejecutar mediante **Run**.

### Desde la terminal

Desde el directorio raíz del proyecto:

```bash
cmake -S . -B build
cmake --build build
```

El ejecutable se genera dentro del directorio de compilación correspondiente.

---

## Autores

**Andrea Julieth Arias Cantillo**
**Santiago Garcia Naranjo**

**Universidad de Antioquia — Informática II**
**Desafío No. 1**
