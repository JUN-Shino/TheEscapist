
#include "Collect.h"
#include "macros.h"

USING_NS_CC;


Collect::Collect()
{
}

Collect::~Collect()
{
  this->removeAllChildren();
}

bool Collect::init()
{
    if(!Layer::init())
    {
        return false;
    }
    
    //シングルタップ用リスナーを用意する
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(_swallowsTouches);
    
    //各イベントの割当
    listener->onTouchBegan = CC_CALLBACK_2(Collect::onTouchBegan,this);
    listener->onTouchEnded = CC_CALLBACK_2(Collect::onTouchEnded, this);
    
    //イベントディスバッチャにシングルタップ用リスナーを追加する
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    createFrame();
    initMenu();
    createStRank();
    showCollect();
    
    return true;
}

bool Collect::onTouchBegan(Touch *touch, Event *unused_event)
{
    //タップ開始時の処理
    CCLOG("onTouchBegan");
    
    return true;
}


void Collect::onTouchEnded(Touch *touch, Event *unused_event)
{
    //タップ終了時の処理
    CCLOG("onTouchEnded");
}


void Collect::endCallback(Ref* pSender)
{
    Director::getInstance()->resume();
    
    this->removeFromParent();
}


void Collect::createFrame()
{
    auto frame = Sprite::create("frame.png");
    frame->setPosition(WINSIZE.width/2,WINSIZE.height/2);
    this->addChild(frame,Z_frame,T_frame);
}


void Collect::initMenu()
{
    Sprite* frame = (Sprite*)getChildByTag(T_frame);
    auto endItem = MenuItemImage::create("retry2.png",
                                         "retry2.png",
                                         CC_CALLBACK_1(Collect::endCallback,this));
    

    endItem->setPosition(Point(frame->getContentSize().width * 0.9 ,
                               frame->getContentSize().height * 0.2));
    
    
    auto menu = Menu::create(endItem,NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu);
    
}

void Collect::createStRank()
{
    //ランク名と取得済かどうかを判断し配列に代入
    
    for(int name_id = 0;name_id < 27; name_id++)
    {
        stRank stRank;
        
        //取得済か
        stRank.collect = SaveSQL::sqliteGetCollectForId(name_id);
        //ランク名
        stRank.collectRank = SaveSQL::sqliteGetRankForId(name_id);
        
        
        _rankArray.push_back(stRank);
    }
    
}


void Collect::showCollect()
{
    Sprite* frame = (Sprite*)getChildByTag(T_frame);
    int PosCount = 0;
    
    
    for(int name_id = 0;name_id < 27; name_id++)
    {
        
        auto collectLine = Label::createWithSystemFont("","Marker Felt", 35);
        
        if(name_id < 14)
        {
            collectLine->setPosition(Vec2(frame->getContentSize().width/2 - frame->getContentSize().width/4,
                                          frame->getContentSize().height - 32 * name_id));
        }
        
        else if(name_id < 27)
        {
            collectLine->setPosition(Vec2(frame->getContentSize().width/2 + frame->getContentSize().width/5,
                                          frame->getContentSize().height - 35 * PosCount));
            PosCount++;

        }
        
        switch (_rankArray[name_id].collect)
        {
            case 0 :
                collectLine->setColor(Color3B::RED);
                collectLine->setString(StringUtils::format("????"));
                _labelArray.push_back(collectLine);
                break;
                
            case 1:
                collectLine->setColor(Color3B::BLUE);
                collectLine->setString(StringUtils::format("(new)%s",_rankArray[name_id].collectRank));
                _labelArray.push_back(collectLine);
                SaveSQL::sqliteUpdateCollectForScore(_rankArray[name_id].collectRank,2);
                break;
                
            default:
                collectLine->setColor(Color3B::MAGENTA);
                collectLine->setString(StringUtils::format("%s",_rankArray[name_id].collectRank));
                _labelArray.push_back(collectLine);
                break;
        }
  
        this->addChild(_labelArray[name_id]);
    }

}



