#include "Figura.h"

Figura::Figura()
{
    m_tipus = NO_FIGURA;
    m_fila = -1;
    m_columna = -1;
    m_gir = 0;
    m_color = NO_COLOR;
    m_nFiles = 0;
    m_nColumnes = 0;
    m_centreFila = 0;
    m_centreColumna = 0;
    for (int i = 0; i < MAX_ALCADA; i++)
    {
        for (int j = 0; j < MAX_AMPLADA; j++)
            m_figura[i][j] = m_color;
    }
}

Figura& Figura::operator=(const Figura& f)
{
	if (&f != this)
	{
		m_tipus = f.getTipus();
	        m_fila = f.getFila();
        	m_columna = f.getColumna();
	        m_gir = f.getGir();
        	m_color = getColor();
	        m_nFiles = f.getNFiles();
        	m_nColumnes = f.getNColumnes();
		m_centreFila = f.getCentreFila();
        	m_centreColumna = f.getCentreColumna();
        
		for (int i = 0; i < m_nFiles; i++)
        	{
            	for (int j = 0; j < m_nColumnes; j++)
                	m_figura[i][j] = f.getFigura(i, j);
        	}
	}
	
	return *this;
}

void Figura::inicialitzaFigura()
{
    switch (m_tipus)
    {
        case FIGURA_O:
            m_nFiles = 2;
            m_nColumnes = 2;
            m_color = COLOR_GROC;
            for (int i = 0; i < m_nFiles; i++)
            {
                for (int j = 0; j < m_nColumnes; j++)
                    m_figura[i][j] = m_color;
            }
            m_centreFila = 0;
            m_centreColumna = 0;
            break;
        
        case FIGURA_I:
            m_nFiles = 4;
            m_nColumnes = 4;
            m_color = COLOR_BLAUCEL;
            for (int i = 0; i < m_nFiles; i++)
            {
                for (int j = 0; j < m_nColumnes; j++)
                {
                    if (i == 1)
                        m_figura[i][j] = m_color;
                    else
                        m_figura[i][j] = NO_COLOR;
                }
            }
            m_centreFila = 1;
            m_centreColumna = 2;
            break;
        
        case FIGURA_T:
            m_nFiles = 3;
            m_nColumnes = 3;
            m_color = COLOR_MAGENTA;
            for (int i = 0; i < m_nFiles; i++)
            {
                for (int j = 0; j < m_nColumnes; j++)
                {
                    if (i == 1 || i == 0 && j == 1)
                        m_figura[i][j] = m_color;
                    else
                        m_figura[i][j] = NO_COLOR;
                }
            }
            m_centreFila = 1;
            m_centreColumna = 1;
            break;
        
        case FIGURA_L:
            m_nFiles = 3;
            m_nColumnes = 3;
            m_color = COLOR_TARONJA;
            for (int i = 0; i < m_nFiles; i++)
            {
                for (int j = 0; j < m_nColumnes; j++)
                {
                    if (i == 1 || i == 0 && j == 2)
                        m_figura[i][j] = m_color;
                    else
                        m_figura[i][j] = NO_COLOR;
                }
            }
            m_centreFila = 1;
            m_centreColumna = 1;
            break;
        
        case FIGURA_J:
            m_nFiles = 3;
            m_nColumnes = 3;
            m_color = COLOR_BLAUFOSC;
            for (int i = 0; i < m_nFiles; i++)
            {
                for (int j = 0; j < m_nColumnes; j++)
                {
                    if (i == 1 || i == 0 && j == 0)
                        m_figura[i][j] = m_color;
                    else
                        m_figura[i][j] = NO_COLOR;
                }
            }
            m_centreFila = 1;
            m_centreColumna = 1;
            break;
        
        case FIGURA_Z:
            m_nFiles = 3;
            m_nColumnes = 3;
            m_color = COLOR_VERMELL;
            for (int i = 0; i < m_nFiles; i++)
            {
                for (int j = 0; j < m_nColumnes; j++)
                {
                    if (i == 0 && (j == 0 || j == 1) || i == 1 && (j == 1 || j == 2))
                        m_figura[i][j] == m_color;
                    else
                        m_figura[i][j] = NO_COLOR;
                }
            }
            m_centreFila = 1;
            m_centreColumna = 1;
        
        case FIGURA_S:
            m_nFiles = 3;
            m_nColumnes = 3;
            m_color = COLOR_VERD;
            for (int i = 0; i < m_nFiles; i++)
            {
                for (int j = 0; j < m_nColumnes; j++)
                {
                    if (i == 0 && (j == 1 || j == 2) || i == 1 && (j == 0 || j == 1))
                        m_figura[i][j] = m_color;
                    else
                        m_figura[i][j] = NO_COLOR;
                }
            }
            m_centreFila = 1;
            m_centreColumna = 1;
            break;
        
        default:
            break;
    }
    
    for (int i = 0; i < m_gir; i++)
        girHorari();
}

void Figura::transposada()
{
    ColorFigura aux;
    int comptador = 1;
    for (int i = 0; i < m_nFiles - 1; i++)
    {
        for (int j = 0 + comptador; j < m_nColumnes; j++)
        {
            aux = m_figura[i][j];
            m_figura[i][j] = m_figura[j][i];
            m_figura[j][i] = aux;
            comptador++;
        }
    }
}

void Figura::invertirColumnes()
{
    ColorFigura matAux[MAX_ALCADA][MAX_AMPLADA];
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            matAux[i][j] = m_figura[i][j];
    }
    
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            m_figura[i][j] = matAux[i][m_nColumnes - 1 - j];
    }
}

void Figura::invertirFiles()
{
    ColorFigura matAux[MAX_ALCADA][MAX_AMPLADA];
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            matAux[i][j] = m_figura[i][j];
    }
    
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            m_figura[i][j] = matAux[m_nFiles - 1 - i][j];
    }
}

void Figura::girHorari()
{
    transposada();
    invertirColumnes();
}

void Figura::girAntiHorari()
{
    transposada();
    invertirFiles();
}

ifstream& operator>>(ifstream& input, Figura& figura)
{
    int tipus, fila, columna, gir;
    input >> tipus >> fila >> columna >> gir;
    figura.setTipus((TipusFigura)tipus);
    figura.setFila(fila);
    figura.setColumna(columna);
    figura.setGir(gir);
    return input;
}
