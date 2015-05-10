#include "LevelSelectLayer.h"
#include "GameUtils.h"
#include "GameData.h"
#include "MenuScene.h"
#include "MyJniHelper.h"

LevelSelectLayer::LevelSelectLayer() :_currentPage(0){//初始化
	clicked = false;
	float maxPage = GameData::getInstance()->getmaxLevel() / g_EachPageCount;// 总的关卡数  每一页的关卡数   float
	_maxPage = GameData::getInstance()->getmaxLevel() / g_EachPageCount;//int类型
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

	auto locte = Sprite::create("lockLevel.png");
	//locte->autorelease();
	//page_scale = GameUtils::getPageScale(leftMenuSpriteNor,normalSprite);
	GameData::getInstance()->setlevelSacle(GameUtils::getLevelScale(locte));
	GameData::getInstance()->setlevelSpriteW(locte->getContentSize().width*GameData::getInstance()->getlevelSacle());

	//返回
	pBack = MenuItemImage::create("btn_back.png", "btn_back.png",CC_CALLBACK_0(LevelSelectLayer::menuBackMainMenu, this));
	pBack->setScaleX(GetXScaleRate);
	pBack->setScaleY(GetYScaleRate);
	pBack->setPosition(Vec2(pBack->boundingBox().size.width / 2 + level_space , VISIBLE_HEIGHT - pBack->boundingBox().size.height / 2 - level_space));
	pMenu = Menu::create(pBack, NULL);
	pMenu->setPosition(Vec2::ZERO);
	this->addChild(pMenu);


	initAllLevels();
	initNavigation();

	MyJniHelper::showBan(1);

			//对手机返回键的监听 
	auto listener = EventListenerKeyboard::create(); 
	//和回调函数绑定 
	listener->onKeyReleased = CC_CALLBACK_2(LevelSelectLayer::onKeyReleased,this); 
	//添加到事件分发器中 
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener,this);

	return true;
}


//初始化导航  
void LevelSelectLayer::initNavigation(){
	float alreadyUseH = banner_height + level_space;

	leftMenuSpritePre = MenuItemImage::create("page_pre.png", "page_pre.png", CC_CALLBACK_0(LevelSelectLayer::prePageBack, this));
	log("changdu %f,%f",leftMenuSpritePre->getContentSize().width,leftMenuSpritePre->getContentSize().height);
	leftMenuSpritePre->setScaleX(GetXScaleRate);
	leftMenuSpritePre->setScaleY(GetYScaleRate);
	float leftW = leftMenuSpritePre->boundingBox().size.width;
	float leftH = leftMenuSpritePre->boundingBox().size.height;
	leftMenuSpritePre->setPosition(VISIBLE_WIDTH*0.5 - leftW ,alreadyUseH+leftH);

	rightMenuSpritePre = MenuItemImage::create("page_next.png", "page_next.png", CC_CALLBACK_0(LevelSelectLayer::nextPageBack, this));
	rightMenuSpritePre->setScaleX(GetXScaleRate);
	rightMenuSpritePre->setScaleY(GetYScaleRate);
	float rightW = rightMenuSpritePre->boundingBox().size.width;
	float rightH = rightMenuSpritePre->boundingBox().size.height;
	rightMenuSpritePre->setPosition(VISIBLE_WIDTH*0.5 + rightW ,alreadyUseH+leftH);

	pageMenu = Menu::create(leftMenuSpritePre,rightMenuSpritePre, NULL);
	pageMenu->setPosition(Vec2::ZERO);
	this->addChild(pageMenu,0);

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
	levelSelectContent->initAllLevels(_currentPage,pBack->boundingBox().size.height+level_space*2);//初始化这页的关卡
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


void LevelSelectLayer::onKeyReleased(EventKeyboard::KeyCode keyCode,Event * pEvent) 
{ 
	if (keyCode == EventKeyboard::KeyCode::KEY_MENU){
		if(clicked) {
			clicked= false;
			CCLog("doubleclick");
			Director::getInstance()->end();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
			#endif
		}else {
			//延时0.25s执行（注意在这0.25s的延时过程中clicked已经为true），
			//如果在这个过程中再次click，那么就执行上面的双击事件处理了
			//否则，那么就执行下面的回调函数了，处理单击事件
			scheduleOnce(schedule_selector(LevelSelectLayer::doubleClickState),0.25f);
			clicked= true;
		}
	}

} 

void LevelSelectLayer::doubleClickState(float tt)
{
    if(clicked) {
        clicked = false;
		CCLog("singleclick");
    }

}

