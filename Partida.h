#ifndef PARTIDA_H
#define PARTIDA_H

#include <stdio.h>
#include <string>
#include "Joc.h"
#include <queue>
using namespace std;

/**
* CLASS Partida
* Classe que permet guardar les dades d'una partida de tetris
* Les dades que conté són: temps que passa entre dues crides; nivell i puntuació de la partida; velocitat de caiguda
* de les figures; tres booleans indicant si la figura que s'utilitza és la primera, si el fitxer s'ha llegit correctament
* i si la partida segueix en curs; un objecte de classe Joc
* Conté mètodes per inicialitzar i modificar l'estat de la partida en mode normal i mode test
*/
class Partida 
{
public:
    Partida();

    int getPuntuacio() const { return m_puntuacio; }

    void inicialitzaPartida();
    bool actualitza(double deltaTime);

    void inicialitzaModeTest(const string& nomFitxerTauler);
    bool actualitzaModeTest(queue<int>& figures, queue<int>& moviments);

private:
    double m_temps;
    int m_nivell;
    int m_puntuacio;
    float m_velocitat;
    
    bool m_primeraFigura;
    bool m_fitxerLlegit;
    bool m_partidaEnCurs;
    
    Joc m_joc;
};

#endif 
