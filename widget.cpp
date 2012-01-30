#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    clipboard = QApplication::clipboard();
    copyDroid = new CopyDroid();

    connect(clipboard, SIGNAL(dataChanged()), this, SLOT(copySlot()));
    connect(ui->testButton, SIGNAL(clicked()), this, SLOT(testAction()));
    connect(ui->addDeviceButton, SIGNAL(clicked()), this, SLOT(addDevice()));

    testSQlite();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::testOnChange()
{
    ui->plainTextEdit->appendPlainText(clipboard->text());
}

void Widget::copySlot()
{
    //ui->plainTextEdit->appendPlainText("Clipboard");
    ui->plainTextEdit->appendPlainText(clipboard->text());
    copyDroid->PostMessage(clipboard->text());

}

void Widget::modeTwo()
{
    ui->plainTextEdit->appendPlainText("Selection");
}

void Widget::modeThree()
{
    ui->plainTextEdit->appendPlainText("FindBuffer");
}

void Widget::testAction()
{
    copyDroid->PostMessage("testpostertje");
}

void Widget::testSQlite()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("copydroid");
    bool ok = db.open();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS device ("
               "device_id INTEGER NOT NULL,"
               "device_name VARCHAR(50) NOT NULL,"
               "device_uid VARCHAR(38) NOT NULL,"
               "PRIMARY KEY (device_id) );");

    qDebug() << query.lastError();

    query.exec("DROP TABLE device;");

    qDebug() << query.lastError();

    db.close();
}

void Widget::addDevice()
{
    AddDialog aDialog;
    aDialog.setCopyDroid(copyDroid);
    connect(copyDroid, SIGNAL(linkRequestValueChanged(QString)), &aDialog, SLOT(setLinkRequestValueText(QString)));

    if (aDialog.exec()) {

    }
}
