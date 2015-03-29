#ifndef _LIANLIANKANX_SETMUSIC_H_
#define _LIANLIANKANX_SETMUSIC_H_

#include "cocos2d.h"

USING_NS_CC;

class SetMusic : public Layer
{
public:
	SetMusic();
	~SetMusic();

	bool init();
	void initSwitch();

	CREATE_FUNC(SetMusic);

	void menuBackMainMenu();
	void menuMusic();
	void menuEffect();

	virtual void onEnter();
	virtual void onExit();
private:
	bool bSoundEffect;
	bool bMusic;
	Sprite *pMusic;
	Sprite *pSoundEffect;
	SpriteFrame *pMusicOn;
	SpriteFrame *pMusicOff;
	SpriteFrame *pEffectOn;
	SpriteFrame *pEffectOff;
};

#endif