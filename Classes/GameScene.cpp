#include "GameScene.h"
#include "GameLayer.h"
#include "Audio.h"
#include "GameData.h"

bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	Audio::getInstance()->playBGM();

	this->addChild(GameLayer::create());
	return true;
}