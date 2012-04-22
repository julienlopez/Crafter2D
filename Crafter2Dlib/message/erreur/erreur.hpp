#ifndef ERREUR_HPP
#define ERREUR_HPP

#include "../message.hpp"

namespace Message {
namespace Erreur {

class Erreur : public Message
{
    Q_OBJECT
public:
    explicit Erreur(quint64 id, const QString& message);

    QString message() const;

    static Message* extract(QDataStream &in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 1000;
private:
    QString m_message;
};

}}

#endif // ERREUR_HPP
