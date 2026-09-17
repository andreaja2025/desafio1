#ifndef TABLERO_H
#define TABLERO_H

/**
 * ============================================================================
 * MÓDULO: Tablero
 * ARCHIVO: tablero.h
 * ----------------------------------------------------------------------------
 * DESCRIPCIÓN:
 * Este módulo contiene la lógica de bajo nivel para el manejo del tablero de
 * juego empaquetado en memoria. Opera sobre un arreglo unidimensional dinámico
 * de tipo `unsigned char*`.
 *
 * DISTRIBUCIÓN DE FUNCIONES:
 * - Reserva y liberación de memoria física (`crearTablero`).
 * - Operaciones Bitwise de lectura/escritura (`obtenerFicha`, `escribirFicha`).
 * - Modificación rápida de casillas (`eliminarFicha`).
 * - Generación e inicialización aleatoria de datos (`generarFichaRandom`,
 *   `llenarTableroRandom`).
 *
 * NOTA DE DISEÑO:
 * Este módulo está separado de la interfaz gráfica y de la lógica del juego,
 * incluyendo las cascadas y los combos.
 * ============================================================================
 */

// Gestión e Impresión
unsigned char* crearTablero(unsigned short bytesTab);

// Recibe 4 parámetros (se agrega bitsExtras)
void verTableroBits(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short bitsExtras);
void verTableroFichas(unsigned char* ptrTablero, unsigned short fil, unsigned short col);

// Operaciones de Bajo Nivel
unsigned char obtenerFicha(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short totalCols, unsigned short bitsExtras);
void escribirFicha(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short totalCols, unsigned short bitsExtras, unsigned char valor);

// Acciones del Juego
void eliminarFicha(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short totalCols, unsigned short bitsExtras);

// Generación de Fichas
unsigned char generarFichaRandom();
void llenarTableroRandom(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short bitsExtras);

#endif // TABLERO_H
