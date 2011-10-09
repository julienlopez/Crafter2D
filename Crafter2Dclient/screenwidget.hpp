#ifndef SCREENWIDGET_HPP
#define SCREENWIDGET_HPP

#include <Message/Message>
#include <Position>

#include <QWidget>

class ScreenWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ScreenWidget(QWidget *parent = 0);

protected:
    void paintEvent(QPaintEvent* evt);

private:
    Position position;

signals:
    void message(Message::Message&);

public slots:
    void handleMessage(Message::Message* message);
};

#endif // SCREENWIDGET_HPP
