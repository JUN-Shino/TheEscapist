#ifndef __TheEscapist__Collect__
#define __TheEscapist__Collect__

#include "cocos2d.h"
#include "SaveSQL.h"


USING_NS_CC;

class Collect : public cocos2d::Layer
{
    enum Zorder
    {
        Z_frame,
    };
    
    enum Tag
    {
        T_frame,
    };
    
    struct stRank
    {
        int collect;
        const char* collectRank;
//        float x;
//        float y;
    };
    
protected:
    void initMenu();
    void showCollect();
    void createFrame();
    void createStRank();
    void endCallback(Ref* pSender);
    
    std::vector<stRank> _rankArray;
    std::vector<Label*> _labelArray;
  
    
   // const char *collectRank;
    
public:
    Collect();
    virtual ~Collect();
    
    virtual bool init();
    CREATE_FUNC(Collect);
    
    virtual bool onTouchBegan(cocos2d::Touch *Touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *Touch, cocos2d::Event *unused_event);

};


#endif /* defined(__TheEscapist__Collect__) */
