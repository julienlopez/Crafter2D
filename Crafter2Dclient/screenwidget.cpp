#include "screenwidget.hpp"
#include "scene.hpp"

#include <Position>

#include <QPainter>
#include <QMessageBox>
#include <QWheelEvent>

ScreenWidget::ScreenWidget(Scene* scene, QWidget *parent) :
    QGraphicsView(scene, parent), zoomLevel(10), m_scene(scene)
{
    connect(scene, SIGNAL(newPosition(Position)), this, SLOT(onNewPosition(Position)));
    scale(zoomLevel, zoomLevel);
    setDragMode(NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void ScreenWidget::wheelEvent(QWheelEvent* event)
{
    /*
    qDebug() << "zoom de " << -(double)event->delta()/5000;
    zoomLevel -= (double)event->delta()/5000;
    if(zoomLevel > 50) zoomLevel = 50;
    qDebug() << "zoomLevel = " << zoomLevel;
    scale(zoomLevel, zoomLevel);
*/
    event->accept();
}

void ScreenWidget::onNewPosition(const Position& p)
{
    if(!p.isValid()) return;
    centerOn(m_scene->player().position());
}
