#include "GameLayer.h"
#include "GameData.h"
#include "GameUtils.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"

#include "Audio.h"
#include "FloatWord.h"
#include "MenuScene.h"
#include "LevelSelectLayer.h"
#include "MapNode.h"
#include "PauseLayer.h"
#include "OverLayer.h"

#include <algorithm>
using std::random_shuffle;

USING_NS_CC_EXT;
USING_NS_CC;

GameLayer::GameLayer()
{
	prePoint = Vec2(-1,-1);
	current_score = 0;
	fill_count = 0;
	preIndex = 0;
	curIndex = 0;
}

GameLayer::~GameLayer()
{
	//CC_SAFE_RELEASE(mapArray);//CC_SAFE_DELETE_ARRAY(mapArray);
	//mapArray->release();
	mapArray.clear();
	//mapArray = NULL;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{

	if (!Layer::init()) {
		return false;
	}

	this->initData();


	this->initUI();

	return true;

}




void GameLayer::initData()
{
	//GameData::getInstance()->getLevelXY( need_score,0);
	//log("initData %d", need_score);
	//this->initImgSpriteSize();
	//mapArray = Array::create();
	//auto levelArr = GameData::getInstance()->getLevelData(0);
	//mapArray->retain();
	GameData::getInstance()->getLevelData(0,x_count,y_count,grid_count,scope);
	auto block = Sprite::create("block/block_top.png");
	GameData::getInstance()->setblockScale(GameUtils::getBlockScale(block,x_count));

	this->initFillBlock();
	mapArray = Vector<MapNode*>(x_count*y_count);
	for (int index = 0; index < x_count*y_count; index++) {
		MapNode *node = new MapNode();
		node->autorelease();
		node->imgid = 0;

		MapNode *node1 = new MapNode();
		node1->autorelease();
		node1->imgid = 0;

		if(index < grid_count*2) {
			srand( (unsigned)time( NULL ) + index*rand()%1000 );
			node->imgid = rand() % scope + 1;
			node1->imgid = node->imgid;
			log("initData imgid = %d", node->imgid);
		}
		mapArray.pushBack(node);
		mapArray.pushBack(node1);
		index++;
		log("initData index= %d", index);
	}

	//SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("icon1.plist");
	//SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common.plist");

	//添加touch监听
	//	Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);//触摸开始
	//touchListener->onTouchMoved = CC_CALLBACK_2(MapLayer::onTouchMoved, this);//触摸移动
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);//触摸结束
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//注册分发器

	prePoint = CCPointMake(-1, -1);


}

void GameLayer::initImgSpriteSize()
{
	//img_w = this->getContentSize().width / total_x;
	//img_h = this->getContentSize().height / total_y;
	//log("image all w %f", img_w);
	//log("image  all h %f", img_h);

}


void GameLayer::initUI()
{
	auto gameBg = Sprite::create("bg.png");
	//float wBg = gameBg->getContentSize().width;
	//Rect rect;
	//if (VISIBLE_WIDTH >= size_width) {
	//	rect = Rect((wBg - VISIBLE_WIDTH)/2, 1, VISIBLE_WIDTH, VISIBLE_HEIGHT);   //图片的大小
	//}else {
	//	rect = Rect((wBg - size_width)/2, 1, size_width, size_height);   //图片的大小
	//}

	//gameBg->setTextureRect(rect);
	gameBg->setScaleX(GetXScaleRate);
	gameBg->setScaleY(GetYScaleRate);
	gameBg->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	this->addChild(gameBg, -1);

	//top Menu
	menu = TopMenu::create();
	this->addChild(menu);

	srand( (unsigned)time(NULL));
	random_shuffle(mapArray.begin(),mapArray.end());
	block_top = Sprite::create("block/block_top.png");
	block_top->setScale(GameData::getInstance()->getblockScale());
	block_w = block_top->boundingBox().size.width;
	block_h = block_top->boundingBox().size.height;
	int block_index = 0;
	int wIndex = 0;
	for (Vector<MapNode*>::const_iterator it = mapArray.begin(); it != mapArray.end(); ++it)  {
		MapNode* mapNode = *it;
		Sprite* sprite;
		auto* topSprite = Sprite::create("block/block_top.png");
		topSprite->setVisible(false);
		if(mapNode->imgid) {
			sprite = Sprite::create(String::createWithFormat("block/block_%d.png", mapNode->imgid)->getCString());
			
			sprite->setName(String::createWithFormat("block_%d.png", mapNode->imgid)->getCString());
		}else {
			sprite = Sprite::create("block/block_touming.png");
			//sprite->setName("block_touming.png");
		}
		sprite->setScale(GameData::getInstance()->getblockScale());
		topSprite->setScale(GameData::getInstance()->getblockScale());
		wIndex = block_index;
		if (block_index >= x_count) {
				wIndex = block_index - int(block_index / x_count) * x_count;
				log("windex = %d,= %d",wIndex,int(block_index / x_count));
		}
			
		sprite->setPosition(ccp((block_w / 2) + block_w * wIndex+level_space, (block_h / 2) + int(block_index / x_count)*block_h+banner_height));
		topSprite->setPosition(ccp((block_w / 2) + block_w * wIndex+level_space, (block_h / 2) + int(block_index / x_count)*block_h+banner_height));
		log("init = %f, = %f",(block_w / 2) + block_w * wIndex+level_space,(block_h / 2) + int(block_index / x_count)*block_h);
		this->addChild(sprite, 2, TAG_START_SPRITE + block_index);
		this->addChild(topSprite, 3, TAG_START_SPRITE *2 + block_index);
		block_index++;
	}
}

//根据当前等级生成随机数
void GameLayer::initFillBlock() {
	//计算要填充的个数，根据等级
	//int level = GameData::getInstance()->getChooseLevel();
	//fill_count = 4+(level/10)*2;
	need_score = grid_count;
}



//屏幕坐标转换成地图坐标
Vec2 GameLayer::pointOfView(Vec2 point)
{

	int x = -1;
	int y = -1;
	if (point.x > 0 && point.x < (x_count * block_w+level_space))
		x = (point.x-level_space) / (block_w);
	if (point.y > 0 && point.y < y_count * block_h)
		y = (point.y) / (block_h );
	log("debug %f,%f",point.x,point.y);
	return Vec2(x, y);
}


//是否在有效范围内
bool GameLayer::isValiableNode(Vec2 point)
{
	return point.x >= 0 && point.x < x_count && point.y >= 0 && point.y < y_count;
}

//是否是空的坐标点
bool GameLayer::isEmptyNode(Vec2 point)
{
	int index = this->indexFromPoint(point);
	if (index >= mapArray.size()) {
		return true;
	}
	MapNode *node = (MapNode *)mapArray.at(index);
	log("isEmptyNode %d, index= %d", node->imgid,index);
	return (node->imgid == 0);
}

//每个sprite的index
int GameLayer::indexFromPoint(Vec2 point)
{
	return point.y * x_count + point.x;

}


//是否是相同的点
bool GameLayer::isSamePoints(Vec2 p1, Vec2 p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}


//清除
void GameLayer::clearNode(Vec2 point)
{
	int index = this->indexFromPoint(point);

	MapNode *node = (MapNode *)mapArray.at(index);

	node->imgid = 0;
}

//判断两个是否可以消除
bool GameLayer::canClearTwo(Vec2 pointpre, Vec2 pointcurrent)
{
	bool bMatch = false;
	int pre = this->indexFromPoint(pointpre);
	int current = this->indexFromPoint(pointcurrent);
	int p = ((MapNode *)(mapArray.at(pre)))->imgid;
	int c = ((MapNode *)(mapArray.at(current)))->imgid;

	if (p == c && this->match(pointcurrent, pointpre))
	{
		bMatch = true;
	}

	return bMatch;
}


//放大缩小动画
void GameLayer::scaleAnimation(cocos2d::Sprite* sprite)
{

	auto *ac1 = ScaleTo::create(0.07f, 1.0);
	auto *ac2 = ScaleTo::create(0.07f, 0.9);
	auto *ac3 = ScaleTo::create(0.07f, 1.0);

	auto *seq = Sequence::create(ac1, ac2, ac3, NULL);
	sprite->runAction(seq);

}

//
bool GameLayer::onTouchBegan(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{

	auto location = Director::sharedDirector()->convertToGL(pTouch->getLocationInView());

	//在这个层区域内返回true
	if (this->boundingBox().containsPoint(location))
	{

		return true;


	}

	//否则返回false,阻止接下来的touch函数
	return false;
}


//
void GameLayer::onTouchEnded(cocos2d::Touch *pTouch, cocos2d::Event *pEvent)
{


	auto location = Director::sharedDirector()->convertToGL(pTouch->getLocationInView());
	location = this->convertToNodeSpace(location);

	//location=CCPointMake(location.x, location.y-40);

	location = this->pointOfView(location);


	CCLOG("x:%f", location.x);
	CCLOG("y:%f", location.y);

	if (this->isValiableNode(location) == false)
	{
		return;
	}

	if (this->isEmptyNode(location))
	{
		return;
	}



	//SimpleAudioEngine::sharedEngine()->playEffect("12.wav");
	Audio::getInstance()->playSprite();
	

	if (prePoint.x == -1 && prePoint.y == -1) {
		auto tmcurrent = (Sprite *)this->getChildByTag(TAG_START_SPRITE*2 + this->indexFromPoint(location));
		tmcurrent->setVisible(true);
		prePoint = location;
		return ;
	}

	if (this->isSamePoints(location, prePoint))
	{
		return;
	}

	//点击当前精灵
	
	auto spritecurrent = (Sprite *)this->getChildByTag(TAG_START_SPRITE + this->indexFromPoint(location));
	auto tmcurrent = (Sprite *)this->getChildByTag(TAG_START_SPRITE*2 + this->indexFromPoint(location));
	tmcurrent->setVisible(true);
	//spritecurrent->setScale(1.1);


	if (this->isValiableNode(prePoint) && !this->isEmptyNode(prePoint))
	{
		CCLOG("%d", this->indexFromPoint(location));
		//前一个
		
		auto spritepre = (Sprite *)this->getChildByTag(TAG_START_SPRITE + this->indexFromPoint(prePoint));
		auto tmpre = (Sprite *)this->getChildByTag(TAG_START_SPRITE*2 + this->indexFromPoint(prePoint));
		//auto *spriteLine = (Sprite *)this->getChildByTag(TAG_START_SPRITE * 2 + this->indexFromPoint(prePoint));//by xie
		//tmpre->setVisible(true);
		linePoints.clear();
		if (this->canClearTwo(prePoint, location))
		{
			curIndex = this->indexFromPoint(location);
			preIndex = this->indexFromPoint(prePoint);
			Audio::getInstance()->playEliminate();
			this->clearNode(location);
			this->clearNode(prePoint);
			prePoint = Vec2(-1,-1);
			this->scheduleOnce(schedule_selector(GameLayer::clearAnimation),0.1f);

		}
		else
		{
			tmpre->setVisible(false);
			//spritepre->setScale(0.9);
			//this->scaleAnimation(spritepre);
			//spriteLine->setVisible(true);//by xie

		}

	}

	prePoint = location;

}

void GameLayer::clearAnimation(float dt)
{
	auto spritecurrent = (Sprite *)this->getChildByTag(TAG_START_SPRITE + curIndex);
	auto tmcurrent = (Sprite *)this->getChildByTag(TAG_START_SPRITE*2 + curIndex);
	auto spritepre = (Sprite *)this->getChildByTag(TAG_START_SPRITE + preIndex);
	auto tmpre = (Sprite *)this->getChildByTag(TAG_START_SPRITE*2 + preIndex);
	std::string fileName = spritecurrent->getName();

	tmcurrent->setVisible(false);
	tmpre->setVisible(false);

	//spritecurrent->setVisible(false);
	spritecurrent->runAction(this->getSpecialEffectsAnimation());
	//spritepre->setVisible(false);
	spritepre->runAction(this->getSpecialEffectsAnimation());

	for (int i = 0; i < linePoints.size(); i++) {
				
		auto point = linePoints[i];
		auto sprite = Sprite::create("block/"+fileName);
		sprite->setScale(GameData::getInstance()->getblockScale());
		sprite->setPosition(ccp((block_w / 2) + block_w * point.x+level_space, (block_h / 2) + point.y*block_h));
		this->addChild(sprite, 3, TAG_START_SPRITE*4 + i);
		sprite->runAction(this->getSpecialEffectsAnimation());
	}
	linePoints.clear();

	

	preIndex = 0;
	curIndex = 0;
	current_score++;
	log("current_score  %d", current_score);
	log("need_socre %d", need_score);
	if (current_score >= need_score) {
		this->scheduleOnce(schedule_selector(GameLayer::gameOverLayOut),0.5);
		//this->gameOverLayOut();
		//this->gameOverSettlement();
	}
    //CCLOG("call oneUpdate once");
}

//旋转特效
FiniteTimeAction* GameLayer::getSpecialEffectsAnimation()
{
	//作用创建一个旋转的动作
	//参数1：旋转的时间  参数2：旋转饿角度  0 - 360
    ActionInterval * rotateby = CCRotateBy::create(0.4, 360);
    //CCActionInterval*  actionByBack = actionBy->reverse();                            //回复
	ActionInterval * scaleto = CCScaleTo ::create(0, 0.3);
	//    作用：创建一个渐变消失的动作
    //    参数是时间
    //    CCActionInterval * fadeout = CCFadeOut::create(2);
    //    sp->runAction(fadeout);
	ActionInterval * fadeout = FadeOut::create(0);
	return Sequence::create(scaleto,rotateby,fadeout,NULL);
	//FiniteTimeAction * spawn =Sequence::create(scaleto,rotateby,fadeout,NULL);
	//sprite->runAction(spawn);
	//sprite->setVisible(false);
}


void GameLayer::addLinePoints(Vec2 a, Vec2 b,bool X)
{
	log("print a.x=%f,a.y=%f,b.x=%f,b.y=%f",a.x,a.y,b.x,b.y);
	if (!(a.x == b.x || a.y == b.y)) {
		return;
	}

	int i;
	if (X) {

		if (a.y > b.y) {
			for (i = a.y ; i >= b.y; --i) {
				linePoints.push_back(Vec2(a.x, i));
			}
		}else {
			for (i = b.y ; i >= a.y; --i) {
				linePoints.push_back(Vec2(a.x, i));
			}
		}
	}
	else {
		if (a.x > b.x) {
			for (i = a.x ; i >= b.x; --i) {
				linePoints.push_back(Vec2(i, a.y));
			}
		}else {
			for (i = b.x ; i >= a.x; --i) {
				linePoints.push_back(Vec2(i, a.y));
			}
		}

	}
}


//三种匹配算法
//一直线
// 1 代表x轴相同  0 代表Y轴相同 -1 代表都不同
int GameLayer::match_direct(Vec2 a, Vec2 b)
{
	if (!(a.x == b.x || a.y == b.y)) {
		return -1;
	}

	int i;
	bool match_x = false;
	
	if (a.x == b.x) {
		match_x = true;
		if (a.y > b.y) {
			for (i = a.y - 1; i > b.y; --i) {
				Vec2 point = CCPointMake(a.x, i);
				if (!this->isValiableNode(point) || !this->isEmptyNode(point)){
					match_x = false;
				}
			}

		} else {
			for (i = b.y - 1; i > a.y; --i) {
				Vec2 point = CCPointMake(a.x, i);
				if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_x = false;
				}
			}
		}
		
		if (match_x)
		{
			return 1;
			//this->addLinePoints(a, b,true);
			//return true;
		}
	} 
	bool match_y = false;
	if(a.y == b.y) {
		match_y = true;
		if (a.x > b.x) {
			for (i = a.x - 1; i > b.x; --i) {
				Vec2 point = CCPointMake(i, a.y);
				if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_y = false;
				}
			}

		}else{
			for (i = b.x - 1; i > a.x; --i) {
				Vec2 point = CCPointMake(i, a.y);
				if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_y = false;
				}
			}
		}
		

		if (match_y)
		{
			return 0;
			//this->addLinePoints(a, b,false);
			//return true;
		}
	}

	return -1;

	//return match_x || match_y;
}

//一个拐点的
bool GameLayer::match_one_corner(Vec2 a, Vec2 b)
{
	auto point = CCPointMake(b.x, a.y);
	int bxaLineStats = this->match_direct(a, point);
	int bxbLineStats = this->match_direct(b, point);
	if (this->isValiableNode(point) && this->isEmptyNode(point) && bxaLineStats >= 0 && bxbLineStats >= 0){
		this->addLinePoints(a, point,bool(bxaLineStats));
		this->addLinePoints(point, b,bool(bxbLineStats));
		return true;
	}

	point = CCPointMake(a.x, b.y);
	int axaLineStats = this->match_direct(a, point);
	int axbLineStats = this->match_direct(b, point);
	if (this->isValiableNode(point) && this->isEmptyNode(point) && axaLineStats>= 0  && axbLineStats>= 0){
		this->addLinePoints(a, point,bool(axaLineStats));
		this->addLinePoints(point,b,bool(axbLineStats));
		return true;
	}

	return false;
}

//两个拐点的
bool GameLayer::match_two_corner(Vec2 a, Vec2 b)
{
	for (int i = a.x - 1; i >= 0; --i) { //y 轴相等
		auto point = CCPointMake(i, a.y);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
			break;
		}
		else {
			if (this->match_one_corner(point, b)) {
				this->addLinePoints(a, point,false);
				return true;
			}
		}
	}

	for (int i = a.x + 1; i < x_count; ++i) {
		auto point = CCPointMake(i, a.y);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
			break;
		}
		else {
			if (this->match_one_corner(point, b)) {
				this->addLinePoints(a, point,false);
				return true;
			}
		}
	}

	for (int i = a.y - 1; i >= 0; --i) {
		auto point = CCPointMake(a.x, i);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
			break;
		}
		else {
			if (this->match_one_corner(point, b)) {
				this->addLinePoints(a, point,true);
				return true;
			}
		}
	}

	for (int i = a.y + 1; i < y_count; ++i) {
		auto point = CCPointMake(a.x, i);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
			break;
		}
		else {
			if (this->match_one_corner(point, b)) {
				this->addLinePoints(a, point,true);
				return true;
			}
		}
	}

	return false;
}


bool GameLayer::match(Vec2 a, Vec2 b)
{
	int lineState = this->match_direct(a, b);
	if (lineState >= 0) {
		this->addLinePoints(a, b,bool(lineState));
		return true;
	}
	if (this->match_one_corner(a, b)) {
		return true;
	}
	if (this->match_two_corner(a, b)) {
		return true;
	}

	return false;
}


void GameLayer::gotoNextLevel(int nexeLevel){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* gameOver = FloatWord::create(
		"NEXT GAME", 80, Point(visibleSize.width, visibleSize.height / 2));
	this->addChild(gameOver);
	gameOver->floatIn(1.0f, []{log("xieyugui"); });
	GameUtils::startGameByLevel(nexeLevel);
}

void GameLayer::gotoGameOver(){

	//GAMEDATA::getInstance()->saveHighestScore();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	FloatWord* gameOver = FloatWord::create(
		"GAME OVER", 80, Point(visibleSize.width, visibleSize.height / 2));
	this->addChild(gameOver);
	gameOver->floatIn(1.0f, []{Director::getInstance()->replaceScene(LevelSelectLayer::createScene()); });
}


void GameLayer::gameOverSettlement()
{
	GameData::getInstance()->passCurrentUserLevel();
	int nextLevel = GameData::getInstance()->getChooseLevel() + 1;
	if (GameData::getInstance()->getmaxLevel() >= nextLevel) {
		this->gotoNextLevel(nextLevel);
	}
	else {
		this->gotoGameOver();
	}
}

void GameLayer::gameOverLayOut(float dt)
{
	menu->overGame();
}



