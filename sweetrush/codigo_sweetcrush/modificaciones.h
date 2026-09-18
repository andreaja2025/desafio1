#ifndef MODIFICACIONES_H
#define MODIFICACIONES_H

#include "tablero.h"

void calcularDimensionesBits(
    unsigned short filas,
    unsigned short columnas,
    unsigned short &bytesNecesarios,
    unsigned short &bitsExtras
    );

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

bool eliminarFila(
    unsigned char*& ptrTablero,
    unsigned short &filas,
    unsigned short columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short filaAEliminar
    );

bool eliminarColumna(
    unsigned char*& ptrTablero,
    unsigned short filas,
    unsigned short &columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short colAEliminar
    );

#endif // MODIFICACIONES_H