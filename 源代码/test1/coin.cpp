#include "coin.h"
#include "QDebug"
#include "QLabel"

Coin::Coin()
{
//    this->setIcon(QIcon(":/image/Coin0001.png"));
    sum = 250;
//    QPixmap pic;
//    bool ret_true =  pic.load(":/image/Coin0001.png");
//    if (!ret_true)
//    {
//        qDebug()<<"图片加载失败";
//        return;
//    }
//    // 按钮固定大小,缩放往往很有效
//    pic = pic.scaled(pic.width(),pic.height());
//    setFixedSize(pic.width()+100,pic.height());
//    // 设置不规则图片样式，语法同css,能创立自己图标本来的形状，如圆形，而不是长方形
//    setStyleSheet("QPushButton{border:0px;color:white;text-align:right;margin-left: 0px;}");
//    // 设置图标与大小
//    setIcon(pic);
//    setIconSize(QSize(pic.width(),pic.height()));

}

int Coin::getMoney()
{
    return sum;
}

void Coin::addMoney(int rewardMoney)
{
    sum = sum + rewardMoney;
}

void Coin::decMoney(int consumeMoney)
{
    sum = sum - consumeMoney;
}
