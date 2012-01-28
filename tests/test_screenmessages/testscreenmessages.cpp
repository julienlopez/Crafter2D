#include "testscreenmessages.hpp"

#include <QDebug>

TestScreenMessages::TestScreenMessages()
{
}


bool TestScreenMessages::run(const QStringList& lst)
{
    QString s;
    foreach(s, lst)
    {
        if(s.endsWith("test_screenmessages.exe")) continue;
        qDebug() << "test de " << s;
        if(!testDir(s))
        {
            qDebug() << "erreur lors du test de " << s;
            return false;
        }
        else qDebug() << s << " ok";
    }
    return true;
}

bool TestScreenMessages::testDir(const QString& str)
{
    m_dir = QDir(str);
    if(!m_dir.exists()) return false;
    QMap<QString, QString> classesFiles;
    QStringList files = m_dir.entryList();
    QString f;
    foreach(f, files)
    {
        if(f == "." || f == ".." || f.startsWith("screen.")) continue;
        f.chop(f.length() - f.lastIndexOf('.'));
        classesFiles[f] = "";
    }
    foreach(f, classesFiles.keys())
    {
        QString str  = checkId(f);
        if(str.isEmpty()) return false;
        classesFiles[f] = str;
    }
    foreach(f, classesFiles.keys()) if(classesFiles[f].isEmpty()) return false;
    return checkExtract(classesFiles);
}

QString TestScreenMessages::checkId(const QString &str)
{
    qint64 id = checkIdHpp(str);
    if(id < 0) return QString();
    return checkIdCpp(str, id);
}

qint64 TestScreenMessages::checkIdHpp(const QString &str)
{
    QFile f(m_dir.filePath(str+".hpp"));
    if(!f.exists() || !f.open(QIODevice::ReadOnly)) return -1;
    QTextStream stream(&f);
    QString line;
    qint64 id = -1;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(!line.contains("static const quint64 s_id =")) continue;
        line.remove(0, line.indexOf("=")+2);
        line.chop(1);
        bool ok = false;
        id = line.toLongLong(&ok);
        if(ok) return id;
    }
    return -1;
}

QString TestScreenMessages::checkIdCpp(const QString& str, qint64 id)
{
    QFile f(m_dir.filePath(str+".cpp"));
    if(!f.exists() || !f.open(QIODevice::ReadOnly)) return QString();
    QTextStream stream(&f);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(line.contains("Message::Screen::"))
        {
            line.remove(0, 17);
            line.chop(line.length() - line.indexOf(":"));
            return line;
        }
    }
    return QString();
}

bool TestScreenMessages::checkExtract(QMap<QString, QString> classes)
{
    QFile f(m_dir.filePath("screen.cpp"));
    if(!f.exists() || !f.open(QIODevice::ReadOnly)) return false;
    QTextStream stream(&f);
    QString line;
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(line.contains("Message::Screen::Screen::extract(")) break;
    }
    while(!stream.atEnd())
    {
        line = stream.readLine();
        if(line == "}") break;
        int i = line.indexOf("==");
        if(i == -1) continue;
        line.remove(0, i+3);
        line.chop(line.length() - line.indexOf(":"));

        if(classes.values().contains(line))
            classes.remove(classes.key(line));
    }
    return classes.empty();
}
