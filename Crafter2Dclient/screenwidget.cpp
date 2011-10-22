#include "screenwidget.hpp"
#include "scene.hpp"

#include <QPainter>
#include <QMessageBox>

ScreenWidget::ScreenWidget(Scene* scene, QWidget *parent) :
    QGraphicsView(scene, parent)
{
    /*setAutoFillBackground(true);
    setPalette(QPalette(Qt::white, Qt::black));*/
    scale(10,10);
}


