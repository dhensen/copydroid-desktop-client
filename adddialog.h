#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QtGui>
#include <QDialog>
#include <QProgressBar>
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
    ~AddDialog();
    QLineEdit *linkRequestValueText;
    void setCopyDroid(CopyDroid *copyDroid);


private:
    QGridLayout *gLayout;
    QLabel *infoLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    CopyDroid *copyDroid;
    QTimer *timer;
    int count;
    QProgressBar *progressBar;
    bool linkRequestStatus;

    
signals:
    
public slots:
    void setLinkRequestValueText(QString value);
    void checkLinkRequestConfirmation();
    void fireTimer();
    void setLinkRequestStatus(bool status);
};

#endif // ADDDIALOG_H
