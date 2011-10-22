#ifndef SCENE_HPP
#define SCENE_HPP

#include <Message/Message>
#include <Position>

#include <QGraphicsScene>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);

private:
    Position position;
    QGraphicsItem* player;

    void setPosition(const Position& p);

signals:
    void message(const Message::Message&);
    void newPosition(const Position&);

public slots:
    void handleMessage(Message::Message* message);

};

#endif // SCENE_HPP
