#include "Game.h"

/*
 * File:   main.cpp
 * Author: Marijo Blazevic https://github.com/marijoblaz
 * Class:  SPA
 * Assigment: 1st year game project
 * See "SPA_PROJ_002_CUSTOM_GAME.docx" for game decisions.
 *
 *
 *   |STATES|
 *   Game -> MainState ->  [->Info o programeru
 *                         |                       
 *                         [->GameState->[GameEditor
 *                         |
 *                         [->lestBogo
 *                         |
 *                         [->guessTheNumber
 *                         |
 *                         [->theMergeDance
 *                         |
 *                         [->theMergeDance
 *
 *  IMPLEMENTING ALL TASKS!
 *  
 *
 *
 */


int main()
{  
    //Game instance
    Game game;

    //Running!!
    game.run();

    return 0;
}