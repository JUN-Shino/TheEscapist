#ifndef __GitTutorial__SaveSQL__
#define __GitTutorial__SaveSQL__

#include "cocos2d.h"
#include "sqlite3.h"

class SaveSQL : public cocos2d::Node {
    
    
public:
    
    virtual  bool init();
    
    static int sqliteOpen(sqlite3 **db);
    static void sqliteCreateTable();

    static const char* sqliteGetRankForScore(int score);
    static const char* sqliteGetRankForId(int name_id);
   

    static void sqliteSetValueForKey();
    static void sqliteUpdateCollectForScore(std::string _rank,int No);
    
    static int sqliteGetCollectForRank(std::string _rank);
     static int sqliteGetCollectForId(int name_id);
    
};


#endif /* defined(__GitTutorial__SaveSQL__) */
