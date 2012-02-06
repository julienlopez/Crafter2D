#include <QtGui/QApplication>
#include "ui/mainwindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    UI::MainWindow w;
    w.show();

    return a.exec();
}
