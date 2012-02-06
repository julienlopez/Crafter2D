#ifndef INVENTORYDOCK_HPP
#define INVENTORYDOCK_HPP

#include <QDockWidget>

class cPlayer;
class QListWidget;

class QBasicTimer;

namespace UI {

class InventoryDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit InventoryDock(quint64 idPlayer, QWidget *parent = 0);

private:
    quint64 m_idPlayer;
    cPlayer* m_player;
    QListWidget* view;

    QBasicTimer* m_timer;

protected:
    void timerEvent(QTimerEvent* event);
    
signals:
    
public slots:
    void maj();
};

}

#endif // INVENTORYDOCK_HPP
