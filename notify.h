#ifndef NOTIFY_H
#define NOTIFY_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class Notify : public QWidget
{
    Q_OBJECT

    QLabel *label;
public:
    explicit Notify(QWidget *parent = nullptr);
    void setText(QString text);

signals:

public slots:
};

#endif // NOTIFY_H
