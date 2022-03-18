
#ifndef ECHANTILLON_H
#define ECHANTILLON_H

#include <QMainWindow>
#include <QtWidgets>
#include <QDebug>
#include <QTableView>
#include <QLayoutItem>
#include <QTextStream>
#include <QComboBox>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QtCore>
#include <QtGui>
#include <QGraphicsRectItem>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QRandomGenerator>

#define VERT 1
#define ROUGE 2
#define BLEU 3
#define VIDE 4



class Echantillon : public QPixmap
{
public :


    //constructeurs
    Echantillon();
    Echantillon(int Xpos , int Ypos , int Angle = 0 , int Couleur = ROUGE,bool Face = false);

    //méthode
    void retourner();
    void afficher(QGraphicsScene *scene);

    //attributs
    int x,y,angle;
    int couleur;
    bool face; //true  = révélé , false = caché


};

#endif // ECHANTILLON_H
