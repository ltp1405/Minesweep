#include "Sound.hpp"

using namespace std;

void Sound::playClick(){
	Click.play();
}

void Sound::playFlag() {
	Flag.play();
}

void Sound::winning() {
	Win.play();
}
