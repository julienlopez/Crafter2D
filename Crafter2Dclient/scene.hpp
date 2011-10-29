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
    Position old_pos;
    QList<QPointF> togo;
    QGraphicsItem* m_player;
    QGraphicsItem* m_root;
    QTimer* timer;
    QTimer* timer_sendPos;

    void setPosition(const Position& p);

signals:
    void message(const Message::Message&);
    void newPosition(const Position&);

public slots:
    void handleMessage(Message::Message* message);

private slots:
    void maj();
    void sendPosition();

};

#endif // SCENE_HPP
