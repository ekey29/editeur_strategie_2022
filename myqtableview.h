#ifndef MYQTABLEVIEW_H
#define MYQTABLEVIEW_H

#include <QTableView>
#include <QScrollBar>
#include <QHeaderView>
#include <QResizeEvent>

class MyQTableView : public QTableView {

    Q_OBJECT

public:
    MyQTableView(QWidget *parent = nullptr) : QTableView(parent) {}
protected:
    virtual void resizeEvent(QResizeEvent * event) {
        // calcul de la mise à l'échelle de la table (largeur zone affichage / largeur mini)
        double ratio = event->size().width() / 505.0;
        // si le ratio est < 1.0, on garde les dimansions => scrollbar horizontale
        if (ratio < 1.0) ratio = 1.0;

        // calcul de la largeur de chaque colonne et l'espace total occupé
        int w;
        int total = 0;
        w = 15*ratio;
        total += w;
        setColumnWidth(0,w);
        w = 70*ratio;
        total += w;
        setColumnWidth(1,w);
        total += w;
        setColumnWidth(3,w);
        total += w;
        setColumnWidth(4,w);
        total += w;
        setColumnWidth(5,w);
        w = 45*ratio;
        total += w;
        setColumnWidth(6,w);
        total += w;
        setColumnWidth(7,w);
        w = 10*ratio;
        total += w;
        setColumnWidth(8,w);
        total += w;
        setColumnWidth(9,w);
        w = 15*ratio;
        total += w;
        setColumnWidth(10,w);
        total += w;
        setColumnWidth(11,w);

        // la colonne 2 occupe l'espace restant (à cause des arrondis)
        w = event->size().width()-total;
        if (w<70) w = 70;
        setColumnWidth(2,w);
        // la ligne ci-dessous fait la même chose mais l'utilisateur ne peut plus faire son réglage de largeur des colonnes
//        horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    }
};

#endif // MYQTABLEVIEW_H
