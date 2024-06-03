#ifndef JOC_H
#define JOC_H
#include "Tauler.h"
#include "Figura.h"
#include <string>

#include "GraphicManager.h"
#include "InfoJoc.h"

/**
* CLASS Joc
* Classe que permet guardar les dades d'una partida de tetris
* Les dades que conté són: tauler del joc i figura en joc
* Conté mètodes per inicialitzar el tauler llegint el seu estat inicial des de fitxer; girar, moure i
* baixar la figura en joc; i guardar l'estat del tauler en un fitxer
*/
class Joc
{
public:
	Figura getFigura() const { return m_figuraJoc;  }

	void setFigura(Figura f) { m_figuraJoc = f; }
	void setTauler(Tauler t) { m_taulerJoc = t; }

	void inicialitza(const string& nomFitxer);
	bool giraFigura(DireccioGir direccio);
	bool mouFigura(int dirX);
	int baixaFigura();
	void escriuTauler(const string& nomFitxer);
	
	void inicialitzaTauler();
	int colocaFigura();
	bool generaFigura();
	void dibuixaTauler() const;

private:
	bool posicioValida(const Figura& f) const;

	Tauler m_taulerJoc;
	Figura m_figuraJoc;
};

#endif
