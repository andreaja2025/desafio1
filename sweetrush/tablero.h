#ifndef TABLERO_H
#define TABLERO_H

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

// Generación de Fichas (¡Asegúrate de tener ambas aquí!)
unsigned char generarFichaRandom();
void llenarTableroRandom(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short bitsExtras);

#endif // TABLERO_H
