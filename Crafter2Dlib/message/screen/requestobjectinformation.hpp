#ifndef REQUESTOBJECTINFORMATION_HPP
#define REQUESTOBJECTINFORMATION_HPP

#include "screen.hpp"

namespace Message {
namespace Screen {

class RequestObjectInformation : public Screen
{
    Q_OBJECT
public:
    RequestObjectInformation(quint64 code, quint64 idPlayer);

    quint64 code() const;
    quint64 idPlayer() const;

    static Message *extract(QDataStream& in);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5006;

private:
    quint64 m_code;
    quint64 m_idPlayer;
};

}}

#endif // REQUESTOBJECTINFORMATION_HPP
