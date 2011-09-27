#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QDataStream>

class Message : public QObject
{
    Q_OBJECT
public:
    Message(quint64 id =0, QObject *parent = 0);
    Message(const Message& m);

    quint64 id() const;

    friend QDataStream& operator << (QDataStream& out, const Message& m);
    friend QDataStream& operator >> (QDataStream& in, Message& m);

protected:
    quint64 m_id;

signals:

public slots:

};

#endif // MESSAGE_H
