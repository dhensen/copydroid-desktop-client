#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    clipboard = QApplication::clipboard();
    copyDroid = new CopyDroid();

    connect(clipboard, SIGNAL(dataChanged()), this, SLOT(onDataChanged()));
    connect(ui->addDeviceButton, SIGNAL(clicked()), this, SLOT(addDevice()));
    connect(copyDroid, SIGNAL(updateDeviceList(QDomNodeList)), this, SLOT(setDevices(QDomNodeList)));

    copyDroid->PostListDevices("Windows7");

    createTable();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::onDataChanged()
{
    ui->plainTextEdit->appendPlainText(clipboard->text());
    copyDroid->PostMessage(clipboard->text());
}

void Widget::createTable()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("copydroid");
    /*bool ok = */db.open();
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS device ("
               "device_id INTEGER NOT NULL,"
               "device_name VARCHAR(50) NOT NULL,"
               "device_uid VARCHAR(38) NOT NULL,"
               "PRIMARY KEY (device_id) );");
    db.close();
}

void Widget::addDevice()
{
    AddDialog aDialog;

    connect(copyDroid, SIGNAL(linkRequestValueChanged(QString)), &aDialog, SLOT(setLinkRequestValueText(QString)));
    connect(copyDroid, SIGNAL(linkRequestStatusChanged(bool)), &aDialog, SLOT(setLinkRequestStatus(bool)));

    aDialog.setCopyDroid(copyDroid);

    aDialog.exec();
}

void Widget::setDevices(QDomNodeList list)
{
    qDebug() << "setDevices...";
    int count = list.count();
    for (int i = 0; i < count; i++) {
        qDebug() << "setDevice";
        ui->listWidget->addItem(list.at(i).toElement().attributeNode("uid").value());
    }
}
