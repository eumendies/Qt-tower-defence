#ifndef MAGICTOWER_H
#define MAGICTOWER_H
#include"tower.h"


class MagicTower:public Tower
{
public:
    MagicTower(int index, Map* map);
    void attack(QVector<Enemy*>& enemyVec, QVector<HitEffect*>& hitEffectVec) override;
    void upgrade() override;
    int getTowerType() override;
};

#endif // MAGICTOWER_H
