#include <QtGui>
#include "adddialog.h"
#include <windows.h>

AddDialog::AddDialog(QWidget *parent) :
    QDialog(parent)
{
    infoLabel = new QLabel("Fill in the code on the Android device you want to connect with and press OK when you are done.");
    okButton = new QPushButton("OK");
    cancelButton = new QPushButton("Cancel");

    linkRequestValueText = new QLineEdit;
    linkRequestValueText->setReadOnly(true);

    infoLabel->setWordWrap(true);

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(infoLabel, 0, 0);

    gLayout->addWidget(linkRequestValueText, 1, 0, Qt::AlignCenter);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    gLayout->addLayout(buttonLayout, 2, 0, Qt::AlignCenter);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(gLayout);
    setLayout(mainLayout);

    connect(okButton, SIGNAL(clicked()),
            this, SLOT(checkLinkRequestConfirmation()));

    connect(cancelButton, SIGNAL(clicked()),
            this, SLOT(reject()));

    setFixedSize(200, 200);
    setWindowTitle(tr("Add a Device"));

}

void AddDialog::setCopyDroid(CopyDroid *copyDroid)
{
    copyDroid = copyDroid;
    copyDroid->PostLinkRequest("Windows7");
}

void AddDialog::setLinkRequestValueText(QString value)
{
    linkRequestValueText->setText(value);
}

void AddDialog::checkLinkRequestConfirmation()
{
    Sleep(3000);
    accept();
}
