#include "LevelSelectLayer.h"
#include "GameUtils.h"
#include "GameData.h"
#include "MenuScene.h"

LevelSelectLayer::LevelSelectLayer() :_currentPage(0){//初始化
	float maxPage = g_maxLevel / g_EachPageCount;// 总的关卡数  每一页的关卡数   float
	_maxPage = g_maxLevel / g_EachPageCount;//int类型
	log("yeshu =%f, =%d",maxPage,_maxPage);
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


	auto gameBg = Sprite::create("bg.png");
	//float wBg = gameBg->getContentSize().width;
	//Rect rect;
	//if (VISIBLE_WIDTH >= size_width) {
	//	rect = Rect((wBg - VISIBLE_WIDTH)/2, 1, VISIBLE_WIDTH, VISIBLE_HEIGHT);   //图片的大小
	//}else {
	//	rect = Rect((wBg - size_width)/2, 1, size_width, size_height);   //图片的大小
	//	
	//}

	//gameBg->setTextureRect(rect);
	gameBg->setScaleX(GetXScaleRate);
	gameBg->setScaleY(GetYScaleRate);
	gameBg->setPosition(Vec2(VISIBLE_WIDTH / 2, VISIBLE_HEIGHT / 2));
	this->addChild(gameBg, -1);

	//返回
	pBack = MenuItemImage::create("btn_back.png", "btn_back.png",CC_CALLBACK_0(LevelSelectLayer::menuBackMainMenu, this));
	pBack->setScaleX(GetXScaleRate);
	pBack->setScaleY(GetYScaleRate);
	pBack->setPosition(Vec2(pBack->boundingBox().size.width / 2 + 10 , VISIBLE_HEIGHT - pBack->boundingBox().size.height / 2 - 10));
	pMenu = Menu::create(pBack, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);


	initAllLevels();
	initNavigation();

	return true;
}


//初始化导航  
void LevelSelectLayer::initNavigation(){
	float alreadyUseH = pBack->boundingBox().size.height + level_space*2  + (g_EachPageCount/g_EachLineCount)*(GameData::getInstance()->getlevelSpriteW() +level_space*2);

	leftMenuSpritePre = MenuItemImage::create("page_pre.png", "page_pre.png", CC_CALLBACK_0(LevelSelectLayer::prePageBack, this));
	log("changdu %f,%f",leftMenuSpritePre->getContentSize().width,leftMenuSpritePre->getContentSize().height);
	leftMenuSpritePre->setScaleX(GetXScaleRate);
	leftMenuSpritePre->setScaleY(GetYScaleRate);
	float leftW = leftMenuSpritePre->boundingBox().size.width;
	float leftH = leftMenuSpritePre->boundingBox().size.height;
	leftMenuSpritePre->setPosition(VISIBLE_WIDTH*0.5 - leftW ,VISIBLE_HEIGHT -(alreadyUseH+leftH/2));

	rightMenuSpritePre = MenuItemImage::create("page_next.png", "page_next.png", CC_CALLBACK_0(LevelSelectLayer::nextPageBack, this));
	rightMenuSpritePre->setScaleX(GetXScaleRate);
	rightMenuSpritePre->setScaleY(GetYScaleRate);
	float rightW = rightMenuSpritePre->boundingBox().size.width;
	float rightH = rightMenuSpritePre->boundingBox().size.height;
	rightMenuSpritePre->setPosition(VISIBLE_WIDTH*0.5 + rightW ,VISIBLE_HEIGHT -(alreadyUseH+leftH/2));

	pageMenu = Menu::create(leftMenuSpritePre,rightMenuSpritePre, NULL);
	pageMenu->setPosition(Vec2::ZERO);
	this->addChild(pageMenu);

	if (_currentPage == 0){
		leftMenuSpritePre->setVisible(false);
	}
	if (_currentPage == (_maxPage - 1)){
		rightMenuSpritePre->setVisible(false);
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
	levelSelectContent->initAllLevels(_currentPage,pBack->boundingBox().size.height + level_space*2);//初始化这页的关卡
}

void LevelSelectLayer::menuBackMainMenu()
{
	Scene *pScene = Scene::create();
	pScene->addChild(MenuScene::create());
	Director::getInstance()->replaceScene(pScene);
}



void LevelSelectLayer::nextPageBack(){
	if (_currentPage < _maxPage - 1){
		_currentPage = _currentPage + 1;

		levelSelectContent->initAllLevels(_currentPage,pBack->boundingBox().size.height + level_space*2);

		if (_currentPage == (_maxPage - 1)){
			rightMenuSpritePre->setVisible(false);
		}
		leftMenuSpritePre->setVisible(true);
	}
}
void LevelSelectLayer::prePageBack(){
	if (_currentPage >= 1){
		_currentPage = _currentPage - 1;

		levelSelectContent->initAllLevels(_currentPage,pBack->boundingBox().size.height + level_space*2);

		if (_currentPage == 0){
			leftMenuSpritePre->setVisible(false);
		}
		rightMenuSpritePre->setVisible(true);
	}
}

