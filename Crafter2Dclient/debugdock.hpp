#ifndef DEBUGDOCK_HPP
#define DEBUGDOCK_HPP

#include <Position>

#include <QDockWidget>

class QVBoxLayout;
class QLineEdit;

class DebugDock : public QDockWidget
{
    Q_OBJECT
public:
    explicit DebugDock(QWidget *parent = 0);

private:
    QVBoxLayout* layout;
    //position
    QLineEdit* lePosx;
    QLineEdit* lePosy;

    void creerGBPosition();
signals:

public slots:
    void setPosition(const Position& pos);
};

#endif // DEBUGDOCK_HPP
