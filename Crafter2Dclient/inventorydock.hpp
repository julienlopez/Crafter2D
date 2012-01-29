#ifndef INVENTORYDOCK_HPP
#define INVENTORYDOCK_HPP

#include <QDockWidget>

class cPlayer;
class QListWidget;

class InventoryDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit InventoryDock(quint64 idPlayer, QWidget *parent = 0);

private:
    cPlayer* m_player;
    QListWidget* view;
    
signals:
    
public slots:
    void maj();
};

#endif // INVENTORYDOCK_HPP
