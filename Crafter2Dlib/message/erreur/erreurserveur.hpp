#ifndef ERREURSERVEUR_HPP
#define ERREURSERVEUR_HPP

#include "erreur.hpp"

namespace Message {
namespace Erreur {

class ErreurServeur : public Erreur
{
    Q_OBJECT
public:
    ErreurServeur(const QString& message);
    ErreurServeur(quint64 id, const QString& message);

    static ErreurServeur* extract(quint64 id, QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 1000;
};

}}

#endif // ERREURSERVEUR_HPP
