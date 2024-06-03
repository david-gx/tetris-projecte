#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include "Joc.h"

#include <iostream>

Partida::Partida()
{
    m_temps = 0;
    for (int i = 0; i < MIDA; i++)
        for (int j = 0; j < MIDA; j++)
            m_forma[i][j] = NO_COLOR;
    m_forma[0][0] = COLOR_BLAUFOSC;
    m_forma[1][0] = COLOR_BLAUFOSC;
    m_forma[1][1] = COLOR_BLAUFOSC;
    m_forma[1][2] = COLOR_BLAUFOSC;
    m_fila = 1;
    m_columna = 5;

    m_puntuacio = 0;
    m_nivell = 1;
    m_velocitat = 1;

    m_primeraFigura = true;
    m_fitxerLlegit = false;
    m_partidaEnCurs = true;

    m_joc.inicialitzaTauler();
}

/**
* inicialitzaPartida
* Funció que dibuixa el tauler inicial, tot buit
*/
void Partida::inicialitzaPartida()
{
    m_temps = 0;
    for (int i = 0; i < MIDA; i++)
        for (int j = 0; j < MIDA; j++)
            m_forma[i][j] = NO_COLOR;
    m_forma[0][0] = COLOR_BLAUFOSC;
    m_forma[1][0] = COLOR_BLAUFOSC;
    m_forma[1][1] = COLOR_BLAUFOSC;
    m_forma[1][2] = COLOR_BLAUFOSC;
    m_fila = 1;
    m_columna = 5;

    m_puntuacio = 0;
    m_nivell = 1;
    m_velocitat = 1;

    m_primeraFigura = true;
    m_fitxerLlegit = false;
    m_partidaEnCurs = true;

    m_joc.inicialitzaTauler();

    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);
}

/**
* actualitza
* Funció que actualitza l'estat de la partida
* @param deltaTime: temps que ha passat des de l'última crida a la funció
*/
bool Partida::actualitza(double deltaTime)
{
    int nFilesCompletades = 0;
    if (m_partidaEnCurs)
    {
        if (!m_joc.getFigura().getMoviment())
            m_partidaEnCurs = m_joc.generaFigura();


        if (m_primeraFigura)
        {
            m_partidaEnCurs = m_joc.generaFigura();
            m_primeraFigura = false;
        }

        if (m_partidaEnCurs)
        {
            m_temps += deltaTime;
            if (m_temps > m_velocitat)
            {
                cout << m_nivell << ", " << m_puntuacio << "\n";
                nFilesCompletades = m_joc.baixaFigura();
                m_temps = 0;
            }

            if (Keyboard_GetKeyTrg(KEYBOARD_RIGHT))
                m_joc.mouFigura(1);
            if (Keyboard_GetKeyTrg(KEYBOARD_LEFT))
                m_joc.mouFigura(-1);
            if (Keyboard_GetKeyTrg(KEYBOARD_UP))
                m_joc.giraFigura(GIR_HORARI);
            if (Keyboard_GetKeyTrg(KEYBOARD_DOWN))
                m_joc.giraFigura(GIR_ANTI_HORARI);
            if (Keyboard_GetKeyTrg(KEYBOARD_SPACE))
                nFilesCompletades = m_joc.colocaFigura();
            m_joc.dibuixaTauler();

            if (!m_joc.getFigura().getMoviment())
            {
                if (nFilesCompletades > 0)
                {
                    m_puntuacio += 100;
                    switch (nFilesCompletades)
                    {
                    case 2:
                        m_puntuacio += 50;
                        break;
                    case 3:
                        m_puntuacio += 75;
                        break;
                    case 4:
                        m_puntuacio += 100;
                        break;
                    }
                }
                else
                    m_puntuacio += 10;

                if (m_puntuacio / 1000 >= m_nivell)
                {
                    m_nivell++;
                    m_velocitat *= 0.7;
                }
            }
        }
    }
    return m_partidaEnCurs;
}

/**
* inicialitzaModeTest
* Funció que dibuixa el tauler inicial del mode test, amb la primera figura, prenent les dades que llegeix des de fitxer
*/
void Partida::inicialitzaModeTest()
{
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0, false);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER, false);

    Figura f;
    Tauler t;
    ifstream fitxer;
    fitxer.open("C:/Users/Usuario/Documents/mp_1r/tetris_projecte/implementacio_llibreria_grafica/1. Resources/data/Games/partida.txt");
    if (fitxer.is_open())
        fitxer >> f >> t;
    fitxer.close();

    f.inicialitzaFigura();
    t.introdueixFigura(f);

    m_joc.setFigura(f);
    m_joc.setTauler(t);

    m_joc.dibuixaTauler();
}
