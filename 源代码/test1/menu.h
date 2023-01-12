#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include<QMediaPlaylist>
#include<QMediaPlayer>
#include<QUrl>
#include<QIcon>
#include<QSlider>
#include"gamewindow.h"


class Menu : public QMainWindow
{
    Q_OBJECT

public:
    QIcon menuIcon,settingIcon;
    GameWindow w;
    int getSliderValue();
    void setVolume();
    Menu(QWidget *parent = nullptr);
    ~Menu();
    void closeEvent(QCloseEvent * );
    QMediaPlaylist bgm1;
    QMediaPlayer playbgm1;
    QSlider bgm1Slider;
signals:
    void MenuClose();
};
#endif // MENU_H
