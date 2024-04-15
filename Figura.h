#ifndef FIGURA_H
#define FIGURA_H

typedef enum
{
    COLOR_NEGRE = 0,
    COLOR_GROC,
    COLOR_BLAUCEL,
    COLOR_MAGENTA,
    COLOR_TARONJA,
    COLOR_BLAUFOSC,
    COLOR_VERMELL,
    COLOR_VERD,
    NO_COLOR
} ColorFigura;


typedef enum
{
    NO_FIGURA = 0,
    FIGURA_O,
    FIGURA_I,
    FIGURA_T,
    FIGURA_L,
    FIGURA_J,
    FIGURA_Z,
    FIGURA_S,
} TipusFigura;

const int MAX_ALCADA = 4;
const int MAX_AMPLADA = 4;

typedef enum
{
    GIR_HORARI = 0,
    GIR_ANTI_HORARI
} DireccioGir;

class Figura
{
public:
    Figura();
    
    void setTipus(const TipusFigura& tipus) { m_tipus = tipus; }
    void setFila(const int& fila) { m_fila = fila; }
    void setColumna(const int& columna) { m_columna = columna; }
    void setGir(const int& gir) { m_gir = gir; }
    
private:
    TipusFigura m_tipus;
    int m_fila;
    int m_columna;
    int m_gir;
    ColorFigura m_color;
    int m_figura[MAX_ALCADA][MAX_AMPLADA];
};


#endif
