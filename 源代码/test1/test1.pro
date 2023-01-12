QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cannontower.cpp \
    coin.cpp \
    enemy.cpp \
    gamewindow.cpp \
    magictower.cpp \
    main.cpp \
    mainwindow.cpp \
    map.cpp \
    menu.cpp \
    tower.cpp \
    towerbox.cpp

HEADERS += \
    cannontower.h \
    coin.h \
    enemy.h \
    gamewindow.h \
    magictower.h \
    mainwindow.h \
    map.h \
    menu.h \
    someStruct.h \
    tower.h \
    towerbox.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc \
    res.qrc

FORMS += \
    towerbox.ui

DISTFILES += \
    Path.txt \
    button_position \
    button_position.txt \
    enemylist.txt \
    image/gameIcon.ico \
    map_1.jpg \
    test1.pro.user
