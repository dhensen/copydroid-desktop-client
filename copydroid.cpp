#include "copydroid.h"

CopyDroid::CopyDroid(QUuid uuid) : nam(new QNetworkAccessManager)
{
    this->uuid = uuid;
}

CopyDroid::~CopyDroid()
{
    delete nam;
}

void CopyDroid::PostMessage(QString message)
{
    QNetworkRequest request = QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray postData = QByteArray();
    postData.append("action=sendMessage&uid="+uuid.toString()+"&message="+message);
    nam->post(request, postData);
}

void CopyDroid::PostLinkRequest()
{
    QNetworkRequest request = QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray postData = QByteArray();
    postData.append("action=requestLink&uid="+uuid.toString());
    nam->post(request, postData);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(ProcessLinkRequest(QNetworkReply*)));
}

void CopyDroid::ProcessLinkRequest(QNetworkReply *reply)
{
    QDomDocument *xmlDocument = new QDomDocument();
    xmlDocument->setContent(reply);

    disconnect(nam, 0, 0, 0);

    QDomNodeList list = xmlDocument->elementsByTagName("LinkRequest");

    if (!list.isEmpty()) {
        QDomElement linkRequestNode = list.at(0).toElement();
        if (linkRequestNode.hasAttribute("value")) {
            linkRequestValue = linkRequestNode.attributeNode("value").value();
        }
    }

    emit linkRequestValueChanged(linkRequestValue);
}

void CopyDroid::PostLinkRequestStatus(QString link_request_value)
{
    QNetworkRequest request = QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray postData = QByteArray();
    postData.append("action=requestLinkStatus&uid="+uuid.toString()+"&link_request_value="+link_request_value);
    nam->post(request, postData);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(ProcessLinkRequestStatus(QNetworkReply*)));
}

void CopyDroid::ProcessLinkRequestStatus(QNetworkReply *reply)
{
    QDomDocument *xmlDocument = new QDomDocument();
    xmlDocument->setContent(reply);

    disconnect(nam, 0, 0, 0);

    QString linkRequestStatus;

    QDomNodeList list = xmlDocument->elementsByTagName("LinkRequestStatus");

    if (!list.isEmpty()) {
        QDomElement linkRequestStatusNode = list.at(0).toElement();
        if (linkRequestStatusNode.hasAttribute("success")) {
            linkRequestStatus = linkRequestStatusNode.attributeNode("success").value();
        }
    }

    emit linkRequestStatusChanged(linkRequestStatus.compare("1") == 0);
}

void CopyDroid::PostListDevices()
{
    QNetworkRequest request = QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray postData = QByteArray();
    postData.append("action=listDevices&uid="+uuid.toString());
    nam->post(request, postData);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(ProcessListDevices(QNetworkReply*)));
}

void CopyDroid::ProcessListDevices(QNetworkReply *reply)
{
    QDomDocument *xmlDocument = new QDomDocument();
    xmlDocument->setContent(reply);

    disconnect(nam, 0, 0, 0);

    QDomNodeList list = xmlDocument->elementsByTagName("Device");

    emit updateDeviceList(list);
}

void CopyDroid::PostUnlinkDevice(QString uid)
{
    QNetworkRequest request = QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray postData = QByteArray();
    postData.append("action=unlinkDevice&uid="+uuid.toString()+"&uid2="+uid);
    nam->post(request, postData);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(ProcessUnlinkDevice(QNetworkReply*)));
}

void CopyDroid::ProcessUnlinkDevice(QNetworkReply *reply)
{
    QDomDocument *xmlDocument = new QDomDocument();
    xmlDocument->setContent(reply);

    disconnect(nam, 0, 0, 0);

    QString linkRequestStatus;
    QDomNodeList list = xmlDocument->elementsByTagName("UnlinkDevice");

    if (!list.isEmpty()) {
        QDomElement linkRequestStatusNode = list.at(0).toElement();
        if (linkRequestStatusNode.hasAttribute("success")) {
            linkRequestStatus = linkRequestStatusNode.attributeNode("success").value();
        }
    }

    emit unlinkDevice(linkRequestStatus.compare("1") == 0);
}

void CopyDroid::PollLatestMessages()
{
    QNetworkRequest request = QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray postData = QByteArray();
    postData.append("action=latestMessages&uid="+uuid.toString());
    nam->post(request, postData);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(ProcessLatestMessage(QNetworkReply*)));
}

void CopyDroid::ProcessLatestMessage(QNetworkReply *reply)
{
    QDomDocument *xmlDocument = new QDomDocument();
    xmlDocument->setContent(reply);

    disconnect(nam, 0, 0, 0);

    QDomNodeList list = xmlDocument->elementsByTagName("Message");

    emit newMessages(list);
}

void CopyDroid::PostLinkDevice(QString link_request_value)
{
    QNetworkRequest request = QNetworkRequest(QUrl("http://copydroid.com/action.php"));
    QByteArray postData = QByteArray();
    postData.append("action=linkDevice&uid="+uuid.toString()+"&link_request_value="+link_request_value);
    nam->post(request, postData);

    connect(nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(ProcessLinkDevice(QNetworkReply*)));
}

void CopyDroid::ProcessLinkDevice(QNetworkReply *reply)
{
    QDomDocument *xmlDocument = new QDomDocument();
    xmlDocument->setContent(reply);

    disconnect(nam, 0, 0, 0);

    QString linkRequestStatus;
    QDomNodeList list = xmlDocument->elementsByTagName("LinkRequest");

    if (!list.isEmpty()) {
        QDomElement linkRequestStatusNode = list.at(0).toElement();
        if (linkRequestStatusNode.hasAttribute("success")) {
            linkRequestStatus = linkRequestStatusNode.attributeNode("success").value();
        }
    }

    emit linkDevice(linkRequestStatus.compare("1") == 0);
}
