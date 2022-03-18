#include "echantillon.h"



Echantillon::Echantillon()
{
    x=0;
    y=0;
    angle=0;
    couleur=1;
    face=true;

}

Echantillon::Echantillon(int Xpos , int Ypos , int Angle, int Couleur,bool Face){
    x=Xpos;
    y=Ypos;
    angle=Angle;
    couleur=Couleur;
    face=Face;



}

void Echantillon::afficher(QGraphicsScene *scene){


    if(!face){
        this->load(":/Images/AgeOfBots/vide.png");
        QGraphicsPixmapItem *vide = scene->addPixmap(*this);
        vide->setOffset(-80,-120);
        vide->setPos(x,y);
        vide->setRotation(angle);
        }
    else{
        switch(couleur){
            case 1 :{
                this->load(":/Images/AgeOfBots/vert.png");
                QGraphicsPixmapItem *vert = scene->addPixmap(*this);
                vert->setOffset(-80,-120);
                vert->setPos(x,y);
                vert->setRotation(angle);
                break;
        }

        case 2:{
                this->load(":/Images/AgeOfBots/rouge.png");
                QGraphicsPixmapItem *rouge = scene->addPixmap(*this);
                rouge->setOffset(-80,-120);
                rouge->setPos(x,y);
                rouge->setRotation(angle);
                break;
        }

        case 3 :{
                this->load(":/Images/AgeOfBots/bleu.png");
                QGraphicsPixmapItem *bleu = scene->addPixmap(*this);
                bleu->setOffset(-80,-120);
                bleu->setPos(x,y);
                bleu->setRotation(angle);
                break;
        }

        }
    }


}



