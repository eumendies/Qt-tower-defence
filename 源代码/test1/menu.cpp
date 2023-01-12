#include "menu.h"
#include"gamewindow.h"
#include<windows.h>
#include<QPushButton>
#include<QMessageBox>
#include<QPixmap>
#include<QDebug>
#include<QWidget>
#include<QSlider>
#include<QLabel>
#include<QString>
#include<QSpinBox>

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)

{
    //设置bgm茉莉花，可单曲循环
    bgm1.addMedia(QUrl("qrc:/sound/Molly.mp3"));
    playbgm1.setPlaylist(&bgm1);
    playbgm1.setVolume(30);
    playbgm1.play();

    //简单设置Menu界面
    menuIcon.addFile(":/image/icon.ico");
    setWindowIcon(menuIcon);
    setWindowTitle("开始菜单");
    setFixedSize(850,530);

    //设置四个按钮
    QPushButton *startBut=new QPushButton("开始游戏",this);
    QPushButton *settingBut=new QPushButton("设置",this);
    QPushButton *aboutBut=new QPushButton("关于游戏",this);
    QPushButton *exitBut=new QPushButton("退出游戏",this);
    startBut->move(275,50);
    settingBut->move(275,160);
    aboutBut->move(275,270);
    exitBut->move(275,380);
    startBut->setStyleSheet("QPushButton{font:50px}");
    settingBut->setStyleSheet("QPushButton{font:50px}");
    aboutBut->setStyleSheet("QPushButton{font:50px}");
    exitBut->setStyleSheet("QPushButton{font:50px}");
    startBut->resize(300,90);
    settingBut->resize(300,90);
    aboutBut->resize(300,90);
    exitBut->resize(300,90);

    //构建设置窗口
    QWidget *settingBox=new QWidget;
    settingIcon.addFile(":/image/settings.ico");
    settingBox->setFixedSize(350,500);
    settingBox->setWindowIcon(settingIcon);
    settingBox->setWindowTitle("设置");

    //用于控制bgm1音量
    int nMin=0;
    int nMax=100;
    int nSingleStep=5;
    // 微调框
    QSpinBox *pSpinBox = new QSpinBox(settingBox);
    pSpinBox->setMinimum(nMin);  // 最小值
    pSpinBox->setMaximum(nMax);  // 最大值
    pSpinBox->setSingleStep(nSingleStep);  // 步长
    pSpinBox->move(70,230);
    // 滑动条
    QSlider *bgm1Slider=new QSlider(settingBox);
    bgm1Slider->setOrientation(Qt::Horizontal);  // 水平方向
    bgm1Slider->setMinimum(nMin);  // 最小值
    bgm1Slider->setMaximum(nMax);  // 最大值
    bgm1Slider->setSingleStep(nSingleStep);  // 步长
    bgm1Slider->move(135,230);
    // 连接信号槽（相互改变）
    connect(pSpinBox, SIGNAL(valueChanged(int)), bgm1Slider, SLOT(setValue(int)));
    connect(bgm1Slider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));
    pSpinBox->setValue(10);
    QLabel *volumeLabel=new QLabel(settingBox);
    volumeLabel->move(113,255);
    QString volumeString="音量："+QString::number(bgm1Slider->value());
    volumeLabel->setText(volumeString);
    volumeLabel->setGeometry(113,255,400,20);
    connect(bgm1Slider,&QSlider::valueChanged,[=](){
        this->setVolume();
        QString volumeString="音量："+QString::number(bgm1Slider->value());
        volumeLabel->setText(volumeString);
    });


    //构建关于窗口
    QMessageBox *aboutGameBox=new QMessageBox(this);
    aboutGameBox->setWindowTitle("关于游戏");
    aboutGameBox->setText("开发人员：");
    qDebug("yes");
    aboutGameBox->setIconPixmap(QPixmap(":/image/aboutGameIcon.ico"));
    QPushButton *closeBut=aboutGameBox->addButton("关闭",QMessageBox::AcceptRole);

    //设置四个按钮按下时的事件
    connect(startBut,&QPushButton::clicked,this,[=](){
        playbgm1.stop();
        settingBox->close();
        this->hide();
        // 开启gamewindow的计时器
        w.startTimer();
        w.show();
    });

    connect(settingBut,&QPushButton::clicked,[=](){
        settingBox->show();
    });

    connect(aboutBut,&QPushButton::clicked,aboutGameBox,[=](){
        settingBox->close();
        aboutGameBox->exec();
    });

    connect(exitBut,&QPushButton::clicked,this,[=](){
        settingBox->close();
        this->close();
    });

    //窗口关闭时关闭其余页面
    connect(this,&Menu::MenuClose,[=](){
        settingBox->close();
        aboutGameBox->close();
    });
    //开始界面休眠展示图片
    Sleep(1000);
}

Menu::~Menu()
{
}

void Menu::closeEvent(QCloseEvent*)
{
    emit MenuClose();
}

int Menu::getSliderValue(){
    return bgm1Slider.value();
}

void Menu::setVolume(){
    int temp=getSliderValue();
    playbgm1.setVolume(temp);
}
