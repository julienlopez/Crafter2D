#ifndef SUTILS_HPP
#define SUTILS_HPP

#include <QFile>
#include <QTextStream>

class sUtils
{
public:
    static QTextStream& log();

private:
    struct Inner
    {
        Inner();
        ~Inner();
        QFile m_nomFileLog;
        QTextStream m_log;
    };

    static Inner s_inner;
};

#endif // SUTILS_HPP
