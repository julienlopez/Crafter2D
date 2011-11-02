#ifndef SENDPOSITION_H
#define SENDPOSITION_H

#include "screen.hpp"
#include "../../position.hpp"

namespace Message {
namespace Screen {

class SendPosition : public Screen
{
    Q_OBJECT
public:
    SendPosition(const Position& position);

    Position position() const;

    static SendPosition* extract(QDataStream& in, quint64 id);
    virtual QDataStream& serialize(QDataStream& out) const;

private:
    Position m_position;
};

}}

#endif // SENDPOSITION_H
