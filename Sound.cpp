#include "Sound.hpp"

using namespace std;

void Sound::playClick(){
	Click.play();
}

void Sound::playFlag() {
	Flag.play();
}

void Sound::playWin() {
	Win.play();
}

void Sound::playLose() {
	Lose.play();
}
