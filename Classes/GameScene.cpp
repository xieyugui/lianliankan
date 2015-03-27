#include "GameScene.h"

#include "AudioProxy.h"
#include "GameLayer.h"
USING_NS_CC;
bool GameScene::init() {
	if (!Scene::init()) {
		return false;
	}
	AudioProxy::getInstance()->playBGM();
	this->addChild(GameLayer::create());
	return true;
}
