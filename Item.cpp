#include "Item.h"

USING_NS_CC;

//コンストラクタ
Item::Item(int itemType) : _itemType (itemType)
{
}

Item* Item::create(int itemType)
{
    auto item = new Item(itemType);
    item->init();
    item->autorelease();
    
    return item;
}

bool Item::init()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    std::random_device rd;
    _mt = std::mt19937(rd());
    
    
    //アイテムの移動範囲
    _height = std::uniform_real_distribution<double>(0.0, 1.0);
    _bigHeight = std::uniform_real_distribution<double>(0.6, 1.0);
    _smallHeight = std::uniform_real_distribution<double>(0.0, 0.5);
    
    std::string filename; //ファイル名
    Vec2 initPos; //初期位置
    Action* action; //障害物の動き
    
    switch (_itemType)
    {
        case Type1:
            filename = "book.png";
            initPos = Vec2(winSize.width * 1.1, winSize.height * 0.5);
            action = getAction1();
            break;
            
        case Type2:
            filename = "sports.png";
            initPos = Vec2(winSize.width * 1.1, winSize.height * 0.5);
            action = getAction2();
            break;
            
        case Type3:
            filename = "game.png";
            initPos = Vec2(winSize.width * 1.1, winSize.height * 0.5);
            action = getAction3();
            break;

    }
    
    if(!Sprite::initWithFile(filename))
    {
        return false;
    }
    //初期位置とアクションをセット
    setPosition(initPos);
    runAction(action);
    
    
    return true;
}

//Type1のアクション
Action* Item::getAction1()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    //移動アクションを生成
    auto move = MoveTo::create(3, Vec2(winSize.width * -0.1, winSize.height * _height(_mt)));
    auto remove = RemoveSelf::create();
    auto seq = Sequence::create(move, remove, NULL);
    
    return seq;
    
}

Action* Item::getAction2()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    //移動アクションを生成
    auto move = MoveTo::create(2, Vec2(winSize.width * -0.1, winSize.height * _height(_mt)));
    auto remove = RemoveSelf::create();
    auto seq = Sequence::create(move, remove, NULL);
    
    return seq;
}

Action* Item::getAction3()
{
    auto winSize = Director::getInstance()->getWinSize();
    
    //移動アクションを生成
    auto move = MoveTo::create(1, Vec2(winSize.width * -0.1, winSize.height * _height(_mt)));
    auto remove = RemoveSelf::create();
    auto seq = Sequence::create(move, remove, NULL);
    
    return seq;
}



