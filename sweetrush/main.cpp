/*
Trabajo para la asignatura de informática 2
de la Universidad de Antioquia
Desafio 1.
*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"
#include "juego.h"

using namespace std;

int main()
{
    srand(time(NULL));

    cout << "=================================" << endl;
    cout << "     BIENVENID@ A SWEET CRUSH    " << endl;
    cout << "=================================" << endl;

    unsigned short filas, columnas;
    cout << "\nDe cuantas filas quiere su tablero?: ";
    cin >> filas;
    cout << "Y cuantas columnas?: ";
    cin >> columnas;

    // Cálculo de dimensiones de memoria
    unsigned int bits = filas * columnas * 3;
    unsigned short bytes = (bits % 8 != 0) ? (bits / 8 + 1) : (bits / 8);
    unsigned int bitsReserv = bytes * 8;
    unsigned short bitsExtras = bitsReserv - bits;

    // Inicialización del tablero
    unsigned char *pTab = crearTablero(bytes);
    llenarTableroRandom(pTab, filas, columnas, bitsExtras);

    // Variables de estadísticas optimizadas (sin signo)
    unsigned int puntuacionAcumulada = 0;
    unsigned int eliminacionesUsuario = 0;
    unsigned int totalFichasEliminadas = 0;
    unsigned int combinacionesDetectadas = 0;

    unsigned short opcion = 0;
    do {
        // Se le pasa 'bitsExtras' a verTableroBits
        verTableroBits(pTab, filas, columnas, bitsExtras);
        verTableroFichas(pTab, filas, columnas);

        // Menú Principal
        cout << "\n--- MENU DE OPCIONES ---" << endl;
        cout << "1. Eliminar Ficha" << endl;
        cout << "2. Eliminar Fila" << endl;
        cout << "3. Eliminar Columna" << endl;
        cout << "4. Agregar Fila" << endl;
        cout << "5. Agregar Columna" << endl;
        cout << "6. Fin" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: {
            unsigned short fElegida, cElegida;
            cout << "\n[ ELIMINAR FICHA ]" << endl;
            cout << "Ingrese la Fila (1 a " << filas << "): ";
            cin >> fElegida;
            cout << "Ingrese la Columna (1 a " << columnas << "): ";
            cin >> cElegida;

            if (fElegida >= 1 && fElegida <= filas && cElegida >= 1 && cElegida <= columnas) {
                eliminarFicha(pTab, fElegida - 1, cElegida - 1, columnas, bitsExtras);
                eliminacionesUsuario++;

                cout << "\n--> Aplicando cascada automatica..." << endl;
                subrutinaCascada(pTab, filas, columnas, bitsExtras);
            } else {
                cout << "\nCoordenadas fuera de rango." << endl;
            }
            break;
        }

        case 2:
        case 3:
        case 4:
        case 5:
            cout << "\n[PROXIMAMENTE] Modificacion de dimensiones del tablero." << endl;
            break;

        case 6:
            delete[] pTab;
            pTab = nullptr;

            cout << "\n=== RESUMEN FINAL DE ESTADISTICAS ===" << endl;
            cout << "Puntuacion acumulada: " << puntuacionAcumulada << endl;
            cout << "Eliminaciones del usuario: " << eliminacionesUsuario << endl;
            cout << "Total de fichas eliminadas: " << totalFichasEliminadas << endl;
            cout << "Combinaciones detectadas: " << combinacionesDetectadas << endl;
            cout << "\n¡Gracias por jugar Sweet Crush!" << endl;
            return 0;

        default:
            cout << "\nRespuesta invalida." << endl;
            break;
        }

    } while (opcion != 6);

    if (pTab != nullptr) delete[] pTab;
    return 0;
}