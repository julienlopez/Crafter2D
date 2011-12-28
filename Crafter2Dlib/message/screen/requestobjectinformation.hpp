#ifndef REQUESTOBJECTINFORMATION_HPP
#define REQUESTOBJECTINFORMATION_HPP

#include "screen.hpp"

namespace Message {
namespace Screen {

class RequestObjectInformation : public Screen
{
    Q_OBJECT
public:
    RequestObjectInformation(quint64 code, quint64 id);

    quint64 code() const;
    quint64 id() const;

    static RequestObjectInformation* extract(QDataStream& in, quint64 id);
    virtual QDataStream& serialize(QDataStream& out) const;

    static const quint64 s_id = 5006;

private:
    quint64 m_code;
    quint64 m_id;
};

}}

#endif // REQUESTOBJECTINFORMATION_HPP
