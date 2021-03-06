#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QList>

#define ROBOTCENTRE robot1->pos().x() -15 + GLOBALOFFSETX,robot1->pos().y() + GLOBALOFFSETY - 20
#define ROBOTCENTREX robot1->pos().x() + GLOBALOFFSETX
#define ROBOTCENTREY robot1->pos().y() + GLOBALOFFSETY

const QStringList MainWindow::dataCol1 = {"Debut Match",
                                          "Ligne Droite",
                                          "Rotation",
                                          "Courbe",
                                          "Action",
                                          "Recalage",
                                          "XYT"};

const QStringList MainWindow::dataEquipe = {"Jaune",
                                            "Bleu"};


const QStringList MainWindow::dataAction = {"Deploiement",

                                            "Prise_bas",
                                            "Passe",
                                            "Pose_bas",
                                            "Pose_Haut",
                                            "Prise_bordure",
                                            "Pose_bordure",
                                            "Prise_distrib",
                                            "Ranger",

                                            "Res_prestest",
                                            "Res_mes",
                                            "Res_rang"

                                            ,"Pre_prise"
                                            ,"Prise_statuette"
                                            ,"Pose_statuette"};

int carreFlag = 1 , robot2Flag = 0;


QPointF bras[17]{};

int coordonneesBase[30][6]{ // coordonnées des échantillons {x,y,COULEUR,etat,rotation,bras}
    // etat : 0-> caché ; 1-> retourné ; 2-> debout
    //0 ->11 échantillon au sol ; 12->17 site de fouilles ;18->29 distributeurs;
    // le dernier paramètre correspond au bras qui a attrapé l'échantillon : 0 -> aucun ; 1 à 6 -> bras du bas ; 11 à 16 -> bras du haut

    {900,555,BLUE,0,0,0}, // au sol côté jaune 00
    {830,679,GREEN,0,0,0},
    {900,805,RED,0,0,0},

    {-65,300,GREEN,0,0,0}, // en hauteur côté jaune 03
    {121,1688,BLUE,0,-45,0},
    {312,1879,RED,0,-45,0},

    {2100,555,BLUE,0,0,0}, // au sol côté violet 06
    {2170,679,GREEN,0,0,0},
    {2100,805,RED,0,0,0},

    {3065,300,GREEN,0,0,0}, // en hauteur côté violet 09
    {2879,1688,BLUE,0,0,0},
    {2688,1879,RED,0,0,0},

    {0,0,GREEN,1,0,0},//site de fouille côté jaune 12
    {0,0,RED,1,0,0},
    {0,0,BLUE,1,0,0},

    {0,0,GREEN,1,0,0},//site de fouille côté violet 15
    {0,0,RED,1,0,0},
    {0,0,BLUE,1,0,0},

    {22,1250,RED,2,0,0},//distributeurs bas côté jaune 18
    {37,1250,GREEN,2,0,0},
    {52,1250,BLUE,2,0,0},

    {1350,22,RED,2,90,0},//distributeurs haut côté jaune 21
    {1350,37,GREEN,2,90,0},
    {1350,52,BLUE,2,90,0},

    {3000-22,1250,RED,2,0,0},//distributeurs bas côté violet 24
    {2985-22,1250,GREEN,2,0,0},
    {2970-22,1250,BLUE,2,0,0},

    {1650,22,RED,2,90,0},//distributeurs haut côté violet 27
    {1650,37,GREEN,2,90,0},
    {1650,52,BLUE,2,90,0}
};

int coordonnees[30][6]{
{900,555,BLUE,0,0,0}, // au sol côté jaune
{830,679,GREEN,0,0,0},
{900,805,RED,0,0,0},

{-65,300,GREEN,0,0,0}, // en hauteur côté jaune
{121,1688,BLUE,0,-45,0},
{312,1879,RED,0,-45,0},

{2100,555,BLUE,0,0,0}, // au sol côté violet
{2170,679,GREEN,0,0,0},
{2100,805,RED,0,0,0},

{3065,300,GREEN,0,0,0}, // en hauteur côté violet
{2879,1688,BLUE,0,0,0},
{2688,1879,RED,0,0,0},

{0,0,GREEN,1,0,0},//site de fouille côté jaune
{0,0,RED,1,0,0},
{0,0,BLUE,1,0,0},

{0,0,GREEN,1,0,0},//site de fouille côté violet
{0,0,RED,1,0,0},
{0,0,BLUE,1,0,0},

{22,1250,RED,2,0,0},//distributeurs bas côté jaune
{37,1250,GREEN,2,0,0},
{52,1250,BLUE,2,0,0},

{1350,22,RED,2,90,0},//distributeurs haut côté jaune
{1350,37,GREEN,2,90,0},
{1350,52,BLUE,2,90,0},

{3000-22,1250,RED,2,0,0},//distributeurs bas côté violet
{2985-22,1250,GREEN,2,0,0},
{2970-22,1250,BLUE,2,0,0},

{1650,22,RED,2,90,0},//distributeurs haut côté violet
{1650,37,GREEN,2,90,0},
{1650,52,BLUE,2,90,0}
};




MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,ptrEchantillon{new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,
                    new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,
                    new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,
                    new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,
                    new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,
                    new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem}
    ,ptrCarre{new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,
              new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem,new QGraphicsPixmapItem}
    ,brasMesure{new QGraphicsRectItem,new QGraphicsRectItem}
    ,ventouse{new QGraphicsEllipseItem ,new QGraphicsEllipseItem,new QGraphicsEllipseItem ,new QGraphicsEllipseItem,new QGraphicsEllipseItem ,
              new QGraphicsEllipseItem ,new QGraphicsEllipseItem,new QGraphicsEllipseItem ,new QGraphicsEllipseItem,new QGraphicsEllipseItem ,
              new QGraphicsEllipseItem ,new QGraphicsEllipseItem,new QGraphicsEllipseItem ,new QGraphicsEllipseItem,new QGraphicsEllipseItem ,
              new QGraphicsEllipseItem ,new QGraphicsEllipseItem}
    ,collisionLine{new QGraphicsLineItem,new QGraphicsLineItem,new QGraphicsLineItem,new QGraphicsLineItem}
    ,brasDistrib{new QGraphicsLineItem , new QGraphicsLineItem,new QGraphicsLineItem , new QGraphicsLineItem,new QGraphicsLineItem,new QGraphicsLineItem}

{

    initVisu();
    initModel();




    MyComboBoxDelegate *cbd = new MyComboBoxDelegate(ui->tableView);

    ui->tableView->setItemDelegateForColumn(1, cbd);
    //ui->tableView->setItemDelegateForColumn(10, cbd);
    //ui->tableView->setItemDelegateForColumn(11, cbd);

    initHeaderData();

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex &)), this, SLOT(tableViewIsClicked(const QModelIndex &)));

    ui->tableView->model()->insertRow(ui->tableView->model()->rowCount());
    ui->tableView->model()->setData(ui->tableView->model()->index(0,0),0);
    ui->tableView->model()->setData(ui->tableView->model()->index(0,1),dataCol1.at(0));
    ui->tableView->model()->setData(ui->tableView->model()->index(0,2),dataEquipe.at(0));
    ui->tableView->model()->setData(ui->tableView->model()->index(0,3),65);
    ui->tableView->model()->setData(ui->tableView->model()->index(0,4),522);
    ui->tableView->model()->setData(ui->tableView->model()->index(0,5),230);
    ui->tableView->model()->setData(ui->tableView->model()->index(0,6),"Précis");
    ui->tableView->model()->setData(ui->tableView->model()->index(0,7),"Attendre");

    ui->tableView->model()->setData(ui->tableView->model()->index(0,10),1);
    ui->tableView->model()->setData(ui->tableView->model()->index(0,11),1);
    QModelIndex newIndex  = ui->tableView->model()->index(0,0);
    ui->tableView->setCurrentIndex(newIndex);
    robot1->setPos(522,230);
    robot1->setRotation(90 - 65);
    robotdep->setPos(522,230);
    robotdep->setRotation(90 - 65);
    ui->lcdPosX->display(522);
    ui->lcdPosY->display(230);
    ui->lcdPosT->display(90 -65);

//    ui->graphicsView->setMouseTracking(true);
//    QWidget::connect (ui->graphicsView, SIGNAL(sendMousePoint(QPointF)),this, SLOT(setMousePoint(QPointF)));

}



void MainWindow::initVisu()
{
    qDebug() << "init visu";
    ui->setupUi(this); //L'user Interface démarre

    // positions initiales des splitter en fixant les zones
    QList<int> size;
    size << 0 << 0;
    size[0] = 0.5 * width();
    size[1] = width() - size[0];
    ui->splitterHoriz->setSizes(size);
    size[0] = 0.75 * height();
    size[1] = height() - size[0];
    ui->splitterVerti->setSizes(size);

    scene = new QGraphicsScene;
    scene->setSceneRect(-165,-165,3300,2250);
    ui->graphicsView->setScene(scene);
    //Intégration des images pour la scene
    QPixmap tapis(":/Images/AgeOfBots/table.png");
    image = scene->addPixmap(tapis);
    image->setOffset(-165,-165);

    QPixmap robot(":/Images/AgeOfBots/ROB2020.png");

    robot1 = scene->addPixmap(robot);
    robot1->setOffset(GLOBALOFFSETX - robot1->boundingRect().center().x(),GLOBALOFFSETY - robot1->boundingRect().center().y());
    robot1->setTransformOriginPoint(robot1->boundingRect().center());
    robot1->setPos(0,0); //Le robot est positionné
    robot1->setRotation(90);
    robotdep = scene->addPixmap(robot);
    robotdep->setOffset(GLOBALOFFSETX - robotdep->boundingRect().center().x(),GLOBALOFFSETY - robotdep->boundingRect().center().y());
    robotdep->setTransformOriginPoint(robotdep->boundingRect().center());
    robotdep->setRotation(90);





    //Création des bordures virtuelles
    QPen redline(Qt::red);
    QPen blackline(Qt::black);
    redline.setStyle(Qt::SolidLine);
    redline.setWidth(3);
    redline.setBrush(Qt::red);
    lineUp = scene->addLine(ORIGINE_X,ORIGINE_Y,LONGUEUR_TABLE,ORIGINE_Y,redline);
    lineDown = scene->addLine(ORIGINE_X,LARGEUR_TABLE,LONGUEUR_TABLE,LARGEUR_TABLE,redline);
    lineRight = scene->addLine(LONGUEUR_TABLE,ORIGINE_Y,LONGUEUR_TABLE,LARGEUR_TABLE,redline);
    lineLeft = scene->addLine(ORIGINE_X,ORIGINE_Y,ORIGINE_X,LARGEUR_TABLE,redline);
    lineMap1 = scene->addLine(OBSTACLE_1_X,OBSTACLE_1_Y,OBSTACLE_1_X,LARGEUR_TABLE,redline);
    lineMap2 = scene->addLine(OBSTACLE_2_X,OBSTACLE_2_Y,OBSTACLE_2_X,LARGEUR_TABLE,redline);
    lineMap3 = scene->addLine(OBSTACLE_3_X,OBSTACLE_3_Y,OBSTACLE_3_X,LARGEUR_TABLE,redline);
    lineUp->hide();
    lineDown->hide();
    lineRight->hide();
    lineLeft->hide();
    lineMap1->hide();
    lineMap2->hide();
    lineMap3->hide();

    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);

//    QGraphicsTextItem *itemTextVentouse = new QGraphicsTextItem;
//    itemTextVentouse->setPos(200, 500);
//    itemTextVentouse->setPlainText("Hello, world!");
//    scene->addItem(itemTextVentouse);


    qDebug() << scene->sceneRect();
}

void MainWindow::SetView()
{
    ui->graphicsView->fitInView(scene->sceneRect(),Qt::KeepAspectRatio);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    QMainWindow::resizeEvent(event); //Détection de l'évènement
    SetView(); //Actualise la vue (taille des images dans le "graphics view")
}

/**********************************************************************************
 *      Fonction setHeaderComboBox(int index) : Modifie les headers en fonction   *
 *                            de l'index de la ComboBox                           *
 *********************************************************************************/
void MainWindow::setHeaderComboBox(int index)
{
    MyComboBoxDelegate *cbd = dynamic_cast<MyComboBoxDelegate *>(ui->tableView->itemDelegateForColumn(1));
    resetComboBox();

    switch (index) {

    case 0 : //Début match
        ui->tableView->model()->setHeaderData(2, Qt::Horizontal, QObject::tr("Equipe"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(3, Qt::Horizontal, QObject::tr("Angle"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(4, Qt::Horizontal, QObject::tr("Abs:x"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(5, Qt::Horizontal, QObject::tr("Ord:y"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(6, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(7, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
        ui->tableView->setItemDelegateForColumn(2,cbd);
        break;

    case 1 : //Ligne droite
        ui->tableView->model()->setHeaderData(2, Qt::Horizontal, QObject::tr("Dist"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(3, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(4, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(5, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole)
                ;
        ui->tableView->model()->setHeaderData(6, Qt::Horizontal, QObject::tr("Précis?"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(7, Qt::Horizontal, QObject::tr("Enchainmnt"),Qt::DisplayRole);
        ui->tableView->setItemDelegateForColumn(6,cbd);
        ui->tableView->setItemDelegateForColumn(7,cbd);
        break;

    case 2 : //Rotation
        ui->tableView->model()->setHeaderData(2, Qt::Horizontal, QObject::tr("Angle"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(3, Qt::Horizontal, QObject::tr("Relatif"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(4, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(5, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(6, Qt::Horizontal, QObject::tr("Précis?"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(7, Qt::Horizontal, QObject::tr("Enchainement"),Qt::DisplayRole);
        ui->tableView->setItemDelegateForColumn(3,cbd);
        ui->tableView->setItemDelegateForColumn(6,cbd);
        ui->tableView->setItemDelegateForColumn(7,cbd);
        break;
    case 3 : //Courbe
        ui->tableView->model()->setHeaderData(2, Qt::Horizontal, QObject::tr("Rayon"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(3, Qt::Horizontal, QObject::tr("Angle"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(4, Qt::Horizontal, QObject::tr("Sens"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(5, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(6, Qt::Horizontal, QObject::tr("Précis?"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(7, Qt::Horizontal, QObject::tr("Enchainement"),Qt::DisplayRole);
        ui->tableView->setItemDelegateForColumn(4,cbd);
        ui->tableView->setItemDelegateForColumn(6,cbd);
        ui->tableView->setItemDelegateForColumn(7,cbd);
        break;

    case 4 : //Action
        ui->tableView->model()->setHeaderData(2, Qt::Horizontal, QObject::tr("Action"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(3, Qt::Horizontal, QObject::tr("Par1"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(4, Qt::Horizontal, QObject::tr("Par2"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(5, Qt::Horizontal, QObject::tr("Par3"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(6, Qt::Horizontal, QObject::tr("Précis?"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(7, Qt::Horizontal, QObject::tr("Enchainmnt"),Qt::DisplayRole);
        ui->tableView->setItemDelegateForColumn(2,cbd);
        ui->tableView->setItemDelegateForColumn(6,cbd);
        ui->tableView->setItemDelegateForColumn(7,cbd);
        break;

    case 5 : //Recalage
        ui->tableView->model()->setHeaderData(2, Qt::Horizontal, QObject::tr("Sens"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(3, Qt::Horizontal, QObject::tr("Type"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(4, Qt::Horizontal, QObject::tr("Axe"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(5, Qt::Horizontal, QObject::tr("Para"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(6, Qt::Horizontal, QObject::tr("Précis?"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(7, Qt::Horizontal, QObject::tr("Enchainmnt"),Qt::DisplayRole);
        ui->tableView->setItemDelegateForColumn(2,cbd);
        ui->tableView->setItemDelegateForColumn(3,cbd);
        ui->tableView->setItemDelegateForColumn(4,cbd);
        ui->tableView->setItemDelegateForColumn(5,cbd);
        ui->tableView->setItemDelegateForColumn(6,cbd);
        ui->tableView->setItemDelegateForColumn(7,cbd);
        break;

    case 6 : //XYT
        ui->tableView->model()->setHeaderData(2, Qt::Horizontal, QObject::tr("Sens"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(3, Qt::Horizontal, QObject::tr("Abs:x"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(4, Qt::Horizontal, QObject::tr("Ord:y"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(5, Qt::Horizontal, QObject::tr("Angle"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(6, Qt::Horizontal, QObject::tr("Précis?"),Qt::DisplayRole);
        ui->tableView->model()->setHeaderData(7, Qt::Horizontal, QObject::tr("Enchainmnt"),Qt::DisplayRole);
        ui->tableView->setItemDelegateForColumn(2,cbd);
        ui->tableView->setItemDelegateForColumn(6,cbd);
        ui->tableView->setItemDelegateForColumn(7,cbd);
        break;
    }
}


/**********************************************************************************
 *               Fonction initHeaderData() : Initialise les headers               *
 *********************************************************************************/
void MainWindow::initHeaderData()
{
    ui->tableView->model()->setHeaderData(1, Qt::Horizontal, QObject::tr("Inst"),Qt::DisplayRole);
    ui->tableView->model()->setHeaderData(8, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
    ui->tableView->model()->setHeaderData(9, Qt::Horizontal, QObject::tr(" "),Qt::DisplayRole);
    ui->tableView->model()->setHeaderData(10, Qt::Horizontal, QObject::tr("L.S."),Qt::DisplayRole);
    ui->tableView->model()->setHeaderData(11, Qt::Horizontal, QObject::tr("SiInter"),Qt::DisplayRole);

//    ui->tableView->resizeColumnsToContents();
}

/**********************************************************************************
 *                  Fonction initModel() : Initialise le modèle                   *
 *********************************************************************************/
void MainWindow::initModel()
{
    MyModel *myModel = new MyModel(this);
    ui->tableView->setModel(myModel);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
}



/**********************************************************************************
 *   Fonction tableViewIsClicked(const QModelIndex &index) : A chaque fois que    *
 *          l'utilisateur clique sur le tableau, actualise les headers            *
 *********************************************************************************/
void MainWindow::tableViewIsClicked(const QModelIndex &index)
{
    updateHeader(index);
    updateVisu(index);
}



void MainWindow::updateHeader(const QModelIndex &index)
{
    QModelIndex i = index.model()->index(index.row(), 1);
    QString data = index.model()->data(i).toString();
    setHeaderComboBox(dataCol1.indexOf(data));
}

void MainWindow::updateVisu(const QModelIndex &index)
{

    //int i = index.row();
    static QGraphicsItem *item[7],*Gobelet[50],*itemVentouse[6],*itemManche[2];
    static QGraphicsItem *itemTextVentouse[6],*itemTextBrasVentouse[6];
    unsigned int Gobelet_coord[30][2]={{400,300},{1200,300},{1085,450},{515,450},{100,670},{400,950},{800,1100},{1200,1270},{1955,1005},{1650,1065},{1650,1335},{1955,1395}};
    int Gobelet_coord_ecueil[20][2]={{1450,-67},{1525,-67},{1600,-67},{1675,-67},{1750,-67},{-67,700},{-67,775},{-67,850},{-67,925},{-67,1000}};
    static int Gobelet_angle_random[6];
    static int Gobelet_rayon_ramdom[6];
    int angle, rayon;
    int Pen_Random[6]={1,2,2,1,1,2};
    double facteur=1;
    //    unsigned int Gobelet_robot[6]={100,100,100,100,100,100};
    int Ventouse_coo[6][2]={{132,-75},{132,0},{132,75},{-132,75},{-132,0},{-132,-75}};
    int Manche_coord[2][2]={{50,-75},{-15,75}};
    int Trajectoire_Ventouse[6][4];
    unsigned int Ventouse_Action_Gobelet[6][2]={{OFF,100},{OFF,100},{OFF,100},{OFF,100},{OFF,100},{OFF,100}};
    static int Ventouse_Couleur_Gobelet[6];
    unsigned int Bras_Action_Gobelet[6][3]={{OFF,100,OFF},{OFF,100,OFF},{OFF,100,OFF},{OFF,100,OFF},{OFF,100,OFF},{OFF,100,OFF}};
    unsigned int Manche_Air_Action[2]={OFF,OFF};
    unsigned int Manche_Air_Couleur=0;
    double rayonCourbeVent[6];
    int Xoffset,Yoffset,avt_arr,incr,numero_Gobelet,valeur=1;
    double m,p,Xdepart,Xarrivee,Ydepart,Yarrivee,x,y,xc,yc,R,calcul;
    unsigned int numero_action,numero_manche,numero_ligne,numero_ligne_courbe;
    int centaine,dizaine,unite;
    QPen redline(Qt::red,10,Qt::SolidLine);
    QPen greenline(Qt::green,10,Qt::SolidLine);
    QPen blacklinedot(Qt::black,10,Qt::DotLine);
    QPen ellipsered(Qt::red,1,Qt::SolidLine);
    QBrush ellipsebrushred(Qt::red,Qt::SolidPattern);
    QPen ellipsedarkred(Qt::darkRed,1,Qt::SolidLine);
    QBrush ellipsebrushdarkred(Qt::darkRed,Qt::SolidPattern);
    QPen ellipsegreen(Qt::green,1,Qt::SolidLine);
    QBrush ellipsebrushgreen(Qt::green,Qt::SolidPattern);
    QPen ellipsedarkgreen(Qt::darkGreen,1,Qt::SolidLine);
    QBrush ellipsebrushdarkgreen(Qt::darkGreen,Qt::SolidPattern);
    QPen Pen[50];
    QBrush Brush;
    QPainterPath path,path1,pathArcVentouse[6];
    QModelIndex j;
    QModelIndex testindex;
    QString data;
    QFont font;
    QPainterPath pathtext[6];
    font.setPixelSize(50);
    font.setBold(false);
    font.setFamily("Times");
    QPixmap tapis(":/Images/AgeOfBots/table.png");
    QPainter painter;
    //QPixmap tapisFlipped(":/Images/AgeOfBots/tableFlipped.png");
    static int equipe, old_equipe, start_update=0,futur_i=0;
    bool check,check_blocage;
    int indexComboBox,flagStop = 0,table_ligne = 0;
    double PosXrob = 0, PosYrob = 0, PosRotrob = 0, PosXrobPres = 90, PosYrobPres =0 , PosRotrobPres = 0,
            PosCXrob= 0, PosCYrob= 0, distanceLigneDroite, rayonCourbe, rayonCourbeVentouse, angleCourbe,angleRotation;
    int newValue;


    bool resDeploye[2] {false,false};


    resetPosEchantillon();


    check = ui->checkBox->isChecked();
    setWindowTitle("éditeur de stratégie 2022 - Age of Bots - 1.5.1");
















    bool collide = true;
    if(check==false)
    {
        //gestions des carré de fouilles
        QPixmap pixArray[10];

        switch(carreFlag){
        case 1 :

            pixArray[0].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[1].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[2].load(":/Images/AgeOfBots/carre_croix");

            pixArray[3].load(":/Images/AgeOfBots/carre_violet");
            pixArray[4].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[5].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[6].load(":/Images/AgeOfBots/carre_violet");

            pixArray[7].load(":/Images/AgeOfBots/carre_croix");
            pixArray[8].load(":/Images/AgeOfBots/carre_violet");
            pixArray[9].load(":/Images/AgeOfBots/carre_violet");
            break;

        case 2 :

            pixArray[0].load(":/Images/AgeOfBots/carre_croix");
            pixArray[1].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[2].load(":/Images/AgeOfBots/carre_jaune");

            pixArray[3].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[4].load(":/Images/AgeOfBots/carre_violet");
            pixArray[5].load(":/Images/AgeOfBots/carre_violet");
            pixArray[6].load(":/Images/AgeOfBots/carre_jaune");

            pixArray[7].load(":/Images/AgeOfBots/carre_violet");
            pixArray[8].load(":/Images/AgeOfBots/carre_violet");
            pixArray[9].load(":/Images/AgeOfBots/carre_croix");
            break;

        case 3 :

            pixArray[0].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[1].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[2].load(":/Images/AgeOfBots/carre_croix");

            pixArray[3].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[4].load(":/Images/AgeOfBots/carre_violet");
            pixArray[5].load(":/Images/AgeOfBots/carre_violet");
            pixArray[6].load(":/Images/AgeOfBots/carre_jaune");

            pixArray[7].load(":/Images/AgeOfBots/carre_croix");
            pixArray[8].load(":/Images/AgeOfBots/carre_violet");
            pixArray[9].load(":/Images/AgeOfBots/carre_violet");
            break;

        case 4 :

            pixArray[0].load(":/Images/AgeOfBots/carre_croix");
            pixArray[1].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[2].load(":/Images/AgeOfBots/carre_jaune");

            pixArray[3].load(":/Images/AgeOfBots/carre_violet");
            pixArray[4].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[5].load(":/Images/AgeOfBots/carre_jaune");
            pixArray[6].load(":/Images/AgeOfBots/carre_violet");

            pixArray[7].load(":/Images/AgeOfBots/carre_violet");
            pixArray[8].load(":/Images/AgeOfBots/carre_violet");
            pixArray[9].load(":/Images/AgeOfBots/carre_croix");
            break;

        }



        for(int i = 0;i<10;i++){
            scene->removeItem(ptrCarre[i]);

            ptrCarre[i] = scene->addPixmap(pixArray[i]);
            ptrCarre[i]->setPos(667.5+i*185,2000);
            ptrCarre[i]->setOffset(-ptrCarre[i]->boundingRect().center().x() + GLOBALOFFSETX,GLOBALOFFSETY);
        }
        carreFlag++;
        if(carreFlag>4) carreFlag = 1;

        //Génération des coordonnées aléatoires des échantillons du site de fouille

            while(collide){
                for (int i=12;i<15 ;i++ ) {



                    coordonnees[i][0] = QRandomGenerator::system()->bounded(800 + 65 ,1150 - 65); // 65 et 75 correspondent a la moitié d'un échantillon
                    coordonnees[i][1] = QRandomGenerator::system()->bounded(1200 + 75,1550 - 75); // ils sont là pour s'assurer que léchantillon ne dépasse pas
                    coordonnees[i][4] = QRandomGenerator::system()->bounded(0,361);

                    coordonneesBase[i][0] = coordonnees[i][0];
                    coordonneesBase[i][1] = coordonnees[i][1];
                    coordonneesBase[i][4] = coordonnees[i][4];

                    afficherEchantillon(i);

                }

                collide = ptrEchantillon[12]->collidesWithItem(ptrEchantillon[13]) ||
                          ptrEchantillon[12]->collidesWithItem(ptrEchantillon[14]) ||
                          ptrEchantillon[13]->collidesWithItem(ptrEchantillon[14]);

       }
            collide = true;
            while(collide){
                for (int i=15;i<18 ;i++ ) {

                    coordonnees[i][0] = QRandomGenerator::system()->bounded(1850 + 65 ,2200 - 65); // 65 et 75 correspondent a la moitié d'un échantillon
                    coordonnees[i][1] = QRandomGenerator::system()->bounded(1200 + 75,1550 - 75); // ils sont là pour s'assurer que léchantillon ne dépasse pas
                    coordonnees[i][4] = QRandomGenerator::system()->bounded(0,361);

                    coordonneesBase[i][0] = coordonnees[i][0];
                    coordonneesBase[i][1] = coordonnees[i][1];
                    coordonneesBase[i][4] = coordonnees[i][4];
                    afficherEchantillon(i);

                }

                collide = ptrEchantillon[15]->collidesWithItem(ptrEchantillon[16]) ||
                          ptrEchantillon[15]->collidesWithItem(ptrEchantillon[17]) ||
                          ptrEchantillon[17]->collidesWithItem(ptrEchantillon[16]);

       }
     }

    nbUpdateVisu++;



    qDebug() << nbUpdateVisu << "______________________________________________________________________________________________________";

    int cpt_boucle=0;

    while((table_ligne<index.row()+1)&&(cpt_boucle<(2*(ui->tableView->model()->rowCount())))) // on suit les numero de lignes et on bloque la boucle infini à 2 occurences
    {
        cpt_boucle++;
        check_blocage = ui->checkBox_blocage->isChecked();
        if((table_ligne==ui->Blocage_ligne->value())&&(check_blocage==true))
        {
            facteur=ui->Blocage_pourcentage->value()/100.0;
            futur_i=ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,11)).toInt();
        }
        else
        {
            facteur=1.0;
            futur_i=ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,10)).toInt();
        }
        j = ui->tableView->model()->index(table_ligne,1);
        data = ui->tableView->model()->data(j).toString();
        indexComboBox = dataCol1.indexOf(data);

        PosXrobPres = PosXrob;
        PosYrobPres = PosYrob;
        PosRotrobPres = PosRotrob;

        if((indexComboBox!=2)&&(indexComboBox!=6))
        {
                robotdep->setPos(PosYrob,PosXrob);
                robotdep->setRotation(90-PosRotrob);
        }
        qDebug() << "Rotation robot = " << robot1->rotation();

        // remove toutes les lignes de déplacement et les lignes des ventouses
        for(int i=0;i<7;i++)
            scene->removeItem(item[i]);
        for(int i=0;i<4;i++)
            scene->removeItem(collisionLine[i]);
        for(int i=0;i<6;i++){
            scene->removeItem(ventouse[i]);
        }
        for(int i=0;i<6;i++){
            scene->removeItem(brasDistrib[i]);
        }


        switch(indexComboBox)
        {
        case 0: //Début match

            old_equipe = equipe;
            testindex = ui->tableView->model()->index(table_ligne,2);
            if(ui->tableView->model()->data(testindex).toString() == "Jaune")
            {
                testindex = ui->tableView->model()->index(table_ligne,4);
                PosXrob = ui->tableView->model()->data(testindex).toDouble();
                testindex = ui->tableView->model()->index(table_ligne,5);
                PosYrob = ui->tableView->model()->data(testindex).toDouble();
                testindex = ui->tableView->model()->index(table_ligne,3);
                PosRotrob = ((PosRotrobPres)+ui->tableView->model()->data(testindex).toDouble());
                PosRotrobPres=PosRotrob;
                PosXrobPres=PosXrob;
                PosYrobPres=PosYrob;
                equipe = 0;
            }

            else if(ui->tableView->model()->data(testindex).toString() == "Violet")
            {
                testindex = ui->tableView->model()->index(table_ligne,4);
                PosXrob = ui->tableView->model()->data(testindex).toDouble();
                testindex = ui->tableView->model()->index(table_ligne,5);
                PosYrob = 3000 - (ui->tableView->model()->data(testindex).toDouble());
                testindex = ui->tableView->model()->index(table_ligne,3);
                PosRotrob = -((PosRotrobPres)+ui->tableView->model()->data(testindex).toDouble());
                PosRotrobPres=PosRotrob;
                PosXrobPres=PosXrob;
                PosYrobPres=PosYrob;
                equipe = 1;
            }

            break;

        case 1: //Ligne Droite
            // effacer les trassé d'avant
            if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="")

            {
                for(int j=2;j<12;j++)
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,j),"");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,0),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,0)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,2),200);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,6),"Non");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,7),"Attendre");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,10),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,10)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,11),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,11)).toInt()+1);
            }
            testindex = ui->tableView->model()->index(table_ligne,2);
            /*
             * x = distance * cos (angle)
             * y = distance * sin (angle)
             */
            distanceLigneDroite = facteur*(ui->tableView->model()->data(testindex).toDouble());
            PosXrob = PosXrobPres + distanceLigneDroite * cos(((PosRotrobPres) * M_PI)/180);
            PosYrob = PosYrobPres + distanceLigneDroite * sin((PosRotrobPres * M_PI)/180);
            if(table_ligne==index.row())
            {
                // Tracé Ligne centre
                item[0]= scene->addLine(int(PosYrobPres), int(PosXrobPres),int(PosYrob),int(PosXrob),redline);
                // Tracé Ligne gauche
                item[1] = scene->addLine(int(PosYrobPres + LARGEUR_ROBOT/2*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrobPres + LARGEUR_ROBOT/2*cos(((PosRotrobPres-90) * M_PI)/180))
                ,int(PosYrob + LARGEUR_ROBOT/2*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrob + LARGEUR_ROBOT/2*cos(((PosRotrobPres-90) * M_PI)/180)),redline);
                // Tracé Ligne de droite
                item[2] = scene->addLine(int(PosYrobPres - LARGEUR_ROBOT/2*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrobPres - LARGEUR_ROBOT/2*cos(((PosRotrobPres-90) * M_PI)/180))
                ,int(PosYrob - LARGEUR_ROBOT/2*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrob - LARGEUR_ROBOT/2*cos(((PosRotrobPres-90) * M_PI)/180)),redline);

                //deux lignes en plus pour la collision des chasses neiges

                item[3] = scene->addLine(int(PosYrobPres + LARGEUR_ROBOT*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrobPres + LARGEUR_ROBOT*cos(((PosRotrobPres-90) * M_PI)/180))
                ,int(PosYrob + LARGEUR_ROBOT*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrob + LARGEUR_ROBOT*cos(((PosRotrobPres-90) * M_PI)/180)),redline);
                item[3]->hide();

                item[4] = scene->addLine(int(PosYrobPres - LARGEUR_ROBOT*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrobPres - LARGEUR_ROBOT*cos(((PosRotrobPres-90) * M_PI)/180))
                ,int(PosYrob - LARGEUR_ROBOT*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrob - LARGEUR_ROBOT*cos(((PosRotrobPres-90) * M_PI)/180)),redline);
                item[4]->hide();

                if(chasseNeigeFlag[0]){
                    qDebug() << "NIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIK";
                    item[4]->setVisible(true);
                    item[3]->setVisible(true);
                    for(int i=0;i<5;i++){
                        for(int j =0;j<3;j++){
                            if(item[i]->collidesWithItem(ptrEchantillon[i + 12])){
                                qDebug() << "site de fouille jaune";
                                coordonneesBase[12][1] += 4000;
                                coordonneesBase[13][1] += 4000;
                                coordonneesBase[14][1] += 4000;


                                chasseNeigeFlag[1] = true;

                            }
                            else if(item[i]->collidesWithItem(ptrEchantillon[i + 15])){
                                qDebug() << "site de fouille violet";
                                coordonneesBase[15][1] += 4000;
                                coordonneesBase[16][1] += 4000;
                                coordonneesBase[17][1] += 4000;
                                chasseNeigeFlag[1] = true;
                            }
                        }
                    }
                }

            }
            // calcul si le mouvement a permis de prendre un gobelet

            // calcul de la trajectoire des ventouses pour savoir si on a attraper un gobelet
            if(distanceLigneDroite>0)
                avt_arr=0;
            else
                avt_arr=3;

            // Avt Gauche
            Xoffset=Ventouse_coo[0+avt_arr][0]*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[0+avt_arr][1]*sin(((PosRotrob) * M_PI)/180);
            Yoffset=Ventouse_coo[0+avt_arr][0]*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[0+avt_arr][1]*cos(((PosRotrob) * M_PI)/180);
            Trajectoire_Ventouse[0+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[0+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[0+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[0+avt_arr][3]=int(PosYrob+Yoffset);
            // Avt Centre
            Xoffset=Ventouse_coo[1+avt_arr][0]*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[1+avt_arr][1]*sin(((PosRotrob) * M_PI)/180);
            Yoffset=Ventouse_coo[1+avt_arr][0]*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[1+avt_arr][1]*cos(((PosRotrob) * M_PI)/180);
            Trajectoire_Ventouse[1+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[1+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[1+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[1+avt_arr][3]=int(PosYrob+Yoffset);
            // Avt Droite
            Xoffset=Ventouse_coo[2+avt_arr][0]*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[2+avt_arr][1]*sin(((PosRotrob) * M_PI)/180);
            Yoffset=Ventouse_coo[2+avt_arr][0]*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[2+avt_arr][1]*cos(((PosRotrob) * M_PI)/180);
            Trajectoire_Ventouse[2+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[2+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[2+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[2+avt_arr][3]=int(PosYrob+Yoffset);

            // vérifie si la trajectoire passe par un cercle de 30mm de diamétre (centre du gobelet)
            for(int i=0+avt_arr;i<3+avt_arr;i++)
            {
                // si ventouse est activé et que pas de gobelet pris
                if((Ventouse_Action_Gobelet[i][0]==ON)&&(Ventouse_Action_Gobelet[i][1]==100))
                {
                    // vérifie si la trajectoire passe par un cercle de 30mm de diamétre (centre du gobelet)
                    for(int j=0;j<24;j++)
                    {
                        xc=double(Gobelet_coord[j][0]);
                        yc=double(Gobelet_coord[j][1]);
                        m=(double(Trajectoire_Ventouse[i][3])-double(Trajectoire_Ventouse[i][1]))
                                /(double(Trajectoire_Ventouse[i][2])-double(Trajectoire_Ventouse[i][0]));
                        p=double(Trajectoire_Ventouse[i][1])-m*double(Trajectoire_Ventouse[i][0]);
                        R=20;
                        // Si déplacement sur l'axe des x plus grand que sur l'axe des y
                        if(abs(Trajectoire_Ventouse[i][0]-Trajectoire_Ventouse[i][2])>abs(Trajectoire_Ventouse[i][1]-Trajectoire_Ventouse[i][3]))
                        {
                            if(Trajectoire_Ventouse[i][0]<Trajectoire_Ventouse[i][2]) // si x arrivee plus grand que x depart
                            {
                                Xdepart=Trajectoire_Ventouse[i][0];
                                Xarrivee=Trajectoire_Ventouse[i][2];
                            }
                            else // si x depart plus grand que x arrivee
                            {
                                Xdepart=Trajectoire_Ventouse[i][2];
                                Xarrivee=Trajectoire_Ventouse[i][0];
                            }
                            for(x=Xdepart;x<Xarrivee;x++) // parcours l'axe des x mm par mm pour voir si la trajectoire du robot croise le gobelet
                            {
                                if(Trajectoire_Ventouse[i][1]==Trajectoire_Ventouse[i][3]) // si trajectoire parllele à l'axe des x
                                        y=Trajectoire_Ventouse[i][1];
                                else
                                        y=m*x+p;
                                calcul=((x-xc)*(x-xc)+(y-yc)*(y-yc));
                                if(calcul<R*R) // trajectoire croise le gobelet
                                {
                                    Ventouse_Action_Gobelet[i][1]=j; // affecte à la ventouse le numero de gobelet
                                    if(Pen[j]==ellipsered) Ventouse_Couleur_Gobelet[i]=RED;
                                    else if(Pen[j]==ellipsegreen) Ventouse_Couleur_Gobelet[i]=GREEN;
                                    break; // casse la boucle for
                                }
                            }
                        }
                        else // Si déplacement sur l'axe des y plus grand que sur l'axe des x
                        {
                            if(Trajectoire_Ventouse[i][1]<Trajectoire_Ventouse[i][3]) // si y arrivee plus grand que y depart
                            {
                                Ydepart=Trajectoire_Ventouse[i][1];
                                Yarrivee=Trajectoire_Ventouse[i][3];
                            }
                            else // si y depart plus grand que y arrivee
                            {
                                Ydepart=Trajectoire_Ventouse[i][3];
                                Yarrivee=Trajectoire_Ventouse[i][1];
                            }
                            for(y=Ydepart;y<Yarrivee;y++)
                            {
                                if(Trajectoire_Ventouse[i][0]==Trajectoire_Ventouse[i][2]) // si trajectoire parllele à l'axe des y
                                    x=Trajectoire_Ventouse[i][0];
                                else
                                    x=(y-p)/m;
                                calcul=((x-xc)*(x-xc)+(y-yc)*(y-yc));
                                if(calcul<R*R)
                                {
                                    Ventouse_Action_Gobelet[i][1]=j;
                                    if(Pen[j]==ellipsered) Ventouse_Couleur_Gobelet[i]=RED;
                                    else if(Pen[j]==ellipsegreen) Ventouse_Couleur_Gobelet[i]=GREEN;
                                    break;
                                }
                            }
                        }

                    }
                }
            }

            break;

        case 2: //Rotation
            if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="")
            {
                for(int j=2;j<12;j++)
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,j),"");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,0),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,0)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,2),0);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),"Absolu");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,6),"Non");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,7),"Attendre");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,10),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,10)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,11),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,11)).toInt()+1);
            }

            if(equipe == 0)
            {
                testindex = ui->tableView->model()->index(table_ligne,2);
                angleRotation=ui->tableView->model()->data(testindex).toDouble();
                if(ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString()=="Relatif")
                    PosRotrob = (PosRotrobPres + angleRotation);
                else
                    PosRotrob = angleRotation;
            }
            if(equipe == 1)
            {
                testindex = ui->tableView->model()->index(table_ligne,2);
                angleRotation=ui->tableView->model()->data(testindex).toDouble();
                if(ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString()=="Relatif")
                    PosRotrob = (PosRotrobPres - angleRotation);
                else
                    PosRotrob = -angleRotation;
            }

            if(table_ligne==index.row())
            {
                unsigned int diag=DIAG_ROBOT1;
                for(int i=0;i<6;i++)
                    if(Ventouse_Action_Gobelet[i][1]!=100)
                        diag=90+DIAG_ROBOT1;
                path1.moveTo((PosYrob+(diag/2)*cos(((90-PosRotrobPres) * M_PI)/180)),PosXrob+(diag/2)*sin(((90-PosRotrobPres) * M_PI)/180));
                path1.arcTo(PosYrob-diag/2,PosXrob-diag/2,diag,diag,PosRotrobPres-90,360);
                item[1]=scene->addPath(path1,blacklinedot);
                path.moveTo((PosYrob+(diag/2)*cos(((90-PosRotrobPres) * M_PI)/180)),PosXrob+(diag/2)*sin(((90-PosRotrobPres) * M_PI)/180));
                path.arcTo(PosYrob-diag/2,PosXrob-diag/2,diag,diag,90-PosRotrobPres,PosRotrob-90);
                item[0]=scene->addPath(path,redline);
            }
            break;

        case 3: //Courbe
            if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="")
            {
                for(int j=2;j<12;j++)
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,j),"");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,0),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,0)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,2),500);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),45);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),"Gauche");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,6),"Non");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,7),"Attendre");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,10),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,10)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,11),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,11)).toInt()+1);
            }
            testindex = ui->tableView->model()->index(table_ligne,2);
            rayonCourbe = ui->tableView->model()->data(testindex).toDouble();
            testindex = ui->tableView->model()->index(table_ligne,3);
            angleCourbe = facteur*(ui->tableView->model()->data(testindex).toDouble());

            //Inversion de sens de courbe si il y a un changement d'équipe
            testindex = ui->tableView->model()->index(table_ligne,4);
            if(equipe==0 && old_equipe==1 && (ui->tableView->model()->data(testindex).toString()) == "Gauche")
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),"Droite");
            }
            else if(equipe==0 && old_equipe==1 && (ui->tableView->model()->data(testindex).toString()) == "Droite")
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),"Gauche");
            }
            else if(equipe==1 && old_equipe==0 && (ui->tableView->model()->data(testindex).toString()) == "Gauche")
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),"Droite");
            }
            else if(equipe==1 && old_equipe==0 && (ui->tableView->model()->data(testindex).toString()) == "Droite")
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),"Gauche");
            }

            if(ui->tableView->model()->data(testindex).toString() == "Gauche")
            {
                // calcul du centre de rotation
                PosCXrob = PosXrobPres - rayonCourbe * sin((PosRotrob * M_PI)/180);
                PosCYrob = PosYrobPres + rayonCourbe * cos((PosRotrob * M_PI)/180);

                PosXrob = PosCXrob + rayonCourbe * sin(((PosRotrob+angleCourbe) * M_PI)/180);
                PosYrob = PosCYrob - rayonCourbe * cos(((PosRotrob+angleCourbe) * M_PI)/180);
                PosRotrob = (PosRotrobPres) + angleCourbe;
                // tracé de la trajectoire
                if(table_ligne==index.row())
                {
                    path.moveTo(PosYrobPres,PosXrobPres);
                    path.arcTo(PosCYrob-rayonCourbe,PosCXrob-rayonCourbe,2*rayonCourbe,2*rayonCourbe,180+PosRotrobPres,angleCourbe);
                    item[0]=scene->addPath(path,redline);
                    path.moveTo(int(PosYrobPres - LARGEUR_ROBOT/2*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrobPres - LARGEUR_ROBOT/2*cos(((PosRotrobPres-90) * M_PI)/180)));
                    path.arcTo(PosCYrob-rayonCourbe+LARGEUR_ROBOT/2,PosCXrob-rayonCourbe+LARGEUR_ROBOT/2,2*(rayonCourbe-LARGEUR_ROBOT/2),2*(rayonCourbe-LARGEUR_ROBOT/2)
                               ,180+PosRotrobPres,angleCourbe);
                    item[1]=scene->addPath(path,redline);
                    path.moveTo(int(PosYrobPres + LARGEUR_ROBOT/2*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrobPres + LARGEUR_ROBOT/2*cos(((PosRotrobPres-90) * M_PI)/180)));
                    path.arcTo(PosCYrob-rayonCourbe-LARGEUR_ROBOT/2,PosCXrob-rayonCourbe-LARGEUR_ROBOT/2,2*(rayonCourbe+LARGEUR_ROBOT/2),2*(rayonCourbe+LARGEUR_ROBOT/2)
                               ,180+PosRotrobPres,angleCourbe);
                    item[2]=scene->addPath(path,redline);
                    unsigned int diag=DIAG_ROBOT1;
                    for(int i=0;i<6;i++)
                        if(Ventouse_Action_Gobelet[i][1]!=100)
                            diag=90+DIAG_ROBOT1;
                    path1.moveTo((PosYrob+(diag/2)*cos(((90-PosRotrobPres) * M_PI)/180)),PosXrob+(diag/2)*sin(((90-PosRotrobPres) * M_PI)/180));
                    path1.arcTo(PosYrob-diag/2,PosXrob-diag/2,diag,diag,PosRotrobPres-90,360);
                    item[3]=scene->addPath(path1,blacklinedot);
                    path.moveTo((PosYrob+(diag/2)*cos(((90-PosRotrobPres) * M_PI)/180)),PosXrob+(diag/2)*sin(((90-PosRotrobPres) * M_PI)/180));
                    path.arcTo(PosYrob-diag/2,PosXrob-diag/2,diag,diag,PosRotrobPres-90,PosRotrobPres-PosRotrob);
                    item[4]=scene->addPath(path,redline);
                }
            }
            else
            {
                // calcul du centre de rotation
                PosCXrob = PosXrobPres + rayonCourbe * sin((PosRotrob * M_PI)/180);
                PosCYrob = PosYrobPres - rayonCourbe * cos((PosRotrob * M_PI)/180);

                PosXrob = PosCXrob - rayonCourbe * sin(((PosRotrob-angleCourbe) * M_PI)/180);
                PosYrob = PosCYrob + rayonCourbe * cos(((PosRotrob-angleCourbe) * M_PI)/180);
                PosRotrob = (PosRotrobPres) - angleCourbe;
                if(table_ligne==index.row())
                {
                    // tracé de la trajectoire
                    scene->removeItem(item[0]);
                    scene->removeItem(item[1]);
                    scene->removeItem(item[2]);
                    path.moveTo(PosYrobPres,PosXrobPres);
                    path.arcTo(PosCYrob-rayonCourbe,PosCXrob-rayonCourbe,2*rayonCourbe,2*rayonCourbe,PosRotrobPres,-angleCourbe);
                    item[0]=scene->addPath(path,redline);
                    path.moveTo(int(PosYrobPres + LARGEUR_ROBOT/2*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrobPres + LARGEUR_ROBOT/2*cos(((PosRotrobPres-90) * M_PI)/180)));
                    path.arcTo(PosCYrob-rayonCourbe+LARGEUR_ROBOT/2,PosCXrob-rayonCourbe+LARGEUR_ROBOT/2,2*(rayonCourbe-LARGEUR_ROBOT/2),2*(rayonCourbe-LARGEUR_ROBOT/2)
                               ,PosRotrobPres,-angleCourbe);
                    item[1]=scene->addPath(path,redline);
                    path.moveTo(int(PosYrobPres - LARGEUR_ROBOT/2*sin(((PosRotrobPres-90) * M_PI)/180)), int(PosXrobPres - LARGEUR_ROBOT/2*cos(((PosRotrobPres-90) * M_PI)/180)));
                    path.arcTo(PosCYrob-rayonCourbe-LARGEUR_ROBOT/2,PosCXrob-rayonCourbe-LARGEUR_ROBOT/2,2*(rayonCourbe+LARGEUR_ROBOT/2),2*(rayonCourbe+LARGEUR_ROBOT/2)
                               ,PosRotrobPres,-angleCourbe);
                    item[2]=scene->addPath(path,redline);

                }
            }
            // calcul si le mouvement a permis de prendre un gobelet

            // calcul de la trajectoire des ventouses pour savoir si on a attraper un gobelet
            if(angleCourbe>0)
                avt_arr=0;
            else
                avt_arr=3;

            // Avt Gauche
            Xoffset=Ventouse_coo[0+avt_arr][0]*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[0+avt_arr][1]*sin(((PosRotrob) * M_PI)/180);
            Yoffset=Ventouse_coo[0+avt_arr][0]*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[0+avt_arr][1]*cos(((PosRotrob) * M_PI)/180);
            Trajectoire_Ventouse[0+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[0+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[0+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[0+avt_arr][3]=int(PosYrob+Yoffset);
            // calcul du rayon de courbure de la ventouse
            x=PosXrob+Xoffset;
            y=PosYrob+Yoffset;
            xc=PosCXrob;
            yc=PosCYrob;
            rayonCourbeVent[0+avt_arr]=sqrt(double((x-xc)*(x-xc))+double((y-yc)*(y-yc)));

            // Avt Centre
            Xoffset=Ventouse_coo[1+avt_arr][0]*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[1+avt_arr][1]*sin(((PosRotrob) * M_PI)/180);
            Yoffset=Ventouse_coo[1+avt_arr][0]*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[1+avt_arr][1]*cos(((PosRotrob) * M_PI)/180);
            Trajectoire_Ventouse[1+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[1+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[1+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[1+avt_arr][3]=int(PosYrob+Yoffset);
            // calcul du rayon de courbure de la ventouse
            x=PosXrob+Xoffset;
            y=PosYrob+Yoffset;
            xc=PosCXrob;
            yc=PosCYrob;
            rayonCourbeVent[1+avt_arr]=sqrt(double((x-xc)*(x-xc))+double((y-yc)*(y-yc)));

            // Avt Droite
            Xoffset=Ventouse_coo[2+avt_arr][0]*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[2+avt_arr][1]*sin(((PosRotrob) * M_PI)/180);
            Yoffset=Ventouse_coo[2+avt_arr][0]*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[2+avt_arr][1]*cos(((PosRotrob) * M_PI)/180);
            Trajectoire_Ventouse[2+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[2+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[2+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[2+avt_arr][3]=int(PosYrob+Yoffset);
            // calcul du rayon de courbure de la ventouse
            x=PosXrob+Xoffset;
            y=PosYrob+Yoffset;
            xc=PosCXrob;
            yc=PosCYrob;
            rayonCourbeVent[2+avt_arr]=sqrt(double((x-xc)*(x-xc))+double((y-yc)*(y-yc)));

            for(int i=0+avt_arr;i<3+avt_arr;i++)
            {
                rayonCourbeVentouse=rayonCourbeVent[i];
                // si ventouse est activé et que pas de gobelet pris
                if((Ventouse_Action_Gobelet[i][0]==ON)&&(Ventouse_Action_Gobelet[i][1]==100))
                {
                    // vérifie si la trajectoire passe par un cercle de 30mm de diamétre (centre du gobelet)
                    for(int j=0;j<24;j++)
                    {
                        xc=double(Gobelet_coord[j][0]);
                        yc=double(Gobelet_coord[j][1]);
                        R=10;
                        //if(abs(Trajectoire_Ventouse[i][0]-Trajectoire_Ventouse[i][2])>abs(Trajectoire_Ventouse[i][1]-Trajectoire_Ventouse[i][3]))
                        //{
                            if(Trajectoire_Ventouse[i][0]<Trajectoire_Ventouse[i][2])
                            {
                                Xdepart=Trajectoire_Ventouse[i][0];
                                Xarrivee=Trajectoire_Ventouse[i][2];
                            }
                            else
                            {
                                Xdepart=Trajectoire_Ventouse[i][2];
                                Xarrivee=Trajectoire_Ventouse[i][0];
                            }
                            for(x=Xdepart;x<Xarrivee;x++)
                            {
                                if(PosCYrob>0)
                                    y=sqrt((rayonCourbeVentouse*rayonCourbeVentouse-(x-PosCXrob)*(x-PosCXrob)))-PosCYrob;
                                else
                                    y=sqrt((rayonCourbeVentouse*rayonCourbeVentouse-(x-PosCXrob)*(x-PosCXrob)))+PosCYrob;
                                y=abs(y);
                                calcul=((x-xc)*(x-xc)+(y-yc)*(y-yc));
                                if(calcul<=R*R)
                                {
                                    Ventouse_Action_Gobelet[i][1]=j;
                                    if(Pen[j]==ellipsered) Ventouse_Couleur_Gobelet[i]=RED;
                                    else if(Pen[j]==ellipsegreen) Ventouse_Couleur_Gobelet[i]=GREEN;
                                    break;
                                }
                            }
                        //}
                        //else
                        //{
                            if(Trajectoire_Ventouse[i][1]<Trajectoire_Ventouse[i][3])
                            {
                                Ydepart=Trajectoire_Ventouse[i][1];
                                Yarrivee=Trajectoire_Ventouse[i][3];
                            }
                            else
                            {
                                Ydepart=Trajectoire_Ventouse[i][3];
                                Yarrivee=Trajectoire_Ventouse[i][1];
                            }
                            for(y=Ydepart;y<Yarrivee;y++)
                            {
                                if(PosCXrob>0)
                                    x=sqrt((rayonCourbeVentouse*rayonCourbeVentouse-(y-PosCYrob)*(y-PosCYrob)))-PosCXrob;
                                else
                                    x=sqrt((rayonCourbeVentouse*rayonCourbeVentouse)-((y-PosCYrob)*(y-PosCYrob)))+PosCXrob;
                                x=abs(x);
                                calcul=((x-xc)*(x-xc)+(y-yc)*(y-yc));
                                if(calcul<=R*R)
                                {
                                    Ventouse_Action_Gobelet[i][1]=j;
                                    if(Pen[j]==ellipsered) Ventouse_Couleur_Gobelet[i]=RED;
                                    else if(Pen[j]==ellipsegreen) Ventouse_Couleur_Gobelet[i]=GREEN;
                                    break;
                                }
                            }
                        //}

                    }
                }
            }


            break;

        case 4: //Action
            if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="")
            {
                scene->removeItem(item[0]);
                scene->removeItem(item[1]);
                scene->removeItem(item[2]);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,0),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,0)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,2),"Prise_bas");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),0);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,10),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,10)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,11),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,11)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,6),"Non");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,7),"Enchainement");
            }

            numero_action=(ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toUInt());
            numero_manche=numero_action;
            //Inversion des pompes et bras selectionnés si il y a un changement d'équipe
            if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="VENT_AT") ||
               ((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="VENT_RE") ||
               ((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="BRAS_AT") ||
               ((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="BRAS_RE")||
               ((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="BRAS_PREPA")||
               ((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="BRAS_POSE"))
            {
                if(equipe!=old_equipe)
                {
                    switch(numero_action)
                    {
                    case 0: numero_action = 2;break;
                    case 2: numero_action = 0;break;
                    case 3: numero_action = 5;break;
                    case 5: numero_action = 3;break;
                    case 10:numero_action = 21;break;
                    case 21:numero_action = 10;break;
                    case 43:numero_action = 54;break;
                    case 54:numero_action = 43;break;
                    }
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),numero_action);
                }
            }
            //Fonctions correspondant au type d'action selectionnée

//Prise_bas____________________________________________________________________________________________________________

            if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Prise_bas")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!="")){

                int brasChoisi = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt());
                QString brasChoisiStr = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString());
                int tabBrasChoisi[3];

                if (brasChoisiStr == "120" || brasChoisiStr == "102" || brasChoisiStr == "012" || brasChoisiStr == "021" || brasChoisiStr == "201" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),210);
                if (brasChoisiStr == "354" || brasChoisiStr == "453" || brasChoisiStr == "435" || brasChoisiStr == "543" || brasChoisiStr == "534" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),345);


                //on determine la centaine, la dizaine et l'unité

                tabBrasChoisi[0] = brasChoisi/100;
                tabBrasChoisi[1] = (brasChoisi - 100*tabBrasChoisi[0])/10; // on enleve la centaine pour trouver la dizaine
                tabBrasChoisi[2] = (brasChoisi - 100*tabBrasChoisi[0]) - 10*tabBrasChoisi[1]; // on enleve la centaine et la dizaine pour trouver l'unité

                // on creer le rectangle qui va contenir le rond qui correspond à la ventouse
                QRect ellipseVentouse(0,0,54,54);
                int echantillonAttrape;



                //on verifie les collisions avec la ventouse qui correspond au bras selectionner par la centaine , la dizaine et l'unité
                // ex : 210 va activer les bras 1 ,2 et 0
                for(int i = 0; i<3;i++){
                   if(tabBrasChoisi[i] != 0 || i == 2 ){
                       ventouse[tabBrasChoisi[i]] = scene->addEllipse(ellipseVentouse);
                       ventouse[tabBrasChoisi[i]]->setPen(redline);
                       echantillonAttrape = collisionVentouse(tabBrasChoisi[i],PosRotrob);
                       if(echantillonAttrape != -1){
                           coordonnees[echantillonAttrape][5] = tabBrasChoisi[i] + 1;
                           bras[tabBrasChoisi[i] + 1] = ventouse[tabBrasChoisi[i] + 1]->pos();
                       }
                   }


                }
            }
//Passe__________________________________________________________________________________________________________
            if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Passe")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!="")){
                int brasChoisi = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt());
                QString brasChoisiStr = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString());
                int tabBrasChoisi[3];

                if (brasChoisiStr == "120" || brasChoisiStr == "102" || brasChoisiStr == "012" || brasChoisiStr == "021" || brasChoisiStr == "201" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),210);
                if (brasChoisiStr == "354" || brasChoisiStr == "453" || brasChoisiStr == "435" || brasChoisiStr == "543" || brasChoisiStr == "534" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),345);


                //on determine la centaine, la dizaine et l'unité

                tabBrasChoisi[0] = brasChoisi/100;
                tabBrasChoisi[1] = (brasChoisi - 100*tabBrasChoisi[0])/10; // on enleve la centaine pour trouver la dizaine
                tabBrasChoisi[2] = (brasChoisi - 100*tabBrasChoisi[0]) - 10*tabBrasChoisi[1]; // on enleve la centaine et la dizaine pour trouver l'unité

                for(int i = 0; i<3;i++){
                    if(tabBrasChoisi[i] != 0 || i == 2 ){
                        for(int J = 0;J < 30; J++){
                            if (coordonnees[J][5] == tabBrasChoisi[i] + 1){
                                coordonnees[J][5] += 10;
                                coordonnees[J][3] = 2;

                            }

                    }
                }


            }
          }

//Pose_bas__________________________________________________________________________________________________________
            if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Pose_bas")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!="")){

                int brasChoisi = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt());
                QString brasChoisiStr = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString());
                int tabBrasChoisi[3];


                if (brasChoisiStr == "120" || brasChoisiStr == "102" || brasChoisiStr == "012" || brasChoisiStr == "021" || brasChoisiStr == "201" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),210);
                if (brasChoisiStr == "354" || brasChoisiStr == "453" || brasChoisiStr == "435" || brasChoisiStr == "543" || brasChoisiStr == "534" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),345);

                //on determine la centaine, la dizaine et l'unité

                tabBrasChoisi[0] = brasChoisi/100;
                tabBrasChoisi[1] = (brasChoisi - 100*tabBrasChoisi[0])/10; // on enleve la centaine pour trouver la dizaine
                tabBrasChoisi[2] = (brasChoisi - 100*tabBrasChoisi[0]) - 10*tabBrasChoisi[1]; // on enleve la centaine et la dizaine pour trouver l'unité

                //on remet le bras choisi à 0 dans le tableau de coordonnées
                for(int i = 0; i<3;i++){
                   if(tabBrasChoisi[i] != 0 || i == 2 ){
                        for(int J = 0;J < 30; J++){
                            if (coordonnees[J][5] == tabBrasChoisi[i] + 1){

                                coordonnees[J][5] = 0;
                                coordonnees[J][0] += ptrEchantillon[i]->boundingRect().center().x() - GLOBALOFFSETX;
                                coordonnees[J][1] += ptrEchantillon[i]->boundingRect().center().y() - GLOBALOFFSETY;
                            }
                        }
                   }
                }

            }
//Pose_Haut__________________________________________________________________________________________________________________
            if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Pose_Haut")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!="")){

                int brasChoisi = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt());
                QString brasChoisiStr = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString());
                int tabBrasChoisi[3];


                if (brasChoisiStr == "120" || brasChoisiStr == "102" || brasChoisiStr == "012" || brasChoisiStr == "021" || brasChoisiStr == "201" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),210);
                if (brasChoisiStr == "354" || brasChoisiStr == "453" || brasChoisiStr == "435" || brasChoisiStr == "543" || brasChoisiStr == "534" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),345);

                //on determine la centaine, la dizaine et l'unité

                tabBrasChoisi[0] = brasChoisi/100;
                tabBrasChoisi[1] = (brasChoisi - 100*tabBrasChoisi[0])/10; // on enleve la centaine pour trouver la dizaine
                tabBrasChoisi[2] = (brasChoisi - 100*tabBrasChoisi[0]) - 10*tabBrasChoisi[1]; // on enleve la centaine et la dizaine pour trouver l'unité

                //on remet le bras choisi à 0 dans le tableau de coordonnées
                for(int i = 0; i<3;i++){
                   if(tabBrasChoisi[i] != 0 || i == 2 ){
                        for(int J = 0;J < 30; J++){
                            if (coordonnees[J][5] == tabBrasChoisi[i] + 11){

                                coordonnees[J][5] = 0;
                                coordonnees[J][3] = 1;
                                coordonnees[J][0] += ptrEchantillon[i]->boundingRect().center().x() - GLOBALOFFSETX;
                                coordonnees[J][1] += ptrEchantillon[i]->boundingRect().center().y() - GLOBALOFFSETY;
                            }
                        }
                   }
                }
            }
//Prise_bordure_____________________________________________________________________________________________________________
            if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Prise_bordure")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!="")){

                int brasChoisi = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt());
                QString brasChoisiStr = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString());
                int tabBrasChoisi[3];

                if (brasChoisiStr == "120" || brasChoisiStr == "102" || brasChoisiStr == "012" || brasChoisiStr == "021" || brasChoisiStr == "201" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),210);
                if (brasChoisiStr == "354" || brasChoisiStr == "453" || brasChoisiStr == "435" || brasChoisiStr == "543" || brasChoisiStr == "534" )
                    ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),345);


                //on determine la centaine, la dizaine et l'unité

                tabBrasChoisi[0] = brasChoisi/100;
                tabBrasChoisi[1] = (brasChoisi - 100*tabBrasChoisi[0])/10; // on enleve la centaine pour trouver la dizaine
                tabBrasChoisi[2] = (brasChoisi - 100*tabBrasChoisi[0]) - 10*tabBrasChoisi[1]; // on enleve la centaine et la dizaine pour trouver l'unité

                // on creer le rectangle qui va contenir le rond qui correspond à la ventouse
                QRect ellipseVentouse(0,0,54,54);
                int echantillonAttrape;



                //on verifie les collisions avec la ventouse qui correspond au bras selectionner par la centaine , la dizaine et l'unité
                // ex : 210 va activer les bras 1 ,2 et 0
                for(int i = 0; i<3;i++){
                   if(tabBrasChoisi[i] != 0 || i == 2 ){
                       ventouse[tabBrasChoisi[i]] = scene->addEllipse(ellipseVentouse);
                       ventouse[tabBrasChoisi[i]]->setPen(greenline);
                       echantillonAttrape = collisionVentouse(tabBrasChoisi[i],PosRotrob);
                       if(echantillonAttrape != -1){
                           coordonnees[echantillonAttrape][5] = tabBrasChoisi[i] + 1 + 10;
                           bras[tabBrasChoisi[i] + 1] = ventouse[tabBrasChoisi[i] + 1]->pos();
                       }
                   }


                }
            }


//Prise_distrib_______________________________________________________________________________________________________________________
            else if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Prise_distrib")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!="")){
                QLine ligneDistrib(0,0,232,0);

                //on fait apparaitre le bon bras sur la scene
                int brasChoisi = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt());

                brasDistrib[brasChoisi] = scene->addLine(ligneDistrib);

                //on le place au bon endroit
                brasDistrib[brasChoisi]->setPen(redline);
                brasDistrib[brasChoisi]->setPos(robot1->pos() + robot1->boundingRect().center());


                switch(brasChoisi){
                case 0 :
                    brasDistrib[brasChoisi]->moveBy(0,135);
                    break;
                case 2 :
                    brasDistrib[brasChoisi]->moveBy(0,-135);
                    break;
                case 3 :
                    brasDistrib[brasChoisi]->moveBy(-232,135);
                    break;
                case 5 :
                    brasDistrib[brasChoisi]->moveBy(-232,-135);
                    break;
                default : break;
                }

                brasDistrib[brasChoisi]->setRotation(90 - PosRotrob);


                //on vérifie la collision avec l'échantillon le plus plus éloigné de chaque distributeur (pour être sur d'être a la bonne distance)

                if(brasDistrib[brasChoisi]->collidesWithItem(ptrEchantillon[18])){ //jaune bas
                    coordonnees[20][5] = 12;
                    coordonnees[19][5] = 13;
                    coordonnees[18][5] = 11;
                }
                if(brasDistrib[brasChoisi]->collidesWithItem(ptrEchantillon[21])){ //jaune haut
                    coordonnees[23][5] = 15;
                    coordonnees[22][5] = 16;
                    coordonnees[21][5] = 14;
                }
                if(brasDistrib[brasChoisi]->collidesWithItem(ptrEchantillon[24])){ //violet bas
                    coordonnees[26][5] = 12;
                    coordonnees[25][5] = 13;
                    coordonnees[24][5] = 11;
                }
                if(brasDistrib[brasChoisi]->collidesWithItem(ptrEchantillon[27])){ //violet haut
                    coordonnees[29][5] = 15;
                    coordonnees[28][5] = 16;
                    coordonnees[27][5] = 14;
                }


            }
//Deploiement________________________________________________________________________________________________________________
            else if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Deploiement")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!="")){
                int ouvertFerme = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt()); // on met a 0 pour ouvrir a 1 pour fermé

                chasseNeigeFlag[0] = ouvertFerme;


            }


            else if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Res_prestest")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!=""))
            {
                resDeploye[(ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt())] = true;
            }
            else if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Res_mes")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!=""))
            {
                int carreMesure = (ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt());
                if (brasMesure[0]->collidesWithItem(ptrCarre[carreMesure])){

                    ptrCarre[carreMesure]->hide();
                }
                else if (brasMesure[1]->collidesWithItem(ptrCarre[carreMesure])){

                    ptrCarre[carreMesure]->hide();
                }
            }
            else if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Res_rang")
                &&((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toString())!=""))
            {
                resDeploye[(ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,3)).toInt())] = false;
            }





            break;

        case 5: //Recalage
            if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="")
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,0),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,0)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,2),"Arrière");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),"Mécanique");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),"Abscisse");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,5),"Rob-");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,10),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,10)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,11),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,11)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,6),"Non");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,7),"Enchainement");
            }

            if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,5)).toString())=="Rob-") newValue = 115;
            else if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,5)).toString())=="Rob+") newValue = 1885;
            else if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,5)).toString())=="Gob-") newValue = 168;
            else if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,5)).toString())=="Gob+") newValue = 1832;
            else newValue=115;

            //Recalage Abscisse
            if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,4)).toString())=="Abscisse") && ((PosRotrob == 90.)||(PosRotrob == 270.)))
            {
                //arrière abscisse
                if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Arrière" && (PosRotrob == 90.))
                {
                    PosYrob= newValue;
                    robot1->setPos(PosYrob,PosXrob);
                }
                else if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Arrière" && (PosRotrob == 270.))
                {
                    PosYrob = newValue;
                    robot1->setPos(PosYrob,PosXrob);
                }
                //avant abscisse
                else if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Avant" && (PosRotrob == 90.))
                {
                    PosYrob = newValue;
                    robot1->setPos(PosYrob,PosXrob);
                }
                else if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Avant" && (PosRotrob == 270.))
                {
                    PosYrob = newValue;
                    robot1->setPos(PosYrob,PosXrob);
                }
            }

            //Recalage Ordonnée
            else if(((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,4)).toString())=="Ordonnée") && ((PosRotrob == 0.)||(PosRotrob == 180.)))
            {
                //Arrière Ordonnée
                if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Arrière" && (PosRotrob == 0.))
                {
                    PosXrob = newValue;
                    robot1->setPos(PosYrob,PosXrob);
                }
                else if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Arrière" && (PosRotrob == 180.))
                {
                    PosXrob = newValue;
                    robot1->setPos(PosYrob,PosXrob);
                }

                //Avant Ordonnée
                if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Avant" && (PosRotrob == 180.))
                {
                    PosXrob = newValue;
                    robot1->setPos(PosYrob,PosXrob);
                }
                else if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Avant" && (PosRotrob == 0.))
                {
                    PosXrob = newValue;
                    robot1->setPos(PosYrob,PosXrob);
                }
            }
            if(table_ligne==index.row())
            {
            }
            break;

        case 6: //XYT
            int diag=DIAG_ROBOT1;
            double anglefin=0;

            if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="")
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,0),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,0)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,2),"Avant");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,3),PosXrob);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),PosYrob);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,5),PosRotrob);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,6),"Non");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,7),"Attendre");
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,10),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,10)).toInt()+1);
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,11),ui->tableView->model()->data(ui->tableView->model()->index(table_ligne-1,11)).toInt()+1);
            }

            testindex = ui->tableView->model()->index(table_ligne,3);
            PosXrob = ui->tableView->model()->data(testindex).toDouble();
            testindex = ui->tableView->model()->index(table_ligne,4);
            PosYrob = ui->tableView->model()->data(testindex).toDouble();
            testindex = ui->tableView->model()->index(table_ligne,5);
            PosRotrob = (ui->tableView->model()->data(testindex).toDouble());

            if(equipe==0 && old_equipe==1) //Jaune à bleu
            {
                PosYrob = 3000-PosYrob;
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),PosYrob);
                PosRotrob = -PosRotrob;
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,5),PosRotrob);
            }
            else if(equipe==1 && old_equipe==0) //bleu à jaune
            {
                PosYrob = 3000-PosYrob;
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,4),PosYrob);
                PosRotrob = -PosRotrob;
                ui->tableView->model()->setData(ui->tableView->model()->index(table_ligne,5),PosRotrob);
            }
            // calculer l'angle à faire pour se positionner sur la ligne droite
            double angle=abs(qAtan2(PosYrob-PosYrobPres,PosXrob-PosXrobPres)* 180)/M_PI;
            avt_arr=0;
            if(PosYrob-PosYrobPres<0)
            {
                angle=-angle;
            }
            if(table_ligne==index.row())
            {
                // Tracé Ligne centre trajectoire du robot
                item[0]= scene->addLine(int(PosYrobPres), int(PosXrobPres),int(PosYrob),int(PosXrob),redline);

                ui->lcdPosArcOffset->display(angle);

                if((ui->tableView->model()->data(ui->tableView->model()->index(table_ligne,2)).toString())=="Arrière")
                {
                    angle+=180;
                    avt_arr=3;
                }
                ui->lcdPosArcDebut->display(angle);
                // Tracé Ligne gauche trajectoire du robot
                item[1] = scene->addLine(int(PosYrobPres + LARGEUR_ROBOT/2*sin(((angle-90) * M_PI)/180)), int(PosXrobPres + LARGEUR_ROBOT/2*cos(((angle-90) * M_PI)/180))
                ,int(PosYrob + LARGEUR_ROBOT/2*sin(((angle-90) * M_PI)/180)), int(PosXrob + LARGEUR_ROBOT/2*cos(((angle-90) * M_PI)/180)),redline);
                // Tracé Ligne de droite trajectoire du robot
                item[2] = scene->addLine(int(PosYrobPres - LARGEUR_ROBOT/2*sin(((angle-90) * M_PI)/180)), int(PosXrobPres - LARGEUR_ROBOT/2*cos(((angle-90) * M_PI)/180))
                ,int(PosYrob - LARGEUR_ROBOT/2*sin(((angle-90) * M_PI)/180)), int(PosXrob - LARGEUR_ROBOT/2*cos(((angle-90) * M_PI)/180)),redline);
                // arc depart
                for(int i=0;i<6;i++)
                    if(Ventouse_Action_Gobelet[i][1]!=100)
                        diag=90+DIAG_ROBOT1;
                path1.moveTo((PosYrobPres+(diag/2)*cos(((90-PosRotrobPres) * M_PI)/180)),PosXrobPres+(diag/2)*sin(((90-PosRotrobPres) * M_PI)/180));
                path1.arcTo(PosYrobPres-diag/2,PosXrobPres-diag/2,diag,diag,PosRotrobPres-90,360);
                item[3]=scene->addPath(path1,blacklinedot);
                path.moveTo((PosYrobPres+(diag/2)*cos(((90-PosRotrobPres) * M_PI)/180)),PosXrobPres+(diag/2)*sin(((90-PosRotrobPres) * M_PI)/180));
                ui->lcdPosArcFin->display(angle-PosRotrobPres);
                robotdep->setRotation(90-angle);
                if(angle-PosRotrobPres<-180)
                    anglefin=360+angle-PosRotrobPres;
                else if(angle-PosRotrobPres>180)
                    anglefin=angle-PosRotrobPres-360;
                else
                    anglefin=angle-PosRotrobPres;
                path.arcTo(PosYrobPres-diag/2,PosXrobPres-diag/2,diag,diag,PosRotrobPres-90,anglefin);
                item[4]=scene->addPath(path,redline);
            }
            // Avt Gauche
            Xoffset=Ventouse_coo[0+avt_arr][0]*cos(((angle) * M_PI)/180)-Ventouse_coo[0+avt_arr][1]*sin(((angle) * M_PI)/180);
            Yoffset=Ventouse_coo[0+avt_arr][0]*sin(((angle) * M_PI)/180)+Ventouse_coo[0+avt_arr][1]*cos(((angle) * M_PI)/180);
            Trajectoire_Ventouse[0+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[0+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[0+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[0+avt_arr][3]=int(PosYrob+Yoffset);
            // Avt Centre
            Xoffset=Ventouse_coo[1+avt_arr][0]*cos(((angle) * M_PI)/180)-Ventouse_coo[1+avt_arr][1]*sin(((angle) * M_PI)/180);
            Yoffset=Ventouse_coo[1+avt_arr][0]*sin(((angle) * M_PI)/180)+Ventouse_coo[1+avt_arr][1]*cos(((angle) * M_PI)/180);
            Trajectoire_Ventouse[1+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[1+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[1+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[1+avt_arr][3]=int(PosYrob+Yoffset);
            // Avt Droite
            Xoffset=Ventouse_coo[2+avt_arr][0]*cos(((angle) * M_PI)/180)-Ventouse_coo[2+avt_arr][1]*sin(((angle) * M_PI)/180);
            Yoffset=Ventouse_coo[2+avt_arr][0]*sin(((angle) * M_PI)/180)+Ventouse_coo[2+avt_arr][1]*cos(((angle) * M_PI)/180);
            Trajectoire_Ventouse[2+avt_arr][0]=int(PosXrobPres+Xoffset);
            Trajectoire_Ventouse[2+avt_arr][1]=int(PosYrobPres+Yoffset);
            Trajectoire_Ventouse[2+avt_arr][2]=int(PosXrob+Xoffset);
            Trajectoire_Ventouse[2+avt_arr][3]=int(PosYrob+Yoffset);

            for(int i=0+avt_arr;i<3+avt_arr;i++)
            {
                // si ventouse est activé et que pas de gobelet pris
                if((Ventouse_Action_Gobelet[i][0]==ON)&&(Ventouse_Action_Gobelet[i][1]==100))
                {
                    // vérifie si la trajectoire passe par un cercle de 30mm de diamétre (centre du gobelet)
                    for(int j=0;j<24;j++)
                    {
                        xc=double(Gobelet_coord[j][0]);
                        yc=double(Gobelet_coord[j][1]);
                        m=(double(Trajectoire_Ventouse[i][3])-double(Trajectoire_Ventouse[i][1]))
                                /(double(Trajectoire_Ventouse[i][2])-double(Trajectoire_Ventouse[i][0]));
                        p=double(Trajectoire_Ventouse[i][1])-m*double(Trajectoire_Ventouse[i][0]);
                        R=15;
                        // Si déplacement sur l'axe des x plus grand que sur l'axe des y
                        if(abs(Trajectoire_Ventouse[i][0]-Trajectoire_Ventouse[i][2])>abs(Trajectoire_Ventouse[i][1]-Trajectoire_Ventouse[i][3]))
                        {
                            if(Trajectoire_Ventouse[i][0]<Trajectoire_Ventouse[i][2]) // si x arrivee plus grand que x depart
                            {
                                Xdepart=Trajectoire_Ventouse[i][0];
                                Xarrivee=Trajectoire_Ventouse[i][2];
                            }
                            else // si x depart plus grand que x arrivee
                            {
                                Xdepart=Trajectoire_Ventouse[i][2];
                                Xarrivee=Trajectoire_Ventouse[i][0];
                            }
                            for(x=Xdepart;x<Xarrivee;x++) // parcours l'axe des x mm par mm pour voir si la trajectoire du robot croise le gobelet
                            {
                                if(Trajectoire_Ventouse[i][1]==Trajectoire_Ventouse[i][3]) // si trajectoire parllele à l'axe des x
                                        y=Trajectoire_Ventouse[i][1];
                                else
                                        y=m*x+p;
                                calcul=((x-xc)*(x-xc)+(y-yc)*(y-yc));
                                if(calcul<R*R) // trajectoire croise le gobelet
                                {
                                    Ventouse_Action_Gobelet[i][1]=j; // affecte à la ventouse le numero de gobelet
                                    if(Pen[j]==ellipsered) Ventouse_Couleur_Gobelet[i]=RED;
                                    else if(Pen[j]==ellipsegreen) Ventouse_Couleur_Gobelet[i]=GREEN;
                                    break; // casse la boucle for
                                }
                            }
                        }
                        else // Si déplacement sur l'axe des y plus grand que sur l'axe des x
                        {
                            if(Trajectoire_Ventouse[i][1]<Trajectoire_Ventouse[i][3]) // si y arrivee plus grand que y depart
                            {
                                Ydepart=Trajectoire_Ventouse[i][1];
                                Yarrivee=Trajectoire_Ventouse[i][3];
                            }
                            else // si y depart plus grand que y arrivee
                            {
                                Ydepart=Trajectoire_Ventouse[i][3];
                                Yarrivee=Trajectoire_Ventouse[i][1];
                            }
                            for(y=Ydepart;y<Yarrivee;y++)
                            {
                                if(Trajectoire_Ventouse[i][0]==Trajectoire_Ventouse[i][2]) // si trajectoire parllele à l'axe des y
                                    x=Trajectoire_Ventouse[i][0];
                                else
                                    x=(y-p)/m;
                                calcul=((x-xc)*(x-xc)+(y-yc)*(y-yc));
                                if(calcul<R*R)
                                {
                                    Ventouse_Action_Gobelet[i][1]=j;
                                    if(Pen[j]==ellipsered) Ventouse_Couleur_Gobelet[i]=RED;
                                    else if(Pen[j]==ellipsegreen) Ventouse_Couleur_Gobelet[i]=GREEN;
                                    break;
                                }
                            }
                        }

                    }
                }
            }
            if(table_ligne==index.row()) // si ligne actuel on trace les arc de cercle pour représenter les rotations
            {
                // arc d arrivee
                for(int i=0;i<6;i++) // on verifie qu'on a au moins gobelet
                {
                    if(Ventouse_Action_Gobelet[i][1]!=100) // si on a un gobelet
                        diag=90+DIAG_ROBOT1; // on augmente le rayon de rotation
                }
                path1.moveTo((PosYrob+(diag/2)*cos(((90-PosRotrobPres) * M_PI)/180)),PosXrob+(diag/2)*sin(((90-PosRotrobPres) * M_PI)/180));
                path1.arcTo(PosYrob-diag/2,PosXrob-diag/2,diag,diag,PosRotrobPres-90,360);
                item[5]=scene->addPath(path1,blacklinedot);
                path.moveTo((PosYrob+(diag/2)*cos(((PosRotrobPres-angle) * M_PI)/180)),PosXrob+(diag/2)*sin(((PosRotrobPres-angle) * M_PI)/180));
                path.arcTo(PosYrob-diag/2,PosXrob-diag/2,diag,diag,anglefin,PosRotrob-anglefin-90);
                item[6]=scene->addPath(path,redline);



            }
            break;
        }// sortie du switch action et deplacement

        //placement du theta entre 0 et 360°
        if(PosRotrob<0)
        {
            PosRotrob=PosRotrob+360;
        }
        else if(PosRotrob>360)
        {
             PosRotrob=PosRotrob-360;
        }
        if((indexComboBox==2)||(indexComboBox==6))
        {
                robotdep->setPos(PosYrob,PosXrob);
                robotdep->setRotation(90-PosRotrob);
        }
        robot1->setPos(PosYrob,PosXrob);
        robot1->setRotation(90-PosRotrob);
        // Affichage de la position en X,Y,T

        // tracé des lignes ventouses
        for(int i=0;i<6;i++)
        {
            scene->removeItem(itemVentouse[i]);
            scene->removeItem(itemTextVentouse[i]);
            Yoffset=Ventouse_coo[i][0]*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[i][1]*cos(((PosRotrob) * M_PI)/180);
            Xoffset=Ventouse_coo[i][0]*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[i][1]*sin(((PosRotrob) * M_PI)/180);
            numero_Gobelet=Ventouse_Action_Gobelet[i][1];
            if(Ventouse_Action_Gobelet[i][0]==ON)
            {
                if(numero_Gobelet==100)
                {
                    int ligne_mouvement=futur_i;
                    int nombre_de_ligne=ui->tableView->model()->rowCount();
                    data = ui->tableView->model()->data(j).toString();
                    unsigned int mouvement=0;
                    while(ligne_mouvement<nombre_de_ligne)
                    {
                        j = ui->tableView->model()->index(ligne_mouvement,1);
                        data = ui->tableView->model()->data(j).toString();
                        mouvement = dataCol1.indexOf(data);
                        if((mouvement==1)||(mouvement==3)||(mouvement)==6)
                        {
                            numero_ligne_courbe=ligne_mouvement;
                            break;
                        }
                        ligne_mouvement=ui->tableView->model()->data(ui->tableView->model()->index(ligne_mouvement,10)).toInt();
                    }

                    if((mouvement==0)||(mouvement==1)) // ligne droite ou pas de mouvement
                        itemVentouse[i] = scene->addLine(int(PosYrob + Yoffset), int(PosXrob + Xoffset)
                    ,int(PosYrob + Yoffset+4000*sin(((PosRotrob+(180*(i/3))) * M_PI)/180)), int(PosXrob + Xoffset+ 4000*cos(((PosRotrob+(180*(i/3))) * M_PI)/180)),blacklinedot);
                    else if(mouvement==3) // courbure
                    {
                        rayonCourbe = ui->tableView->model()->data(ui->tableView->model()->index(numero_ligne_courbe,2)).toDouble();
                        angleCourbe = ui->tableView->model()->data(ui->tableView->model()->index(numero_ligne_courbe,3)).toDouble();
                        double angle,angleDebut,angleFin;
                        if (ui->tableView->model()->data(ui->tableView->model()->index(numero_ligne_courbe,4)).toString() == "Gauche")
                        {
                            angle=abs((qAtan2(rayonCourbe-Ventouse_coo[i][1],Ventouse_coo[i][0])*180/M_PI)-90);
                            if(angleCourbe<0)
                                angle=-angle;
                            // calcul du centre de rotation du robot
                            PosCXrob = PosXrob - rayonCourbe * sin((PosRotrob * M_PI)/180);
                            PosCYrob = PosYrob + rayonCourbe * cos((PosRotrob * M_PI)/180);
                            // calcul du rayon de courbure de la ventouse
                            x=PosXrob+Xoffset;
                            y=PosYrob+Yoffset;
                            xc=PosCXrob;
                            yc=PosCYrob;
                            rayonCourbeVentouse=sqrt(double((x-xc)*(x-xc))+double((y-yc)*(y-yc)));
                            // calcul de l'angle de départ est d'arrivée
                            pathArcVentouse[i].moveTo(y,x);
                            angleDebut=180+PosRotrobPres+angle;
                            angleFin=angleCourbe;
                            pathArcVentouse[i].arcTo(yc-rayonCourbeVentouse,xc-rayonCourbeVentouse,2*rayonCourbeVentouse,2*rayonCourbeVentouse,angleDebut,angleFin);
                            itemVentouse[i]=scene->addPath(pathArcVentouse[i],blacklinedot);
                        }
                        else
                        {
                            angle=abs((qAtan2(rayonCourbe+Ventouse_coo[i][1],Ventouse_coo[i][0])*180/M_PI)-90);
                            if(angleCourbe<0)
                                angle=-angle;
                            // calcul du centre de rotation(
                            PosCXrob = PosXrobPres + rayonCourbe * sin((PosRotrob * M_PI)/180);
                            PosCYrob = PosYrobPres - rayonCourbe * cos((PosRotrob * M_PI)/180);

                            // calcul du rayon de courbure de la ventouse
                            x=PosXrob+Xoffset;
                            y=PosYrob+Yoffset;
                            xc=PosCXrob;
                            yc=PosCYrob;
                            rayonCourbeVentouse=sqrt(double((x-xc)*(x-xc))+double((y-yc)*(y-yc)));
                            // calcul de l'angle de départ est d'arrivée
                            angleDebut=PosRotrobPres-angle;
                            angleFin=-angleCourbe;
                            pathArcVentouse[i].moveTo(y,x);//PosYrobPres+Yoffset,PosXrobPres+Xoffset); // point de depart de l'arc
                            pathArcVentouse[i].arcTo(yc-rayonCourbeVentouse,xc-rayonCourbeVentouse,2*rayonCourbeVentouse,2*rayonCourbeVentouse,angleDebut,angleFin);
                            itemVentouse[i]=scene->addPath(pathArcVentouse[i],blacklinedot);
                        }
                        ui->lcdPosArcOffset->display(angle);
                        ui->lcdPosArcDebut->display(angleDebut);
                        ui->lcdPosArcFin->display(angleFin);
                    }
                    else if(mouvement==6)
                    {
                        double PosXrobfinal = ui->tableView->model()->data(ui->tableView->model()->index(numero_ligne_courbe,3)).toDouble();
                        double PosYrobfinal = ui->tableView->model()->data(ui->tableView->model()->index(numero_ligne_courbe,4)).toDouble();
                        double PosRotrobfinal = (ui->tableView->model()->data(ui->tableView->model()->index(numero_ligne_courbe,5)).toDouble());
                        double angle=abs(qAtan2(PosYrobfinal-PosYrobPres,PosXrobfinal-PosXrobPres)* 180)/M_PI;
                        if(PosYrobfinal-PosYrobPres<0)
                        {
                            angle=-angle;
                        }
                        if((ui->tableView->model()->data(ui->tableView->model()->index(numero_ligne_courbe,2)).toString())=="Arrière")
                        {
                            angle+=180;
                        }
                        Yoffset=Ventouse_coo[i][0]*sin(((angle) * M_PI)/180)+Ventouse_coo[i][1]*cos(((angle) * M_PI)/180);
                        Xoffset=Ventouse_coo[i][0]*cos(((angle) * M_PI)/180)-Ventouse_coo[i][1]*sin(((angle) * M_PI)/180);
                        itemVentouse[i] = scene->addLine(int(PosYrobPres + Yoffset), int(PosXrobPres + Xoffset)
                    ,int(PosYrobfinal + Yoffset+4000*sin(((angle+(180*(i/3))) * M_PI)/180)), int(PosXrobfinal + Xoffset+ 4000*cos(((angle+(180*(i/3))) * M_PI)/180)),blacklinedot);
                    }
                }
                else
                {
                    // affichage gobelet
                    Gobelet_coord[numero_Gobelet][0]=uint(PosXrob + Xoffset); //-36
                    Gobelet_coord[numero_Gobelet][1]=uint(PosYrob + Yoffset); //-36
                    Gobelet[numero_Gobelet]->setPos(Gobelet_coord[numero_Gobelet][1]-36, Gobelet_coord[numero_Gobelet][0]-36);
                    pathtext[i].addText(0,0 , font,  QString::number(i));
                    itemTextVentouse[i]=scene->addPath(pathtext[i], QPen(QBrush(Qt::black), 3), QBrush(Qt::black));
                    itemTextVentouse[i]->setPos(Gobelet_coord[numero_Gobelet][1]-12,Gobelet_coord[numero_Gobelet][0]+12);
                }

            }

            ventouse[i]->setTransformOriginPoint(ventouse[0]->boundingRect().center());
            ventouse[i]->setPos(ROBOTCENTRE);

            switch (i){

                case 0 : ventouse[i]->moveBy((206.06)*sin(((PosRotrob) * M_PI)/180 - 28.6*M_PI/180) , (206.06)*cos(((PosRotrob) * M_PI)/180 - 28.6*M_PI/180));
                        break;
                case 1 : ventouse[i]->moveBy((107.5)*sin(((PosRotrob) * M_PI)/180) , (107.5)*cos(((PosRotrob) * M_PI)/180));
                        break;
                case 2 : ventouse[i]->moveBy((206.06)*sin(((PosRotrob) * M_PI)/180 + 28.6*M_PI/180) , (206.06)*cos(((PosRotrob) * M_PI)/180 + 28.6*M_PI/180));
                        break;
                case 5 : ventouse[i]->moveBy((206.06)*sin(((PosRotrob) * M_PI)/180 + 28.6*M_PI/180 + M_PI) , (206.06)*cos(((PosRotrob) * M_PI)/180 + 28.6*M_PI/180 + M_PI));
                        break;
                case 4 : ventouse[i]->moveBy((107.5)*sin(((PosRotrob) * M_PI)/180 + M_PI) , (107.5)*cos(((PosRotrob) * M_PI)/180 + M_PI));
                        break;
                case 3 : ventouse[i]->moveBy((206.06)*sin(((PosRotrob) * M_PI)/180 + 28.6*M_PI/180 - M_PI) , (206.06)*cos(((PosRotrob) * M_PI)/180 - 28.6*M_PI/180 + M_PI));
                        break;
            }

            bras[i + 1] = ventouse[i]->pos();
            //bras[i + 11] = ventouse[i + 10]->pos();



            if(resDeploye[0]){
                scene->removeItem(brasMesure[0]); // on supprime le bras

                int signeoffset0;
                QRect rect0(0,0,100,150);


                //on ajoutre le bras et place son point de transformation au point de contact avec le robot
                brasMesure[0]= scene->addRect(rect0);
                brasMesure[0]->setPen(redline);
                brasMesure[0]->setTransformOriginPoint(brasMesure[0]->boundingRect().center().x(),0);







                brasMesure[0]->setPos(robot1->pos() + robot1->boundingRect().center());
                brasMesure[0]->setRotation(90 - PosRotrob);
                brasMesure[0]->moveBy(-50,135+150);


            }
            else
                scene->removeItem(brasMesure[0]);

            if(resDeploye[1]){
                scene->removeItem(brasMesure[1]); // on supprime le bras


                QRect rect1(0,0,100,150);

                //on ajoutre le bras et place son point de transformation au point de contact avec le robot
                brasMesure[1]= scene->addRect(rect1);
                brasMesure[1]->setPen(redline);
                brasMesure[1]->setTransformOriginPoint(brasMesure[1]->boundingRect().center().x(),0);

                //on détermine l'offset



                brasMesure[1]->setPos(robot1->pos() + robot1->boundingRect().center());
                brasMesure[1]->setRotation(90 - PosRotrob);
                brasMesure[1]->moveBy(-50,130);

            }
            else
                scene->removeItem(brasMesure[1]);

            qDebug() << "cos(M_PI) = " << cos(M_PI);
            qDebug() << "cos(180) = " << cos(180);
        }
        for(int i=0;i<6;i++)
        {
            scene->removeItem(itemTextBrasVentouse[i]);
            if(Bras_Action_Gobelet[i][0]==ON)
            {
                int numero_gobelet=Bras_Action_Gobelet[i][1];
                // change coord gobelet et deplacement
                if(Bras_Action_Gobelet[i][2]==ON)
                {
                    Yoffset=(Ventouse_coo[i][0]*1.6)*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[i][1]*cos(((PosRotrob) * M_PI)/180);
                    Xoffset=(Ventouse_coo[i][0]*1.6)*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[i][1]*sin(((PosRotrob) * M_PI)/180);
                }
                else
                {
                    Yoffset=Ventouse_coo[i][0]/2*sin(((PosRotrob) * M_PI)/180)+Ventouse_coo[i][1]*cos(((PosRotrob) * M_PI)/180);
                    Xoffset=Ventouse_coo[i][0]/2*cos(((PosRotrob) * M_PI)/180)-Ventouse_coo[i][1]*sin(((PosRotrob) * M_PI)/180);
                }
                Gobelet_coord_ecueil[numero_gobelet][0]=uint(PosXrob + Xoffset-36);
                Gobelet_coord_ecueil[numero_gobelet][1]=uint(PosYrob + Yoffset-36);
                Gobelet[numero_gobelet+24]->setPos(Gobelet_coord_ecueil[numero_gobelet][1], Gobelet_coord_ecueil[numero_gobelet][0]);
                pathtext[i].addText(0,0 , font,  QString::number(i));
                itemTextBrasVentouse[i]=scene->addPath(pathtext[i], QPen(QBrush(Qt::black), 3), QBrush(Qt::black));
                itemTextBrasVentouse[i]->setPos(Gobelet_coord_ecueil[numero_gobelet][1]+24,Gobelet_coord_ecueil[numero_gobelet][0]+48);
            }
        }
        for(int i=0;i<2;i++)
        {
            scene->removeItem(itemManche[i]);
            int angle;
            Yoffset=Manche_coord[i][0]*sin(((PosRotrob) * M_PI)/180)+Manche_coord[i][1]*cos(((PosRotrob) * M_PI)/180);
            Xoffset=Manche_coord[i][0]*cos(((PosRotrob) * M_PI)/180)-Manche_coord[i][1]*sin(((PosRotrob) * M_PI)/180);
            if(Manche_Air_Action[i]==ON)
            {
                if(i==0) angle = -1;
                if(i==1) angle = 1;
                if(Manche_Air_Couleur == 1) //Niveau bas
                {
                    itemManche[i] = scene->addLine(int(PosYrob + Yoffset), int(PosXrob + Xoffset),
                                                   int(PosYrob + Yoffset+150*sin(((PosRotrob+(90*(angle))) * M_PI)/180)),
                                                   int(PosXrob + Xoffset+150*cos(((PosRotrob+(90*(angle))) * M_PI)/180)),redline);
                }
                else if(Manche_Air_Couleur == 2) //Niveau Moyen
                {
                    itemManche[i] = scene->addLine(int(PosYrob + Yoffset), int(PosXrob + Xoffset),
                                                   int(PosYrob + Yoffset+150*sin(((PosRotrob+(90*(angle))) * M_PI)/180)),
                                                   int(PosXrob + Xoffset+150*cos(((PosRotrob+(90*(angle))) * M_PI)/180)),greenline);
                }
                /*
                pathtext[i].addText(0,0 , font, QString::number(i));
                itemTextManche[i]=scene->addPath(pathtext[i], QPen(QBrush(Qt::black), 3), QBrush(Qt::black));
                itemTextManche[i]->setPos(Manche_coord[i][0]+24,Manche_coord[i][1]+48);
                */
            }
        }


        table_ligne=futur_i;
        for(int i = 0; i < 30; ++i){
            if(coordonnees[i][5] > 10) coordonnees[i][4] = PosRotrob - 90 ;
            afficherEchantillon(i);

        }


    }

    ui->lcdPosX->display(PosXrob);
    ui->lcdPosY->display(PosYrob);
    ui->lcdPosT->display(PosRotrob);

}

/**********************************************************************************
 *             Fonction resetComboBox() : Supprime les combobox                   *
 *********************************************************************************/
void MainWindow::resetComboBox()
{
    ui->tableView->setItemDelegateForColumn(2,nullptr);
    ui->tableView->setItemDelegateForColumn(3,nullptr);
    ui->tableView->setItemDelegateForColumn(4,nullptr);
    ui->tableView->setItemDelegateForColumn(5,nullptr);
    ui->tableView->setItemDelegateForColumn(6,nullptr);
    ui->tableView->setItemDelegateForColumn(7,nullptr);
}

/**********************************************************************************
 *    Fonction setFocusOnButton() : Sélectionne le 1er bouton de la ligne créer   *
 *********************************************************************************/
void MainWindow::setFocusOnButton()
{
    QModelIndex index = ui->tableView->currentIndex();
    int row = index.row() + 1;
    int column = 0;
    QModelIndex newIndex  = ui->tableView->model()->index(row,column);
    ui->tableView->selectionModel()->select(newIndex, QItemSelectionModel::Select);
    ui->tableView->setCurrentIndex(newIndex);
    ui->tableView->setFocus();
    ui->tableView->edit(newIndex);
}

void MainWindow::on_CreateRowButton_clicked()
{
    QModelIndex index = ui->tableView->currentIndex();  // Recupere l'index
    QString data;                                       // creer un string
    int row = index.row();                              // recupere la ligne
    int nbre_row=ui->tableView->model()->rowCount();
    if(nbre_row==row+1)
    {
        ui->tableView->model()->insertRow(nbre_row);
        data = ui->tableView->model()->data(index).toString();
        ui->tableView->model()->setData(ui->tableView->model()->index(row+1,0),ui->tableView->model()->data(ui->tableView->model()->index(row,0)).toInt()+1);
        //ui->tableView->model()->setData(ui->tableView->model()->index(row+1,1),dataCol1.at((dataCol1.indexOf(data))%6+1));
        ui->tableView->model()->setData(ui->tableView->model()->index(row+1,10),ui->tableView->model()->data(ui->tableView->model()->index(row,10)).toInt()+1);
        ui->tableView->model()->setData(ui->tableView->model()->index(row+1,11),ui->tableView->model()->data(ui->tableView->model()->index(row,11)).toInt()+1);
        setFocusOnButton();
    }
}

void MainWindow::on_InsertRowButton_clicked()
{
    int index;
    QModelIndexList l = ui->tableView->selectionModel()->selection().indexes();
    if (l.isEmpty())
    {
        index = 0;
    }
    else
    {
        index = l[0].row();
    }

    ui->tableView->model()->insertRow(index);
    setFocusOnButton();
    ui->tableView->model()->setData(ui->tableView->model()->index(index,0),ui->tableView->model()->data(ui->tableView->model()->index(index-1,0)).toInt()+1);
//    ui->tableView->model()->setData(ui->tableView->model()->index(index,1),dataCol1.at(1));
//    ui->tableView->model()->setData(ui->tableView->model()->index(index,2),0);
//    ui->tableView->model()->setData(ui->tableView->model()->index(index,6),"Non");
//    ui->tableView->model()->setData(ui->tableView->model()->index(index,7),"Attendre");
    ui->tableView->model()->setData(ui->tableView->model()->index(index,10),ui->tableView->model()->data(ui->tableView->model()->index(index-1,10)).toInt()+1);
    ui->tableView->model()->setData(ui->tableView->model()->index(index,11),ui->tableView->model()->data(ui->tableView->model()->index(index-1,11)).toInt()+1);
    for(int i = index+1; i < ui->tableView->model()->rowCount(); i++)
    {
        ui->tableView->model()->setData(ui->tableView->model()->index(i,0),ui->tableView->model()->data(ui->tableView->model()->index(i,0)).toInt()+1);
        ui->tableView->model()->setData(ui->tableView->model()->index(i,10),ui->tableView->model()->data(ui->tableView->model()->index(i,10)).toInt()+1);
        ui->tableView->model()->setData(ui->tableView->model()->index(i,11),ui->tableView->model()->data(ui->tableView->model()->index(i,11)).toInt()+1);

    }

}

void MainWindow::on_DeleteRowButton_clicked()
{
    int index;
    QModelIndexList l = ui->tableView->selectionModel()->selection().indexes();
    if (l.isEmpty()) {
        index = 0;
    } else {
        index = l[0].row();
    }
    ui->tableView->model()->removeRow(index);
    for(int i = index; i < ui->tableView->model()->rowCount(); i++)
    {
        ui->tableView->model()->setData(ui->tableView->model()->index(i,0),ui->tableView->model()->data(ui->tableView->model()->index(i,0)).toInt()-1);
        ui->tableView->model()->setData(ui->tableView->model()->index(i,10),ui->tableView->model()->data(ui->tableView->model()->index(i,10)).toInt()-1);
        ui->tableView->model()->setData(ui->tableView->model()->index(i,11),ui->tableView->model()->data(ui->tableView->model()->index(i,11)).toInt()-1);

    }
}

void MainWindow::on_ExportFileButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save as",QString(),"texte (*.txt)");
    QFile file(fileName);

    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot save file: " + file.errorString());
        return;
    }

    QTextStream textStream(&file);
    QModelIndex j;
    QModelIndex testindex;
    QString data,data2;
    int indexComboBox,indexComboBoxAction,ligne;
    double angle = 0;
    double newValue;

    for(int i = 0; i < ui->tableView->model()->rowCount(); i++)
    {
        j = ui->tableView->model()->index(i,1);
        data = ui->tableView->model()->data(j).toString();
        indexComboBox = dataCol1.indexOf(data);

        testindex = ui->tableView->model()->index(i,0);
        ligne = ui->tableView->model()->data(testindex).toInt();
        textStream << ligne << ",";

        switch(indexComboBox)
        {
        case 0: //Début match
            textStream << "P"
                       << ",";
            testindex = ui->tableView->model()->index(i,2);
            if(ui->tableView->model()->data(testindex).toString() == "bleu")
                textStream << "B" << "," ;
            else
                textStream << "J" << "," ;
            testindex = ui->tableView->model()->index(i,4);
            textStream << ui->tableView->model()->data(testindex).toString()
                       << ",";
            testindex = ui->tableView->model()->index(i,5);
            textStream << ui->tableView->model()->data(testindex).toString()
                       << ",";
            testindex = ui->tableView->model()->index(i,3);
            angle = ui->tableView->model()->data(testindex).toDouble()*10;
            textStream << angle;
            break;

        case 1: //Ligne Droite
            textStream << "L"
                       << ",";
            testindex = ui->tableView->model()->index(i,2);
            if (ui->tableView->model()->data(testindex).toInt() > 0) textStream << "F";
            else textStream << "B";
            textStream << ","
                       << abs(ui->tableView->model()->data(testindex).toInt())
                       << ","
                       << "0"
                       << ","
                       << "0";
            break;

        case 2: //Rotation
            testindex = ui->tableView->model()->index(i,2);
            angle = (ui->tableView->model()->data(testindex).toDouble()) * 10;
            textStream << "T"
                       << ",";
            testindex = ui->tableView->model()->index(i,3);
            if(ui->tableView->model()->data(testindex).toString() == "Absolu")
                textStream << "A" << "," << "0" << "," << "0" << "," << angle;
            else
                textStream << "R" << "," << "0" << "," << "0" << "," << angle;
            break;

        case 3: //Courbe
            textStream << "C"
                       << ",";
            testindex = ui->tableView->model()->index(i,4);
            if (ui->tableView->model()->data(testindex).toString() == "Gauche") textStream << "L"
                                                                                           << ",";
            else textStream << "R"
                            << ",";
            testindex = ui->tableView->model()->index(i,2);
            textStream << ui->tableView->model()->data(testindex).toString()
                       << ","
                       << "0"
                       << ",";
            testindex = ui->tableView->model()->index(i,3);
            textStream << ui->tableView->model()->data(testindex).toDouble()*10;
            break;

        case 4: //Action
            textStream << "A"
                       << ","
                       << "0"
                       << ",";
            testindex = ui->tableView->model()->index(i,2);
            data2 = ui->tableView->model()->data(testindex).toString();
            indexComboBoxAction = dataAction.indexOf(data2);
            switch(indexComboBoxAction){

            case 0 : //Deploiement
                textStream << "170";
                break;

            case 1: //Prise_bas
                textStream << "171";
                break;
            case 2: //Passe
                textStream << "172";
                break;
            case 3: //Pose_bas
                textStream << "173";
                break;
            case 4 : //Pose_Haut
                textStream << "174";
                break;
            case 5 : //Prise_bordure
                textStream << "175";
                break;
            case 6 : //Pose_bordure
                textStream << "176";
                break;
            case 7 : //Prise_distrib
                textStream << "177";
                break;
            case 8 : //Ranger
                textStream << "178";
                break;

            case 9: //Res_prestest
                textStream << "154";
                break;
            case 10: //Res_mes
                textStream << "155";
                break;
            case 11: //Res_rang
                textStream << "156";
                break;

            case 12: //Pre_prise
                textStream << "180";
                break;
            case 13: //Prise_statuette
                textStream << "181";
                break;
            case 14: //Pose_statuette
                textStream << "182";
                break;



            }
            textStream << ",";
                          testindex = ui->tableView->model()->index(i,3);
                          textStream << ui->tableView->model()->data(testindex).toString()
                       << ","
                       << "0";

            break;

        case 5: //Recalage
            textStream << "R"
                       << ",";
            testindex = ui->tableView->model()->index(i,2);
            if (ui->tableView->model()->data(testindex).toString() == "Avant" ) textStream << "F"
                                                                                           << ",";
            else textStream << "B"
                            << ",";

            testindex = ui->tableView->model()->index(i,5);
            if(ui->tableView->model()->data(testindex).toString() == "Rob-") newValue = 115;
            if(ui->tableView->model()->data(testindex).toString() == "Rob+") newValue = 1885;
            if(ui->tableView->model()->data(testindex).toString() == "Gob-") newValue = 168;
            if(ui->tableView->model()->data(testindex).toString() == "Gob+") newValue = 1832;

            testindex = ui->tableView->model()->index(i,4);
            if (ui->tableView->model()->data(testindex).toString() == "Abscisse")
            {
                textStream << newValue
                           << ","
                           << "0"
                           << ","
                           << "0"
                           << ","
                           << "Y"
                           << ",";
            }
            else { textStream << newValue
                              << ","
                              << "0"
                              << ","
                              << "0"
                              << ","
                              << "X"
                              << ",";
            }
            testindex = ui->tableView->model()->index(i,3);
            if (ui->tableView->model()->data(testindex).toString() == "Mécanique") textStream << "M"
                                                                                              << ","
                                                                                              << "0"
                                                                                              << ",";
            else textStream << "C"
                            << ","
                            << "0"
                            << ",";
            break;

        case 6: //XYT
            textStream << "X"
                       << ",";
            testindex = ui->tableView->model()->index(i,2);
            if (ui->tableView->model()->data(testindex).toString() == "Avant" ) textStream << "F"
                                                                                           << ",";
            else textStream << "B"
                            << ",";
            testindex = ui->tableView->model()->index(i,3);
            textStream << ui->tableView->model()->data(testindex).toString()
                       << ",";
            testindex = ui->tableView->model()->index(i,4);
            textStream << ui->tableView->model()->data(testindex).toString()
                       << ",";
            testindex = ui->tableView->model()->index(i,5);
            textStream << ui->tableView->model()->data(testindex).toString()
                       << "0";
            break;

        }

        if(indexComboBox != 5)
        {
            textStream << ",";
            testindex = ui->tableView->model()->index(i,6);
            if (ui->tableView->model()->data(testindex).toString() == "Précis")
            {
                textStream << "P"
                           << ",";

            }
            else textStream << "0"
                            << ",";

            testindex = ui->tableView->model()->index(i,7);
            if (ui->tableView->model()->data(testindex).toString() == "Attendre")
            {
                textStream << "W"
                           << ","
                           << "T"
                           << ",";
            }
            else if (ui->tableView->model()->data(testindex).toString() == "Saut(Position)")
            {
                textStream << "J"
                           << ","
                           << "0"
                           << ",";
            }
            else if (ui->tableView->model()->data(testindex).toString() == "Saut(Délais)")
            {
                textStream << "E"
                           << ","
                           << "P"
                           << ",";
            }
            else if (ui->tableView->model()->data(testindex).toString() == "Enchainement")
            {
                textStream << "E"
                           << ","
                           << "T"
                           << ",";
            }
            else if (ui->tableView->model()->data(testindex).toString() == "Clothoïde")
            {
                textStream << "C"
                           << ","
                           << "0"
                           << ",";
            }
        }

        textStream << "0"
                   << ","
                   << "0"
                   << ",";
        testindex = ui->tableView->model()->index(i,10);
        textStream << ui->tableView->model()->data(testindex).toString()
                   << ",";
        testindex = ui->tableView->model()->index(i,11);
        textStream << ui->tableView->model()->data(testindex).toString()
                   << ","
                   << "0"
                   << ","
                   << "0"
                   << ","
                   << "0";

        textStream << "\n";
    }
    file.close();
}

void MainWindow::on_ImportFileButton_clicked()
{
    QModelIndexList l;
    int index;
    QString fileName = QFileDialog::getOpenFileName(this, "Open the file",QString(),"texte (*.txt)");
    QFile file(fileName);
    QString text;
    QStringList liste;
    int i = 0, confirm = 0;

    if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "Warning", "Cannot open file: " + file.errorString());
        return;
    }

    QTextStream in(&file);
    do{
        l = ui->tableView->selectionModel()->selection().indexes();
        if (l.isEmpty()) {
            index = 0;
        }else if(confirm==0){
            index = l[0].row();
            i = index;
            confirm  = 1;
        }else{
            index = l[0].row();
        }
        ui->tableView->model()->insertRow(index);
        text = in.readLine();
        if(!text.isNull())
        {
            liste = text.split(",");
            //i = liste[0].toInt();
            qDebug() << liste;
//            ui->tableView->model()->setData(ui->tableView->model()->index(index,0),liste[0].toInt()+i);
//            ui->tableView->model()->setData(ui->tableView->model()->index(index,10),liste[11].toInt()+i);
//            ui->tableView->model()->setData(ui->tableView->model()->index(index,11),liste[12].toInt()+i);
            ui->tableView->model()->setData(ui->tableView->model()->index(index,0),liste[0].toInt()+i);
            ui->tableView->model()->setData(ui->tableView->model()->index(index,10),liste[11].toInt()+i);
            ui->tableView->model()->setData(ui->tableView->model()->index(index,11),liste[12].toInt()+i);
            if(liste[1] == "P") //Debut match
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(index,1),dataCol1[0]);
                if(liste[2] == "B")
                    ui->tableView->model()->setData(ui->tableView->model()->index(index,2),"bleu");
                else
                    ui->tableView->model()->setData(ui->tableView->model()->index(index,2),"Jaune");
                ui->tableView->model()->setData(ui->tableView->model()->index(index,3),liste[5].toDouble()/10);
                ui->tableView->model()->setData(ui->tableView->model()->index(index,4),liste[3]);
                ui->tableView->model()->setData(ui->tableView->model()->index(index,5),liste[4]);
            }
            else if(liste[1] == "L") //Ligne Droite
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(index,1),dataCol1[1]);
                if(liste[2] =="F")
                    ui->tableView->model()->setData(ui->tableView->model()->index(index,2),liste[3]);
                else
                    ui->tableView->model()->setData(ui->tableView->model()->index(index,2),(-(liste[3].toInt())));
            }
            else if(liste[1] == "T") //Rotation
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(index,1),dataCol1[2]);
                ui->tableView->model()->setData(ui->tableView->model()->index(index,2),liste[5].toDouble() / 10);
                if(liste[2] == "A") ui->tableView->model()->setData(ui->tableView->model()->index(index,3),"Absolu");
                else ui->tableView->model()->setData(ui->tableView->model()->index(index,3),"Relatif");
            }
            else if(liste[1] == "C") //Courbe
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(index,1),dataCol1[3]);
                if(liste[2] == "R") ui->tableView->model()->setData(ui->tableView->model()->index(index,4),"Droite");
                else ui->tableView->model()->setData(ui->tableView->model()->index(index,4),"Gauche");
                ui->tableView->model()->setData(ui->tableView->model()->index(index,2),liste[3]);
                ui->tableView->model()->setData(ui->tableView->model()->index(index,3),liste[5].toDouble() / 10);
            }
            else if(liste[1] == "A") //Action
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(index,1),dataCol1[4]);
                ui->tableView->model()->setData(ui->tableView->model()->index(index,2),dataAction[getAction(liste[3].toInt())]);
                ui->tableView->model()->setData(ui->tableView->model()->index(index,3),liste[4]);
            }
            else if(liste[1] == "R") //Recalage
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(index,1),dataCol1[5]);
                if(liste[2] == "F") ui->tableView->model()->setData(ui->tableView->model()->index(index,2),"Avant");
                else ui->tableView->model()->setData(ui->tableView->model()->index(index,2),"Arrière");
                if(liste[6] == "Y") ui->tableView->model()->setData(ui->tableView->model()->index(index,4),"Abscisse");
                else ui->tableView->model()->setData(ui->tableView->model()->index(index,4),"Ordonnée");
                if(liste[7] == "M") ui->tableView->model()->setData(ui->tableView->model()->index(index,3),"Mécanique");
                else ui->tableView->model()->setData(ui->tableView->model()->index(index,3),"Arrière");
                if(liste[3] == "115") ui->tableView->model()->setData(ui->tableView->model()->index(index,5),"Rob-");
                else if(liste[3] == "1885") ui->tableView->model()->setData(ui->tableView->model()->index(index,5),"Rob+");
                else if(liste[3] == "168") ui->tableView->model()->setData(ui->tableView->model()->index(index,5),"Gob-");
                else if(liste[3] == "1832") ui->tableView->model()->setData(ui->tableView->model()->index(index,5),"Gob+");
            }
            else if(liste[1] == "X") //XYT
            {
                ui->tableView->model()->setData(ui->tableView->model()->index(index,1),dataCol1[6]);
                if(liste[2] == "F") ui->tableView->model()->setData(ui->tableView->model()->index(index,2),"Avant");
                else ui->tableView->model()->setData(ui->tableView->model()->index(index,2),"Arrière");
                ui->tableView->model()->setData(ui->tableView->model()->index(index,3),liste[3]);
                ui->tableView->model()->setData(ui->tableView->model()->index(index,4),liste[4]);
                ui->tableView->model()->setData(ui->tableView->model()->index(index,5),liste[5].toDouble() / 10);
            }

            if(liste[6] == "P")
                ui->tableView->model()->setData(ui->tableView->model()->index(index,6),"Précis");
            else
                ui->tableView->model()->setData(ui->tableView->model()->index(index,6),"Non");

            if(liste[7] == "W" && liste[8] == "T") ui->tableView->model()->setData(ui->tableView->model()->index(index,7),"Attendre");
            else if (liste[7] == "J" && liste[8] == "0") ui->tableView->model()->setData(ui->tableView->model()->index(index,7),"Saut(Position)");
            else if (liste[7] == "E" && liste[8] == "P") ui->tableView->model()->setData(ui->tableView->model()->index(index,7),"Saut(Délais)");
            else if (liste[7] == "E" && liste[8] == "T") ui->tableView->model()->setData(ui->tableView->model()->index(index,7),"Enchainement");
            else if (liste[7] == "M" && liste[8] == "0") ui->tableView->model()->setData(ui->tableView->model()->index(index,7),"Enchainement");
            else if (liste[7] == "C" && liste[8] == "0") ui->tableView->model()->setData(ui->tableView->model()->index(index,7),"Clothoïde");
        }

    }
    while(!text.isNull());
    //Suprimmer la derniere ligne
    ui->tableView->model()->removeRow(index);
   if(dataCol1.indexOf(ui->tableView->model()->data(ui->tableView->model()->index(index,1)).toString())==0)
        ui->tableView->model()->removeRow(index);
//
    // recalculer les sauts des index d'aprés
    file.close();

    //actualisation des indices après l'import
    QModelIndex testindex;
    int pos, delai;
    int indexdebut = (liste[0].toInt()+i)+1;
    int y = (liste[11].toInt()+i)+1;

    for(int ligne = index; ligne < ui->tableView->model()->rowCount(); ligne++)
    {
        testindex = ui->tableView->model()->index(ligne,10);
        pos = ui->tableView->model()->data(testindex).toInt();
        testindex = ui->tableView->model()->index(ligne,11);
        delai = (ui->tableView->model()->data(testindex).toInt())-pos;
        ui->tableView->model()->setData(ui->tableView->model()->index(ligne,0),indexdebut);
        ui->tableView->model()->setData(ui->tableView->model()->index(ligne,10),y);
        ui->tableView->model()->setData(ui->tableView->model()->index(ligne,11),y+delai);
        y++;
        indexdebut++;
    }
}




QPixmap MainWindow::determinerCouleur(int i){
    QPixmap pixReturn;

    //on vérifie d'abord si l'échantillon doit être face caché
    if (coordonnees[i][3] == 0){
        switch(coordonnees[i][2]){
        case GREEN :
            pixReturn.load(":/Images/AgeOfBots/videV.png");
            break;
        case RED :
            pixReturn.load(":/Images/AgeOfBots/videR.png");
            break;
        case BLUE  :
            pixReturn.load(":/Images/AgeOfBots/videB.png");
            break;
        }
    }

    //puis on vérifie si il est debout
    else if (coordonnees[i][3] == 2){
        switch(coordonnees[i][2]){
        case GREEN :
            pixReturn.load(":/Images/AgeOfBots/deboutV.png");
            break;
        case RED :
            pixReturn.load(":/Images/AgeOfBots/deboutR.png");
            break;
        case BLUE  :
            pixReturn.load(":/Images/AgeOfBots/deboutB.png");
            break;
        }
    }

    //et enfin , si il est retourné
    else{
        switch(coordonnees[i][2]){
        case GREEN :
            pixReturn.load(":/Images/AgeOfBots/vert.png");
            break;
        case RED :
            pixReturn.load(":/Images/AgeOfBots/rouge.png");
            break;
        case BLUE  :
            pixReturn.load(":/Images/AgeOfBots/bleu.png");
            break;
        }
    }

    return pixReturn;
}

void MainWindow::afficherEchantillon(int i){
    //on supprime l'item et on détermine sa nouvelle apparence
    scene->removeItem(ptrEchantillon[i]);
    QPixmap pix(determinerCouleur(i));

    //on dessine son numéro dans la table de coordonnées , très utile pour le débug



    //si l'echantillon est pris par un bras , on met ses coordonnées égales à celle de la ventouse correspondante
    if (coordonnees[i][5] != 0){
        QPainter paint(&pix);
        QFont font;
        QPen pen;
        pen.setWidth(5);
        pen.setColor(Qt::black);
        paint.setPen(pen);
        font.setPixelSize(50);
        paint.setFont(font);

        QString str = QString::number(coordonnees[i][5] - 1);
        paint.drawText(pix.rect().center().x() - 20,pix.rect().center().y() + 15,str);



        if(coordonnees[i][5] > 10){
            coordonnees[i][0] = bras[coordonnees[i][5] - 10].x() - 50*cos(((coordonnees[i][4]) * M_PI)/180);
            coordonnees[i][1] = bras[coordonnees[i][5] - 10].y() + 50*sin(((coordonnees[i][4]) * M_PI)/180);
            pen.setColor(Qt::cyan);
            paint.setPen(pen);
            paint.drawEllipse(pix.rect().center() , 54,54);
        }
        else{
            coordonnees[i][0] = bras[coordonnees[i][5]].x();
            coordonnees[i][1] = bras[coordonnees[i][5]].y();
            pen.setColor(Qt::green);
            paint.setPen(pen);
            paint.drawEllipse(pix.rect().center() , 54,54);
        }

    }

    //on ajoute l'item aux bonnes coordonnées
    ptrEchantillon[i] = scene->addPixmap(pix);
    ptrEchantillon[i]->setPos(coordonnees[i][0],coordonnees[i][1]);

    //on effectue les différentes transformations nécéssaires

    if (coordonnees[i][5] == 0){
    ptrEchantillon[i]->setOffset(-ptrEchantillon[i]->boundingRect().center().x() + GLOBALOFFSETX,
                                 -ptrEchantillon[i]->boundingRect().center().y() + GLOBALOFFSETY);
    }
    else ptrEchantillon[i]->setOffset(-ptrEchantillon[i]->boundingRect().center().x() +35,-ptrEchantillon[i]->boundingRect().center().y() + 30);
    //quand l'échantillon est pris par un bras du bas , pas besoin du global offset puisque sa position est la même que les ventouse qui ont le global offset
    //il faut toujours l'offset qui permet de les centrer cependant

    ptrEchantillon[i]->setTransformOriginPoint(ptrEchantillon[i]->boundingRect().center());//cela met le point de rotation au centre au lieu d'en haut à droite
    ptrEchantillon[i]->setRotation(coordonnees[i][4]);
}


int MainWindow::collisionVentouse(int i,int rotRob){
    QLine ligneVentouse(0,0,10,0);
    int toReturn = -1; //la fonction retournera -1 si aucune collision n'est détecté, autrement , elle renvoie le numéro de l'échantillon attrapé.
    int position[2] = {0,0};

    //on setup le pen qui va dessiner les lignes
    QPen pen;
    pen.setColor(Qt::green);
    pen.setWidth(5);

    //on ajoute les lignes à la scène et on et leurs associe le pen
    collisionLine[0] = scene->addLine(ligneVentouse);
    collisionLine[0]->setPen(pen);
    collisionLine[1] = scene->addLine(ligneVentouse);
    collisionLine[1]->setPen(pen);
    collisionLine[2] = scene->addLine(ligneVentouse);
    collisionLine[2]->setPen(pen);
    collisionLine[3] = scene->addLine(ligneVentouse);
    collisionLine[3]->setPen(pen);

    //on détermine la position de la ventouse choisie par le paramètre i

    switch (i){
        case 0 : position[0] = (206.06)*sin(((rotRob) * M_PI)/180 - 28.6*M_PI/180) ;
                 position[1] =  (206.06)*cos(((rotRob) * M_PI)/180 - 28.6*M_PI/180);
                break;
        case 1 : position[0] = (107.5)*sin(((rotRob) * M_PI)/180) ;
                 position[1] =  (107.5)*cos(((rotRob) * M_PI)/180);
                break;
        case 2 : position[0] = (206.06)*sin(((rotRob) * M_PI)/180 + 28.6*M_PI/180) ;
                 position[1] =  (206.06)*cos(((rotRob) * M_PI)/180 + 28.6*M_PI/180);
                break;
        case 5 : position[0] = (206.06)*sin(((rotRob) * M_PI)/180 + 28.6*M_PI/180 + M_PI) ;
                 position[1] =  (206.06)*cos(((rotRob) * M_PI)/180 + 28.6*M_PI/180 + M_PI);
                break;
        case 4 : position[0] = (107.5)*sin(((rotRob) * M_PI)/180 + M_PI) ;
                 position[1] =  (107.5)*cos(((rotRob) * M_PI)/180 + M_PI);
                break;
        case 3 : position[0] = (206.06)*sin(((rotRob) * M_PI)/180 + 28.6*M_PI/180 - M_PI) ;
                 position[1] =  (206.06)*cos(((rotRob) * M_PI)/180 - 28.6*M_PI/180 + M_PI);
                break;
    }

    collisionLine[0]->setPos(ROBOTCENTRE);
    collisionLine[0]->moveBy(position[0],position[1]);
    collisionLine[0]->moveBy(27-5,0); // on soustrait la position par 5 pixels pour centrer la ligne qui est de 10 pixels
    collisionLine[1]->setPos(ROBOTCENTRE);
    collisionLine[1]->moveBy(position[0],position[1]);
    collisionLine[1]->moveBy(27-5,54);
    collisionLine[2]->setPos(ROBOTCENTRE);
    collisionLine[2]->moveBy(position[0],position[1]);
    collisionLine[2]->moveBy(0-5,27);
    collisionLine[3]->setPos(ROBOTCENTRE);
    collisionLine[3]->moveBy(position[0],position[1]);
    collisionLine[3]->moveBy(54-5,27);

    for(int j =0;j<30;j++){
        if(collisionLine[0]->collidesWithItem(ptrEchantillon[j]) //ça fait peur , mais ça veut juste dire si les quatre lignes vertes touchent l'échantillon
           && collisionLine[1]->collidesWithItem(ptrEchantillon[j])
           && collisionLine[2]->collidesWithItem(ptrEchantillon[j])
           && collisionLine[3]->collidesWithItem(ptrEchantillon[j])){
            toReturn  = j;
        }



    }
    //on cache les lignes de collision pour éviter les bug graphique (et parceque c'est moche) n'hesitez pas a commenter cette boucle pour mieux comprendre le système
    for(int i=0;i<4;i++)
        collisionLine[i]->hide();
    return toReturn;
}

void MainWindow::resetPosEchantillon(void){

    for(int i = 0; i<30 ; i++){

            for(int j = 0; j< 6 ; j++){
                coordonnees[i][j] = coordonneesBase[i][j];
            }

    }
}

int MainWindow::getAction(int chiffre){
    int toReturn = 0;
    switch(chiffre){

    case 170 : //Deploiement
        toReturn = 0 ;
        break;

    case 171: //Prise_bas
        toReturn = 1  ;
        break;
    case 172: //Passe
        toReturn = 2  ;
        break;
    case 173: //Pose_bas
        toReturn = 3  ;
        break;
    case 174 : //Pose_Haut
        toReturn = 4  ;
        break;
    case 175 : //Prise_bordure
        toReturn = 5 ;
        break;
    case 176 : //Pose_bordure
        toReturn = 6 ;
        break;
    case 177 : //Prise_distrib
        toReturn = 7 ;
        break;
    case 178: //Ranger
        toReturn = 8 ;
        break;

    case 154: //Res_prestest
        toReturn = 9 ;
        break;
    case 155: //Res_mes
        toReturn = 10 ;
        break;
    case 156: //Res_rang
        toReturn = 11 ;
        break;

    case 180: //Pre_prise
        toReturn = 12 ;
        break;
    case 181: //Prise_statuette
        toReturn = 13 ;
        break;
    case 182: //Pose_statuette
        toReturn = 14 ;
        break;


    }
    return toReturn;
}

void MainWindow::on_pushButton_clicked()
{


        QPixmap robot(":/Images/AgeOfBots/ROB2020.png");

        switch(robot2Flag){
        case 0 :
            robot2Flag++;
            break;

        case 1:

            robot2 =  scene->addPixmap(robot);

            robot2->setOffset(GLOBALOFFSETX - robot2->boundingRect().center().x(),GLOBALOFFSETY - robot2->boundingRect().center().y());
            robot2->setTransformOriginPoint(robot2->boundingRect().center());

            robot2->setPos(ui->secondX->value(),ui->secondY->value());
            robot2->setRotation(ui->secondTheta->value());

            robot2Flag++;

            break;

        default://case 2:

            scene->removeItem(robot2);
            robot2Flag = 1;
            break;

        }
}

