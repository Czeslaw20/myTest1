#include "dragonSword.h"
#include "fileManage.h"

DragonSword::DragonSword()
{
    //给属性初始化

    //获取基础伤害
    FileManager fm;
    map<string,map<string,string>>mWeaponData;
    fm.loadCSVData("Weapons.csv",mWeaponData);

    string id=mWeaponData["3"]["weaponId"];

    this->weaponName=mWeaponData[id]["weaponName"];//武器名称
    //string    ->   char *    ->     int
    //        .c_str          atoi()
    this->baseDamage=atoi(mWeaponData[id]["weaponAtk"].c_str());//武器伤害
    this->critPlus=atoi(mWeaponData[id]["weaponCritPlus"].c_str());//武器暴击系数
    this->critRate=atoi(mWeaponData[id]["weaponCritRate"].c_str());//武器暴击率
    this->suckPlus=atoi(mWeaponData[id]["weaponSuckPlus"].c_str());//武器吸血系数
    this->suckRate=atoi(mWeaponData[id]["weaponSuckRate"].c_str());//武器吸血率
    this->frozenRate=atoi(mWeaponData[id]["weaponFrozenRate"].c_str());//武器冰冻率
}

//获取基础伤害
int DragonSword::getBaseDamage()
{
    return this->baseDamage;
}

//获取暴击
int DragonSword::getCrit()
{
    if(isTrigger(this->critRate))
    {
        return this->baseDamage * this->critPlus;
    }
    else
    {
        return 0;
    }
}

//获取吸血 
int DragonSword::getSuckBlood()
{
    if(isTrigger(this->suckRate))
    {
        return this->baseDamage * this->suckPlus;
    }
    else
    {
        return 0;
    }
}

//冰冻效果 
int DragonSword::getFrozen()
{
    if(isTrigger(this->frozenRate))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//是否触发
bool DragonSword::isTrigger(int rate)
{
    int num=rand()%100+1;//1~100
    if(num<=rate)
    {
        return true;
    }
    return false;
}