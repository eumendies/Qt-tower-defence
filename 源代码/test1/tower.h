#ifndef TOWER_H
#define TOWER_H
#include<QVector>
#include "enemy.h"
#include "map.h"
#include"someStruct.h"

class Tower
{
public:
    Tower(int index, Map* map);
    Tower();
    virtual void attack(QVector<Enemy*>& enemyVec, QVector<HitEffect*>& hitEffectVec);
    int getX();
    int getY();
    int getIndex();
    int getPower();
    virtual int getTowerType();
    virtual void upgrade();
protected:
    int index;
    int x,y;
    int power;
    int attackRange;
    Map* map;
    int towerType;
};

#endif // TOWER_H
