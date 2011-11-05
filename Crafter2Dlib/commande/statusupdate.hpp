#ifndef STATUSUPDATE_HPP
#define STATUSUPDATE_HPP

#include <Commande/Commande>

namespace Commande {

class StatusUpdate : public Commande
{
    Q_OBJECT
public:
    StatusUpdate(const QString& str);

    static StatusUpdate* extract(QDataStream& in);
    QDataStream& serialize(QDataStream& out) const;

    QString message() const;

private:
    QString m_message;

};

}

#endif // STATUSUPDATE_HPP
