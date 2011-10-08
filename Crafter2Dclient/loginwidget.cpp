#include "loginwidget.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent)
{
    QWidget* w = new QWidget();
    w->setFixedSize(250,200);

    QVBoxLayout* vl = new QVBoxLayout;
    vl->setAlignment(Qt::AlignCenter);

    QHBoxLayout* hl = new QHBoxLayout;
    hl->setAlignment(Qt::AlignCenter);
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

    w->setLayout(vl);

    QVBoxLayout* l = new QVBoxLayout;
    l->setAlignment(Qt::AlignCenter);
    l->addWidget(w);
    setLayout(l);
}

void LoginWidget::onLoginSend()
{
    emit sendLogin(loginLabel->text(), mdpLabel->text());
    loginLabel->setDisabled(true);
    mdpLabel->setDisabled(true);
    bouton->setDisabled(true);
}
