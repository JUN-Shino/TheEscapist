#ifndef __TheEscapist__Item__
#define __TheEscapist__Item__

#include "cocos2d.h"
#include <random>

class Item : public cocos2d::Sprite
{
    
//protected:
    int _itemType; //アイテムの種類
    
    cocos2d::Action* getAction1();
    cocos2d::Action* getAction2();
    cocos2d::Action* getAction3();
    
    
    std::mt19937 _mt; //乱数生成エンジン
    std::uniform_real_distribution<double> _height;
    std::uniform_real_distribution<double> _smallHeight;
    std::uniform_real_distribution<double> _bigHeight;
    
public:
    //アイテムのタイプ
    enum ItemType
    {
        Type1 = 1,
        Type2,
        Type3,
        
    };
    

    Item(int itemType); //コンストラクタ
    virtual bool init(); //初期化
    static Item* create(int itemType); //create関数
    
};

#endif /* defined(__TheEscapist__Item__) */