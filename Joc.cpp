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
{/*
    ifstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
        fitxer >> m_figuraJoc >> m_taulerJoc;
    fitxer.close();
    
    m_taulerJoc.introdueixFigura(m_figuraJoc);*/
}

bool Joc::giraFigura(DireccioGir direccio)
{
    return false;
}

bool Joc::mouFigura(int dirX)
{
    return false;
}

int Joc::baixaFigura()
{
    return 0;
}

void Joc::escriuTauler(const string& nomFitxer)
{
    ofstream fitxer;
    fitxer.open(nomFitxer);
    if (fitxer.is_open())
        fitxer << m_taulerJoc;
    fitxer.close();
}
