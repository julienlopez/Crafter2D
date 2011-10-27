#ifndef SCENE_HPP
#define SCENE_HPP

#include <Message/Message>
#include <Position>

#include <QGraphicsScene>

class QTimer;

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);

    Position player() const;

    static const double dt = 0.01;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    Position position;
    QList<QPointF> togo;
    QGraphicsItem* m_player;
    QGraphicsItem* m_root;
    QTimer* timer;

    void setPosition(const Position& p);

signals:
    void message(const Message::Message&);
    void newPosition(const Position&);

public slots:
    void handleMessage(Message::Message* message);

private slots:
    void maj();

};

#endif // SCENE_HPP
