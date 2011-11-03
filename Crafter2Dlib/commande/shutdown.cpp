#include "shutdown.hpp"

Commande::Shutdown::Shutdown(): Commande(2)
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
