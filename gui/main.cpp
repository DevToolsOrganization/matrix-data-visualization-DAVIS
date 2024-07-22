#include "davis_gui.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DavisGUI w;
    w.show();
    return a.exec();
}
