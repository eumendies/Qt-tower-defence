#ifndef COIN_H
#define COIN_H

#include <QPushButton>
class Coin
{
public:
    Coin();
    int getMoney();
    void addMoney(int rewardMoney);
    void decMoney(int consumeMoney);
private:
    int sum;


};

#endif // COIN_H
