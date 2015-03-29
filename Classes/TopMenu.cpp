#include "TopMenu.h"

#include "Audio.h"
#include "GameUtils.h"
#include "GameData.h"
#include "PauseLayer.h"

bool TopMenu::init(){
	if (!Node::init()){
		return false;
	}
	level = Label::create(String::create("Level: ")->_string + String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string, "Verdana-Bold", 30);
	level->setPosition(100, VISIBLE_HEIGHT - 50);
	this->addChild(level,1);

	auto startBtn = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_0(TopMenu::pauseGame, this));
	auto menu = Menu::create(startBtn, NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT - 50));
	this->addChild(menu,1);

	return true;
}


void TopMenu::refresh(){
	
	level->setString(String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string);
}

void TopMenu::pauseGame() {
	Audio::getInstance()->playButtonClick();
	//�õ����ڵĴ�С  
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCRenderTexture *renderTexture = CCRenderTexture::create(visibleSize.width, visibleSize.height);

	//������ǰ��������ӽڵ���Ϣ������renderTexture�С�  
	//�������ƽ�ͼ��  
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//����Ϸ������ͣ��ѹ�볡����ջ�����л���GamePause����  
	CCDirector::sharedDirector()->pushScene(PauseLayer::scene(renderTexture));
}
