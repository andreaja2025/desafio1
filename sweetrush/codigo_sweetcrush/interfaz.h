#ifndef INTERFAZ_H
#define INTERFAZ_H

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
    unsigned int combosTurno
    );

void mostrarMenu(unsigned short &opcion);

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
    );

void mostrarResumenFinal(
    unsigned int puntuacionAcumulada,
    unsigned int eliminacionesUsuario,
    unsigned int totalFichasEliminadas,
    unsigned int combinacionesDetectadas
    );

#endif // INTERFAZ_H

