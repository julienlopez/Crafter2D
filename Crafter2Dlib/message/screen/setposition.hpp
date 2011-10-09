#ifndef SETPOSITION_HPP
#define SETPOSITION_HPP

#include "screen.hpp"
#include "../../position.hpp"

namespace Message {
namespace Screen {

class SetPosition : public Screen
{
    Q_OBJECT
public:
    explicit SetPosition(const Position& position);

    Position position() const;

    static SetPosition* extract(QDataStream& in, quint64 id);
    virtual QDataStream& serialize(QDataStream& out) const;

private:
    Position m_position;
};

}}

#endif // SETPOSITION_HPP
