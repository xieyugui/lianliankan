#include "TopMenu.h"

#include "Audio.h"
#include "GameUtils.h"
#include "GameData.h"
#include "PauseLayer.h"

bool TopMenu::init(){
	if (!Node::init()){
		return false;
	}

	header_bg = Sprite::create("header_bg.png");
	header_bg->setScaleX(GetXScaleRate);
	header_bg->setScaleY(GetYScaleRate);
	header_bg->setPosition(VISIBLE_WIDTH/2,VISIBLE_HEIGHT-header_bg->boundingBox().size.height/2);
	this->addChild(header_bg);

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
	
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(VISIBLE_WIDTH, VISIBLE_HEIGHT);
 
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//暂停页面
	CCDirector::sharedDirector()->pushScene(PauseLayer::scene(renderTexture));
}
