#pragma once
#include "Button.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Menu {
  public:
    int choice;
    int numberOfChoice;
    bool choiceSelected = false;
    PushButton entries[100];

    Menu();
    void handleEvent(sf::Event event);
    void draw(sf::RenderWindow &window);
    void addEntry(string name);

  private:
    sf::Vector2u size;
    sf::Vector2i position;

    void chooseNext();
    void choosePrev();
    void getChoiceFromMousePosition(sf::Vector2f mousePos,
                                    sf::Vector2f winSize);
};

class StartMenu : public Menu {
  public:
    enum {
        CONTINUE,
        NEW,
        QUIT,
    };
};
