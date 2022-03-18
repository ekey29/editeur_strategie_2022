#ifndef MAINWINDOW_H
#define MAINWINDOW_H


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




#include "mymodel.h"
#include "mycomboboxitemdelegate.h"
#include "ui_mainwindow.h"


#define LONGUEUR_TABLE 3000
#define LARGEUR_TABLE 2000
#define LONGUEUR_ROBOT 240
#define LARGEUR_ROBOT 230
#define LARGEUR_VENTOUSE 150
#define DIAG_ROBOT1 300

#define OFF 0
#define ON 1

#define GREEN 1
#define RED 2
#define BLUE 3
#define EMPTY 4

#define GLOBALOFFSETX -15
#define GLOBALOFFSETY -40

#define ORIGINE_X 0
#define ORIGINE_Y 0

#define OBSTACLE_1_X 895
#define OBSTACLE_1_Y 1850

#define OBSTACLE_2_X 1495
#define OBSTACLE_2_Y 1700

#define OBSTACLE_3_X 2095
#define OBSTACLE_3_Y 1850

QT_BEGIN_NAMESPACE
//class QTableView;




namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;

    //QTableView *tableView;

    QGraphicsScene *scene;
    QGraphicsPixmapItem *image;
    QGraphicsPixmapItem *robot1, *robotdep,*ptrEchantillon[30],*ptrCarre[10];
    QGraphicsLineItem *lineUp;
    QGraphicsLineItem *lineDown;
    QGraphicsLineItem *lineRight;
    QGraphicsLineItem *lineLeft;
    QGraphicsLineItem *lineMap1;
    QGraphicsLineItem *lineMap2;
    QGraphicsLineItem *lineMap3;
    QGraphicsLineItem *ligneDroite;
    QGraphicsLineItem *lineRandom;
    QGraphicsEllipseItem *ellipseRandom;
    QGraphicsRectItem *tempItem[5];


public:
    explicit MainWindow(QWidget *parent = nullptr);

    static const QStringList dataCol1;
    static const QStringList dataEquipe;
    static const QStringList dataAction;


    int nbUpdateVisu = 0;

public slots:
    void setHeaderComboBox(int index);                  //Modifie les headers en fonction de l'index de la ComboBox
    void initHeaderData();                              //Initialise les headers
    void initModel();                                   //Initialise le modèle
    void tableViewIsClicked(const QModelIndex &index);  //A chaque fois que l'utilisateur clique sur le tableau, actualise les headers
    void resetComboBox();                               //Supprime les combobox
    void setFocusOnButton();                            //Sélectionne le 1er bouton de la ligne créer
    void updateHeader(const QModelIndex &index);        //Actualise les Headers
    void updateVisu(const QModelIndex &index);          //Actualise les éléments visuels de la table de jeu
    void SetView();                                     //Actualise la vue (taille des images dans le "graphics view")
    void initVisu();                                    //Initialise la table de jeu et la position initiale du robot
    QPixmap determinerCouleur(int i);
    void afficherEchantillon(int i);


protected:
    virtual void resizeEvent(QResizeEvent *event);      //Détection d'évènements et redimensionne la vue

private slots:
    void on_CreateRowButton_clicked();
    void on_InsertRowButton_clicked();
    void on_DeleteRowButton_clicked();
    void on_ExportFileButton_clicked();
    void on_ImportFileButton_clicked();

};
#endif // MAINWINDOW_H
