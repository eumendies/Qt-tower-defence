#include"menu.h"
#include"gamewindow.h"
#include<QMovie>
#include<QPixmap>
#include<QSplashScreen>
#include <QApplication>
#include<QLabel>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
        QPixmap pixmap(":/image/startPicture.png");
        QSplashScreen splash(pixmap);
        splash.show();
        a.processEvents();
        Menu w;
        w.show();
        splash.finish(&w);
        return a.exec();
}
