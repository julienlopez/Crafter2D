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

    static Screen* extract(QDataStream& in, quint64 id);
    virtual QDataStream& serialize(QDataStream& out) const;

};

}}

#endif // SCREEN_HPP
