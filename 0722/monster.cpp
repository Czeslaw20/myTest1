#include "monster.h"
#include "fileManage.h"

//有参构造
Monster::Monster(int monsterId)
{
    FileManager fm;
    map<string,map<string,string>>mMonsterData;
    fm.loadCSVData("Monsters.csv",mMonsterData);

    string tmpId=to_string(monsterId);
    //怪物ID号
    string id=mMonsterData[tmpId]["monsterId"];

    this->monsterName=mMonsterData[id]["monsterName"];//怪物姓名
    this->monsterAtk=atoi(mMonsterData[id]["monsterAtk"].c_str());//攻击力
    this->monsterDef=atoi(mMonsterData[id]["monsterDef"].c_str());//防御力
    this->monsterHp=atoi(mMonsterData[id]["monsterHp"].c_str());//血量

    this->isFrozen=false;//冰冻状态
}

//怪物攻击函数
void Monster::Attack(Hero * hero)
{
    if(this->isFrozen)
    {
        cout<<"怪物<<"<<this->monsterName<<">>被冰冻了，本回合无法攻击<<"<<"!"<<endl;
        return;
    }

    //计算伤害
    int damage=this->monsterAtk-hero->heroDef;
    if(damage<=0)
    {
        damage=1;
    }

    //英雄掉血
    hero->heroHp-=damage;

    cout<<"怪物<<"<<this->monsterName<<">>攻击了英雄<<"<<hero->heroName<<">>造成的伤害为："<<damage<<"!"<<endl;
}