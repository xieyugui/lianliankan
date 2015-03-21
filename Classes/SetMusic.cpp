#include "SetMusic.h"
#include "MenuScene.h"
#include "SimpleAudioEngine.h"
#include <string>
USING_NS_CC;
using namespace CocosDenshion;
using namespace std;


SetMusic::SetMusic()
{
	// 默认的音乐和音效都是开着
	bMusic = true;
	bSoundEffect = true;
}

SetMusic::~SetMusic()
{

}

bool SetMusic::init()
{
	Sprite *pBg = Sprite::create("background.png");
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	pBg->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(pBg, 0);

	Sprite *pSetBg = Sprite::create("Set_Music.png");
	pSetBg->setAnchorPoint(ccp(129.0 / 248, 71.0 / 132));
	pSetBg->setPosition(ccp(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(pSetBg, 1);

	MenuItemImage *pBack = MenuItemImage::create("backA.png", "backB.png",
		CC_CALLBACK_0(SetMusic::menuBackMainMenu, this));
	pBack->setPosition(ccp(origin.x + 20, origin.y + visibleSize.height - 20));
	Menu *pMenu = Menu::create(pBack, NULL);
	pMenu->setAnchorPoint(Vec2::ZERO);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 2);

	this->initSwitch();

	return true;
}

void SetMusic::menuBackMainMenu()
{
	Scene *pScene = Scene::create();
	pScene->addChild(MenuScene::create());
	Director::getInstance()->replaceScene(pScene);
}

void SetMusic::initSwitch()
{
	Point origin = Director::getInstance()->getVisibleOrigin();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	pMusicOn = SpriteFrame::create("music_on.png", CCRectMake(0, 0, 70, 63));
	pMusicOn->retain();
	pMusicOff = SpriteFrame::create("music_off.png", CCRectMake(0, 0, 70, 63));
	pMusicOff->retain();
	pEffectOn = SpriteFrame::create("sound_effect_on.png", CCRectMake(0, 0, 70, 63));
	pEffectOn->retain();
	pEffectOff = SpriteFrame::create("sound_effect_off.png", CCRectMake(0, 0, 70, 63));
	pEffectOff->retain();

	pMusic = Sprite::createWithSpriteFrame(pMusicOn);
	pMusic->setPosition(ccp(origin.x + visibleSize.width / 2 + 80, origin.y + visibleSize.height / 2 - 40));
	this->addChild(pMusic, 3);

	pSoundEffect = Sprite::createWithSpriteFrame(pEffectOn);
	pSoundEffect->setPosition(ccp(origin.x + visibleSize.width / 2 + 80, origin.y + visibleSize.height / 2 + 40));
	this->addChild(pSoundEffect, 3);

	MenuItemImage *pMusicMenu = MenuItemImage::create("switchBg.png", "switchBg.png",
		CC_CALLBACK_0(SetMusic::menuMusic, this));
	pMusicMenu->setPosition(ccp(origin.x + visibleSize.width / 2 + 80, origin.y + visibleSize.height / 2 - 40));
	MenuItemImage *pEffectMenu = MenuItemImage::create("switchBg.png", "switchBg.png",
		CC_CALLBACK_0(SetMusic::menuEffect, this));
	pEffectMenu->setPosition(ccp(origin.x + visibleSize.width / 2 + 80, origin.y + visibleSize.height / 2 + 40));

	Menu *pMenu = Menu::create(pMusicMenu, pEffectMenu, NULL);
	pMenu->setAnchorPoint(Vec2::ZERO);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu, 1);
}

void SetMusic::menuMusic()
{
	if (bMusic)
	{
		bMusic = false;
		pMusic->setDisplayFrame(pMusicOff);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
		UserDefault::sharedUserDefault()->setStringForKey("Music", "off");
	}
	else
	{
		bMusic = true;
		pMusic->setDisplayFrame(pMusicOn);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
		UserDefault::sharedUserDefault()->setStringForKey("Music", "on");
	}
}

void SetMusic::menuEffect()
{
	if (bSoundEffect)
	{
		bSoundEffect = false;
		pSoundEffect->setDisplayFrame(pEffectOff);
		SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
		UserDefault::sharedUserDefault()->setStringForKey("SoundEffect", "off");
	}
	else
	{
		bSoundEffect = true;
		pSoundEffect->setDisplayFrame(pEffectOn);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
		UserDefault::sharedUserDefault()->setStringForKey("SoundEffect", "on");
	}
}

void SetMusic::onEnter()
{
	Layer::onEnter();

	string str = UserDefault::sharedUserDefault()->getStringForKey("Music");
	if (str == "on")
	{
		bMusic = true;
		pMusic->setDisplayFrame(pMusicOn);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(1.0f);
	}
	else if (str == "off")
	{
		bMusic = false;
		pMusic->setDisplayFrame(pMusicOff);
		SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.0f);
	}

	str = UserDefault::sharedUserDefault()->getStringForKey("SoundEffect");
	if (str == "on")
	{
		bSoundEffect = true;
		pSoundEffect->setDisplayFrame(pEffectOn);
		SimpleAudioEngine::getInstance()->setEffectsVolume(1.0f);
	}
	else if (str == "off")
	{
		bSoundEffect = false;
		pSoundEffect->setDisplayFrame(pEffectOff);
		SimpleAudioEngine::getInstance()->setEffectsVolume(0.0f);
	}
}

void SetMusic::onExit()
{


	Layer::onExit();
}

