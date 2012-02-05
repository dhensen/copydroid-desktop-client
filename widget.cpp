#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QCoreApplication::setOrganizationName("CopyDroid");
    QCoreApplication::setOrganizationDomain("copydroid.com");
    QCoreApplication::setApplicationName("CopyDroid");

    ui->setupUi(this);
    clipboard = QApplication::clipboard();

    readSettings();

    copyDroid = new CopyDroid(uuid);

    connect(clipboard, SIGNAL(dataChanged()), this, SLOT(onDataChanged()));
    connect(ui->addDeviceButton, SIGNAL(clicked()), this, SLOT(addDevice()));
    connect(ui->deleteDeviceButton, SIGNAL(clicked()), this, SLOT(deleteDevice()));
    connect(copyDroid, SIGNAL(updateDeviceList(QDomNodeList)), this, SLOT(setDevices(QDomNodeList)));

    copyDroid->PostListDevices();

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

    if(aDialog.exec()) {
        copyDroid->PostListDevices();
    } else {
        qDebug("Rejected adding a device, deal with it.");
    }
}

void Widget::setDevices(QDomNodeList list)
{
    qDebug() << "setDevices...";

    ui->listWidget->clear();

    int count = list.count();
    for (int i = 0; i < count; i++) {
        QListWidgetItem *item = new QListWidgetItem(list.at(i).toElement().attributeNode("uid").value(), ui->listWidget);
        item->setData(Qt::UserRole, list.at(i).toElement().attributeNode("id").value());

//        ui->listWidget->addItem(list.at(i).toElement().attributeNode("uid").value());
    }
}

void Widget::deleteDevice()
{
    QListWidgetItem *item = ui->listWidget->currentItem();
    if (item != NULL) {
        // post delete item to copydroid.com/action.php
        delete item;
    }
}

void Widget::readSettings()
{
    QSettings settings;
    uuid = QUuid(settings.value("uuid", QUuid::createUuid().toString()).toString());
    qDebug() << uuid.toString();
}

void Widget::writeSettings()
{
    QSettings settings;
    settings.setValue("uuid", uuid.toString());
}

void Widget::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}
