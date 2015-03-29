#include "GameScene.h"
#include "GameLayer.h"
#include "Audio.h"
#include "GameData.h"

USING_NS_CC;
bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	Audio::getInstance()->playBGM();

	this->addChild(GameLayer::create());
	return true;
}
