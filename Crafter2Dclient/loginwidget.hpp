#ifndef LOGINWIDGET_HPP
#define LOGINWIDGET_HPP

#include <QWidget>

class QLineEdit;
class QPushButton;

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);

private:
    QLineEdit* loginLabel;
    QLineEdit* mdpLabel;
    QPushButton* bouton;

signals:
    void sendLogin(QString, QString);

private slots:
    void onLoginSend();
};

#endif // LOGINWIDGET_HPP
