#ifndef OSRECOGNIZER_H
#define OSRECOGNIZER_H

#include <QObject>

class OSRecognizer : public QObject
{
    Q_OBJECT
public:
    explicit OSRecognizer(QObject *parent = 0);
    static QString getOperatingSystem();

signals:
    
public slots:
    
};

#endif // OSRECOGNIZER_H
