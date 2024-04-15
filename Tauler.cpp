#include "Tauler.h"

Tauler::Tauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            m_tauler[i][j] = 0;
    }
}

void Tauler::eliminaFila(const int& fila)
{
    for (int i = 0; i < MAX_COL - 1; i++)
    {
        for (int j = fila; j < MAX_FILA; j++)
            m_tauler[j][i] = m_tauler[j + 1][i];
        
        m_tauler[MAX_FILA - 1][i] = 0;
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
            if (m_tauler[i][j] != 0)
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
