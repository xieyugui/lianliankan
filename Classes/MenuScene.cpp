#include "MenuScene.h"
#include "MenuLayer.h"
#include "cocos-ext.h"
#include "ExtensionMacros.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "AudioProxy.h"

USING_NS_CC_EXT;
USING_NS_CC;

bool MenuScene::init() {
	if (!Scene::init()) {
		return false;
	}
	AudioProxy::getInstance()->playBGM();
	this->addChild(MenuLayer::create());
	return true;
}