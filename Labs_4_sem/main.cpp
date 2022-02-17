#include "Dekstra.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dekstra w;
    w.show();
    return a.exec();
}
