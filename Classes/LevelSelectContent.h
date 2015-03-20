#ifndef __LIANLIANKANX__LevelSelectContent__
#define __LIANLIANKANX__LevelSelectContent__

#include "cocos2d.h"
#include "LevelSelectItem.h"
USING_NS_CC;

class LevelSelectContent :public Layer{
public:
	LevelSelectContent();
	~LevelSelectContent();
	virtual bool init();
	CREATE_FUNC(LevelSelectContent);
	void contentFadeOut();
	void initAllLevels(int page);
private:
	Menu* _levelMenu;


};

#endif