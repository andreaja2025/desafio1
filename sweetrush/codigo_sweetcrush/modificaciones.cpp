/**
 * ============================================================================
 * ARCHIVO: modificaciones.cpp
 * IMPLEMENTACIÓN: Módulo de Modificaciones Estructurales
 * ----------------------------------------------------------------------------
 * DESCRIPCIÓN:
 * Implementa la reorganización del tablero y de la memoria dinámica para
 * permitir insertar y eliminar filas y columnas en tiempo de ejecución.
 *
 * NOTA DE DISEÑO:
 * - Cada ficha utiliza 3 bits.
 * - Se recalculan las dimensiones y los bits extras después de cada cambio.
 * - Para las eliminaciones se aplica la regla del 65% sobre la memoria
 *   reservada.
 * - Para las inserciones se reserva directamente la memoria necesaria.
 * ============================================================================
 */

#include "modificaciones.h"
#include "tablero.h"

    /**
 * Calcula la cantidad de bytes necesarios para almacenar el tablero
 * y la cantidad de bits extras del último byte.
 */
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

/**
 * Copia el contenido del tablero original al nuevo tablero,
 * omitiendo opcionalmente una fila y/o una columna.
 *
 * filaOmite = -1 significa que no se omite ninguna fila.
 * colOmite  = -1 significa que no se omite ninguna columna.
 */
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

/**
 * Elimina una fila del tablero.
 *
 * Se crea un nuevo bloque de memoria, se copian todas las filas excepto
 * la seleccionada y posteriormente se libera el bloque anterior.
 *
 * Se aplica la regla del 65% para decidir si se reduce la memoria reservada.
 */
bool eliminarFila(
    unsigned char*& ptrTablero,
    unsigned short &filas,
    unsigned short columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short filaAEliminar
    )
{
    // El tablero debe conservar al menos una fila.
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

    // Se conserva la memoria actual salvo que la nueva necesidad
    // represente menos del 65% de la memoria reservada.
    unsigned short bytesAReservar = bytesReservados;

    if (bytesNecesarios < 0.65 * bytesReservados) {
        bytesAReservar = bytesNecesarios;
    }

    // La reserva nunca puede ser menor que la memoria necesaria.
    if (bytesAReservar < bytesNecesarios) {
        bytesAReservar = bytesNecesarios;
    }

    unsigned char* nuevoTablero =
        crearTablero(bytesAReservar);

    if (!nuevoTablero) {
        return false;
    }

    // Copiar todas las filas excepto la seleccionada.
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

    // Liberar el bloque anterior.
    delete[] ptrTablero;

    // Actualizar el estado del tablero.
    ptrTablero = nuevoTablero;
    filas = nuevasFilas;
    bitsExtras = nuevosBitsExtras;
    bytesReservados = bytesAReservar;

    return true;
}

/**
 * Elimina una columna del tablero.
 *
 * Se crea un nuevo bloque, se copian todas las columnas excepto la
 * seleccionada y se libera la memoria anterior.
 */
bool eliminarColumna(
    unsigned char*& ptrTablero,
    unsigned short filas,
    unsigned short &columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short colAEliminar
    )
{
    // El tablero debe conservar al menos una columna.
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

    // La reserva nunca puede ser menor que la memoria necesaria.
    if (bytesAReservar < bytesNecesarios) {
        bytesAReservar = bytesNecesarios;
    }

    unsigned char* nuevoTablero =
        crearTablero(bytesAReservar);

    if (!nuevoTablero) {
        return false;
    }

    // Copiar todas las columnas excepto la seleccionada.
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

/**
 * Agrega una nueva fila en la posición indicada por el usuario.
 *
 * La posición ingresada por el usuario comienza en 1:
 *
 * 1 = antes de la primera fila
 * 2 = antes de la segunda fila
 * ...
 * filas + 1 = después de la última fila
 */
bool agregarFila(
    unsigned char*& ptrTablero,
    unsigned short &filas,
    unsigned short columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short posFilaUser
    )
{
    // La posición válida va desde 1 hasta filas + 1.
    if (posFilaUser < 1 || posFilaUser > filas + 1) {
        return false;
    }

    // Convertir posición del usuario a índice base 0.
    unsigned short posFila = posFilaUser - 1;

    unsigned short nuevasFilas = filas + 1;

    unsigned short bytesNecesarios;
    unsigned short nuevosBitsExtras;

    calcularDimensionesBits(
        nuevasFilas,
        columnas,
        bytesNecesarios,
        nuevosBitsExtras
        );

    // Para agregar se reserva la cantidad exacta necesaria.
    unsigned char* nuevoTablero =
        crearTablero(bytesNecesarios);

    if (!nuevoTablero) {
        return false;
    }

    // Copiar las filas existentes desplazando una posición
    // las que están después de la posición de inserción.
    for (unsigned short f = 0; f < filas; f++) {

        unsigned short filaDestino;

        if (f >= posFila) {
            filaDestino = f + 1;
        } else {
            filaDestino = f;
        }

        for (unsigned short c = 0; c < columnas; c++) {

            unsigned char ficha =
                obtenerFicha(
                    ptrTablero,
                    f,
                    c,
                    columnas,
                    bitsExtras
                    );

            escribirFicha(
                nuevoTablero,
                filaDestino,
                c,
                columnas,
                nuevosBitsExtras,
                ficha
                );
        }
    }

    // Generar las fichas aleatorias de la nueva fila.
    for (unsigned short c = 0; c < columnas; c++) {

        escribirFicha(
            nuevoTablero,
            posFila,
            c,
            columnas,
            nuevosBitsExtras,
            generarFichaRandom()
            );
    }

    // Liberar la memoria anterior.
    delete[] ptrTablero;

    // Actualizar el estado.
    ptrTablero = nuevoTablero;
    filas = nuevasFilas;
    bitsExtras = nuevosBitsExtras;
    bytesReservados = bytesNecesarios;

    return true;
}

/**
 * Agrega una nueva columna en la posición indicada por el usuario.
 *
 * La posición ingresada por el usuario comienza en 1:
 *
 * 1 = antes de la primera columna
 * 2 = antes de la segunda columna
 * ...
 * columnas + 1 = después de la última columna
 */
bool agregarColumna(
    unsigned char*& ptrTablero,
    unsigned short filas,
    unsigned short &columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned short posColUser
    )
{
    // La posición válida va desde 1 hasta columnas + 1.
    if (posColUser < 1 || posColUser > columnas + 1) {
        return false;
    }

    unsigned short nuevasColumnas = columnas + 1;

    unsigned short bytesNuevos;
    unsigned short bitsExtrasNuevos;

    calcularDimensionesBits(
        filas,
        nuevasColumnas,
        bytesNuevos,
        bitsExtrasNuevos
        );

    // Para agregar se reserva la cantidad exacta necesaria.
    unsigned char* nuevoTablero =
        crearTablero(bytesNuevos);

    if (!nuevoTablero) {
        return false;
    }

    // Convertir posición del usuario a índice base 0.
    unsigned short colIdx = posColUser - 1;

    // Recorrer todas las posiciones del nuevo tablero.
    for (unsigned short f = 0; f < filas; f++) {

        for (unsigned short c = 0; c < nuevasColumnas; c++) {

            unsigned char valorFicha;

            if (c < colIdx) {

                // Las columnas anteriores permanecen en la misma posición.
                valorFicha =
                    obtenerFicha(
                        ptrTablero,
                        f,
                        c,
                        columnas,
                        bitsExtras
                        );

            } else if (c == colIdx) {

                // Esta es la nueva columna.
                valorFicha = generarFichaRandom();

            } else {

                // Las columnas posteriores se desplazan una posición.
                valorFicha =
                    obtenerFicha(
                        ptrTablero,
                        f,
                        c - 1,
                        columnas,
                        bitsExtras
                        );
            }

            escribirFicha(
                nuevoTablero,
                f,
                c,
                nuevasColumnas,
                bitsExtrasNuevos,
                valorFicha
                );
        }
    }

    // Liberar el bloque anterior.
    delete[] ptrTablero;

    // Actualizar el estado.
    ptrTablero = nuevoTablero;
    columnas = nuevasColumnas;
    bitsExtras = bitsExtrasNuevos;
    bytesReservados = bytesNuevos;

    return true;
}