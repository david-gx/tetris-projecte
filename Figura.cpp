#include "Figura.h"

/**
* Figura
* Constructor per defecte de la classe figura
*/
Figura::Figura()
{
    m_tipus = NO_FIGURA;
    m_fila = -1;
    m_columna = -1;
    m_gir = 0;
    m_color = NO_COLOR;
    m_nFiles = 0;
    m_nColumnes = 0;
    m_moviment = true;
    for (int i = 0; i < MAX_ALCADA; i++)
    {
        for (int j = 0; j < MAX_AMPLADA; j++)
            m_figura[i][j] = m_color;
    }
}

/**
* operator=
* Sobrecàrrega de l'operador =
*/
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
        m_moviment = f.getMoviment();

        for (int i = 0; i < m_nFiles; i++)
        {
            for (int j = 0; j < m_nColumnes; j++)
                m_figura[i][j] = f.getFigura(i, j);
        }
    }
    return *this;
}

/**
* inicialitzaFigura
* Funció que inicialitza la matriu de la figura i la marca com a no fixa. Assumeix la prèvia
* assignació de les variables m_tipus, m_fila, m_columna i m_gir
*/
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
                    m_figura[i][j] = m_color;
                else
                    m_figura[i][j] = NO_COLOR;
            }
        }
        break;

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
        break;

    default:
        break;
    }

    m_moviment = true;
    for (int i = 0; i < m_gir; i++)
        girHorari();
}


/**
* transposada
* Funció que calcula la transposada de la matriu de la figura
*/
void Figura::transposada()
{
    ColorFigura aux;
    int comptador = 1;
    for (int i = 0; i < m_nFiles - 1; i++)
    {
        for (int j = comptador; j < m_nColumnes; j++)
        {
            aux = m_figura[i][j];
            m_figura[i][j] = m_figura[j][i];
            m_figura[j][i] = aux;
        }
        comptador++;
    }
}

/**
* invertirColumnes
* Funció que inverteix les columnes de la matriu de la figura
*/
void Figura::invertirColumnes()
{
    // Crea una matriu auxiliar
    ColorFigura** matAux;
    matAux = new ColorFigura * [m_nFiles];
    for (int i = 0; i < m_nFiles; i++)
        matAux[i] = new ColorFigura[m_nColumnes];

    // Guarda la matriu de la figura en la matriu auxiliar
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            matAux[i][j] = m_figura[i][j];
    }

    // Inverteix les columnes en la matriu de la figura utilitzant la matriu auxiliar
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            m_figura[i][j] = matAux[i][m_nColumnes - 1 - j];
    }

    // Elimina la matriu auxiliar
    for (int i = 0; i < m_nFiles; i++)
    {
        delete matAux[i];
        matAux[i] = nullptr;
    }
    delete matAux;
    matAux = nullptr;
}

/**
* invertirFiles
* Funció que inverteix les files de la matriu de la figura
*/
void Figura::invertirFiles()
{
    // Crea una matriu auxiliar
    ColorFigura** matAux;
    matAux = new ColorFigura * [m_nFiles];
    for (int i = 0; i < m_nFiles; i++)
        matAux[i] = new ColorFigura[m_nColumnes];

    // Guarda la matriu de la figura en la matriu auxiliar
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            matAux[i][j] = m_figura[i][j];
    }

    // Inverteix les files en la matriu de la figura utilitzant la matriu auxiliar
    for (int i = 0; i < m_nFiles; i++)
    {
        for (int j = 0; j < m_nColumnes; j++)
            m_figura[i][j] = matAux[m_nFiles - 1 - i][j];
    }

    // Elimina la matriu auxiliar
    for (int i = 0; i < m_nFiles; i++)
    {
        delete matAux[i];
        matAux[i] = nullptr;
    }
    delete matAux;
    matAux = nullptr;
}

/**
* girHorari
* Funció que gira la matriu de la figura en sentit horari
*/
void Figura::girHorari()
{
    transposada();
    invertirColumnes();
}

/**
* girAntihorari
* Funció que gira la matriu de la figura en sentit antihorari
*/
void Figura::girAntiHorari()
{
    transposada();
    invertirFiles();
}

/**
* operator>>
* Sobrecàrrega de l'operador >>
*/
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
