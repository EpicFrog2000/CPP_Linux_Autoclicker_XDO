#include <QApplication>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window1 w;
    w.show();
    return a.exec();
}
