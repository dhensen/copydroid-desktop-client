#ifndef ADDDIALOG_H
#define ADDDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QProgressBar>
#include <copydroid.h>

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
    QProgressBar *progressBar;
    bool linkRequestStatus;

public slots:
    void setLinkRequestValueText(QString value);
    void checkLinkRequestConfirmation();
    void fireTimer();
    void setLinkRequestStatus(bool status);
};

#endif // ADDDIALOG_H
