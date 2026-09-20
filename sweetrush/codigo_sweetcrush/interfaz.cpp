#include <iostream>
#include <iomanip>

#include "interfaz.h"
#include "tablero.h"
#include "juego.h"
#include "modificaciones.h"

    using namespace std;

unsigned short leerValor(
    unsigned short minimo,
    unsigned short maximo,
    const char mensaje[]
    )
{
    unsigned short valor;

    while (true) {

        cout << mensaje;
        cin >> valor;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << ">> Error: Entrada no valida. "
                    "Por favor, ingrese un numero entero.\n";
            continue;
        }

        if (valor < minimo || valor > maximo) {
            cout << ">> Error: El valor debe estar entre "
                 << minimo << " y " << maximo << ".\n";
            continue;
        }

        cin.ignore(1000, '\n');

        return valor;
    }
}

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
    cout << "                                  DESAFIO 1 : SWEET CRUSH                             \n";
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
    unsigned short bytesUtiles;

    if (bitsUtiles % 8 != 0) {
        bytesUtiles = (bitsUtiles / 8) + 1;
    } else {
        bytesUtiles = bitsUtiles / 8;
    }

    const void* direccion = pTab;

    cout << "\n";
    cout << "  +---------------------------------------------------------------------------------+\n";
    cout << "  | ESTADO DEL BUFFER DE MEMORIA DINAMICA (HEAP)                                    |\n";
    cout << "  +---------------------------------------------------------------------------------+\n";

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
    unsigned int rondasTurno,
    unsigned int combosTurno
    )
{
    cout << "\n";
    cout << "   .------------------------------------------------------------------------------------.\n";
    cout << "   |  ESTADISTICAS Y METRICAS DE LA JUGADA                                              |\n";
    cout << "   +---------------------------------------------------+--------------------------------+\n";

    cout << "   |  Puntuacion Obtenida en este Turno                |  "
         << left << setw(30)
         << puntuacionTurno
         << "|\n";

    cout << "   |  Puntuacion Total Acumulada                       |  "
         << left << setw(30)
         << puntuacionTotal
         << "|\n";

    cout << "   |  Fichas Destruidas en este Turno                  |  "
         << left << setw(30)
         << fichasTurno
         << "|\n";

    cout << "   |  Total Historico de Fichas Destruidas             |  "
         << left << setw(30)
         << fichasTotal
         << "|\n";

    cout << "   |  Rondas de Combinacion en este Turno              |  "
         << left << setw(30)
         << rondasTurno
         << "|\n";

    cout << "   |  Combos Detectados en este Turno                  |  "
         << left << setw(30)
         << combosTurno
         << "|\n";

    cout << "   '------------------------------------------------------------------------------------'\n";
}

void mostrarMenu()
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
    unsigned int &combDetectadas,
    unsigned int &combosDetectados
    )
{
    unsigned int pAnt = puntuacion;
    unsigned int fAnt = totalFichasElim;
    unsigned int cAnt = combDetectadas;
    unsigned int combosAnt = combosDetectados;

    bool accionEjecutada = false;

    switch (opcion) {

    case 1: {
        unsigned short fElegida;
        unsigned short cElegida;

        cout << "\n[ ELIMINAR FICHA ]\n";

        cout << "Ingrese la fila (1-" << filas << "): ";
        fElegida = leerValor(1, filas, "");

        cout << "Ingrese la columna (1-" << columnas << "): ";
        cElegida = leerValor(1, columnas, "");

        eliminarFicha(
            pTab,
            fElegida - 1,
            cElegida - 1,
            columnas,
            bitsExtras
            );

        eliminacionesUser++;
        accionEjecutada = true;

        break;
    }

    case 2: {
        unsigned short filaAEliminar;

        cout << "\n[ ELIMINAR FILA ]\n";

        cout << "Ingrese la fila a eliminar (1-" << filas << "): ";
        filaAEliminar = leerValor(1, filas, "");

        bool exito = eliminarFila(
            pTab,
            filas,
            columnas,
            bitsExtras,
            bytesReservados,
            filaAEliminar - 1
            );

        if (exito) {
            eliminacionesUser++;
            accionEjecutada = true;
        } else {
            cout << "\n[Error] No se puede eliminar la fila "
                    "(el tablero debe tener mas de 1 fila).\n";
        }

        break;
    }

    case 3: {
        unsigned short colAEliminar;

        cout << "\n[ ELIMINAR COLUMNA ]\n";

        cout << "Ingrese la columna a eliminar (1-" << columnas << "): ";
        colAEliminar = leerValor(1, columnas, "");

        bool exito = eliminarColumna(
            pTab,
            filas,
            columnas,
            bitsExtras,
            bytesReservados,
            colAEliminar - 1
            );

        if (exito) {
            eliminacionesUser++;
            accionEjecutada = true;
        } else {
            cout << "\n[Error] No se puede eliminar la columna "
                    "(el tablero debe tener mas de 1 columna).\n";
        }

        break;
    }

    case 4: {
        unsigned short posFila;

        cout << "\n[ AGREGAR FILA ]\n";

        if (filas == 65535) {
            cout << ">> Error: No se puede insertar otra fila. "
                    "Se alcanzo el maximo permitido de filas.\n";
            break;
        }

        cout << "Ingrese la posicion de la nueva fila (1-"
             << filas + 1 << "): ";

        posFila = leerValor(
            1,
            filas + 1,
            ""
            );

        bool exito = agregarFila(
            pTab,
            filas,
            columnas,
            bitsExtras,
            bytesReservados,
            posFila
            );

        if (exito) {
            accionEjecutada = true;
        } else {
            cout << "\n[Error] Posicion invalida o fallo en asignacion de memoria.\n";
        }

        break;
    }

    case 5: {
        unsigned short posCol;

        cout << "\n[ AGREGAR COLUMNA ]\n";

        unsigned int maxCasillasMemoria = 174760;
        unsigned int maxColumnasMemoria = maxCasillasMemoria / filas;

        unsigned short maxColumnas = 25;

        if (maxColumnasMemoria < maxColumnas) {
            maxColumnas = maxColumnasMemoria;
        }

        if (columnas >= maxColumnas) {
            cout << ">> Error: No se puede insertar otra columna. "
                    "Se alcanzo el maximo permitido de "
                 << maxColumnas << " columnas.\n";
            break;
        }

        cout << "Ingrese la posicion de la nueva columna (1-"
             << columnas + 1 << "): ";

        posCol = leerValor(
            1,
            columnas + 1,
            ""
            );

        bool exito = agregarColumna(
            pTab,
            filas,
            columnas,
            bitsExtras,
            bytesReservados,
            posCol
            );

        if (exito) {
            accionEjecutada = true;
        } else {
            cout << "\n[!] Error: Posicion invalida o fallo en asignacion de memoria.\n";
        }

        break;
    }

    default:
        cout << "\nRespuesta invalida.\n";
        break;
    }

    if (accionEjecutada) {

        bool huboCombinacion = false;

        do {

            subrutinaCascada(
                pTab,
                filas,
                columnas,
                bitsExtras
                );

            huboCombinacion = subrutinaCombinaciones(
                pTab,
                filas,
                columnas,
                bitsExtras,
                puntuacion,
                totalFichasElim,
                combDetectadas,
                combosDetectados
                );

        } while (huboCombinacion);

        unsigned int puntuacionTurno = puntuacion - pAnt;
        unsigned int fichasTurno = totalFichasElim - fAnt;
        unsigned int combinacionesTurno = combDetectadas - cAnt;
        unsigned int combosTurno = combosDetectados - combosAnt;

        mostrarEstadisticasJugada(
            puntuacionTurno,
            puntuacion,
            fichasTurno,
            totalFichasElim,
            combinacionesTurno,
            combosTurno
            );
    }
}

void mostrarResumenFinal(
    unsigned int puntuacionAcumulada,
    unsigned int eliminacionesUsuario,
    unsigned int totalFichasEliminadas,
    unsigned int combinacionesDetectadas,
    unsigned int combosDetectados
    )
{
    cout << "\n";
    cout << "  ========================================================================================\n";
    cout << "                               RESUMEN FINAL DE LA SESION DE JUEGO                        \n";
    cout << "  ========================================================================================\n";

    cout << "   .------------------------------------------------------------------------------------.\n";
    cout << "   |  PARAMETRO / METRICA                               |  VALOR REGISTRADO              |\n";
    cout << "   +---------------------------------------------------+--------------------------------+\n";

    cout << "   |  Puntuacion Total Acumulada                       |  "
         << left << setw(30)
         << puntuacionAcumulada
         << "|\n";

    cout << "   |  Intervenciones Directas del Usuario              |  "
         << left << setw(30)
         << eliminacionesUsuario
         << "|\n";

    cout << "   |  Total de Fichas Destruidas (Cascada + Usuario)   |  "
         << left << setw(30)
         << totalFichasEliminadas
         << "|\n";

    cout << "   |  Rondas de Combinacion Totales                    |  "
         << left << setw(30)
         << combinacionesDetectadas
         << "|\n";

    cout << "   |  Combos Detectados Totales                        |  "
         << left << setw(30)
         << combosDetectados
         << "|\n";

    cout << "   '------------------------------------------------------------------------------------'\n";
    cout << "  ========================================================================================\n";
    cout << "   Fin del juego\n";
}