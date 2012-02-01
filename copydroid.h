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
    void PostMessage(QString message);
    void PostLinkRequest(QString uid);
    void PostLinkRequestStatus(QString uid, QString link_request_value);

public slots:
    void ProcessLinkRequest();
    void ProcessLinkRequestStatus();

signals:
    void linkRequestValueChanged(QString);
    void linkRequestStatusChanged(bool);

private:
    QNetworkReply *reply;
    QDomDocument *xmlDocument;
    QString linkRequestValue;
};

#endif // COPYDROID_H
