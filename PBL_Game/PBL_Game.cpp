// PBL_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "Game.hpp"
#include "Window.hpp"

using namespace PBLGame;

int main()
{
    Window okienko(Game::WINDOW_WIDTH, Game::WINDOW_HEIGHT, "37");
    Game gierka(okienko);
    gierka.Granko();
}

