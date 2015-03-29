#include "TopMenu.h"

#include "Audio.h"
#include "GameUtils.h"
#include "GameData.h"
#include "PauseLayer.h"
#include "OverLayer.h"

bool TopMenu::init(){
	if (!Node::init()){
		return false;
	}

	header_bg = Sprite::create("header_bg.png");
	header_bg->setScaleX(GetXScaleRate);
	header_bg->setScaleY(GetYScaleRate);
	header_bg->setPosition(VISIBLE_WIDTH/2,VISIBLE_HEIGHT-header_bg->boundingBox().size.height/2);
	this->addChild(header_bg,1);

	float topH = VISIBLE_HEIGHT-header_bg->boundingBox().size.height/2;

	level = Label::create(String::create("Level: ")->_string + String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string, "Verdana-Bold", 30);
	level->setPosition(100, topH);
	this->addChild(level,2);

	startBtn = MenuItemImage::create("btn_pause.png", "btn_pause.png", CC_CALLBACK_0(TopMenu::pauseGame, this));
	startBtn->setScaleX(GetXScaleRate);
	startBtn->setScaleY(GetYScaleRate);
	startBtn->setPosition(Vec2(VISIBLE_WIDTH - startBtn->boundingBox().size.width/2 - 100,topH));

	menu = Menu::create(startBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	//menu->alignItemsVertically();
	this->addChild(menu,2);

	return true;
}


void TopMenu::refresh(){
	
	level->setString(String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string);
}

void TopMenu::pauseGame() {
	Audio::getInstance()->playButtonClick();
	
	CCSize visibleSize = CCDirector::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(VISIBLE_WIDTH, VISIBLE_HEIGHT);
 
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//暂停页面
	CCDirector::getInstance()->pushScene(PauseLayer::scene(renderTexture));
}

//结束版面
void TopMenu::overGame() {

	CCSize visibleSize = CCDirector::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(VISIBLE_WIDTH, VISIBLE_HEIGHT);
 
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//结束页面
	CCDirector::getInstance()->pushScene(OverLayer::scene(renderTexture));
}
