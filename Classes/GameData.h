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

const float g_maxLevel = 40;
const int g_EachPageCount = 16;
const float g_EachLineCount = 4;

const float size_width = 768;
const float size_height = 1136;

const float level_space = 10;

class GameData{
public:
	static GameData* getInstance();
	/*当前等级*/
	CC_SYNTHESIZE(int, cur_level, CurLevel);//定义了get set //varType, varName, funName
	CC_SYNTHESIZE(int, choose_level, ChooseLevel);
	CC_SYNTHESIZE(bool,is_pause, isPause);
	CC_SYNTHESIZE(float,page_scale, pageSacle);
	CC_SYNTHESIZE(float,level_scale, levelSacle);
	CC_SYNTHESIZE(float,level_sprite_w,levelSpriteW);//缩放之后的大小

	//CC_SYNTHESIZE(int, next_level, NextLevel);

	void saveUserPassLevel();
	void initUserPassLevel();
	void passCurrentUserLevel();//当前关卡已过
	int getLevelCount();

	void initLevelData();
	void initLevelScale();

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