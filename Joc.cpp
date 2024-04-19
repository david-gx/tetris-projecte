#include "Joc.h"

void Joc::inicialitza(const string& nomFitxer)
{
    ifstream fitxerIn;
    string nomFitxerIn;
    cin >> nomFitxerIn;
    fitxerIn.open(nomFitxerIn);
    fitxerIn >> m_figuraJoc >> m_taulerJoc;
    fitxerIn.close();
    
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
    ofstream fitxerOut;
    string nomFitxerOut;
    cin >> nomFitxerOut;
    fitxerOut.open(nomFitxerOut);
    fitxerOut << m_taulerJoc;
    fitxerOut.close();
}
