#ifndef ERREURCLIENT_HPP
#define ERREURCLIENT_HPP

#include "erreur.hpp"

namespace Message {
namespace Erreur {

class ErreurClient : public Erreur
{
    Q_OBJECT
public:
    ErreurClient(const QString& message);
    ErreurClient(quint64 id, const QString& message);

    static ErreurClient* extract(quint64 id, QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;
};

}}

#endif // ERREURCLIENT_HPP
