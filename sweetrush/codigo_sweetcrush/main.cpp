/*
Trabajo para la asignatura de informática 2
Universidad de Antioquia - Desafío 1
*/

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "tablero.h"
#include "juego.h"
#include "interfaz.h"
#include "validaciones.h"

using namespace std;

// LIMITES DEL TABLERO

// Ancho seguro de consola.
// Cada columna del tablero utiliza aproximadamente 3 caracteres:
// " X "
//
// Se dejan 4 caracteres para mostrar el numero de fila.
constexpr unsigned short ANCHO_CONSOLA_SEGURO = 80;
constexpr unsigned short MARGEN_FILA_CHARS = 4;
constexpr unsigned short CHARS_POR_COLUMNA = 3;

// Maximo de columnas que pueden visualizarse sin exceder
// el ancho seguro establecido.
constexpr unsigned short MAX_COLUMNAS_PANTALLA =
    (ANCHO_CONSOLA_SEGURO - MARGEN_FILA_CHARS) /
    CHARS_POR_COLUMNA;

// Cada ficha utiliza 3 bits.
constexpr unsigned int BITS_POR_FICHA = 3;

// Cantidad maxima de bytes que puede representar
// la variable unsigned short utilizada para el tablero.
constexpr unsigned int MAX_BYTES_MEMORIA = 65535;

// Cantidad maxima de fichas que pueden almacenarse
// utilizando 65535 bytes y 3 bits por ficha.
constexpr unsigned int MAX_CASILLAS_MEMORIA =
    (MAX_BYTES_MEMORIA * 8) / BITS_POR_FICHA;


int main()
{
    srand(time(nullptr));

    mostrarBienvenida();

    // LECTURA DE FILAS

    // Las filas utilizan unsigned short.
    // El maximo representable es 65535.
    unsigned short maxFilas = 65535;

    unsigned short filas = leerOpcionSegura(
        1,
        maxFilas,
        "\nDe cuantas filas quiere su tablero? (min 1, max "
        );


    // LECTURA DE COLUMNAS

    // Primero se calcula cuantas columnas permite la memoria
    // teniendo en cuenta las filas que eligio el usuario.
    unsigned int maxColumnasMemoria =
        MAX_CASILLAS_MEMORIA / filas;

    // El limite final de columnas es el menor entre:
    //
    // 1. Lo que puede visualizarse en la consola.
    // 2. Lo que permite la memoria del tablero.
    unsigned short maxColumnas =
        MAX_COLUMNAS_PANTALLA;

    if (maxColumnasMemoria < maxColumnas) {
        maxColumnas = maxColumnasMemoria;
    }

    unsigned short columnas = leerOpcionSegura(
        1,
        maxColumnas,
        "\nY cuantas columnas? (min 1, max "
        );


    // CALCULO DE MEMORIA

    // Se calcula primero la cantidad total de casillas.
    unsigned int totalCasillas =
        filas * columnas;

    // Cada casilla utiliza 3 bits.
    unsigned int totalBits =
        totalCasillas * BITS_POR_FICHA;

    // Redondeo hacia arriba para obtener la cantidad de bytes.
    unsigned int bytesCalculados =
        (totalBits + 7) / 8;


    // Barrera de seguridad final.
    if (bytesCalculados > MAX_BYTES_MEMORIA) {

        cout << "\n>> Error: Las dimensiones seleccionadas exceden "
                "la capacidad de memoria del tablero.\n";

        return 1;
    }

    unsigned short bytes =
        bytesCalculados;

    unsigned short bitsExtras =
        (bytes * 8) - totalBits;

    unsigned short bytesReservados =
        bytes;


    // CREACION Y LLENADO DEL TABLERO

    unsigned char* pTab =
        crearTablero(bytes);

    llenarTableroRandom(
        pTab,
        filas,
        columnas,
        bitsExtras
        );


    unsigned int puntuacionAcumulada = 0;
    unsigned int eliminacionesUsuario = 0;
    unsigned int totalFichasEliminadas = 0;
    unsigned int combinacionesDetectadas = 0;

    // Almacena la cantidad de combos independientes detectados.
    unsigned int combosDetectados = 0;


    // COMBINACIONES INICIALES

    subrutinaCombinaciones(
        pTab,
        filas,
        columnas,
        bitsExtras,
        puntuacionAcumulada,
        totalFichasEliminadas,
        combinacionesDetectadas,
        combosDetectados
        );

    mostrarEstadisticasJugada(
        puntuacionAcumulada,
        puntuacionAcumulada,
        totalFichasEliminadas,
        totalFichasEliminadas,
        combinacionesDetectadas,
        combosDetectados
        );


    // MENU PRINCIPAL

    unsigned short opcion = 0;

    do {

        verTableroBits(
            pTab,
            filas,
            columnas,
            bitsExtras
            );

        verTableroFichas(
            pTab,
            filas,
            columnas
            );

        // El menu solamente muestra las opciones.
        mostrarMenu();

        // La lectura y validacion de la opcion
        // se realiza mediante el modulo de validaciones.
        opcion = leerOpcionSegura(
            1,
            6,
            "Seleccione una opcion (1-"
            );

        ejecutarOpcion(
            opcion,
            pTab,
            filas,
            columnas,
            bitsExtras,
            bytesReservados,
            puntuacionAcumulada,
            eliminacionesUsuario,
            totalFichasEliminadas,
            combinacionesDetectadas,
            combosDetectados
            );

    } while (opcion != 6);


    // LIBERACION DE MEMORIA

    if (pTab != nullptr) {
        delete[] pTab;
        pTab = nullptr;
    }


    // RESUMEN FINAL

    mostrarResumenFinal(
        puntuacionAcumulada,
        eliminacionesUsuario,
        totalFichasEliminadas,
        combinacionesDetectadas,
        combosDetectados
        );

    return 0;
}