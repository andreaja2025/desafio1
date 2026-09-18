#include "modificaciones.h"
#include "tablero.h"

void calcularDimensionesBits(
    unsigned short filas,
    unsigned short columnas,
    unsigned short &bytesNecesarios,
    unsigned short &bitsExtras
    )
{
    unsigned int bitsNecesarios = filas * columnas * 3;

    if (bitsNecesarios % 8 != 0) {
        bytesNecesarios = (bitsNecesarios / 8) + 1;
    } else {
        bytesNecesarios = bitsNecesarios / 8;
    }

    bitsExtras = (bytesNecesarios * 8) - bitsNecesarios;
}

void copiarTableroExcluyendo(
    unsigned char* orig,
    unsigned char* dest,
    unsigned short filasOrig,
    unsigned short colsOrig,
    short filaOmite,
    short colOmite,
    unsigned short bitsExOrig,
    unsigned short bitsExDest
    )
{
    unsigned short fDest = 0;
    unsigned short colsDest = colsOrig;

    if (colOmite >= 0) {
        colsDest = colsOrig - 1;
    }

    for (unsigned short f = 0; f < filasOrig; f++) {

        if (f == filaOmite) {
            continue;
        }

        unsigned short cDest = 0;

        for (unsigned short c = 0; c < colsOrig; c++) {

            if (c == colOmite) {
                continue;
            }

            unsigned char valor =
                obtenerFicha(
                    orig,
                    f,
                    c,
                    colsOrig,
                    bitsExOrig
                    );

            escribirFicha(
                dest,
                fDest,
                cDest,
                colsDest,
                bitsExDest,
                valor
                );

            cDest++;
        }

        fDest++;
    }
}

bool eliminarFila(
    unsigned char*& ptrTablero,
    unsigned short &filas,
    unsigned short columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short filaAEliminar
    )
{
    if (filas <= 1 || filaAEliminar >= filas) {
        return false;
    }

    unsigned short nuevasFilas = filas - 1;
    unsigned short bytesNecesarios;
    unsigned short nuevosBitsExtras;

    calcularDimensionesBits(
        nuevasFilas,
        columnas,
        bytesNecesarios,
        nuevosBitsExtras
        );

    unsigned short bytesAReservar = bytesReservados;

    if (bytesNecesarios < 0.65 * bytesReservados) {
        bytesAReservar = bytesNecesarios;
    }

    if (bytesAReservar < bytesNecesarios) {
        bytesAReservar = bytesNecesarios;
    }

    unsigned char* nuevoTablero =
        crearTablero(bytesAReservar);

    if (!nuevoTablero) {
        return false;
    }

    copiarTableroExcluyendo(
        ptrTablero,
        nuevoTablero,
        filas,
        columnas,
        filaAEliminar,
        -1,
        bitsExtras,
        nuevosBitsExtras
        );

    delete[] ptrTablero;

    ptrTablero = nuevoTablero;
    filas = nuevasFilas;
    bitsExtras = nuevosBitsExtras;
    bytesReservados = bytesAReservar;

    return true;
}

bool eliminarColumna(
    unsigned char*& ptrTablero,
    unsigned short filas,
    unsigned short &columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short colAEliminar
    )
{
    if (columnas <= 1 || colAEliminar >= columnas) {
        return false;
    }

    unsigned short nuevasColumnas = columnas - 1;
    unsigned short bytesNecesarios;
    unsigned short nuevosBitsExtras;

    calcularDimensionesBits(
        filas,
        nuevasColumnas,
        bytesNecesarios,
        nuevosBitsExtras
        );

    unsigned short bytesAReservar = bytesReservados;

    if (bytesNecesarios < 0.65 * bytesReservados) {
        bytesAReservar = bytesNecesarios;
    }

    if (bytesAReservar < bytesNecesarios) {
        bytesAReservar = bytesNecesarios;
    }

    unsigned char* nuevoTablero =
        crearTablero(bytesAReservar);

    if (!nuevoTablero) {
        return false;
    }

    copiarTableroExcluyendo(
        ptrTablero,
        nuevoTablero,
        filas,
        columnas,
        -1,
        colAEliminar,
        bitsExtras,
        nuevosBitsExtras
        );

    delete[] ptrTablero;

    ptrTablero = nuevoTablero;
    columnas = nuevasColumnas;
    bitsExtras = nuevosBitsExtras;
    bytesReservados = bytesAReservar;

    return true;
}