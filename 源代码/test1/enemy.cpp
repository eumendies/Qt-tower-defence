#include "enemy.h"
#include<QDebug>
#include<QTimer>
#include<ctime>
#include<QVector2D>
using namespace std;


Enemy::Enemy()
{
    //初始化起始位置、目前位置、目标位置
    this->startPoint = QPoint(786,90);
    this->currentPoint = this->startPoint;
    this->targetPoint = QPoint(85,90);
    //初始化生命上限、生命值
    this->orignalHealth = 1000;
    this->health = this->orignalHealth;
    //初始化移动速度
    this->speed = 1.0;
    // 初始化奖励金钱
    this->rewardMoney = 50;
    // 初始化怪物类型
    this->enemyType = 1;
}

Enemy::Enemy(int originalHealth, double speed, int enemyType)
{
    //初始化起始位置、目前位置、目标位置
    this->startPoint = QPoint(786,90);
    this->currentPoint = this->startPoint;
    this->targetPoint = QPoint(85,90);
    //初始化生命上限、生命值
    this->orignalHealth = originalHealth;
    this->health = this->orignalHealth;
    //初始化移动速度
    this->speed = speed;
    // 初始化奖励金钱
    this->rewardMoney = 30;
    //初始化怪物类型
    this->enemyType = enemyType;
}

//void Enemy::move()
//{
//    if (x>85 && y!=373) {
//        this->x = this->x - speed;
//        return;
//    }
//    if (y<373){
//        this->y = this->y + speed;
//        return;
//    }
//    if (x<786){
//        this->x = this->x + speed;
//        return;
//    }
//}

void Enemy::move(){
    //qDebug("move");
    double x0=currentPoint.x();
    double y0=currentPoint.y();
    if((x0<=85)&&(y0==90))
    {
     targetPoint=QPoint(85,373);
     startPoint=QPoint(85,90);
    }
    if((x0<=85)&&(y0>=373)){
        targetPoint=QPoint(786,373);
        startPoint=QPoint(85,373);
    }
    QVector2D vector(targetPoint-startPoint);
    vector.normalize();
    currentPoint=currentPoint+vector.toPoint()*speed;
    if(x0>=786){
        ;
    }
}

int Enemy::getX()
{
    return this->currentPoint.x();
    //return x;
}

int Enemy::getY()
{
    return this->currentPoint.y();
    //return y;
}

void Enemy::setHealth(int health)
{
    if(health<0){
        this->health = 0;
        return;
    }
    else this->health = health;
}

int Enemy::getHealth()
{
    return this->health;
}

int Enemy::getRewardMoney()
{
    return this->rewardMoney;
}

int Enemy::getOrignalHealth()
{
    return this->orignalHealth;
}
