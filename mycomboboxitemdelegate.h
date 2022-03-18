#ifndef MYCOMBOBOXITEMDELEGATE_H
#define MYCOMBOBOXITEMDELEGATE_H

#include <QStyledItemDelegate>
#include <QString>
#include <QComboBox>
#include <QtWidgets>
#include <QDebug>
#include "mainwindow.h"

class MyComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MyComboBoxDelegate(QObject *parent = nullptr);
    ~MyComboBoxDelegate() override;

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
};

#endif // MYCOMBOBOXITEMDELEGATE_H
