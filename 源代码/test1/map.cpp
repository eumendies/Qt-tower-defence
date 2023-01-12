#include "map.h"
#include<QFile>
#include<QTextStream>
#include<QChar>
#include<QStringList>

Map::Map()
{
    // 初始化towerType的映射
    this->towerType["noTower"] = 0;
    this->towerType["magicTower"] = 1;
    this->towerType["cannonTower"] = 2;
    this->towerType["magicTower2"] = 3;
    this->towerType["cannonTower2"] = 4;

    //获取塔的像素位置
    QFile file(":/button_position.txt");
    QTextStream in(&file);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        return;
    }

    // 读取文件中的位置坐标
    QString positions = in.readAll();
    positions = positions.replace(QChar('\n'),QChar(' '));
    QStringList positionList = positions.split(' ');

    for(int i = 0; i < 28;)
    {
        towerPositions[i/2][0] = positionList.at(i).toLocal8Bit().toInt();
        towerPositions[i/2][1] = positionList.at(i+1).toLocal8Bit().toInt();
        i = i + 2;
    }
}

// 建造塔，成功返回true
bool Map::buildTower(int index, int towerType)
{
    if(tower[index]==0)
    {
        tower[index] = towerType;
        return true;
    }
    else
    {
        return false;
    }
}

// 判断某个位置是否有塔，有则返回true
bool Map::hasTower(int index)
{
    if(tower[index]!=0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// 删除塔
void Map::deleteTower(int index)
{
    tower[index] = 0;
}

// 获取某个塔的x坐标或y坐标
int Map::getTowerPosition(int towerIndex, QString x_Or_y)
{
    if(x_Or_y == "x")
    {
        return this->towerPositions[towerIndex][0];
    }
    if(x_Or_y == "y")
    {
        return this->towerPositions[towerIndex][1];
    }
}

// 获取tower的类型
int Map::getTowerIndex(int index)
{
    return tower[index];
}

void Map::upgradeTower(int index)
{
    if(tower[index]==towerType["magicTower"])
    {
        tower[index]=towerType["magicTower2"];
        towerUpgrade[index] = true;
    }
    if(tower[index]==towerType["cannonTower"])
    {
        tower[index]=towerType["cannonTower2"];
        towerUpgrade[index] = true;
    }
    if(tower[index]==towerType["magicTower2"] || tower[index]==towerType["cannonTower2"])
    {
        towerUpgrade[index] = true;
    }
}

bool Map::ifUpgrade(int index)
{
    return towerUpgrade[index];
}

void Map::setUpgrade(int index, bool ifUpgrade)
{
    towerUpgrade[index] = ifUpgrade;
}
