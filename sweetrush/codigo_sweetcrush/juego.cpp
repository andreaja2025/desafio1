#include "juego.h"
#include <iostream>

/**
 * ============================================================================
 * ARCHIVO: juego.cpp
 * IMPLEMENTACIÓN: Módulo de Lógica de Juego
 * ----------------------------------------------------------------------------
 * Implementa los algoritmos de búsqueda bidireccional (horizontal y vertical),
 * el control de arreglos dinámicos temporales (mapa de marcas auxiliares)
 * para evitar el sobreconteo de fichas cruzadas, y el ciclo iterativo de
 * reordenamiento por cascada.
 * ============================================================================
 */

using namespace std;

void subrutinaCascada(
    unsigned char* ptrTablero,
    unsigned short filas,
    unsigned short columnas,
    unsigned short bitsExtras
    )
{
    // Validación del tablero y sus dimensiones.
    if (ptrTablero == nullptr || filas == 0 || columnas == 0) {
        return;
    }

    bool huboCambios;

    do {
        huboCambios = false;

        // Recorrer columnas de abajo hacia arriba.
        for (unsigned short c = 0; c < columnas; c++) {

            for (unsigned short f = filas - 1; f > 0; f--) {

                if (obtenerFicha(
                        ptrTablero,
                        f,
                        c,
                        columnas,
                        bitsExtras
                        ) == 0)
                {
                    unsigned char arriba = obtenerFicha(
                        ptrTablero,
                        f - 1,
                        c,
                        columnas,
                        bitsExtras
                        );

                    if (arriba != 0) {

                        escribirFicha(
                            ptrTablero,
                            f,
                            c,
                            columnas,
                            bitsExtras,
                            arriba
                            );

                        eliminarFicha(
                            ptrTablero,
                            f - 1,
                            c,
                            columnas,
                            bitsExtras
                            );

                        huboCambios = true;
                    }
                }
            }
        }

        // Generar nuevas fichas en la primera fila.
        for (unsigned short c = 0; c < columnas; c++) {

            if (obtenerFicha(
                    ptrTablero,
                    0,
                    c,
                    columnas,
                    bitsExtras
                    ) == 0)
            {
                escribirFicha(
                    ptrTablero,
                    0,
                    c,
                    columnas,
                    bitsExtras,
                    generarFichaRandom()
                    );

                huboCambios = true;
            }
        }

    } while (huboCambios);
}


bool subrutinaCombinaciones(
    unsigned char* ptrTablero,
    unsigned short filas,
    unsigned short columnas,
    unsigned short bitsExtras,
    unsigned int &puntuacion,
    unsigned int &totalFichasEliminadas,
    unsigned int &combDetectadas,
    unsigned int &combosDetectados
    )
{
    // Validación del tablero y sus dimensiones.
    if (ptrTablero == nullptr || filas == 0 || columnas == 0) {
        return false;
    }

    bool huboAlMenosUnaComb = false;
    unsigned int contadorCascadasJugada = 0;

    while (true) {

        unsigned int totalCasillas = filas * columnas;

        // Mapa auxiliar para marcar las fichas que pertenecen
        // a una combinación.
        bool* mapaAuxiliar = new bool[totalCasillas]();

        bool combinacionEnEstaRonda = false;

        // BÚSQUEDA HORIZONTAL
        for (unsigned short f = 0; f < filas; f++) {

            unsigned short c = 0;

            while (c < columnas) {

                unsigned char fichaActual = obtenerFicha(
                    ptrTablero,
                    f,
                    c,
                    columnas,
                    bitsExtras
                    );

                if (fichaActual == 0) {
                    c++;
                    continue;
                }

                unsigned short len = 1;

                while (
                    c + len < columnas &&
                    obtenerFicha(
                        ptrTablero,
                        f,
                        c + len,
                        columnas,
                        bitsExtras
                        ) == fichaActual
                    ) {
                    len++;
                }

                if (len >= 3) {

                    combinacionEnEstaRonda = true;

                    // Cada grupo independiente de 3 o más fichas
                    // cuenta como un combo.
                    combosDetectados++;

                    for (unsigned short k = 0; k < len; k++) {

                        mapaAuxiliar[
                            f * columnas + (c + k)
                        ] = true;
                    }
                }

                c += len;
            }
        }

        // BÚSQUEDA VERTICAL
        for (unsigned short c = 0; c < columnas; c++) {

            unsigned short f = 0;

            while (f < filas) {

                unsigned char fichaActual = obtenerFicha(
                    ptrTablero,
                    f,
                    c,
                    columnas,
                    bitsExtras
                    );

                if (fichaActual == 0) {
                    f++;
                    continue;
                }

                unsigned short len = 1;

                while (
                    f + len < filas &&
                    obtenerFicha(
                        ptrTablero,
                        f + len,
                        c,
                        columnas,
                        bitsExtras
                        ) == fichaActual
                    ) {
                    len++;
                }

                if (len >= 3) {

                    combinacionEnEstaRonda = true;

                    // Cada grupo independiente de 3 o más fichas
                    // cuenta como un combo.
                    combosDetectados++;

                    for (unsigned short k = 0; k < len; k++) {

                        mapaAuxiliar[
                            (f + k) * columnas + c
                        ] = true;
                    }
                }

                f += len;
            }
        }


        // PROCESAMIENTO Y ESTADÍSTICAS

        if (combinacionEnEstaRonda) {

            huboAlMenosUnaComb = true;

            // Cuenta la ronda en la que se encontró al menos
            // una combinación.
            combDetectadas++;

            unsigned int destruidasEstaRonda = 0;

            // Cambiar a "Vacía" (0) las fichas marcadas.
            for (unsigned short f = 0; f < filas; f++) {

                for (unsigned short c = 0; c < columnas; c++) {

                    if (mapaAuxiliar[
                            f * columnas + c
                    ])
                    {
                        eliminarFicha(
                            ptrTablero,
                            f,
                            c,
                            columnas,
                            bitsExtras
                            );

                        destruidasEstaRonda++;
                    }
                }
            }

            totalFichasEliminadas += destruidasEstaRonda;

            puntuacion += destruidasEstaRonda * 10;

            // Aplicar cascada existente.
            subrutinaCascada(
                ptrTablero,
                filas,
                columnas,
                bitsExtras
                );

            contadorCascadasJugada++;

            // cout << "\n[!] Combinacion detectada. Fichas destruidas: "
            //      << destruidasEstaRonda
            //      << endl;

            // cout << "    Puntuacion acumulada: "
            //      << puntuacion
            //      << " | Cascadas en esta jugada: "
            //      << contadorCascadasJugada
            //      << endl;

            delete[] mapaAuxiliar;
        }
        else {

            delete[] mapaAuxiliar;

            // No hay más combinaciones.
            break;
        }
    }

    return huboAlMenosUnaComb;
}