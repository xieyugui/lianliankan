#include "MenuLayer.h"

#include "GameUtils.h"
#include "GameData.h"
#include "LevelSelectLayer.h"
#include "MyJniHelper.h"

bool MenuLayer::init() {
	if (!Layer::init()) {
		return false;
	}
	clicked = false;
	this->setTouchEnabled(true);
	this->setKeypadEnabled(true);

	auto background = Sprite::create("title_bg.png");
	//float wBg = background->getContentSize().width;
	
	//Rect rect;
	//if (VISIBLE_WIDTH >= 680) {
	//	rect = Rect((wBg - VISIBLE_WIDTH)/2, 1, VISIBLE_WIDTH, VISIBLE_HEIGHT);   //ͼƬ�Ĵ�С
	//}else {
	//	rect = Rect((wBg - 680)/2, 1, 680, 960);   //ͼƬ�Ĵ�С
	//}

	//background->setTextureRect(rect);
	//background->setScaleX(GameUtils::getConScaleFactorX());
	//background->setScaleY(GameUtils::getConScaleFactorY());
	background->setScaleX(GetXScaleRate);
	background->setScaleY(GetYScaleRate);
	background->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	log("GameUtil1 %f", VISIBLE_WIDTH);
	this->addChild(background, -1);


	//开始按钮
	startBtn = MenuItemImage::create("btn_start.png", "btn_start.png", CC_CALLBACK_0(MenuLayer::startGame, this));
	startBtn->setScaleX(GetXScaleRate);
	startBtn->setScaleY(GetYScaleRate);
	//startBtn->setScaleX(GameUtils::getConScaleFactorX());
	//startBtn->setScaleY(GameUtils::getConScaleFactorY());
	startBtn->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));

	//more
	//moreBtn = MenuItemImage::create("btn_more.png", "btn_more.png",CC_CALLBACK_0(MenuLayer::menuMore, this));
	//moreBtn->setScaleX(GetXScaleRate);
	//moreBtn->setScaleY(GetYScaleRate);
	//moreBtn->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2 - moreBtn->boundingBox().size.height - 20));
	//log("morebtn = %f, = %f",moreBtn->getContentSize().height,moreBtn->boundingBox().size.height);

	// music
	MenuItemImage *_turnOn, *_turnOff;
	_turnOn = MenuItemImage::create(
		"music_p.png",
		"music_p.png");
	_turnOff = MenuItemImage::create(
		"music_c.png",
		"music_c.png");
	MenuItemToggle *toggleItem = MenuItemToggle::createWithCallback(CC_CALLBACK_0(MenuLayer::menuMusicCallback, this), _turnOn, _turnOff, NULL);
	toggleItem->setScaleX(GetXScaleRate);
	toggleItem->setScaleY(GetYScaleRate);
	toggleItem->setPosition(Vec2(VISIBLE_WIDTH - _turnOn->boundingBox().size.width / 2 - 10 , VISIBLE_HEIGHT - _turnOn->boundingBox().size.height / 2 - 10));
	if(GameData::getInstance()->getisPause())
		toggleItem->setSelectedIndex(1);

	pMenu = Menu::create(toggleItem,startBtn, NULL);
	pMenu->setPosition(Vec2::ZERO);

	this->addChild(pMenu,0);


	MyJniHelper::showBan(1);

		//对手机返回键的监听 
	auto listener = EventListenerKeyboard::create(); 
	//和回调函数绑定 
	listener->onKeyReleased = CC_CALLBACK_2(MenuLayer::onKeyReleased,this); 
	//添加到事件分发器中 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this); 

	return true;

}

void MenuLayer::menuMusicCallback()
{    
	GameData::getInstance()->playOrStopMusic();
	GameData::getInstance()->setisPause(( (GameData::getInstance()->getisPause() == false) ? true:false));
}

void MenuLayer::menuMore(){

}

void MenuLayer::menuQuit()
{
	Director::getInstance()->end();
}


void MenuLayer::startGame() {
	GameData::getInstance();
	Director::getInstance()->replaceScene(LevelSelectLayer::createScene());
	log("START!");
}

void MenuLayer::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent) 
{ 
	if (keyCode == EventKeyboard::KeyCode::KEY_MENU){
		if(clicked) {
			clicked= false;
			CCLog("doubleclick");
			Director::getInstance()->end();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
			#endif
		}else {
			//延时0.25s执行（注意在这0.25s的延时过程中clicked已经为true），
			//如果在这个过程中再次click，那么就执行上面的双击事件处理了
			//否则，那么就执行下面的回调函数了，处理单击事件
			scheduleOnce(schedule_selector(MenuLayer::doubleClickState),0.25f);
			clicked= true;
		}
	}

} 

void MenuLayer::doubleClickState(float tt)
{
    if(clicked) {
        clicked = false;
		CCLog("singleclick");
    }

}
