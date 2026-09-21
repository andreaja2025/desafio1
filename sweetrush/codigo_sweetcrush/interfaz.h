#ifndef INTERFAZ_H
#define INTERFAZ_H

    unsigned short leerValor(
        unsigned short minimo,
        unsigned short maximo,
        const char mensaje[]
        );

void mostrarBienvenida();

void mostrarMonitorMemoria(
    const unsigned char* pTab,
    unsigned short filas,
    unsigned short columnas,
    unsigned short bytesReservados
    );

void mostrarEstadisticasJugada(
    unsigned int puntuacionTurno,
    unsigned int puntuacionTotal,
    unsigned int fichasTurno,
    unsigned int fichasTotal,
    unsigned int rondasTurno,
    unsigned int combosTurno
    );

void mostrarMenu();

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
    );

void mostrarResumenFinal(
    unsigned int puntuacionAcumulada,
    unsigned int eliminacionesUsuario,
    unsigned int totalFichasEliminadas,
    unsigned int combinacionesDetectadas,
    unsigned int combosDetectados
    );

#endif // INTERFAZ_H