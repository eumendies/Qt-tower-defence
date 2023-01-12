#ifndef ENEMY_H
#define ENEMY_H
#include<QPoint>
#include<QPixmap>

class Enemy
{
public:
    Enemy();
    Enemy(int orignalHealth, double speed, int enemyType);
    void move();
    int getX();
    int getY();
    void setHealth(int health);
    int getHealth();
    int getRewardMoney();
    int getOrignalHealth();
    int enemyType;
    QPixmap enemyPixmap;
private:
    int orignalHealth;
    int health;
    QPoint startPoint;
    QPoint targetPoint;
    QPoint currentPoint;
    double speed;
    int rewardMoney; // 怪物死亡后给予玩家的金钱

};

#endif // ENEMY_H
