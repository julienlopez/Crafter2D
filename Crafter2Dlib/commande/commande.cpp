#include "commande.hpp"
#include "status.hpp"
#include "shutdown.hpp"
#include "statusupdate.hpp"

Commande::Commande::Commande(quint64 id, QObject *parent) :
    QObject(parent), m_id(id)
{}

Commande::Commande::Commande(const Commande& m): QObject(m.parent()), m_id(m.m_id)
{}

quint64 Commande::Commande::id() const
{
    return m_id;
}

Commande::Commande* Commande::Commande::extract(QDataStream& in)
{
    quint64 id;
    in >> id;
    if(id == 1) return Status::extract(in);
    if(id == 2) return Shutdown::extract(in);
    if(id == 3) return StatusUpdate::extract(in);
    return new Commande(id);
}

QDataStream& Commande::Commande::serialize(QDataStream& out) const
{
    out << m_id;
    return out;
}
