#include "Tetris.h"
#include <queue>

/**
* juga
* Funció que executa una partida de tetris en mode normal
* @param pantalla: pantalla on es visualitza la partida
* @param nomFitxerPuntuacions: nom del fitxer que conté les puntuacions
*/
void Tetris::juga(Screen& pantalla, const string& nomFitxerPuntuacions)
{   
    //Mostrem la finestra grafica
    m_partida.inicialitzaPartida();
    pantalla.show();
    
    bool partidaEnCurs = true;

    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    do
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());

        // Captura tots els events de ratolí i teclat de l'ultim cicle
        pantalla.processEvents();

        partidaEnCurs = m_partida.actualitza(deltaTime);
        if (!partidaEnCurs)
        {
            string msg = "GAME OVER";
            GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 80, POS_Y_TAULER + 250, 1.0, msg);
        }
        // Actualitza la pantalla
        pantalla.update();

    } while (!Keyboard_GetKeyTrg(KEYBOARD_ESCAPE) && partidaEnCurs);
    // Sortim del bucle si pressionem ESC o si finalitza la partida

    cout << "Introdueix el teu nom: ";
    string nom;
    cin >> nom;
    afegeixPuntuacio(nom, m_partida.getPuntuacio());
}

/**
* afegeixPuntuacio
* Funció que afegeix ordenadament una puntuació a la llista de puntuacions
* @param nom: nom del jugador
* @param punts: puntuació del jugador
*/
void Tetris::afegeixPuntuacio(const string& nom, const int& punts)
{
	std::forward_list<Puntuacio>::iterator anterior = m_puntuacions.before_begin();
	std::forward_list<Puntuacio>::iterator actual = m_puntuacions.begin();
	bool trobat = false;

	while (!trobat && actual != m_puntuacions.end())
	{
		if ((*actual).getPunts() < punts)
			trobat = true;
		else
		{
			anterior = actual;
			actual++;
		}
	}

	Puntuacio puntuacio(nom, punts);
	m_puntuacions.insert_after(anterior, puntuacio);
}

/**
* mostraPuntuacions
* Funció que mostra per consola les millors puntuacions registrades
*/
void Tetris::mostraPuntuacions()
{
    cout << "\n";
    for (std::forward_list<Puntuacio>::iterator actual = m_puntuacions.begin(); actual != m_puntuacions.end(); actual++)
        cout << (*actual).getNom() << " " << (*actual).getPunts() << "\n";
}

/**
* guardaPuntuacions
* Funció que guarda les puntuacions en un fitxer
* @param nomFitxerPuntuacions: nom del fitxer on es guarden les puntuacions
*/
void Tetris::guardaPuntuacions(const string& nomFitxerPuntuacions)
{
    ofstream fitxerOut;
    fitxerOut.open(nomFitxerPuntuacions);
    Puntuacio pAux;
    if (fitxerOut.is_open())
    {
        while (!m_puntuacions.empty())
        {
            pAux = m_puntuacions.front();
            m_puntuacions.pop_front();
            fitxerOut << pAux.getNom() << " " << pAux.getPunts() << "\n";
        }
    }
}

/**
* Funció que executa una partida de tetris en mode test
* @param pantalla: pantalla on es visualitza la partida
* @param nomFitxerTauler: nom del fitxer des del qual es llegeix la primera figura i l'estat inicial del tauler
* @param nomFitxerFigures: nom del fitxer des del qual es llegeixen les figures que aniran apareixent
* @param nomFitxermoviments: nom del fitxer des del qual es llegeixen els moviments que s'executaran
*/
void Tetris::jugaModeTest(Screen& pantalla, const string& nomFitxerTauler, const string& nomFitxerFigures, const string& nomFitxerMoviments)
{
    // Inicialitza i dibuixa l'estat inicial del tauler
    pantalla.show();
    pantalla.processEvents();    
    m_partida.inicialitzaModeTest(nomFitxerTauler);
    pantalla.update();

    // Guarda les dades dels fitxers que contenen les figures i els moviments en dues cues
    std::queue<int> figures;
    std::queue<int> moviments;

    ifstream fitxer;
    int valor;
    fitxer.open(nomFitxerFigures);
    if (fitxer.is_open())
    {
        while (!fitxer.eof())
        {
            fitxer >> valor;
            if (!fitxer.eof())
                figures.push(valor);
        }
    }
    fitxer.close();

    fitxer.open(nomFitxerMoviments);
    if (fitxer.is_open())
    {
        while (!fitxer.eof())
        {
            fitxer >> valor;
            if (!fitxer.eof())
                moviments.push(valor);
        }
    }
    fitxer.close();

    // Fa tots els moviments en el tauler, deixant intervals de temps constants entre cada moviment
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;
    float temps = 0;

    bool partidaEnCurs = true;
    while (partidaEnCurs && !moviments.empty())
    {
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
        temps += deltaTime;
        if (temps > 0.5)
        {
            partidaEnCurs = m_partida.actualitzaModeTest(figures, moviments);
            pantalla.update();
            temps = 0;
        }
    }

    string msg = "GAME OVER";
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, POS_X_TAULER + 80, POS_Y_TAULER + 250, 1.0, msg);
    pantalla.update();
}
