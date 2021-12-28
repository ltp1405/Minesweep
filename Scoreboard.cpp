#include "Scoreboard.hpp"

Scoreboard::Scoreboard() {
    font.loadFromFile("./resource/FFFFORWA.TTF");
    fillColor = sf::Color(237, 205, 97), borderColor = sf::Color::Black,
    textColor = sf::Color::Black;
    size = sf::Vector2f(640.f, 600.f);
    pos = sf::Vector2f(300.f, 150.f);
    maxDisplayEntries = 8;
    fontSize = 16;
    titleFontSize = 28;
    easyScores.difficulty = 0;
    mediumScores.difficulty = 1;
    hardScores.difficulty = 2;
}

void Scoreboard::drawColumn(sf::RenderWindow &window, const string titleString,
                            Scores scores, sf::Vector2f position) {
    float lineSpacing = 40.f;
    float titleSpacing = 40.f;
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(fontSize);
    text.setFillColor(textColor);
    text.setPosition(position);
    text.setOrigin(titleString.length() * titleFontSize / 1.8, 0.f);

    sf::Text title;
    title.setFont(font);
    title.setCharacterSize(titleFontSize);
    title.setFillColor(textColor);
    title.setPosition(position);
    title.setOrigin(titleString.length() * titleFontSize / 1.8, 0.f);

    title.setString(titleString);
    float xOffset = titleFontSize * 0.8 * (titleString.length() / 2) - 24.f;
    text.move(xOffset, titleSpacing);
    window.draw(title);
    int i = 0;
    while (i < scores.count && i < maxDisplayEntries) {
        char s[20];
        float n = scores.get(i);
        sprintf_s(s, "%04.2fs", n);
        text.setString(s);
        text.move(0.f, lineSpacing);
        window.draw(text);
        i++;
    }
}

void Scoreboard::drawBigTitle(sf::RenderWindow &window) {
    sf::Text title;
    title.setFont(font);
    title.setFillColor(textColor);
    title.setCharacterSize(48);
    title.setString("SCOREBOARD");
    title.setPosition(375.f, 50.f);
    window.draw(title);
}

void Scoreboard::draw(sf::RenderWindow &window) {
    drawBigTitle(window);
    sf::Vector2f winSize(window.getSize());
    pos.x = winSize.x / 2 - size.x / 2;
    float colSpacing = 220.f;
    float lineSpacing = 60.f;
    float titleSpacing = 80.f;
    sf::RectangleShape rect(size);
    rect.setPosition(pos);
    rect.setFillColor(fillColor);
    rect.setOutlineThickness(4.f);
    rect.setOutlineColor(borderColor);
    window.draw(rect);

    sf::Vector2f colPos(pos);
    colPos += sf::Vector2f(125.f, 75.f);
    drawColumn(window, "EASY", easyScores, colPos);
    colPos += sf::Vector2f(colSpacing, 0);
    drawColumn(window, "MEDIUM", mediumScores, colPos);
    colPos += sf::Vector2f(colSpacing, 0);
    drawColumn(window, "HARD", hardScores, colPos);
}

void Scoreboard::save(float time, int difficulty) {
    ofstream fout;
    fout.open("record.dta", ios::app);
    fout << time << " " << difficulty << endl;
    fout.close();
}

void Scoreboard::load() {
    easyScores.clear();
    mediumScores.clear();
    hardScores.clear();
    ifstream fin;
    fin.open("record.dta");
    if (!fin)
        return;
    while (true) {
        float time;
        int difficulty;
        fin >> time >> difficulty;
        if (fin.eof())
            break;
        if (difficulty == easyScores.difficulty)
            easyScores.add(time);
        else if (difficulty == mediumScores.difficulty)
            mediumScores.add(time);
        else if (difficulty == hardScores.difficulty)
            hardScores.add(time);
    }
    easyScores.sort();
    mediumScores.sort();
    hardScores.sort();
    fin.close();
}

// int main() {
//     sf::RenderWindow window(sf::VideoMode(900, 900), "TESTING",
//     sf::Style::Close);
//
//     Scoreboard sBoard;
//     sBoard.load();
//     while (window.isOpen()) {
//         window.clear(sf::Color::White);
//         sf::Event event;
//         while (window.pollEvent(event)) {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//             else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
//                 sBoard.save(10.f, 1);
//             }
//         }
//         sBoard.draw(window);
//         window.display();
//     }
// }
