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
    void PostMessage(const QString &message);
    void PostLinkRequest(const QString &uid);
    void PostLinkRequestStatus(const QString &uid, const QString &link_request_value);

public slots:
    void ProcessLinkRequest();
    void ProcessLinkRequestStatus();

signals:
    void linkRequestValueChanged(QString value);
    void linkRequestStatusChanged(bool status);

private:
    QNetworkReply *reply;
    QDomDocument *xmlDocument;
    QString linkRequestValue;
};

#endif // COPYDROID_H
