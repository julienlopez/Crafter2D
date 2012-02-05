#include "gplayer.hpp"

gPlayer::gPlayer(quint64 id, const QString& pseudo): WorldElement(id), m_pseudo(pseudo)
{}

void gPlayer::serialize(QDataStream& out) const
{
    out << s_code << id() << m_pseudo << position() << m_inventory;
}

gPlayer* gPlayer::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    QString pseudo;
    in >> pseudo;
    gPlayer* res = new gPlayer(id, pseudo);
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

QString gPlayer::pseudo() const
{
    return m_pseudo;
}

Inventory& gPlayer::inventory()
{
    return m_inventory;
}

const Inventory& gPlayer::inventory() const
{
    return m_inventory;
}

void gPlayer::setPseudo(const QString& pseudo)
{
    m_pseudo = pseudo;
}
