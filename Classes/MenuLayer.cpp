#include "MenuLayer.h"

#include "GameUtils.h"
#include "GameData.h"
#include "LevelSelectLayer.h"

bool MenuLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	auto background = Sprite::create("title_bg.png");
	//float wBg = background->getContentSize().width;
	
	//Rect rect;
	//if (VISIBLE_WIDTH >= 680) {
	//	rect = Rect((wBg - VISIBLE_WIDTH)/2, 1, VISIBLE_WIDTH, VISIBLE_HEIGHT);   //ͼƬ�Ĵ�С
	//}else {
	//	rect = Rect((wBg - 680)/2, 1, 680, 960);   //ͼƬ�Ĵ�С
	//}

	//background->setTextureRect(rect);
	background->setScaleX(GetXScaleRate);
	background->setScaleY(GetYScaleRate);
	background->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	log("GameUtil1 %f", VISIBLE_WIDTH);
	this->addChild(background, -1);


	//开始按钮
	startBtn = MenuItemImage::create("btn_start.png", "btn_start.png", CC_CALLBACK_0(MenuLayer::startGame, this));
	startBtn->setScaleX(GetXScaleRate);
	startBtn->setScaleY(GetYScaleRate);
	startBtn->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));

	//more
	//moreBtn = MenuItemImage::create("btn_more.png", "btn_more.png",CC_CALLBACK_0(MenuLayer::menuMore, this));
	//moreBtn->setScaleX(GetXScaleRate);
	//moreBtn->setScaleY(GetYScaleRate);
	//moreBtn->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 - moreBtn->boundingBox().size.height - 20));
	//log("morebtn = %f, = %f",moreBtn->getContentSize().height,moreBtn->boundingBox().size.height);

	// music
	MenuItemImage *_turnOn, *_turnOff;
	_turnOn = MenuItemImage::create(
		"music_p.png",
		"music_p.png");
	_turnOff = MenuItemImage::create(
		"music_c.png",
		"music_c.png");
	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MenuLayer::menuMusicCallback, this), _turnOn, _turnOff, NULL);
	toggleItem->setScaleX(GetXScaleRate);
	toggleItem->setScaleY(GetYScaleRate);
	toggleItem->setPosition(Vec2(VISIBLE_WIDTH - _turnOn->boundingBox().size.width / 2 - 10 , VISIBLE_HEIGHT - _turnOn->boundingBox().size.height / 2 - 10));
	if(GameData::getInstance()->getisPause())
		toggleItem->setSelectedIndex(1);

	pMenu = Menu::create(toggleItem,startBtn, NULL);
	pMenu->setPosition(Vec2::ZERO);

	this->addChild(pMenu,0);


	return true;

}

void MenuLayer::menuMusicCallback()
{    
	GameData::getInstance()->playOrStopMusic();
	GameData::getInstance()->setisPause(( (GameData::getInstance()->getisPause() == false) ? true:false));
}

void MenuLayer::menuMore(){

}

void MenuLayer::menuQuit()
{
	Director::getInstance()->end();
}


void MenuLayer::startGame() {
	GameData::getInstance();
	Director::getInstance()->replaceScene(LevelSelectLayer::createScene());
	log("START!");
}
