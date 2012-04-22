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

    static Message *extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5003;

private:
    Position m_position;
};

}}

#endif // SENDPOSITION_H
