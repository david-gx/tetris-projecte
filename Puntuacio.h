#ifndef PUNTUACIO_H
#define PUNTUACIO_H

#include <iostream>
using namespace std;
#include <string>

class Puntuacio
{
public:
	Puntuacio() { m_nom = "", m_punts = 0; }
	Puntuacio(const string& nom, const int& punts) { m_nom = nom; m_punts = punts; }

	void setNom(const string& nom) { m_nom = nom;  }
	void setPunts(const int& punts) { m_punts = punts; }
	string getNom() const { return m_nom; }
	int getPunts() const { return m_punts; }

private:
	string m_nom;
	int m_punts;
};

#endif
