//
//  PauseScene.mm
//  MR_BOMB
//
//  Created by yunong on 1/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "PauseLayer.h"
#include "SimpleAudioEngine.h"

#include "AudioProxy.h"
#include "MenuLayer.h"
#include "GameUtils.h"
#include "LevelSelectLayer.h"
#include "GameScene.h"

USING_NS_CC;

//����һ��CCrenderTexture   
//�൱��һ���������е���Ϸ�Ľ�ͼ��Ϊ�����ͣ�Ի���ı���   
//�����Ϳ��������ǶԻ�������Ϸ����֮�ϣ�һ����Ϸ���ж���������д�ġ�  
CCScene* PauseLayer::scene(CCRenderTexture* sqr)
{
	CCScene *scene = CCScene::create();
	PauseLayer *layer = PauseLayer::create();
	scene->addChild(layer, 1);//����Ϸ������棬���ǻ�Ҫ��������Ű�ť  


	//���Ӳ��֣�ʹ��Game�����н�ͼ��sqr����ͼƬ����Sprite  
	//����Sprite��ӵ�GamePause��������  
	//�õ����ڵĴ�С  
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCSprite *back_spr = CCSprite::createWithTexture(sqr->getSprite()->getTexture());
	back_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�  
	back_spr->setFlipY(true);            //��ת����ΪUI�����OpenGL���겻ͬ  
	back_spr->setColor(Color3B::GRAY); //ͼƬ��ɫ���ɫ  
	scene->addChild(back_spr);


	//�����Ϸ��ͣ����Сͼ�������Ű�ť  
	CCSprite *back_small_spr = CCSprite::create("back_pause.png");
	back_small_spr->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2)); //����λ��,������������λ�á�  
	scene->addChild(back_small_spr);


	return scene;
}

bool PauseLayer::init()
{

	if (!CCLayer::init())
	{
		return false;
	}
	//�õ����ڵĴ�С  
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	//ԭ������  
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

	//������Ϸ��ť  
	CCMenuItemImage *pContinueItem = CCMenuItemImage::create(
		"pause_continue.png",
		"pause_continue.png",
		CC_CALLBACK_0(PauseLayer::menuContinueCallback,this));

	pContinueItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 + 30));

	//���¿�ʼ��Ϸ��ť  
	CCMenuItemImage *pRestartItem = CCMenuItemImage::create(
		"pause_restart.png",
		"pause_restart.png",
		CC_CALLBACK_0(PauseLayer::menuRestart, this));

	pRestartItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 20));

	//��������  
	CCMenuItemImage *pLoginItem = CCMenuItemImage::create(
		"pause_login.png",
		"pause_login.png",
		CC_CALLBACK_0(PauseLayer::menuLogin, this));

	pLoginItem->setPosition(ccp(visibleSize.width / 2, visibleSize.height / 2 - 70));


	// create menu, it's an autorelease object  
	CCMenu* pMenu = CCMenu::create(pContinueItem, pRestartItem, pLoginItem, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1000);

	CCDirector::sharedDirector()->pause();

	return true;
}
void PauseLayer::menuContinueCallback()
{
	
	AudioProxy::getInstance()->playButtonClick();
	CCDirector::sharedDirector()->popScene();
	//removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->resume();

}

//���¿�ʼ��Ϸ  
void  PauseLayer::menuRestart()
{
	AudioProxy::getInstance()->playButtonClick();
	//removeFromParentAndCleanup(true);
	CCDirector::sharedDirector()->popScene();
	CCDirector::sharedDirector()->resume();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));
}
//��������  
void  PauseLayer::menuLogin()
{
	AudioProxy::getInstance()->playButtonClick();
	CCDirector::sharedDirector()->popScene();
	//removeFromParentAndCleanup(true);
	Director::sharedDirector()->resume();
	Director::getInstance()->replaceScene(LevelSelectLayer::createScene());
}