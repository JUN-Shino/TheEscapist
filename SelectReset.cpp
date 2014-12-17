#include "SelectReset.h"


USING_NS_CC;

SelectReset::SelectReset()
{
}

SelectReset::~SelectReset()
{
}


bool SelectReset::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //各イベントの割当
    listener->onTouchBegan = CC_CALLBACK_2(SelectReset::onTouchBegan,this);
    listener->onTouchEnded = CC_CALLBACK_2(SelectReset::onTouchEnded, this);
    
    //イベントディスバッチャにシングルタップ用リスナーを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    initBackground();
    selectButton();
    
    return true;
}


void SelectReset::initBackground()
{
    Label* question = Label::createWithSystemFont("社会復帰（スコアリセット）する？","Marker Felt", 60);
    question->setColor(Color3B::BLACK);
    question->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2 + WINSIZE.height/4));
    this->addChild(question,Z_Label);
    
    
    Sprite* Background = Sprite::create("frame.png");
    Background->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2));
    
    this->addChild(Background,Z_Background,T_Background);
}


bool SelectReset::onTouchBegan(Touch *touch, Event *unused_event)
{
    //タップ開始時の処理
    CCLOG("onTouchBegan");
    
    return true;
}


void SelectReset::onTouchEnded(Touch *touch, Event *unused_event)
{
    //タップ終了時の処理
    CCLOG("onTouchEnded");
}




void SelectReset::selectButton()
{
    //イエスボタン
    auto yesButton = MenuItemImage::create("btGreen.png",
                                           "btGreen.png",
                                           CC_CALLBACK_1(SelectReset::resetYes,this));
    yesButton->setPosition(Vec2(WINSIZE.width/4,WINSIZE.height/3));

    
    Label* yesLabel = Label::createWithSystemFont("復帰するか・・・","Marker Felt", 35);
    yesLabel->setColor(Color3B::BLACK);
    yesLabel->setPosition(yesButton->getPosition());
    this->addChild(yesLabel,Z_Label,T_Yes);
    
    
    //ノーボタン
    auto noButton = MenuItemImage::create("btGreen.png",
                                           "btGreen.png",
                                           CC_CALLBACK_1(SelectReset::resetNo,this));
    noButton->setPosition(Vec2(WINSIZE.width/2 + WINSIZE.width/4,WINSIZE.height/3));
  
    
    Label* noLabel = Label::createWithSystemFont("いやだ！！","Marker Felt", 35);
    noLabel->setColor(Color3B::BLACK);
    noLabel->setPosition(noButton->getPosition());
      this->addChild(noLabel,Z_Label,T_No);
    
    
    
    //戻るボタン
    Sprite* frame = (Sprite*)getChildByTag(T_Background);
    auto backButton = MenuItemImage::create("retry2.png",
                                         "retry2.png",
                                         CC_CALLBACK_1(SelectReset::backButton,this));
    
    backButton->setPosition(Point(frame->getContentSize().width * 0.9 ,
                               frame->getContentSize().height * 0.2));
    
    
    
    auto menu = Menu::create(yesButton,noButton,backButton,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,Z_Menu,T_Menu);
    
}

void SelectReset::resetYes(Ref* pSender)
{
    auto menuItem = (Menu*)getChildByTag(T_Menu);
    menuItem->setVisible(false);
    
    
    for(int name_id = 0;name_id < 27; name_id++)
    {
        const char * gameScoreRank = SaveSQL::sqliteGetRankForId(name_id);
        SaveSQL::sqliteUpdateCollectForScore(gameScoreRank,0);
    }
    
    auto resetScore = UserDefault::getInstance();
    resetScore->setIntegerForKey("gameScore", 0);
     resetScore->setIntegerForKey("highScore", 0);
    resetScore->flush();
    
    Label* complete = Label::createWithSystemFont("社会復帰しました！","Marker Felt", 60);
    complete->setColor(Color3B::BLUE);
    complete->setPosition(Vec2(WINSIZE.width/2,WINSIZE.height/2));
    this->addChild(complete,Z_Label);
    
    removeChildByTag(T_Yes);
    removeChildByTag(T_No);
    
    Director::getInstance()->resume();
    
    this->scheduleOnce(schedule_selector
                       (SelectReset::close), 1.0f );
    
}

void SelectReset::resetNo(Ref* pSender)
{
    Director::getInstance()->resume();
    
    this->removeFromParent();
}

void SelectReset::backButton(Ref* pSender)
{
    Director::getInstance()->resume();
    
    this->removeFromParent();
}

void SelectReset::close(float tm)
{
  
    this->removeFromParent();
}
