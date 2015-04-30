#ifndef _LIANLIANKAN_GAMELAYER_H_
#define _LIANLIANKAN_GAMELAYER_H_

#include "cocos2d.h"
#include "TopMenu.h"
#include "PauseLayer.h"
#include "MapNode.h"
USING_NS_CC;

class GameLayer :public Layer{
public:
	virtual bool init();
	virtual bool onTouchBegan(Touch *pTouch, Event *pEvent);
	virtual void onTouchEnded(Touch *pTouch, Event *pEvent);
	CREATE_FUNC(GameLayer);
	GameLayer();
	~GameLayer();

	CC_SYNTHESIZE(float,block_w,blockW);//缩放之后的大小
	CC_SYNTHESIZE(float,block_h,blockH);
	CC_SYNTHESIZE(float,bottom_h,bottomH);//距离底部高度
private:
	void initUI(void);

	void initData(void);


	cocos2d::String* imageFilename(int index);

	cocos2d::Point pointOfView(Vec2 point);


	bool isValiableNode(Vec2 point);

	bool isEmptyNode(Vec2 point);

	int indexFromPoint(Vec2 point);


	bool isSamePoints(Vec2 p1, Vec2 p2);


	void clearNode(Vec2 point);


	int match_direct(Vec2 a, Vec2 b);
	bool match_one_corner(Vec2 a, Vec2 b);
	bool match_two_corner(Vec2 a, Vec2 b);
	bool match(Vec2 a, Vec2 b);

	bool canClearTwo(Vec2 pointpre, Vec2 pointcurrent);

	void scaleAnimation(Sprite* sprite);
	void initImgSpriteSize();

	void gotoGameOver();
	void gotoNextLevel(int nexeLevel);

	void gameOverSettlement();
	void gameOverLayOut(float dt);

	void initFillBlock();

	void  clearAnimation(float dt);
	FiniteTimeAction* getSpecialEffectsAnimation();

	void addLinePoints(Vec2 a, Vec2 b,bool X);

	float getStartH();

	Vec2 prePoint; //前一个点坐标
	Vec2 location; //当前点坐标
	int preIndex;//前一个index
	int curIndex;//当前的index
	std::vector<Vec2> linePoints;




	//Array *mapArray;
	Vector<MapNode *> mapArray;

	int need_score;
	int current_score;

	Label* level;
	int fill_count;
	//PauseLayer *pauseLayer;

	TopMenu* menu;
	Sprite* block_top;

	float x_count;
	float y_count;
	int grid_count;
	int scope;


};


#endif
