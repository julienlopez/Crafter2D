#ifndef MESSAGELOGINFAILURE_HPP
#define MESSAGELOGINFAILURE_HPP

#include "message.hpp"

class MessageLoginFailure : public Message
{
    Q_OBJECT
public:
    MessageLoginFailure(const QString& erreur);

    QString erreur() const;

    static MessageLoginFailure* extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

private:
    QString m_erreur;
};

#endif // MESSAGELOGINFAILURE_HPP
