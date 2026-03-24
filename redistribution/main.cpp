#include "redistribution.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    redistribution w;
    w.show();
    return QCoreApplication::exec();
}
