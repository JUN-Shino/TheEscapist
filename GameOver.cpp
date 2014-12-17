
#include "GameOver.h"
#include "MainScene.h"
#include "macros.h"
#include "NativeController.h"

USING_NS_CC;

GameOver::GameOver()
: _showhighScore(0)
, _showScore(0)
{
}

GameOver::~GameOver()
{
    this->removeAllChildren();
}

Scene* GameOver::createScene()
{
    auto scene = Scene::create();
    auto layer = GameOver::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameOver::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
   
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    
    //各イベントの割当
    listener->onTouchBegan = CC_CALLBACK_2(GameOver::onTouchBegan,this);
    listener->onTouchEnded = CC_CALLBACK_2(GameOver::onTouchEnded, this);
    
    //イベントディスバッチャにシングルタップ用リスナーを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

void GameOver::onEnter()
{
    Layer::onEnter();
    
    
    //背景を表示
    initBackground();
    
    initMenu();
    
    initShowScore();
    
}

void GameOver::onExit()
{
    Layer::onExit();
}

void GameOver::initBackground()
{
    //背景の生成
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
    this->addChild(background,Z_Bg);
    
    auto whiteFrame = Sprite::create("whiteFrame.png");
    whiteFrame->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
    this->addChild(whiteFrame,Z_Frame);
    
}

void GameOver::initMenu()
{
    //戻るボタンとやめるボタンの実装
    auto retryItem = MenuItemImage::create("retry.png",
                                           "retry.png",
                                           CC_CALLBACK_1(GameOver::menuRetryCallback,this));
    retryItem->setPosition(Vec2(WINSIZE.width / 2 , WINSIZE. height * 0.3));
    
    
    auto scoreReset = MenuItemImage::create("btOrange.png",
                                           "btOrange.png",
                                           CC_CALLBACK_1(GameOver::menuResetCallback,this));
    
    scoreReset->setPosition(Vec2(WINSIZE.width * 0.8, WINSIZE. height * 0.35));
    auto ResetLabel = Label::createWithSystemFont(" 社会復帰（スコアリセット）","Marker Felt", 25);
    ResetLabel->setPosition(scoreReset->getPosition());
    ResetLabel->setColor(Color3B::BLUE);

    this->addChild(ResetLabel,Z_Label);
    

    
    auto collectItem = MenuItemImage::create("btOrange.png",
                                         "btOrange.png",
                                         CC_CALLBACK_1(GameOver::collectCallback,this));

    collectItem->setPosition(Vec2(WINSIZE.width * 0.8, WINSIZE. height * 0.25));
    
    auto collectLabel = Label::createWithSystemFont("飛行の軌跡(実績）","Marker Felt", 30);
    collectLabel->setPosition(collectItem->getPosition());
    collectLabel->setColor(Color3B::BLUE);
    
    this->addChild(collectLabel,Z_Label);
    
    
    //menuに登録
    auto menu = Menu::create(retryItem,scoreReset,collectItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,Z_Menu);
    
    
}


void GameOver::initShowScore()
{
    auto _user = UserDefault::getInstance();
    
    int sqlFlag = _user->getIntegerForKey("sqlFlag");
    
    if(sqlFlag == 0){
        SaveSQL::sqliteCreateTable();
        SaveSQL::sqliteSetValueForKey();
        _user->setIntegerForKey("sqlFlag", 1);
    }
    
    //今回のスコアを取り出す
   
    int _showScore = _user->getIntegerForKey("gameScore");
    
    //ハイスコアを取り出す
    int _showhighScore = _user->getIntegerForKey("highScore");
    
    //今回のスコアからランクを呼び出す（SQliteを使用）
    const char * gameScoreRank = SaveSQL::sqliteGetRankForScore(_showScore);
    const char * highScoreRank = SaveSQL::sqliteGetRankForScore(_showhighScore);
    
    
    //実績アップデート
    int _collect = SaveSQL::sqliteGetCollectForRank(gameScoreRank);
    CCLOG("collectNO %d",_collect);
    
    if(_collect==0)
    {
            //まだ取得したことのないランクだった場合
        SaveSQL::sqliteUpdateCollectForScore(gameScoreRank,1);
    }
    
    //スコア表示
    auto scoreLabel = Label::createWithSystemFont("","Marker Felt", 48);
    scoreLabel->setPosition(Point(WINSIZE.width * 0.5, WINSIZE.height * 0.9));
    scoreLabel->setColor(Color3B::WHITE);
    scoreLabel->enableOutline(Color4B::BLACK,5);
    this->addChild(scoreLabel,Z_Label);
    
    scoreLabel->setString(StringUtils::format("現実逃避日数 : %d 日 \n現実逃避年数 : %d 年 %d 日", _showScore, _showScore/365, _showScore%365));
    
    
    //ランク表示
    auto rankLabel = Label::createWithSystemFont("","Marker Felt", 50);
    rankLabel->setPosition(Point(WINSIZE.width * 0.5, WINSIZE.height * 0.5));
    rankLabel->setColor(Color3B::MAGENTA);
    rankLabel->enableOutline(Color4B::BLACK,5);
    
    this->addChild(rankLabel,Z_Label);
    
    rankLabel->setString(StringUtils::format("ランク : %s", gameScoreRank));
 
    
    //ハイスコアandランク表示
    auto scoreLabel2 = Label::createWithSystemFont("","Marker Felt", 30);
    scoreLabel2->setPosition(Point(WINSIZE.width * 0.7, WINSIZE.height * 0.7));
    scoreLabel2->setColor(Color3B::RED);
    
    this->addChild(scoreLabel2,Z_Label);
    
    scoreLabel2->setString(StringUtils::format("最高逃避日数 : %d 日 \n最高現実逃避年数 : %d 年 %d 日 \n ランク : %s", _showhighScore, _showhighScore/365, _showhighScore%365, highScoreRank));
}



bool GameOver::onTouchBegan(Touch *touch, Event *unused_event)
{
    //タップ開始時の処理
    CCLOG("onTouchBegan");
    
    return true;
}


void GameOver::onTouchEnded(Touch *touch, Event *unused_event)
{
    //タップ終了時の処理
    CCLOG("onTouchEnded");
}


void GameOver::menuRetryCallback(Ref* pSender)
{
    //新しく画面を用意する
    auto scene = MainScene::createScene();
    
    //フェードアニメーションの設定
    auto tran = TransitionFade::create(1, scene);
    
    //新しい画面に画面遷移する
    Director::getInstance()->replaceScene(tran);
}


void GameOver::menuResetCallback(Ref* pSender)
{
    Director::getInstance()->pause();
    
    Layer* selectLayer = SelectReset::create();
    
    this->addChild(selectLayer,Z_PopFrame);
}


void GameOver::collectCallback(Ref* pSender)
{
    Director::getInstance()->pause();
    
    Layer* modalLayer = Collect::create();
    
    this->addChild(modalLayer,Z_PopFrame);
}
