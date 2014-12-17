#ifndef __TheEscapist__Obstacle__
#define __TheEscapist__Obstacle__

#include "cocos2d.h"
#include <random>

class Obstacle : public cocos2d::Sprite
{
public:
    //障害物のタイプ
    enum ObstacleType
    {
        Type1 = 1,
        Type2,
        Type3,
        Type4,
        Type5,
        Type6,
    };
    

private://protected:
    int _obstacleType; //障害物の種類
    
    cocos2d::Action* getAction1();
    cocos2d::Action* getAction2();
    cocos2d::Action* getAction3();
    cocos2d::Action* getAction4();
    cocos2d::Action* getAction5();
    cocos2d::Action* getAction6();
    
    std::mt19937 _mt;//乱数生成エンジン
    std::uniform_real_distribution<float> _height;
    std::uniform_real_distribution<float> _smallHeight;
    std::uniform_real_distribution<float> _bigHeight;
    std::uniform_real_distribution<float> type1and6;
    std::uniform_real_distribution<float> typeOther;

public:
    Obstacle(int obstacleType); //コンストラクタ
    virtual bool init(); //初期化
    static Obstacle* create(int obstaleType); //create関数
    
};



#endif /* defined(__TheEscapist__Obstacle__) */
