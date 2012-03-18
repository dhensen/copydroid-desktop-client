#include "osrecognizer.h"

OSRecognizer::OSRecognizer(QObject *parent) :
    QObject(parent)
{
}

QString OSRecognizer::getOperatingSystem()
{
#ifdef Q_OS_LINUX
    return "Linux";
#endif

#ifdef Q_OS_WIN

    switch (QSysInfo::windowsVersion())
    {
    case QSysInfo::WV_WINDOWS7:
        return "Windows 7";
        break;
    case QSysInfo::WV_VISTA:
        return "Windows Vista";
        break;
    case QSysInfo::WV_XP:
        return "Windows XP";
        break;
    default:
        return "Windows";
        break;
    }
#endif

#ifdef Q_OS_MAC
    return "Mac";
#endif
}
