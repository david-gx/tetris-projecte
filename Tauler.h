#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

class Tauler
{
public:
    Tauler();
    
    void setTauler(const ColorFigura& valor, const int& fila, const int& columna) { m_tauler[fila][columna] = valor; }
    ColorFigura getTauler(const int& fila, const int& columna) { return m_tauler[fila][columna]; }
    
    void cercaEliminaFiles();
    
private:
    void eliminaFila(const int& fila);
    ColorFigura m_tauler[MAX_FILA][MAX_COL];
};

ifstream& operator>>(ifstream& input, Tauler& tauler);
ofstream& operator<<(ofstream& output, Tauler& tauler);

#endif
