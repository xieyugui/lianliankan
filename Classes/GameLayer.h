#ifndef _LIANLIANKAN_GAMELAYER_H_
#define _LIANLIANKAN_GAMELAYER_H_

#include "cocos2d.h"
#include "TopMenu.h"
#include "PauseLayer.h"
USING_NS_CC;

class GameLayer :public Layer{
public:
	virtual bool init();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	CREATE_FUNC(GameLayer);
	GameLayer();
	~GameLayer();
private:
	void initUI(void);

	void initData(void);

	//void initTopMenuUI();

	cocos2d::String* imageFilename(int index);

	cocos2d::Point pointOfView(Vec2 point);


	bool isValiableNode(Vec2 point);

	bool isEmptyNode(Vec2 point);

	int indexFromPoint(Vec2 point);


	bool isSamePoints(Vec2 p1, Vec2 p2);


	void clearNode(Vec2 point);


	bool match_direct(Vec2 a, Vec2 b);
	bool match_one_corner(Vec2 a, Vec2 b);
	bool match_two_corner(Vec2 a, Vec2 b);
	bool match(Vec2 a, Vec2 b);

	bool canClearTwo(Vec2 pointpre, Vec2 pointcurrent);

	void scaleAnimation(Sprite* sprite);
	void initImgSpriteSize();

	void gotoGameOver();
	void gotoNextLevel(int nexeLevel);

	void gameOverSettlement();

	void pauseGame();

	//前一个点坐标
	Vec2 prePoint;

	Array *mapArray;


	int total_x;
	int total_y;
	int need_score;
	int current_score;

	float img_w;
	float img_h;

	Label* level;
	//PauseLayer *pauseLayer;

	TopMenu* menu;


};


#endif
