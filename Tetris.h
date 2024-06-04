#ifndef TETRIS_H
#define TETRIS_H

#include <forward_list>
#include "Puntuacio.h"
#include "Partida.h"

/**
* CLASS Tetris
* Classe que permet guardar les dades del joc Tetris
* Les dades que conté són: un objecte de classe Partida i una llista amb les millors puntuacions
* Conté mètodes per jugar en mode normal i mode test i per gestionar les puntuacions dels jugadors
*/
class Tetris
{
public:
	void juga(Screen& pantalla, const string& nomFitxerPuntuacions);
	void mostraPuntuacions();
	void afegeixPuntuacio(const string& nom, const int& punts);
	void guardaPuntuacions(const string& nomFitxerPuntuacions);

	void jugaModeTest(Screen& pantalla, const string& nomFitxerTauler, const string& nomFitxerFigures, const string& nomFitxerMoviments);

private:
	Partida m_partida;
	std::forward_list<Puntuacio> m_puntuacions;
};

#endif
