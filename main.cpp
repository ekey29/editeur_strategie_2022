/**********************************************************************
CRAC 2022
Version 2022 de l'éditeur de stratégie sous Qt
Ne pas partager en dehors du CRAC de l'IUT de Cachan
En cas de difficulté , n'hésitez pas à me poser des question par discord: ekey29#9834
ou par mail : rayan.smaali1@gmail.com
***********************************************************************/

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return a.exec();
}


