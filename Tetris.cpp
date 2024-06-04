#include "Tetris.h"
#include <queue>

void Tetris::juga(Screen& pantalla)
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

void Tetris::mostraPuntuacions()
{
    cout << "\n";
	for (std::forward_list<Puntuacio>::iterator actual = m_puntuacions.begin(); actual != m_puntuacions.end(); actual++)
		cout << (*actual).getNom() << " " << (*actual).getPunts() << "\n";
}

void Tetris::jugaModeTest(Screen& pantalla, const string& nomFitxerTauler, const string& nomFitxerFigures, const string& nomFitxerMoviments)
{
    pantalla.show();

    pantalla.processEvents();
    
    m_partida.inicialitzaModeTest(nomFitxerTauler);
    pantalla.update();

    
    /*
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

    /*
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    double deltaTime = 0;

    int temps = 0;
    bool partidaEnCurs = true;
    while (partidaEnCurs && !moviments.empty())
    {
        do
        {
            LAST = NOW;
            NOW = SDL_GetPerformanceCounter();
            deltaTime = (double)((NOW - LAST) / (double)SDL_GetPerformanceFrequency());
            temps += deltaTime;
        } while (temps < 0.5);
        temps = 0;
    }*/
}
