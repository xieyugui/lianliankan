#include "GameLayer.h"
#include "GameData.h"
#include "GameUtils.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"

#include "AudioProxy.h"
#include "FloatWord.h"
#include "MenuScene.h"
#include "LevelSelectLayer.h"
#include "MapNode.h"
#include "PauseLayer.h"

USING_NS_CC_EXT;
USING_NS_CC;

GameLayer::GameLayer() :current_score(0), prePoint(Vec2(-1,-1))
{

}

GameLayer::~GameLayer()
{
	//CC_SAFE_RELEASE(mapArray);//CC_SAFE_DELETE_ARRAY(mapArray);
	mapArray->release();
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

	menu = TopMenu::create();
	this->addChild(menu);
	//this->initTopMenuUI();

	return true;

}


void GameLayer::initData()
{
	GameData::getInstance()->getLevelXY(total_x, total_y, need_score,0);
	log("initData %d,%d,%d", total_x, total_y, need_score);
	this->initImgSpriteSize();
	mapArray = Array::create();
	auto levelArr = GameData::getInstance()->getLevelData(0);
	mapArray->retain();
	for (int index = 0; index < levelArr->count(); index++) {
		MapNode *node = new MapNode();
		node->autorelease();
		node->imgid = ((String *)(levelArr->objectAtIndex(index)))->intValue();
		log("initData = %d", node->imgid);
		mapArray->addObject(node);
	}

	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("icon1.plist");
	SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("common.plist");

	//���touch����
	//	Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 1, true);
	auto _eventDispatcher = Director::getInstance()->getEventDispatcher();
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);//������ʼ
	//touchListener->onTouchMoved = CC_CALLBACK_2(MapLayer::onTouchMoved, this);//�����ƶ�
	touchListener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);//��������
	touchListener->setSwallowTouches(true);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);//ע��ַ���

	prePoint = CCPointMake(-1, -1);


}

void GameLayer::initImgSpriteSize()
{
	img_w = this->getContentSize().width / total_x;
	img_h = this->getContentSize().height / total_y;
	log("image all w %f", img_w);
	log("image  all h %f", img_h);

}


void GameLayer::initUI()
{
	//auto spriteScale = this->getSpriteS();
	//����sprite
	int wIndex = 0;
	for (int index = 0; index < total_x *total_y; index++)    {
		log("image file name %d", index);
		if (this->imageFilename(index))
		{

			auto *sprite = Sprite::createWithSpriteFrameName(this->imageFilename(index)->getCString());
			//auto rectInsets = CCRectMake(0, 0, img_w, img_h); //left��right��width��height	
			//sprite->setTextureRect(rectInsets);
			wIndex = index;
			if (index > total_x) {
				wIndex = index - int(index / total_x) * total_x;
			}
			sprite->setPosition(ccp((img_w / 2) + wIndex*img_w, (img_h / 2) + int(index / total_x)*img_h));
			log("y=%d", int(index / total_x));

			this->addChild(sprite, 1, TAG_START_SPRITE + index);

		}

	}
}

//void GameLayer::initTopMenuUI(){
//	level = Label::create(String::create("Level: ")->_string + String::createWithFormat("%d", GameData::getInstance()->getChooseLevel())->_string,"Arial", 30);
//	level->setPosition(100, VISIBLE_HEIGHT - 50);
//	this->addChild(level, 1);
//
//	auto startBtn = MenuItemImage::create("pause.png", "pause.png", CC_CALLBACK_0(GameLayer::pauseGame, this));
//	auto menu = Menu::create(startBtn, NULL);
//	menu->alignItemsVertically();
//	menu->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT - 50));
//	this->addChild(menu, 1);
//}

void GameLayer::pauseGame() {
	AudioProxy::getInstance()->playButtonClick();
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


//��ȡͼƬ
String* GameLayer::imageFilename(int index)
{
	if (index < 0 || index >= mapArray->count()) {
		return NULL;
	}

	int n = ((MapNode *)(mapArray->objectAtIndex(index)))->imgid;
	if (n >= 1) {
		log("imageFilename = %d", n);
		return String::createWithFormat("%d.png", n);
	}
	return NULL;

}




//��Ļ����ת���ɵ�ͼ����
Vec2 GameLayer::pointOfView(Vec2 point)
{

	int x = -1;
	int y = -1;
	if (point.x > 0 && point.x < total_x * img_w)
		x = (point.x) / (img_w );
	if (point.y > 0 && point.y < total_y * img_h)
		y = (point.y) / (img_h );

	return Vec2(x, y);
}


//�Ƿ�����Ч��Χ��
bool GameLayer::isValiableNode(Vec2 point)
{
	return point.x >= 0 && point.x < total_x && point.y >= 0 && point.y < total_y;
}

//�Ƿ��ǿյ������
bool GameLayer::isEmptyNode(Vec2 point)
{
	int index = this->indexFromPoint(point);
	if (index >= mapArray->count()) {
		return true;
	}
	MapNode *node = (MapNode *)mapArray->objectAtIndex(index);
	log("isEmptyNode %d", node->imgid);
	return (node->imgid == 0);
}

//ÿ��sprite��index
int GameLayer::indexFromPoint(Vec2 point)
{
	return point.y * total_x + point.x;

}


//�Ƿ�����ͬ�ĵ�
bool GameLayer::isSamePoints(Vec2 p1, Vec2 p2)
{
	return (p1.x == p2.x && p1.y == p2.y);
}


//���
void GameLayer::clearNode(Vec2 point)
{
	int index = this->indexFromPoint(point);

	MapNode *node = (MapNode *)mapArray->objectAtIndex(index);

	node->imgid = 0;
}

//�ж������Ƿ��������
bool GameLayer::canClearTwo(Vec2 pointpre, Vec2 pointcurrent)
{
	bool bMatch = false;
	int pre = this->indexFromPoint(pointpre);
	int current = this->indexFromPoint(pointcurrent);
	int p = ((MapNode *)(mapArray->objectAtIndex(pre)))->imgid;
	int c = ((MapNode *)(mapArray->objectAtIndex(current)))->imgid;

	if (p == c && this->match(pointcurrent, pointpre))
	{
		bMatch = true;
	}

	return bMatch;
}


//�Ŵ���С����
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

	//������������ڷ���true
	if (this->boundingBox().containsPoint(location))
	{

		return true;


	}

	//���򷵻�false,��ֹ��������touch����
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
	AudioProxy::getInstance()->playSprite();

	if (prePoint.x == -1 && prePoint.y == -1) {
		prePoint = location;
		return ;
	}

	if (this->isSamePoints(location, prePoint))
	{
		return;
	}

	//�����ǰ����
	auto *spritecurrent = (Sprite *)this->getChildByTag(TAG_START_SPRITE + this->indexFromPoint(location));
	spritecurrent->setScale(1.1);


	if (this->isValiableNode(prePoint) && !this->isEmptyNode(prePoint))
	{
		CCLOG("%d", this->indexFromPoint(location));
		//ǰһ��
		auto *spritepre = (Sprite *)this->getChildByTag(TAG_START_SPRITE + this->indexFromPoint(prePoint));
		//auto *spriteLine = (Sprite *)this->getChildByTag(TAG_START_SPRITE * 2 + this->indexFromPoint(prePoint));//by xie

		if (this->canClearTwo(prePoint, location))
		{

			//SimpleAudioEngine::sharedEngine()->playEffect("4.wav");
			AudioProxy::getInstance()->playEliminate();
			this->clearNode(location);
			this->clearNode(prePoint);
			prePoint = Vec2(-1,-1);
			spritecurrent->setVisible(false);
			spritepre->setVisible(false);
			current_score++;
			log("current_score  %d", current_score);
			log("need_socre %d", need_score);
			if (current_score >= need_score) {
				this->gameOverSettlement();
			}
		}
		else
		{
			spritepre->setScale(0.9);
			this->scaleAnimation(spritepre);
			//spriteLine->setVisible(true);//by xie

		}

	}

	prePoint = location;

}



//����ƥ���㷨
//һֱ��
bool GameLayer::match_direct(Vec2 a, Vec2 b)
{
	if (!(a.x == b.x || a.y == b.y)) {
		return false;
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
		}
		if (b.y > a.y) {
			for (i = b.y - 1; i > a.y; --i) {
				Vec2 point = CCPointMake(a.x, i);
				if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_x = false;
				}
			}
		}
	}

	bool match_y = false;
	if (a.y == b.y) {
		match_y = true;
		if (a.x > b.x) {
			for (i = a.x - 1; i > b.x; --i) {
				Vec2 point = CCPointMake(i, a.y);
				if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_y = false;
				}
			}
		}
		if (b.x > a.x) {
			for (i = b.x - 1; i > a.x; --i) {
				Vec2 point = CCPointMake(i, a.y);
				if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
					match_y = false;
				}
			}
		}
	}

	return match_x || match_y;
}

//һ���յ��
bool GameLayer::match_one_corner(Vec2 a, Vec2 b)
{
	auto point = CCPointMake(b.x, a.y);

	if (this->isValiableNode(point) && this->isEmptyNode(point) && this->match_direct(a, point) && this->match_direct(b, point)){
		return true;
	}

	point = CCPointMake(a.x, b.y);
	if (this->isValiableNode(point) && this->isEmptyNode(point) && this->match_direct(a, point) && this->match_direct(b, point)){
		return true;
	}

	return false;
}

//�����յ��
bool GameLayer::match_two_corner(Vec2 a, Vec2 b)
{
	for (int i = a.x - 1; i >= 0; --i) {
		auto point = CCPointMake(i, a.y);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
			break;
		}
		else {
			if (this->match_one_corner(point, b)) {
				return true;
			}
		}
	}

	for (int i = a.x + 1; i < total_x; ++i) {
		auto point = CCPointMake(i, a.y);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
			break;
		}
		else {
			if (this->match_one_corner(point, b)) {
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
				return true;
			}
		}
	}

	for (int i = a.y + 1; i < total_y; ++i) {
		auto point = CCPointMake(a.x, i);
		if (!this->isValiableNode(point) || !this->isEmptyNode(point)) {
			break;
		}
		else {
			if (this->match_one_corner(point, b)) {
				return true;
			}
		}
	}

	return false;
}


bool GameLayer::match(Vec2 a, Vec2 b)
{
	if (this->match_direct(a, b)) {
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
	if (GameData::getInstance()->getLevelCount() >= nextLevel) {
		this->gotoNextLevel(nextLevel);
	}
	else {
		this->gotoGameOver();
	}
}



