#include "LevelSelectContent.h"
#include "GameUtils.h"

LevelSelectContent::LevelSelectContent(){

}
LevelSelectContent::~LevelSelectContent(){

}

bool LevelSelectContent::init(){
	if (!Layer::init()){
		return false;
	}

	//initAllLevels();
	return true;
}

void LevelSelectContent::contentFadeOut(){//内容渐渐消失
	auto fadeAction = FadeOut::create(0.2);
	this->runAction(fadeAction);
}

void LevelSelectContent::initAllLevels(int page){//初始化当前page 的关卡
	this->removeAllChildren();


	const int eachPageItemCount = g_EachPageCount;

	_levelMenu = Menu::create();//创建关卡菜单
	this->addChild(_levelMenu);

	int const constStartPositionX = VISIBLE_WIDTH * 0.5 - levelMarginX * (g_EachLineCount / 2 - 0.5);
	int startPositionX = constStartPositionX;
	int topStartPositionY = VISIBLE_HEIGHT * 0.5 + levelMarginY * (g_EachPageCount / g_EachLineCount / 2 - 0.5);

	for (int i = 0 + page * eachPageItemCount; i < eachPageItemCount + page * eachPageItemCount; i++){
		if (i < g_maxLevel){
			int lineCount = g_EachLineCount;
			if (i != (0 + page * eachPageItemCount) && i % lineCount == 0){
				startPositionX = constStartPositionX;
				topStartPositionY = topStartPositionY - levelMarginY;
			}

			int levelCount = i + 1;
			auto oneLevelItem = LevelSelectItem::create(levelCount);
			_levelMenu->addChild(oneLevelItem);
			oneLevelItem->setPosition(startPositionX, topStartPositionY);
			startPositionX += levelMarginX;
		}
	}

	_levelMenu->setPosition(0, 0);
	_levelMenu->setOpacity(0);
	auto fadeAction = FadeIn::create(0.5);
	_levelMenu->runAction(fadeAction);
}