#ifndef CLIENTINFO_HPP
#define CLIENTINFO_HPP

#include <QString>

class sPlayer;

class ClientInfo
{
public:
    ClientInfo();

    quint64 id() const;
    QString pseudo() const;
    sPlayer* player();

protected:
    void setId(quint64 id);
    void setPseudo(QString pseudo);
    void setPlayer(sPlayer* p);

private:
    quint64 m_id;
    QString m_pseudo;
    sPlayer* m_player;
};

#endif // CLIENTINFO_HPP
