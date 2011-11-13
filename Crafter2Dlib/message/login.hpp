#ifndef LOGIN_HPP
#define LOGIN_HPP

#include <Message/Message>

namespace Message {

class Login : public Message
{
    Q_OBJECT

public:
    Login(QString login, QString mdp, QObject *parent = 0);

    QString login() const;
    QString mdp() const;

    static Login* extract(QDataStream& in);
    QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 1;

private:
    QString m_login;
    QString m_mdp;
};

}

#endif // MESSAGELOGIN_HPP
