/**********************************************************************
CRAC 2020
Version 2020 de l'éditeur de stratégie sous Qt
Ne pas partager en dehors du CRAC de l'IUT de Cachan
Pour toutes questions : parisludovicpro@gmail.com
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


