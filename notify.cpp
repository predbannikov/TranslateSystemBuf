#include "notify.h"

Notify::Notify(QWidget *parent) : QWidget(parent)
{
    setWindowFlag(Qt::FramelessWindowHint);
//    setFixedSize(50,50);
    hlbox = new QHBoxLayout;
    pbutton = new QPushButton("bt");
    checkBox = new QCheckBox("mode");
    connect(checkBox, &QCheckBox::stateChanged, this, &Notify::slotModeChange);

    hlbox->addWidget(pbutton);
    hlbox->addWidget(checkBox);


    vlbox = new QVBoxLayout;
    this->setLayout(vlbox);
    this->setMaximumSize(600, 400);
    this->setMinimumSize(180, 240);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    label = new QLabel;
    label->setWordWrap(true);
    vlbox->addLayout(hlbox);
    vlbox->addWidget(label);

}

void Notify::setText(QStringList list)
{
    textList = list;
    checkBox->setChecked(true);
    slotModeChange(1);
//    label->setText(textList.join("\n"));

//    qDebug() << qPrintable(label->text());
    //    this->resize(label->size());
}

void Notify::slotModeChange(int state)
{
    QString str1;
    if(state) {
        QString str2;
        for(int i = 0; i < textList.size(); i++) {
            if(i%2)
                str2.append("\n" + textList[i]);
            else {
                str1.append("\n" + textList[i]);
            }
        }
        str1.append("\n\n");
        str1.append(str2);
        label->setText(str1);
    } else {
        str1 = textList.join("\n");
        label->setText(str1);
    }

    this->setFocus();
    qDebug() << qPrintable(str1);


}
