#ifndef MESSAGELOGIN_HPP
#define MESSAGELOGIN_HPP

#include <Message>

class MessageLogin : public Message
{
    Q_OBJECT

public:
    MessageLogin(QString login, QString mdp, QObject *parent = 0);

    QString login() const;
    QString mdp() const;

    static MessageLogin* extract(QDataStream& in);
    QDataStream& serialize(QDataStream& out) const;

private:
    QString m_login;
    QString m_mdp;
};

#endif // MESSAGELOGIN_HPP
