#include "Tauler.h"

Tauler::Tauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            m_tauler[i][j] = COLOR_NEGRE;
    }
}

void Tauler::introdueixFigura(const Figura& figura)
{
    int nFiles = figura.getNFiles(), nColumnes = figura.getNColumnes();
    int xInicial = figura.getFila() - figura.getCentreFila(), yInicial = figura.getColumna() - figura.getCentreColumna();
    for (int i = xInicial; i < nFiles; i++)
    {
        for (int j = yInicial; j < nColumnes; j++)
        {
            if (figura.getFigura(i - xInicial, j - yInicial) != NO_COLOR)
                m_tauler[i][j] = figura.getFigura(i - xInicial, j - yInicial);
        }
    }
    
}

void Tauler::eliminaFila(const int& fila)
{
    for (int i = 0; i < MAX_COL - 1; i++)
    {
        for (int j = fila; j < MAX_FILA; j++)
            m_tauler[j][i] = m_tauler[j + 1][i];
        
        m_tauler[MAX_FILA - 1][i] = COLOR_NEGRE;
    }
}

void Tauler::cercaEliminaFiles()
{
    int i = MAX_FILA, j = 0;
    int filaDalt = 0;
    bool elimina = true;
    while (i > filaDalt)
    {
        while (j < MAX_COL && elimina)
        {
            if (m_tauler[i][j] != COLOR_NEGRE)
                 j++;
            else
                elimina = false;
        }
        
        if (elimina)
        {
            eliminaFila(i);
            filaDalt++;
        }
        else
            i--;
    }
}

ifstream& operator>>(ifstream& input, Tauler& tauler)
{
    int valor;
    ColorFigura valorColor;
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            input >> valor;
            valorColor = (ColorFigura)valor;
            tauler.setTauler(valorColor, i, j);
            cout << valorColor;
        }
    }
    return input;
}

ofstream& operator<<(ofstream& output, Tauler& tauler)
{
    int posicio;
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            posicio = (int)tauler.getTauler(i, j);
            output << posicio;
        }
    }
    return output;
}
