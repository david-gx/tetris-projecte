#include "Joc.h"

/**
 * posicioValida
 * Funció que indica si la posició en que està col·locada una figura sobre el taulell és vàlida o no
 * @param f: la figura
 * @return Booleà: true si la posició és vàlida, false sinó
 */
bool Joc::posicioValida(const Figura& f) const
{
    int maxFiles = f.getNFiles();
    int maxColumnes = f.getNColumnes();
    int fila = f.getFila();
    int columna = f.getColumna();
    int centreX = f.getCentreFila();
    int centreY = f.getCentreColumna();
    for (int i = 0; i < maxFiles; i++)
    {
        for (int j = 0; j < maxColumnes; j++)
        {
            // Comprova que la figura no surti fora del tauler
            if ((fila + i - centreX >= MAX_FILA || columna + j - centreY < 0 || columna + j - centreY >= MAX_COL) && f.getFigura(i, j) != NO_COLOR)
                return false;

            // Comprova que la figura no es superposi amb caselles ja ocupades
            if (f.getFigura(i, j) != NO_COLOR && m_taulerJoc.getTauler(fila + i - centreX, columna + j - centreY) != COLOR_NEGRE)
                return false;
        }
    }
    return true;
}

/**
 * inicialitza
 * Funció que inicialitza el tauler i la figura amb les dades llegides per fitxer
 * @param nomFitxer: nom del fitxer
 */
void Joc::inicialitza(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
        fitxer >> m_figuraJoc >> m_taulerJoc;
    fitxer.close();

    m_figuraJoc.inicialitzaFigura();
    m_taulerJoc.introdueixFigura(m_figuraJoc);
}

/**
* giraFigura
* Funció que, si és possible, gira la figura en el sentit indicat
* @param direccio: sentit del gir
* @return Booleà indicant si s'ha pogut fer el gir o no
*/
bool Joc::giraFigura(DireccioGir direccio)
{
    if (m_figuraJoc.getMoviment())
    {
        Figura f = m_figuraJoc;
        switch (direccio)
        {
        case GIR_HORARI:
            f.girHorari();
            break;

        case GIR_ANTI_HORARI:
            f.girAntiHorari();
            break;

        default:
            return false;
            break;
        }

        if (posicioValida(f))
        {
            m_figuraJoc = f;
            m_taulerJoc.introdueixFigura(m_figuraJoc);
            return true;
        }
        return false;
    }
    else
        return false;
}

/**
* mouFigura
* Funció que, si és possible, mou la figura en el sentit que s'indica
* @param dirX: sentit en el que es mou la figura (1 dreta, -1 esquerra)
* @return Booleà indicant si s'ha pogut fer el moviment o no
*/
bool Joc::mouFigura(int dirX)
{
    if (m_figuraJoc.getMoviment())
    {
        Figura f = m_figuraJoc;
        switch (dirX)
        {
        case 1:
            f.setColumna(f.getColumna() + 1);
            break;

        case -1:
            f.setColumna(f.getColumna() - 1);
            break;

        default:
            return false;
        }

        if (posicioValida(f))
        {
            m_figuraJoc = f;
            m_taulerJoc.introdueixFigura(m_figuraJoc);
            return true;
        }
        return false;
    }
    else
        return false;
}

/**
* baixaFigura
* Funció que, si és possible, baixa la figura. En el cas que no pugui tornar a baixar,
* la bloqueja, la incorpora al tauler i elimina les files completades, per tal que es
* pugui passar a la següent figura
* @return Nombre de files completades
*/
int Joc::baixaFigura()
{
    int nFilesCompletades = 0;
    if (m_figuraJoc.getMoviment())
    {
        Figura f = m_figuraJoc;
        f.setFila(m_figuraJoc.getFila() + 1);

        // Si la següent posició és vàlida, baixa la figura
        if (posicioValida(f))
        {
            m_figuraJoc = f;
            m_taulerJoc.introdueixFigura(m_figuraJoc);
            f.setFila(f.getFila() + 1);
            // Si, un cop baixada la figura, la següent posició no és vàlida, fixa la figura
            if (!posicioValida(f))
            {
                m_taulerJoc.actualitzaTauler();
                nFilesCompletades = m_taulerJoc.cercaEliminaFiles();
                m_figuraJoc.setMoviment(false);
            }
        }
        // Si la següent posició no és vàlida, fixa la figura
        else
        {
            m_taulerJoc.introdueixFigura(m_figuraJoc);
            m_taulerJoc.actualitzaTauler();
            nFilesCompletades = m_taulerJoc.cercaEliminaFiles();
            m_figuraJoc.setMoviment(false);
        }
    }
    return nFilesCompletades;
}

/**
* escriuTauler
* Funció que escriu el tauler en un fitxer
* @param nomFitxer: nom del fitxer
*/
void Joc::escriuTauler(const string& nomFitxer)
{
    ofstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
        fitxer << m_taulerJoc;
    fitxer.close();
}
