//
//  PauseScene.mm
//  MR_BOMB
//
//  Created by yunong on 1/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "PauseLayer.h"
#include "SimpleAudioEngine.h"

#include "Audio.h"
#include "MenuLayer.h"
#include "GameUtils.h"
#include "LevelSelectLayer.h"
#include "GameScene.h"

USING_NS_CC;

//传入一个CCrenderTexture   
//相当于一个正在运行的游戏的截图作为这个暂停对话框的背景   
//这样就看起来像是对话框在游戏界面之上，一般游戏当中都是这样子写的。  
CCScene* PauseLayer::scene(CCRenderTexture* sqr)
{
	CCScene *scene = CCScene::create();
	PauseLayer *layer = PauseLayer::create();
	scene->addChild(layer, 1); 

	//增加部分：使用Game界面中截图的sqr纹理图片创建Sprite  
    //并将Sprite添加到GamePause场景层中  
    //得到窗口的大小  
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2)); //放置位置,这个相对于中心位置。  
	back_spr->setFlipY(true);           //翻转，因为UI坐标和OpenGL坐标不同  
	back_spr->setColor(Color3B::GRAY); //图片颜色变灰色  
	scene->addChild(back_spr);


	CCSprite *back_small_spr = CCSprite::create("back_pause.png");
	back_small_spr->setPosition(ccp(VISIBLE_WIDTH /2 , VISIBLE_HEIGHT / 2)); 
	scene->addChild(back_small_spr);


	return scene;
}

bool PauseLayer::init()
{

	if (!CCLayer::init())
	{
		return false;
	}
	
	CCPoint origin = CCDirector::getInstance()->getVisibleOrigin();

	
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"pause_continue.png",
		"pause_continue.png",
		CC_CALLBACK_0(PauseLayer::menuContinueCallback,this));

	pContinueItem->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 + 30));

	
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
		"pause_restart.png",
		"pause_restart.png",
		CC_CALLBACK_0(PauseLayer::menuRestart, this));

	pRestartItem->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 - 20));


	CCMenuItemImage *pLoginItem = CCMenuItemImage::create(
		"pause_login.png",
		"pause_login.png",
		CC_CALLBACK_0(PauseLayer::menuLogin, this));

	pLoginItem->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 - 70));


	// create menu, it's an autorelease object  
	CCMenu* pMenu = CCMenu::create(pContinueItem, pRestartItem, pLoginItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1000);

	CCDirector::sharedDirector()->pause();

	return true;
}
void PauseLayer::menuContinueCallback()
{
	
	Audio::getInstance()->playButtonClick();
	CCDirector::sharedDirector()->popScene();
	//removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->resume();

}


void  PauseLayer::menuRestart()
{
	Audio::getInstance()->playButtonClick();
	//removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->popScene();
	CCDirector::sharedDirector()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));
}

void  PauseLayer::menuLogin()
{
	Audio::getInstance()->playButtonClick();
	CCDirector::sharedDirector()->popScene();
	//removeFromParentAndCleanup(true);
	Director::sharedDirector()->resume();
	Director::getInstance()->replaceScene(LevelSelectLayer::createScene());
}
