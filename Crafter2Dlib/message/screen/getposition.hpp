#ifndef GETPOSITION_HPP
#define GETPOSITION_HPP

#include "screen.hpp"

namespace Message {
namespace Screen {

class GetPosition : public Screen
{
    Q_OBJECT
public:
    explicit GetPosition();

    static Message *extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5001;
};

}}

#endif // GETPOSITION_HPP
