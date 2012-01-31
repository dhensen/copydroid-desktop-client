#include "copydroid.h"

CopyDroid::CopyDroid()
{
}

void CopyDroid::PostMessage(const QString &message)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QNetworkRequest *request = new QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray *postData = new QByteArray();
    postData->append("action=sendMessage&message="+message);
    nam->post(*request, *postData);
}

void CopyDroid::PostLinkRequest(const QString &uid)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QNetworkRequest *request = new QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray *postData = new QByteArray();
    postData->append("action=requestLink&uid="+uid);
    reply = nam->post(*request, *postData);

    connect(reply, SIGNAL(finished()), this, SLOT(ProcessLinkRequest()));
}

void CopyDroid::ProcessLinkRequest()
{
    xmlDocument = new QDomDocument("xml");
    xmlDocument->setContent(reply);

    disconnect(reply, 0, 0, 0);

    QDomNodeList list = xmlDocument->elementsByTagName("LinkRequest");

    if (!list.isEmpty()) {
        QDomElement linkRequestNode = list.at(0).toElement();
        if (linkRequestNode.hasAttribute("value")) {
            linkRequestValue = linkRequestNode.attributeNode("value").value();
        }
    }

    emit linkRequestValueChanged(linkRequestValue);
}

void CopyDroid::PostLinkRequestStatus(const QString &uid, const QString &link_request_value)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QNetworkRequest *request = new QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray *postData = new QByteArray();
    postData->append("action=requestLinkStatus&uid="+uid+"&link_request_value="+link_request_value);
    reply = nam->post(*request, *postData);

//    connect(reply, SIGNAL(finished()), this, SLOT(ProcessLinkRequestStatus()));
}

void CopyDroid::ProcessLinkRequestStatus()
{
    xmlDocument = new QDomDocument("xml");
    xmlDocument->setContent(reply);

    disconnect(reply, 0, 0, 0);

    QString linkRequestStatus;

    QDomNodeList list = xmlDocument->elementsByTagName("LinkRequestStatus");

    if (!list.isEmpty()) {
        QDomElement linkRequestStatusNode = list.at(0).toElement();
        if (linkRequestStatusNode.hasAttribute("success")) {
            linkRequestStatus = linkRequestStatusNode.attributeNode("success").value();
        }
    } else {
        qDebug() << "reply finished:" << reply->isFinished();
    }

    bool status = (bool)(linkRequestStatus.compare("1") == 0);
    emit linkRequestStatusChanged(status);
}
