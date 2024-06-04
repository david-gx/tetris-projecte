#include "Partida.h"
#include "InfoJoc.h"
#include "GraphicManager.h"
#include "Joc.h"

#include <iostream>
#include <string>

Partida::Partida()
{
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
    m_puntuacio = 0;
    m_nivell = 1;
    m_velocitat = 1;

    m_primeraFigura = true;
    m_fitxerLlegit = false;
    m_partidaEnCurs = true;

    m_joc.inicialitzaTauler();
}

/**
* actualitza
* Funció que actualitza l'estat de la partida
* @param deltaTime: temps que ha passat des de l'última crida a la funció
*/
bool Partida::actualitza(double deltaTime)
{
    // Dibuixa l'estat del tauler
    m_joc.dibuixaTauler();

    // Si la partida continua
    int nFilesCompletades = 0;
    if (m_partidaEnCurs)
    {
        // Genera la figura que es jugarà
        if (!m_joc.getFigura().getMoviment())
            m_partidaEnCurs = m_joc.generaFigura();
        if (m_primeraFigura)
        {
            m_partidaEnCurs = m_joc.generaFigura();
            m_primeraFigura = false;
        }

        // Si la posició on es genera la figura és vàlida
        if (m_partidaEnCurs)
        {
            // Baixa la figura si ha transcorregut temps suficient
            m_temps += deltaTime;
            if (m_temps > m_velocitat)
            {
                nFilesCompletades = m_joc.baixaFigura();
                m_temps = 0;
            }

            // LLegeix els events per teclat
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
            
            // Mostra les puntuacions
            string msg = "Puntuacio: " + to_string(m_puntuacio) + "  Nivell: " + to_string(m_nivell);
            GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);
            
            // Si es col·loca una figura, modifica les puntuacions i comprova si s'ha pujat de nivell
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

    // Retorna si la partida continua
    return m_partidaEnCurs;
}

/**
* inicialitzaModeTest
* Funció que dibuixa el tauler inicial del mode test, amb la primera figura, prenent les dades que llegeix des de fitxer
*/
void Partida::inicialitzaModeTest(const string& nomFitxerTauler)
{
    // Inicialitza els atributs necessaris
    m_puntuacio = 0;
    m_nivell = 1;
    m_primeraFigura = true;
    m_fitxerLlegit = false;
    m_partidaEnCurs = true;

    // Llegeix la figura inicial i el tauler per fitxer
    Figura f;
    Tauler t;
    ifstream fitxer;
    fitxer.open(nomFitxerTauler);
    if (fitxer.is_open())
        fitxer >> f >> t;
    fitxer.close();
    
    f.inicialitzaFigura();
    t.introdueixFigura(f);
    
    m_joc.setFigura(f);
    m_joc.setTauler(t);
    
    // Dibuixa el tauler i la puntuació inicial
    m_joc.dibuixaTauler();
    string msg = "Puntuacio: " + to_string(m_puntuacio) + "  Nivell: " + to_string(m_nivell);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);
}

/**
* actualitzaModeTest
* Funció que actualitza l'estat actual de la partida en funció de dades llegides per fitxer
* @param figures: cua amb les dades de les figures que s'han llegit per fitxer
* @param moviments: cua amb les dades dels moviments que s'han llegit per fitxer
* @return Si la partida continua
*/
bool Partida::actualitzaModeTest(queue<int>& figures, queue<int>& moviments)
{
    // Llegeix i executa el moviment
    int nFilesCompletades = 0;
    TipusMoviment moviment = (TipusMoviment)moviments.front();
    moviments.pop();
    switch (moviment)
    {
    case (MOVIMENT_ESQUERRA):
        m_joc.mouFigura(-1);
        break;
    case (MOVIMENT_DRETA):
        m_joc.mouFigura(1);
        break;
    case (MOVIMENT_GIR_HORARI):
        m_joc.giraFigura(GIR_HORARI);
        break;
    case (MOVIMENT_GIR_ANTI_HORARI):
        m_joc.giraFigura(GIR_ANTI_HORARI);
        break;
    case (MOVIMENT_BAIXA):
        nFilesCompletades = m_joc.baixaFigura();
        break;
    case (MOVIMENT_BAIXA_FINAL):
        nFilesCompletades = m_joc.colocaFigura();
        break;
    default:
        break;
    }

    // Comprova si la figura ha estat col·locada
    if (!m_joc.getFigura().getMoviment())
    {
        // Modifica la puntuació
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

        // Llegeix les dades de la següent figura i la genera
        int tipus, fila, columna, gir;
        tipus = figures.front();
        figures.pop();
        fila = figures.front();
        figures.pop();
        columna = figures.front();
        figures.pop();
        gir = figures.front();
        figures.pop();
        m_partidaEnCurs = m_joc.generaFiguraModeTest(tipus, fila, columna, gir);
    }

    // Dibuixa el tauler
    m_joc.dibuixaTauler();
    string msg = "Puntuacio: " + to_string(m_puntuacio) + "  Nivell: " + to_string(m_nivell);
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER, POS_Y_TAULER - 50, 1.0, msg);

    // Retorna si la partida continua
    return m_partidaEnCurs;
}
