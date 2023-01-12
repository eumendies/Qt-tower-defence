#ifndef TOWERBOX_H
#define TOWERBOX_H

#include <QWidget>
#include "map.h"
#include "coin.h"

class TowerBox : public QWidget
{
    Q_OBJECT
public:
    TowerBox(QWidget *parent = nullptr, Map * map = nullptr, Coin * coin = nullptr, int index=-1);
private:
    Map * map;
    Coin * coin;
    int towerIndex;  //这个消息框对应的炮塔

signals:

};

#endif // TOWERBOX_H
