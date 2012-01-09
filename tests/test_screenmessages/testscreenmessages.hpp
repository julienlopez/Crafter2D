#ifndef TESTSCREENMESSAGES_HPP
#define TESTSCREENMESSAGES_HPP

#include <QStringList>
#include <QDir>

class TestScreenMessages
{
public:
    TestScreenMessages();

    bool run(const QStringList& lst);

private:
    QDir m_dir;

    bool testDir(const QString& str);
    QString checkId(const QString& str);
    qint64 checkIdHpp(const QString& str);
    QString checkIdCpp(const QString& str, qint64 id);
    bool checkExtract(QMap<QString, QString> classes);
};

#endif // TESTSCREENMESSAGES_HPP
