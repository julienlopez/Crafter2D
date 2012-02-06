#ifndef MENU_HPP
#define MENU_HPP

#include <QGraphicsWidget>

class QGraphicsLinearLayout;

namespace UI {

class Menu : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit Menu(QGraphicsItem* parent = 0);

    void addItem(QGraphicsWidget* item);
    void addStretch(int stretch = 1);

    static Menu* openedMenu();

    void fermer();

private:
    QGraphicsLinearLayout* m_layout;

    static Menu* s_openedMenu;
    
signals:
    
public slots:
    
};

}

#endif // MENU_HPP
