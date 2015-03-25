#ifndef _LIANLIANKANX_MENULAYER_H_
#define _LIANLIANKANX_MENULAYER_H_
#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public Layer{
public:
	virtual bool init();
	CREATE_FUNC(MenuLayer);
	void startGame();

	void menuQuit();
	void menuSetting();

	void menuMusicCallback();

private:
	MenuItemImage *startBtn;
	MenuItemImage *pSetting;
	MenuItemImage *moreBtn;
	MenuItemImage *soundBtn;

	Menu *pMenu;
};

#endif