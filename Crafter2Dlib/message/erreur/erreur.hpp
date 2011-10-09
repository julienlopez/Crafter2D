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

    static Erreur* extract(quint64 id, QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

private:
    QString m_message;
};

}}

#endif // ERREUR_HPP
