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

    static Message *extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5002;

private:
    Position m_position;
};

}}

#endif // SETPOSITION_HPP
