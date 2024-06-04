#ifndef TETRIS_H
#define TETRIS_H

#include <forward_list>
#include "Puntuacio.h"
#include "Partida.h"

class Tetris
{
public:
	void juga(Screen& pantalla);
	void mostraPuntuacions();
	void afegeixPuntuacio(const string& nom, const int& punts);

	void jugaModeTest(Screen& pantalla, const string& nomFitxerTauler, const string& nomFitxerFigures, const string& nomFitxerMoviments);

private:
	Partida m_partida;
	std::forward_list<Puntuacio> m_puntuacions;
};

#endif
