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

void LevelSelectContent::initAllLevels(int page,float topH){//初始化当前page 的关卡
	this->removeAllChildren();


	const int eachPageItemCount = g_EachPageCount;

	_levelMenu = Menu::create();//创建关卡菜单
	this->addChild(_levelMenu);
	
	auto levelSp = Sprite::create("lockLevel.png");
	float levelW = levelSp->getContentSize().width*GameData::getInstance()->getlevelSacle();
	float space = level_space;
	//float constStartPositionX = levelW/2+space*2;
	float constStartPositionX = VISIBLE_WIDTH * 0.5 - (levelW+space*2)*(g_EachLineCount / 2 )+levelW/2+space;
	log("rizhi=%f,=%f,=%f",levelW,VISIBLE_WIDTH * 0.5,constStartPositionX);
	float startPositionX = constStartPositionX;
	float topStartPositionY = VISIBLE_HEIGHT - topH - levelW/2;

	for (int i = 0 + page * eachPageItemCount; i < eachPageItemCount + page * eachPageItemCount; i++){
		if (i < g_maxLevel){
			int lineCount = g_EachLineCount;
			if (i != (0 + page * eachPageItemCount) && i % lineCount == 0){
				startPositionX = constStartPositionX;
				topStartPositionY = topStartPositionY - levelW -space *2;
			}

			int levelCount = i + 1;
			auto oneLevelItem = LevelSelectItem::create(levelCount);
			_levelMenu->addChild(oneLevelItem);
			log("jiba = %f, =%f,=%f",oneLevelItem->getContentSize().width,oneLevelItem->getContentSize().height,GameData::getInstance()->getlevelSacle());
			oneLevelItem->setPosition(startPositionX, topStartPositionY);
			startPositionX += levelW+space*2;
		}
	}

	_levelMenu->setPosition(0, 0);
	_levelMenu->setOpacity(0);
	auto fadeAction = FadeIn::create(0.5);
	_levelMenu->runAction(fadeAction);
}