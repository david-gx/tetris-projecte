#include "Figura.h"

Figura::Figura()
{
    m_tipus = NO_FIGURA;
    m_fila = -1;
    m_columna = -1;
    m_gir = 0;
    m_color = NO_COLOR;
    for (int i = 0; i < MAX_ALCADA; i++)
    {
        for (int j = 0; j < MAX_AMPLADA; j++)
            m_figura[i][j] = m_tipus;
    }
}
