#include "menu.hpp"

#include <QGraphicsLinearLayout>

#include <QDebug>

UI::Menu* UI::Menu::s_openedMenu = 0;

UI::Menu::Menu(QGraphicsItem *parent) :
    QGraphicsWidget(parent)
{
    m_layout = new QGraphicsLinearLayout(Qt::Vertical);
    m_layout->setContentsMargins(1,1,1,1);
    setLayout(m_layout);

    setAutoFillBackground(true);
    setPalette(QPalette(Qt::black, Qt::gray));

    if(s_openedMenu) s_openedMenu->fermer();
    s_openedMenu = this;
}

void UI::Menu::addItem(QGraphicsWidget *item)
{
    m_layout->addItem(item);
    item->setParent(this);
    item->setParentItem(this);
    item->setPalette(palette());
}

void UI::Menu::addStretch(int stretch)
{
    m_layout->addStretch(stretch);
}

UI::Menu* UI::Menu::openedMenu()
{
    return s_openedMenu;
}

void UI::Menu::fermer()
{
    qDebug() << "Menu::femer()";
    hide();
    deleteLater();
}
