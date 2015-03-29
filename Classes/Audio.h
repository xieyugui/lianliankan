#ifndef _LIANLIANKANX_AUDIO_H_
#define _LIANLIANKANX_AUDIO_H_

#include "cocos2d.h"

class Audio {
public:
	static Audio* getInstance();
	void playBGM(); //背景音乐
	void playSprite();//点击图标音乐 12.wav
	void playEliminate();// 消除音乐 4.wav
	void prepare();
	void playButtonClick();
	void pauseAllEffects(); //暂停所有音乐
	void resumeAllEffects();//恢复所有音乐

	Audio();
private:
	static Audio* m_instance;

	bool isPause;
};

#endif
