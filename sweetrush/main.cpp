/*
Trabajo para la asignatura de informática 2
de la Universidad de Antioquia
Desafio 1.
*/
#include <iostream>
#include "tablero.h"

using namespace std;

int main()
{
    cout << "=================================" << endl;
    cout << "     BIENVENID@ A SWEET CRUSH    " << endl;
    cout << "=================================" << endl;

    unsigned short filas, columnas;
    cout << "\nDe cuantas filas quiere su tablero?: ";
    cin >> filas;
    cout << "Y cuantas columnas?: ";
    cin >> columnas;

    unsigned int bits = filas * columnas * 3;
    unsigned short bytes = (bits % 8 != 0) ? (bits / 8 + 1) : (bits / 8);
    unsigned int bitsReserv = bytes * 8;
    short bitsExtras = bitsReserv - bits;

    unsigned char *pTab = crearTablero(bytes);

    // =========================================================================
    // OPCIÓN PROVISIONAL: Llenar el tablero con fichas de prueba (valores de 1 a 7)
    // =========================================================================
    for (short f = 0; f < filas; f++) {
        for (short c = 0; c < columnas; c++) {
            // Asigna valores alternados entre 1 y 7 usando la fórmula ((f + c) % 7) + 1
            unsigned char valPrueba = ((f + c) % 7) + 1;
            escribirFicha(pTab, f, c, columnas, bitsExtras, valPrueba);
        }
    }
    // =========================================================================

    // Muestra los tableros iniciales
    verTableroBits(pTab, filas, columnas);
    verTableroFichas(pTab, filas, columnas);

    int opcion = 0;
    do {
        // Menú de opciones
        cout << "\n--- MENU DE OPCIONES ---" << endl;
        cout << "1. Eliminar una Ficha" << endl;
        cout << "2. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            short fElegida, cElegida;
            cout << "\n[ ELIMINAR FICHA ]" << endl;

            // Pedir coordenadas e informar el rango válido
            cout << "Ingrese la Fila (01 a " << (filas < 10 ? "0" : "") << filas << "): ";
            cin >> fElegida;
            cout << "Ingrese la Columna (01 a " << (columnas < 10 ? "0" : "") << columnas << "): ";
            cin >> cElegida;

            // Validación de entradas dentro del rango
            if (fElegida >= 1 && fElegida <= filas && cElegida >= 1 && cElegida <= columnas) {
                // Se convierte de 1-based (usuario) a 0-based (arreglo)
                eliminarFicha(pTab, fElegida - 1, cElegida - 1, columnas, bitsExtras);

                cout << "\nFicha en (" << (fElegida < 10 ? "0" : "") << fElegida
                     << ", " << (cElegida < 10 ? "0" : "") << cElegida
                     << ") eliminada exitosamente." << endl;

                // Mostrar el resultado en ambos tableros
                verTableroBits(pTab, filas, columnas);
                verTableroFichas(pTab, filas, columnas);
            } else {
                cout << "\nCoordenadas fuera de rango. Operacion cancelada." << endl;
            }
        } else if (opcion != 2) {
            cout << "\nOpcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 2);

    // Liberación de memoria
    delete[] pTab;
    cout << "\n¡Gracias por jugar Sweet Crush!" << endl;
    return 0;
}