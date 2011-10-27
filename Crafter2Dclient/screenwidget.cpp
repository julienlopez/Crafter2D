#include "screenwidget.hpp"
#include "scene.hpp"

#include <Position>

#include <QPainter>
#include <QMessageBox>

#include <QDebug>

ScreenWidget::ScreenWidget(Scene* scene, QWidget *parent) :
    QGraphicsView(scene, parent), m_scene(scene)
{
    connect(scene, SIGNAL(newPosition(Position)), this, SLOT(onNewPosition(Position)));
    /*setAutoFillBackground(true);
    setPalette(QPalette(Qt::white, Qt::black));*/
    scale(10,10);
}

void ScreenWidget::onNewPosition(const Position& p)
{
    //qDebug() << "ScreenWidget::onNewPosition(" << p.position() << ")";
    if(!p.isValid()) return;
    centerOn(m_scene->player().position());
}


