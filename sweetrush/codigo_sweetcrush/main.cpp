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

using namespace std;

int main()
{
    srand(time(nullptr));

    mostrarBienvenida();

    unsigned short filas = 0;
    unsigned short columnas = 0;

    cout << "\nDe cuantas filas quiere su tablero?: ";
    cin >> filas;

    cout << "Y cuantas columnas?: ";
    cin >> columnas;

    unsigned int bits = filas * columnas * 3;

    unsigned short bytes = 0;

    if (bits % 8 != 0) {
        bytes = (bits / 8) + 1;
    } else {
        bytes = bits / 8;
    }

    unsigned short bitsExtras = (bytes * 8) - bits;
    unsigned short bytesReservados = bytes;

    unsigned char* pTab = crearTablero(bytes);

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

    subrutinaCombinaciones(
        pTab,
        filas,
        columnas,
        bitsExtras,
        puntuacionAcumulada,
        totalFichasEliminadas,
        combinacionesDetectadas
        );

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

        mostrarMenu(opcion);

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
            combinacionesDetectadas
            );

    } while (opcion != 6);

    if (pTab != nullptr) {
        delete[] pTab;
        pTab = nullptr;
    }

    mostrarResumenFinal(
        puntuacionAcumulada,
        eliminacionesUsuario,
        totalFichasEliminadas,
        combinacionesDetectadas
        );

    return 0;
}