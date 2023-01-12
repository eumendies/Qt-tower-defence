#ifndef MAP_H
#define MAP_H
#include<QMap>

// 存放各种信息的类
class Map
{
public:
    Map();
    bool buildTower(int index, int towerType);
    bool hasTower(int index);
    void deleteTower(int index);
    void upgradeTower(int index);
    int getTowerPosition(int towerIndex, QString x_Or_y);
    int getTowerIndex(int index);
    QMap<QString,int> towerType;
    bool ifUpgrade(int index);
    void setUpgrade(int index, bool ifUpgrade);
private:
    int tower[14] = {0};    // 全部赋初值为0，即没有塔
    int towerPositions[14][2];
    bool towerUpgrade[14] = {0};  // 记录需要升级的tower
};

#endif // MAP_H
