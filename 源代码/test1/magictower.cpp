#include "magictower.h"
#include<cmath>

inline double getDistance(int x1,int y1,int x2,int y2)
{
    return sqrt(pow(x1-x2,2)+pow(y1-y2,2));
}

MagicTower::MagicTower(int index, Map* map)
{
    this->map = map;
    this->index = index;
    this->towerType = map->towerType["magicTower"];
    this->power = 10;
    this->attackRange = 150;
    this->x = map->getTowerPosition(index,"x") + 40;
    this->y = map->getTowerPosition(index,"y") + 40;
}

void MagicTower::attack(QVector<Enemy*>& enemyVec, QVector<HitEffect*>& hitEffectVec)
{
    if(this->towerType != map->getTowerIndex(this->index))
    {
        upgrade();
    }
    for(auto enemy:enemyVec)
    {
        // 若tower和enemy的距离小于攻击距离，则减少enemy的生命值并向hitEffectVec中插入攻击效果
        if(getDistance(this->x,this->y,enemy->getX(),enemy->getY()) < this->attackRange)
        {
            enemy->setHealth(enemy->getHealth()-this->power);
            hitEffectVec.push_back(new HitEffect(this->x - 113,this->y - 113,1,this->towerType));
        }
    }
}

void MagicTower::upgrade()
{
    this->towerType = map->towerType["magicTower2"];
    this->power = this->power + 20;
}

int MagicTower::getTowerType()
{
    return this->towerType;
}
