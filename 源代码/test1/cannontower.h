#ifndef CANNONTOWER_H
#define CANNONTOWER_H

#include "tower.h"

class CannonTower : public Tower
{
public:
    CannonTower(int index, Map* map);
    void upgrade() override;
    void attack(QVector<Enemy*>& enemyVec, QVector<HitEffect*>& hitEffectVec) override;
    int getTowerType() override;
};

#endif // CANNONTOWER_H
