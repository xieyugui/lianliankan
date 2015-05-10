#include "TopMenu.h"

#include "Audio.h"
#include "GameUtils.h"
#include "GameData.h"
#include "PauseLayer.h"
#include "OverLayer.h"

bool TopMenu::init(){
	if (!Node::init()){
		return false;
	}

	auto header_bg = Sprite::create("header_bg.png");
	header_bg->setScaleX(GetXScaleRate);
	header_bg->setScaleY(GetYScaleRate);
	header_bg->setPosition(VISIBLE_WIDTH/2,VISIBLE_HEIGHT-header_bg->boundingBox().size.height/2);
	this->addChild(header_bg,1);

	//block_h = block_top->boundingBox().size.height;

	float topH = VISIBLE_HEIGHT-header_bg->boundingBox().size.height/2;


	auto levelSp = Sprite::create("header_level.png");
	levelSp->setScaleX(GetXScaleRate);
	levelSp->setScaleY(GetYScaleRate);
	levelSp->setPosition(level_space,VISIBLE_HEIGHT-header_bg->boundingBox().size.height/2);
	this->addChild(levelSp,2);


	auto level = Label::create(String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string, "Verdana-Bold",45*GetXScaleRate,Size(85*GetXScaleRate,65*GetYScaleRate),TextHAlignment::CENTER,TextVAlignment::TOP);
	//auto level = Label::create(String::createWithFormat("%f", VISIBLE_HEIGHT)->_string, "Verdana-Bold",45*GetXScaleRate,Size(85*GetXScaleRate,65*GetYScaleRate),TextHAlignment::CENTER,TextVAlignment::TOP);	
	level->setPosition(206 * GetXScaleRate+ 85*GetXScaleRate/2, topH);
	this->addChild(level,2);

	auto startBtn = MenuItemImage::create("btn_pause.png", "btn_pause.png", CC_CALLBACK_0(TopMenu::pauseGame, this));
	startBtn->setScaleX(GetXScaleRate);
	startBtn->setScaleY(GetYScaleRate);
	startBtn->setPosition(Vec2(VISIBLE_WIDTH - startBtn->boundingBox().size.width/2 - level_space,topH));

	auto promptBtn = MenuItemImage::create("btn_pause.png", "btn_pause.png", CC_CALLBACK_0(TopMenu::promptGame, this));
	promptBtn->setScaleX(GetXScaleRate);
	promptBtn->setScaleY(GetYScaleRate);
	promptBtn->setPosition(Vec2(VISIBLE_WIDTH - promptBtn->boundingBox().size.width/2 - startBtn->boundingBox().size.width-level_space *2,topH));



	auto menu = Menu::create(promptBtn,startBtn, NULL);
	menu->setPosition(Vec2::ZERO);
	//menu->alignItemsVertically();
	this->addChild(menu,2);

	return true;
}


void TopMenu::refresh(){
	
	//level->setString(String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string);
}

void TopMenu::pauseGame() {
	Audio::getInstance()->playButtonClick();
	
	CCSize visibleSize = CCDirector::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(VISIBLE_WIDTH, VISIBLE_HEIGHT);
 
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//暂停页面
	CCDirector::getInstance()->pushScene(PauseLayer::scene(renderTexture));
}

//结束版面
void TopMenu::overGame() {

	CCSize visibleSize = CCDirector::getInstance()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(VISIBLE_WIDTH, VISIBLE_HEIGHT);
 
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//结束页面
	CCDirector::getInstance()->pushScene(OverLayer::scene(renderTexture));
}

void TopMenu::promptGame() 
{

}

