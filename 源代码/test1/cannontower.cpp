#include "cannontower.h"
#include<cmath>

// 用于计算tower和enemy距离的内联函数
inline double getDistance(int x1,int y1,int x2,int y2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

CannonTower::CannonTower(int index, Map* map)
{
    this->map = map;
    this->index = index;
    this->towerType = map->towerType["cannonTower"];
    this->power = 20;
    this->attackRange = 200;
    this->x = map->getTowerPosition(index,"x") + 40;
    this->y = map->getTowerPosition(index,"y") + 40;
}

void CannonTower::attack(QVector<Enemy*>& enemyVec, QVector<HitEffect*>& hitEffectVec)
{
    for(auto enemy:enemyVec)
    {
        // 若tower和enemy的距离小于攻击距离，则减少enemy的生命值并向hitEffectVec中插入攻击效果
        if(getDistance(this->x,this->y,enemy->getX(),enemy->getY()) < this->attackRange)
        {
            enemy->setHealth(enemy->getHealth() - this->power);
            hitEffectVec.push_back(new HitEffect(enemy->getX(),enemy->getY(),1,this->towerType));
            // 炮塔只攻击第一个enemy
            break;
        }
    }
}

void CannonTower::upgrade()
{
    this->towerType = map->towerType["cannonTower2"];
    this->power = this->power + 40;
    this->attackRange = this->attackRange + 40;
}

int CannonTower::getTowerType()
{
    return this->towerType;
}
