//
//  PauseScene.h
//  MR_BOMB
//
//  Created by yunong on 1/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef _LIANLIANKANX_PAUSELAYER_H_
#define _LIANLIANKANX_PAUSELAYER_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion;


class PauseLayer : public cocos2d::CCLayer
{
public:
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	CREATE_FUNC(PauseLayer);
	CCSize size;
	void updateAll(float dt);
	void restart(CCNode * node);
	void setIsdialog(float dt);
	void resume(CCNode * node);

	void gotoMenu(CCNode * node);
	static void getAlertdiog();
	int lastState;

	~PauseLayer();
};

#endif // _HELLOWORLD_SCENE_H_
