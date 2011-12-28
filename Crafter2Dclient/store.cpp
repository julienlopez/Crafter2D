#include "store.hpp"
#include "cplayer.hpp"

#include <gBuilding>
#include <gObject>
#include <gStaticObject>
#include <Message/Screen/RequestObjectInformation>

Store Store::s_instance;

void Store::updatePosition(quint64 code, quint64 id, const Position& pos) {
    switch(code)
    {
    case gPlayer::s_code:
        updatePositionPlayer(id, pos);
        break;
    case gBuilding::s_code:
        updatePositionBuilding(id, pos);
        break;
    case gObject::s_code:
        updatePositionObject(id, pos);
        break;
    case gStaticObject::s_code:
        updatePositionStaticObject(id, pos);
        break;
    }
}

void Store::updatePositionPlayer(quint64 id, const Position &pos)
{
    if(s_instance.m_players.contains(id)) {
        s_instance.m_players[id]->setPosition(pos);
        return;
    }

    s_instance.emitMessage(Message::Screen::RequestObjectInformation(gPlayer::s_code, id));
}

void Store::updatePositionBuilding(quint64 id, const Position &pos)
{
    if(s_instance.m_building.contains(id)) {
        s_instance.m_building[id]->setPosition(pos);
        return;
    }

    s_instance.emitMessage(Message::Screen::RequestObjectInformation(gBuilding::s_code, id));
}

void Store::updatePositionObject(quint64 id, const Position &pos)
{
    if(s_instance.m_objetcs.contains(id)) {
        s_instance.m_objetcs[id]->setPosition(pos);
        return;
    }

    s_instance.emitMessage(Message::Screen::RequestObjectInformation(gObject::s_code, id));
}

void Store::updatePositionStaticObject(quint64 id, const Position &pos)
{
    if(s_instance.m_staticobjects.contains(id)) {
        s_instance.m_staticobjects[id]->setPosition(pos);
        return;
    }

    s_instance.emitMessage(Message::Screen::RequestObjectInformation(gStaticObject::s_code, id));
}

Store& Store::instance()
{
    return s_instance;
}

Store::Store()
{}

void Store::emitMessage(const Message::Message& message)
{
    emit sendMessage(message);
}
