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


	auto normalSprite = Sprite::create(ret->getFrameNameByType(ret->_type));
	//normalSprite->setScale(GameData::getInstance()->getlevelSacle());

	auto selectedSprite = Sprite::create(ret->getFrameNameByType(ret->_type));
	//selectedSprite->setScale(GameData::getInstance()->getlevelSacle());
	auto disabledSprite = Sprite::create(ret->getFrameNameByType(ret->_type));
	//disabledSprite->setScale(GameData::getInstance()->getlevelSacle());
	ret->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, callback);
	ret->extraInit();
	ret->autorelease();
	ret->setScale(GameData::getInstance()->getlevelSacle());
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
			//valueLabel = Label::createWithBMFont("fonts/blueLevel.fnt", levelBuffer);
			valueLabel =  Label::createWithTTF(levelBuffer, "fonts/Marker Felt.ttf", 36);

		}
		else if (_type == kNotPassYet){
			valueLabel =  Label::createWithTTF(levelBuffer, "fonts/Marker Felt.ttf", 36);
			//valueLabel = Label::createWithBMFont("fonts/whiteLevel.fnt", levelBuffer);
		}
		//valueLabel->setScale(GetXScaleRate);
		
		valueLabel->setPosition(this->boundingBox().size.width /2, this->boundingBox().size.height /2);
		this->addChild(valueLabel);

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
		return "lockLevel.png";
	}
}