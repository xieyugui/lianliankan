#ifndef __LIANLIANKANX__GMEUTILS__
#define __LIANLIANKANX__GMEUTILS__

#include "cocos2d.h"
USING_NS_CC;

class GameUtils{
public:
	static cocos2d::Vec2 pointOffsetCenter(float x, float y);
	static float getXScaleRate();
	static float getYScaleRate();
	static float getSpriteXScaleRate(Sprite* sprite);
	static float getSpriteYScaleRate(Sprite* sprite);
	static float getPainSpriteXScaleRate(Sprite* sprite);
	static float getVisibleWidth();
	static float getVisibleHeight();
	static float getLevelScale(Sprite* sprite);
	static float getBlockScale(Sprite* sprite);
	static float getPageScale(Sprite* page,Sprite* sprite);
	static float getSpaceSizeRate(int spCount);

	static Animation* getAnimationByKeyAndFrameName(const std::string& aniKey, const std::string& frameName, const int& frameCount, float delay);
	static Animation* getAnimationByKeyAndFileName(const std::string& aniKey, const std::string& fileName, const int& frameCount, float delay);
	static void startGameByLevel(int level);
};


#define GameCCPointC(x,y) GameUtils::pointOffsetCenter(x,y)
#define GetXScaleRate GameUtils::getXScaleRate()
#define GetYScaleRate GameUtils::getYScaleRate()
#define GetSpriteXScaleRate(sprite) GameUtils::getSpriteXScaleRate(sprite)
#define GetSpriteYScaleRate(sprite) GameUtils::getSpriteYScaleRate(sprite)
#define GetPainSpriteXScaleRate(sprite) GameUtils::getPainSpriteXScaleRate(sprite)
#define VISIBLE_WIDTH GameUtils::getVisibleWidth()
#define VISIBLE_HEIGHT GameUtils::getVisibleHeight()
#define GetPageScaleRate(page,sprite) GameUtils::getPageScale(Sprite* page,Sprite* sprite)
#define GetSpaceSize(spCount) GameUtils::getSpaceSizeRate(int spCount)

#endif;