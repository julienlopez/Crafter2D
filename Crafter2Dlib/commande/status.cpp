#include "status.hpp"

Commande::Status::Status() : Commande(s_id)
{}

Commande::Status* Commande::Status::extract(QDataStream& in)
{
    return new Status;
}

QDataStream& Commande::Status::serialize(QDataStream& out) const
{
    out << id();
    return out;
}
