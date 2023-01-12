#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QMainWindow>
#include<QPaintEvent>
#include<QIcon>
#include<QMediaPlaylist>
#include<QMediaPlayer>
#include<QUrl>
#include "map.h"

class GameWindow : public QMainWindow
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    void paintEvent(QPaintEvent * event);
    void setTowerButton();
    void drawTower(QPainter& painter);
    void drawHitEffect(QPainter& painter);
    void closeEvent(QCloseEvent * event);
    void drawEnemy(QPainter& painter);
    void drawUpgradeEffect(QPainter& painter);
    void startTimer();
    void addEnemy1();
    void addEnemy2();
    void addEnemy3();
    void delay(int mSec);
    void drawGameOver(QPainter& painter);
    QMediaPlaylist bgm2;
    QMediaPlayer playbgm2;
    QIcon GameIcon;
    enum WINFLAG{
        WIN,DEFEATED,UNKNOWN
    };

private:
    Map map;
    QTimer* timer1;
    QTimer* timer2;
    QTimer* timer3;
    WINFLAG isWin;
signals:
    void windowClose();
    void gameOver();
};
#endif // GAMEWINDOW_H
