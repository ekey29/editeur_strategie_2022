#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractTableModel>
#include <QAbstractItemModel>
#include <QString>
#include <QDebug>
#include <QStandardItem>


const int COLS= 12;

class MyModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;     //Retourne la taille
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;  //du tableau.
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override ;    //Accède aux données du tableau dont les données de la case sélectionnée.
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;    //Autorise les modifications
    Qt::ItemFlags flags(const QModelIndex &index) const override;                                       //du tableau.
    virtual bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;    //Insère une ligne.
    virtual bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;    //Supprime une ligne.
    virtual bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role = Qt::EditRole) override;  //Modifie l’en-tête
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;               //du tableau.
private:
    QVector<QVector<QString>> m_gridData;   //tableau dynamique à deux dimensions.
    QString header[COLS];                   //Tableau permettant de contenir des chaines de caractères.
signals:
    void editCompleted(const QString &);    //Lorsque que case modifiée, parcours le tableau et récupère les nouvelles données de chaque case pour modifier le modèle.
};

#endif // MYMODEL_H
