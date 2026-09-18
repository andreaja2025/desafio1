#include <iostream>
#include <iomanip>

#include "interfaz.h"
#include "tablero.h"
#include "juego.h"
#include "modificaciones.h"

    using namespace std;

void mostrarBienvenida()
{
    cout << "\n";
    cout << "  ====================================================================================\n";
    cout << "   ((((()  (  (  (  ((((((  ((((((  ((((((    ((((((  ((((()  (    (  ((((()  (    (\n";
    cout << "  ((       (  (  (  ((      ((        ((      ((      ((   (  (    (  ((      (    (\n";
    cout << "   ((((()  (  (  (  (((((   (((((     ((      ((      ((((()  (    (   ((((() ((((((\n";
    cout << "       HH   H H H   H       H         HH      HH      H  HH   H    H       HH H    H\n";
    cout << "  HHHHHHH   H H H   HHHHHH  HHHHHH    HH      HHHHHH  H    HH HHHHHH  HHHHHHH H    H\n";
    cout << "  HHHHHH     H H    HHHHHH  HHHHHH    HH      HHHHHH  H    HH HHHHHH  HHHHHH  H    H\n";
    cout << "\n";
    cout << "                                 DESAFIO 1 : SWEET CRUSH                              \n";
    cout << "  ====================================================================================\n";
}

void mostrarMonitorMemoria(
    const unsigned char* pTab,
    unsigned short filas,
    unsigned short columnas,
    unsigned short bytesReservados
    )
{
    unsigned int bitsUtiles = filas * columnas * 3;

    unsigned short bytesUtiles =
        (bitsUtiles % 8 != 0)
            ? (bitsUtiles / 8 + 1)
            : (bitsUtiles / 8);

    cout << "\n";
    cout << "  +---------------------------------------------------------------------------------+\n";
    cout << "  | ESTADO DEL BUFFER DE MEMORIA DINAMICA (HEAP)                                    |\n";
    cout << "  +---------------------------------------------------------------------------------+\n";

    /*
     * Se pasa el puntero a const void* mediante una asignacion implicita.
     * No se utiliza ningun cast.
     */
    const void* direccion = pTab;

    cout << "  Puntero Base (RAM)     : " << direccion << "\n";

    cout << "  Memoria Utilizada      : "
         << bytesUtiles
         << " bytes ("
         << bitsUtiles
         << " bits requeridos para la matriz)\n";

    cout << "  Memoria Reservada      : "
         << bytesReservados
         << " bytes (Bloque fisico asignado en Heap)\n";
}

void mostrarEstadisticasJugada(
    unsigned int puntuacionTurno,
    unsigned int puntuacionTotal,
    unsigned int fichasTurno,
    unsigned int fichasTotal,
    unsigned int combosTurno
    )
{
    cout << "\n";
    cout << "   .------------------------------------------------------------------------------------.\n";
    cout << "   |  ESTADISTICAS Y METRICAS DE LA JUGADA                                              |\n";
    cout << "   +---------------------------------------------------+--------------------------------+\n";

    cout << "   |  Puntuacion Obtenida en este Turno                 |  +"
         << left << setw(29)
         << puntuacionTurno
         << "|\n";

    cout << "   |  Puntuacion Total Acumulada                        |  "
         << left << setw(30)
         << puntuacionTotal
         << "|\n";

    cout << "   |  Fichas Destruidas en este Turno                   |  "
         << left << setw(30)
         << fichasTurno
         << "|\n";

    cout << "   |  Total Historico de Fichas Destruidas              |  "
         << left << setw(30)
         << fichasTotal
         << "|\n";

    cout << "   |  Cascadas detectadas                               |  "
         << left << setw(30)
         << combosTurno
         << "|\n";

    cout << "   '------------------------------------------------------------------------------------'\n";
}

void mostrarMenu(unsigned short &opcion)
{
    cout << "\n";
    cout << "  +------------------ MENU DE CONTROL ------------------+\n";
    cout << "  |                                                     |\n";
    cout << "  |   [1] Eliminar Ficha Especifica                     |\n";
    cout << "  |   [2] Eliminar Fila                                 |\n";
    cout << "  |   [3] Eliminar Columna                              |\n";
    cout << "  |   [4] Insertar Fila                                 |\n";
    cout << "  |   [5] Insertar Columna                              |\n";
    cout << "  |   [6] Finalizar partida                             |\n";
    cout << "  |                                                     |\n";
    cout << "  +-----------------------------------------------------+\n";
    cout << "   Seleccione una opcion: ";

    cin >> opcion;
}

void ejecutarOpcion(
    unsigned short opcion,
    unsigned char*& pTab,
    unsigned short &filas,
    unsigned short &columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned int &puntuacion,
    unsigned int &eliminacionesUser,
    unsigned int &totalFichasElim,
    unsigned int &combDetectadas
    )
{
    // Estado anterior para calcular las metricas del turno.
    unsigned int pAnt = puntuacion;
    unsigned int fAnt = totalFichasElim;
    unsigned int cAnt = combDetectadas;

    bool accionEjecutada = false;

    switch (opcion) {

    case 1: {

        unsigned short fElegida;
        unsigned short cElegida;

        cout << "\n[ ELIMINAR FICHA ]\n";

        cout << "Ingrese la Fila (1 a "
             << filas
             << "): ";

        cin >> fElegida;

        cout << "Ingrese la Columna (1 a "
             << columnas
             << "): ";

        cin >> cElegida;

        if (fElegida >= 1 &&
            fElegida <= filas &&
            cElegida >= 1 &&
            cElegida <= columnas) {

            eliminarFicha(
                pTab,
                fElegida - 1,
                cElegida - 1,
                columnas,
                bitsExtras
                );

            eliminacionesUser++;

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
                puntuacion,
                totalFichasElim,
                combDetectadas
                );

            accionEjecutada = true;

        } else {

            cout << "\nCoordenadas fuera de rango.\n";
        }

        break;
    }

    case 2: {

        unsigned short filaAEliminar;

        cout << "\n[ ELIMINAR FILA ]\n";

        cout << "Ingrese el numero de Fila a eliminar (1 a "
             << filas
             << "): ";

        cin >> filaAEliminar;

        if (filaAEliminar >= 1 &&
            filaAEliminar <= filas) {

            bool exito =
                eliminarFila(
                    pTab,
                    filas,
                    columnas,
                    bitsExtras,
                    bytesReservados,
                    filaAEliminar - 1
                    );

            if (exito) {

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
                    puntuacion,
                    totalFichasElim,
                    combDetectadas
                    );

                accionEjecutada = true;

            } else {

                cout << "\n[Error] No se puede eliminar la fila "
                        "(el tablero debe tener mas de 1 fila).\n";
            }

        } else {

            cout << "\nNumero de fila fuera de rango.\n";
        }

        break;
    }

    case 3: {

        unsigned short colAEliminar;

        cout << "\n[ ELIMINAR COLUMNA ]\n";

        cout << "Ingrese el numero de Columna a eliminar (1 a "
             << columnas
             << "): ";

        cin >> colAEliminar;

        if (colAEliminar >= 1 &&
            colAEliminar <= columnas) {

            bool exito =
                eliminarColumna(
                    pTab,
                    filas,
                    columnas,
                    bitsExtras,
                    bytesReservados,
                    colAEliminar - 1
                    );

            if (exito) {

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
                    puntuacion,
                    totalFichasElim,
                    combDetectadas
                    );

                accionEjecutada = true;

            } else {

                cout << "\n[Error] No se puede eliminar la columna "
                        "(el tablero debe tener mas de 1 columna).\n";
            }

        } else {

            cout << "\nNumero de columna fuera de rango.\n";
        }

        break;
    }

    case 4: {

        unsigned short posFila;

        cout << "\n[ AGREGAR FILA ]\n";

        cout << "En que posicion desea insertar la fila? (1 a "
             << (filas + 1)
             << "): ";

        cin >> posFila;

        if (agregarFila(
                pTab,
                filas,
                columnas,
                bitsExtras,
                bytesReservados,
                posFila)) {

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
                puntuacion,
                totalFichasElim,
                combDetectadas
                );

            accionEjecutada = true;

        } else {

            cout << "\n[Error] Posicion invalida o fuera de rango.\n";
        }

        break;
    }

    case 5: {

        unsigned short posCol;

        cout << "\n[ AGREGAR COLUMNA ]\n";

        cout << "En que posicion desea insertar la columna? (1 a "
             << (columnas + 1)
             << "): ";

        cin >> posCol;

        if (agregarColumna(
                pTab,
                filas,
                columnas,
                bitsExtras,
                bytesReservados,
                posCol)) {

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
                puntuacion,
                totalFichasElim,
                combDetectadas
                );

            accionEjecutada = true;

        } else {

            cout << "\n[!] Error: Posicion invalida o fallo en "
                    "asignacion de memoria.\n";
        }

        break;
    }

    default:

        cout << "\nRespuesta invalida.\n";

        break;
    }

    // Mostrar las metricas correspondientes a la accion realizada.
    if (accionEjecutada) {

        unsigned int pTurno =
            puntuacion - pAnt;

        unsigned int fTurno =
            totalFichasElim - fAnt;

        unsigned int cTurno =
            combDetectadas - cAnt;

        mostrarEstadisticasJugada(
            pTurno,
            puntuacion,
            fTurno,
            totalFichasElim,
            cTurno
            );
    }
}

void mostrarResumenFinal(
    unsigned int puntuacionAcumulada,
    unsigned int eliminacionesUsuario,
    unsigned int totalFichasEliminadas,
    unsigned int combinacionesDetectadas
    )
{
    cout << "\n";
    cout << "  ========================================================================================\n";
    cout << "                               RESUMEN FINAL DE LA SESION DE JUEGO                        \n";
    cout << "  ========================================================================================\n";

    cout << "   .------------------------------------------------------------------------------------.\n";
    cout << "   |  PARAMETRO / METRICA                               |  VALOR REGISTRADO              |\n";
    cout << "   +---------------------------------------------------+--------------------------------+\n";

    cout << "   |  Puntuacion Total Acumulada                        |  "
         << left << setw(30)
         << puntuacionAcumulada
         << "|\n";

    cout << "   |  Intervenciones Directas del Usuario               |  "
         << left << setw(30)
         << eliminacionesUsuario
         << "|\n";

    cout << "   |  Total de Fichas Destruidas (Cascada + Usuario)    |  "
         << left << setw(30)
         << totalFichasEliminadas
         << "|\n";

    cout << "   |  Combinaciones Evaluadas (Combos)                  |  "
         << left << setw(30)
         << combinacionesDetectadas
         << "|\n";

    cout << "   '------------------------------------------------------------------------------------'\n";
    cout << "  ========================================================================================\n";
    cout << "   Fin del juego\n";
}
