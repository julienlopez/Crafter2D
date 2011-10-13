#include "splayer.hpp"

#include <QSqlQuery>
#include <QVariant>

sPlayer::sPlayer(quint64 id) throw(DataAccessor::Exception): gPlayer(id)
{
    QSqlQuery q("SELECT position FROM user WHERE id=" + id);
    if(!q.exec()) throw DataAccessor::Exception("Impossible d'executer la requetes");
    if(q.size() != 1) throw DataAccessor::Exception("Erreur de base de données");

    q.first();
    Position p(q.value(0).toString());
    if(!p.isValid()) throw DataAccessor::Exception("position invalide");

    setPosition(p);
}
