#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
//#include <QDebug>
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
    CopyDroid *copyDroid;
    QClipboard *clipboard;
    void createTable();

public slots:
    void onDataChanged();
    void addDevice();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
