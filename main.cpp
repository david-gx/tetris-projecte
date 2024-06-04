#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || defined  (_WIN64)

#include <iostream>
//Definicio necesaria per poder incloure la llibreria i que trobi el main
#define SDL_MAIN_HANDLED
#include <windows.h>
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#include <conio.h>      /* getch */

#elif __APPLE__
//Llibreria grafica
#include "../Graphic Lib/libreria.h"
#include "../Graphic Lib/NFont/NFont.h"
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <SDL2/SDL.h>
#pragma clang diagnostic pop

#endif

#include "./Partida.h"
#include "./InfoJoc.h"

#include "GraphicManager.h"
#include "Tetris.h"

int main(int argc, const char* argv[])
{
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);

    Tetris tetris;
    bool final = false;
    int instruccio = 0;

    string nomFitxerPuntuacions;
    cout << "Introdueix el nom del fitxer on es guardaran les puntuacions: ";
    cin >> nomFitxerPuntuacions;


    ifstream fitxerIn;
    fitxerIn.open(nomFitxerPuntuacions);
    if (fitxerIn.is_open())
    {
        string nomAux;
        int puntuacioAux;
        while (!fitxerIn.eof())
        {
            fitxerIn >> nomAux >> puntuacioAux;
            if (!fitxerIn.eof())
                tetris.afegeixPuntuacio(nomAux, puntuacioAux);
        }
    }
    fitxerIn.close();

    do
    {
        cout << "\n" << "MENU PRINCIPAL" << "\n";
        cout << "============" << "\n";
        cout << "1. Joc en mode normal" << "\n";
        cout << "2. Joc en mode test" << "\n";
        cout << "3. Mostrar puntuacions" << "\n";
        cout << "4. Sortir" << "\n";
        
        string nomFitxerTauler, nomFitxerFigures, nomFitxerMoviments;
        cin >> instruccio;
        switch (instruccio)
        {
        case 1:
            tetris.juga(pantalla, nomFitxerPuntuacions);
            break;

        case 2:            
            cout << "Nom del fitxer amb l'estat inicial del tauler: ";
            cin >> nomFitxerTauler;
            cout << "Nom del fitxer amb la sequencia de figures: ";
            cin >> nomFitxerFigures;
            cout << "Nom del fitxer amb la sequencia de moviments: ";
            cin >> nomFitxerMoviments;
            tetris.jugaModeTest(pantalla, nomFitxerTauler, nomFitxerFigures, nomFitxerMoviments);
            break;

        case 3:
            tetris.mostraPuntuacions();
            break;

        case 4:
            final = true;
            break;

        default:
            cout << "ERROR" << "\n";
            break;
        }

    } while (!final);

    SDL_Quit();

    tetris.guardaPuntuacions(nomFitxerPuntuacions);
    
    return 0;
}
