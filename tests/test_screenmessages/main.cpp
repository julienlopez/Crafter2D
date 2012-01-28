#include "testscreenmessages.hpp"

int main(int argc, char *argv[])
{
    TestScreenMessages t;
    QStringList lst;
    for(int i = 0; i < argc; ++i)
        lst << QString(argv[i]);
    return t.run(lst);
}
