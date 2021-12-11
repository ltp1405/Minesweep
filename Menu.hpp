#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include "Board.hpp"

void drawGameoverMenu(sf::RenderWindow &window);
void drawGameTitle(sf::RenderWindow &window);
void drawGameStatus(sf::RenderWindow &window, int bomb, int flag, float timer);
void drawStartMenu(sf::RenderWindow &window);
void drawWin(sf::RenderWindow &window);
