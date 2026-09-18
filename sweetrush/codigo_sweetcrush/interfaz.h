#ifndef INTERFAZ_H
#define INTERFAZ_H

void mostrarBienvenida();

void mostrarMenu(unsigned short &opcion);

void ejecutarOpcion(
    unsigned short opcion,
    unsigned char*& pTab,
    unsigned short &filas,
    unsigned short &columnas,
    unsigned short &bitsExtras,
    unsigned short &bytesReservados,
    unsigned int &puntuacionAcumulada,
    unsigned int &eliminacionesUsuario,
    unsigned int &totalFichasEliminadas,
    unsigned int &combinacionesDetectadas
    );

void mostrarResumenFinal(
    unsigned int puntuacionAcumulada,
    unsigned int eliminacionesUsuario,
    unsigned int totalFichasEliminadas,
    unsigned int combinacionesDetectadas
    );

#endif // INTERFAZ_H