
#include "NativeController_JNI.h"

#include "platform/android/jni/JniHelper.h"

//パッケージ名を指定
#define CLASS_NAME "org/cocos2dx/cpp/AppActivity"

extern "C"
{
    
    void sendJni(){
        
        cocos2d::JniMethodInfo methodInfo;
        
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,CLASS_NAME,"showBanner", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticObjectMethod(methodInfo.classID,methodInfo.methodID);
        
        
    }
    
    
    void sendJni2(){
        
        
        cocos2d::JniMethodInfo methodInfo;
        
        if (!cocos2d::JniHelper::getStaticMethodInfo(methodInfo,CLASS_NAME,"hideBanner", "()V"))
        {
            return;
        }
        
        methodInfo.env->CallStaticObjectMethod(methodInfo.classID,methodInfo.methodID);
        
        
        
    }
    
}