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

    static Message* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 3000;
};

}}

#endif // ERREURCLIENT_HPP
