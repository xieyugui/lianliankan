#ifndef __LIANLIANKANX__LEVELSELECTLAYER__
#define __LIANLIANKANX__LEVELSELECTLAYER__

#include "cocos2d.h"
#include "LevelSelectContent.h"

USING_NS_CC;

class LevelSelectLayer :public Layer{
public:
	LevelSelectLayer();
	~LevelSelectLayer();
	virtual bool init();
	CREATE_FUNC(LevelSelectLayer);
	static Scene* createScene();

private:
	LevelSelectContent* levelSelectContent;//等级内容
	int _currentPage;//当前页
	int _maxPage;//最大页数
	MenuItemImage* leftMenuSpritePre;
	MenuItemImage* rightMenuSpritePre;
	Menu* pageMenu;
	MenuItemImage* pBack;
	Menu* pMenu;

	void initNavigation();//初始化导航
	void initAllLevels();//初始化所有等级
	void nextPageBack();//下一页
	void prePageBack();//前一页
	void menuBackMainMenu();
};


#endif