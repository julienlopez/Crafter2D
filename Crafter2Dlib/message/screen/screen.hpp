#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "../message.hpp"

namespace Message {
namespace Screen {


class Screen : public Message
{
    Q_OBJECT
public:
    Screen(quint64 id);

    static Message *extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5000;
};

}}

#endif // SCREEN_HPP
