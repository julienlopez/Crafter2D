#ifndef JSONPARSER_HPP
#define JSONPARSER_HPP

#include <QVariantList>

namespace Utils {

class JsonParser
{

protected:
    QString     m_lastError;
    static QList<QChar> caractereEvitementDebut;
    static QList<QChar> caractereEvitementFin;

    QVariantMap parseObject( QString object, bool *ok );

    QVariantMap parsePair( const QString& value, bool *ok );

    QVariant parseValue( QString valeur, bool *ok );
    QVariantList parseArray( QString array, bool *ok );

    QVariant parseNumber( const QString& value, bool *ok );

    static QStringList split(QString string, QChar separator);

public:
    JsonParser();

    QVariantMap parse(const QString &jsonData, bool *ok = 0);

    QString lastError() const;

    void clearLastError();
};

}

#endif // JSONPARSER_HPP
