#include "Joc.h"

bool Joc::posicioValida(const Tauler& t, const Figura& f) const
{
    int maxFiles = f.getNFiles();
    int maxColumnes = f.getNColumnes();
    int fila = f.getFila();
    int columna = f.getColumna();
    int centreX = f.getCentreFila();
    int centreY = f.getCentreColumna();
    
    if ((fila - centreX < 0) || (fila + maxFiles - centreX > MAX_FILA) || (columna - centreY < 0) || (columna + maxColumnes - centreY > MAX_COL))
        return false;
    
    for (int i = 0; i < maxFiles; i++)
    {
        for (int j = 0; j < maxColumnes; j++)
        {
            if (f.getFigura(i, j) != NO_COLOR && t.getTauler(fila + i - centreX, columna + i - centreY) != COLOR_NEGRE)
                return false;
        }
    }
    return true;
}

void Joc::inicialitza(const string& nomFitxer)
{
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
        fitxer >> m_figuraJoc >> m_taulerJoc;
    fitxer.close();
    
    m_taulerJoc.introdueixFigura(m_figuraJoc);
}


bool Joc::giraFigura(DireccioGir direccio)
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
    }
    
    if (posicioValida(m_taulerJoc, f))
    {
        m_figuraJoc = f;
        m_taulerJoc.introdueixFigura(m_figuraJoc);
        return true;
    }
    return false;
}

bool Joc::mouFigura(int dirX)
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
    
    if (posicioValida(m_taulerJoc, f))
    {
        m_figuraJoc = f;
        m_taulerJoc.introdueixFigura(m_figuraJoc);
        return true;
    }
    return false;
}

int Joc::baixaFigura()
{
    int nFilesCompletades = 0;
    m_figuraJoc.setFila(m_figuraJoc.getFila() + 1);
    Figura f = m_figuraJoc;
    f.setFila(f.getFila() + 1);
    
    if (! posicioValida(m_taulerJoc, f))
    {
        m_taulerJoc.introdueixFigura(m_figuraJoc);
        m_taulerJoc.actualitzaTauler();
        nFilesCompletades = m_taulerJoc.cercaEliminaFiles();
    }
    return nFilesCompletades;
}

void Joc::escriuTauler(const string& nomFitxer)
{
    ofstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
        fitxer << m_taulerJoc;
    fitxer.close();
}
