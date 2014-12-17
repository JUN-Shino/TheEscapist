
#import "NativeController.h"
#include "AppController.h"
#include <cocos2d.h>


static void static_sendJNI()
{
  
   AppController *appController =
    (AppController*)[UIApplication sharedApplication].delegate;
    [appController showAdView];
   
}

static void static_sendJNI2()
{
    AppController *appController =
    (AppController*)[UIApplication sharedApplication].delegate;
    [appController hideAdView];
    
}



#pragma mark -
namespace Cocos2dxExt
{
    
    void NativeController::sendJNI()
    {
        
        static_sendJNI();
        
    }
    void NativeController::sendJNI2()
    {
        
        static_sendJNI2();
        
    }
    
    
}