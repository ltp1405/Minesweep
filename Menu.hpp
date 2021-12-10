#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

void DrawGameoverMenu(sf::RenderWindow &window);
void DrawGameTitle(sf::RenderWindow &window);
void DrawGameStatus(sf::RenderWindow &window, int bomb, int flag, float timer);
void DrawStartMenu(sf::RenderWindow &window);
void DrawWin(sf::RenderWindow &window);
