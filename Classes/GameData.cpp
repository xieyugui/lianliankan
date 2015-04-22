#include "GameData.h"
#include "Audio.h"
#include "GameUtils.h"

USING_NS_CC;

GameData* GameData::_instance = 0;
GameData::GameData() {
	this->init();
}

GameData* GameData::getInstance() {
	if (_instance == 0) {
		_instance = new GameData();
	}
	return _instance;
}

void GameData::init() {
	//读取用户当前等级
	this->initUserPassLevel();
	//读取等级配置数据
	this->initLevelData();
	is_pause = false;
	//初始化等级关卡一些参数
	this->initLevelScale();
}

void GameData::initLevelScale() {
	//SpriteFrameCache::getInstance()->addSpriteFramesWithFile("startUI.plist", "startUI.png");
	//auto leftMenuSpriteNor = Sprite::create("page_pre.png");
	auto locte = Sprite::create("lockLevel.png");
	//locte->autorelease();
	//page_scale = GameUtils::getPageScale(leftMenuSpriteNor,normalSprite);
	level_scale = GameUtils::getLevelScale(locte);
	level_sprite_w = locte->getContentSize().width*level_scale;
	//level_space = GameUtils::getSpaceSizeRate(2+g_EachLineCount);
	//log("init level Data =%f,=%f,=%f",page_scale,level_scale,level_space);

}

void GameData::initUserPassLevel() {
	if (!UserDefault::getInstance()->getBoolForKey(PlayerPassLevelCountKey))
	{
		UserDefault::getInstance()->setBoolForKey(PlayerPassLevelCountKey, true);
		UserDefault::getInstance()->setIntegerForKey("curlevel", 1);
		UserDefault::getInstance()->flush();
	}
	this->setCurLevel(UserDefault::getInstance()->getIntegerForKey("curlevel"));
	this->setChooseLevel(this->getCurLevel());
}

void GameData::saveUserPassLevel() {
	if (!UserDefault::getInstance()->getBoolForKey(PlayerPassLevelCountKey))
	{
		UserDefault::getInstance()->setBoolForKey(PlayerPassLevelCountKey, true);
	}
	UserDefault::getInstance()->setIntegerForKey("curlevel", this->getCurLevel());
	UserDefault::getInstance()->flush();
}

void GameData::passCurrentUserLevel() {
	if (this->getChooseLevel() > this->getCurLevel()) {
		if (this->getCurLevel() >= max_level) {
			return;
		}
		this->setCurLevel(this->getCurLevel() + 1);
		this->saveUserPassLevel();
	}
}

/*
auto find_sp = sp_map.find("10");//通过find()查找key为“10”的pair类型。
auto sp3 = find_sp->second;//键对应的对象
std::string find_str = find_sp->first;//键
CCLOG("sp6 key value is %s",find_str.c_str());//打印出键

auto sp2=sp_map.at("sp1");//通过key取出sp1
sp_map.insert("11",sp2);//再将sp1以三个key值的方式存入map
sp_map.insert("22",sp2);
sp_map.insert("33",sp2);
auto _key=sp_map.keys(sp1);//获得sp1对应的key值
for(const auto&e : _key)
{
CCLOG("_key is %s",e.c_str());//输出sp1对应的key值（有四个，分别是：sp1,11,22,33）
}

*/
//初始化游戏数据配置
void GameData::initLevelData() {
	//读取plist数据文件
	std::string plistPath = FileUtils::sharedFileUtils()->fullPathFromRelativeFile("levelinfo.plist", "levelinfo.plist");
	level_data.clear();
	auto allkeys = Array::create();
	//level_data = dynamic_cast<Array *>(Dictionary::createWithContentsOfFile(plistPath.c_str()));
	auto plistDic = Dictionary::createWithContentsOfFile(plistPath.c_str());
	auto block_count= dynamic_cast<String *> (plistDic->objectForKey("block_count"));
	this->setblockCount(block_count->intValue());
	log("block_count=%s", block_count->getCString());
	auto game_levels= dynamic_cast<String *> (plistDic->objectForKey("levels"));
	this->setmaxLevel(game_levels->floatValue());
	//7,7,10,10;7,8,12,17
	auto level_info = dynamic_cast<String *> (plistDic->objectForKey("level_info"));
	level_data = this->split(level_info->getCString(),";");
	//log("level_info=%s", level_info->getCString());

}

//字符串分割函数  
std::vector<std::string> GameData::split(std::string str,std::string pattern)  
{  
    std::string::size_type pos;  
    std::vector<std::string> result;  
    str+=pattern;//扩展字符串以方便操作  
    int size=str.size();  
  
    for(int i=0; i<size; i++)  
    {  
        pos=str.find(pattern,i);  
        if(pos<size)  
        {  
            std::string s=str.substr(i,pos-i);  
            result.push_back(s);  
            i=pos+pattern.size()-1;  
        }  
    }  
    return result;  
} 



void GameData::getLevelData(int level,float &x_count,float &y_count, int &grid_count,int &scope) {
	if (level > max_level) {
		return;
	}
	if (level == 0) {
		level = this->getChooseLevel();
	}
	if(level > level_data.size()) {
		level = level_data.size();
	}
	std::string levels = level_data.at(level-1);
	std::vector<std::string> linfo = this->split(levels,",");
	x_count = 7.0;
	y_count = 9.0;
	grid_count = 10;
	scope = 10;
	if (linfo.size() == 4) {
		x_count = atoi(linfo.at(0).c_str())*1.0;
		y_count = atoi(linfo.at(1).c_str())*1.0;
		grid_count = atoi(linfo.at(2).c_str());
		scope = atoi(linfo.at(3).c_str());
	}
}

void GameData::playOrStopMusic() {
	if( is_pause==false )
    {
		Audio::getInstance()->pauseAllEffects();
    }
    else
    {
		Audio::getInstance()->resumeAllEffects();
    }
}