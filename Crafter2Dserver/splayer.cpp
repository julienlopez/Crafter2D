#include "splayer.hpp"
#include "sutils.hpp"

#include <QSqlQuery>
#include <QVariant>

#include <QSqlError>
#include <QDebug>

sPlayer::sPlayer(quint64 id) throw(DataAccessor::Exception): gPlayer(id)
{
    QSqlQuery q("SELECT position FROM user WHERE id=" + QString::number(id));
    if(!q.exec()) throw DataAccessor::Exception("Impossible d'executer la requetes");
    if(q.size() != 1) throw DataAccessor::Exception("Erreur de base de données");

    q.first();
    Position p(q.value(0).toString());
    if(!p.isValid()) throw DataAccessor::Exception("position invalide");

    setPosition(p);
}

sPlayer::~sPlayer()
{}

void sPlayer::save()
{
    qDebug() << "destruction du player " << id();
    QSqlQuery query;
    query.prepare("UPDATE user SET position=:pos WHERE id=:id");
    query.bindValue(":pos", position().toString());
    query.bindValue(":id", id());
    if(!query.exec())
    {
        qDebug() << "impossible d'executer la sauvegarde de sPlayer" << query.lastError().text();
        //SUtils::log() << "impossible d'executer la sauvegarde de sPlayer" + query.lastError().text() + '\n' ;
        return;
    }
    qDebug() << "player sauvegardé";
}
