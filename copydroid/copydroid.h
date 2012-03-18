#ifndef COPYDROID_H
#define COPYDROID_H

#include <QObject>
#include <QtNetwork>
#include <QtXml>

class CopyDroid : public QObject
{
    Q_OBJECT

public:
    CopyDroid(QUuid uuid);
    ~CopyDroid();
    void PostMessage(QString message);
    void PostLinkRequest();
    void PostLinkRequestStatus(QString link_request_value);
    void PostUnlinkDevice(QString uid);
    void PollLatestMessages();
    void PostLinkDevice(QString link_request_value);
    void PostRegisterDevice(QString device_name);

public slots:
    void PostListDevices();
    void ProcessLinkRequest(QNetworkReply *reply);
    void ProcessLinkRequestStatus(QNetworkReply *reply);
    void ProcessListDevices(QNetworkReply *reply);
    void ProcessUnlinkDevice(QNetworkReply *reply);
    void ProcessLatestMessage(QNetworkReply *reply);
    void ProcessLinkDevice(QNetworkReply *reply);

signals:
    void linkRequestValueChanged(QString);
    void linkRequestStatusChanged(bool);
    void updateDeviceList(QDomNodeList);
    void unlinkDevice(bool);
    void newMessages(QDomNodeList);
    void linkDevice(bool);

private:
    QUuid uuid;
    QNetworkAccessManager *nam;
    QString linkRequestValue;
};

#endif // COPYDROID_H
