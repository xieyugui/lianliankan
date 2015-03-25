#include "LevelSelectLayer.h"
#include "GameUtils.h"
#include "GameData.h"

LevelSelectLayer::LevelSelectLayer() :_currentPage(0){//初始化
	float maxPage = g_maxLevel / g_EachPageCount;// 总的关卡数  每一页的关卡数   float
	_maxPage = g_maxLevel / g_EachPageCount;//int类型
	if (maxPage > _maxPage){//比较大小
		_maxPage = _maxPage + 1;
	}
}
LevelSelectLayer::~LevelSelectLayer(){

}

Scene* LevelSelectLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LevelSelectLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LevelSelectLayer::init(){
	if (!Layer::init()){
		return false;
	}
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("startUI.plist", "startUI.png");


	auto gameBg = Sprite::create("game_bg.png");
	float wBg = gameBg->getContentSize().width;
	if (VISIBLE_WIDTH > wBg) {
		wBg = VISIBLE_WIDTH - (VISIBLE_WIDTH - wBg) / 2;
	}

	auto rect = Rect(((VISIBLE_WIDTH - wBg) / 2) / wBg, 1, wBg, VISIBLE_HEIGHT);   //图片的大小
	gameBg->setTextureRect(rect);
	gameBg->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	this->addChild(gameBg, -1);

	//auto colorLayer = LayerColor::create(Color4B(0x24, 0x2c, 0x3c, 255));
	//this->addChild(colorLayer, 0);


	initAllLevels();
	initNavigation();

	return true;
}



//初始化导航
void LevelSelectLayer::initNavigation(){


	auto leftMenuSpriteNor = Sprite::createWithSpriteFrameName("prePage.png");
	auto leftMenuSpritePre = Sprite::createWithSpriteFrameName("prePagePre.png");
	auto leftMenuItem = MenuItemSprite::create(leftMenuSpriteNor, leftMenuSpritePre, CC_CALLBACK_1(LevelSelectLayer::prePageBack, this));
	_leftMenu = Menu::create(leftMenuItem, NULL);
	this->addChild(_leftMenu);
	_leftMenu->setPosition(100, VISIBLE_HEIGHT * 0.5);

	auto rightMenuSpriteNor = Sprite::createWithSpriteFrameName("nextPage.png");
	auto rightMenuSpritePre = Sprite::createWithSpriteFrameName("nextPagePre.png");
	auto rightMenuItem = MenuItemSprite::create(rightMenuSpriteNor, rightMenuSpritePre, CC_CALLBACK_1(LevelSelectLayer::nextPageBack, this));
	_rightMenu = Menu::create(rightMenuItem, NULL);
	this->addChild(_rightMenu);
	_rightMenu->setPosition(VISIBLE_WIDTH - 100, VISIBLE_HEIGHT * 0.5);

	if (_currentPage == 0){
		_leftMenu->setVisible(false);
	}
	if (_currentPage == (_maxPage - 1)){
		_rightMenu->setVisible(false);
	}
}


void LevelSelectLayer::initAllLevels(){
	//UserDefault *save = UserDefault::getInstance();
	//g_passLevelCount = save->getIntegerForKey(PlayerPassLevelCountKey, 0);//获取用户当前的关卡等级
	//log("g_passLevelCount:%d", g_passLevelCount);

	//just for test, in real game, comment the below code
	//g_passLevelCount = 10;
	int g_passLevelCount = GameData::getInstance()->getCurLevel();
	log("g_passLevelCount:%d", g_passLevelCount);

	levelSelectContent = LevelSelectContent::create();//关卡等级选项
	this->addChild(levelSelectContent);
	_currentPage = g_passLevelCount / g_EachPageCount;//根据用户当前的关卡等级，算出当前页数
	if (_currentPage >= _maxPage){
		_currentPage = _maxPage - 1;
	}
	levelSelectContent->initAllLevels(_currentPage);//初始化这页的关卡
}



void LevelSelectLayer::nextPageBack(Ref* sender){
	if (_currentPage < _maxPage - 1){
		_currentPage = _currentPage + 1;

		levelSelectContent->initAllLevels(_currentPage);

		if (_currentPage == (_maxPage - 1)){
			_rightMenu->setVisible(false);
		}
		_leftMenu->setVisible(true);
	}
}
void LevelSelectLayer::prePageBack(Ref* sender){
	if (_currentPage >= 1){
		_currentPage = _currentPage - 1;

		levelSelectContent->initAllLevels(_currentPage);

		if (_currentPage == 0){
			_leftMenu->setVisible(false);
		}
		_rightMenu->setVisible(true);
	}
}

