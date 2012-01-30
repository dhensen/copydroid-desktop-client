#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <copydroid.h>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
class QLineEdit;
QT_END_NAMESPACE

class AddDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddDialog(QWidget *parent = 0);
    QLineEdit *linkRequestValueText;
    void setCopyDroid(CopyDroid *copyDroid);


private:
    QLabel *infoLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    CopyDroid *copyDroid;

    
signals:
    
public slots:
    void setLinkRequestValueText(QString value);
    void checkLinkRequestConfirmation();
};

#endif // ADDDIALOG_H
