#include "sutils.hpp"

#include <QDateTime>
#include <QDebug>

sUtils::Inner sUtils::s_inner;

QTextStream& sUtils::log()
{
    s_inner.m_log << QDateTime::currentDateTime().toString("dd-MM-yyyy hh:mm'ss : ");
    return s_inner.m_log;
}

sUtils::Inner::Inner(): m_nomFileLog("log.txt"), m_log(&m_nomFileLog)
{
    if(!m_nomFileLog.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Impossible d'ouvrir le fichier de debug:";
        qDebug() << m_nomFileLog.errorString();
        qDebug() << m_nomFileLog.fileName();
    }
    log() << "log opérationnel\n";
}

sUtils::Inner::~Inner()
{
    m_nomFileLog.close();
}
