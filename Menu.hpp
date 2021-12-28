#pragma once

#include "Board.hpp"
#include <SFML/Graphics.hpp>
#include <string>

void drawBackground(sf::RenderWindow &window);
void drawGameoverMenu(sf::RenderWindow &window);
void drawGameTitle(sf::RenderWindow &window);
void drawGameStatus(sf::RenderWindow &window, int bomb, int flag, float timer);
void drawStartMenu(sf::RenderWindow &window);
void drawWin(sf::RenderWindow &window);
