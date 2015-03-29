#ifndef __LIANLIANKANX__LevelSelectItem__
#define __LIANLIANKANX__LevelSelectItem__

#include "cocos2d.h"
#include "GameData.h"
#include <string>
USING_NS_CC;


class LevelSelectItem : public MenuItemSprite{
	CC_SYNTHESIZE(int, _level, Level);//定义了get set //varType, varName, funName 可以解鎖的等級
	CC_SYNTHESIZE(LevelItemType, _type, Type);
public:
	LevelSelectItem(int level);//构造函数
	static LevelSelectItem* create(int level); //创建本身
private:
	void selectCallBack(Ref* sender);
	void extraInit();
	std::string getFrameNameByType(const LevelItemType& type);
};

#endif