#include "HBService.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HBService w;
    w.show();
    return a.exec();
}
