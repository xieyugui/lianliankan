#ifndef _LIANLIANKANX_MYJNIHELPER_H_
#define _LIANLIANKANX_MYJNIHELPER_H_

#include "cocos2d.h"  

USING_NS_CC; 

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)  
#include <jni.h>
#include "platform/android/jni/JniHelper.h"  
#define  CLASS_NAME "org/cocos2dx/cpp/AppActivity"  
#endif   

class MyJniHelper 
{  
	public: MyJniHelper();  
	 ~MyJniHelper(); 
	static void showBan(int adTag);
};

#endif
