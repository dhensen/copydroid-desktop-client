#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    QCoreApplication::setOrganizationName("CopyDroid");
    QCoreApplication::setOrganizationDomain("copydroid.com");
    QCoreApplication::setApplicationName("CopyDroid");

    createActions();
    createTrayIcon();
    setIcon();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    readSettings();
    copyDroid = new CopyDroid(uuid);

    clipboard = QApplication::clipboard();
    connect(clipboard, SIGNAL(dataChanged()), this, SLOT(onDataChanged()));

    ui->setupUi(this);
    connect(ui->addDeviceButton, SIGNAL(clicked()), this, SLOT(addDevice()));
    connect(ui->deleteDeviceButton, SIGNAL(clicked()), this, SLOT(deleteDevice()));
    connect(copyDroid, SIGNAL(updateDeviceList(QDomNodeList)), this, SLOT(setDevices(QDomNodeList)));

    copyDroid->PostListDevices();
}

Widget::~Widget()
{
    writeSettings();
    delete ui;
}

void Widget::onDataChanged()
{
    ui->plainTextEdit->appendPlainText(clipboard->text());
    copyDroid->PostMessage(clipboard->text());
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
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}

void Widget::setIcon()
{
    QIcon icon = QIcon(":/copydroid.ico");
    //setWindowIcon(icon);
    trayIcon->setIcon(icon);
    trayIcon->setToolTip("CopyDroid");
    trayIcon->show();
}

void Widget::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason) {
    case QSystemTrayIcon::Trigger:
        break;
    case QSystemTrayIcon::DoubleClick:
        show();
        /*  to put the windows in front of every other window
            (otherwise it sits in background while its focused in taskbar) */
        activateWindow();
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void Widget::createActions()
{
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void Widget::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
}
