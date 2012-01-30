#include "copydroid.h"

CopyDroid::CopyDroid()
{
}

void CopyDroid::PostMessage(const QString &message)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QNetworkRequest *request = new QNetworkRequest(QUrl("http://copydroid.com/response.php"));
    QByteArray *postData = new QByteArray();
    postData->append("message="+message);
    nam->post(*request, *postData);
}

void CopyDroid::PostLinkRequest(const QString &uid)
{
    QNetworkAccessManager *nam = new QNetworkAccessManager();
    QNetworkRequest *request = new QNetworkRequest(QUrl("http://copydroid.com/response.php"));
    QByteArray *postData = new QByteArray();
    postData->append("link_request=1&uid="+uid);
    reply = nam->post(*request, *postData);

    connect(reply, SIGNAL(finished()), this, SLOT(ProcessLinkRequest()));
}

void CopyDroid::ProcessLinkRequest()
{
    xmlDocument = new QDomDocument("xml");
    xmlDocument->setContent(reply);

    QDomNodeList list = xmlDocument->elementsByTagName("LinkRequest");

    if (!list.isEmpty()) {
        QDomElement linkRequestNode = list.at(0).toElement();
        if (linkRequestNode.hasAttribute("value")) {
            linkRequestValue = linkRequestNode.attributeNode("value").value();
        }
    }

    emit linkRequestValueChanged(linkRequestValue);
}
