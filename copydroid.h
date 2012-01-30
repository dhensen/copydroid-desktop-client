#ifndef COPYDROID_H
#define COPYDROID_H

#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtXml>

class CopyDroid : public QObject
{
    Q_OBJECT

public:
    CopyDroid();
    void PostMessage(const QString &message);
    void PostLinkRequest(const QString &uid);
    QString getLinkRequestValue();

public slots:
    void ProcessLinkRequest();

signals:
    void linkRequestValueChanged(QString value);

private:
    QNetworkReply *reply;
    QDomDocument *xmlDocument;
    QString linkRequestValue;
};

#endif // COPYDROID_H
