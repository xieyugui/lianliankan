#ifndef _LIANLIANKANX_OVERLAYER_H_
#define _LIANLIANKANX_OVERLAYER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


class OverLayer : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();
	static cocos2d::CCScene* scene(CCRenderTexture* sqr);

	CREATE_FUNC(OverLayer);
	//继续游戏  
	void menuContinueCallback();
	//选关 
	void menuLogin();
};

#endif // _HELLOWORLD_SCENE_H_
