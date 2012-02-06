#ifndef MENU_HPP
#define MENU_HPP

#include <QGraphicsWidget>

class QGraphicsLinearLayout;

class Menu : public QGraphicsWidget
{
    Q_OBJECT
public:
    explicit Menu(QGraphicsItem* parent = 0);

    void addItem(QGraphicsWidget* item);
    void addStretch(int stretch = 1);

private:
    QGraphicsLinearLayout* m_layout;
    
signals:
    
public slots:
    
};

#endif // MENU_HPP
