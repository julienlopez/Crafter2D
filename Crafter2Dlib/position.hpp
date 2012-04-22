#ifndef POSITION_HPP
#define POSITION_HPP

#include <QPointF>
#include <QString>
#include <QDataStream>

class Position
{
public:
    Position();
    Position(const QPointF& position, double angle);
    Position(QString str);

    bool isValid() const;
    QPointF position() const;
    QPointF& position();

    double angle() const;
    double& angle();

    QString toString() const;

    friend QDataStream& operator >>(QDataStream& in, Position& pos);
    friend QDataStream& operator <<(QDataStream& out, const Position& pos);

    bool operator == (const Position& pos) const;
    bool operator != (const Position& pos) const;

    double distance(const Position& pos) const;
    double distance2(const Position& pos) const;

private:
    bool m_valid;
    double m_angle;
    QPointF m_position;
};

#endif // POSITION_HPP
