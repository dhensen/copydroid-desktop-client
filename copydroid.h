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

public slots:
    void PostListDevices();
    void ProcessLinkRequest(QNetworkReply *reply);
    void ProcessLinkRequestStatus(QNetworkReply *reply);
    void ProcessListDevices(QNetworkReply *reply);

signals:
    void linkRequestValueChanged(QString);
    void linkRequestStatusChanged(bool);
    void updateDeviceList(QDomNodeList);

private:
    QUuid uuid;
    QNetworkAccessManager *nam;
    QString linkRequestValue;
};

#endif // COPYDROID_H
