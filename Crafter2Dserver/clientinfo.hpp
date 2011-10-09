#ifndef CLIENTINFO_HPP
#define CLIENTINFO_HPP

#include <QString>

class ClientInfo
{
public:
    quint64 id() const;
    QString pseudo() const;

protected:
    void setId(quint64 id);
    void setPseudo(QString pseudo);

private:
    quint64 m_id;
    QString m_pseudo;
};

#endif // CLIENTINFO_HPP
