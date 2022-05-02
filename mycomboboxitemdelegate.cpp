#include "mycomboboxitemdelegate.h"


MyComboBoxDelegate::MyComboBoxDelegate(QObject *parent)
    : QStyledItemDelegate(parent){

}

MyComboBoxDelegate::~MyComboBoxDelegate()
{
}


QWidget *MyComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    QComboBox *cb = new QComboBox(parent);

    if(index.column() == 1)
    {
        cb->addItems(dynamic_cast<MainWindow *>(parent)->dataCol1);

        connect(cb, SIGNAL(currentIndexChanged(int)), parent->parent()->parent()->parent(), SLOT(setHeaderComboBox(int)));

        cb->setCurrentText(model->data(index).toString());
        return cb;
    }

    if(index.column() == 2 or index.column() == 3 or index.column() == 4 or index.column() == 5
    or index.column() == 6 or index.column() == 7 or index.column() == 10 or index.column() == 11 )
    {
        return cb;
    }
}

void MyComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cb = qobject_cast<QComboBox *>(editor);
    Q_ASSERT(cb);
    model->setData(index, cb->currentText(), Qt::EditRole);
}

void MyComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    const QAbstractItemModel *model = index.model();
    QComboBox *cb = static_cast<QComboBox*>(editor);

    if(index.column() == 2)
    {
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Debut Match"))
        {
            cb->addItem(QString("Jaune"));
            cb->addItem(QString("Bleu"));
            cb->setCurrentText(model->data(index).toString());
        }

        else if((model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Recalage"))||(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("XYT")))
        {
            cb->addItem(QString("Arrière"));
            cb->addItem(QString("Avant"));
            cb->setCurrentText(model->data(index).toString());
        }

        else if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Action"))
        {
            //chasse neige
            cb->addItem(QString("DEPLOIEMENT"));

            //action liées aux bras
            cb->addItem(QString("PRISE_BAS"));
            cb->addItem(QString("PASSE"));
            cb->addItem(QString("RELACHER_BAS"));
            cb->addItem(QString("POSE_HAUT"));
            cb->addItem(QString("PRISE_BORDURE"));
            cb->addItem(QString("POSE_BORDURE"));
            cb->addItem(QString("PRISE_DISTRIB"));

            //actions liées aux bras de mesures
            cb->addItem(QString("RES_PRETEST"));
            cb->addItem(QString("RES_MES"));
            cb->addItem(QString("RES_RANG"));

            cb->setCurrentText(model->data(index).toString());
        }
//        else if(model->data(model->index(index.row(), 0),Qt::DisplayRole).toString().contains("Ligne Droite"))
//            sb->setValue(500);
    }
    if(index.column() == 3)
    {
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Rotation"))
        {
            cb->addItem(QString("Relatif"));
            cb->addItem(QString("Absolu"));
            cb->setCurrentText(model->data(index).toString());
        }


        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Recalage"))
        {
            cb->addItem(QString("Mécanique"));
            cb->addItem(QString("Capteur"));
            cb->setCurrentText(model->data(index).toString());
        }

    }

    if(index.column() == 4)
    {
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Recalage"))
        {
            cb->addItem(QString("Abscisse"));
            cb->addItem(QString("Ordonnée"));
            cb->setCurrentText(model->data(index).toString());
        }
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Courbe"))
        {
            cb->addItem(QString("Droite"));
            cb->addItem(QString("Gauche"));
            cb->setCurrentText(model->data(index).toString());
        }
    }

    if(index.column() == 5)
    {
        if(model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Recalage"))
        {
            cb->addItem(QString("Rob-")); //115
            cb->addItem(QString("Rob+")); //1885
            cb->addItem(QString("Gob-")); //163
            cb->addItem(QString("Gob+")); //1837
            cb->setCurrentText(model->data(index).toString());
        }
    }

    if(index.column() == 6)
    {
        if(!model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Debut Match"))
        {
            cb->addItem(QString("Précis"));
            cb->addItem(QString("Non"));
            cb->setCurrentText(model->data(index).toString());
        }
    }

    if(index.column() == 7)
    {
        if(!model->data(model->index(index.row(), 1),Qt::DisplayRole).toString().contains("Debut Match"))
        {
            cb->addItem(QString("Attendre"));
            cb->addItem(QString("Saut(Position)"));
            cb->addItem(QString("Saut(Délais)"));
            cb->addItem(QString("Enchainement"));
            cb->addItem(QString("Clothoïde"));
            cb->setCurrentText(model->data(index).toString());
        }
    }

    if(index.column() == 10 or index.column() == 11)
    {
        for(int i = 0; i <= model->rowCount(); i++)
        {
            cb->addItem(QString::number(i+1));
        }
        cb->setCurrentText(model->data(index).toString());
    }

}
