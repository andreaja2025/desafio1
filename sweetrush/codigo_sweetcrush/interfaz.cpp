#include "interfaz.h"
#include "tablero.h"
#include "juego.h"

#include <iostream>

using namespace std;

void mostrarBienvenida()
{
    cout << "=================================" << endl;
    cout << "     BIENVENID@ A SWEET CRUSH    " << endl;
    cout << "=================================" << endl;
}

void mostrarMenu(unsigned short &opcion)
{
    cout << "\n--- MENU DE OPCIONES ---" << endl;
    cout << "1. Eliminar Ficha" << endl;
    cout << "2. Eliminar Fila" << endl;
    cout << "3. Eliminar Columna" << endl;
    cout << "4. Agregar Fila" << endl;
    cout << "5. Agregar Columna" << endl;
    cout << "6. Fin" << endl;
    cout << "Seleccione una opcion: ";

    cin >> opcion;
}

void ejecutarOpcion(
    unsigned short opcion,
    unsigned char*& pTab,
    unsigned short filas,
    unsigned short columnas,
    unsigned short bitsExtras,
    unsigned int &puntuacionAcumulada,
    unsigned int &eliminacionesUsuario,
    unsigned int &totalFichasEliminadas,
    unsigned int &combinacionesDetectadas
    )
{
    switch (opcion) {

    case 1: {
        unsigned short fElegida;
        unsigned short cElegida;

        cout << "\n[ ELIMINAR FICHA ]" << endl;
        cout << "Ingrese la Fila (1 a " << filas << "): ";
        cin >> fElegida;

        cout << "Ingrese la Columna (1 a " << columnas << "): ";
        cin >> cElegida;

        if (fElegida >= 1 && fElegida <= filas &&
            cElegida >= 1 && cElegida <= columnas) {

            eliminarFicha(
                pTab,
                fElegida - 1,
                cElegida - 1,
                columnas,
                bitsExtras
                );

            eliminacionesUsuario++;

            cout << "\n--> Aplicando cascada automatica y evaluando posibles combinaciones" << endl;

            subrutinaCascada(
                pTab,
                filas,
                columnas,
                bitsExtras
                );

            subrutinaCombinaciones(
                pTab,
                filas,
                columnas,
                bitsExtras,
                puntuacionAcumulada,
                totalFichasEliminadas,
                combinacionesDetectadas
                );

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
        break;

    default:
        cout << "\nRespuesta invalida." << endl;
        break;
    }
}

void mostrarResumenFinal(
    unsigned int puntuacionAcumulada,
    unsigned int eliminacionesUsuario,
    unsigned int totalFichasEliminadas,
    unsigned int combinacionesDetectadas
    )
{
    cout << "\n=== RESUMEN FINAL DE ESTADISTICAS ===" << endl;
    cout << "Puntuacion acumulada: " << puntuacionAcumulada << endl;
    cout << "Eliminaciones del usuario: " << eliminacionesUsuario << endl;
    cout << "Total de fichas eliminadas: " << totalFichasEliminadas << endl;
    cout << "Combinaciones detectadas: " << combinacionesDetectadas << endl;
    cout << "\n¡Gracias por jugar Sweet Crush!" << endl;
}