#include "widget.h"
#include "ui_widget.h"

QString Widget::serverName = QString("CopyDroid");

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    localServer = new QLocalServer(this);
    connect(localServer, SIGNAL(newConnection()), this, SLOT(newLocalSocketConnection()));
    localServer->listen(Widget::serverName);

    QCoreApplication::setOrganizationName("CopyDroid");
    QCoreApplication::setOrganizationDomain("copydroid.com");
    QCoreApplication::setApplicationName("CopyDroid");

    qDebug() << QApplication::applicationDirPath();

    createActions();
    createTrayIcon();
    setIcon();

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    readSettings();
    copyDroid = new CopyDroid(uuid);

    alienCopyValue = QString();
    clipboard = QApplication::clipboard();
    connect(clipboard, SIGNAL(dataChanged()), this, SLOT(onDataChanged()));

    ui->setupUi(this);
    connect(ui->attachToDeviceButton, SIGNAL(clicked()), this, SLOT(attachToDevice()));
    connect(ui->addDeviceButton, SIGNAL(clicked()), this, SLOT(addDevice()));
    connect(ui->deleteDeviceButton, SIGNAL(clicked()), this, SLOT(onDeleteDeviceClick()));
    connect(copyDroid, SIGNAL(updateDeviceList(QDomNodeList)), this, SLOT(setDevices(QDomNodeList)));
    connect(copyDroid, SIGNAL(unlinkDevice(bool)), this, SLOT(deleteDevice(bool)));
    connect(copyDroid, SIGNAL(newMessages(QDomNodeList)), this, SLOT(newMessages(QDomNodeList)));

    copyDroid->PostListDevices();

    startPolling();
}

Widget::~Widget()
{
    writeSettings();
    delete ui;
}

void Widget::newLocalSocketConnection()
{
    socket = localServer->nextPendingConnection();
    connect(socket, SIGNAL(readyRead()), this, SLOT(socketReadAction()));
}

void Widget::socketReadAction()
{
    QByteArray data = socket->readAll();

    if (data == "show")
        setVisible(true);
}


void Widget::onDataChanged()
{
    QString currentCopyValue = QString(clipboard->text());

    //    if (alienCopyValue.isEmpty()) {
    //        ui->plainTextEdit->appendPlainText("[empty]");
    //    }

    if (currentCopyValue != alienCopyValue) {
        ui->plainTextEdit->appendPlainText(clipboard->text());
        copyDroid->PostMessage(currentCopyValue);
    }
}

void Widget::attachToDevice()
{
    AttachDialog attachDialog;

    connect(copyDroid, SIGNAL(linkDevice(bool)), &attachDialog, SLOT(linkStatus(bool)));

    attachDialog.setCopyDroid(copyDroid);

    if(attachDialog.exec()) {
        copyDroid->PostListDevices();
    }
}

void Widget::addDevice()
{
    AddDialog addDialog;

    connect(copyDroid, SIGNAL(linkRequestValueChanged(QString)), &addDialog, SLOT(setLinkRequestValueText(QString)));
    connect(copyDroid, SIGNAL(linkRequestStatusChanged(bool)), &addDialog, SLOT(setLinkRequestStatus(bool)));

    addDialog.setCopyDroid(copyDroid);

    if(addDialog.exec()) {
        copyDroid->PostListDevices();
    }
}

void Widget::setDevices(QDomNodeList list)
{
    ui->listWidget->clear();

    int count = list.count();
    for (int i = 0; i < count; i++) {
        QListWidgetItem *item = new QListWidgetItem(list.at(i).toElement().attributeNode("uid").value(), ui->listWidget);
        item->setData(Qt::UserRole, list.at(i).toElement().attributeNode("uid").value());

//        ui->listWidget->addItem(list.at(i).toElement().attributeNode("uid").value());
    }
}

void Widget::onDeleteDeviceClick()
{
    deleteItem = ui->listWidget->currentItem();
    if (deleteItem != NULL) {
        // post delete item to copydroid.com/action.php
        copyDroid->PostUnlinkDevice(deleteItem->data(Qt::UserRole).toString());
    }
}

void Widget::deleteDevice(bool doDelete)
{
    if (doDelete && deleteItem != NULL)
        delete deleteItem;
}

void Widget::readSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());

    // remove curly braces from the UUID
    uuid = QUuid(settings.value("uuid", QUuid::createUuid().toString().mid(1,36)).toString());
}

void Widget::writeSettings()
{
    QSettings settings(QSettings::IniFormat, QSettings::UserScope, QCoreApplication::organizationName(), QCoreApplication::applicationName());
    settings.setValue("uuid", uuid.toString().mid(1,36));
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

void Widget::startPolling()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(poll()));
    timer->start(10000);
}

void Widget::poll()
{
    copyDroid->PollLatestMessages();
}

void Widget::newMessages(QDomNodeList list)
{
    if (!list.isEmpty()) {
        QDomElement message = list.at(0).toElement();
        alienCopyValue = message.text();
        clipboard->setText(alienCopyValue);
    }
}
