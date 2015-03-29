#ifndef _LIANLIANKANX_AUDIO_H_
#define _LIANLIANKANX_AUDIO_H_

#include "cocos2d.h"

class Audio {
public:
	static Audio* getInstance();
	void playBGM(); //��������  class.mp3
	void playSprite();//���ͼ������ 12.wav
	void playEliminate();// �������� 4.wav
	void prepare();
	void playButtonClick();
	void pauseAllEffects(); //��ͣ������Ч
	void resumeAllEffects();//�ָ�������Ч

	Audio();
private:
	static Audio* m_instance;

	bool isPause;
};

#endif
