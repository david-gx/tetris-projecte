#include "Joc.h"
#include <cstdlib>

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

/**
* inicialitzaTauler
* Funció que inicialitza totes les caselles del tauler a color negre
*/
void Joc::inicialitzaTauler()
{
    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            m_taulerJoc.setTauler(COLOR_NEGRE, i, j);
            m_taulerJoc.setTaulerFigura(COLOR_NEGRE, i, j);
        }
    }
}

/**
* colocaFigura
* Funció que baixa la figura fins que aquesta queda col·locada
* @return: Nombre de files completades
*/
int Joc::colocaFigura()
{
    int nFilesCompletades = 0;
    while (m_figuraJoc.getMoviment())
        nFilesCompletades = baixaFigura();
    return nFilesCompletades;
}

/**
* generaFigura
* Funció que genera una figura aleatòria
* @return Si la figura es superposa amb alguna de les ja col·locades al tauler
*/
bool Joc::generaFigura()
{
    m_figuraJoc.setTipus((TipusFigura)(0 + (rand() % 8)));
    m_figuraJoc.setFila((TipusFigura)(1));
    m_figuraJoc.setColumna((TipusFigura)(2 + (rand() % 8)));
    m_figuraJoc.setGir((TipusFigura)(0 + (rand() % 4)));
    m_figuraJoc.inicialitzaFigura();
    m_taulerJoc.introdueixFigura(m_figuraJoc);
    if (posicioValida(m_figuraJoc))
        return true;
    return false;
}

/**
* dibuixaTauler
* Funció que dibuixa el tauler a través de la llibreria gràfica
*/
void Joc::dibuixaTauler() const
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    for (int i = 0; i < MAX_FILA; i++)
    {
        for (int j = 0; j < MAX_COL; j++)
        {
            ColorFigura color = m_taulerJoc.getTaulerFigura(i, j);
            if (color != COLOR_NEGRE)
                GraphicManager::getInstance()->drawSprite((IMAGE_NAME)(color + 1), POS_X_TAULER + ((j + 1) * MIDA_QUADRAT),
                    POS_Y_TAULER + (((i + 1) - 1) * MIDA_QUADRAT), false);
        }
    }
}

/**
* generaFiguraModeTest
* Funció que genera una figura predeterminada
* @param tipus: tipus de la figura
* @param fila: fila on està ubicada la figura en el tauler
* @param columna: columna on està ubicada la figura en el tauler
* @param gir: gir de la figura
*/
bool Joc::generaFiguraModeTest(const int& tipus, const int& fila, const int& columna, const int& gir)
{
    m_figuraJoc.setTipus((TipusFigura)tipus);
    m_figuraJoc.setFila((TipusFigura)fila);
    m_figuraJoc.setColumna((TipusFigura)columna);
    m_figuraJoc.setGir((TipusFigura)gir);
    m_figuraJoc.inicialitzaFigura();
    m_taulerJoc.introdueixFigura(m_figuraJoc);
    if (posicioValida(m_figuraJoc))
        return true;
    return false;
}
