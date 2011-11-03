#ifndef SHUTDOWN_HPP
#define SHUTDOWN_HPP

#include <Commande/Commande>

namespace Commande {

class Shutdown : public Commande
{
    Q_OBJECT
public:
    Shutdown();

    static Shutdown* extract(QDataStream& in);
    QDataStream& serialize(QDataStream& out) const;

};

}

#endif // SHUTDOWN_HPP
