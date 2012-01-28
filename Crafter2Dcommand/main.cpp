#include <QCoreApplication>

#include "cmd.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Cmd c;
    return a.exec();
}
