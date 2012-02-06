#include "menu.hpp"

#include <QGraphicsLinearLayout>

Menu::Menu(QGraphicsItem *parent) :
    QGraphicsWidget(parent)
{
    m_layout = new QGraphicsLinearLayout(Qt::Vertical);

    setLayout(m_layout);
}

void Menu::addItem(QGraphicsWidget *item)
{
    m_layout->addItem(item);
}

void Menu::addStretch(int stretch)
{
    m_layout->addStretch(stretch);
}
