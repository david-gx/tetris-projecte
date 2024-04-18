#include "Figura.h"

Figura::Figura()
{
    m_tipus = NO_FIGURA;
    m_fila = -1;
    m_columna = -1;
    m_gir = 0;
    m_color = NO_COLOR;
    for (int i = 0; i < MAX_ALCADA; i++)
    {
        for (int j = 0; j < MAX_AMPLADA; j++)
            m_figura[i][j] = m_color;
    }
}

void Figura::transposada()
{
    int aux;
    int comptador = 1;
    for (int i = 0; i < m_nFiles - 1; i++)
    {
        for (int j = 0 + comptador; j < m_nColumnes; j++)
        {
            aux = m_figura[i][j];
            m_figura[i][j] = m_figura[j][i];
            m_figura[j][i] = aux;
            comptador++;
        }
    }
}

void Figura::invertirColumnes()
{
    int matAux[m_nFiles][m_nColumnes];
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            matAux[i][j] = m_figura[i][j];
    }
    
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            m_figura[i][j] = matAux[i][m_nColumnes - 1 - j];
    }
}

void Figura::invertirFiles()
{
    int matAux[m_nFiles][m_nColumnes];
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            matAux[i][j] = m_figura[i][j];
    }
    
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            m_figura[i][j] = matAux[m_nFiles - 1 - i][j];
    }
}

void Figura::girHorari()
{
    transposada();
    invertirColumnes();
}

void Figura::girAntiHorari()
{
    transposada();
    invertirFiles();
}

ifstream& operator>>(ifstream& input, Figura& figura)
{
    int tipus, fila, columna, gir;
    input >> tipus >> fila >> columna >> gir;
    figura.setTipus((TipusFigura)tipus);
    figura.setFila(fila);
    figura.setColumna(columna);
    figura.setGir(gir);
    return input;
}
