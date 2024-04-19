#include "Joc.h"

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
