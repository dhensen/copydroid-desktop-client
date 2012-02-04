#ifndef COPYDROID_H
#define COPYDROID_H

#include <QObject>
#include <QtNetwork>
#include <QtXml>

class CopyDroid : public QObject
{
    Q_OBJECT

public:
    CopyDroid();
    ~CopyDroid();
    void PostMessage(QString message);
    void PostLinkRequest(QString uid);
    void PostLinkRequestStatus(QString uid, QString link_request_value);
    void PostListDevices(QString uid);

public slots:
    void ProcessLinkRequest(QNetworkReply *reply);
    void ProcessLinkRequestStatus(QNetworkReply *reply);
    void ProcessListDevices(QNetworkReply *reply);

signals:
    void linkRequestValueChanged(QString);
    void linkRequestStatusChanged(bool);
    void updateDeviceList(QDomNodeList);

private:
    QNetworkAccessManager *nam;
    QString linkRequestValue;
};

#endif // COPYDROID_H
