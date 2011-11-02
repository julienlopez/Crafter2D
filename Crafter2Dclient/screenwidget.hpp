#ifndef SCREENWIDGET_HPP
#define SCREENWIDGET_HPP

#include <QGraphicsView>

class Scene;
class Position;

class ScreenWidget : public QGraphicsView
{
    Q_OBJECT
public:
    ScreenWidget(Scene* scene, QWidget *parent = 0);

protected:
    void wheelEvent(QWheelEvent* event);

private:
    double zoomLevel;
    Scene* m_scene;

private slots:
    void onNewPosition(const Position& p);
};

#endif // SCREENWIDGET_HPP
