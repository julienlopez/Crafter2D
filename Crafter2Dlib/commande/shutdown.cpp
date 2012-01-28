#include "shutdown.hpp"

Commande::Shutdown::Shutdown(): Commande(s_id)
{}

Commande::Shutdown* Commande::Shutdown::extract(QDataStream& in)
{
    return new Shutdown;
}

QDataStream& Commande::Shutdown::serialize(QDataStream& out) const
{
    out << id();
    return out;
}
