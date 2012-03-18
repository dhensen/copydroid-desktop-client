#include "adddialog.h"
#include <QTimer>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent)
{
    linkRequestStatus = false;
    infoLabel = new QLabel("Fill in the code on the Android device you want to connect with and press OK when you are done.");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    timer = new QTimer(this);
    linkRequestValueText = new QLineEdit;
    linkRequestValueText->setReadOnly(true);

    infoLabel->setWordWrap(true);

    gLayout = new QGridLayout;
    gLayout->addWidget(infoLabel, 0, 0);

    gLayout->addWidget(linkRequestValueText, 1, 0, Qt::AlignCenter);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 3, 0, Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()), this, SLOT(fireTimer()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setFixedSize(200, 200);
    setWindowTitle(tr("Add a Device"));

}

AddDialog::~AddDialog()
{
}

void AddDialog::setCopyDroid(CopyDroid *copyDroid)
{
    this->copyDroid = copyDroid;
    copyDroid->PostLinkRequest();
}

void AddDialog::setLinkRequestValueText(QString value)
{
    linkRequestValueText->setText(value);
}

void AddDialog::fireTimer()
{
    okButton->setDisabled(true);

    progressBar = new QProgressBar();
    progressBar->setRange(0, 30);
    progressBar->setFixedWidth(130);
    progressBar->setAlignment(Qt::AlignCenter);

    gLayout->addWidget(progressBar, 2, 0, Qt::AlignCenter);

    connect(timer, SIGNAL(timeout()), this, SLOT(checkLinkRequestConfirmation()));

    timer->start(1000);
}

void AddDialog::setLinkRequestStatus(bool status)
{
    linkRequestStatus = status;
}

void AddDialog::checkLinkRequestConfirmation()
{
    progressBar->setValue(progressBar->value()+1);

    if (progressBar->value() >= progressBar->maximum()) {
        disconnect(timer, SIGNAL(timeout()), 0, 0);
        timer->stop();
        reject();
    }

    if (linkRequestStatus) {
        progressBar->setValue(progressBar->maximum());
        disconnect(timer, SIGNAL(timeout()), 0, 0);
        timer->stop();
        accept();
    } else {
        copyDroid->PostLinkRequestStatus(linkRequestValueText->text());
    }

}
