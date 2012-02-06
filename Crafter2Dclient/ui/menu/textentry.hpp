#ifndef TEXTENTRY_HPP
#define TEXTENTRY_HPP

#include <QGraphicsProxyWidget>

namespace UI {

class TextEntry : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    TextEntry(const QString& text, QGraphicsItem* parent = 0);
    
signals:
    
public slots:
    
};

}

#endif // TEXTENTRY_HPP
