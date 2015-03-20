//
//  PauseScene.mm
//  MR_BOMB
//
//  Created by yunong on 1/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "PauseLayer.h"
#include "SimpleAudioEngine.h"
#include "MenuLayer.h"
#include "GameUtils.h"
#include "Audio.h"
#include "LevelSelectLayer.h"
#include "GameScene.h"

USING_NS_CC;

bool PauseLayer::init()
{

	if (!CCLayer::init())
	{
		return 0;
	}
	setTouchEnabled(true);
	//setAccelerometerEnabled(true);
	setKeypadEnabled(true);



	auto bg = Sprite::create("bgpics/mask.png");
	bg->setPosition(ccp(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	this->addChild(bg, 1000);


	MenuItemSprite *restart_item = MenuItemSprite::create(Sprite::createWithSpriteFrameName("retry_btn.png"),
		Sprite::createWithSpriteFrameName("retry_btn_selected.png"), CC_CALLBACK_0(PauseLayer::restart, this));
	restart_item->setPosition(ccp(VISIBLE_WIDTH / 4, VISIBLE_HEIGHT / 2));


	MenuItemSprite *resume_item = MenuItemSprite::create(CCSprite::createWithSpriteFrameName("resume_btn.png"),
		Sprite::createWithSpriteFrameName("resume_btn_selected.png"), CC_CALLBACK_0(PauseLayer::resume, this));
	resume_item->setPosition(ccp(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));


	MenuItemSprite *quit_item = MenuItemSprite::create(CCSprite::createWithSpriteFrameName("menu_btn.png"),
		CCSprite::createWithSpriteFrameName("menu_btn_selected.png"), CC_CALLBACK_0(PauseLayer::gotoMenu, this));
	quit_item->setPosition(ccp(VISIBLE_WIDTH / 4 * 3, VISIBLE_HEIGHT / 2));

	//resume_item->setPosition(restart_item->getPosition());
	Vector<MenuItem*> items;
	items.pushBack(quit_item);
	items.pushBack(resume_item);
	
	auto menu = Menu::createWithArray(items);
	menu->setPosition(ccp(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	this->addChild(menu, 1001);

	//schedule(schedule_selector(PauseLayer::updateAll));

	//		
	//	SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CCDirector::sharedDirector()->pause();

	return this;
}

void PauseLayer::updateAll(float dt)
{
	CCDirector::sharedDirector()->pause();
}
void PauseLayer::restart(CCNode * node)
{

	Audio::getInstance()->playButtonClick();
	removeFromParentAndCleanup(true);

	CCDirector::sharedDirector()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));

}
void PauseLayer::resume(CCNode * node)
{
	Audio::getInstance()->playButtonClick();
	removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->resume();


}
void PauseLayer::gotoMenu(CCNode * node)
{

	Audio::getInstance()->playButtonClick();
	removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->resume();
	Director::getInstance()->replaceScene(LevelSelectLayer::createScene());

}


PauseLayer::~PauseLayer()
{
	
}

