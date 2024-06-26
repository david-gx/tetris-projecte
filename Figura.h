#ifndef FIGURA_H
#define FIGURA_H

#include <fstream>
using namespace std;

#include "InfoJoc.h"

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

/**
* CLASS Figura
* Classe que permet guardar les dades d'una figura
* Les dades que conté són: tipus, fila, columna, gir, color, nombre de files, nombre de columnes,
* matriu amb la figura i booleà que indica si es pot seguir movent
* Conté mètodes per accedir i modificar les dades, inicialitzar la figura i rotar-la
*/
class Figura
{
public:
    Figura();

    void setTipus(const TipusFigura& tipus) { m_tipus = tipus; }
    void setFila(const int& fila) { m_fila = fila; }
    void setColumna(const int& columna) { m_columna = columna; }
    void setGir(const int& gir) { m_gir = gir; }
    void setMoviment(const bool& moviment) { m_moviment = moviment; }

    TipusFigura getTipus() const { return m_tipus; }
    int getFila() const { return m_fila; }
    int getColumna() const { return m_columna; }
    int getGir() const { return m_gir; }
    ColorFigura getColor() { return m_color; }
    int getNFiles() const { return m_nFiles; }
    int getNColumnes() const { return m_nColumnes; }
    int getCentreFila() const { return m_centreFila; }
    int getCentreColumna() const { return m_centreColumna; }
    ColorFigura getFigura(const int& fila, const int& columna) const { return m_figura[fila][columna]; }
    bool getMoviment() const { return m_moviment; }

    Figura& operator=(const Figura& f);

    void inicialitzaFigura();
    void girHorari();
    void girAntiHorari();

private:
    void transposada();
    void invertirColumnes();
    void invertirFiles();

    const int m_centreFila = 1;
    const int m_centreColumna = 1;

    TipusFigura m_tipus;
    int m_fila;
    int m_columna;
    int m_gir;
    ColorFigura m_color;
    int m_nFiles;
    int m_nColumnes;
    ColorFigura m_figura[MAX_ALCADA][MAX_AMPLADA];
    bool m_moviment;
};

ifstream& operator>>(ifstream& input, Figura& figura);

#endif
