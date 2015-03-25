#include "MenuLayer.h"
#include "Audio.h"
#include "GameUtils.h"
#include "GameData.h"
#include "LevelSelectLayer.h"
#include "SetMusic.h"

bool MenuLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//log("yuanshi daxiao %f", visibleSize.height);

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	
	// 初始化背景
	auto background = Sprite::create("bg_title.png");
	float wBg = background->getContentSize().width;
	if (VISIBLE_WIDTH > wBg) {
		wBg = VISIBLE_WIDTH - (VISIBLE_WIDTH - wBg) / 2;
	}
	
	auto rect = Rect(((VISIBLE_WIDTH - wBg) / 2) / wBg, 1, wBg, VISIBLE_HEIGHT);   //图片的大小
	background->setTextureRect(rect);
	background->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	log("GameUtil1 %f", VISIBLE_WIDTH);
	this->addChild(background, -1);

	//初始化菜单
	startBtn = MenuItemImage::create("menu_adventure.png", "menu_adventure.png", CC_CALLBACK_0(MenuLayer::startGame, this));
	startBtn->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));

	pSetting = MenuItemImage::create("Setting_n.png", "setting_s.png",
		CC_CALLBACK_0(MenuLayer::menuSetting, this));
	pSetting->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 - 80));

	//初始化more 和静音按钮
	moreBtn = MenuItemImage::create("button_sound_on.png", "button_sound_on.png",
		CC_CALLBACK_0(MenuLayer::menuSetting, this));
	moreBtn->setPosition(Vec2(VISIBLE_WIDTH - moreBtn->getContentSize().width / 2 - 10, VISIBLE_HEIGHT - moreBtn->getContentSize().height / 2 - 10));

	//soundBtn = MenuItemImage::create("button_sound_on.png", "button_sound_off.png",
	//	CC_CALLBACK_0(MenuLayer::menuSetting, this));
	//soundBtn->setPosition(Vec2(VISIBLE_WIDTH - soundBtn->getContentSize().width / 2 - 20 - moreBtn->getContentSize().width, VISIBLE_HEIGHT - soundBtn->getContentSize().height / 2 - 10));

	// 添加 声音  的开关按钮
	MenuItemImage *_turnOn, *_turnOff;
	_turnOn = MenuItemImage::create(
		"button_sound_on.png",
		"button_sound_on.png");
	_turnOff = MenuItemImage::create(
		"button_sound_off.png",
		"button_sound_off.png");
	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MenuLayer::menuMusicCallback, this), _turnOn, _turnOff, NULL);

	//toggleItem->setScale(0.3f);
	toggleItem->setPosition(Vec2(VISIBLE_WIDTH - _turnOn->getContentSize().width / 2 - 20 - moreBtn->getContentSize().width, VISIBLE_HEIGHT - _turnOn->getContentSize().height / 2 - 10));

	pMenu = Menu::create(moreBtn,toggleItem,startBtn, pSetting, NULL);
	pMenu->setPosition(Vec2::ZERO);

	this->addChild(pMenu,0);


	return true;

}

void MenuLayer::menuMusicCallback()
{    
	GameData::getInstance()->playOrStopMusic();
	GameData::getInstance()->setisPause(( (GameData::getInstance()->getisPause() == false) ? true:false));
}

void MenuLayer::menuQuit()
{
	Director::getInstance()->end();
}

void MenuLayer::menuSetting()
{
	Scene *pScene = Scene::create();
	pScene->addChild(SetMusic::create());
	Director::getInstance()->replaceScene(pScene);
}

void MenuLayer::startGame() {
	GameData::getInstance();
	Director::getInstance()->replaceScene(LevelSelectLayer::createScene());
	log("START!");
}