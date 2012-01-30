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
    CopyDroid *copyDroid;
    QClipboard *clipboard;
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void testSQlite();

public slots:
    void testOnChange();
    void testAction();
    void copySlot();
    void modeTwo();
    void modeThree();
    void addDevice();
private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
