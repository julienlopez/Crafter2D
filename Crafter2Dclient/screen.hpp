#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <Message>
#include <Position>

#include <QWidget>

class Screen : public QWidget
{
    Q_OBJECT
public:
    explicit Screen(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* evt);

private:
    Position position;

signals:
    void message(Message&);

public slots:
    void handleMessage(Message* message);
};

#endif // SCREEN_HPP
