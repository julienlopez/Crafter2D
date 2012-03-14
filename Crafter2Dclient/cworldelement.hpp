#ifndef CWORLDELEMENT_HPP
#define CWORLDELEMENT_HPP

#include <Position>

#include <QGraphicsItem>

namespace UI {
    class Menu;
}

/**
  * \brief spécialisation de la classe WorldElement pour le client.
  *
  *
  */
class cWorldElement : public QGraphicsItem
{
public:
    cWorldElement(QGraphicsItem* parent);

    virtual void setPosition(const Position& p);
    virtual Position position() const =0;

    UI::Menu* menu();

protected:
    cWorldElement();
    void init();

    void mousePressEvent(QGraphicsSceneMouseEvent* evt);

    virtual void showMenu() =0;

private:
    UI::Menu* m_menu;
};

#endif // CWORLDELEMENT_HPP
