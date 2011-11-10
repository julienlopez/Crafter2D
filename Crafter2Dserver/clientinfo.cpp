#include "clientinfo.hpp"

ClientInfo::ClientInfo()
{
    m_player = 0;
}

quint64 ClientInfo::id() const
{
    return m_id;
}

QString ClientInfo::pseudo() const
{
    return m_pseudo;
}

sPlayer* ClientInfo::player()
{
    return m_player;
}

void ClientInfo::setId(quint64 id)
{
    m_id = id;
}

void ClientInfo::setPseudo(QString pseudo)
{
    m_pseudo = pseudo;
}

void ClientInfo::setPlayer(sPlayer* p)
{
    m_player = p;
}
