#include "MenuLayer.h"

#include "AudioProxy.h"
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
	
	// ��ʼ������
	auto background = Sprite::create("background.png");
	background->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	log("GameUtil1 %f", VISIBLE_WIDTH);
	this->addChild(background, -1);

	//��ʼ���˵�
	startBtn = MenuItemImage::create("menu_adventure.png", "menu_adventure.png", CC_CALLBACK_0(MenuLayer::startGame, this));
	startBtn->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));

	pSetting = MenuItemImage::create("Setting_n.png", "setting_s.png",
		CC_CALLBACK_0(MenuLayer::menuSetting, this));
	pSetting->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 - 80));

	pMenu = Menu::create(startBtn, pSetting, NULL);
	pMenu->setPosition(Vec2::ZERO);

	//auto menu = Menu::create(startBtn, NULL);
	//menu->alignItemsVertically();
	//menu->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));

	this->addChild(pMenu);
	return true;

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