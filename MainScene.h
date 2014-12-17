#ifndef __TheEscapist__MainScene__
#define __TheEscapist__MainScene__

#include "cocos2d.h"
#include "Obstacle.h"
#include "item.h"
#include <random>

USING_NS_CC;

class MainScene : public cocos2d::Layer
{
    //Zオーダー
    enum ZOrder
    {
        Z_Bg = 0,
        Z_Obstscle,
        Z_Item,
        Z_Player,
        Z_Score,
        Z_GameStartLayer,
        Z_gameOverLayer,
        Z_Title,
    
    };
    
    enum class State
    {
        GameStart,
        Gaming,
        GameOver,
    };


    enum Tag
    {
        T_BG1 = 0,
        T_BG2,
        T_Obstacle,
        T_Player,
        T_Item1 = 901,
        T_Item2 = 902,
        T_Item3 = 903,
        T_label = 4,
        T_Start,
        T_Title,
    };
    
    //障害物の設定
    struct ObstacleConfig
    {
        int obstacleType; //障害物の種類
        //float appearanceTime; //出現時間
    };
    
    std::mt19937 _mt; //乱数生成エンジン
    std::uniform_int_distribution<> _obtype;
    std::uniform_int_distribution<> _itemType;
    
    
    Sprite* backgrounds1;
    Sprite* backgrounds2;
    //Sprite* _player;
    //スコア表示
    int _score;
    State _state;
    float _time; //ゲーム時間
    float _jumpingTime;
    float _jumpPointY;
    float _nextObstacleTime;
    float _nextItemTime;    
    float _plusPoint;
    
    ObstacleConfig _obstacleConfigs;
    Obstacle* _obstacle;
    Item* _item;
    
    void initBackground(); //背景の表示
    void initPlayer();
    void initScore(); //障害物設定の初期化
    void showObstacle();//障害物を表示する
    void showItem();
    bool contactObstacle(); //当たり判定
    void contactItem();
    void toGameOverScene(float delayTime);
  

    // ゲームオーバー時シーン切り替え
    
    void ScoreSave();
   
  
public:
    
    MainScene();
    virtual ~MainScene();
    
    static cocos2d::Scene* createScene(); //シーンを作成
    virtual bool init(); //初期化
    CREATE_FUNC(MainScene); //create関数作成
    
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt); //毎フレーム処理

    void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches,cocos2d::Event *event);
    
    //virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
};

#endif // __MAIN_SCENE_H__
