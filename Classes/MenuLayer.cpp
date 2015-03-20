#include "MenuLayer.h"
#include "Audio.h"
#include "GameUtils.h"
#include "GameData.h"
#include "LevelSelectLayer.h"

bool MenuLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//log("yuanshi daxiao %f", visibleSize.height);

	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);
	
	// 初始化背景
	auto background = Sprite::create("background.png");
	background->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	log("GameUtil1 %f", VISIBLE_WIDTH);
	this->addChild(background, -1);

	//初始化菜单
	auto startBtn = MenuItemImage::create("menu_adventure.png", "menu_adventure.png", CC_CALLBACK_0(MenuLayer::startGame, this));
	auto menu = Menu::create(startBtn, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	log("GameUtil2 %f", VISIBLE_WIDTH);
	this->addChild(menu);
	return true;

}

void MenuLayer::startGame() {
	GameData::getInstance();
	Director::getInstance()->replaceScene(LevelSelectLayer::createScene());
	log("START!");
}