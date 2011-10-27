#include "position.hpp"

#include <QStringList>

Position::Position(): m_valid(false)
{}

Position::Position(const QPointF& position): m_valid(true), m_position(position)
{}

Position::Position(QString str): m_valid(false)
{
    if(!str.startsWith('{') || !str.endsWith('}')) return;
    str.chop(1);
    str.remove(0,1);
    QStringList lst = str.split(',');
    if(lst.size() != 2) return;
    bool ok = false;
    m_position.setX(lst.at(0).toDouble(&ok));
    if(!ok) return;
    m_position.setY(lst.at(0).toDouble(&ok));
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

QString Position::toString() const
{
    return '{' + QString::number(m_position.x()) + "," + QString::number(m_position.y()) + '}';
}

QDataStream& operator >>(QDataStream& in, Position& pos)
{
    in >> pos.m_valid;
    in >> pos.m_position;
    return in;
}

QDataStream& operator <<(QDataStream& out, const Position& pos)
{
    out << pos.m_valid;
    out << pos.m_position;
    return out;
}
