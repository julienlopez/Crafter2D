#ifndef COMMANDE_HPP
#define COMMANDE_HPP

#include <QObject>
#include <QVariant>
#include <QDataStream>

namespace Commande {

class Commande : public QObject
{
    Q_OBJECT
public:
    Commande(quint64 id =0, QObject *parent = 0);
    Commande(const Commande& m);

    quint64 id() const;

    static Commande* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

protected:
    quint64 m_id;

};

}

#endif // COMMANDE_HPP
