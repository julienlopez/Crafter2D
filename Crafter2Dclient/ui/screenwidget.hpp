#ifndef SCREENWIDGET_HPP
#define SCREENWIDGET_HPP

#include <QGraphicsView>
#include <QPen>

class Scene;
class Position;

namespace UI {

class ScreenWidget : public QGraphicsView
{
    Q_OBJECT
public:
    ScreenWidget(Scene* scene, QWidget *parent = 0);

    static ScreenWidget* instance();

protected:
    void wheelEvent(QWheelEvent* event);
    void drawBackground(QPainter* painter, const QRectF& rect);

private:
    static ScreenWidget* s_instance;

    double zoomLevel;
    Scene* m_scene;

    QPen m_sandPen;
    QPen m_grassPen;
    QPen m_waterPen;

    static const int dx = 10;

private slots:
    void onNewPosition(const Position& p);
};

}

#endif // SCREENWIDGET_HPP
