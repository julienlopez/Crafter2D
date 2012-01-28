#include "statusupdate.hpp"

#include <QDebug>

Commande::StatusUpdate::StatusUpdate(const QString& str): Commande(s_id), m_message(str)
{}

Commande::StatusUpdate* Commande::StatusUpdate::extract(QDataStream& in)
{
    QString str;
    in >> str;
    return new StatusUpdate(str);
}

QDataStream& Commande::StatusUpdate::serialize(QDataStream& out) const
{
    qDebug() << "StatusUpdate::serialize(): " << id() << ", " << m_message;
    out << id();
    out << m_message;
    return out;
}

QString Commande::StatusUpdate::message() const
{
    return m_message;
}
