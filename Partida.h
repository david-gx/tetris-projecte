#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "Joc.h"

using namespace std;

class Partida 
{
public:
    Partida();

    void setPrimeraFigura(const bool& primeraFigura) { m_primeraFigura = primeraFigura; }

    int getPuntuacio() const { return m_puntuacio; }

    void inicialitzaPartida();
    bool actualitza(double deltaTime);

    void inicialitzaModeTest();

private:
    double m_temps;
    int m_nivell;
    int m_puntuacio;
    float m_velocitat;
    
    bool m_primeraFigura;

    bool m_fitxerLlegit;
    bool m_partidaEnCurs;
    
    Joc m_joc;
    // Atributs necessaris només pels exemples d'utilització de la llibreria. 
    // S'hauran d'eliminar per la implementació del projecte
    static const int MIDA = 4;
    ColorFigura m_forma[MIDA][MIDA];
    int m_fila, m_columna;
};

#endif 
