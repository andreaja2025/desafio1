#include <iostream>

#include "validaciones.h"

using namespace std;

unsigned short leerOpcionSegura(
    unsigned short minimo,
    unsigned short maximo,
    const char prompt[]
    )
{
    char entrada[20];

    while (true) {

        cout << prompt << maximo << "): ";

        cin >> entrada;

        bool esNumero = true;

        for (unsigned short i = 0; entrada[i] != '\0'; i++) {

            if (entrada[i] < '0' || entrada[i] > '9') {
                esNumero = false;
                break;
            }
        }

        if (!esNumero) {

            cout << ">> Error: Entrada no valida. "
                 << "Por favor, ingrese un numero entero.\n";

            cin.clear();
            cin.ignore(1000, '\n');

            continue;
        }

        unsigned int valor = 0;

        bool excedeLimite = false;

        for (unsigned short i = 0; entrada[i] != '\0'; i++) {

            unsigned int digito = entrada[i] - '0';

            if (valor > (maximo - digito) / 10) {
                excedeLimite = true;
                break;
            }

            valor = valor * 10 + digito;
        }

        if (excedeLimite) {

            cout << ">> Error: El valor ingresado es demasiado grande.\n";

            cin.clear();
            cin.ignore(1000, '\n');

            continue;
        }

        if (valor < minimo || valor > maximo) {

            cout << ">> Error: El valor debe estar entre "
                 << minimo << " y " << maximo << ".\n";

            cin.clear();
            cin.ignore(1000, '\n');

            continue;
        }

        cin.ignore(1000, '\n');

        return valor;
    }
}