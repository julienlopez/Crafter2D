#include "debugdock.hpp"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLineEdit>

UI::DebugDock::DebugDock(QWidget *parent) :
    QDockWidget("debug", parent)
{
    setFixedWidth(200);
    QWidget* w = new QWidget;
    layout = new QVBoxLayout;

    creerGBPosition();

    layout->addSpacing(1);
    w->setLayout(layout);
    setWidget(w);
}

void UI::DebugDock::creerGBPosition()
{
    QGroupBox* gb = new QGroupBox("position");
    QHBoxLayout* hl = new QHBoxLayout;

    lePosx = new QLineEdit;
    lePosx->setReadOnly(true);
    lePosx->setEnabled(false);
    hl->addWidget(lePosx);

    lePosy = new QLineEdit;
    lePosy->setReadOnly(true);
    lePosy->setEnabled(false);
    hl->addWidget(lePosy);

    gb->setLayout(hl);
    layout->addWidget(gb);
}

void UI::DebugDock::setPosition(const Position& pos)
{
    if(!pos.isValid()) {
        lePosx->setText("");
        lePosx->setEnabled(false);
        lePosy->setText("");
        lePosy->setEnabled(false);
        return;
    }
    lePosx->setText(QString::number(pos.position().x()));
    lePosx->setEnabled(true);
    lePosy->setText(QString::number(pos.position().y()));
    lePosy->setEnabled(true);
}
