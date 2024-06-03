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
#include "Joc.h"

int main(int argc, const char* argv[])
{
    //Instruccions necesaries per poder incloure la llibreria i que trobi el main
    SDL_SetMainReady();
    SDL_Init(SDL_INIT_VIDEO);

    //Inicialitza un objecte de la classe Screen que s'utilitza per gestionar la finestra grafica
    Screen pantalla(SCREEN_SIZE_X, SCREEN_SIZE_Y);

    Tetris tetris;
    bool final = false;
    int instruccio = 0;

    do
    {
        cout << "MENU PRINCIPAL" << "\n";
        cout << "============" << "\n";
        cout << "1. Joc en mode normal" << "\n";
        cout << "2. Joc en mode test" << "\n";
        cout << "3. Mostrar puntuacions" << "\n";
        cout << "4. Sortir" << "\n";
        cin >> instruccio;

        switch (instruccio)
        {
        case 1:
            tetris.juga(pantalla);
            break;

        case 2:
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

    //Instruccio necesaria per alliberar els recursos de la llibreria 
    SDL_Quit();

    return 0;
}
