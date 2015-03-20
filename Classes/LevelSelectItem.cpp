#include "LevelSelectItem.h"
#include "HelloWorldScene.h"
#include "GameUtils.h"
#include "GameData.h"
#include "GameScene.h"

LevelSelectItem::LevelSelectItem(int level) :_level(level), _type(kLockLevel){//初始化等级，以及该按钮的属性
	int g_passLevelCount = GameData::getInstance()->getCurLevel();
	if (level > (g_passLevelCount + 1)){
		this->setEnabled(false);//设置按钮是否可用
		_type = kLockLevel;
	}
	else if (level == (g_passLevelCount + 1)){
		this->setEnabled(true);
		_type = kNotPassYet;
	}
	else if (level < (g_passLevelCount + 1)){
		this->setEnabled(true);
		_type = kAlreadyPass;
	}
}


LevelSelectItem* LevelSelectItem::create(int level){
	LevelSelectItem *ret = new LevelSelectItem(level);//创建
	auto callback = CC_CALLBACK_1(LevelSelectItem::selectCallBack, ret);


	auto normalSprite = Sprite::createWithSpriteFrameName(ret->getFrameNameByType(ret->_type));
	auto selectedSprite = Sprite::createWithSpriteFrameName(ret->getFrameNameByType(ret->_type));
	auto disabledSprite = Sprite::createWithSpriteFrameName(ret->getFrameNameByType(ret->_type));
	ret->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
	ret->extraInit();
	ret->autorelease();
	return ret;
}

void LevelSelectItem::selectCallBack(Ref* sender){
	if (_type != kLockLevel){
		log("level item %d", _level);
		GameData::getInstance()->setChooseLevel(_level);
		//GameUtils::startGameByLevel(_level);
		//auto scene = HelloWorld::createScene();
		GameUtils::startGameByLevel(_level);
		//Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));
		//创建游戏
	}
}

void LevelSelectItem::extraInit(){


	if (_type != kLockLevel){
		char levelBuffer[20] = { 0 };
		sprintf(levelBuffer, "%d", _level);
		Label* valueLabel = nullptr;
		if (_type == kAlreadyPass){
			valueLabel = Label::createWithBMFont("fonts/blueLevel.fnt", levelBuffer);

		}
		else if (_type == kNotPassYet){
			valueLabel = Label::createWithBMFont("fonts/whiteLevel.fnt", levelBuffer);
		}
		this->addChild(valueLabel);
		auto size = this->getContentSize();
		valueLabel->setPosition(size.width * 0.5, size.height * 0.5);

	}


}

std::string LevelSelectItem::getFrameNameByType(const LevelItemType& type)
{
	switch (type) {
	case kLockLevel:
	{
		return "lockLevel.png";
	}
		break;
	case kNotPassYet:
	{
		return "notPassYet.png";
	}
		break;
	case kAlreadyPass:
	{
		return "alreadyPass.png";
	}
		break;
	default:
		break;
	}
}