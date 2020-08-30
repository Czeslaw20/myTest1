#include "hero.h"
#include "fileManage.h"

//英雄的有参构造
Hero::Hero(int heroId)
{
    FileManager fm;
    map<string,map<string,string>>mHeroData;
    fm.loadCSVData("Hero.csv",mHeroData);

    //int -> string
    string temId=to_string(heroId);
    string id=mHeroData[temId]["heroId"];

    this->heroName=mHeroData[id]["heroName"];//英雄姓名
    this->heroAtk=atoi(mHeroData[id]["heroAtk"].c_str());//英雄攻击力
    this->heroDef=atoi(mHeroData[id]["heroDef"].c_str());//英雄防御力
    this->heroHp=atoi(mHeroData[id]["heroHp"].c_str());//英雄血量
    this->heroInfo=mHeroData[id]["heroInfo"];//英雄简介

    this->weapon=nullptr;//武器指针初始化为空
}
//英雄的攻击
void Hero::Attack(Monster * monster)
{
    int crit=0;
    int suck=0;
    int frozen=0;
    int damage=0;

    if(this->weapon==nullptr)
    {
        damage=this->heroAtk;
    }
    else
    {
        //伤害
        damage=this->heroAtk+weapon->getBaseDamage();

        //暴击
        crit=this->weapon->getCrit();

        //吸血
        suck=this->weapon->getSuckBlood();
        
        //冰冻
        frozen=this->weapon->getFrozen();

    }

    if(crit)//触发暴击
    {
        damage+=crit;
        cout<<"英雄的武器触发的暴击效果，怪物受到暴击伤害！"<<endl;
    }

    if(suck)//触发吸血
    {
        cout<<"英雄的武器触发的吸血效果，英雄增加血量："<<suck<<endl;
    }

    if(frozen)//触发暴击
    {
        cout<<"英雄的武器触发的冰冻效果，怪物<<"<<monster->monsterName<<">>停止攻击一回合"<<endl;
    }
    monster->isFrozen=frozen;//更新怪物冰冻效果
    this->heroHp+=suck;//更新回血数值
    int trueDamage=damage-monster->monsterDef;
    if(trueDamage<=0)
    {
        trueDamage=1;
    }

    monster->monsterHp-=trueDamage;

    cout<<"英雄"<<this->heroName<<">>攻击了怪物<<"<<monster->monsterName<<">>造成的伤害为："<<trueDamage<<endl;

} 
//装备武器
void Hero::EquipWeapon(Weapon * weapon)
{
    if(weapon==nullptr)//不装备武器
    {
        return;
    }

    this->weapon=weapon;
    cout<< "英雄<<"<<this->heroName<<">>装备了武器：" <<weapon->weaponName<<"!"<<endl;
}