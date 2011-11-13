#include "gplayer.hpp"

gPlayer::gPlayer(quint64 id): WorldElement(id)
{}

Position gPlayer::position() const
{
    return m_position;
}

void gPlayer::setPosition(const Position& p)
{
    m_position = p;
}

void gPlayer::serialize(QDataStream& out) const
{
    out << s_code << id() << m_position;
}

gPlayer* gPlayer::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    gPlayer* res = new gPlayer(id);
    in >> res->m_position;
    return res;
}
