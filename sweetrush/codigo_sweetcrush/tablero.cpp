#include "tablero.h"
#include <iostream>
#include <cstdlib> // para utilizar rand() en generarFichaRandom()

/**
 * ============================================================================
 * ARCHIVO: tablero.cpp
 * IMPLEMENTACIÓN: Módulo de Memoria y Bitwise
 * ----------------------------------------------------------------------------
 * Implementa las operaciones aritméticas de bits y acceso directo al arreglo
 * dinámico `unsigned char*` declarado en tablero.h.
 * ============================================================================
 */

using namespace std;

unsigned char* crearTablero(unsigned short bytesTab) {
    // esta funcion se encarga de reservar el espacio necesario
    // para el tablero solicitado, podría asignar a todos los espacios un
    // vacio pero lo mejor será que no a menos de ser necesario

    unsigned char* tab = new unsigned char[bytesTab]{}; // incializado en 0
    return tab;
}

void verTableroBits(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short bitsExtras) {
    unsigned int bitsTab = fil * col * 3;
    unsigned short bytesTab = (bitsTab % 8 != 0) ? (bitsTab / 8 + 1) : (bitsTab / 8);
    unsigned short byteInicial = 0;

    // Encabezados de columnas
    for (unsigned short i = 0; i <= col; i++) {
        if (i < 10) {
            cout << '0' << i << "  ";
        } else {
            cout << i << "  ";
        }
    }

    unsigned short cont3bits = 0;
    unsigned short contFilas = 1;

    for (unsigned short i = byteInicial; i < bytesTab; i++) {
        // Se calcula el bit inicial
        int bitInicio = (i == byteInicial) ? (7 - bitsExtras) : 7;

        for (int bit = bitInicio; bit >= 0; bit--) {
            if (cont3bits % (col * 3) == 0) {
                cout << endl;
                if (contFilas < 10) cout << '0' << contFilas;
                else cout << contFilas;
                contFilas++;
            }
            if ((cont3bits % 3) == 0) cout << " ";

            cout << ((ptrTablero[i] >> bit) & 1);
            cont3bits++;
        }
    }
    cout << endl;
}


// Genera un valor aleatorio de ficha (1 a 6)
unsigned char generarFichaRandom() {
    return (rand() % 6) + 1;
}

// Recorre todas las posiciones escribiendo una ficha aleatoria
void llenarTableroRandom(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short bitsExtras) {
    for (unsigned short f = 0; f < fil; f++) {
        for (unsigned short c = 0; c < col; c++) {
            escribirFicha(ptrTablero, f, c, col, bitsExtras, generarFichaRandom());
        }
    }
}

// Extrae una ficha de 3 bits utilizando operaciones de byte completo (máscaras y desplazamientos)
unsigned char obtenerFicha(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short totalCols, unsigned short bitsExtras) {
    unsigned int bitInicio = bitsExtras + (fil * totalCols + col) * 3;
    unsigned int numByte = bitInicio / 8;
    unsigned int bitDentroByte = bitInicio % 8;

    unsigned char valor = 0;

    // Caso 1: Los 3 bits están completamente dentro del mismo byte
    if (bitDentroByte <= 5) {
        valor = (ptrTablero[numByte] >> (5 - bitDentroByte)) & 0x07;
    }
    // Caso 2: La ficha está dividida entre dos bytes consecutivos
    else {
        unsigned short bitsEnPrimerByte = 8 - bitDentroByte;
        unsigned short bitsEnSegundoByte = 3 - bitsEnPrimerByte;

        unsigned char parteAlta = (ptrTablero[numByte] & ((1 << bitsEnPrimerByte) - 1)) << bitsEnSegundoByte;
        unsigned char parteBaja = ptrTablero[numByte + 1] >> (8 - bitsEnSegundoByte);

        valor = parteAlta | parteBaja;
    }

    return valor;
}

// Escribe un valor de 3 bits (0 a 7) en una posición específica de memoria dinámica
void escribirFicha(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short totalCols, unsigned short bitsExtras, unsigned char valor) {
    unsigned int bitInicio = bitsExtras + (fil * totalCols + col) * 3;
    unsigned int numByte = bitInicio / 8;
    unsigned int bitDentroByte = bitInicio % 8;

    valor &= 0x07; // Garantiza el enmascaramiento exacto a 3 bits

    // Caso 1: Los 3 bits están completamente dentro del mismo byte
    if (bitDentroByte <= 5) {
        unsigned short desp = 5 - bitDentroByte;
        unsigned char mascara = ~(0x07 << desp);
        ptrTablero[numByte] = (ptrTablero[numByte] & mascara) | (valor << desp);
    }
    // Caso 2: La ficha está dividida entre dos bytes consecutivos
    else {
        unsigned short bitsEnPrimerByte = 8 - bitDentroByte;
        unsigned short bitsEnSegundoByte = 3 - bitsEnPrimerByte;

        unsigned char mascara1 = ~((1 << bitsEnPrimerByte) - 1);
        unsigned char parteAlta = valor >> bitsEnSegundoByte;
        ptrTablero[numByte] = (ptrTablero[numByte] & mascara1) | parteAlta;

        unsigned char mascara2 = ~(~((1 << (8 - bitsEnSegundoByte)) - 1));
        unsigned char parteBaja = valor << (8 - bitsEnSegundoByte);
        ptrTablero[numByte + 1] = (ptrTablero[numByte + 1] & mascara2) | parteBaja;
    }
}

// Mapea el número de 3 bits (0 a 7) al símbolo visual
char obtenerSimbolo(unsigned char valor) {
    switch (valor) {
    case 0: return '@'; // Vacío
    case 1: return '$';
    case 2: return '#';
    case 3: return 'O';
    case 4: return '%';
    case 5: return '?';
    case 6: return 'X';
    default: return 'R';
    }
}

void verTableroFichas(unsigned char* ptrTablero, unsigned short fil, unsigned short col) {
    unsigned int bitsTab = fil * col * 3;
    unsigned short bytesTab = (bitsTab % 8 != 0) ? (bitsTab / 8 + 1) : (bitsTab / 8);
    unsigned int bitsReserv = bytesTab * 8;
    unsigned short bitsExtras = bitsReserv - bitsTab;

    cout << "\n=== TABLERO JUGABLE ===" << endl;

    // Encabezado de columnas
    cout << "00  ";
    for (unsigned short c = 1; c <= col; c++) {
        if (c < 10) cout << "0" << c << " ";
        else cout << c << " ";
    }
    cout << endl;

    // Filas con fichas
    for (unsigned short f = 0; f < fil; f++) {
        if (f + 1 < 10) cout << "0" << (f + 1) << "  ";
        else cout << (f + 1) << "  ";

        for (unsigned short c = 0; c < col; c++) {
            unsigned char valor = obtenerFicha(ptrTablero, f, c, col, bitsExtras);
            char simbolo = obtenerSimbolo(valor);
            cout << " " << simbolo << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Cambia la ficha en la posición especificada al estado Vacío (@ / 0)
void eliminarFicha(unsigned char* ptrTablero, unsigned short fil, unsigned short col, unsigned short totalCols, unsigned short bitsExtras) {
    escribirFicha(ptrTablero, fil, col, totalCols, bitsExtras, 0);
}