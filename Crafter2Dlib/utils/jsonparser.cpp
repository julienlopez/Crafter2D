#include "jsonparser.hpp"

#include <QStringList>
#include <QStack>

QList<QChar> Utils::JsonParser::caractereEvitementDebut = QList<QChar>() << '"' << '{' << '[';
QList<QChar> Utils::JsonParser::caractereEvitementFin = QList<QChar>() << '"' << '}' << ']';

Utils::JsonParser::JsonParser()
{
    clearLastError();
}

QVariantMap Utils::JsonParser::parse( const QString &jsonData, bool *ok )
{
    bool parsingOk = false;
    QVariantMap resultat = parseObject( jsonData, &parsingOk );
    if ( ok!=0 )
        *ok = parsingOk;
    if ( parsingOk )
    {
        return resultat;
    }
    else
    {
        return QVariantMap();
    }
}

QString Utils::JsonParser::lastError() const
{
    return m_lastError;
}

void Utils::JsonParser::clearLastError()
{
    m_lastError = "Aucune erreur";
}

QVariantMap Utils::JsonParser::parseObject( QString object, bool *ok )
{
    if ( ! object.startsWith( '{' ) || ! object.endsWith( '}' ) )
    {
        m_lastError = "Syntaxe incorrecte, un objet doit commencer par '{' et finir par '}'";
        if ( ok != NULL )
            *ok = false;
        return QVariantMap();
    }
    object.remove( 0, 1 );
    object.remove( object.size() - 1, 1 );
    bool parsingOk = false;
    QVariantMap res = parsePair( object, &parsingOk );
    if ( ok != 0 )
    {
        *ok = parsingOk;
    }
    if ( parsingOk )
    {
        return res;
    }
    else
    {
        return QVariantMap();
    }
}

QVariantMap Utils::JsonParser::parsePair( const QString &object, bool *ok )
{
    QVariantMap resultat;
    QStringList membres = JsonParser::split( object, ',' );
    for ( int i = 0 ; i < membres.size() ; i++ )
    {
        QStringList detail = JsonParser::split( membres.at( i ), ':' );
        if ( detail.size() != 2 )
        {
            m_lastError = "syntaxe incorrecte vers: ` " + membres.at( i ) + " `";
            *ok = false;
            return QVariantMap();
        }
        QString valeur = detail.at( 1 ).trimmed();
        QString nom = detail.at( 0 ).trimmed();

        if ( nom.startsWith( '"' ) && nom.endsWith( '"' ) )
        {
            nom.remove( 0, 1 );
            nom.remove( nom.size() - 1, 1 );
        }
        bool res = false;
        QVariant value = parseValue( valeur, &res );
        if(!res)
        {
            *ok = false;
            return resultat;
        }
        resultat.insert( nom, value );
    }
    *ok = true;
    return resultat;
}

QVariant Utils::JsonParser::parseValue( QString valeur, bool *ok )
{
    bool res = false;
    if ( valeur.startsWith( '{' ) && valeur.endsWith( '}' ) )
    {
        // c'est un objet
        QVariantMap value = parseObject( valeur, &res );
        if ( ! res )
        {
            m_lastError = "Impossible de parser l'objet' : ` " + valeur + " `";
            *ok = false;
            return QVariant();
        }
        *ok = true;
        return value;
    }
    else
    {
        if ( valeur.startsWith( '\"' ) && valeur.endsWith( '\"' ) )
        {
            //c'est une chaine de carractÃ¨re
            valeur.remove( 0, 1 );
            valeur.remove( valeur.size() - 1, 1 );
            *ok = true;
            return QVariant( valeur );
        }
        else
        {
            if ( valeur.startsWith( '[' ) && valeur.endsWith( ']' ) )
            {
                //c'est un tableau
                QVariantList array = parseArray( valeur, &res );
                if ( !res )
                {
                    m_lastError = "Impossible de parser le tableau : ` " + valeur + " `";
                    *ok = false;
                    return QVariant();
                }
                *ok = true;
                return array;
            }
            else
            {
                *ok = true;
                if ( valeur == "true" )
                    return QVariant( true );
                if ( valeur == "false" )
                    return QVariant( false );
                if ( valeur == "null" )
                    return QVariant();
                QVariant nombre =  parseNumber( valeur, &res );
                if( ! res )
                {
                    m_lastError = "Impossible de parser le nombre ` " + valeur + " `";
                    *ok = false;
                    return QVariant();
                }
                return nombre;
            }
        }
    }
}

QVariantList Utils::JsonParser::parseArray ( QString array, bool *ok )
{
    if ( !array.startsWith( '[' ) || !array.endsWith( ']' ) )
    {
        *ok = false;
        return QVariantList();
    }
    array.remove( 0, 1 );
    array.remove( array.size() - 1, 1 );
    QStringList valuesList = split( array, ',');
    QVariantList resultat;
    for ( int i = 0; i<valuesList.size(); i++ )
    {
        bool res = false;
        QVariant value = parseValue( valuesList.at(i), &res );
        if(!res)
        {
            *ok = false;
            return resultat;
        }
        resultat << value;
    }
    *ok = true;
    return resultat;
}

QVariant Utils::JsonParser::parseNumber( const QString &value, bool *ok )
{
    QVariant resultat;
    bool res;
    if ( value.contains( '.' ) || value.contains( 'e' ) || value.contains( 'E' ) )
        resultat = value.toDouble( &res );
    else resultat = value.toInt( &res );
    if ( ! res )
    {
        *ok = false;
        return QVariant();
    }
    *ok = true;
    return resultat;
}

QStringList Utils::JsonParser::split(QString string, QChar separator)
{
    QStringList resultat;
    while(true)
    {
        int pos = string.indexOf( separator );
        if ( pos == -1 ) break;
        QStack<unsigned int> pile;
        for ( int i = 0; true; i++ )
        {
            if ( i==string.size()-1 )
            {
                pos = -1;
                break;
            }
            if ( string.at( i ) == separator && pile.empty() )
            {
                if ( i > pos ) pos = i;
                break;
            }
            if ( caractereEvitementDebut.contains( string.at( i ) ) && ( i == 0 || string.at( i - 1 ) != '\\' ) )
                pile.push( caractereEvitementDebut.indexOf( string.at( i ) ) );

            if ( !pile.empty() && string.at( i ) == caractereEvitementFin.at( pile.top() ) )
                pile.pop();
        }

        if ( pos == -1 ) break;
        resultat << string.left(pos);
        string.remove(0,pos+1);
    }
    if(!string.isEmpty()) resultat << string;
    return resultat;
}
