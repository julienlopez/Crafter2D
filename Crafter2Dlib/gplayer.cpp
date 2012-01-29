#include "gplayer.hpp"

gPlayer::gPlayer(quint64 id): WorldElement(id)
{}

void gPlayer::serialize(QDataStream& out) const
{
    out << s_code << id() << position() << m_inventory;
}

gPlayer* gPlayer::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    gPlayer* res = new gPlayer(id);
    Position pos;
    in >> pos;
    res->setPosition(pos);
    in >> res->m_inventory;
    return res;
}

quint64 gPlayer::code() const
{
    return s_code;
}

Inventory& gPlayer::inventory()
{
    return m_inventory;
}

const Inventory& gPlayer::inventory() const
{
    return m_inventory;
}
