#ifndef TAULER_H
#define TAULER_H
#include "Figura.h"

const int MAX_FILA = 8;
const int MAX_COL = 8;

/**
* CLASS Tauler
* Classe que permet guardar les dades d'un tauler
* Les dades que conté són: matriu amb les figures ja col·locades i matriu amb les figures ja col·locades i la figura en moviment
* Conté mètodes per accedir i modificar les dades, introduir la figura en moviment, fixar la figura en moviment i eliminar les
* files completades
*/
class Tauler
{
public:
    Tauler();

    void setTauler(const ColorFigura& valor, const int& fila, const int& columna) { m_tauler[fila][columna] = valor; }
    void setTaulerFigura(const ColorFigura& valor, const int& fila, const int& columna) { m_taulerFigura[fila][columna] = valor; }

    ColorFigura getTauler(const int& fila, const int& columna) const { return m_tauler[fila][columna]; }
    ColorFigura getTaulerFigura(const int& fila, const int& columna) const { return m_taulerFigura[fila][columna]; }

    void introdueixFigura(const Figura& figura);
    void actualitzaTauler();
    int cercaEliminaFiles();

private:
    void eliminaFila(const int& fila);

    ColorFigura m_tauler[MAX_FILA][MAX_COL];
    ColorFigura m_taulerFigura[MAX_FILA][MAX_COL];
};

ifstream& operator>>(ifstream& input, Tauler& tauler);
ofstream& operator<<(ofstream& output, Tauler& tauler);

#endif
