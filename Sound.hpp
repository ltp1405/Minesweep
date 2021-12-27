#pragma once

#include <SFML/Audio.hpp>

class Sound {
public:
	Sound(){
		bufferClick.loadFromFile("./resource/sound/click.wav");
		Click.setBuffer(bufferClick);

		bufferFlag.loadFromFile("./resource/sound/flag.wav");
		Flag.setBuffer(bufferFlag);

		Win.openFromFile("./resource/sound/win.wav");
	}
	void playClick();
	void playFlag();
	void winning();

private:
	sf::SoundBuffer bufferClick;
	sf::Sound Click;

	sf::SoundBuffer bufferFlag;
	sf::Sound Flag;

	sf::Music Win;
	sf::Music Lose;
};