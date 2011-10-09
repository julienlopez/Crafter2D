#include "clientinfo.hpp"

quint64 ClientInfo::id() const
{
    return m_id;
}

QString ClientInfo::pseudo() const
{
    return m_pseudo;
}

void ClientInfo::setId(quint64 id)
{
    m_id = id;
}

void ClientInfo::setPseudo(QString pseudo)
{
    m_pseudo = pseudo;
}
