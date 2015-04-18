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

//const float g_maxLevel = 50;
const int g_EachPageCount = 16;
const float g_EachLineCount = 4;

const float size_width = 768;
const float size_height = 1136;

const float level_space = 10;

//const float x_count = 8;//设置x block 个数
//const float y_count = 10;// 设置y block 的个数

//const int block_count = 17; //图标的个数

const float banner_height = 100; //广告条的高度 

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
	CC_SYNTHESIZE(float,block_scale,blockScale);
	CC_SYNTHESIZE(int,block_count,blockCount);
	CC_SYNTHESIZE(float,max_level,maxLevel);

	//CC_SYNTHESIZE(int, next_level, NextLevel);

	void saveUserPassLevel();
	void initUserPassLevel();
	void passCurrentUserLevel();//当前关卡已过

	void initLevelData();
	void initLevelScale();

	void playOrStopMusic();
	void getLevelData(int level,float &x_count,float &y_count, int &grid_count,int &scope);
	std::vector<std::string> split(std::string str,std::string pattern);


private:
	GameData();
	void init();
	

private:
	static GameData* _instance;
	//int cur_level;
	//Array* level_data;
	std::vector<std::string> level_data;
	//int next_level;
};

#endif