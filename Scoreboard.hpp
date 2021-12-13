#pragma once

#include <fstream>
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;

#define SCORE_CAPACITY 1000

struct Scores {
    int difficulty;
    float s[SCORE_CAPACITY];
    int count = 0;

    void add(float score) {
        s[count] = score;
        count++;
    }

    void clear() {
        count = 0;
    }

    bool empty() {
        return count == 0;
    }

    void sort() {
        for (int i = 0; i < count-1; i++)
            for (int j = i+1; j < count; j++)
                if (s[i] > s[j]) {
                    float temp = s[i];
                    s[i] = s[j];
                    s[j] = temp;
                }
    }

    float pop() {
        count--;
        return s[count];
    }

    float get(int i) {
        return s[i];
    }
};

class Scoreboard {
private:
    sf::Font font;
    sf::Vector2f pos;
    sf::Vector2f size;
    sf::Color fillColor;
    sf::Color borderColor;
    sf::Color textColor;
    float titleFontSize;
    float fontSize;
    int maxDisplayEntries;
    Scores easyScores;
    Scores mediumScores;
    Scores hardScores;

    void drawColumn(sf::RenderWindow &window, const string title, Scores scores, sf::Vector2f position);
    void drawBigTitle(sf::RenderWindow &window);

public:
    Scoreboard();
    void load();
    void save(float time, int difficulty);
    void draw(sf::RenderWindow &window);
    void setSize();
    void setPosition();
    void setFillColor();
    void setTextColor();
    void setBorderColor();
    void setTitleFontSize();
    void setFontSize();
};
