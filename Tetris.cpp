#include "Tauler.h"

/**
* Tauler
* Constructor per defecte de la classe Tauler. Inicialitza totes les posicions del tauler a COLOR_NEGRE
*/
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

/**
* introdueixFigura
* Funció que introdueix la figura passada com a paràmetre al tauler
* @param figura: figura a introduir
*/
void Tauler::introdueixFigura(const Figura& figura)
{
    // Copia en la matriu del tauler que es visualitzarà per pantalla el tauler amb les figures ja col·locades
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            m_taulerFigura[i][j] = m_tauler[i][j];
    }

    // Afegeix en la matriu del tauler que es visualitzarà per pantalla la figura
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

/**
* actualitzaTauler
* Funció que actualitza el tauler, de tal manera que, si hi havia una figura en moviment, quedarà fixa
*/
void Tauler::actualitzaTauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
            m_tauler[i][j] = m_taulerFigura[i][j];
    }
}

/**
* eliminaFila
* Funció que elimina una fila
* @param fila: fila a eliminiar
*/
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

/**
* cercaEliminaFiles
* Funció que elimina totes les files completades del tauler
* @return Nombre de files eliminades
*/
int Tauler::cercaEliminaFiles()
{
    int nFilesEliminades = 0;
    int i = MAX_FILA, j = 0;
    int filaDalt = 0;
    bool elimina = true;
    while (i > filaDalt)
    {
        // Cerca si una fila està ocupada, començant per la d'abaix
        elimina = true;
        j = 0;
        while (j < MAX_COL && elimina)
        {
            if (m_tauler[i][j] != COLOR_NEGRE)
                j++;
            else
                elimina = false;
        }

        // Si la fila està ocupada, l'elimina
        if (elimina)
        {
            eliminaFila(i);
            filaDalt++;
            nFilesEliminades++;
        }
        // Si la fila no està ocupada, es passa a la següent fila
        else
            i--;
    }
    return nFilesEliminades;
}

/**
* operator>>
* Sobrecàrrega de l'operador >>
*/
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
        }
    }
    return input;
}

/**
* operator<<
* Sobrecàrrega de l'operador <<
*/
ofstream& operator<<(ofstream& output, Tauler& tauler)
{
    int posicio;
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            posicio = (int)tauler.getTaulerFigura(i, j);
            output << posicio << " ";
        }
        output << "\n";
    }
    return output;
}

