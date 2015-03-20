#ifndef _LIANLIANKANX_AUDIO_H_
#define _LIANLIANKANX_AUDIO_H_

#include "cocos2d.h"

class Audio {
public:
	static Audio* getInstance();
	void playBGM(); //±≥æ∞“Ù¿÷  class.mp3
	void playSprite();//µ„ª˜Õº±Í“Ù¿÷ 12.wav
	void playEliminate();// œ˚≥˝“Ù¿÷ 4.wav
	void prepare();
	void playButtonClick();
private:
	static Audio* m_instance;
};

#endif