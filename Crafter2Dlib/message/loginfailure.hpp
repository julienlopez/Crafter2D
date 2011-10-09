#ifndef LOGINFAILURE_HPP
#define LOGINFAILURE_HPP

#include "message.hpp"

namespace Message {

class LoginFailure : public Message
{
    Q_OBJECT
public:
    LoginFailure(const QString& erreur);

    QString erreur() const;

    static LoginFailure* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

private:
    QString m_erreur;
};

}

#endif // MESSAGELOGINFAILURE_HPP
