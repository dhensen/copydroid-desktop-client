#include <QtGui/QApplication>
#include <QLocalSocket>
#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setQuitOnLastWindowClosed(false);

    QLocalSocket socket;
    QString serverName = QString(Widget::serverName);
    socket.connectToServer(serverName);
    if (socket.waitForConnected(500)) {
        socket.flush();
        socket.write(QByteArray("show"));
        socket.waitForBytesWritten(1000);

        return 0; // Exit already a process running
    }

    Widget w;
    w.show();
//    w.setVisible(false); //replaced w.show(); to start minimized

    return a.exec();
}
