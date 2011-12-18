#include "gplayer.hpp"

gPlayer::gPlayer(quint64 id): WorldElement(id)
{}

void gPlayer::serialize(QDataStream& out) const
{
    out << s_code << id() << position();
}

gPlayer* gPlayer::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    gPlayer* res = new gPlayer(id);
    Position pos;
    in >> pos;
    res->setPosition(pos);
    return res;
}
