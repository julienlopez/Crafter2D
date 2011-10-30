#include "position.hpp"

#include <QStringList>

Position::Position(): m_valid(false), m_angle(0)
{}

Position::Position(const QPointF& position, double angle): m_valid(true), m_angle(angle), m_position(position)
{}

Position::Position(QString str): m_valid(false)
{
    m_valid = false;
    if(!str.startsWith('{') || !str.endsWith('}')) return;
    str.chop(1);
    str.remove(0,1);
    QStringList lst = str.split(',');
    if(lst.size() != 3) return;
    bool ok = false;
    m_position.setX(lst.at(0).toDouble(&ok));
    if(!ok) return;
    m_position.setY(lst.at(1).toDouble(&ok));
    if(!ok) return;
    m_angle = lst.at(2).toDouble(&ok);
    if(!ok) return;
    m_valid = true;
}

bool Position::isValid() const
{
    return m_valid;
}

QPointF Position::position() const
{
    return m_position;
}

QPointF& Position::position()
{
    return m_position;
}

double Position::angle() const
{
    return m_angle;
}

double& Position::angle()
{
    return m_angle;
}

QString Position::toString() const
{
    return '{' + QString::number(m_position.x()) + "," + QString::number(m_position.y()) + '}';
}

QDataStream& operator >>(QDataStream& in, Position& pos)
{
    in >> pos.m_valid;
    in >> pos.m_position;
    in >> pos.m_angle;
    return in;
}

QDataStream& operator <<(QDataStream& out, const Position& pos)
{
    out << pos.m_valid;
    out << pos.m_position;
    out << pos.m_angle;
    return out;
}

bool Position::operator == (const Position& pos) const
{
    return m_valid==pos.m_valid && m_position == pos.m_position && m_angle == pos.m_angle;
}

bool Position::operator != (const Position& pos) const
{
    return m_valid!=pos.m_valid || m_position != pos.m_position || m_angle != pos.m_angle;
}
