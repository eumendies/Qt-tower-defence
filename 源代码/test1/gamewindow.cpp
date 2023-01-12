#include "gamewindow.h"
#include "towerbox.h"
#include<QPixmap>
#include<QPainter>
#include<QToolBar>
#include<QPushButton>
#include<QAction>
#include<QMenu>
#include<QMenuBar>
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<QChar>
#include<QStringList>
#include<QTimer>
#include<QVector>
#include "enemy.h"
#include"someStruct.h"
#include"tower.h"
#include<QLabel>
#include<QUrl>
#include<QEventLoop>
#include "magictower.h"
#include "cannontower.h"
#include "coin.h"

// 保存enemy的向量
QVector<Enemy*> enemyVec;
// 攻击效果的向量
QVector<HitEffect*> hitEffectVec;
// 升级效果的向量
QVector<UpgradeEffect*> upEffectVec;
// 玩家的生命值
int playerHealth = 10;
// 创建地图类
Map map;
// 创建金币类
Coin coin;
// tower的指针数组
Tower* towerlist[14];
//怪物相关时间计数量
int enemyTimeCount=0;
//游戏结束过后用于时延的QTimer
QTimer* timer4;
GameWindow::GameWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置窗口大小
    resize(850,530);
    setFixedSize(850,530);
    GameIcon.addFile(":/image/gameIcon.ico");
    setWindowIcon(GameIcon);
    setWindowTitle("开始战斗");

    //设置bgm喀秋莎，可单曲循环
    bgm2.addMedia(QUrl("qrc:/sound/Katyusha.mp3"));
    playbgm2.setPlaylist(&bgm2);
    playbgm2.setVolume(30);
    playbgm2.play();

    //创建菜单栏
    QMenuBar * bar = menuBar();
    setMenuBar(bar);

    //创建暂停游戏和继续游戏按钮
    QAction * pauseAction = bar->addAction("暂停");
    pauseAction->setIcon(QIcon(":/image/pause.jpg"));
    QAction * continueAction = bar->addAction("继续");
    continueAction->setIcon(QIcon(":/image/continue.jpg"));

    // 金钱标签
    QLabel* moneyLabel = new QLabel(this);
    moneyLabel->move(10,25);
    moneyLabel->setFont(QFont("黑体", 10));
    moneyLabel->setStyleSheet("background:white;");
    moneyLabel->setText(QString("金钱：%1").arg(coin.getMoney()));

    //生命标签
    QLabel* lifeLabel = new QLabel(this);
    lifeLabel->move(10,50);
    lifeLabel->setFont(QFont("黑体", 10));
    lifeLabel->setStyleSheet("background:white;");
    lifeLabel->setText(QString("生命：%1").arg(playerHealth));

    //设置是否胜利标签
    isWin = UNKNOWN;

    // 设置创建炮塔的透明按钮
    setTowerButton();


    //用于添加怪物的定时器
    timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout,[=](){
        enemyTimeCount++;
        qDebug()<<enemyTimeCount;
        addEnemy1();
        addEnemy2();
        addEnemy3();
        // 删除升级效果
        for(auto upgradeIt = upEffectVec.begin(); upgradeIt != upEffectVec.end(); upgradeIt++)
        {
            if((*upgradeIt)->beShowed)
            {
                delete *upgradeIt;
                upEffectVec.erase(upgradeIt);
                if(upEffectVec.isEmpty())
                {
                    break;
                }
            }
        }

        if(enemyVec.isEmpty())
        {
            if(enemyTimeCount>211)
            {
                isWin = WIN;
            }
        }
    });

    //用于移动怪物的定时器
    timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout,[=](){
        // 在此更新money数量，因为可能由于创建tower导致money数值变化
        moneyLabel->setText(QString("金钱：%1").arg(coin.getMoney()));
        for(auto enemyIt=enemyVec.begin();enemyIt!=enemyVec.end();enemyIt++)
        {
            //若enemy走到终点，则玩家生命减一，并删除该enemy
            if((*enemyIt)->getX()>=786 && (*enemyIt)->getY()>=373)
            {
                playerHealth--;
                lifeLabel->setText(QString("生命：%1").arg(playerHealth));
                if(playerHealth==0)
                {
                    isWin = DEFEATED;
                }
                delete *enemyIt;
                enemyVec.erase(enemyIt);
                if(enemyVec.isEmpty())
                {
                    break;
                }
            }
            //若enemy生命为0则删除该enemy并给玩家添加金钱
            else if((*enemyIt)->getHealth() == 0)
            {
                coin.addMoney((*enemyIt)->getRewardMoney());
                moneyLabel->setText(QString("金钱：%1").arg(coin.getMoney()));
                delete *enemyIt;
                enemyVec.erase(enemyIt);
                //若删除了最后一个enemy则退出循环，防止访问非法内存导致崩溃
                if(enemyVec.isEmpty())
                {
                    break;    
                }
                if(enemyIt==enemyVec.end())
                {
                    break;
                }
            }
            else (*enemyIt)->move();
        }
        update();
    });

    timer3 = new QTimer(this);
    connect(timer3,&QTimer::timeout,[=](){
        // 定时检查是否建造了tower，若建造了则new出tower的对象；若拆除了则delete掉已有的对象
        for(int i=0;i<14;i++)
        {
            if(map.hasTower(i) && towerlist[i]==NULL){
                //towerlist[i] = new Tower(i, &map);
                if(map.getTowerIndex(i)==map.towerType["magicTower"])
                {
                    towerlist[i] = new MagicTower(i, &map);
                }
                if(map.getTowerIndex(i) == map.towerType["cannonTower"])
                {
                    towerlist[i] = new CannonTower(i, &map);
                }
            }
            else if(!map.hasTower(i) && towerlist[i]!=NULL){
                delete towerlist[i];
                towerlist[i] = nullptr;
            }
            // 若有tower且已创建了对象，则进行升级或攻击动作
            else if(map.hasTower(i) && towerlist[i]!=NULL){
                if(map.ifUpgrade(i))
                {
                    towerlist[i]->upgrade();
                    map.setUpgrade(i, false);
                }
                towerlist[i]->attack(enemyVec,hitEffectVec);
            }
        }

        //显示击中效果
        for(auto hit = hitEffectVec.begin(); hit != hitEffectVec.end(); hit++)
        {

            if((*hit)->index <=5 && ((*hit)->type==map.towerType["magicTower"]||(*hit)->type==map.towerType["magicTower2"])){
                (*hit)->index++;
            }
            if((*hit)->index <=7 && ((*hit)->type==map.towerType["cannonTower"]||(*hit)->type==map.towerType["cannonTower2"])){
                (*hit)->index++;
            }
        }

        //删除击中效果
        for(auto hit = hitEffectVec.begin(); hit != hitEffectVec.end(); hit++){
            if((*hit)->type==1 && (*hit)->index >= 6)
            {
                delete *hit;
                hitEffectVec.erase(hit);
                if(hit==hitEffectVec.end())
                {
                    break;
                }
            }
            if((*hit)->type==2 && (*hit)->index >= 8)
            {
                delete *hit;
                hitEffectVec.erase(hit);
                if(hit==hitEffectVec.end())
                {
                    break;
                }
            }
        }

        update();
    });

    timer4 = new QTimer(this);
    connect(timer4, &QTimer::timeout,[=](){
        emit gameOver();
    });

    connect(this,&GameWindow::gameOver,[=](){
        this->close();
    });

    connect(pauseAction,&QAction::triggered,[=](){
        qDebug()<<"暂停";
        timer1->stop();
        timer2->stop();
        timer3->stop();
    });

    connect(continueAction,&QAction::triggered,[=](){
        qDebug()<<"继续";
        timer1->start(1000);
        timer2->start(20);
        timer3->start(150);
    });
}

GameWindow::~GameWindow()
{
    for(int i = 0;i < 14;i++)
    {
        delete towerlist[i];
        towerlist[i] = nullptr;
    }

    for(auto it = enemyVec.begin();it!=enemyVec.end();it++)
    {
        delete *it;
        it = nullptr;
    }
    enemyVec.clear();

    for(auto it = hitEffectVec.begin();it!=hitEffectVec.end();it++)
    {
        delete *it;
        it = nullptr;
    }
    hitEffectVec.clear();

    for(auto it = upEffectVec.begin();it!=upEffectVec.end();it++)
    {
        delete *it;
        it = nullptr;
    }
    upEffectVec.clear();
}

void GameWindow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.drawPixmap(0,13,QPixmap(":/image/map.jpg"));
    painter.drawPixmap(766,373,80,80,QPixmap(":/image/home.png"));

    drawTower(painter);
    drawHitEffect(painter);
    drawEnemy(painter);
    drawUpgradeEffect(painter);
    drawGameOver(painter);
}

void GameWindow::setTowerButton()
{
    //在岩石地设置不可见的按钮，用于创建炮塔
    QPushButton * towerButton[14];
    TowerBox * towerBox[14];

    // 创建按钮
    for (int i = 0;i < 14;i++)
    {
        towerButton[i] = new QPushButton(this);
        towerButton[i]->resize(80,80);
        towerButton[i]->move(map.getTowerPosition(i,"x"),map.getTowerPosition(i,"y"));
        towerButton[i]->setCursor(QCursor(Qt::PointingHandCursor));
        // 将按钮设置为透明
        towerButton[i]->setStyleSheet("QPushButton{border:none;background:transparent;}");

        // 创建建造炮塔时的消息框
        // 所有消息框共用同一份地图类
        towerBox[i] = new TowerBox(nullptr,&map,&coin,i);
        connect(towerButton[i],&QPushButton::clicked,[=](){
            towerBox[i]->show();
        });

        // 游戏窗口关闭时消息框也关闭
        connect(this,&GameWindow::windowClose,towerBox[i],[=](){
            towerBox[i]->close();
            playbgm2.stop();
        });
    }
}

void GameWindow::drawTower(QPainter& painter)
{
    for(int i = 0;i < 14;i++)
    {
        if(map.hasTower(i))
        {
            // 根据tower的类型来画出tower的图片
            if(map.getTowerIndex(i)==map.towerType["magicTower"])
            {
                painter.drawPixmap(map.getTowerPosition(i,"x"),map.getTowerPosition(i,"y"),80,80,QPixmap(":/image/magicTower.png"));
            }

            if(map.getTowerIndex(i)==map.towerType["cannonTower"])
            {
                painter.drawPixmap(map.getTowerPosition(i,"x"),map.getTowerPosition(i,"y"),80,80,QPixmap(":/image/cannonTower.png"));
            }

            if(map.getTowerIndex(i)==map.towerType["magicTower2"])
            {
                painter.drawPixmap(map.getTowerPosition(i,"x"),map.getTowerPosition(i,"y"),80,80,QPixmap(":/image/magicTower_2.png"));
            }

            if(map.getTowerIndex(i)==map.towerType["cannonTower2"])
            {
                painter.drawPixmap(map.getTowerPosition(i,"x"),map.getTowerPosition(i,"y"),80,80,QPixmap(":/image/cannonTower_2.png"));
            }
        }
    }
}

void GameWindow::drawHitEffect(QPainter& painter)
{
    for(auto hitEffectIt = hitEffectVec.begin(); hitEffectIt!=hitEffectVec.end(); hitEffectIt++)
    {
        if((*hitEffectIt)->type==map.towerType["magicTower"] || (*hitEffectIt)->type==map.towerType["magicTower2"])
        {
            painter.drawPixmap((*hitEffectIt)->x,(*hitEffectIt)->y,QPixmap(QString(":/image/MagicEffect%1.png").arg((*hitEffectIt)->index)));
        }

        if((*hitEffectIt)->type==map.towerType["cannonTower"] || (*hitEffectIt)->type==map.towerType["cannonTower2"])
        {
            painter.drawPixmap((*hitEffectIt)->x,(*hitEffectIt)->y,80,80,QPixmap(QString(":/image/ExplosionEffect%1.png").arg((*hitEffectIt)->index)));
        }
    }
}

void GameWindow::drawEnemy(QPainter& painter)
{
    for(auto enemy:enemyVec)
    {
        if(enemy->getHealth() / enemy->getOrignalHealth() >=0.5)
        {
            painter.setBrush(QBrush(Qt::green,Qt::SolidPattern));
        }
        else
        {
            painter.setBrush(QBrush(Qt::red,Qt::SolidPattern));
        }
        // 画出敌人的血条
        painter.drawRect(enemy->getX(),enemy->getY()-10,80 * ((float)enemy->getHealth() / enemy->getOrignalHealth()), 6);
        switch(enemy->enemyType){
        case 1:{
            enemy->enemyPixmap=QPixmap(":/image/Penguin_barry.gif");
           //qDebug("1");
            break;
        }
        case 2:{
            enemy->enemyPixmap=QPixmap(":/image/Skeleton_warrior.gif");
            //qDebug("2");
            break;
        }
        case 3:{
             enemy->enemyPixmap=QPixmap(":/image/Fiery_dragon.gif");
             //qDebug("3");
             break;
            }
    }
        painter.drawPixmap(enemy->getX(),enemy->getY(),80,80,enemy->enemyPixmap);
    }
}

void GameWindow::drawUpgradeEffect(QPainter& painter)
{
    for(auto upgradeEffect : upEffectVec)
    {
        painter.drawPixmap(upgradeEffect->x, upgradeEffect->y, 40, 40, QPixmap(":/image/upgrade.png"));
        upgradeEffect->beShowed = true;
    }
}

// 游戏窗口关闭时发送信号，触发消息框的关闭
void GameWindow::closeEvent(QCloseEvent * event)
{
    emit windowClose();
}

void GameWindow::startTimer()
{
    timer1->start(1000);
    timer2->start(20);
    timer3->start(150);
}

//企鹅进攻
void GameWindow::addEnemy1(){
    //第一波
    if((enemyTimeCount<36)&&(enemyTimeCount%4==0))
    {
        enemyVec.push_back(new Enemy(1000,1.0,1));
        qDebug("第一波");
    }
    //第二波
    if((enemyTimeCount<81)&&(enemyTimeCount>45)&&(enemyTimeCount%3==0))
    {
        enemyVec.push_back(new Enemy(1000,1.0,1));
        qDebug("第二波");
    }
    //第三波
    if((enemyTimeCount<131)&&(enemyTimeCount>95)&&(enemyTimeCount%2==0))
    {
        enemyVec.push_back(new Enemy(2500,1.0,1));
        qDebug("第三波");
    }
    //第四波第一小波
    if((enemyTimeCount<176)&&(enemyTimeCount>145)&&(enemyTimeCount%2==0))
    {
        enemyVec.push_back(new Enemy(2500,2.0,1));
        qDebug("第四波第一小波");
    }
    //第四波第二小波
    if((enemyTimeCount<211)&&(enemyTimeCount>180)&&(enemyTimeCount%1==0))
    {
        enemyVec.push_back(new Enemy(3000,2.0,1));
        qDebug("第四波第二小波");
    }
}

//骷髅进攻
void GameWindow::addEnemy2(){
    //第二波
    if((enemyTimeCount<81)&&(enemyTimeCount>45)&&(enemyTimeCount%7==0))
    {
        enemyVec.push_back(new Enemy(2500,0.55,2));
    }
    //第四波第二小波
    if((enemyTimeCount<207)&&(enemyTimeCount>180)&&(enemyTimeCount%3==0))
    {
        enemyVec.push_back(new Enemy(5500,1.0,2));
    }
}

//飞龙进攻
void GameWindow::addEnemy3(){
    //第三波
    if((enemyTimeCount<131)&&(enemyTimeCount>95)&&(enemyTimeCount%7==0))
    {
        enemyVec.push_back(new Enemy(1200,3.0,3));
    }
    //第四波第一小波
    if((enemyTimeCount<173)&&(enemyTimeCount>145)&&(enemyTimeCount%5==0))
    {
        enemyVec.push_back(new Enemy(1800,4.0,3));
    }
    //第四波第二小波
    if((enemyTimeCount<207)&&(enemyTimeCount>180)&&(enemyTimeCount%10==0))
    {
        enemyVec.push_back(new Enemy(1800,4.0,3));
    }
}

void GameWindow::delay(int mSec){
    QEventLoop loop;
    QTimer::singleShot(mSec,&loop,SLOT(quit()));
    loop.exec();
}

void GameWindow::drawGameOver(QPainter& painter)
{
    if(isWin != UNKNOWN)
    {
        if(isWin == WIN)
        {
            painter.drawPixmap(150,200,600,400,QPixmap(":/image/win1.png"));
        }
        else if(isWin == DEFEATED)
        {
            painter.drawPixmap(150,200,600,400,QPixmap(":/image/defeated1.png"));
        }
        if(!timer4->isActive())
        {
            timer4->start(5000);
        }
    }
}
