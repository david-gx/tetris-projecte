#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
    Tauler();
    void cercaEliminaFiles();
    
private:
    void eliminaFila(const int& fila);
    int m_tauler[MAX_FILA][MAX_COL];
};

#endif
