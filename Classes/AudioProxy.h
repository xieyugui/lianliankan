#ifndef _LIANLIANKANX_AUDIO_H_
#define _LIANLIANKANX_AUDIO_H_

#include "cocos2d.h"


class AudioProxy {
public:
	static AudioProxy* getInstance();
	void playBGM(); //��������  class.mp3
	void playSprite();//���ͼ������ 12.wav
	void playEliminate();// �������� 4.wav
	void prepare();
	void playButtonClick();
	AudioProxy(){};
private:
	static AudioProxy* m_instance;
};

#endif
