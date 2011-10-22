#ifndef SCREENWIDGET_HPP
#define SCREENWIDGET_HPP

#include <QGraphicsView>

class Scene;

class ScreenWidget : public QGraphicsView
{
    Q_OBJECT
public:
    ScreenWidget(Scene* scene, QWidget *parent = 0);
};

#endif // SCREENWIDGET_HPP
