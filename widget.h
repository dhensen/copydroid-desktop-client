#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QClipboard>
#include <QtSql>
#include <copydroid.h>
#include <adddialog.h>

namespace Ui {
    class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void onDataChanged();
    void addDevice();
    void setDevices(QDomNodeList list);
    void deleteDevice();

protected:
    void closeEvent(QCloseEvent *event);

private:
    Ui::Widget *ui;
    CopyDroid *copyDroid;
    QClipboard *clipboard;
    void createTable();
    void readSettings();
    void writeSettings();
    QUuid uuid;

};

#endif // WIDGET_H
