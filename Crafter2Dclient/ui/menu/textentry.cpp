#include "textentry.hpp"

#include <QLabel>
#include <QFont>

UI::TextEntry::TextEntry(const QString& text, QGraphicsItem* parent) :
    QGraphicsProxyWidget(parent)
{
    QLabel* l = new QLabel(text);
    l->setFont(QFont("arial", 1));
    setWidget(l);
}
