#ifndef MAJPOSITION_HPP
#define MAJPOSITION_HPP

#include "screen.hpp"

#include "../../position.hpp"

class WorldElement;

namespace Message {
namespace Screen {

class MajPosition : public Screen
{
    Q_OBJECT
public:
    MajPosition(WorldElement* el);
    MajPosition(quint64 objectCode, quint64 objectId, const Position& position);

    quint64 objectCode() const;
    quint64 objectId() const;
    Position position() const;

    static Message *extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5005;
    
private:
    quint64 m_objectCode;
    quint64 m_objectId;
    Position m_position;
    
};

}}

#endif // MAJPOSITION_HPP
