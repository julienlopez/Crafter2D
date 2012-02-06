#include "screenwidget.hpp"
#include "../scene.hpp"
#include "../terrainmanager.hpp"

#include <Position>

#include <QPainter>
#include <QMessageBox>
#include <QWheelEvent>

#include <cmath>

#include <QDebug>

UI::ScreenWidget* UI::ScreenWidget::s_instance = 0;

UI::ScreenWidget::ScreenWidget(Scene* scene, QWidget *parent) :
    QGraphicsView(scene, parent), zoomLevel(10), m_scene(scene)
{
    connect(scene, SIGNAL(newPosition(Position)), this, SLOT(onNewPosition(Position)));
    scale(zoomLevel, zoomLevel);
    setDragMode(NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //creation des pens
    m_sandPen = QPen(QBrush(QColor(255,255,100), Qt::SolidPattern/*Qt::RadialGradientPattern*/), dx);
    m_grassPen = QPen(QBrush(QColor(100,255,100), Qt::SolidPattern), dx/2-2);
    m_waterPen = QPen(QBrush(QColor(100,100,255), Qt::SolidPattern), dx/2-2);

    Q_ASSERT(!s_instance);
    s_instance = this;
}

UI::ScreenWidget* UI::ScreenWidget::instance()
{
    return s_instance;
}

void UI::ScreenWidget::wheelEvent(QWheelEvent* event)
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

void UI::ScreenWidget::drawBackground(QPainter* painter, const QRectF &rect)
{
    painter->save();
    int right = round(rect.right()) + dx;
    int bottom = round(rect.bottom()) + dx;
    for(int x = round(rect.left())-dx; x<=right; x += dx)
        for(int y = round(rect.top())-dx; y<=bottom; y += dx)
        {
            TerrainManager::Terrain t = TerrainManager::get(x,y);
            switch(t)
            {
                case TerrainManager::sand:
                    painter->setPen(m_sandPen);
                    break;
                case TerrainManager::grass:
                    painter->setPen(m_grassPen);
                    break;
                case TerrainManager::water:
                    painter->setPen(m_waterPen);
                    break;
            }
            //painter->drawPoint(x,y);
        }
    painter->restore();
}

void UI::ScreenWidget::onNewPosition(const Position& p)
{
    if(!p.isValid()) return;
    centerOn(m_scene->player().position());
}
