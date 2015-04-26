#include "MyJniHelper.h"

void MyJniHelper::showBan(int adTag)
{  
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)   
		JniMethodInfo t;
		if (JniHelper::getStaticMethodInfo(t, CLASS_NAME, "showBan", "(I)V"))
		{   
			t.env->CallStaticVoidMethod(t.classID, t.methodID,adTag);
			t.env->DeleteLocalRef(t.classID);   
		}  
	#endif 
}
