#include "GameScene.h"
#include "GameLayer.h"
#include "Audio.h"

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	Audio::getInstance()->playBGM();
	this->addChild(GameLayer::create());
	return true;
}