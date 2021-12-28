#pragma once

#include <SFML/Audio.hpp>

class Sound {
public:
	Sound(){
		bufferClick.loadFromFile("./resource/sound/click.wav");
		Click.setBuffer(bufferClick);

		bufferFlag.loadFromFile("./resource/sound/flag.wav");
		Flag.setBuffer(bufferFlag);

		bufferWin.loadFromFile("./resource/sound/win.wav");
		Win.setBuffer(bufferWin);

		bufferLose.loadFromFile("./resource/sound/lose.wav");
		Lose.setBuffer(bufferLose);
	}
	void playClick();
	void playFlag();
	void playWin();
	void playLose();

private:
	sf::SoundBuffer bufferClick;
	sf::Sound Click;

	sf::SoundBuffer bufferFlag;
	sf::Sound Flag;

	sf::SoundBuffer bufferWin;
	sf::Sound Win;

	sf::SoundBuffer bufferLose;
	sf::Sound Lose;
};