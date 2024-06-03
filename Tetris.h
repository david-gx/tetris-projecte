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

private:
	Partida m_partida;
	std::forward_list<Puntuacio> m_puntuacions;
};

#endif
