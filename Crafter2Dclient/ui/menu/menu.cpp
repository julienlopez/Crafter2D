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

bool UI::Menu::fermerOpenedMenu()
{
    if(!s_openedMenu) return false;
    s_openedMenu->fermer();
    return true;
}

void UI::Menu::ouvrir()
{
    qDebug() << "Menu::ouvrir()";
    fermerOpenedMenu();
    show();
    s_openedMenu = this;
}

void UI::Menu::fermer()
{
    qDebug() << "Menu::femer()";
    hide();
    deleteLater();
    if(s_openedMenu == this) s_openedMenu = 0;
}
