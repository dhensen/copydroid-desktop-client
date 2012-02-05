#include <QtGui/QApplication>
#include <QSharedMemory>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    /* begin sharedMemory: to prevent this app from being ran multiple times */
    QSharedMemory sharedMemory;
    sharedMemory.setKey("CopyDroid");
    if(sharedMemory.attach()) {
        return 0;
    }

    if (!sharedMemory.create(1)) {
        return 0; // Exit already a process running
    }
    /* end sharedMemory */

    Widget w;
    w.setVisible(false); //replaced w.show(); to start minimized

    return a.exec();
}
