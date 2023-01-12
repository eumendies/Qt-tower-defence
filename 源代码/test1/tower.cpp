#include "tower.h"
#include<cmath>
#include<QVector>
#include<QDebug>

// 用于计算tower和enemy距离的内联函数
inline double getDistance(int x1,int y1,int x2,int y2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

Tower::Tower()
{

}

Tower::Tower(int index, Map* map)
{
    this->map = map;
    this->index = index;
    // 从Map类中获取该tower的中心位置（用于计算与enemy的距离）
    this->x = map->getTowerPosition(index,"x") + 40;
    this->y = map->getTowerPosition(index,"y") + 40;
    // 从Map类中获得该tower的类型
    this->towerType = map->getTowerIndex(index);
    // 初始化攻击力、攻击范围
    this->power = 25;
    this->attackRange = 200;
}

void Tower::attack(QVector<Enemy*>& enemyVec, QVector<HitEffect*>& hitEffectVec)
{
    //升级tower
    if(this->towerType!=map->getTowerIndex(this->index))
    {
        this->towerType = map->getTowerIndex(this->index);
    }
    for(auto enemy:enemyVec)
    {
        // 若tower和enemy的距离小于攻击距离，则减少enemy的生命值并向hitEffectVec中插入攻击效果
        if(getDistance(this->x,this->y,enemy->getX(),enemy->getY()) < this->attackRange)
        {
            if(towerType==map->towerType["magicTower"] || towerType==map->towerType["magicTower2"])
            {
                enemy->setHealth(enemy->getHealth()-this->power);
                hitEffectVec.push_back(new HitEffect(this->x - 113,this->y - 113,1,this->towerType));
            }

            if(towerType==map->towerType["cannonTower"] || towerType==map->towerType["cannonTower2"])
            {
                enemy->setHealth(enemy->getHealth() - this->power);
                hitEffectVec.push_back(new HitEffect(enemy->getX(),enemy->getY(),1,this->towerType));
                // 炮塔只攻击第一个enemy
                break;
            }
        }
    }
}

int Tower::getX()
{
    return this->x;
}

int Tower::getY()
{
    return this->y;
}

int Tower::getIndex()
{
    return this->index;
}

void Tower::upgrade()
{

}

int Tower::getPower()
{
    return this->power;
}

int Tower::getTowerType()
{

}
