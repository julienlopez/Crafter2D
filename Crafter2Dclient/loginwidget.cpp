#include "loginwidget.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent)
{
    QVBoxLayout* vl = new QVBoxLayout;

    QHBoxLayout* hl = new QHBoxLayout;
    hl->addWidget(new QLabel(tr("Login: ")));
    loginLabel = new QLineEdit;
    hl->addWidget(loginLabel);
    vl->addLayout(hl);

    hl = new QHBoxLayout;
    hl->addWidget(new QLabel(tr("Mot de Passe: ")));
    mdpLabel = new QLineEdit;
    mdpLabel->setEchoMode(QLineEdit::Password);
    hl->addWidget(mdpLabel);
    vl->addLayout(hl);

    hl = new QHBoxLayout;
    hl->addSpacing(0);
    bouton = new QPushButton(tr("Connexion"));
    connect(bouton, SIGNAL(clicked()), this, SLOT(onLoginSend()));
    hl->addWidget(bouton);
    vl->addLayout(hl);

    setLayout(vl);
}

void LoginWidget::onLoginSend()
{
    emit sendLogin(loginLabel->text(), mdpLabel->text());
    loginLabel->setDisabled(true);
    mdpLabel->setDisabled(true);
    bouton->setDisabled(true);
}
