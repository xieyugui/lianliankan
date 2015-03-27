#ifndef _LIANLIANKANX_GAMEDATA_H_
#define _LIANLIANKANX_GAMEDATA_H_

#include "cocos2d.h"
USING_NS_CC;


#define TAG_START_SPRITE			        200
#define OFFSET_X							12*2
#define OFFSET_Y							12*2
#define IMG_W								42*2
#define IMG_H								42*2

typedef enum{
	kAlreadyPass,
	kNotPassYet,
	kLockLevel
}LevelItemType;

const char PlayerPassLevelCountKey[] = "LianLianKanByXie";

const int levelMarginX = 113;
const int levelMarginY = 134;

const int g_maxLevel = 45;
const int g_EachPageCount = 15;
const int g_EachLineCount = 5;

class GameData{
public:
	static GameData* getInstance();
	/*当前等级*/
	CC_SYNTHESIZE(int, cur_level, CurLevel);//定义了get set //varType, varName, funName
	CC_SYNTHESIZE(int, choose_level, ChooseLevel);
	CC_SYNTHESIZE(bool,is_pause, isPause);
	//CC_SYNTHESIZE(int, next_level, NextLevel);

	void saveUserPassLevel();
	void initUserPassLevel();
	void passCurrentUserLevel();//当前关卡已过
	int getLevelCount();

	void initLevelData();

	void playOrStopMusic();
	
	void getLevelXY(int &x, int &y, int &score,int level);
	Array* getLevelData(int level);


private:
	GameData();
	void init();

private:
	static GameData* _instance;
	//int cur_level;
	//Array* level_data;
	Map<int, Array*> level_data;
	Map<int, Array*> xy_data;
	//int next_level;
};

#endif