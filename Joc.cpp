#include "Joc.h"

bool posicioValida(const Tauler& t, const Figura& f)
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
			if ((fila + i - centreX >= MAX_FILA || columna + j - centreY < 0 || columna + j - centreY >= MAX_COL) && f.getFigura(i, j) != NO_COLOR)
				return false;

			if (f.getFigura(i, j) != NO_COLOR && t.getTauler(fila + i - centreX, columna + j - centreY) != COLOR_NEGRE)
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
    
    m_figuraJoc.inicialitzaFigura();
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
            break;
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
    if (m_figuraJoc.getMoviment())
    {
        Figura f = m_figuraJoc;
        f.setFila(m_figuraJoc.getFila() + 1);
        
        if (posicioValida(m_taulerJoc, f))
        {
            m_figuraJoc = f;
            m_taulerJoc.introdueixFigura(m_figuraJoc);
            f.setFila(f.getFila() + 1);
            if (! posicioValida(m_taulerJoc, f))
            {
                m_taulerJoc.actualitzaTauler();
                nFilesCompletades = m_taulerJoc.cercaEliminaFiles();
                m_figuraJoc.setMoviment(false);
            }
        }
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

void Joc::escriuTauler(const string& nomFitxer)
{
    ofstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
        fitxer << m_taulerJoc;
    fitxer.close();
}
