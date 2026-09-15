#include "tablero.h"
#include <iostream>

using namespace std;

unsigned char* crearTablero(unsigned short bytesTab) {
    //esta funcion se encarga de reservar el espacio necesario
    //para el tablero solicitado, podría asignar a todos los espacios un
    //vacio pero lo mejor será que no a menos de ser necesario

    unsigned char* tab = new unsigned char[bytesTab] {}; //incializado en 0
    return tab;
}

void verTableroBits(unsigned char* ptrTablero, short fil, short col){
    unsigned int bitsTab = fil*col*3; //bits
    short bytesTab = 0;
    if(bitsTab%8!=0){ //bytes precisos que requiere el tablero
        bytesTab = bitsTab/8+1;
    } else bytesTab = bitsTab/8;
    //int cantFichas = fil*col; //esto x3 sería lo que se imprime
    unsigned int bitsReserv = bytesTab*8;
    short byteInicial = 0; //primer byte del tablero jugable
    short bitsExtras = bitsReserv-bitsTab; //bit del 3er byte donde incia el tablero jugable
    //unsigned short bitTabActual =  ;

    cout << "bitsTab: " << bitsTab <<endl;
    cout << "bitsReserv: " << bitsReserv <<endl;
    cout << "bitsExtras: " << bitsExtras <<endl;
    cout << "Byte incial del tablero reservado: ";
    for (int bit = 8; bit > 0; bit--) {
        cout << ((ptrTablero[0] >> bit) & 1);
    }
    cout <<endl;

    for (short i = 0; i<=col; i++){
        if (i<10){
            cout << '0'<< i << "  ";
        } else cout << i << "  ";
    }

    short cont3bits = 0;
    short contFilas = 1;

    for (int i = byteInicial; i < bytesTab; i++) {
        for (int bit = 8; bit > 0; bit--) {
            if (cont3bits%((col*3)) == 0) {
                cout << endl;
                if (contFilas<10) cout << '0'<< contFilas;
                else cout << contFilas;
                contFilas++;
            }
            if ((cont3bits%3) == 0) cout << " ";
            //los condicionales sgtes son claves pa no imprimir los bits vacios a la izq
            if (i==byteInicial) {          //(8-bitsExtras)
                cout << ((ptrTablero[i] >> (bit-bitsExtras)) & 1);
                cont3bits++;
                if (bit-bitsExtras==1) break; //sale del for cuando se acaba el 1er byte
            }

            else {
                cout << ((ptrTablero[i] >> bit) & 1);
                cont3bits++;
            }
        }
    }
}

// Extrae una ficha de 3 bits utilizando operaciones de byte completo (máscaras y desplazamientos)
unsigned char obtenerFicha(unsigned char* ptrTablero, short fil, short col, short totalCols, short bitsExtras) {
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
        short bitsEnPrimerByte = 8 - bitDentroByte;
        short bitsEnSegundoByte = 3 - bitsEnPrimerByte;

        unsigned char parteAlta = (ptrTablero[numByte] & ((1 << bitsEnPrimerByte) - 1)) << bitsEnSegundoByte;
        unsigned char parteBaja = ptrTablero[numByte + 1] >> (8 - bitsEnSegundoByte);

        valor = parteAlta | parteBaja;
    }

    return valor;
}

// Escribe un valor de 3 bits (0 a 7) en una posición específica de memoria dinámica
void escribirFicha(unsigned char* ptrTablero, short fil, short col, short totalCols, short bitsExtras, unsigned char valor) {
    unsigned int bitInicio = bitsExtras + (fil * totalCols + col) * 3;
    unsigned int numByte = bitInicio / 8;
    unsigned int bitDentroByte = bitInicio % 8;

    valor &= 0x07; // Garantiza el enmascaramiento exacto a 3 bits

    // Caso 1: Los 3 bits están completamente dentro del mismo byte
    if (bitDentroByte <= 5) {
        short desp = 5 - bitDentroByte;
        unsigned char mascara = ~(0x07 << desp);
        ptrTablero[numByte] = (ptrTablero[numByte] & mascara) | (valor << desp);
    }
    // Caso 2: La ficha está dividida entre dos bytes consecutivos
    else {
        short bitsEnPrimerByte = 8 - bitDentroByte;
        short bitsEnSegundoByte = 3 - bitsEnPrimerByte;

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

void verTableroFichas(unsigned char* ptrTablero, short fil, short col) {
    unsigned int bitsTab = fil * col * 3;
    short bytesTab = (bitsTab % 8 != 0) ? (bitsTab / 8 + 1) : (bitsTab / 8);
    unsigned int bitsReserv = bytesTab * 8;
    short bitsExtras = bitsReserv - bitsTab;

    cout << "\n=== TABLERO JUGABLE ===" << endl;

    // Encabezado de columnas desde 01
    cout << "00  ";
    for (short c = 1; c <= col; c++) {
        if (c < 10) cout << "0" << c << " ";
        else cout << c << " ";
    }
    cout << endl;

    // Filas con fichas
    for (short f = 0; f < fil; f++) {
        if (f + 1 < 10) cout << "0" << (f + 1) << "  ";
        else cout << (f + 1) << "  ";

        for (short c = 0; c < col; c++) {
            unsigned char valor = obtenerFicha(ptrTablero, f, c, col, bitsExtras);
            char simbolo = obtenerSimbolo(valor);
            cout << " " << simbolo << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// Cambia la ficha en la posición especificada al estado Vacío (@ / 0)
void eliminarFicha(unsigned char* ptrTablero, short fil, short col, short totalCols, short bitsExtras) {
    escribirFicha(ptrTablero, fil, col, totalCols, bitsExtras, 0);
}