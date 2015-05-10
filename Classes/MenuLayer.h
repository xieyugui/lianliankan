#ifndef _LIANLIANKANX_MENULAYER_H_
#define _LIANLIANKANX_MENULAYER_H_
#include "cocos2d.h"

USING_NS_CC;

class MenuLayer : public Layer{
public:
	virtual bool init();
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent);
	CREATE_FUNC(MenuLayer);
	void startGame();

	void menuQuit();
	void menuMore();

	void menuMusicCallback();
	void doubleClickState(float tt);

private:
	MenuItemImage *startBtn;
	MenuItemImage *moreBtn;
	MenuItemImage *soundBtn;

	Menu *pMenu;

	bool clicked;
};

#endif