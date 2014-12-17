//
//  SaveSQL.cpp
//
//
//  Created by albatrus on 2014/06/10.
//
//

#include "SaveSQL.h"

#define dbName "Escapist.db"

USING_NS_CC;

//データベースを開く
int SaveSQL::sqliteOpen(sqlite3 **db){
    
    auto filePath = FileUtils::getInstance()->getWritablePath();
    filePath += dbName;
    
    
    return sqlite3_open(filePath.c_str(),db);
    
}



//データベースのテーブルの作成
void SaveSQL::sqliteCreateTable(){
    
    sqlite3 *db = NULL;
    if(sqliteOpen(&db) == SQLITE_OK){
        
        // key とvalueの２つ値がある テーブル(test1)を作成
        const char *sql_createtable = "CREATE TABLE rank(name_id INTEGER,judge_min INTEGER,judge_max INTEGER,rank_name TEXT NOT NULL,collect INTEGER)";
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_createtable, -1, &stmt, NULL) == SQLITE_OK) {
            
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                
                CCLOG("create table done");
            }
            
            sqlite3_reset(stmt);
        }
        sqlite3_finalize(stmt);
    }
    sqlite3_close(db);
}


void SaveSQL::sqliteSetValueForKey()
{

    sqlite3 *db = NULL;
    const char *sql_select;
    
    if (sqliteOpen(&db) == SQLITE_OK)
    {
        for (int count = 0 ; count < 27 ; count++)
        {
            switch (count)
            {
                    log("%d",count);
                case 0 : sql_select = "INSERT INTO rank VALUES(0,0, 30, '夏休みレベル',0)";break;
                case 1 : sql_select = "INSERT INTO rank VALUES(1,31, 60, 'MADOGIWA LAST BOY',0);";break;
                case 2 : sql_select = "INSERT INTO rank VALUES(2,61, 80, '居ない物扱い',0);";break;
                case 3 : sql_select = "INSERT INTO rank VALUES(3,81, 120, '骨折アピールマン',0);";break;
                case 4 : sql_select = "INSERT INTO rank VALUES(4,121, 150, '充電期間',0);";break;
                case 5 : sql_select = "INSERT INTO rank VALUES(5,151, 180, '夢追い系男子',0);";break;
                case 6 : sql_select = "INSERT INTO rank VALUES(6,181, 240, 'ハロワ皆勤賞',0);";break;
                case 7 : sql_select = "INSERT INTO rank VALUES(7,241, 365, '伝説の自宅浪人生',0);";break;
                case 8 : sql_select = "INSERT INTO rank VALUES(8,366, 405, 'モラトリアムクズ',0);";break;
                case 9 : sql_select = "INSERT INTO rank VALUES(9,406, 515, 'まだ本気出してないだけ',0);";break;
                case 10 : sql_select = "INSERT INTO rank VALUES(10,516, 730, '和製キ○ヌ•リーブス',0);";break;
                case 11 : sql_select = "INSERT INTO rank VALUES(11,731, 1095, 'ベーシスト（無職）',0);";break;
                case 12 : sql_select = "INSERT INTO rank VALUES(12,1096, 1460, 'ただ飯食らい',0);";break;
                case 13 : sql_select = "INSERT INTO rank VALUES(13,1461, 1825, '妖怪親泣かせ',0);";break;
                case 14 : sql_select = "INSERT INTO rank VALUES(14,1826, 2190, 'エリートオンラインゲーマー',0);";break;
                case 15 : sql_select = "INSERT INTO rank VALUES(15,2191, 2555, 'リビングデッド',0);";break;
                case 16 : sql_select = "INSERT INTO rank VALUES(16,2556, 3650, 'プロネットサーファー',0);";break;
                case 17 : sql_select = "INSERT INTO rank VALUES(17,3651, 4380, '自宅に巣食う者',0);";break;
                case 18 : sql_select = "INSERT INTO rank VALUES(18,4381, 5475, '親のスネかじり虫',0);";break;
                case 19 : sql_select = "INSERT INTO rank VALUES(19,5476, 6250, '職歴ホワイト',0);";break;
                case 20 : sql_select = "INSERT INTO rank VALUES(20,6251, 7300, '自宅寄生獣',0);";break;
                case 21 : sql_select = "INSERT INTO rank VALUES(21,7301, 8395, '末代',0);";break;
                case 22 : sql_select = "INSERT INTO rank VALUES(22,8396, 10950, '戦闘力５',0);";break;
                case 23 : sql_select = "INSERT INTO rank VALUES(23,10951, 18250, 'ヨットスクール強制入門',0);";break;
                case 24 : sql_select = "INSERT INTO rank VALUES(24,18251, 25550, 'ダンボールハウス経営',0);";break;
                case 25 : sql_select = "INSERT INTO rank VALUES(25,25551, 36500, '壁殴り仙人',0);";break;
                case 26 : sql_select = "INSERT INTO rank VALUES(26,36501, 99999, 'メシア',0);";break;
                default : break;
            }
            
            sqlite3_stmt *stmt = NULL;
            
            if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK)
            {
                if (sqlite3_step(stmt) == SQLITE_DONE)
                {
                    
                }
                sqlite3_reset(stmt);
            }
            sqlite3_finalize(stmt);
        }
    }
    sqlite3_close(db);
}


//keyから値を取り出す。
const char *SaveSQL::sqliteGetRankForScore(int score){
    
    __String *strValue = NULL;
    sqlite3 *db = NULL;
    if (sqliteOpen(&db) == SQLITE_OK) {
        
        //Escapist.dbテーブルからkeyに合わせたvalueを取り出す
        std::string sql_select = StringUtils::format("SELECT*FROM rank WHERE judge_min <= %d AND judge_max >= %d",score,score);
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_select.c_str(), -1, &stmt, NULL) == SQLITE_OK) {
            
            //sqlite3_bind_text(stmt, 1, key, -1, SQLITE_TRANSIENT);

            int ret = sqlite3_step(stmt);
            if (ret == SQLITE_DONE || ret == SQLITE_ROW) {
                
                const char *val = (const char*)sqlite3_column_text(stmt, 3);
                strValue = __String::create(val);
                
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
    
    //valueがある場合
    if (strValue != NULL) {
        
        return strValue->getCString();
        CCLOG("out");
    }
    
    return NULL;
}


const char *SaveSQL::sqliteGetRankForId(int name_id){

    __String *strValue = NULL;
    sqlite3 *db = NULL;
    if (sqliteOpen(&db) == SQLITE_OK) {
        
        //Escapist.dbテーブルからkeyに合わせたvalueを取り出す
        const char* sql_select = "SELECT*FROM rank WHERE name_id = ?";
        sqlite3_stmt *stmt = NULL;
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt, 1, name_id);
            
            int ret = sqlite3_step(stmt);
            if (ret == SQLITE_DONE || ret == SQLITE_ROW) {
                
                const char *val = (const char*)sqlite3_column_text(stmt, 3);
                strValue = __String::create(val);
                
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
    
    //valueがある場合
    if (strValue != NULL) {
        
        return strValue->getCString();
        CCLOG("out");
    }
    
    return NULL;
}






int SaveSQL::sqliteGetCollectForRank(std::string _rank){

    sqlite3 *db = NULL;
    
    int collect = 0;
    
    if (sqliteOpen(&db) == SQLITE_OK) {
        
        const char *sql_select = "SELECT*FROM rank WHERE rank_name = ? ";
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_text(stmt, 1, _rank.c_str(), -1, SQLITE_TRANSIENT);
            
            int ret = sqlite3_step(stmt);
            if (ret == SQLITE_DONE || ret == SQLITE_ROW) {
                
                collect = sqlite3_column_int(stmt, 4);
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
    if(collect != 0)
    {
        return collect;
        CCLOG("%d",collect);
    }
    
    
    return 0;
    
}


int SaveSQL::sqliteGetCollectForId(int name_id){
    
    sqlite3 *db = NULL;
    
    int collect = 0;
    
    if (sqliteOpen(&db) == SQLITE_OK) {
        
        const char *sql_select = "SELECT*FROM rank WHERE name_id = ? ";
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt, 1, name_id);
            
            int ret = sqlite3_step(stmt);
            if (ret == SQLITE_DONE || ret == SQLITE_ROW) {
                
                collect = sqlite3_column_int(stmt, 4);
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
    if(collect != 0)
    {
        return collect;
        CCLOG("%d",collect);
    }
    
    
    return 0;
    
}





//keyを元にValueの値を更新する
void SaveSQL::sqliteUpdateCollectForScore(std::string _rank,int No){
    
    sqlite3 *db = NULL;
    
    if (sqliteOpen(&db) == SQLITE_OK) {
        
        const char *sql_select = "UPDATE rank SET collect =? WHERE rank_name =? ";
        sqlite3_stmt *stmt = NULL;
        
        if (sqlite3_prepare_v2(db, sql_select, -1, &stmt, NULL) == SQLITE_OK) {
            
            sqlite3_bind_int(stmt, 1, No);
            sqlite3_bind_text(stmt, 2, _rank.c_str(), -1, SQLITE_TRANSIENT);
         
            if (sqlite3_step(stmt) == SQLITE_DONE) {
                
            }
            
            sqlite3_reset(stmt);
            
        }
        
        sqlite3_finalize(stmt);
        
    }
    
    sqlite3_close(db);
    
}





