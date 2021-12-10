#pragma once
#include <SFML/Graphics.hpp>

class Menu {
public:
    int choice;
    int numberOfChoice;
    bool choiceSelected = false;

    Menu();
    void HandleEvent(sf::Event event);
    void Draw(sf::RenderWindow &window);

private:
    sf::Vector2u size;
    sf::Vector2i position;

    void ChooseNext();
    void ChoosePrev();
};

