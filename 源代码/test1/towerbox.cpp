#include "towerbox.h"
#include<QPushButton>
#include "map.h"
#include<QDebug>
#include<QMessageBox>
#include "coin.h"
#include "someStruct.h"

extern QVector<UpgradeEffect*>upEffectVec;

TowerBox::TowerBox(QWidget *parent, Map * map, Coin * coin, int index)
    : QWidget{parent},map(map),coin(coin),towerIndex(index)
{
    setWindowTitle("创建");
    resize(250,400);
    setFixedSize(250,400);
    QPushButton * Tower_1 = new QPushButton(this);
    Tower_1->resize(100,30);
    Tower_1->move(75,20);
    Tower_1->setText("法塔($100)");

    QPushButton * Tower_2 = new QPushButton(this);
    Tower_2->resize(100,30);
    Tower_2->move(75,120);
    Tower_2->setText("炮塔（$150）");

    QPushButton * Tower_3 = new QPushButton(this);
    Tower_3->resize(100,30);
    Tower_3->move(75,220);
    Tower_3->setText("拆除(+$50)");

    QPushButton * Tower_4 = new QPushButton(this);
    Tower_4->resize(100,30);
    Tower_4->move(75,320);
    Tower_4->setText("升级($300)");

    // 给按钮创建建造法塔的连接
    connect(Tower_1,&QPushButton::clicked,[=](){
        if(!map->hasTower(towerIndex))
        {
            if(coin->getMoney()>=100)
            {
                map->buildTower(towerIndex, map->towerType["magicTower"]);
                coin->decMoney(100);
                qDebug()<<"创建法塔";
                this->close();
            }
            else
            {
                QMessageBox::critical(nullptr,"警告","金钱不足，法塔创建失败！");
            }
        }
        else
        {
            QMessageBox::critical(nullptr,"警告","已建造，法塔创建失败！");
        }
    });

    connect(Tower_2,&QPushButton::clicked,[=](){
        if(!map->hasTower(towerIndex))
        {
            if(coin->getMoney()>=150)
            {
                map->buildTower(towerIndex, map->towerType["cannonTower"]);
                coin->decMoney(150);
                qDebug()<<"创建炮塔";
                this->close();
            }
            else
            {
                QMessageBox::critical(nullptr,"警告","金钱不足，炮塔创建失败！");
            }
        }
        else
        {
            QMessageBox::critical(nullptr,"警告","已建造，炮塔创建失败！");
        }
    });

    // 拆除tower的连接
    connect(Tower_3,&QPushButton::clicked,[=](){
        if(map->hasTower(towerIndex))
        {
            map->deleteTower(towerIndex);
            coin->addMoney(50);
            qDebug()<<"已拆除";
            this->close();
        }
        else
        {
            QMessageBox::critical(nullptr,"警告","未建造，拆除失败！");
        }
    });

    // 升级tower的连接
    connect(Tower_4,&QPushButton::clicked,[=](){
        if(map->hasTower(towerIndex))
        {
            if(coin->getMoney()>=300)
            {
                if(map->getTowerIndex(towerIndex)==map->towerType["magicTower"] || map->getTowerIndex(towerIndex)==map->towerType["magicTower2"])
                {
                    qDebug()<<"法塔升级";
                    map->upgradeTower(towerIndex);
                    upEffectVec.push_back(new UpgradeEffect(map->getTowerPosition(towerIndex,"x") + 20,
                                                            map->getTowerPosition(towerIndex,"y") + 20));
                    coin->decMoney(300);
                    this->close();
                }
                if(map->getTowerIndex(towerIndex)==map->towerType["cannonTower"] || map->getTowerIndex(towerIndex)==map->towerType["cannonTower2"])
                {
                    qDebug()<<"炮塔升级";
                    map->upgradeTower(towerIndex);
                    upEffectVec.push_back(new UpgradeEffect(map->getTowerPosition(towerIndex,"x") + 20,
                                                            map->getTowerPosition(towerIndex,"y") + 20));
                    coin->decMoney(300);
                    this->close();
                }
            }
            else
            {
                QMessageBox::critical(nullptr,"警告","金钱不足，升级失败！");
            }
        }
        else
        {
            QMessageBox::critical(nullptr,"警告","未建造，升级失败！");
        }
    });
}
