#include "juego.h"

void subrutinaCascada(unsigned char* ptrTablero, unsigned short filas, unsigned short columnas, unsigned short bitsExtras) {
    bool huboCambios;

    do {
        huboCambios = false;

        // Recorrer columnas de abajo hacia arriba con unsigned short
        for (unsigned short c = 0; c < columnas; c++) {
            for (unsigned short f = filas - 1; f > 0; f--) {
                if (obtenerFicha(ptrTablero, f, c, columnas, bitsExtras) == 0) {
                    unsigned char arriba = obtenerFicha(ptrTablero, f - 1, c, columnas, bitsExtras);
                    if (arriba != 0) {
                        escribirFicha(ptrTablero, f, c, columnas, bitsExtras, arriba);
                        eliminarFicha(ptrTablero, f - 1, c, columnas, bitsExtras);
                        huboCambios = true;
                    }
                }
            }
        }

        // Generar nuevas fichas en la primera fila
        for (unsigned short c = 0; c < columnas; c++) {
            if (obtenerFicha(ptrTablero, 0, c, columnas, bitsExtras) == 0) {
                escribirFicha(ptrTablero, 0, c, columnas, bitsExtras, generarFichaRandom());
                huboCambios = true;
            }
        }

    } while (huboCambios);
}