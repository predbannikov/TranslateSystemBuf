#include "notify.h"

Notify::Notify(QWidget *parent) : QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
//    setFixedSize(50,50);
    QVBoxLayout vlbox;
    this->setLayout(&vlbox);
    label = new QLabel;
    label->setWordWrap(true);
    vlbox.addWidget(label);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

}

void Notify::setText(QString text)
{
    label->setText(text);
    this->resize(label->size());
}
