#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QClipboard>
#include <QSystemTrayIcon>
#include <QLocalServer>
#include <QLocalSocket>
#include "copydroid.h"
#include "adddialog.h"

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    static QString serverName;

public slots:
    void newLocalSocketConnection();
    void socketReadAction();

    void onDataChanged();
    void addDevice();
    void setDevices(QDomNodeList list);
    void deleteDevice();

private slots:
    void iconActivated(QSystemTrayIcon::ActivationReason reason);

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::Widget *ui;
    QLocalServer *localServer;
    QLocalSocket *socket;
    QUuid uuid;
    CopyDroid *copyDroid;
    QClipboard *clipboard;

    void readSettings();
    void writeSettings();

    QAction *restoreAction;
    QAction *quitAction;
    QMenu *trayIconMenu;
    QSystemTrayIcon *trayIcon;

    void setIcon();
    void createActions();
    void createTrayIcon();

};

#endif // WIDGET_H
