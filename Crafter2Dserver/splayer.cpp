#include "splayer.hpp"
#include "sutils.hpp"

#include <QSqlQuery>
#include <QVariant>

#include <QSqlError>
#include <QDebug>

sPlayer::sPlayer(quint64 id) throw(DataAccessor::Exception): gPlayer(id)
{
    QSqlQuery q("SELECT pseudo, position, inventory FROM user WHERE id=" + QString::number(id));
    if(!q.exec()) throw DataAccessor::Exception("Impossible d'executer la requetes");
    if(q.size() != 1) throw DataAccessor::Exception("Erreur de base de données");

    q.first();
    setPseudo(q.value(0).toString());
    Position p(q.value(1).toString());
    if(!p.isValid()) throw DataAccessor::Exception("position invalide");
    setPosition(p);

    inventory() = Inventory::fromString(q.value(2).toString());
}

sPlayer::~sPlayer()
{
    qDebug() << "destruction du player " << id();
}

void sPlayer::save()
{
    qDebug() << "sauvegarde du player " << id();
    QSqlQuery query;
    query.prepare("UPDATE user SET position=:pos WHERE id=:id");
    query.bindValue(":pos", position().toString());
    query.bindValue(":id", id());
    query.bindValue(":inventory", inventory().toString());
    if(!query.exec())
    {
        qDebug() << "impossible d'executer la sauvegarde de sPlayer" << query.lastError().text();
        return;
    }
    qDebug() << "player sauvegardé";
}
