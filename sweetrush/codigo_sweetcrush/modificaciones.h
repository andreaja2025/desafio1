/**
 * ============================================================================
 * MÓDULO: Modificaciones Estructurales
 * ARCHIVO: modificaciones.h
 * ----------------------------------------------------------------------------
 * DESCRIPCIÓN:
 * Este módulo gestiona los cambios de dimensión del tablero en tiempo de
 * ejecución, permitiendo la inserción y eliminación de filas y columnas.
 *
 * DISTRIBUCIÓN DE FUNCIONES:
 * - Cálculo de dimensiones y bits extras.
 * - Copia selectiva del tablero.
 * - Eliminación de filas y columnas.
 * - Inserción de filas y columnas.
 *
 * NOTA DE DISEÑO:
 * Este módulo depende de tablero.h para acceder a la manipulación bitwise
 * de bajo nivel, aislando la lógica de realocación dinámica de memoria.
 * ============================================================================
 */

#ifndef MODIFICACIONES_H
#define MODIFICACIONES_H

#include "tablero.h"

    // Calcula los bytes necesarios y los bits de relleno para un tamaño dado.
    void calcularDimensionesBits(
        unsigned short filas,
        unsigned short columnas,
        unsigned short &bytesNecesarios,
        unsigned short &bitsExtras
        );

// Copia el tablero omitiendo una fila y/o columna.
void copiarTableroExcluyendo(
    unsigned char* orig,
    unsigned char* dest,
    unsigned short filasOrig,
    unsigned short colsOrig,
    short filaOmite,
    short colOmite,
    unsigned short bitsExOrig,
    unsigned short bitsExDest
    );

// Elimina una fila del tablero.
bool eliminarFila(
    unsigned char*& ptrTablero,
    unsigned short &filas,
    unsigned short columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short filaAEliminar
    );

// Elimina una columna del tablero.
bool eliminarColumna(
    unsigned char*& ptrTablero,
    unsigned short filas,
    unsigned short &columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short colAEliminar
    );

// Inserta una nueva fila en una posición determinada.
bool agregarFila(
    unsigned char*& ptrTablero,
    unsigned short &filas,
    unsigned short columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short posFilaUser
    );

// Inserta una nueva columna en una posición determinada.
bool agregarColumna(
    unsigned char*& ptrTablero,
    unsigned short filas,
    unsigned short &columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short posColUser
    );

#endif // MODIFICACIONES_H
