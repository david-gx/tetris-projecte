#include "Tauler.h"

Tauler::Tauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            m_tauler[i][j] = COLOR_NEGRE;
            m_taulerFigura[i][j] = COLOR_NEGRE;
        }
    }
}

void Tauler::introdueixFigura(const Figura& figura)
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            m_taulerFigura[i][j] = m_tauler[i][j];
    }

    int nFiles = figura.getNFiles();
    int nColumnes = figura.getNColumnes();
    int xInicial = figura.getFila() - figura.getCentreFila();
    int yInicial = figura.getColumna() - figura.getCentreColumna();
    for (int i = xInicial; i < nFiles + xInicial; i++)
    {
        for (int j = yInicial; j < nColumnes + yInicial; j++)
        {
            if (figura.getFigura(i - xInicial, j - yInicial) != NO_COLOR)
                m_taulerFigura[i][j] = figura.getFigura(i - xInicial, j - yInicial);
        }
    }
}

void Tauler::actualitzaTauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            m_tauler[i][j] = m_taulerFigura[i][j];
    }
}

void Tauler::eliminaFila(const int& fila)
{
    for (int i = 0; i < MAX_COL; i++)
    {
        for (int j = fila; j > 0; j--)
        {
            m_tauler[j][i] = m_tauler[j - 1][i];
            m_taulerFigura[j][i] = m_tauler[j - 1][i];
        }
        m_tauler[0][i] = COLOR_NEGRE;
        m_taulerFigura[0][i] = COLOR_NEGRE;
    }
}

int Tauler::cercaEliminaFiles()
{
    int nFilesEliminades = 0;
    int i = MAX_FILA, j = 0;
    int filaDalt = 0;
    bool elimina = true;
    while (i > filaDalt)
    {
        elimina = true;
        j = 0;
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
            nFilesEliminades++;
        }
        else
            i--;
    }
    return nFilesEliminades;
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
            tauler.setTaulerFigura(valorColor, i, j);
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
            posicio = (int)tauler.getTaulerFigura(i, j);
            output << posicio;
        }
    }
    return output;
}
