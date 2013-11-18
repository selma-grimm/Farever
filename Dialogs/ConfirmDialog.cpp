#include "ConfirmDialog.h"

ConfirmDialog::ConfirmDialog(QWidget *parent) :
    QWidget(parent)
  , label_(new QLabel(this))
{    
    setFixedHeight(70);

    QPushButton* pOkBut = new QPushButton("OK", this);
    QPushButton* pCancelBut = new QPushButton("Cancel", this);
    connect(pOkBut, SIGNAL(clicked()), SIGNAL(confirm()));
    connect(pOkBut, SIGNAL(clicked()), SIGNAL(close()));
    connect(pCancelBut, SIGNAL(clicked()), SIGNAL(close()));
    pOkBut->setObjectName("ok_but");
    pCancelBut->setObjectName("cancel_but");
    pOkBut->setFixedSize(70, 26);
    pCancelBut->setFixedSize(70, 26);
    label_->setObjectName("question_label");

    pCancelBut->setDefault(true);

    QGridLayout* pMainLayout = new QGridLayout(this);
    pMainLayout->addWidget(label_, 0, 0, 1, 3);
    pMainLayout->addWidget(pOkBut, 1, 1);
    pMainLayout->addWidget(pCancelBut, 1, 2);

    QSpacerItem* pSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Fixed);
    pMainLayout->addItem(pSpacer, 1, 0);

}

void ConfirmDialog::showDialog(const QString &obj_name)
{
    label_->setText(obj_name);
    show();
}

void ConfirmDialog::keyPressEvent(QKeyEvent* event)
{
    QWidget::keyPressEvent(event);

    switch (event->key())
    {
    case Qt::Key_Enter:
    case 16777220:
        emit confirm();
        emit close();
        break;
    case Qt::Key_Escape:
        emit close();
        break;
    default:
        break;
    }
}

void ConfirmDialog::showEvent(QShowEvent * event)
{
    QWidget::showEvent(event);
    setFocus();
}
