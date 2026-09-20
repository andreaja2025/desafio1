#ifndef JUEGO_H
#define JUEGO_H

#include "tablero.h"

/**
 * ============================================================================
 * MÓDULO: Lógica de Juego
 * ARCHIVO: juego.h
 * ----------------------------------------------------------------------------
 * DESCRIPCIÓN:
 * Este módulo coordina las reglas de la partida en SweetCrush. Se
 * encarga del análisis de patrones, aplicación de cascada y reordenamiento de
 * elementos tras cada movimiento o eliminación.
 *
 * DISTRIBUCIÓN DE FUNCIONES:
 * - Aplicación de cascada y reposición de vacíos (`subrutinaCascada`).
 * - Detección de patrones en 'L', 'T' o líneas (>=3), cálculo de combos,
 *   puntuación acumulada y métricas de juego (`subrutinaCombinaciones`).
 *
 * NOTA DE DISEÑO:
 * Este módulo depende de `tablero.h` para acceder a la memoria de bajo nivel,
 * operando de forma completamente independiente de la impresión por consola (UI).
 * ============================================================================
 */

void subrutinaCascada(
    unsigned char* ptrTablero,
    unsigned short filas,
    unsigned short columnas,
    unsigned short bitsExtras
    );

bool subrutinaCombinaciones(
    unsigned char* ptrTablero,
    unsigned short filas,
    unsigned short columnas,
    unsigned short bitsExtras,
    unsigned int &puntuacion,
    unsigned int &totalFichasEliminadas,
    unsigned int &combDetectadas,
    unsigned int &combosDetectados
    );

#endif // JUEGO_H
