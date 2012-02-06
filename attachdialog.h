#ifndef ATTACHDIALOG_H
#define ATTACHDIALOG_H

#include <QDialog>
#include <QtGui>
#include <QProgressBar>
#include <copydroid.h>

class AttachDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AttachDialog(QWidget *parent = 0);
    ~AttachDialog();
    QLineEdit *linkRequestValueText;
    void setCopyDroid(CopyDroid *copyDroid);

private:
    QGridLayout *gLayout;
    QLabel *infoLabel;
    QPushButton *okButton;
    QPushButton *cancelButton;
    CopyDroid *copyDroid;

signals:
    
public slots:
    void linkToDevice();
    void linkStatus(bool status);

};

#endif // ATTACHDIALOG_H
