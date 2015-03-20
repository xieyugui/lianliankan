#include "GameUtils.h"
#include "GameData.h"
#include "GameScene.h"
USING_NS_CC;


Vec2 GameUtils::pointOffsetCenter(float x, float y){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return Vec2(visibleSize.width / 2 + x, visibleSize.height / 2 + y);
}

float GameUtils::getXScaleRate(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return visibleSize.width / 960;
}

float GameUtils::getSpriteXScaleRate(Sprite* sprite){
	float spriteWidth = sprite->getContentSize().width;
	float scaleRate = VISIBLE_WIDTH / spriteWidth;
	if (scaleRate <= 1){
		return 1;
	}
	else{
		return scaleRate;
	}
}

float GameUtils::getSpriteYScaleRate(Sprite* sprite){
	float spriteHeight = sprite->getContentSize().height;
	float scaleRate = VISIBLE_HEIGHT / spriteHeight;
	if (scaleRate <= 1){
		return 1;
	}
	else{
		return scaleRate;
	}
}

float GameUtils::getPainSpriteXScaleRate(Sprite* sprite){
	float spriteWidth = sprite->getContentSize().width;
	float scaleRate = VISIBLE_WIDTH / spriteWidth;
	return scaleRate;
}

float GameUtils::getVisibleWidth(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return visibleSize.width;
}

float GameUtils::getVisibleHeight(){
	auto visibleSize = Director::getInstance()->getVisibleSize();
	return visibleSize.height;
}





Animation* GameUtils::getAnimationByKeyAndFrameName(const std::string& aniKey, const std::string& frameName,
	const int& frameCount, float delay){
	auto animCache = AnimationCache::getInstance();
	auto resultAnimation = animCache->getAnimation(aniKey);
	if (resultAnimation == nullptr){
		auto frameCache = SpriteFrameCache::getInstance();
		Vector<SpriteFrame*> animFrames(frameCount);
		char str[50] = { 0 };
		for (int i = 0; i < frameCount; i++){
			sprintf(str, frameName.c_str(), i);
			auto frame = frameCache->getSpriteFrameByName(str);
			CCASSERT(frame != nullptr, "frame is null!");
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames, delay);

		// Add an animation to the Cache
		AnimationCache::getInstance()->addAnimation(animation, aniKey);
		animFrames.clear();
		resultAnimation = animCache->getAnimation(aniKey);
		//log("no cache");
	}
	return resultAnimation;
}


Animation* GameUtils::getAnimationByKeyAndFileName(const std::string& aniKey, const std::string& fileName,


	const int& frameCount, float delay){
	auto animCache = AnimationCache::getInstance();
	auto resultAnimation = animCache->getAnimation(aniKey);
	if (resultAnimation == nullptr){
		auto cache = Director::getInstance()->getTextureCache();
		Vector<SpriteFrame*> animFrames(frameCount);
		char str[50] = { 0 };
		for (int i = 0; i < frameCount; i++){
			sprintf(str, fileName.c_str(), i);
			auto texture = cache->addImage(str);
			CCASSERT(texture != nullptr, "texture is null!");
			auto size = texture->getContentSize();
			auto rect = Rect(0, 0, size.width, size.height);
			auto frame = SpriteFrame::createWithTexture(texture, rect);
			animFrames.pushBack(frame);
		}
		auto animation = Animation::createWithSpriteFrames(animFrames, delay);

		// Add an animation to the Cache
		AnimationCache::getInstance()->addAnimation(animation, aniKey);
		animFrames.clear();
		resultAnimation = animCache->getAnimation(aniKey);
		//log("no cache");
	}
	return resultAnimation;
}

void GameUtils::startGameByLevel(int level){
	if (level != 0) {
		GameData::getInstance()->setChooseLevel(level);
	}
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, GameScene::create()));
}


