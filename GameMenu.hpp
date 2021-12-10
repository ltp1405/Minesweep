#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;

class Menu {
public:
    int choice;
    int numberOfChoice;
    bool choiceSelected = false;
    string entries[100];

    Menu();
    void HandleEvent(sf::Event event);
    void Draw(sf::RenderWindow &window);
    void AddEntry(string name);

private:
    sf::Vector2u size;
    sf::Vector2i position;

    void ChooseNext();
    void ChoosePrev();
};


class StartMenu : public Menu {
public:
    enum {
        CONTINUE,
        NEW,
        QUIT,
    };
};
