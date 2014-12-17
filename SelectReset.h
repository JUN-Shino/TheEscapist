#ifndef __TheEscapist2__SelectReset__
#define __TheEscapist2__SelectReset__

#include "cocos2d.h"
#include "SaveSQL.h"
#include "macros.h"


class SelectReset : public cocos2d::Layer
{
    enum Zorder
    {
        Z_Background = 0,
        Z_Menu,
        Z_Button,
        Z_Label,
    };
    
    enum Tag
    {
        T_Background,
        T_Menu,
        T_Yes,
        T_No
    };
    
    void initBackground();
    void selectButton();
    void resetYes(Ref* pSender);
    void resetNo(Ref* pSender);
    void backButton(Ref* pSender);
    void close(float tm);
    
public:
    SelectReset();
    virtual ~SelectReset();

    virtual bool init();
    CREATE_FUNC(SelectReset);

    virtual bool onTouchBegan(cocos2d::Touch *Touch, cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *Touch, cocos2d::Event *unused_event);

};


#endif /* defined(__TheEscapist2__SelectReset__) */
