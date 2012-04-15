#include "splayer.hpp"
#include "sutils.hpp"

#include <QSqlQuery>
#include <QVariant>

#include <QSqlError>
#include <QDebug>

sPlayer::sPlayer(quint64 id): gPlayer(id)
{}

sPlayer::~sPlayer()
{
    qDebug() << "destruction du player " << id();
}

void sPlayer::save()
{
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
}

sPlayer* sPlayer::load(quint64 id) throw(DataAccessor::Exception)
{
    QSqlQuery q("SELECT pseudo, position, inventory FROM user WHERE id=" + QString::number(id));
    if(!q.exec()) throw DataAccessor::Exception("Impossible d'executer la requetes");
    if(q.size() != 1) throw DataAccessor::Exception("Erreur de base de données");

    sPlayer* player = new sPlayer(id);
    q.first();
    player->setPseudo(q.value(0).toString());
    Position p(q.value(1).toString());
    if(!p.isValid()) throw DataAccessor::Exception("position invalide");
    player->setPosition(p);

    player->inventory() = Inventory::fromString(q.value(2).toString());

    return player;
}
