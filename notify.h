#ifndef NOTIFY_H
#define NOTIFY_H

#include <QWidget>
#include <QDebug>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>

class Notify : public QWidget
{
    Q_OBJECT

    QVBoxLayout *vlbox;
    QHBoxLayout *hlbox;
    QLabel *label;
    QPushButton *pbutton;
    QCheckBox *checkBox;
    QStringList textList;
public:
    explicit Notify(QWidget *parent = nullptr);
    void setText(QStringList list);

signals:

public slots:
    void slotModeChange(int state);
};

#endif // NOTIFY_H
