#include "TopMenu.h"
#include "GameUtils.h"
#include "GameData.h"
#include "Audio.h"
#include "PauseLayer.h"

bool TopMenu::init(){
	if (!Node::init()){
		return false;
	}
	level = Label::create(String::create("Level: ")->_string + String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string, "Verdana-Bold", 30);
	level->setPosition(100, VISIBLE_HEIGHT - 50);
	this->addChild(level,1);

	auto startBtn = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_0(TopMenu::pauseGame, this));
	auto menu = Menu::create(startBtn, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT - 50));
	this->addChild(menu,1);

	return true;
}


void TopMenu::refresh(){
	
	level->setString(String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string);
}

void TopMenu::pauseGame() {
	Audio::getInstance()->playButtonClick();
	//得到窗口的大小  
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width, visibleSize.height);

	//遍历当前类的所有子节点信息，画入renderTexture中。  
	//这里类似截图。  
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//将游戏界面暂停，压入场景堆栈。并切换到GamePause界面  
	CCDirector::sharedDirector()->pushScene(PauseLayer::scene(renderTexture));
}
