#ifndef POSITION_HPP
#define POSITION_HPP

#include <QPointF>
#include <QString>
#include <QDataStream>

class Position
{
public:
    Position();
    Position(const QPointF& position);
    Position(QString str);

    bool isValid() const;
    QPointF position() const;

    QString toString() const;

    friend QDataStream& operator >>(QDataStream& in, Position& pos);
    friend QDataStream& operator <<(QDataStream& out, const Position& pos);

private:
    bool m_valid;
    QPointF m_position;
};

#endif // POSITION_HPP
