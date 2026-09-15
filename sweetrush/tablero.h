#ifndef TABLERO_H
#define TABLERO_H

// Gestión e Impresión
unsigned char* crearTablero(unsigned short bytesTab);
void verTableroBits(unsigned char* ptrTablero, short fil, short col);

// Extrae los 3 bits de una coordenada y devuelve el carácter correspondiente (@, $, #, etc.)
void verTableroFichas(unsigned char* ptrTablero, short fil, short col);

// Operaciones de Bajo Nivel (Reutilizables para cualquier acción del juego)
unsigned char obtenerFicha(unsigned char* ptrTablero, short fil, short col, short totalCols, short bitsExtras);
void escribirFicha(unsigned char* ptrTablero, short fil, short col, short totalCols, short bitsExtras, unsigned char valor);

// Acciones del Juego
void eliminarFicha(unsigned char* ptrTablero, short fil, short col, short totalCols, short bitsExtras);

#endif // TABLERO_H
