#include "attachdialog.h"

AttachDialog::AttachDialog(QWidget *parent) :
    QDialog(parent)
{
    infoLabel = new QLabel("Fill in the code from the Android device you want to connect to and press OK when you are done.");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    linkRequestValueText = new QLineEdit;

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

    connect(okButton, SIGNAL(clicked()), this, SLOT(linkToDevice()));
    connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));

    setFixedSize(200, 200);
    setWindowTitle(tr("Attach to a Device"));
}

AttachDialog::~AttachDialog()
{
}

void AttachDialog::setCopyDroid(CopyDroid *copyDroid)
{
    this->copyDroid = copyDroid;
}

void AttachDialog::linkToDevice()
{
    copyDroid->PostLinkDevice(linkRequestValueText->text());
}

void AttachDialog::linkStatus(bool status)
{
    if (status) {
        accept();
    } else {
        reject();
    }
}
