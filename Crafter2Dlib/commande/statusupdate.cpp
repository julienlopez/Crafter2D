#include "statusupdate.hpp"

Commande::StatusUpdate::StatusUpdate(const QString& str): Commande(3), m_message(str)
{}

Commande::StatusUpdate* Commande::StatusUpdate::extract(QDataStream& in)
{
    QString str;
    in >> str;
    return new StatusUpdate(str);
}

QDataStream& Commande::StatusUpdate::serialize(QDataStream& out) const
{
    out << id();
    out << m_message;
    return out;
}

QString Commande::StatusUpdate::message() const
{
    return m_message;
}
