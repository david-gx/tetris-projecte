#include "Tetris.h"

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

        // Actualitza la pantalla
        if (partidaEnCurs)
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
	for (std::forward_list<Puntuacio>::iterator actual = m_puntuacions.begin(); actual != m_puntuacions.end(); actual++)
		cout << (*actual).getNom() << " " << (*actual).getPunts() << "\n";
}
