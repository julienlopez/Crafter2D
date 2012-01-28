#ifndef STATUS_HPP
#define STATUS_HPP

#include <Commande/Commande>

namespace Commande {

class Status : public Commande
{
    Q_OBJECT
public:
    Status();

    static Status* extract(QDataStream& in);
    QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 1;
};

}

#endif // STATUS_HPP
