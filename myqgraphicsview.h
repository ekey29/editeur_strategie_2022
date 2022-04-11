#ifndef MYQGRAPHICSVIEW_H
#define MYQGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QScrollBar>
#include <QResizeEvent>

class MyQGraphicsView : public QGraphicsView {

    Q_OBJECT

public:
    MyQGraphicsView(QWidget *parent = nullptr) : QGraphicsView(parent) {}
protected:
    virtual void resizeEvent(QResizeEvent *) {
        fitInView(scene()->sceneRect(),Qt::KeepAspectRatio);
    }
};

#endif // MYQGRAPHICSVIEW_H
