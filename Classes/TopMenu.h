#ifndef _TOPMENU_H_
#define _TOPMENU_H_
#include "cocos2d.h"
#include "GameLayer.h"

USING_NS_CC;

class TopMenu : public Node{
public:
	virtual bool init();
	CREATE_FUNC(TopMenu);
	void refresh();
	void overGame();

private:
	void pauseGame();
	void promptGame();
};
#endif